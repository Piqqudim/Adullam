/*#pragma once
#include<BRepOffsetAPI_MakeOffset.hxx>
#include<FaceNodeData.hpp>
#include<NodeDelegateModel>
#include<NodeInitializer.hpp>
#include<InfoUtility.hpp>
#include<FloatNodeData.hpp>
#include<IntegerNodeData.hpp>
#include<ShapeNodeData.hpp>
#include<WireNodeData.hpp>
#include<memory>
#include<WireNodeData.hpp>
using namespace std;
using namespace QtNodes;
using namespace INFO;
class MakeOffsetFace:public NodeDelegateModel,public NodeInitializer{
private:
std::weak_ptr<FaceNodeData> inputFaceData;
std::weak_ptr<TemplatedData<GeomAbs_JoinType>> joinData;
std::weak_ptr<BooleanNodeData> setApproxData;
std::weak_ptr<FloatNodeData> offsetData;
std::shared_ptr<ShapeNodeData> outputData;
TopoDS_Shape outputShape;
TopoDS_Face inputFace;
GeomAbs_JoinType jtype=GeomAbs_Arc;
bool ToApprox=false;
double offsetValue=2.0; //by default,we have an offset value of 2.0
bool isPortASet=false;
public:
MakeOffsetFace(){
    return;
}
unsigned int nPorts(PortType portType) const override{
    switch(portType){
        case PortType::In:{
            return 4;
        }
        case PortType::Out:{
            return 1;
        }
    }
    return 0;
}
QString caption() const override{
    return tr("Make Face Offset Node");
}
void SetToFalse() override{
    isPortASet=false;
    return;
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::In:{
            switch(portIndex){
                case 0:
                   return FaceNodeData(tr("Input Face")).type();
                case 1:
                   return TemplatedData<GeomAbs_JoinType>(tr("Join Type"),tr("Join Type")).type();
                case 2:
                 return BooleanNodeData(tr("set Approx")).type();
                case 3:
                   return FloatNodeData(tr("Offset")).type();                        
                
               
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
            inputFaceData=dynamic_pointer_cast<FaceNodeData>(data);
            if(inputFaceData.lock()){
                inputFace=inputFaceData.lock()->GetFaceData();
                isPortASet=true;
                break;
            }
        }
        case 1:{
            joinData=dynamic_pointer_cast<TemplatedData<GeomAbs_JoinType>>(data);
            if(joinData.lock()){
                jtype=joinData.lock()->Data();
                break;
            }
        }
        case 2:{
        setApproxData=dynamic_pointer_cast<BooleanNodeData>(data);
        if(setApproxData.lock()){
            ToApprox=setApproxData.lock()->Data();
            break;
        }
    }
    case 3:{
        offsetData=dynamic_pointer_cast<FloatNodeData>(data);
        if(offsetData.lock()){
            offsetValue=(double)offsetData.lock()->Data();
            break;
        }
    }
  if(outputData){
    if(isPortASet==false){
        return;
    }
    if(inputFace.IsSame(TopoDS_Face())){
        return;
    }
    BRepOffsetAPI_MakeOffset offsetmaker(inputFace,jtype);
    offsetmaker.SetApprox(ToApprox);
    try{
    offsetmaker.Perform(offsetValue);
    }
    catch(const StdFail_NotDone& notdone){
        LoadMessage(tr("Make Offset Face Error"),tr("Failed to compute offset"));
        return;
    }
    if(offsetmaker.IsDone()){
        outputShape=offsetmaker.Shape();
    }
    else{
        return;
    }
    outputData->SetData(outputShape);
  }
  else{
    outputData=std::make_shared<ShapeNodeData>(tr(""));
     if(isPortASet==false){
        return;
    }
    if(inputFace.IsSame(TopoDS_Face())){
        return;
    }
    BRepOffsetAPI_MakeOffset offsetmaker(inputFace,jtype);
    offsetmaker.SetApprox(ToApprox);
    try{
    offsetmaker.Perform(offsetValue);
    }
    catch(const StdFail_NotDone& notdone){
        LoadMessage(tr("Make Offset Face Error"),tr("Failed to compute offset"));
        return;
    }
    if(offsetmaker.IsDone()){
        outputShape=offsetmaker.Shape();
    }
    else{
        return;
    }
    outputData->SetData(outputShape);
  }
  emit dataUpdated(0);
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(outputData){
        return std::static_pointer_cast<NodeData>(outputData);
    }
    std::shared_ptr<NodeData> mptr;
    return mptr;
}
QWidget* embeddedWidget() override{
    return nullptr;
}
};


class MakeOffsetWire:public NodeDelegateModel,public NodeInitializer{
private:
td::weak_ptr<WireNodeData> inputWireData;
std::weak_ptr<TemplatedData<GeomAbs_JoinType>> joinData;
std::weak_ptr<BooleanNodeData> setApproxData;
std::weak_ptr<FloatNodeData> offsetData;
std::shared_ptr<ShapeNodeData> outputData;
TopoDS_Shape outputShape;
TopoDS_Wire inputWire;
GeomAbs_JoinType jtype=GeomAbs_Arc;
bool ToApprox=false;
double offsetValue=2.0; //by default,we have an offset value of 2.0
bool isPortASet=false;



public:
MakeOffsetWire(){
    return;
}
unsigned int nPorts(PortType portType) const override{
    switch(portType){
        case PortType::In:{
            return 4;
        }
        case PortType::Out:{
            return 1;
        }
    }
    return 0;
}
QString caption() const override{
    return tr("Make Wire Offset Node");
}
void SetToFalse() override{
    isPortASet=false;
    return;
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::In:{
            switch(portIndex){
                case 0:
                   return WireNodeData(tr("Input Wire")).type();
                case 1:
                   return TemplatedData<GeomAbs_JoinType>(tr("Join Type"),tr("Join Type")).type();
                case 2:
                 return BooleanNodeData(tr("set Approx")).type();
                case 3:
                   return FloatNodeData(tr("Offset")).type();                        
                
               
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
            inputWireData=dynamic_pointer_cast<WireNodeData>(data);
            if(inputWireData.lock()){
                inputWire=inputWireData.lock()->Data();
                isPortASet=true;
                break;
            }
        }
        case 1:{
            joinData=dynamic_pointer_cast<TemplatedData<GeomAbs_JoinType>>(data);
            if(joinData.lock()){
                jtype=joinData.lock()->Data();
                break;
            }
        }
        case 2:{
        setApproxData=dynamic_pointer_cast<BooleanNodeData>(data);
        if(setApproxData.lock()){
            ToApprox=setApproxData.lock()->Data();
            break;
        }
    }
    case 3:{
        offsetData=dynamic_pointer_cast<FloatNodeData>(data);
        if(offsetData.lock()){
            offsetValue=(double)offsetData.lock()->Data();
            break;
        }
    }
  if(outputData){
    if(isPortASet==false){
        return;
    }
    if(inputWire.IsSame(TopoDS_Wire())){
        return;
    }
    BRepOffsetAPI_MakeOffset offsetmaker(inputWire,jtype);
    offsetmaker.SetApprox(ToApprox);
    try{
    offsetmaker.Perform(offsetValue);
    }
    catch(const StdFail_NotDone& notdone){
        LoadMessage(tr("Make Offset Wire Error"),tr("Failed to compute offset"));
        return;
    }
    if(offsetmaker.IsDone()){
        outputShape=offsetmaker.Shape();
    }
    else{
        return;
    }
    outputData->SetData(outputShape);
  }
  else{
    outputData=std::make_shared<ShapeNodeData>(tr(""));
     if(isPortASet==false){
        return;
    }
    if(inputWire.IsSame(TopoDS_Wire())){
        return;
    }
    BRepOffsetAPI_MakeOffset offsetmaker(inputWire,jtype);
    offsetmaker.SetApprox(ToApprox);
    try{
    offsetmaker.Perform(offsetValue);
    }
    catch(const StdFail_NotDone& notdone){
        LoadMessage(tr("Make Offset Wire Error"),tr("Failed to compute offset"));
        return;
    }
    if(offsetmaker.IsDone()){
        outputShape=offsetmaker.Shape();
    }
    else{
        return;
    }
    outputData->SetData(outputShape);
  }
  emit dataUpdated(0);
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(outputData){
        return std::static_pointer_cast<NodeData>(outputData);
    }
    std::shared_ptr<NodeData> mptr;
    return mptr;
}
QWidget* embeddedWidget() override{
    return nullptr;
}
};






*/




