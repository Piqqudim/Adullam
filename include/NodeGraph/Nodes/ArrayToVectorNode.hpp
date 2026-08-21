#pragma once
#include<VectorDataNodeData.hpp>
#include<NodeInitializer.hpp>
#include<NodeDelegateModel>
#include<DataArrayNode.hpp>
#include<ShapeNodeData.hpp>

#include<memory>
#include<iostream>
using namespace std;
using QtNodes::NodeDelegateModel;
//For Shape case
class ArrayToVectorNode:public NodeDelegateModel,public NodeInitializer{
private:

std::weak_ptr<DataArrayNode<5,ShapeNodeData>> InputShape_1;
std::weak_ptr<DataArrayNode<5,ShapeNodeData>> InputShape_2;
std::shared_ptr<VectorDataNode<ShapeNodeData>> output_shape;
std::vector<ShapeNodeData> outputData;
std::array<ShapeNodeData,10> shapearray;

public:
ArrayToVectorNode(){
   outputData.reserve(10); //reallocates when elements are more than 10;
}
unsigned int nPorts(PortType portType) const override{
    switch(portType){
        case PortType::In:{
            return 2;  //number of input node
        }
        case PortType::Out:{
            return 1;
        }
        default:
           return 0;
    }
    return 0;
}
QString caption() const override{
    return tr("Arrays To Vector(Shape)");
}
QString name() const override{
    return caption();
}

NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::In:{
            switch(portIndex){
                case 0:
                  return DataArrayNode<5,ShapeNodeData>(tr("Array"),tr("ArrayOfShape")).type();
                case 1:
                  return DataArrayNode<5,ShapeNodeData>(tr("Array"),tr("ArrayOfShape")).type();
            }
        }
        case PortType::Out:{
            switch(portIndex){
                case 0:                  //name        //name of type
                   return VectorDataNode<ShapeNodeData>(tr("Vector"),tr("VectorOfShape")).type();


            }
        }
    }
     return {tr(""),tr("")};
}
//Fill the index 0 collection of shapes first before filling the index 1 collection
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
    if(!data.get()){
      return;
    }
   
    switch(portIndex){
        case 0:{
             InputShape_1=std::dynamic_pointer_cast< DataArrayNode<5,ShapeNodeData>>(data);
             if(InputShape_1.lock()){
              
              for(int i=0;i<InputShape_1.lock()->Size();i++){
                  shapearray[i]=InputShape_1.lock()->GetValueAt(i);
                 }
                 
             }
             std::cout<<"First Array Set"<<"\n";
             break;
        }
      case 1:{
          InputShape_2=std::dynamic_pointer_cast< DataArrayNode<5,ShapeNodeData>>(data);
          if(InputShape_2.lock()){
            int j=InputShape_2.lock()->Size();
             for(int i=0;i<InputShape_2.lock()->Size();i++){
                 
                   shapearray[i+j]=InputShape_2.lock()->GetValueAt(i);
                 }
          }
          std::cout<<"Second Array Set"<<"\n";
             break;
      }
    }
    if(output_shape){
        if(!outputData.empty()){
            outputData.clear();
        }
        for(int i=0;i<shapearray.size();i++){
                cout<<i<<"'s Shape Index:"<<shapearray.at(i).index()<<"\n";
                outputData.emplace_back(shapearray.at(i).aspect(),shapearray.at(i).Data(),shapearray.at(i).index());
            
        }
       output_shape->SetData(outputData);
    }
    else{
      output_shape=std::make_shared<VectorDataNode<ShapeNodeData>>(tr(""));
      if(!outputData.empty()){
            outputData.clear();
        }
        for(int i=0;i<shapearray.size();i++){
                 cout<<i<<"'s Shape Index:"<<shapearray.at(i).index()<<"\n";
                outputData.emplace_back(shapearray.at(i).aspect(),shapearray.at(i).Data(),shapearray.at(i).index());
            
        }
      output_shape->SetData(outputData);
    }
    emit dataUpdated(0);
    //try to implement an algorithm to remove duplicates......
    return;
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(output_shape.get()){
      return static_pointer_cast<NodeData>(output_shape);
      
    }
   std::shared_ptr<NodeData> mptr;
   return mptr;      
       
 
   

}
QWidget* embeddedWidget () override{
    return nullptr;
}
};