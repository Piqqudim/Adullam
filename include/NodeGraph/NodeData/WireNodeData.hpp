#pragma once
#include<NodeData>
#include<TopoDS_Shape.hxx>
#include<TopoDS_Wire.hxx>
using namespace QtNodes;
class WireNodeData:public NodeData {
private:
TopoDS_Wire m_Data;
QString m_Name;

public:
explicit WireNodeData(const TopoDS_Wire& wire){
    m_Data=wire;
    return;
}
WireNodeData(const QString& name=QString("")):m_Name{name}{
    return;
}
WireNodeData(const WireNodeData& data){
    m_Data=data.Data();
    return;
}
void SetData(const TopoDS_Wire& wire){
    m_Data=wire;
    return;
}
TopoDS_Wire Data() const{
    return m_Data;
}
WireNodeData& operator=(const WireNodeData& wirenodedata){
    m_Data=wirenodedata.Data();
    return *this;
}
NodeDataType type() const override{
    return {"Wire",m_Name};
}
};