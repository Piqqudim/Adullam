#ifndef INTEGER_INPUT_NODE_HPP
#define INTEGER_INPUT_NODE_HPP
#include<IntegerNodeData.hpp>
#include<NodeDelegateModel>
#include<NodeDescription.hpp>
#include<QtCore/QJsonObject>
#include<memory>
using namespace std;
using namespace QtNodes;
class IntegerInputNode:public QtNodes::NodeDelegateModel{
private:
std::shared_ptr<IntegerNodeData> output_data;
int output=0;
public:
IntegerInputNode(){
   return;
}
QJsonObject save() const override{
    QJsonObject object=NodeDelegateModel::save();
    object["IntegerValue"]=output;
    return object;
}
void load(const QJsonObject& object) override{
    int d=object["IntegerValue"].toInt();
    SetIntData(d);
    return;
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
void SetIntData(const int& val){
    output=val;
    return;
}
void DataUpdated(){
    emit dataUpdated(0);
    return;
}
void SetOutput(const int& output_1){
    output=output_1;
    if(output_data){
        output_data->SetData(output);
    }
    else{
        output_data=std::make_shared<IntegerNodeData>(tr(""));
        output_data->SetData(output);
    }
    emit dataUpdated(0);
    return;
}
int Output() const {
    return output;
}
QString caption() const override{
    return tr("Integer");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
     switch(portType){
        case PortType::Out:{
            switch(portIndex){
                case 0:
                   return IntegerNodeData(0,tr("")).type();
            }
        }
    }
}
std::shared_ptr<NodeData> outData(PortIndex port)  override{
    if(output_data){
        output_data->SetData(output);
    }
    else{
        output_data=std::make_shared<IntegerNodeData>(tr(""));
        output_data->SetData(output);
    }
    return static_pointer_cast<NodeData>(output_data);
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
    return;
}
QWidget* embeddedWidget() override{ return nullptr;}

};








#endif