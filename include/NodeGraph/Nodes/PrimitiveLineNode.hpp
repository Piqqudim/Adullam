#pragma once
#include<NodeDelegateModel>
#include<BRepBuilderAPI_MakeEdge.hxx>
#include<gp_Dir.hxx>
#include<TopoDS_Shape.hxx>
#include<ShapeNodeData.hpp>
#include<Geom_Line.hxx>
#include<memory>
#include<gp_Pnt.hxx>
using namespace std;
class PrimitiveLineNode:public NodeDelegateModel{
private:
shared_ptr<ShapeNodeData> outputData;
TopoDS_Shape outputShape;
gp_Dir dir=gp_Dir(0.0,0.0,1.0);
float Length=1.0f;
gp_Pnt point; //this is the start position
public:
PrimitiveLineNode(){
    return;
}
unsigned int nPorts(PortType portType) const override{
    switch(portType){
        case PortType::In:{
            return 0;
        }
        case PortType::Out:{
            return 1;
        }
    }
    return 0;
}
void SetLine(const gp_Dir& u_dir,const gp_Pnt& _p,const float& val){
    point=_p;
    dir=u_dir;
    Length=val;
    if(outputData){
     Handle(Geom_Line) line=new Geom_Line(_p,u_dir);
     if(!line){
        return;
     }
     BRepBuilderAPI_MakeEdge edgemaker;
     edgemaker.Init(line,0,val);
     if(edgemaker.IsDone()){
        outputData->SetData(edgemaker.Edge());
     }
    }
    else{
      outputData=std::make_shared<ShapeNodeData>(tr(""));
      Handle(Geom_Line) line=new Geom_Line(_p,u_dir);
     if(!line){
        return;
     }
     BRepBuilderAPI_MakeEdge edgemaker;
     edgemaker.Init(line,0,val);
     if(edgemaker.IsDone()){
        outputData->SetData(edgemaker.Edge());
     }
    }
    return;
}
QString caption() const override{
    return tr("Primitive Line");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::Out:{
            switch(portIndex){
                case 0:
                   return ShapeNodeData(tr("Output Shape")).type();

            }
        }
    }
    return {tr(""),tr("")};
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(outputData){
        return std::static_pointer_cast<NodeData>(outputData);
    }
    std::shared_ptr<NodeData> mptr;
    return mptr;
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
    return;
}
QWidget* embeddedWidget() override{
    return nullptr;
}
};