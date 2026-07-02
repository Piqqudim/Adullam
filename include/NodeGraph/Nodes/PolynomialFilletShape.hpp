#pragma once
#include<ChFi3d_FilletShape.hxx>
#include<IntegerNodeData.hpp>
#include<memory>
#include<NodeDelegateModel>
using namespace std;
using namespace QtNodes;
class PolynomialFilletShape:public NodeDelegateModel{
private:
std::shared_ptr<TemplatedData<ChFi3d_FilletShape>> chdata;
ChFi3d_FilletShape chType=ChFi3d_Polynomial;
public:
PolynomialFilletShape(){
    chdata=std::make_shared<TemplatedData<ChFi3d_FilletShape>>(tr(""),tr(""));
    chdata->SetData(chType);
    return;
}
QString caption() const override{
    return tr("Polynomial FilletTypeShape");
}
QString name() const{
    return caption();
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
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::Out:{
            switch(portIndex){
                case 0:
                   return TemplatedData<ChFi3d_FilletShape>(tr("Fillet Type"),tr("Fillet Type")).type();
            }
        }
    }
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
  return static_pointer_cast<NodeData>(chdata);
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
   return;
}
QWidget* embeddedWidget() override{
  return nullptr;
}

};

class QuasiAngularFilletShape:public NodeDelegateModel{
private:
std::shared_ptr<TemplatedData<ChFi3d_FilletShape>> chdata;
ChFi3d_FilletShape chType=ChFi3d_QuasiAngular;
public:
QuasiAngularFilletShape(){
    chdata=std::make_shared<TemplatedData<ChFi3d_FilletShape>>(tr(""),tr(""));
    chdata->SetData(chType);
    return;
}
QString caption() const override{
    return tr("QuasiAngular FilletTypeShape");
}
QString name() const{
    return caption();
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
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::Out:{
            switch(portIndex){
                case 0:
                   return TemplatedData<ChFi3d_FilletShape>(tr("Fillet Type"),tr("Fillet Type")).type();
            }
        }
    }
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
  return static_pointer_cast<NodeData>(chdata);
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
   return;
}
QWidget* embeddedWidget() override{
  return nullptr;
}
};
