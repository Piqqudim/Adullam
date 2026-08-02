#pragma once
#include<NodeDelegateModel>
#include<gp_Trsf.hxx>
#include<ShapeNodeData.hpp>
#include<DisplayType.hpp>
#include<NodeInitializer.hpp>
#include<BRepBuilderAPI_Transform.hxx>
#include<AxisNodeData.hpp>
#include<PointNodeData.hpp>
#include<memory>
using namespace std;
using namespace QtNodes;
class AboutPlaneMirrorNode:public NodeDelegateModel,public NodeInitializer{
 private:
 std::shared_ptr<ShapeNodeData> outputShape;
 std::weak_ptr<ShapeNodeData> shapedata;
 std::weak_ptr<AxisNodeData> axisdata;
 std::weak_ptr<PointNodeData> pointdata;
 TopoDS_Shape inputShape;
 gp_Pnt inputPoint;
 gp_Dir inputDir;

 bool isPortASet=false;
 bool isPortBSet=false;
 bool isPortCSet=false;
 public:
 AboutPlaneMirrorNode()
{
   return;
}
unsigned int nPorts(PortType portType) const override{
   switch(portType){
    case PortType::In:{
        return 3;
    }
    case PortType::Out:{
      return 1;
    }
   }
   return 0;
}
QString caption() const override{
    return tr("About Plane Mirror Node");
}
QString name() const override{
    return caption();
}
void SetToFalse() override{
    isPortASet=false;
    isPortBSet=false;
    isPortCSet=false;
    return;
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::In:{
            switch(portIndex){
                case 0:
                   return ShapeNodeData(tr("Input Shape")).type();
                case 1:{
                   return AxisNodeData(tr("Input Axis")).type();
                }
                case 2:{
                    return PointNodeData(tr("Input Position")).type();
                }
            }
        }
        case PortType::Out:{
            switch(portIndex){
            case 0:{
               return ShapeNodeData(tr("Output Shape")).type();
            }
        }
        }
       
    }
     return {tr(""),tr("")};
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(outputShape){
      return static_pointer_cast<NodeData>(outputShape);
    }
    std::shared_ptr<NodeData> mptr;
    return mptr;
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
    if(!data){
        return;
    }
    switch(portIndex){
        case 0:{
            shapedata=dynamic_pointer_cast<ShapeNodeData>(data);
            if(shapedata.lock()){
              inputShape=shapedata.lock()->Data();
              isPortASet=true;
              break;
            }
        }
        case 1:{
            axisdata=dynamic_pointer_cast<AxisNodeData>(data);
            if(axisdata.lock()){
                inputDir=axisdata.lock()->Data().Direction();
                isPortBSet=true;
                break;
            }
        }
        case 2:{
            pointdata=dynamic_pointer_cast<PointNodeData>(data);
            if(pointdata.lock()){
                inputPoint=pointdata.lock()->ToPnt();
                isPortCSet=true;
                break;
            }
        }
    }
    if(outputShape){
        if(isPortASet==false){
            //No input Shape is assigned
            return;
        }
        if(isPortBSet==false){
            return;
        }
        if(isPortCSet==false){
            return;
        }
        gp_Trsf mirrorTrans;
        mirrorTrans.SetMirror(gp_Ax2(inputPoint,inputDir));
        BRepBuilderAPI_Transform trans(inputShape,mirrorTrans,true);
        if(!trans.IsDone()){
            return;
        }
        if(outputShape->displayType()!=DP_MIRROR){
            outputShape->SetDisplayType(DP_MIRROR);
        }
        outputShape->SetData(trans.Shape());
    }
    else{
        outputShape=std::make_shared<ShapeNodeData>(tr(""));
         if(isPortASet==false){
            //No input Shape is assigned
            return;
        }
        if(isPortBSet==false){
            return;
        }
        if(isPortCSet==false){
            return;
        }
        gp_Trsf mirrorTrans;
        mirrorTrans.SetMirror(gp_Ax2(inputPoint,inputDir));
        BRepBuilderAPI_Transform trans(inputShape,mirrorTrans,true);
        if(!trans.IsDone()){
            return;
        }
        if(outputShape->displayType()!=DP_MIRROR){
            outputShape->SetDisplayType(DP_MIRROR);
        }
        outputShape->SetData(trans.Shape());
    }
    emit dataUpdated(0);
    return;
}
QWidget* embeddedWidget() override{ 
   return nullptr;
 }
};


