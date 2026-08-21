#pragma once 
#include<DataArrayNode.hpp>
#include<NodeDelegateModel>
#include<ShapeNodeData.hpp>
#include<VectorDataNodeData.hpp>
#include<InfoUtility.hpp>
#include<iostream>
#include<memory>
using namespace INFO;
using namespace std;
using namespace QtNodes;
class ArrayVectorNode:public NodeDelegateModel{
private:
std::weak_ptr<VectorDataNode<ShapeNodeData>> shape_1;
std::weak_ptr<DataArrayNode<5,ShapeNodeData>> shape_2;
std::vector<ShapeNodeData> shapedata;
std::array<ShapeNodeData,5> shapearray;
std::shared_ptr<VectorDataNode<ShapeNodeData>> output_data;

public:
ArrayVectorNode(){

}
unsigned int nPorts(PortType portType) const override{
    switch(portType){
        case PortType::In:{
            return  2;
        }
        case PortType::Out:{
            return 1;
        }
        default:
         break;
    }
    return 0;
}
QString caption() const override{
    return tr("ArrayVector Of Shape Node");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::In:{
            switch(portIndex){
                case 0:{
                    return VectorDataNode<ShapeNodeData>(tr("Vector Of Shapes"),tr("VectorOfShape")).type();
                }
              case 1:{
                     return DataArrayNode<5,ShapeNodeData>(tr("Array Of Shapes"),tr("ArrayOfShape")).type();
              }
             

            }
        }
      case PortType::Out:{
            if(portIndex==0){
                return VectorDataNode<ShapeNodeData>(tr("Output Shapes"),tr("VectorOfShape")).type();

            }
        }
    
    }
    return {tr(""),tr("")};
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
 if(!data){
    return;
 }
  
 switch(portIndex){
   case 0:{
    shape_1=dynamic_pointer_cast<VectorDataNode<ShapeNodeData>>(data);
    if(shape_1.lock()){
       if(!shapedata.empty()){
        shapedata.clear();
       }
        for(int i=0;i<shape_1.lock()->Size();i++){
            shapedata.emplace_back(shape_1.lock()->GetValue(i).aspect(),shape_1.lock()->GetValue(i).Data(),shape_1.lock()->GetValue(i).index());
        }
    }
    break;
   }
   case 1:{
     shape_2=dynamic_pointer_cast<DataArrayNode<5,ShapeNodeData>>(data);
     if(shape_2.lock()){
        for(int i=0;i<shape_2.lock()->Size();i++){
            shapearray[i]=shape_2.lock()->GetValueAt(i);
        }
     }
     break;
   }
   }
   if(output_data){
     std::vector<ShapeNodeData> shapeVector;
     
     if(!shapedata.empty()){
     for(int i=0;i<shapedata.size();i++){
        cout<<i<<"'s Shape Index:"<<shapedata.at(i).index()<<"\n";
        shapeVector.emplace_back(shapedata.at(i).aspect(),shapedata.at(i).Data(),shapedata.at(i).index());

     }
     }
     for(int i=0;i<shapearray.size();i++){
        cout<<i<<"'s Shape Index:"<<shapearray.at(i).index()<<"\n";
        shapeVector.emplace_back(shapearray[i].aspect(),shapearray[i].Data(),shapearray[i].index());

     }
     output_data->SetData(shapeVector);
}
 else{
    output_data=std::make_shared<VectorDataNode<ShapeNodeData>>(tr(""),tr(""));
     std::vector<ShapeNodeData> shapeVector;
     if(!shapedata.empty()){
     for(int i=0;i<shapedata.size();i++){
         cout<<i<<"'s Shape Index:"<<shapedata.at(i).index()<<"\n";
        shapeVector.emplace_back(shapedata.at(i).aspect(),shapedata.at(i).Data(),shapedata.at(i).index());

     }
     }
     for(int i=0;i<shapearray.size();i++){
         cout<<i<<"'s Shape Index:"<<shapearray.at(i).index()<<"\n";
        shapeVector.emplace_back(shapearray[i].aspect(),shapearray[i].Data(),shapearray[i].index());

     }
     output_data->SetData(shapeVector);
 }
 emit dataUpdated(0);
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(output_data.get()){
      return static_pointer_cast<NodeData>(output_data);
      
    }
   std::shared_ptr<NodeData> mptr;
   return mptr;      
}
QWidget* embeddedWidget () override{
    return nullptr;
}
};