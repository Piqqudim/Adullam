#pragma once
#include<QDialog>
#include<QFormLayout>
#include<QVBoxLayout>
#include<QDialogButtonBox>
#include<MyCustomAIS_Shape.hxx>
#include<Geom_Circle.hxx>
#include<Section.h>
#include<ColorPane.hpp>
#include<QRadioButton>
#include<ColorDialog.hpp>
#include<DoubleLineEdit.hpp>
#include<AIS_InteractiveContext.hxx>
#include<BRepBuilderAPI_MakeEdge.hxx>
#include<gp_Circ.hxx>

using namespace std;

class TwoPointArcDialog:public QDialog{
private:
Handle(CustomAIS_Shape) circleShape;
unique_ptr<DoubleEdit> radiusEdit;
unique_ptr<DoubleEdit> angleEdit;
unique_ptr<Section> axisSection;
unique_ptr<Section> rotateSection;
unique_ptr<QRadioButton> xdirect;
unique_ptr<QRadioButton> ydirect;
unique_ptr<QRadioButton> zdirect;
unique_ptr<QRadioButton> axisX;
unique_ptr<QRadioButton> axisY;
unique_ptr<QRadioButton> axisZ;
unique_ptr<QVBoxLayout> vlayout;
unique_ptr<QVBoxLayout> vlayout_1;
unique_ptr<QVBoxLayout> vlayout_2;
unique_ptr<QFormLayout> flayout;
unique_ptr<QDialogButtonBox> dialogButtons;
unique_ptr<ColorPane> clrpane;
unique_ptr<ColorDialog> colorDialog;
Handle(Geom_Circle) circle;
Handle(AIS_InteractiveContext) context;
TopoDS_Edge outputEdge=TopoDS_Edge();
gp_Ax2 axis;
gp_Pnt pnt;
float pie;
gp_Ax1 axisOfRotation;
public:
TwoPointArcDialog():QDialog(){
    setWindowTitle(tr("Two Point Arc Dialog"));
    pie=3.14159265;
    radiusEdit=make_unique<DoubleEdit>(this,QString::number(0.0),8);
    angleEdit=make_unique<DoubleEdit>(this,QString::number(0.0),8);
    axisSection=make_unique<Section>(tr("Axis Of Orientation"));
    rotateSection=make_unique<Section>(tr("Axis Of Rotation"));
    xdirect=make_unique<QRadioButton>(tr("X Direction"));
    ydirect=make_unique<QRadioButton>(tr("Y Direction"));
    zdirect=make_unique<QRadioButton>(tr("Z Direction"));
    axisX=make_unique<QRadioButton>(tr("X Direction"));
    axisY=make_unique<QRadioButton>(tr("Y Direction"));
    axisZ=make_unique<QRadioButton>(tr("Z Direction"));
    clrpane=make_unique<ColorPane>();
    vlayout=make_unique<QVBoxLayout>();
    vlayout_1=make_unique<QVBoxLayout>();
    vlayout_2=make_unique<QVBoxLayout>();
    colorDialog=make_unique<ColorDialog>();
    flayout=make_unique<QFormLayout>();
    vlayout->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    vlayout_1->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    vlayout_2->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    flayout->addRow(tr("Radius:"),radiusEdit.get());
    flayout->addRow(tr("Angle:"),angleEdit.get());
    flayout->addRow(tr("Color Pane:"),clrpane.get());
    vlayout->addLayout(flayout.get());
    vlayout_1->addWidget(xdirect.get());
    vlayout_1->addWidget(ydirect.get());
    vlayout_1->addWidget(zdirect.get());
    axisSection->setContentLayout(*vlayout_1.get());
    vlayout->addWidget(axisSection.get());
    vlayout_2->addWidget(axisX.get());
    vlayout_2->addWidget(axisY.get());
    vlayout_2->addWidget(axisZ.get());
    dialogButtons=make_unique<QDialogButtonBox>(QDialogButtonBox::Ok|QDialogButtonBox::Cancel);
    rotateSection->setContentLayout(*vlayout_2.get());
    vlayout->addWidget(rotateSection.get());
    vlayout->addWidget(dialogButtons.get());
    setLayout(vlayout.get());
    connect(dialogButtons.get(),&QDialogButtonBox::rejected,this,&TwoPointArcDialog::reject);
    connect(dialogButtons.get(),&QDialogButtonBox::accepted,this,&TwoPointArcDialog::accept);
    connect(radiusEdit.get(),&DoubleEdit::GetValue,this,&TwoPointArcDialog::OnHandleValue);
    connect(angleEdit.get(),&DoubleEdit::GetValue,this,&TwoPointArcDialog::OnHandleValue);
    connect(xdirect.get(),&QRadioButton::toggled,this,&TwoPointArcDialog::OnHandleValue);
    connect(ydirect.get(),&QRadioButton::toggled,this,&TwoPointArcDialog::OnHandleValue);    
    connect(zdirect.get(),&QRadioButton::toggled,this,&TwoPointArcDialog::OnHandleValue);    
    connect(axisX.get(),&QRadioButton::toggled,this,&TwoPointArcDialog::OnHandleValue);    
    connect(axisY.get(),&QRadioButton::toggled,this,&TwoPointArcDialog::OnHandleValue);    
    connect(axisZ.get(),&QRadioButton::toggled,this,&TwoPointArcDialog::OnHandleValue);    
    connect(clrpane.get(),&ColorPane::IsDoubleClicked,this,&TwoPointArcDialog::DoubleClick);
    connect(colorDialog->ColorWidget(),&ColorCollectionWidget::GetSelectedColor,this,&TwoPointArcDialog::OnHandleColor);

    return;
}
void SetContext(const Handle(AIS_InteractiveContext) con){
    context=con;
    return;
}
Handle(CustomAIS_Shape) CircleShape() const{
    return circleShape;
}
Handle(Geom_Circle) Circle() const{
    return circle;
}
void Nullify(){
    if(circleShape){
        context->Remove(circleShape,true);
        circleShape=nullptr;
    }
    return;
}
void SetPoint(const gp_Pnt& pnt_1){
    pnt=pnt_1;
    return;
}
void DetermineValue(){
    if(xdirect->isChecked()){
        axis=gp_Ax2(pnt,gp_Dir(1.0,0.0,0.0));
    }
    else if(ydirect->isChecked()){
        axis=gp_Ax2(pnt,gp_Dir(0.0,1.0,0.0));
    }
    else if(zdirect->isChecked()){
        axis=gp_Ax2(pnt,gp_Dir(0.0,0.0,1.0));
    }
    if(axisX->isChecked()){
        axisOfRotation=gp_Ax1(pnt,gp_Dir(1.0,0.0,0.0));
    }
    else if(axisY->isChecked()){
        axisOfRotation=gp_Ax1(pnt,gp_Dir(0.0,1.0,0.0));
    }
    else if(axisZ->isChecked()){
        axisOfRotation=gp_Ax1(pnt,gp_Dir(0.0,0.0,1.0));
    }
    return;
}
void OnDisplay(){
    if(!context){
        return;
    }
    DetermineValue();
    if(radiusEdit->Result()<=0.0){
        return;
    }
    float rad=angleEdit->Result()*(pie/180.0f);
    auto drawAxis=axis; //create a copy of the initial axis
    drawAxis.Rotate(axisOfRotation,rad);
    BRepBuilderAPI_MakeEdge edgemaker;
    if(!circle){
    circle=new Geom_Circle(drawAxis,radiusEdit->Result());
    }
    else{
   gp_Circ circ(drawAxis,radiusEdit->Result());
   circle->SetCirc(circ);
    }
    edgemaker.Init(circle);
    if(!edgemaker.IsDone()){
        return;
    }
    outputEdge=edgemaker.Edge();
    if(!circleShape){
        circleShape=new CustomAIS_Shape(edgemaker.Edge());
        circleShape->SetColor(colorDialog->GetColor());
        circleShape->SetZLayer(Graphic3d_ZLayerId_Topmost);
    }
    else{
        circleShape->Set(edgemaker.Edge());
        circleShape->SetColor(colorDialog->GetColor());
        circleShape->SetZLayer(Graphic3d_ZLayerId_Topmost);
    }
    if(context->IsDisplayed(circleShape)){
        context->Redisplay(circleShape,true);
    }
    else{
        context->Display(circleShape,true);
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
   }
 
  }
 return;  
}
public slots:
void OnHandleColor(){
    if(circleShape){
        circleShape->SetColor(colorDialog->GetColor());

    }
    clrpane->SetColorFromOC(colorDialog->GetColor());
    OnDisplay();
    return;
}
void OnHandleValue(const float& value){
  OnDisplay();
  return;
}
void OnHandleChecked(bool value){
    OnDisplay();
    return;
}
void DoubleClick(const int val){
    colorDialog->setWindowTitle(tr("Arc Circle Dialog"));
    colorDialog->exec();
    return;
}

};