class AboutPointMirrorNode:public NodeDelegateModel,public NodeInitializer{
    private:
 std::shared_ptr<ShapeNodeData> outputShape;
 std::weak_ptr<ShapeNodeData> shapedata;
 
 std::weak_ptr<PointNodeData> pointdata;
 TopoDS_Shape inputShape;
 gp_Pnt inputPoint;
 

 bool isPortASet=false;
 bool isPortBSet=false;

 public:
 AboutPointMirrorNode()
{
   return;
}
unsigned int nPorts(PortType portType) const override{
   switch(portType){
    case PortType::In:{
        return 2;
    }
    case PortType::Out:{
      return 1;
    }
   }
   return 0;
}
QString caption() const override{
    return tr("About Point Mirror Node");
}
QString name() const override{
    return caption();
}
void SetToFalse() override{
    isPortASet=false;
    isPortBSet=false;
    return;
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::In:{
            switch(portIndex){
                case 0:
                   return ShapeNodeData(tr("Input Shape")).type();
                case 1:{
                    return PointNodeData(tr("Input Position")).type();
                }
            }
        }
        case PortType::Out:{
            switch(portIndex){
            case 0:{
               return ShapeNodeData(tr("Output Shape")).type();
            }
        }
        }
       
    }
     return {tr(""),tr("")};
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(outputShape){
      return static_pointer_cast<NodeData>(outputShape);
    }
    std::shared_ptr<NodeData> mptr;
    return mptr;
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
    if(!data){
        return;
    }
    switch(portIndex){
        case 0:{
            shapedata=dynamic_pointer_cast<ShapeNodeData>(data);
            if(shapedata.lock()){
              inputShape=shapedata.lock()->Data();
              isPortASet=true;
              break;
            }
        }
        
        case 1:{
            pointdata=dynamic_pointer_cast<PointNodeData>(data);
            if(pointdata.lock()){
                inputPoint=pointdata.lock()->ToPnt();
                isPortBSet=true;
                break;
            }
        }
    }
    if(outputShape){
        if(isPortASet==false){
            //No input Shape is assigned
            return;
        }
        if(isPortBSet==false){
            return;
        }
        gp_Trsf mirrorTrans;
        mirrorTrans.SetMirror(inputPoint);
        BRepBuilderAPI_Transform trans(inputShape,mirrorTrans,true);
        if(!trans.IsDone()){
            return;
        }
        if(outputShape->displayType()!=DP_MIRROR){
            outputShape->SetDisplayType(DP_MIRROR);
        }
        outputShape->SetData(trans.Shape());
    }
    else{
        outputShape=std::make_shared<ShapeNodeData>(tr(""));
         if(isPortASet==false){
            //No input Shape is assigned
            return;
        }
        if(isPortBSet==false){
            return;
        }
        
        gp_Trsf mirrorTrans;
        mirrorTrans.SetMirror(inputPoint);
        BRepBuilderAPI_Transform trans(inputShape,mirrorTrans,true);
        if(!trans.IsDone()){
            return;
        }
        if(outputShape->displayType()!=DP_MIRROR){
            outputShape->SetDisplayType(DP_MIRROR);
        }
        outputShape->SetData(trans.Shape());
    }
    emit dataUpdated(0);
    return;
}
QWidget* embeddedWidget() override{ 
   return nullptr;
 }
};
class AboutAxisMirrorNode:public NodeDelegateModel,public NodeInitializer{
private:
 std::shared_ptr<ShapeNodeData> outputShape;
 std::weak_ptr<ShapeNodeData> shapedata;
 std::weak_ptr<AxisNodeData> axisdata;
 std::weak_ptr<PointNodeData> pointdata;
 TopoDS_Shape inputShape;
 gp_Pnt inputPoint;
 gp_Dir inputDir;

