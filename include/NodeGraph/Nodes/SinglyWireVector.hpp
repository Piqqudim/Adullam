#pragma once
#include<WireNodeData.hpp>
#include<VectorDataNodeData.hpp>
#include<NodeDelegateModel>
#include<memory>
using namespace std;
using namespace QtNodes;
class SinglyWireVector:public NodeDelegateModel{
private:
std::shared_ptr<VectorDataNode<WireNodeData>> outputData;
std::vector<TopoDS_Wire> wires;



public:
SinglyWireVector(){
    return;
}
void SetWires(const vector<TopoDS_Wire>& wires_1){
  if(wires_1.empty()){
    return;
  }
  wires=wires_1;
  if(outputData){
   std::vector<WireNodeData> wirenodedatas;
   for(int i=0;i<wires.size();i++){
     wirenodedatas.emplace_back(wires.at(i));
   }
   outputData->SetData(wirenodedatas);
  }
  else{
     outputData=make_shared<VectorDataNode<WireNodeData>>();
      std::vector<WireNodeData> wirenodedatas;
   for(int i=0;i<wires.size();i++){
     wirenodedatas.emplace_back(wires.at(i));
   }
   outputData->SetData(wirenodedatas);
  }
  emit dataUpdated(0);
  return;
}
unsigned int nPorts(PortType portType) const override{
    switch(portType){
        case PortType::In:{
            return 0;
        }
        case PortType::Out:{
            return 1;
        } 
       
    }
    return 0;
}
QString caption() const override{
    return tr("Wires");
}
QString name() const override{
    return caption();
}
//VectorDataNode(tr("Inputs"),tr("wires")).type();
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::Out:{
            switch(portIndex){
                case 0:
                   return VectorDataNode<WireNodeData>(tr("outputs"),tr("wires")).type();

            }
        }
    }
    return {tr(""),tr("")};
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(outputData){
        return static_pointer_cast<NodeData>(outputData);
    }
    return std::static_pointer_cast<NodeData>(outputData);
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
   return;
}
QWidget* embeddedWidget() override{ 
   return nullptr;
 }
};