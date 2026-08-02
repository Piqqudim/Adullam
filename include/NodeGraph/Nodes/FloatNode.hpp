#pragma once 
#include<NodeDelegateModel>
#include<FloatNodeData.hpp>
#include<memory>
#include<QtCore/QJsonObject>

using namespace std;
using namespace QtNodes;
class FloatNode:public NodeDelegateModel{
    private:
    shared_ptr<FloatNodeData> outputData;
    float Data=1.0f;
public:
FloatNode(){
    return;
}
QJsonObject save() const override{
    QJsonObject object=NodeDelegateModel::save();
    object["Value"]=Data;
    return object;
}
void load(const QJsonObject& object) override{
    Data=object["Value"].toDouble(1.0);
   SetFloatData(Data);
    return;
}
void UpdateData(){
    emit dataUpdated(0);
}
void SetFloatData(const float& d){
    Data=d;
    if(outputData){
        outputData->SetData(d);
    }
    else{
        outputData=std::make_shared<FloatNodeData>(tr(""));
        outputData->SetData(d);
    }
    return;
}
void SetData(const float& d){
    Data=d;
    if(outputData){
        outputData->SetData(d);
    }
    else{
        outputData=std::make_shared<FloatNodeData>();
        outputData->SetData(d);
    }
     emit dataUpdated(0);
    return;
}
float GetData() const{
    return Data;
}
unsigned int nPorts(PortType portType) const override{
    switch(portType){
        case PortType::Out:{
            return 1;  //number of output node
        }
        default:
           return 0;
    }
    return 0;
}
QString caption() const override{
    return tr("Float");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::Out:{
            switch(portIndex){
                case 0:
                   return FloatNodeData(tr("float")).type();
            }
        }
    }
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(outputData){
        return std::static_pointer_cast<NodeData>(outputData);
    }
    outputData=std::make_shared<FloatNodeData>(tr(""));
    outputData->SetData(Data);
    return static_pointer_cast<FloatNodeData>(outputData);
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
   return;
}
QWidget* embeddedWidget() override{
  return nullptr;
}  
};