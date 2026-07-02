#pragma once
#include<BRepOffsetAPI_MakeEvolved.hxx>
#include<ShapeNodeData.hpp>
#include<WireNodeData.hpp>
#include<BooleanNodeData.hpp>
#include<FloatNodeData.hpp>
#include<memory>
#include<NodeDelegateModel>
#include<NodeInitializer.hpp>
#include<InfoUtility.hpp>
#include<GeomAbs_JoinType.hxx>
using namespace std;
using namespace INFO;
class MakeEvolvedNode:public NodeDelegateModel,public NodeInitializer{
private:
std::weak_ptr<ShapeNodeData> inputShapeData;
std::weak_ptr<WireNodeData> wireShapeData;
std::weak_ptr<TemplatedData<GeomAbs_JoinType>> joinData;
std::weak_ptr<BooleanNodeData> isAxeProfData; //use profile axis
std::weak_ptr<BooleanNodeData> isSolidData;  //make solid
std::weak_ptr<BooleanNodeData> isProfOnSpineData;  //is profile on spine(an object of TopoDS_Wire)
std::shared_ptr<ShapeNodeData> outputData;
TopoDS_Shape outputShape;
TopoDS_Shape inputShape;
TopoDS_Wire inputWire;
GeomAbs_JoinType jtype=GeomAbs_Arc;
bool isAxeProf=true;
bool isSolid=false;
bool isProfOnSpine=false;
bool isPortASet=false;
bool isPortBSet=false;

public:
MakeEvolvedNode(){
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
                   return WireNodeData(tr("Input Wire")).type();
                case 2:
                   return TemplatedData<GeomAbs_JoinType>(tr("Join Type"),tr("Join Type")).type();
                case 3:
                   return BooleanNodeData(tr("Use Profile Axis")).type();                        
                case 4:
                  return BooleanNodeData(tr("Make Solid")).type();
                case 5:
                  return BooleanNodeData(tr("Profile On Spine")).type();
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
        inputShapeData=dynamic_pointer_cast<ShapeNodeData>(data);
        if(inputShapeData.lock()){
            inputShape=inputShapeData.lock()->Data();
            isPortASet=true;
            break;
        }
    }
    case 1:{
        wireShapeData=dynamic_pointer_cast<WireNodeData>(data);
        if(wireShapeData.lock()){
            inputWire=wireShapeData.lock()->Data();
            isPortBSet=true;
            break;
        }
    }
    case 2:{
        joinData=dynamic_pointer_cast<TemplatedData<GeomAbs_JoinType>>(data);
        if(joinData.lock()){
            jtype=joinData.lock()->Data();
            break;
        }
    }
    case 3:{
        isAxeProfData=dynamic_pointer_cast<BooleanNodeData>(data);
        if(isAxeProfData.lock()){
            isAxeProf=isAxeProfData.lock()->Data();
            break;
        }
    }
    case 4:{
       isSolidData=dynamic_pointer_cast<BooleanNodeData>(data);
       if(isSolidData.lock()){
         isSolid=isSolidData.lock()->Data();
         break;
       } 
    }
    case 5:{
        isProfOnSpineData=dynamic_pointer_cast<BooleanNodeData>(data);
        if(isProfOnSpineData.lock()){
            isProfOnSpine=isProfOnSpineData.lock()->Data();
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
    if(inputShape.ShapeType()!=4 || inputShape.ShapeType()!=TopAbs_WIRE){
        LoadMessage(tr("Shape Selection Error"),tr("The Input Shape is neither a face or a wire,please reselect the shape"));
        return;
    }
    BRepOffsetAPI_MakeEvolved evolvedmaker(inputShape,inputWire,jtype,isAxeProf,isSolid,isProfOnSpine);
    evolvedmaker.Build();
    if(evolvedmaker.IsDone()){
        outputShape=evolvedmaker.Shape();
    }
    else{

        return;
    }
    outputData->SetData(outputShape);
 }
 else{
  outputData=std::make_shared<ShapeNodeData>();
  if(isPortASet==false){
      return;
    }
    if(isPortBSet==false){
        return;
    }
    if(inputShape.ShapeType()!=4 || inputShape.ShapeType()!=TopAbs_WIRE){
        LoadMessage(tr("Shape Selection Error"),tr("The Input Shape is neither a face or a wire,please reselect the shape"));
        return;
    }
    BRepOffsetAPI_MakeEvolved evolvedmaker(inputShape,inputWire,jtype,isAxeProf,isSolid,isProfOnSpine);
    evolvedmaker.Build();
    if(evolvedmaker.IsDone()){
        outputShape=evolvedmaker.Shape();
    }
    else{

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
