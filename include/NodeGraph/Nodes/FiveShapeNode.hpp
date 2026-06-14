#pragma once
#include<DataArrayNode.hpp>
#include<NodeDelegateModel>
#include<ShapeNodeData.hpp>
#include<memory>
#include<iostream>
using namespace QtNodes;
using namespace std;
class FiveShapeNode:public NodeDelegateModel{
private:
std::weak_ptr<ShapeNodeData> shape_1;

std::shared_ptr<DataArrayNode<5,ShapeNodeData>> outputData;
std::array<ShapeNodeData,5> outputArray;

public:
FiveShapeNode(){

}
unsigned int nPorts(PortType portType) const override{
    switch(portType){
        case PortType::In:{
            return  5;
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
    return tr("Five Shape Node");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::In:{
            switch(portIndex){
                case 0:{
                    return ShapeNodeData(tr("1st Shape")).type();
                }
              case 1:{
                     return ShapeNodeData(tr("2nd Shape")).type();
              }
              case 2:{
                      return ShapeNodeData(tr("3rd Shape")).type();
              }
              case 3:{
                    return ShapeNodeData(tr("4th Shape")).type();    
              }
            case 4:{
                   return ShapeNodeData(tr("5th Shape")).type();
            }

            }
        }
      case PortType::Out:{
            if(portIndex==0){
                return DataArrayNode<5,ShapeNodeData>(tr("Output Shapes"),tr("ArrayOfShape")).type();

            }
        }
    
    }

}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
  if(!data){
    return;
  }
  switch(portIndex){
     case 0:{
        shape_1=dynamic_pointer_cast<ShapeNodeData>(data);
        if(shape_1.lock()){
            outputArray[0]=*shape_1.lock().get();
            std::cout<<"First Value of Array Data is Set"<<"\n";
            std::cout<<"First Value's Index"<<outputArray[0].index()<<"\n";

            break;
        }
     }
      case 1:{
        shape_1=dynamic_pointer_cast<ShapeNodeData>(data);
        if(shape_1.lock()){
            outputArray[1]=*shape_1.lock().get();
             std::cout<<"Second Value of Array Data is Set"<<"\n";
            std::cout<<"Second Value's Index"<<outputArray[1].index()<<"\n";

            break;
        }
     }
     case 2:{
        shape_1=dynamic_pointer_cast<ShapeNodeData>(data);
        if(shape_1.lock()){
            outputArray[2]=*shape_1.lock().get();
             std::cout<<"Third Value of Array Data is Set"<<"\n";
            std::cout<<"Third Value's Index"<<outputArray[2].index()<<"\n";
            break;
        }
     }
    case 3:{
        shape_1=dynamic_pointer_cast<ShapeNodeData>(data);
        if(shape_1.lock()){
            outputArray[3]=*shape_1.lock().get();
             std::cout<<"Fourth Value of Array Data is Set"<<"\n";
            std::cout<<"Fourth Value's Index"<<outputArray[3].index()<<"\n";
            break;
        }
     } 
    case 4:{
        shape_1=dynamic_pointer_cast<ShapeNodeData>(data);
        if(shape_1.lock()){
            outputArray[4]=*shape_1.lock().get();
             std::cout<<"Fifth Value of Array Data is Set"<<"\n";
            std::cout<<"Fifth Value's Index"<<outputArray[4].index()<<"\n";
            break;
        }
     }
  }
  if(outputData){
    outputData->SetData(outputArray);

  }
  else{
    outputData=std::make_shared<DataArrayNode<5,ShapeNodeData>>(tr(""),tr(""));
     outputData->SetData(outputArray);
  }
  emit dataUpdated(0);
  return;
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
  if(outputData){
    return std::static_pointer_cast<NodeData>(outputData);
  }
  std::shared_ptr<NodeData> mptr;
  return mptr;  
}
QWidget* embeddedWidget() override{return nullptr;}
};