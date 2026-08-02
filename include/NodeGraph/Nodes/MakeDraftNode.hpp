#pragma once
#include<BRepOffsetAPI_MakeDraft.hxx>
#include<IntegerNodeData.hpp>
#include<NodeDelegateModel>
#include<ShapeNodeData.hpp>
#include<AxisNodeData.hpp>
#include<FloatNodeData.hpp>
#include<Standard_Failure.hxx>
#include<BooleanNodeData.hpp>
#include<InfoUtility.hpp>
#include<NodeInitializer.hpp>
#include<memory>
using namespace std;
using namespace QtNodes;
using namespace INFO;
class MakeDraftNode:public NodeDelegateModel,public NodeInitializer{
private:
std::weak_ptr<ShapeNodeData> shapeInputData;
std::weak_ptr<AxisNodeData> axisInputData;
std::weak_ptr<FloatNodeData> floatInputData;
std::weak_ptr<FloatNodeData> angleInputData;
std::weak_ptr<TemplatedData<BRepBuilderAPI_TransitionMode>> transInputData;
std::weak_ptr<BooleanNodeData> isInternalInputData;
std::shared_ptr<ShapeNodeData> outputData;
TopoDS_Shape outputShape=TopoDS_Shape();
TopoDS_Shape inputShape=TopoDS_Shape();
gp_Ax2 outputAxis=gp_Ax2();
double Angle=0.0f; //angle is zero
double maxLength=0.0;
BRepBuilderAPI_TransitionMode trmode;
bool isInternal;
const double pie=3.141592653;
bool isPortASet=false;
bool isPortBSet=false;
bool isPortCSet=false;
bool isPortDSet=false;
bool isPortESet=false;
bool isPortFSet=false;
public:
MakeDraftNode(){
    return;
}
unsigned int nPorts(PortType portType) const override{
    switch(portType){
        case PortType::In:{
            return 6;
        }
        case PortType::Out:{
            return 1;
        }
    }
    return 0;
}
QString caption() const override{
    return tr("Make Draft Node");
}
void SetToFalse() override{
  isPortASet=false;
  isPortBSet=false;
  isPortCSet=false;
  isPortDSet=false;
  isPortESet=false;
  isPortFSet=false;
    return;
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
                case 1:
                   return AxisNodeData(tr("Input Axis")).type();
                case 2:
                   return FloatNodeData(tr("Max Length")).type();
                case 3:
                   return FloatNodeData(tr("Angle")).type();                        
                case 4:
                  return TemplatedData<BRepBuilderAPI_TransitionMode>(tr("Transtion Mode"),tr("Transition Mode")).type();
                case 5:
                  return BooleanNodeData(tr("isInternal")).type();
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
            shapeInputData=dynamic_pointer_cast<ShapeNodeData>(data);
            if(shapeInputData.lock()){
                inputShape=shapeInputData.lock()->Data();
                isPortASet=true;
                break;
            }
        }
        case 1:{
            axisInputData=dynamic_pointer_cast<AxisNodeData>(data);
            if(axisInputData.lock()){
                outputAxis=axisInputData.lock()->Data();
                isPortBSet=true;
                break;
            }
        }
        case 2:{
            floatInputData=dynamic_pointer_cast<FloatNodeData>(data);
            if(floatInputData.lock()){
                maxLength=(double)floatInputData.lock()->Data();
                isPortCSet=true;
                break;
            }
        }
        case 3:{
            angleInputData=dynamic_pointer_cast<FloatNodeData>(data);
            if(angleInputData.lock()){
                Angle=(double)angleInputData.lock()->Data();
                isPortDSet=true;
                break;
            }
        }
        case 4:{
            transInputData=dynamic_pointer_cast<TemplatedData<BRepBuilderAPI_TransitionMode>>(data);
          if(transInputData.lock()){
            trmode=transInputData.lock()->Data();
            isPortESet=true;
            break;
          }
        }
    case 5:{
        isInternalInputData=dynamic_pointer_cast<BooleanNodeData>(data);
        if(isInternalInputData.lock()){
            isInternal=isInternalInputData.lock()->Data();
            isPortFSet=true;
            break;
        }
    }
    }
  if(outputData){
    if(isPortASet==false){
      return;
    }
    if(isPortBSet==false){
        return;
    }
    if(isPortCSet==false){
        return;
    }
    if(isPortDSet==false){
        return;
    }
    if(inputShape.ShapeType()!=4 || inputShape.ShapeType()!=3 ||inputShape.ShapeType()!=5){
        LoadMessage(tr(""),tr("The Input Shape is either not a face or wire or shell"));
        return;
    }
    if(Angle>360.0){
        Angle=360.0;
    }
    double ang;
    ang=Angle*(pie/180.000000);
    BRepOffsetAPI_MakeDraft draftmaker(inputShape,outputAxis.Direction(),Angle);
    if(isPortESet){
        draftmaker.SetOptions(trmode);
    }
    if(isPortFSet){
        draftmaker.SetDraft(isInternal);
    }
    try{
    draftmaker.Perform(maxLength);
    }
    catch(const Standard_Failure& failure){
        LoadMessage(tr(""),tr("Draft Failed"));
        return;
    }
    if(draftmaker.IsDone()){
        outputShape=draftmaker.Shape();
    }
    else{
        LoadMessage(tr("Make Draft Node Error"),tr("Failed to construct shape"));
        return;
    }
    outputData->SetData(outputShape);
  }
  else{
    outputData=std::make_shared<ShapeNodeData>(tr(""));
     if(isPortASet==false){
      return;
    }
    if(isPortBSet==false){
        return;
    }
    if(isPortCSet==false){
        return;
    }
    if(isPortDSet==false){
        return;
    }
    if(inputShape.ShapeType()!=4 || inputShape.ShapeType()!=3 ||inputShape.ShapeType()!=5){
        LoadMessage(tr(""),tr("The Input Shape is either not a face or wire or shell"));
        return;
    }
    if(Angle>360.0){
        Angle=360.0;
    }
    Angle=Angle*(pie/180.000000);
    BRepOffsetAPI_MakeDraft draftmaker(inputShape,outputAxis.Direction(),Angle);
    if(isPortESet){
        draftmaker.SetOptions(trmode);
    }
    if(isPortFSet){
        draftmaker.SetDraft(isInternal);
    }
    try{
    draftmaker.Perform(maxLength);
    }
    catch(const Standard_Failure& failure){
        LoadMessage(tr(""),tr("Draft Failed"));
        return;
    }
    if(draftmaker.IsDone()){
        outputShape=draftmaker.Shape();
    }
    else{
        LoadMessage(tr("Make Draft Node Error"),tr("Failed to construct shape"));
        return;
    }
    outputData->SetData(outputShape);
  }
  emit dataUpdated(0);
  return;
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