 bool isPortASet=false;
 bool isPortBSet=false;
 bool isPortCSet=false;
 public:
 AboutAxisMirrorNode()
{
   return;
}
unsigned int nPorts(PortType portType) const override{
   switch(portType){
    case PortType::In:{
        return 3;
    }
    case PortType::Out:{
      return 1;
    }
   }
   return 0;
}
QString caption() const override{
    return tr("About Axis Mirror Node");
}
QString name() const override{
    return caption();
}
void SetToFalse() override{
    isPortASet=false;
    isPortBSet=false;
    isPortCSet=false;
    return;
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::In:{
            switch(portIndex){
                case 0:
                   return ShapeNodeData(tr("Input Shape")).type();
                case 1:{
                   return AxisNodeData(tr("Input Axis")).type();
                }
                case 2:{
                    return PointNodeData(tr("Input Position")).type();
                }
            }
        }
        case PortType::Out:{
            switch(portIndex){
            case 0:{
               return ShapeNodeData(tr("Output Shape")).type();
            }
        }
        }
       
    }
     return {tr(""),tr("")};
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(outputShape){
      return static_pointer_cast<NodeData>(outputShape);
    }
    std::shared_ptr<NodeData> mptr;
    return mptr;
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
    if(!data){
        return;
    }
    switch(portIndex){
        case 0:{
            shapedata=dynamic_pointer_cast<ShapeNodeData>(data);
            if(shapedata.lock()){
              inputShape=shapedata.lock()->Data();
              isPortASet=true;
              break;
            }
        }
        case 1:{
            axisdata=dynamic_pointer_cast<AxisNodeData>(data);
            if(axisdata.lock()){
                inputDir=axisdata.lock()->Data().Direction();
                isPortBSet=true;
                break;
            }
        }
        case 2:{
            pointdata=dynamic_pointer_cast<PointNodeData>(data);
            if(pointdata.lock()){
                inputPoint=pointdata.lock()->ToPnt();
                isPortCSet=true;
                break;
            }
        }
    }
    if(outputShape){
        if(isPortASet==false){
            //No input Shape is assigned
            return;
        }
        if(isPortBSet==false){
            return;
        }
        if(isPortCSet==false){
            return;
        }
        gp_Trsf mirrorTrans;
        mirrorTrans.SetMirror(gp_Ax2(inputPoint,inputDir).Axis());
        BRepBuilderAPI_Transform trans(inputShape,mirrorTrans,true);
        if(!trans.IsDone()){
            return;
        }
        if(outputShape->displayType()!=DP_MIRROR){
            outputShape->SetDisplayType(DP_MIRROR);
        }
        outputShape->SetData(trans.Shape());
    }
    else{
        outputShape=std::make_shared<ShapeNodeData>(tr(""));
         if(isPortASet==false){
            //No input Shape is assigned
            return;
        }
        if(isPortBSet==false){
            return;
        }
        if(isPortCSet==false){
            return;
        }
        gp_Trsf mirrorTrans;
        mirrorTrans.SetMirror(gp_Ax2(inputPoint,inputDir).Axis());
        BRepBuilderAPI_Transform trans(inputShape,mirrorTrans,true);
        if(!trans.IsDone()){
            return;
        }
        if(outputShape->displayType()!=DP_MIRROR){
            outputShape->SetDisplayType(DP_MIRROR);
        }
        outputShape->SetData(trans.Shape());
    }
    emit dataUpdated(0);
    return;
}
QWidget* embeddedWidget() override{ 
   return nullptr;
 }
};