#pragma once
#include<ShapeNodeData.hpp>
#include<memory>



#include<NodeInitializer.hpp>
#include<MaterialNodeData.hpp>
#include<NodeDelegateModel>



#include<iostream>
using namespace QtNodes;
using namespace std;

//this should contain ShouldSend Variable,ShouldKeep Variable, Transform Variable and etc;
class PrimitiveShapeNode:public NodeDelegateModel,public NodeInitializer{
private:

weak_ptr<ShapeNodeData> input_data; //0-index
shared_ptr<ShapeNodeData> output_data;
std::weak_ptr<MaterialNodeData> inputMaterial;



public:
TopoDS_Shape outputShape;
Graphic3d_MaterialAspect material;
int Index=-1;
PrimitiveShapeNode(){
   return;
}
TopoDS_Shape Shape() const{
   return TopoDS_Shape();
}
//This sets both the shape and the transform
void SetShape(const TopoDS_Shape& shape){
    
    return;
}


unsigned int nPorts(PortType portType) const override{
    switch(portType){
        case PortType::In:{
            return  2;
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
    return tr("Primitive Shape");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::In:{
            switch(portIndex){
                case 0:
                    return ShapeNodeData(tr("InputShape")).type();
              
               case 1:{
                  return MaterialNodeData(tr("Material")).type();
               }
            }
        }
        case PortType::Out:{
             switch(portIndex){
                case 0:
                 return ShapeNodeData(tr("OutputShape")).type();
               
             }
        }
        
    }
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
  if(output_data){
    return static_pointer_cast<NodeData>(output_data);
  } 

std::shared_ptr<NodeData> mptr;
    return static_pointer_cast<NodeData>(mptr);
}

void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
   if(!data){
    return;
   }
   switch(portIndex){
    case 0:{
        input_data=dynamic_pointer_cast<ShapeNodeData>(data);
        if(input_data.lock()){
            outputShape=input_data.lock()->Data();
            Index=input_data.lock()->index();

        }
        break;
    }
    case 1:{
      inputMaterial=dynamic_pointer_cast<MaterialNodeData>(data);
      if(inputMaterial.lock()){
        material=inputMaterial.lock()->Data();
    
      }
      break;
    }
   }
   if(output_data){
    output_data->SetAspect(material);
    output_data->SetData(outputShape);
    output_data->SetIndex(Index);
   }
   else{
    output_data=make_unique<ShapeNodeData>(tr(""));
     output_data->SetAspect(material);
    output_data->SetData(outputShape);
    output_data->SetIndex(Index);
   }
   emit dataUpdated(0);
   return;
}
QWidget* embeddedWidget() override{
    return nullptr;
}
signals:
void EmitShape(const TopoDS_Shape& shape);

};
