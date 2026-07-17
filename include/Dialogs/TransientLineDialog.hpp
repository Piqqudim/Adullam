#pragma once 
#include<QtWidgets/QDialog>
#include<memory>
#include<QtWidgets/QVBoxLayout>
#include<QtWidgets/QDialogButtonBox>
#include<Section.h>
#include<QtWidgets/QFormLayout>
#include<DoubleLineEdit.hpp>
#include<MyCustomAIS_Shape.hxx>
#include<AIS_InteractiveContext.hxx>
#include<gp_Dir.hxx>
#include<gp_Ax1.hxx>
#include<BRepBuilderAPI_MakeEdge.hxx>

using namespace std;
class TransientLineDialog:public QDialog{
private:
std::unique_ptr<QVBoxLayout> vlayout;
unique_ptr<QFormLayout> formLayout;
unique_ptr<QFormLayout> formLayout_1;
unique_ptr<QVBoxLayout> vlayout_2; //for direction of rotation
unique_ptr<QVBoxLayout> vlayout_3; //for direction of draw.
std::unique_ptr<DoubleEdit> lengthEdit;
unique_ptr<DoubleEdit> relativeAngleEdit;
unique_ptr<Section> directOfDrawSection;
unique_ptr<Section> directOfRotateSection;
std::unique_ptr<QRadioButton> xDirectButton;
std::unique_ptr<QRadioButton> yDirectButton;
std::unique_ptr<QRadioButton> zDirectButton;
std::unique_ptr<QRadioButton> inXButton;
std::unique_ptr<QRadioButton> inYButton;
std::unique_ptr<QRadioButton> inZButton;
std::unique_ptr<QRadioButton> negInXButton;
std::unique_ptr<QRadioButton> negInYButton;
std::unique_ptr<QRadioButton> negInZButton;
std::unique_ptr<QDialogButtonBox> dialogButtons;

Handle(AIS_InteractiveContext) context;
Handle(CustomAIS_Shape) lineShape;
float pie;
float relativeAngle=0.0f; //specified in degrees,it has to be converted to radian
float length=0.0;  // length..
gp_Dir direction=gp_Dir(0.0,.0,1.0); // direction of draw
gp_Dir changedDir=gp_Dir(0.0,0.0,1.0);
gp_Ax1 axisOfRotation; //axis of rotation;

gp_Pnt pointOfRotation;

public:
TransientLineDialog(QWidget* parent=nullptr):QDialog(parent){
    pie=3.14159265;
    setWindowTitle(tr("Transient Line Dialog"));
    vlayout=std::make_unique<QVBoxLayout>();
    vlayout->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    formLayout=std::make_unique<QFormLayout>();
    formLayout_1=make_unique<QFormLayout>();
    vlayout_2=make_unique<QVBoxLayout>();
    vlayout_3=make_unique<QVBoxLayout>();
    lengthEdit=make_unique<DoubleEdit>(this,QString::number(0.0),8); //no length
    relativeAngleEdit=make_unique<DoubleEdit>(this,QString::number(0.0),8); //no relative angle
    directOfDrawSection=make_unique<Section>(tr("Direction Of Draw"));
    directOfRotateSection=make_unique<Section>(tr("Direction Of Rotation"));
    xDirectButton=make_unique<QRadioButton>(tr("About X direction"));
    yDirectButton=make_unique<QRadioButton>(tr("About Y direction"));
    zDirectButton=make_unique<QRadioButton>(tr("About Z direction"));
    inXButton=make_unique<QRadioButton>(tr("X  direction"));
    inYButton=make_unique<QRadioButton>(tr("Y direction"));
    inZButton=make_unique<QRadioButton>(tr("Z direction"));
    negInXButton=make_unique<QRadioButton>(tr("-X direction"));
    negInYButton=make_unique<QRadioButton>(tr("-Y direction"));
    negInZButton=make_unique<QRadioButton>(tr("-Z direction"));
   
   
    formLayout->addRow(tr("Length:"),lengthEdit.get());
    vlayout->addLayout(formLayout.get());
    formLayout_1->addRow(tr("Relative Angle:"),relativeAngleEdit.get());
    vlayout->addLayout(formLayout_1.get());
    
    vlayout_2->addWidget(inXButton.get());
    vlayout_2->addWidget(inYButton.get());
    vlayout_2->addWidget(inZButton.get());
    vlayout_2->addWidget(negInXButton.get());
    vlayout_2->addWidget(negInYButton.get());
    vlayout_2->addWidget(negInZButton.get());
    directOfDrawSection->setContentLayout(*vlayout_2.get());
    vlayout->addWidget(directOfDrawSection.get());
    vlayout_3->addWidget(xDirectButton.get());
    vlayout_3->addWidget(yDirectButton.get());
    vlayout_3->addWidget(zDirectButton.get());

    directOfRotateSection->setContentLayout(*vlayout_3.get());
    vlayout->addWidget(directOfRotateSection.get());
    dialogButtons=make_unique<QDialogButtonBox>(QDialogButtonBox::Ok|QDialogButtonBox::Cancel);
    vlayout->addWidget(dialogButtons.get());
    setLayout(vlayout.get());
    setSizeGripEnabled(true);
    connect(relativeAngleEdit.get(),&DoubleEdit::GetValue,this,&TransientLineDialog::OnHandleEditValue);
    connect(lengthEdit.get(),&DoubleEdit::GetValue,this,&TransientLineDialog::OnHandleEditValue);
    
   
    connect(dialogButtons.get(),&QDialogButtonBox::accepted,this,&TransientLineDialog::OnHandleOk);
    connect(dialogButtons.get(),&QDialogButtonBox::rejected,this,&TransientLineDialog::OnHandleCancel);
    connect(xDirectButton.get(),&QRadioButton::toggled,this,&TransientLineDialog::isToggled);
    connect(yDirectButton.get(),&QRadioButton::toggled,this,&TransientLineDialog::isToggled);
    connect(zDirectButton.get(),&QRadioButton::toggled,this,&TransientLineDialog::isToggled);
    connect(inXButton.get(),&QRadioButton::toggled,this,&TransientLineDialog::isToggled);
    connect(inYButton.get(),&QRadioButton::toggled,this,&TransientLineDialog::isToggled);
    connect(inZButton.get(),&QRadioButton::toggled,this,&TransientLineDialog::isToggled);
    connect(negInXButton.get(),&QRadioButton::toggled,this,&TransientLineDialog::isToggled);
    connect(negInYButton.get(),&QRadioButton::toggled,this,&TransientLineDialog::isToggled);
    connect(negInZButton.get(),&QRadioButton::toggled,this,&TransientLineDialog::isToggled);
    return;
}
void SetPoint(const gp_Pnt& pnt){
    pointOfRotation=pnt;
    return;
}
void SetContext(Handle(AIS_InteractiveContext) con){
    context=con;
    return;
}
void EraseShape(){
 if(context->IsDisplayed(lineShape)){
   context->Erase(lineShape,true);    
 }
    return;
}
float Angle() const{
    return relativeAngleEdit->Result();
}
float Length() const{
    return lengthEdit->Result();
}
gp_Dir Direction() const{
    return direction;
}
gp_Dir ChangedDir() const{
    return changedDir;
}
gp_Ax1 Axis() const{
    return axisOfRotation;
}
void NullifyShape(){
 lineShape.Nullify();
 return;
}
void DetermineValue(){
     if(inXButton->isChecked()){
        direction=gp_Dir(1.0,0.0,0.0);
    }
    else if(inYButton->isChecked()){
        direction=gp_Dir(0.0,1.0,0.0);
    }
    else if(inZButton->isChecked()){
        direction=gp_Dir(0.0,0.0,1.0);
    }
    else if(negInXButton->isChecked()){
        direction=gp_Dir(-1.0,0.0,0.0);
    }
    else if(negInYButton->isChecked()){
        direction=gp_Dir(0.0,-1.0,0.0);
    }
    else if(negInZButton->isChecked()){
        direction=gp_Dir(0.0,0.0,-1.0);
    }
    if(xDirectButton->isChecked()){
        axisOfRotation=gp_Ax1(pointOfRotation,gp_Dir(1.0,0.0,0.0));
    }
    else if(yDirectButton->isChecked()){
        axisOfRotation=gp_Ax1(pointOfRotation,gp_Dir(0.0,1.0,0.0));
    }
     if(zDirectButton->isChecked()){
        axisOfRotation=gp_Ax1(pointOfRotation,gp_Dir(0.0,0.0,1.0));
    }
    return;
    
}
void OnDisplay(){
    if(!context){
        return;
    }
    DetermineValue();
    if(Length()==0.0){
        return;
    }
   float ang=Angle()*(pie/180.0f);
   auto dir=Direction(); 
    auto axis=Axis();
    dir.Rotate(axis,ang);
    changedDir=dir; //after applying transformation
    BRepBuilderAPI_MakeEdge edgeMaker;
    Handle(Geom_Line) line=new Geom_Line(pointOfRotation,dir);
    edgeMaker.Init(line,0,Length());
    if(!edgeMaker.IsDone()){
        return;
    }
     if(lineShape.IsNull()){
      lineShape=new CustomAIS_Shape(edgeMaker.Edge());
      context->Display(lineShape,true);
      return;
    }
   lineShape->SetShape(edgeMaker.Edge());
   CheckDisplayStatus(lineShape,context->DisplayStatus(lineShape));
   context->UpdateCurrentViewer(); 

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
void isToggled(bool value){
    OnDisplay();
    return;
}
void OnHandleCancel(){
    if(lineShape){
        context->Erase(lineShape,true);
    }
    reject();
    return;
}
void OnHandleOk(){
    accept();
    return;
}
void OnHandleEditValue(const float& val){
    OnDisplay();
    return;
}

};