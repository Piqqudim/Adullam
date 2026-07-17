#ifndef SHAPENODEDATA_HPP
#define SHAPENODEDATA_HPP
#include<NodeData>
#include<TopoDS_Shape.hxx>
#include<Graphic3d_MaterialAspect.hxx>
using namespace QtNodes;
class ShapeNodeData:public NodeData{
    private:
    TopoDS_Shape m_Data;
     Graphic3d_MaterialAspect mat_aspect;
    
    QString m_Name;
    bool hasMaterial=true;  //ByDefault the object has no material
    int Index=-1;
 public:
explicit ShapeNodeData(const TopoDS_Shape& sh){
  m_Data=sh;
  return;
}
 ShapeNodeData(const Graphic3d_MaterialAspect& mat,const TopoDS_Shape& shape=TopoDS_Shape(),const int& ind=-1){
     m_Data=shape;
     Index=ind;
     mat_aspect=mat;
     return;
 }
    //it belongs to this class and not to an object of Shape
 ShapeNodeData(const QString& name=QString(""),const TopoDS_Shape& shape=TopoDS_Shape()):m_Name(name){
     m_Data=shape;
     return;
 }
 ShapeNodeData(const QString& name,const Graphic3d_MaterialAspect& mat,const TopoDS_Shape& shape){
  m_Name=name;
  mat_aspect=mat;
  m_Data=shape;
  return;
 }
 ShapeNodeData(const ShapeNodeData&& data){
  *this=std::move(data);
  return;
 }
 ShapeNodeData(const ShapeNodeData& shapedata){
  this->m_Data=shapedata.Data();
   this->mat_aspect=shapedata.aspect();
   this->hasMaterial=shapedata.HasMaterial();
   this->Index=shapedata.index(); 
   return;
 }
 TopoDS_Shape Data() const{
    return m_Data;
 }
 void SetIndex(const int& ind){
  Index=ind;
  return;
 }
 int index() const{
  return Index;
 }
 void SetTransform(const gp_Trsf& trsf){
    m_Data.Location(trsf);
    return;
 }
 void SetData(const TopoDS_Shape& shape){
   m_Data=shape;
   return;
 }
 void SetHasMaterialAspect(const bool& truth){
    hasMaterial=truth;
    return;
 }
 bool HasMaterial() const{
  return hasMaterial;
 }
 void SetHasMaterial(bool truth){
   hasMaterial=truth;
   return;
 }

 Graphic3d_MaterialAspect aspect() const{
   return mat_aspect;
 }
 void SetAspect(const Graphic3d_MaterialAspect& mat){
   mat_aspect=mat;
   return;
 }
 NodeDataType type() const override{
    return {"Shape",m_Name};
 }
 ShapeNodeData& operator=(const ShapeNodeData&& data){
   m_Data=std::move(data.Data()); 
   mat_aspect=std::move(data.aspect());
   hasMaterial=std::move(data.HasMaterial());
   Index=std::move(data.index());
   
   return *this;
 }
 ShapeNodeData& operator=(const ShapeNodeData& shapedata){
   this->m_Data=shapedata.Data();
   this->mat_aspect=shapedata.aspect();
   this->hasMaterial=shapedata.HasMaterial();
   this->Index=shapedata.index();
   return *this;
 }
};
#endif