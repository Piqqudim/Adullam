#pragma once
#include<NodeInitializer.hpp>
#include<NodeDelegateModel>
#include<TransformNodeData.hpp>

#include<JsonShapeConverter.hpp>
#include<memory>
using namespace std;
using namespace QtNodes;
using namespace JsonConverter;
class SinglyTransformNode:public NodeDelegateModel,public NodeInitializer{
private:
gp_Trsf InputValue;
std::shared_ptr<TransformNodeData> output_data;
public:
SinglyTransformNode(){

}
void SetTransformData(const gp_Trsf& transform){
    InputValue=transform;
    emit dataUpdated(0);
    return;
}
void SetTransform(const gp_Trsf& trans){
    InputValue=trans;
    return;    
}
QJsonObject save() const override{
    QJsonObject object=NodeDelegateModel::save();
    QJsonArray transArray;
    transArray.append(ToJsonTranslate(InputValue.TranslationPart()));
    transArray.append(ToJsonQuaternion(InputValue.GetRotation()));
    QJsonObject sFactor;
    sFactor["Scale Factor"]=InputValue.ScaleFactor();
    transArray.append(sFactor);
    object["Transform"]=transArray;
    return object;
}
void load(const QJsonObject& object) override{
    QJsonArray transArray=object["Transform"].toArray();
    InputValue.SetTranslationPart(ToVector(transArray.at(0).toObject()));
    InputValue.SetRotation(ToQuat(transArray.at(1).toObject()));
    QJsonObject sObject=transArray.at(2).toObject();
    InputValue.SetScaleFactor(sObject["Scale Factor"].toDouble());
    
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
    return tr("Transform Node");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::Out:{
            switch(portIndex){
                case 0:
                   return TransformNodeData(tr("Output Transform")).type();

            }
        }
    }
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(output_data.get()){
        output_data->SetData(InputValue);
        return std::static_pointer_cast<NodeData>(output_data);
    }
   output_data=std::make_shared<TransformNodeData>(tr(""));
    output_data->SetData(InputValue);
    return std::static_pointer_cast<NodeData>(output_data);
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
   return;
}
QWidget* embeddedWidget() override{ 
   return nullptr;
 }
};