#pragma once 
#include<BRepOffsetAPI_ThruSections.hxx>
#include<ShapeNodeData.hpp>
#include<IntegerNodeData.hpp>
#include<PointNodeData.hpp>
#include<BRepBuilderAPI_MakeVertex.hxx>
#include<BooleanNodeData.hpp>
#include<FloatNodeData.hpp>
#include<Standard_Failure.hxx>
#include<memory>
#include<WireNodeData.hpp>
#include<InfoUtility.hpp>
#include<VectorDataNodeData.hpp>
using namespace INFO;
using namespace std;
using namespace QtNodes;
namespace LoftError{
 inline QString LoftEnumToString(const BRepFill_ThruSectionErrorStatus status){
    switch(status){
    case BRepFill_ThruSectionErrorStatus_NotDone:{
        return QString("Loft Algorithm Failed to be done");
    }
    case BRepFill_ThruSectionErrorStatus_NotSameTopology:{
       return QString("All Profiles are not of the same topology(they should be all closed or all opened)"); 
    }
    case BRepFill_ThruSectionErrorStatus_ProfilesInconsistent:{
       return QString("Profiles are inconsistent");
    }
    case BRepFill_ThruSectionErrorStatus_WrongUsage:{
       return QString("Wrong Usage");
    }
    case BRepFill_ThruSectionErrorStatus_Null3DCurve:{
      return QString("Null 3D curve in edge");
    }
    case BRepFill_ThruSectionErrorStatus_Failed:{
      return QString("Thrusection algorithm has failed");

    }
    default:
    break;

    }
    
    
    return QString("");
 }

}
class LoftNode:public NodeDelegateModel,public NodeInitializer{
private:
std::weak_ptr<VectorDataNode<WireNodeData>> inputWiresData;
std::weak_ptr<BooleanNodeData> isSolidData;
std::weak_ptr<BooleanNodeData> isRuledData;
std::weak_ptr<BooleanNodeData> compatData;
std::weak_ptr<BooleanNodeData> smoothData;
std::weak_ptr<BooleanNodeData> mutableData;
std::weak_ptr<TemplatedData<Approx_ParametrizationType>> parData;
std::weak_ptr<TemplatedData<GeomAbs_Shape>> continuityData;
std::weak_ptr<IntegerNodeData> integerData;
std::weak_ptr<PointNodeData> pointData;
std::shared_ptr<ShapeNodeData> outputData;
vector<WireNodeData> inputWires;
bool isSolid=false;
bool isRuled=false;
bool isCompat=true;
bool useSmooth=false;
bool isMutable=true;
Approx_ParametrizationType parType;
GeomAbs_Shape continuity;
int maxDegree=-1;
gp_Pnt pnt;
bool isPort0Set=false;
bool isPort6Set=false;
bool isPort7Set=false;
bool isPort8Set=false;
bool isPort9Set=false;
TopoDS_Shape outputShape;
public:
LoftNode(){

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
  return tr("Loft Node");
}
QString name() const override{
  return caption();

}
void SetToFalse() override{
     isPort0Set=false;
     isPort6Set=false;
     isPort7Set=false;
     isPort8Set=false;
     isPort9Set=false; 
 return;
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
   switch(portType){
     case PortType::In:{
       switch(portIndex){
       case 0:{
          return VectorDataNode<WireNodeData>(tr("Inputs"),tr("wires")).type();
       }
       case 1:{
         return BooleanNodeData(tr("Is Solid")).type();
       }
       case 2:{
          return BooleanNodeData(tr("Is Ruled")).type();
       }
       case 3:{
          return BooleanNodeData(tr("Is Compatible")).type();
        }
        case 4:{
          return BooleanNodeData(tr("Use Smoothing")).type();
        }
        case 5:{
         return BooleanNodeData(tr("Is Mutable")).type();
        }
        case 6:{
           return TemplatedData<Approx_ParametrizationType>(tr("ApproxParam"),tr("ApproxParam")).type();
        }
        case 7:{
          return TemplatedData<GeomAbs_Shape>(tr("Continuity"),tr("Continuity")).type();
        }
        case 8:{
          return IntegerNodeData(tr("Degree")).type();
        }
        case 9:{
          return PointNodeData(tr("input vertex")).type();
        }
       default:
         break;
       
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
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
  if(!data){
  return;
  }
  switch(portIndex){
   case 0:{
     inputWiresData=dynamic_pointer_cast<VectorDataNode<WireNodeData>>(data);
     if(inputWiresData.lock()){
      inputWires=inputWiresData.lock()->Data();
      isPort0Set=true;
      break;
     } 
   }
   case 1:{
     isSolidData=dynamic_pointer_cast<BooleanNodeData>(data);
     if(isSolidData.lock()){
     isSolid=isSolidData.lock()->Data();
     break;
     }
   }
   case 2:{
    isRuledData=dynamic_pointer_cast<BooleanNodeData>(data);
    if(isRuledData.lock()){
     isRuled=isRuledData.lock()->Data();
     break;
    }
   }
    case 3:{
    compatData=dynamic_pointer_cast<BooleanNodeData>(data);
    if(compatData.lock()){
     isCompat=compatData.lock()->Data();
     break;
    }
   }
   case 4:{
    smoothData=dynamic_pointer_cast<BooleanNodeData>(data);
    if(smoothData.lock()){
     useSmooth=smoothData.lock()->Data();
     break;
    }
   }
   case 5:{
   mutableData=dynamic_pointer_cast<BooleanNodeData>(data);
   if(mutableData.lock()){
    isMutable=mutableData.lock()->Data();
    break;
   }
   }
   case 6:{
   parData=dynamic_pointer_cast<TemplatedData<Approx_ParametrizationType>>(data);
   if(parData.lock()){
     parType=parData.lock()->Data();
     isPort6Set=true;
     break;
  }
}
  case 7:{
    continuityData=dynamic_pointer_cast<TemplatedData<GeomAbs_Shape>>(data);
    if(continuityData.lock()){
     continuity=continuityData.lock()->Data();
     isPort7Set=true;
     break;
    }
   }
   case 8:{
   integerData=dynamic_pointer_cast<IntegerNodeData>(data);
   if(integerData.lock()){
     maxDegree=integerData.lock()->Data();
     isPort8Set=true;
     break;
   }
   }
   case 9:{
   pointData=dynamic_pointer_cast<PointNodeData>(data);
   if(pointData.lock()){
     pnt=pointData.lock()->ToPnt();
     isPort9Set=true;
     break;
   }
   }
   }
   if(outputData){
    if(isPort0Set==false){
     return;
    }
    BRepOffsetAPI_ThruSections loftmaker(isSolid,isRuled);
    for(int i=0;i<inputWires.size();i++){
      loftmaker.AddWire(inputWires.at(i).Data());
    }
    loftmaker.CheckCompatibility(isCompat);
    loftmaker.SetSmoothing(useSmooth);
    loftmaker.SetMutableInput(isMutable);
    
    if(isPort6Set){
      loftmaker.SetParType(parType);
    }
     if(isPort7Set){
     loftmaker.SetContinuity(continuity);
     }
     if(isPort8Set){
       loftmaker.SetMaxDegree(maxDegree);
     }
     if(isPort9Set){
     BRepBuilderAPI_MakeVertex vertexmaker(pnt);
     if(vertexmaker.IsDone()){
       loftmaker.AddVertex(vertexmaker.Vertex());
     }
     }
     loftmaker.Build();
     if(loftmaker.IsDone()){
       outputShape=loftmaker.Shape();

     }
     else{
      LoadMessage(tr("Lofting Error"),LoftError::LoftEnumToString(loftmaker.GetStatus()));
      return;
     }
     outputData->SetData(outputShape);
   }
   else{
   outputData=std::make_shared<ShapeNodeData>(tr(""));
     if(isPort0Set==false){
     return;
    }
    BRepOffsetAPI_ThruSections loftmaker(isSolid,isRuled);
    for(int i=0;i<inputWires.size();i++){
      loftmaker.AddWire(inputWires.at(i).Data());
    }
    loftmaker.CheckCompatibility(isCompat);
    loftmaker.SetSmoothing(useSmooth);
    loftmaker.SetMutableInput(isMutable);
    
    if(isPort6Set){
      loftmaker.SetParType(parType);
    }
     if(isPort7Set){
     loftmaker.SetContinuity(continuity);
     }
     if(isPort8Set){
       loftmaker.SetMaxDegree(maxDegree);
     }
     if(isPort9Set){
     BRepBuilderAPI_MakeVertex vertexmaker(pnt);
     if(vertexmaker.IsDone()){
       loftmaker.AddVertex(vertexmaker.Vertex());
     }
     }
     loftmaker.Build();
     if(loftmaker.IsDone()){
       outputShape=loftmaker.Shape();

     }
     else{
      LoadMessage(tr("Lofting Error"),LoftError::LoftEnumToString(loftmaker.GetStatus()));
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





