#pragma once
#include<NodeDelegateModel>
#include<memory>
#include<gp_Ax1.hxx>
#include<gp_Dir.hxx>
#include<NodeInitializer.hpp>
#include<AxisNodeData.hpp>
using namespace std;
using namespace QtNodes; 
class InvertDirectionNode:public NodeDelegateModel,public NodeInitializer{
private:
std::weak_ptr<AxisNodeData> inputData;
shared_ptr<AxisNodeData> axisData;
gp_Ax2 outputAxis;
bool isInverted=false; //the stores the state of whether outputAxis is negated

public:
InvertDirectionNode(){
    return;
}
unsigned int nPorts(PortType portType) const override{
    switch(portType){
        case PortType::In:{
            return 1;
        }
        case PortType::Out:{
            return 1;
        }
    }
    return 0;
}
void SetToFalse() override{
    isInverted=false;
    return;
}
QString caption() const override{
    return tr("Invert Dir");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::Out:{
            switch(portIndex){
                case 0:
                   return AxisNodeData(tr("Output Dir")).type();

            }
        }
     case PortType::In:{
          if(portIndex==0){
            return AxisNodeData(tr("Input Dir")).type();
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
        inputData=dynamic_pointer_cast<AxisNodeData>(data);
        if(inputData.lock()){
            outputAxis=inputData.lock()->Data();
            isInverted=false;
        }
    }
   }
   if(axisData){
    if(isInverted==false){
        gp_Dir ax=outputAxis.Direction().Reversed();
        outputAxis.SetDirection(ax);
        isInverted=true;
    }
    axisData->SetData(outputAxis);
   }
   else{
    axisData=std::make_shared<AxisNodeData>(tr(""));
    if(isInverted==false){
        gp_Dir ax=outputAxis.Direction().Reversed();
        outputAxis.SetDirection(ax);
        isInverted=true;
    }
    axisData->SetData(outputAxis);
   }
   return;
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(axisData){
        return std::static_pointer_cast<AxisNodeData>(axisData);
    }
    std::shared_ptr<NodeData> mptr;
    return mptr;
}
QWidget* embeddedWidget() override{
  return nullptr;
}
};