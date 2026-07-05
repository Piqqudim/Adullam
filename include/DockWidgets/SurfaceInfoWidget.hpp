#pragma once 
#include<QtWidgets/QWidget>
#include<QtWidgets/QVBoxLayout>
#include<QtWidgets/QStackedWidget>
#include<SurfaceInfoPane.hpp>
#include<MyCustomAIS_Shape.hxx>
using namespace SURFACE;
class SurfaceInfoWidget:public QStackedWidget{
 private:
 Q_OBJECT
 std::unique_ptr<SurfaceInfoSection> surface_section;
 std::unique_ptr<QVBoxLayout> vlayout;
 Handle(CustomAIS_Shape) prevShape;
 Handle(CustomAIS_Shape) currShape;
 public:
 SurfaceInfoWidget(QWidget* parent=nullptr):QStackedWidget(parent){
  return;
 }
 SurfaceInfoWidget(QWidget* parent,const SurfaceInfo& info,const QString& title){
  surface_section=std::make_unique<SurfaceInfoSection>(info,title,this);
  vlayout=make_unique<QVBoxLayout>();
  vlayout->setAlignment(Qt::AlignTop|Qt::AlignLeft);
  vlayout->addWidget(surface_section.get());
  setLayout(vlayout.get());
  return;
 }
 
 void SetSurfaceInfo(const SurfaceInfo& info){
   if(surface_section){
    removeWidget(surface_section.get());
    surface_section->setParent(nullptr);
    surface_section.reset();
   }
   surface_section=std::make_unique<SurfaceInfoSection>(info,QString("Surface Section"),nullptr);
   addWidget(surface_section.get());
   setCurrentWidget(surface_section.get());
   return;
 }
 void SetSurfaceInfos(const Handle(CustomAIS_Shape)& shape){
      
    return;
 }
 void SetCurrentShape(const Handle(CustomAIS_Shape)& shape){
  currShape=shape;
  return;
 }
 Handle(CustomAIS_Shape) GetCurrentShape() const{ 
  return currShape;
 }
 signals:
 void EmitIndex(unsigned int index);


 public slots:
 void OnReceiveIndex(unsigned int index){
     emit EmitIndex(index);
     return;
 }
};
