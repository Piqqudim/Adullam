#pragma once 
#include<AIS_InteractiveContext.hxx>
#include<Geom_Circle.hxx>
#include<gp_Ax2.hxx>
#include<Section.h>
#include<MyCustomAIS_Shape.hxx>
#include<QtWidgets/QVBoxLayout>
#include<memory>
#include<DoubleLineEdit.hpp>
#include<QtWidgets/QDialog>
#include<QtWidgets/QRadioButton>
#include<QtWidgets/QDialogButtonBox>
#include<QtWidgets/QFormLayout>
#include<BRepBuilderAPI_MakeEdge.hxx>
using namespace std;

class TransientCircleDialog:public QDialog{
private:
std::unique_ptr<DoubleEdit> radiusEdit;
std::unique_ptr<DoubleEdit> angleEdit;
std::unique_ptr<Section> axisSection;
std::unique_ptr<Section> rotateSection;
std::unique_ptr<QRadioButton> xDirect;
std::unique_ptr<QRadioButton> yDirect;
std::unique_ptr<QRadioButton> zDirect;
std::unique_ptr<QRadioButton> negXDirect;
std::unique_ptr<QRadioButton> negYDirect;
std::unique_ptr<QRadioButton> negZDirect;
std::unique_ptr<QRadioButton> axisX;
std::unique_ptr<QRadioButton> axisY;
std::unique_ptr<QRadioButton> axisZ;
std::unique_ptr<QVBoxLayout> vlayout;
std::unique_ptr<QVBoxLayout> vlayout_1;
std::unique_ptr<QVBoxLayout> vlayout_2;
std::unique_ptr<QFormLayout> flayout;
std::unique_ptr<QDialogButtonBox> dialogButtons;
Handle(AIS_InteractiveContext) context;
Handle(CustomAIS_Shape) circleShape;
gp_Ax1 axisOfRotation;
gp_Ax2 axisOfDraw;
gp_Pnt pnt;
gp_Ax2 changedAxis;
float pie=3.14159265;

public:
TransientCircleDialog():QDialog(){
    setWindowTitle(tr("Transient Circle Dialog"));
    radiusEdit=std::make_unique<DoubleEdit>(this,QString::number(0.0),8);
   angleEdit=std::make_unique<DoubleEdit>(this,QString::number(0.0),8);
   axisSection=std::make_unique<Section>(tr("Axis Of Orientation"));
   rotateSection=std::make_unique<Section>(tr("Axis Of Rotation"));
   xDirect=std::make_unique<QRadioButton>(tr("X Direction"));
   yDirect=std::make_unique<QRadioButton>(tr("Y Direction"));
   zDirect=std::make_unique<QRadioButton>(tr("Z Direction"));
   negXDirect=std::make_unique<QRadioButton>(tr("-X Direction"));
   negYDirect=std::make_unique<QRadioButton>(tr("-Y Direction"));
   negZDirect=std::make_unique<QRadioButton>(tr("-Z Direction"));
    axisX=std::make_unique<QRadioButton>(tr("X Direction"));
    axisY=std::make_unique<QRadioButton>(tr("Y Direction"));
    axisZ=std::make_unique<QRadioButton>(tr("Z Direction"));
    vlayout=std::make_unique<QVBoxLayout>();
    vlayout_1=std::make_unique<QVBoxLayout>();
    vlayout_2=std::make_unique<QVBoxLayout>();
    flayout=std::make_unique<QFormLayout>();
    vlayout->setAlignment(Qt::AlignTop| Qt::AlignLeft);
    vlayout_1->setAlignment(Qt::AlignTop| Qt::AlignLeft);
    vlayout_2->setAlignment(Qt::AlignTop| Qt::AlignLeft);
    flayout->addRow(tr("Radius:"),radiusEdit.get());
    flayout->addRow(tr("Angle:"),angleEdit.get());
    vlayout->addLayout(flayout.get());
    vlayout_1->addWidget(xDirect.get());
    vlayout_1->addWidget(yDirect.get());
    vlayout_1->addWidget(zDirect.get());
    vlayout_1->addWidget(negXDirect.get()); 
    vlayout_1->addWidget(negYDirect.get());  
    vlayout_1->addWidget(negZDirect.get());  
    vlayout_2->addWidget(axisX.get());
    vlayout_2->addWidget(axisY.get());
    vlayout_2->addWidget(axisZ.get());  
    axisSection->setContentLayout(*vlayout_1.get());
    rotateSection->setContentLayout(*vlayout_2.get());
    vlayout->addWidget(axisSection.get());
    vlayout->addWidget(rotateSection.get());
    dialogButtons=std::make_unique<QDialogButtonBox>(QDialogButtonBox::Ok|QDialogButtonBox::Cancel,nullptr);
    vlayout->addWidget(dialogButtons.get());
    setLayout(vlayout.get());
    setSizeGripEnabled(true);
    
    connect(radiusEdit.get(),&DoubleEdit::GetValue,this,&TransientCircleDialog::OnGetValue);
    connect(angleEdit.get(),&DoubleEdit::GetValue,this,&TransientCircleDialog::OnGetValue);
    connect(dialogButtons.get(),&QDialogButtonBox::rejected,this,&TransientCircleDialog::HandleCancel);
    connect(dialogButtons.get(),&QDialogButtonBox::accepted,this,&TransientCircleDialog::HandleOk);
    connect(xDirect.get(),&QRadioButton::toggled,this,&TransientCircleDialog::OnHandleChecked);
    connect(yDirect.get(),&QRadioButton::toggled,this,&TransientCircleDialog::OnHandleChecked);
    connect(zDirect.get(),&QRadioButton::toggled,this,&TransientCircleDialog::OnHandleChecked);
    connect(negXDirect.get(),&QRadioButton::toggled,this,&TransientCircleDialog::OnHandleChecked);
    connect(negYDirect.get(),&QRadioButton::toggled,this,&TransientCircleDialog::OnHandleChecked);
    connect(negZDirect.get(),&QRadioButton::toggled,this,&TransientCircleDialog::OnHandleChecked);
    connect(axisX.get(),&QRadioButton::toggled,this,&TransientCircleDialog::OnHandleChecked);
    connect(axisY.get(),&QRadioButton::toggled,this,&TransientCircleDialog::OnHandleChecked); 
   connect(axisZ.get(),&QRadioButton::toggled,this,&TransientCircleDialog::OnHandleChecked);
    return;
}
void SetContext(Handle(AIS_InteractiveContext) con){
    context=con;
    return;
}
gp_Ax2 AxisOfDraw() const{
    return axisOfDraw;
}
gp_Ax2 ChangedAxis() const{
    return changedAxis;
}
void SetPoint(const gp_Pnt& p){
    pnt=p;
    return;
}
float Radius() const{
    return radiusEdit->Result();
}
float Angle() const{
    return angleEdit->Result();
}

void GetRadAngle(double& val){
    val=Angle()*(pie/180.0f);
    return;
}

void OnDisplay(){
    if(!context){
        return;
    }
    
    if(radiusEdit->Result()<=0.0){
        return;
    }
    DetermineValue();
    float rad=angleEdit->Result()*(pie/180.0f);
    auto drawAxis=axisOfDraw;
    drawAxis.Rotate(axisOfRotation,rad);
    changedAxis=drawAxis;

    BRepBuilderAPI_MakeEdge edgeMaker;
    Handle(Geom_Circle) circle=new Geom_Circle(drawAxis,radiusEdit->Result());
    edgeMaker.Init(circle);
    if(!edgeMaker.IsDone()){
        return;
    }
    if(!circleShape){
        circleShape=new CustomAIS_Shape(edgeMaker.Edge());
        context->Display(circleShape,true);
        return;
    }
    circleShape->SetShape(edgeMaker.Edge());
    CheckDisplayStatus(circleShape,context->DisplayStatus(circleShape));
    context->UpdateCurrentViewer();
    
    return;
}

void DetermineValue(){
    if(xDirect->isChecked()){
       axisOfDraw=gp_Ax2(pnt,gp_Dir(1.0,0.0,0.0));
      }
      else if(yDirect->isChecked()){
        axisOfDraw=gp_Ax2(pnt,gp_Dir(0.0,1.0,0.0));
      }
      else if(zDirect->isChecked()){
         axisOfDraw=gp_Ax2(pnt,gp_Dir(0.0,0.0,1.0));
      }
      else if(negXDirect->isChecked()){
         axisOfDraw=gp_Ax2(pnt,gp_Dir(-1.0,0.0,0.0));
      }
     else if(negYDirect->isChecked()){
         axisOfDraw=gp_Ax2(pnt,gp_Dir(0.0,-1.0,0.0));
     }
    else if(negZDirect->isChecked()){
          axisOfDraw=gp_Ax2(pnt,gp_Dir(0.0,0.0,-1.0));
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
void NullifyShape(){
    if(circleShape){
        circleShape.Nullify();
    }
    return;
}
void EraseShape(){
    if(context->IsDisplayed(circleShape)){
        context->Erase(circleShape,true);
    }
    return;
}

public slots:
void HandleCancel(){
    if(circleShape){
        context->Erase(circleShape,true);
    }
    reject();
    return;
}
void HandleOk(){
    accept();
    return;
}
void OnGetValue(const float& val){
    OnDisplay();
    return;
}
void OnHandleChecked(bool value){
    OnDisplay();
    return;
}
};