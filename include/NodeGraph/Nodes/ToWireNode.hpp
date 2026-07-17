#pragma once 
#include<NodeDelegateModel>
#include<ShapeNodeData.hpp>
#include<WireNodeData.hpp>
#include<EdgeNodeData.hpp>
#include<FaceNodeData.hpp>
#include<TopoDS.hxx>
#include<InfoUtility.hpp>
#include<TopAbs_ShapeEnum.hxx>
#include<memory>
using namespace std;
using namespace QtNodes;
using namespace INFO;
class ToWireNode:public NodeDelegateModel{
private:
shared_ptr<WireNodeData> wireOutput;
TopoDS_Wire outputWire=TopoDS_Wire();
weak_ptr<ShapeNodeData> inputShape;
TopoDS_Shape input;

public:
ToWireNode(){
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
    return 0;
}
QString caption() const override{
    return tr("To Wire");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::In:{
             switch(portIndex){
                case 0:
                 return ShapeNodeData(tr("Input")).type();
               
             }
        }
        case PortType::Out:{
            switch(portIndex){
                case 0:{
                    return WireNodeData(tr("Output")).type();
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
        inputShape=dynamic_pointer_cast<ShapeNodeData>(data);
        if(inputShape.lock()){
         input=inputShape.lock()->Data();
         break;
        }
        }
    }
    if(wireOutput){
       if(input.ShapeType()!=TopAbs_WIRE){
         LoadMessage(tr(""),tr("The Shape is not a wire, so it is not convertible"));
        return;
       }
       outputWire=TopoDS::Wire(input);
       wireOutput->SetData(outputWire);      
    }
    else{
    wireOutput=std::make_shared<WireNodeData>(tr(""));
     if(input.ShapeType()!=TopAbs_WIRE){
         LoadMessage(tr(""),tr("The Shape is not a wire, so it is not convertible"));
        return;
       }
       outputWire=TopoDS::Wire(input);
       wireOutput->SetData(outputWire);
    }
    emit dataUpdated(0);
    return;
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
  if(wireOutput){
    return static_pointer_cast<NodeData>(wireOutput);
  } 

    std::shared_ptr<NodeData> mptr;
    return static_pointer_cast<NodeData>(mptr);
}
QWidget* embeddedWidget() override{
    return nullptr;
}
};



class ToFaceNode:public NodeDelegateModel{
private:
shared_ptr<FaceNodeData> faceOutput;
TopoDS_Face outputFace=TopoDS_Face();
weak_ptr<ShapeNodeData> inputShape;
TopoDS_Shape input;

public:
ToFaceNode(){
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
    return 0;
}
QString caption() const override{
    return tr("To Face");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::In:{
             switch(portIndex){
                case 0:
                 return ShapeNodeData(tr("Input")).type();
               
             }
        }
        case PortType::Out:{
            switch(portIndex){
                case 0:{
                    return FaceNodeData(tr("Output")).type();
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
        inputShape=dynamic_pointer_cast<ShapeNodeData>(data);
        if(inputShape.lock()){
         input=inputShape.lock()->Data();
         break;
        }
        }
    }
    if(faceOutput){
       if(input.ShapeType()!=TopAbs_FACE){
         LoadMessage(tr(""),tr("The Shape is not a face, so it is not convertible"));
        return;
       }
       outputFace=TopoDS::Face(input);
       faceOutput->SetFaceData(outputFace);      
    }
    else{
    faceOutput=std::make_shared<FaceNodeData>(tr(""));
     if(input.ShapeType()!=TopAbs_FACE){
         LoadMessage(tr(""),tr("The Shape is not a face, so it is not convertible"));
        return;
       }
       outputFace=TopoDS::Face(input);
       faceOutput->SetFaceData(outputFace);
    }
    emit dataUpdated(0);
    return;
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
  if(faceOutput){
    return static_pointer_cast<NodeData>(faceOutput);
  } 

    std::shared_ptr<NodeData> mptr;
    return static_pointer_cast<NodeData>(mptr);
}
QWidget* embeddedWidget() override{
    return nullptr;
}


};

//EdgeNode implementation
class ToEdgeNode:public NodeDelegateModel{
private:
shared_ptr<EdgeNodeData> edgeOutput;
TopoDS_Edge outputEdge=TopoDS_Edge();
weak_ptr<ShapeNodeData> inputShape;
TopoDS_Shape input;

public:
ToEdgeNode(){
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
    return 0;
}
QString caption() const override{
    return tr("To Edge");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::In:{
             switch(portIndex){
                case 0:
                 return ShapeNodeData(tr("Input")).type();
               
             }
        }
        case PortType::Out:{
            switch(portIndex){
                case 0:{
                    return EdgeNodeData(tr("Output")).type();
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
        inputShape=dynamic_pointer_cast<ShapeNodeData>(data);
        if(inputShape.lock()){
         input=inputShape.lock()->Data();
         break;
        }
        }
    }
    if(edgeOutput){
       if(input.ShapeType()!=TopAbs_EDGE){
         LoadMessage(tr(""),tr("The Shape is not an edge, so it is not convertible"));
        return;
       }
       outputEdge=TopoDS::Edge(input);
        edgeOutput->SetEdge(outputEdge);      
    }
    else{
    edgeOutput=std::make_shared<EdgeNodeData>(tr(""));
     if(input.ShapeType()!=TopAbs_EDGE){
         LoadMessage(tr(""),tr("The Shape is not an edge, so it is not convertible"));
        return;
       }
       outputEdge=TopoDS::Edge(input);
       edgeOutput->SetEdge(outputEdge);
    }
    emit dataUpdated(0);
    return;
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
  if(edgeOutput){
    return static_pointer_cast<NodeData>(edgeOutput);
  } 

    std::shared_ptr<NodeData> mptr;
    return static_pointer_cast<NodeData>(mptr);
}
QWidget* embeddedWidget() override{
    return nullptr;
}

};