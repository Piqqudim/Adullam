#pragma once
#include<NodeDelegateModel>
#include<MaterialNodeData.hpp>

#include<memory>
using namespace std;
using namespace QtNodes;

//so we can not apply material properties to objects of type 5 to 7
class SinglyMaterialNode:public NodeDelegateModel{
private:
shared_ptr<MaterialNodeData> output_data;
Graphic3d_MaterialAspect mat;

public:
SinglyMaterialNode(){
    return;
}
void SetMaterial(const Graphic3d_MaterialAspect& mat1){
  mat=mat1;
  if(output_data){
    output_data->SetData(mat);
  }
  else{
    output_data=std::make_unique<MaterialNodeData>(tr(""));
    output_data->SetData(mat);
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
    return tr("Singly Material Node");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::Out:{
            switch(portIndex){
                case 0:
                   return MaterialNodeData(tr("Output Material")).type();

            }
        }
    }
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(output_data){
        output_data->SetData(mat);
    }
    return std::static_pointer_cast<NodeData>(output_data);
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
   return;
}
QWidget* embeddedWidget() override{ 
   return nullptr;
 }
};