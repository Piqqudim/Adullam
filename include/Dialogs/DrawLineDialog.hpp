#pragma once
#include<QtWidgets/QDialog>
#include<memory>
#include<QtWidgets/QDialogButtonBox>
#include<QtWidgets/QVBoxLayout>
#include<Section.h>
#include<QtWidgets/QFormLayout>
#include<DoubleLineEdit.hpp>
#include<QtWidgets/QRadioButton>
#include<QtWidgets/QPushButton>
#include<MyCustomAIS_Shape.hxx>
#include<AIS_InteractiveContext.hxx>
#include<Geom_Line.hxx>
#include<gp_Dir.hxx>
#include<gp_Ax1.hxx>
#include<gp_Pnt.hxx>
#include<gp_Ax2.hxx>
#include<BRepBuilderAPI_MakeEdge.hxx>
#include<ColorPane.hpp>

#include<ColorDialog.hpp>
using namespace std;
class DrawLineDialog:public QDialog{
private:
Q_OBJECT
std::unique_ptr<QVBoxLayout> vlayout;
unique_ptr<QFormLayout> formLayout; //for length specification 
unique_ptr<QFormLayout> formLayout_1; //for relative angle specification
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
std::unique_ptr<ColorDialog> colorDialog;
std::unique_ptr<ColorPane> lineColorPane;
Handle(AIS_InteractiveContext) context;
Handle(CustomAIS_Shape) lineShape;
float pie;
QPushButton* okButton=nullptr;
float relativeAngle=0.0f; //specified in degrees,it has to be converted to radian
float length=0.0;  // length..
gp_Dir direction=gp_Dir(0.0,.0,1.0); // direction of draw
gp_Ax1 axisOfRotation; //axis of rotation;
gp_Ax2 faceAxis;
gp_Pnt pointOfRotation;
Quantity_Color output;
bool isFace=false; //by default,it is false.....
public:
DrawLineDialog(QWidget* parent=nullptr):QDialog(parent){
    pie=3.14159265;
    setWindowTitle(tr("Draw Line Dialog"));
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
    lineColorPane=make_unique<ColorPane>(nullptr);
    colorDialog=std::make_unique<ColorDialog>(nullptr);
    colorDialog->SetTitle(tr("Line Color Dialog"));
    formLayout->addRow(tr("Length:"),lengthEdit.get());
    formLayout->addRow(tr("Line Color:"),lineColorPane.get());
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
    dialogButtons=std::make_unique<QDialogButtonBox>(QDialogButtonBox::Cancel|QDialogButtonBox::Ok,nullptr);
    okButton=dialogButtons->button(QDialogButtonBox::Ok);
    if(okButton){
     connect(okButton,&QPushButton::clicked,this,&DrawLineDialog::OnHandleOk);      
    }
    connect(relativeAngleEdit.get(),&DoubleEdit::GetValue,this,&DrawLineDialog::OnGetValueFromRelativeAngleEdit);
    connect(lengthEdit.get(),&DoubleEdit::GetValue,this,&DrawLineDialog::OnGetValueFromLengthEdit);
    
    connect(lineColorPane.get(),&ColorPane::IsDoubleClicked,this,&DrawLineDialog::IsClicked);
    connect(colorDialog->ColorWidget(),&ColorCollectionWidget::GetSelectedColor,this,&DrawLineDialog::OnGetColor);
    connect(dialogButtons.get(),&QDialogButtonBox::rejected,this,&DrawLineDialog::OnHandleCancel);
    connect(xDirectButton.get(),&QRadioButton::toggled,this,&DrawLineDialog::isToggled);
    connect(yDirectButton.get(),&QRadioButton::toggled,this,&DrawLineDialog::isToggled);
    connect(zDirectButton.get(),&QRadioButton::toggled,this,&DrawLineDialog::isToggled);
    connect(inXButton.get(),&QRadioButton::toggled,this,&DrawLineDialog::isToggled);
    connect(inYButton.get(),&QRadioButton::toggled,this,&DrawLineDialog::isToggled);
    connect(inZButton.get(),&QRadioButton::toggled,this,&DrawLineDialog::isToggled);
    connect(negInXButton.get(),&QRadioButton::toggled,this,&DrawLineDialog::isToggled);
    connect(negInYButton.get(),&QRadioButton::toggled,this,&DrawLineDialog::isToggled);
    connect(negInZButton.get(),&QRadioButton::toggled,this,&DrawLineDialog::isToggled);
    vlayout->addWidget(dialogButtons.get());
    setLayout(vlayout.get());
    setSizeGripEnabled(true);
    return;
}
void SetPointOfRotation(const gp_Pnt& pnt){
    pointOfRotation=pnt;
    return;
}


void SetContext(Handle(AIS_InteractiveContext) con){
    context=con;
    return;
}
Quantity_Color OutputColor() const{
    return output;
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
void OnDisplay(){
    if(!context){
        return;
    }
    
    if(Length()==0.0){
        return;
    }
    DetermineValue();
    float ang=Angle()*(pie/180.0f);
    auto dir=Direction();
    auto axis=Axis();
    dir.Rotate(axis,ang);
    BRepBuilderAPI_MakeEdge edgeMaker;
    Handle(Geom_Line) line=new Geom_Line(pointOfRotation,dir);
    edgeMaker.Init(line,0,Length());
    if(!edgeMaker.IsDone()){
        return;
    }
    if(lineShape.IsNull()){
      lineShape=new CustomAIS_Shape(edgeMaker.Edge());
      lineShape->SetColor(output);
      context->Display(lineShape,true);
      return;
    }
   lineShape->SetColor(output);
   lineShape->SetShape(edgeMaker.Edge());
   CheckDisplayStatus(lineShape,context->DisplayStatus(lineShape));
   context->UpdateCurrentViewer(); 
    return; 
}
gp_Dir Direction() const{
    return direction;
}

float Angle() const{
    return relativeAngle;
}
float Length() const{
    return length;
}
gp_Ax1 Axis() const{
    return axisOfRotation;
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
signals:
void OnEmitDone();
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
    //this gets the relative angles,length,axis of rotation
   DetermineValue();
    emit OnEmitDone();
    if(lineShape){
    context->Erase(lineShape,true);
    }
    accept();
    return;
}
void IsClicked(const size_t& index){
    colorDialog->exec();
    return;
}
void OnGetColor(){
    output=colorDialog->ColorWidget()->GetChosenColor();
    lineColorPane->SetColorFromOC(output);
    OnDisplay();
    return;
}
void OnGetValueFromLengthEdit(const float& value){
    length=value;
    OnDisplay();
    return;
}
void OnGetValueFromRelativeAngleEdit(const float& value){
    relativeAngle=value;
    OnDisplay();
    return;
}
};





