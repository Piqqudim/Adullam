#pragma once
#include<NodeDelegateModel>
#include<NodeInitializer.hpp>
#include<BRepPrimAPI_MakePrism.hxx>
#include<AxisNodeData.hpp>
#include<FloatNodeData.hpp>
#include<ShapeUtil.hpp>
#include<ShapeNodeData.hpp>
#include<memory>
//inputs: a 
//outputs:
using namespace std;
using namespace QtNodes;
using namespace Shape_Utility;
class ExtrusionNode:public NodeDelegateModel,public NodeInitializer{
    private:
    weak_ptr<ShapeNodeData> face_input_data;
    weak_ptr<AxisNodeData> dir_input_data;
    weak_ptr<FloatNodeData> float_input_data;
    std::shared_ptr<ShapeNodeData> outputShape;
    TopoDS_Shape  face;
    gp_Dir dir;
    float value=4.0f; //by default,the value is 4.0;
    bool isPortASet=false;
    bool isPortBSet=false;
    bool isPortCSet=false;
public:
ExtrusionNode(){
    dir.SetX(1.0);
    dir.SetY(0.0);
    dir.SetZ(0.0);
    return;
}
void SetToFalse() override{
    isPortASet=false;
    isPortBSet=false;
    isPortCSet=false;
    return;
} 
unsigned int nPorts(PortType portType) const override{
    switch(portType){
        case PortType::In:{
            return  3;
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
    return tr("Extrusion Node");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::In:{
            switch(portIndex){
                case 0:
                   return ShapeNodeData(tr("Input Shape")).type(); 
                case 1:{
                    return AxisNodeData(tr("Direction")).type();
                }
                case 2:{
                    return FloatNodeData(tr("Input Value")).type();
                }
            }
        }
        case PortType::Out:{
            if(portIndex==0){
                return ShapeNodeData(tr("Output Shape")).type();
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
            face_input_data=dynamic_pointer_cast<ShapeNodeData>(data);
            if(face_input_data.lock()){
                face=face_input_data.lock()->Data();
                isPortASet=true;
            }
            break;
        }
        case 1:{
            dir_input_data=dynamic_pointer_cast<AxisNodeData>(data);
            if(dir_input_data.lock()){
                
                dir=dir_input_data.lock()->Data().Direction();
                isPortBSet=true;
            }
            break;
        }
        case 2:{
            float_input_data=dynamic_pointer_cast<FloatNodeData>(data);
            if(float_input_data.lock()){
                isPortCSet=true;
                value=float_input_data.lock()->Data();
            }
            break;
        }
    }
        if(outputShape.get()){
         if(isPortASet==false){
            return;
         }
         if(isPortBSet==false){
            return;
         }
         if(isPortCSet==false){
            return;
         }
         gp_Vec vec(dir);
         vec.Multiply(value);
         outputShape->SetData(Extrude(face,vec));
        }
        else{
            outputShape=make_shared<ShapeNodeData>(tr(""));
         if(isPortASet==false){
            return;
         }
         if(isPortBSet==false){
            return;
         }
         if(isPortCSet==false){
            return;
         }
            gp_Vec vec(dir);
            vec.Multiply(value);
            outputShape->SetData(Extrude(face,vec));
        }
    emit dataUpdated(0);
    return;
}

std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(outputShape.get()){
        return std::static_pointer_cast<NodeData>(outputShape);
    }
   outputShape=make_shared<ShapeNodeData>(tr(""));
   gp_Vec vec(dir);
   vec.Multiply(value);
   outputShape->SetData(Extrude(face,vec));
    return std::static_pointer_cast<NodeData>(outputShape);
    
} 
QWidget* embeddedWidget() override{return nullptr;}



};