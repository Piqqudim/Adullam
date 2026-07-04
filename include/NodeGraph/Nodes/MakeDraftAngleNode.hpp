#pragma once 
#include<ShapeNodeData.hpp>
#include<FaceNodeData.hpp>
#include<NodeDelegateModel>
#include<NodeInitializer.hpp>
#include<InfoUtility.hpp>
#include<AxisNodeData.hpp>
#include<FloatNodeData.hpp>
#include<SurfaceUtility.hpp>
#include<BooleanNodeData.hpp>
#include<BRepOffsetAPI_DraftAngle.hxx>
#include<Draft_ErrorStatus.hxx>
#include<memory>
using namespace std;
using namespace QtNodes;
using namespace INFO;
namespace DraftError{
    inline QString DraftErrorToString(const Draft_ErrorStatus& status){
        switch(status){
            case Draft_FaceRecomputation:{
                return QString("Face Recomputation Error");
                break;
            }
            case Draft_EdgeRecomputation:{
                return QString("Edge Recomputation Error");
                break;
            }
            case Draft_VertexRecomputation:{
                return QString("Vertex Recomputation Error");
            }
            default:

            break;
        }
        return QString("No Error ");
    }
}
class MakeDraftAngleNode:public NodeDelegateModel,public NodeInitializer{
private:
std::shared_ptr<ShapeNodeData> outputData;
std::weak_ptr<ShapeNodeData> inputData;
std::weak_ptr<FaceNodeData> faceData;
std::weak_ptr<FloatNodeData> angleData;
std::weak_ptr<AxisNodeData> axisData;
std::weak_ptr<BooleanNodeData> boolData;
TopoDS_Shape outputShape;
TopoDS_Shape inputShape;
TopoDS_Face inputFace;
double Angle=0.0f;
gp_Dir dir;
bool isFlag=true;
bool isPortASet=false;
bool isPortBSet=false;
bool isPortCSet=false;
bool isPortDSet=false;
bool isPortESet=false;
const double pie=3.14159;
public:
MakeDraftAngleNode(){
    return;
}
unsigned int nPorts(PortType portType) const override{
    switch(portType){
        case PortType::In:{
            return 5;
        }
        case PortType::Out:{
            return 1;
        }
    }
    return 0;
}
QString caption() const override{
    return tr("Make Draft Angle Node");
}
QString name() const override{
    return caption();
}
void SetToFalse() override{
  isPortASet=false;
  isPortBSet=false;
  isPortCSet=false;
  isPortDSet=false;
  isPortESet=false;
    return;
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::In:{
            switch(portIndex){
                case 0:
                   return ShapeNodeData(tr("Input Shape")).type();
                case 1:
                   return FaceNodeData(tr("Input Face")).type();
                case 2:
                 return AxisNodeData(tr("Input Axis")).type();
                case 3:
                   return FloatNodeData(tr("Angle")).type();                        
                
                case 4:
                  return BooleanNodeData(tr("isFlag")).type();
            }
        }
     case PortType::Out:{
          if(portIndex==0){
            return ShapeNodeData(tr("Output Shape")).type();
          }
     }
    }
    return {tr(""),tr("")};
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
    if(!data){
        return;
    }
    switch(portIndex){
        case 0:{
          inputData=dynamic_pointer_cast<ShapeNodeData>(data);
          if(inputData.lock()){
            inputShape=inputData.lock()->Data();
            isPortASet=true;
            break;
          }   
        }
        case 1:{
         faceData=dynamic_pointer_cast<FaceNodeData>(data);
         if(faceData.lock()){
           inputFace=faceData.lock()->GetFaceData();
           isPortBSet=true;
           break;
         }
        }
        case 2:{
            angleData=dynamic_pointer_cast<FloatNodeData>(data);
            if(angleData.lock()){
                Angle=(double)angleData.lock()->Data();
                isPortCSet=true;
                break;
            }
        }
        case 3:{
            axisData=dynamic_pointer_cast<AxisNodeData>(data);
            if(axisData.lock()){
                dir=axisData.lock()->Data().Direction();
                isPortDSet=true;
                break;
            }
        }
        case 4:{
            boolData=dynamic_pointer_cast<BooleanNodeData>(data);
            if(boolData.lock()){
                isFlag=boolData.lock()->Data();
                isPortESet=true;
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
    BRepOffsetAPI_DraftAngle draftmaker;
    draftmaker.Init(inputShape);
    double ang=(Angle*pie)/180.00;
     gp_Pnt centre=SURFACE::GetSurfaceCentre(inputFace);
    gp_Pln plane(centre,dir);
    draftmaker.Add(inputFace,dir,ang,plane,isFlag);
    draftmaker.Build();
    if(draftmaker.IsDone()){
        outputShape=draftmaker.Shape();
    }
    else{
       LoadMessage(tr("Draft Error"),DraftError::DraftErrorToString(draftmaker.Status())); 
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
    BRepOffsetAPI_DraftAngle draftmaker;
    draftmaker.Init(inputShape);
    double ang=(Angle*pie)/180.00;
     gp_Pnt centre=SURFACE::GetSurfaceCentre(inputFace);
    gp_Pln plane(centre,dir);
    draftmaker.Add(inputFace,dir,ang,plane,isFlag);
    draftmaker.Build();
    if(draftmaker.IsDone()){
        outputShape=draftmaker.Shape();
    }
    else{
        LoadMessage(tr("Draft Error"),DraftError::DraftErrorToString(draftmaker.Status()));
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