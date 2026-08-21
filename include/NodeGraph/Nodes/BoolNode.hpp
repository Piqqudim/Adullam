#pragma once 
#include<NodeDelegateModel>
#include<BooleanNodeData.hpp>
#include<JsonShapeConverter.hpp>
#include<memory>
using namespace std;
using namespace QtNodes;
class BoolNode:public NodeDelegateModel{
private:
std::shared_ptr<BooleanNodeData> outputData;
bool value;


public:
BoolNode(){
    return;
}
bool Value() const{
    return value;
}
QJsonObject save() const override{
    QJsonObject object=NodeDelegateModel::save();
    object["Value"]=value;
    return object;
}
void load(const QJsonObject& object) override{
    value=object["Value"].toBool();
    return;
}
void SetValue(const bool& val){
  value=val;
  if(outputData){
    outputData->SetData(value);
  }
  else{
    outputData=std::make_shared<BooleanNodeData>(tr(""));
    outputData->SetData(value);
  }
  emit dataUpdated(0); 
  return;
}
void SetBoolData(bool ch){
    value=ch;
    return;
}
void UpdateData(){
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
}
QString caption() const override{
    return tr("Bool Node");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::Out:{
            switch(portIndex){
                case 0:
                   return BooleanNodeData(tr("Value")).type();

            }
        }
    }
     return {tr(""),tr("")};
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
   if(outputData){
     return static_pointer_cast<NodeData>(outputData);
   }
   outputData=std::make_shared<BooleanNodeData>(tr(""));
   outputData->SetData(value);
  
  return static_pointer_cast<NodeData>(outputData);
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
   return;
}
QWidget* embeddedWidget() override{ 
   return nullptr;
 }
};