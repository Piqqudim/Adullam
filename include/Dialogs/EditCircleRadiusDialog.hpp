#pragma once
#include<QtWidgets/QFormLayout>
#include<MyCustomAIS_Shape.hxx>
#include<QtWidgets/QLabel>
#include<QtWidgets/QDialog>
#include<DoubleLineEdit.hpp>
#include<QtWidgets/QVBoxLayout>
#include<QtWidgets/QDialogButtonBox>
#include<Geom_Circle.hxx>
#include<BRepBuilderAPI_MakeEdge.hxx>

class EditDialog:public QDialog{
private:
Q_OBJECT
Handle(Geom_Circle) circle;
Handle(CustomAIS_Shape) circleShape;
std::unique_ptr<QFormLayout> flayout;
std::unique_ptr<QVBoxLayout> vlayout;
std::unique_ptr<QLabel> label;
std::unique_ptr<DoubleEdit> radiusEdit;
Handle(AIS_InteractiveContext) context;
std::unique_ptr<QDialogButtonBox> buttons;
float radius=0.0f;
public:
EditDialog():QDialog(){
   setWindowTitle(tr("Edit Circle Radius Dialog"));
   flayout=std::make_unique<QFormLayout>();
   label=std::make_unique<QLabel>(QString::number(0.0));
   radiusEdit=std::make_unique<DoubleEdit>(nullptr,QString::number(0.0),8);
   vlayout=std::make_unique<QVBoxLayout>();
   vlayout->setAlignment(Qt::AlignTop|Qt::AlignLeft);
   flayout->addRow(tr("Previous Radius:"),label.get());
   flayout->addRow(tr("Current Radius:"),radiusEdit.get());
   vlayout->addLayout(flayout.get());
   buttons=std::make_unique<QDialogButtonBox>(QDialogButtonBox::Ok|QDialogButtonBox::Cancel,nullptr);
   vlayout->addWidget(buttons.get());
   setLayout(vlayout.get());
   connect(radiusEdit.get(),&DoubleEdit::GetValue,this,&EditDialog::OnGetRadius);
   connect(buttons.get(),&QDialogButtonBox::rejected,this,&EditDialog::OnHandleCancel);
   connect(buttons.get(),&QDialogButtonBox::accepted,this,&EditDialog::OnHandleOk);
   return;
}
void SetContext(Handle(AIS_InteractiveContext) con){
    context=con;
    return;
}
void SetPreviousRadius(const float& r){
   label->setText(QString::number(r));
   return;
}
void SetCircleInfo(const Handle(Geom_Circle) c){
    circle=c;
  return;
}
Handle(Geom_Circle) CircleInfo() const{
    return circle;
}
void OnDisplay(){
    if(!circle){
        return;
    }
    if(radius==0.0){
        return;
    }
    circle->SetRadius(radius);
    BRepBuilderAPI_MakeEdge edgeMaker;
    edgeMaker.Init(circle);
    if(!edgeMaker.IsDone()){
       return;
    }
    if(!circleShape){
    circleShape=new CustomAIS_Shape(edgeMaker.Edge());
    context->Display(circleShape,true);
    }
    else{
        circleShape->SetShape(edgeMaker.Edge());
      CheckDisplayStatus(circleShape,context->DisplayStatus(circleShape));
      context->UpdateCurrentViewer();
    }
    return;
}
void CheckDisplayStatus(Handle(AIS_InteractiveObject) object,const PrsMgr_DisplayStatus& status){
  switch(status){
    case PrsMgr_DisplayStatus_Displayed:{
      context->Redisplay(object,false);
      break;
    }
   case PrsMgr_DisplayStatus_Erased:{
     context->Display(object,false);
     break;
   }
 
  }
 return;  
}
float Radius() const{
    return radius;
}
signals:
void Done();


public slots:
void OnHandleCancel(){
    if(circleShape){
        context->Erase(circleShape,true);
    }
    reject();
    return;
}
void OnHandleOk(){
    if(circleShape){
        context->Erase(circleShape,true);
    }
    emit Done();
    accept();
    return;
}
void OnGetRadius(const float& r){
    radius=r;
    OnDisplay();
    return;
}
};
