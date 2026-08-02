#pragma once 
#include<NodeDelegateModel>
#include<NodeInitializer.hpp>
#include<IntegerNodeData.hpp>
#include<FloatNodeData.hpp>
#include<BooleanNodeData.hpp>
#include<memory>
#include<ShapeNodeData.hpp>
#include<BRepOffset_MakeOffset.hxx>
#include<BRepOffset_Mode.hxx>
#include<GeomAbs_JoinType.hxx>
#include<InfoUtility.hpp>
#include<Standard_Failure.hxx>
using namespace std;
using namespace QtNodes;
using namespace INFO;
class MakeOffsetShapeNode:public NodeDelegateModel,public NodeInitializer{
 private:
 std::shared_ptr<ShapeNodeData> outputShape;
 std::weak_ptr<ShapeNodeData> shapedata;
 std::weak_ptr<FloatNodeData> offsetdata;
 std::weak_ptr<TemplatedData<BRepOffset_Mode>> offsetmodedata;
 std::weak_ptr<BooleanNodeData> intersectdata;
 std::weak_ptr<BooleanNodeData> selfintersectdata;
 std::weak_ptr<TemplatedData<GeomAbs_JoinType>> joindata;
 std::weak_ptr<BooleanNodeData> isthickendata;
 std::weak_ptr<BooleanNodeData> isremoveintersectedgedata; //remove intersecting edges;
 std::weak_ptr<BooleanNodeData> makesoliddata;
 std::weak_ptr<BooleanNodeData> allowLineardata;
 TopoDS_Shape inputShape=TopoDS_Shape();
 double inputoffset=1.0;
 BRepOffset_Mode inputoffsetmode=BRepOffset_Skin;
 bool inputintersect=false;
 bool inputselfintersect=false;
 GeomAbs_JoinType inputjointype=GeomAbs_Arc;
 bool isthicken=false;
 bool isremoveintersectedge=false;
 bool makesolid=false;
 bool allowlinear=false;
 bool isPortASet=false; //0
 bool isPortBSet=false; //1
 bool isPortCSet=false; //2
 bool isPortDSet=false; //3
 bool isPortESet=false; //4
 bool isPortFSet=false; //5
 bool isPortGSet=false; //6
 bool isPortHSet=false; //7
 bool isPortISet=false; //8
 bool isPortJSet=false; //9
 public:
 MakeOffsetShapeNode(){
    return;
 }
 unsigned int nPorts(PortType portType) const override{
   switch(portType){
   case PortType::In:{
     return 10;
   
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
    return tr("Make Offset Shape");
}
QString name() const override{
    return caption();
}
void SetToFalse() override{
isPortASet=false; //0
 isPortBSet=false; //1
 isPortCSet=false; //2
 isPortDSet=false; //3
 isPortESet=false; //4
 isPortFSet=false; //5
 isPortGSet=false; //6
 isPortHSet=false; //7
 isPortISet=false; //8
 isPortJSet=false; //9
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::In:{
            switch(portIndex){
            case 0:{
                return ShapeNodeData(tr("Input Shape")).type();
            }
            case 1:{
                return FloatNodeData(tr("Offset")).type();
            }
            case 2:{
                return TemplatedData<BRepOffset_Mode>(tr("Offset Mode"),tr("Offset Mode")).type();
            }
            case 3:{
                return BooleanNodeData(tr("Should Intersect")).type();
            }
            case 4:{
                return BooleanNodeData(tr("Self Intersect")).type();
            }
            case 5:{
                 return TemplatedData<GeomAbs_JoinType>(tr("Join Type"),tr("Join Type")).type();
            }
            case 6:{
                return BooleanNodeData(tr("Is Thicken")).type();
            }
            case 7:{
                return BooleanNodeData(tr("Shoud Remove Int Edge")).type();
            }
            case 8:{
                return BooleanNodeData(tr("Should Make Solid")).type();
            }
            case 9:{
                return BooleanNodeData(tr("Allow Linearization")).type();
            }
        }
    }
        case PortType::Out:{
            switch(portIndex){
            case 0:
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
         shapedata=dynamic_pointer_cast<ShapeNodeData>(data);
         if(shapedata.lock()){
            inputShape=shapedata.lock()->Data();
            isPortASet=true;
            break;
         }
        }
        case 1:{
            offsetdata=dynamic_pointer_cast<FloatNodeData>(data);
            if(offsetdata.lock()){
                inputoffset=offsetdata.lock()->Data();
                isPortBSet=true;
                break;
            }
        }
        case 2:{
            offsetmodedata=dynamic_pointer_cast<TemplatedData<BRepOffset_Mode>>(data);
            if(offsetmodedata.lock()){
                inputoffsetmode=offsetmodedata.lock()->Data();
                isPortCSet=true;
                break;
            }
        }
        case 3:{
            intersectdata=dynamic_pointer_cast<BooleanNodeData>(data);
            if(intersectdata.lock()){
                inputintersect=intersectdata.lock()->Data();
                isPortDSet=true;
                break;
            }
        }
         case 4:{
            selfintersectdata=dynamic_pointer_cast<BooleanNodeData>(data);
            if(selfintersectdata.lock()){
                inputselfintersect=selfintersectdata.lock()->Data();
                isPortESet=true;
                break;
            }
        }
        case 5:{
            joindata=dynamic_pointer_cast<TemplatedData<GeomAbs_JoinType>>(data);
            if(joindata.lock()){
                inputjointype=joindata.lock()->Data();
                isPortFSet=true;
                break;
            }
        }
        case 6:{
            isthickendata=dynamic_pointer_cast<BooleanNodeData>(data);
            if(isthickendata.lock()){
               isthicken=isthickendata.lock()->Data();
               isPortGSet=true;
               break;    
            }
        }
        case 7:{
            isremoveintersectedgedata=dynamic_pointer_cast<BooleanNodeData>(data);
            if(isremoveintersectedgedata.lock()){
                isremoveintersectedge=isremoveintersectedgedata.lock()->Data();
                isPortFSet=true;
                break;
            }
        }
        case 8:{
            makesoliddata=dynamic_pointer_cast<BooleanNodeData>(data);
            if(makesoliddata.lock()){
                makesolid=makesoliddata.lock()->Data();
                isPortGSet=true;
                break;
            }
        }
        case 9:{
          allowLineardata=dynamic_pointer_cast<BooleanNodeData>(data);
          if(allowLineardata.lock()){
            allowlinear=allowLineardata.lock()->Data();
            isPortHSet=true;
            break;
          }          
        }

}
  if(outputShape){
    if(isPortASet==false){
     LoadMessage(tr(""),tr("Shape is not set"));
     return;
    }
    BRepOffset_MakeOffset offsetmaker;
    offsetmaker.Initialize(inputShape,inputoffset,1e-6,inputoffsetmode,inputintersect,inputselfintersect,inputjointype,isthicken,isremoveintersectedge);
    if(makesolid){
        offsetmaker.MakeThickSolid();
    }
    offsetmaker.AllowLinearization(allowlinear);
    try{
        offsetmaker.MakeOffsetShape();
    }
    catch(Standard_Failure& efailure){
        LoadMessage(tr(""),tr("Failed to perform Offseting"));
        return;
    }
    if(offsetmaker.IsDone()){
        outputShape->SetData(offsetmaker.Shape());
    }
  }
  else{
    outputShape=std::make_shared<ShapeNodeData>(tr(""));
    if(isPortASet==false){
     LoadMessage(tr(""),tr("Shape is not set"));
     return;
    }
    BRepOffset_MakeOffset offsetmaker;
    offsetmaker.Initialize(inputShape,inputoffset,1e-6,inputoffsetmode,inputintersect,inputselfintersect,inputjointype,isthicken,isremoveintersectedge);
    if(makesolid){
        offsetmaker.MakeThickSolid();
    }
    offsetmaker.AllowLinearization(allowlinear);
    try{
        offsetmaker.MakeOffsetShape();
    }
    catch(Standard_Failure& efailure){
        LoadMessage(tr(""),tr("Failed to perform Offseting"));
        return;
    }
    if(offsetmaker.IsDone()){
        outputShape->SetData(offsetmaker.Shape());
    }
  }
  emit dataUpdated(0);
    return;
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
     if(outputShape){
        return static_pointer_cast<NodeData>(outputShape);
     }
     std::shared_ptr<NodeData> mptr;
     return mptr;
}
QWidget* embeddedWidget() override{
    return nullptr;
}
};