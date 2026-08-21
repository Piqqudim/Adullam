#pragma once
#include<NodeDelegateModel>
#include<BRepBuilderAPI_MakeFace.hxx>
#include<ShapeNodeData.hpp>
#include<InfoUtility.hpp >
#include<TopoDS.hxx>
#include<TopAbs_ShapeEnum.hxx>
#include<memory>
using namespace std;
using namespace QtNodes;
using namespace INFO;
class ConvertToFace: public NodeDelegateModel{
private:
std::shared_ptr<ShapeNodeData> outputShape;
std::weak_ptr<ShapeNodeData> inputShape;
TopoDS_Wire wire;

public:

ConvertToFace(){
    return;
}
unsigned int nPorts(PortType portType) const override{
    switch(portType){
        case PortType::In:{
          return 1;
        }
        case PortType::Out:{
            return 1;
        }
    }
}
QString caption() const override{
    return tr("Convert To Face");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::In:{
            switch(portIndex){
                case 0:{
                    return ShapeNodeData(tr("Input")).type();
                }
            }
        }
        case PortType::Out:{
            switch(portIndex){
                case 0:{
                    return ShapeNodeData(tr("Output")).type();
                }
            }
        }
    default:
    break;
    }
    return {tr(""),tr("")};
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
    if(!data){
        return;
    }
    switch(portIndex){
        case 0:{
          inputShape=dynamic_pointer_cast<ShapeNodeData>(data);
          if(inputShape.lock()){
           if(inputShape.lock()->Data().ShapeType()==TopAbs_WIRE){
           wire=TopoDS::Wire(inputShape.lock()->Data());
           }
           break;
          }  
        }
    }
    if(outputShape){
    if(wire.IsNull()){
      LoadMessage(tr(""),tr("Failed to convert to wire"));
      return;
    }
     BRepBuilderAPI_MakeFace facemaker(wire);
     if(facemaker.IsDone()){
        outputShape->SetData(facemaker.Face());
     }
     else{
        LoadMessage(tr(""),tr("Failed to convert to face"));
        return;
     }
    }
    else{
       outputShape=std::make_shared<ShapeNodeData>(tr(""));
    if(wire.IsNull()){
      LoadMessage(tr(""),tr("Failed to convert to wire"));
      return;
    }
     BRepBuilderAPI_MakeFace facemaker(wire);
     if(facemaker.IsDone()){
        outputShape->SetData(facemaker.Face());
     }
     else{
        LoadMessage(tr(""),tr("Failed to construct face from wire"));
        return;
     }
     }
    
    emit dataUpdated(0);

}
std::shared_ptr<NodeData> outData(PortIndex port) override{
  if(outputShape){
    return static_pointer_cast<NodeData>(outputShape);
  } 

    std::shared_ptr<NodeData> mptr;
    return static_pointer_cast<NodeData>(mptr);
}
QWidget* embeddedWidget() override{
    return nullptr;
}
};
