#pragma once
#include<memory>
#include<ShapeNodeData.hpp>
#include<NodeDelegateModel>
#include<WireNodeData.hpp>
#include<FaceNodeData.hpp>
#include<InfoUtility.hpp>
#include<EdgeNodeData.hpp>
using namespace INFO;
using namespace QtNodes;
using namespace std;
class ConvertWireToShape:public NodeDelegateModel{
private:
TopoDS_Wire inputWire;
std::weak_ptr<WireNodeData> inputWireData;
std::shared_ptr<ShapeNodeData> outputData;

public:
ConvertWireToShape(){

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
    return 0;
}
QString caption() const override{
    return tr("Convert Wire To Shape");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::In:{
            if(portIndex==0){
                return WireNodeData(tr("Input Wire")).type();
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
std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(outputData){
        outputData->SetData(inputWire);
        return static_pointer_cast<ShapeNodeData>(outputData);
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
            inputWireData=dynamic_pointer_cast<WireNodeData>(data);
            if(inputWireData.lock()){
                inputWire=inputWireData.lock()->Data();
                break;
            }
        }
    }
    if(outputData){
        if(inputWire.IsNull()){
         LoadMessage(tr(""),tr("The Input Wire is invalid"));
        }
        outputData->SetData(inputWire);
    }
    else{
    outputData=std::make_shared<ShapeNodeData>(tr(""));
     if(inputWire.IsNull()){
         LoadMessage(tr(""),tr("The Input Wire is invalid"));
        }
        outputData->SetData(inputWire);
    }
    emit dataUpdated(0);
    return;
}
QWidget* embeddedWidget() override{
    return nullptr;
}
};

class ConvertFaceToShape:public NodeDelegateModel{
private:
TopoDS_Face inputFace;
std::weak_ptr<FaceNodeData> inputFaceData;
std::shared_ptr<ShapeNodeData> outputData;

public:
ConvertFaceToShape(){

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
    return 0;
}
QString caption() const override{
    return tr("Convert Face To Shape");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::In:{
            if(portIndex==0){
                return FaceNodeData(tr("Input Face")).type();
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
std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(outputData){
        outputData->SetData(inputFace);
        return static_pointer_cast<ShapeNodeData>(outputData);
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
            inputFaceData=dynamic_pointer_cast<FaceNodeData>(data);
            if(inputFaceData.lock()){
                inputFace=inputFaceData.lock()->GetFaceData();
                break;
            }
        }
    }
    if(outputData){
        if(inputFace.IsNull()){
         LoadMessage(tr(""),tr("The Input Face is invalid"));
        }
        outputData->SetData(inputFace);
    }
    else{
    outputData=std::make_shared<ShapeNodeData>(tr(""));
     if(inputFace.IsNull()){
         LoadMessage(tr(""),tr("The Input Face is invalid"));
        }
        outputData->SetData(inputFace);
    }
    emit dataUpdated(0);
    return;
}
QWidget* embeddedWidget() override{
    return nullptr;
}
};



class ConvertEdgeToShape:public NodeDelegateModel{
private:
TopoDS_Edge inputEdge;
std::weak_ptr<EdgeNodeData> inputEdgeData;
std::shared_ptr<ShapeNodeData> outputData;

public:
ConvertEdgeToShape(){

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
    return 0;
}
QString caption() const override{
    return tr("Convert Edge To Shape");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::In:{
            if(portIndex==0){
                return EdgeNodeData(tr("Input Edge")).type();
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
std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(outputData){
        outputData->SetData(inputEdge);
        return static_pointer_cast<ShapeNodeData>(outputData);
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
            inputEdgeData=dynamic_pointer_cast<EdgeNodeData>(data);
            if(inputEdgeData.lock()){
                inputEdge=inputEdgeData.lock()->edge();
                break;
            }
        }
    }
    if(outputData){
        if(inputEdge.IsNull()){
         LoadMessage(tr(""),tr("The Input Edge is invalid"));
        }
        outputData->SetData(inputEdge);
    }
    else{
    outputData=std::make_shared<ShapeNodeData>(tr(""));
     if(inputEdge.IsNull()){
         LoadMessage(tr(""),tr("The Input Edge is invalid"));
        }
        outputData->SetData(inputEdge);
    }
    emit dataUpdated(0);
    return;
}
QWidget* embeddedWidget() override{
    return nullptr;
}
};