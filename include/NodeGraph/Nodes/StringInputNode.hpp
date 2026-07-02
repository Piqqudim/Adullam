#ifndef STRING_INPUT_NODE_HPP
#define STRING_INPUT_NODE_HPP
#include<NodeDelegateModel>
#include<NodeDescription.hpp>
#include<memory>
#include<StringNodeData.hpp>
using namespace std;
using namespace QtNodes;
class StringInputNode:public QtNodes::NodeDelegateModel{
private:
shared_ptr<StringNodeData> output_data;
QString output;

public:
StringInputNode(){

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
void SetData(const QString& data){
    output=data;
    if(output_data){
        output_data->SetData(output);
    }
    else{
        output_data=std::make_shared<StringNodeData>(tr(""));
        output_data->SetData(output);
    }
    emit dataUpdated(0);
    return;
}
QString Data() const{
    return output;
}
QString caption() const override{
    return tr("String");
} 
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
     switch(portType){
        case PortType::Out:{
            switch(portIndex){
                case 0:
                   return StringNodeData(tr("Output")).type();
            }
        }
    }
    return {tr(""),tr("")};
}
std::shared_ptr<NodeData> outData(PortIndex port)  override{
    if(output_data){
        return static_pointer_cast<NodeData>(output_data);
    }
    std::shared_ptr<NodeData> mptr;
    return mptr;
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
    return;
}
QWidget* embeddedWidget() override{
    return nullptr;
}
};








#endif