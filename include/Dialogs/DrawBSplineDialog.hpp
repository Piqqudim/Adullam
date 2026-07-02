#pragma once
#include<DrawLineDialog.hpp>
#include<QtWidgets/QColorDialog>
#include<vector>
#include<Geom_BSplineCurve.hxx>
#include<GeomAPI_PointsToBSpline.hxx>
#include<NCollection_Array1.hxx>
#include<BRepBuilderAPI_MakeEdge.hxx>
#include<MyCustomAIS_Shape.hxx>
#include<PrsMgr_DisplayStatus.hxx>
#include<iostream>
using namespace std;
class DrawBSplineDialog:public QDialog{
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


QPushButton* okButton=nullptr;
float relativeAngle=0.0f; //specified in degrees,it has to be converted to radian
float length=0.0;  // length..
gp_Dir direction; // direction of draw
gp_Ax1 axisOfRotation; //axis of rotation;
gp_Pnt pointOfRotation;
gp_Pnt nextPoint;
gp_Pnt startPoint;
Handle(CustomAIS_Shape) bsplineShape;
Handle(CustomAIS_Shape) lineShape;
Handle(AIS_InteractiveContext) context;
bool isNextPoint=false;
bool isClosed=false;


public:
std::vector<gp_Pnt> points;
DrawBSplineDialog(QWidget* parent=nullptr):QDialog(parent){
    setWindowTitle(tr("Draw BSpline Dialog"));
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
    dialogButtons=std::make_unique<QDialogButtonBox>(QDialogButtonBox::Cancel|QDialogButtonBox::Ok,nullptr);
    okButton=dialogButtons->button(QDialogButtonBox::Ok);
    if(okButton){
     connect(okButton,&QPushButton::clicked,this,&DrawBSplineDialog::OnHandleOk);      
    }
    
    connect(relativeAngleEdit.get(),&DoubleEdit::GetValue,this,&DrawBSplineDialog::OnGetValueFromRelativeAngleEdit);
    connect(lengthEdit.get(),&DoubleEdit::GetValue,this,&DrawBSplineDialog::OnGetValueFromLengthEdit);
    

    connect(dialogButtons.get(),&QDialogButtonBox::rejected,this,&DrawBSplineDialog::OnHandleCancel);
    vlayout->addWidget(dialogButtons.get());
    setLayout(vlayout.get());
    setSizeGripEnabled(true);
    connect(xDirectButton.get(),&QRadioButton::toggled,this,&DrawBSplineDialog::IsClicked);
    connect(yDirectButton.get(),&QRadioButton::toggled,this,&DrawBSplineDialog::IsClicked);
   connect(zDirectButton.get(),&QRadioButton::toggled,this,&DrawBSplineDialog::IsClicked);
   connect(inXButton.get(),&QRadioButton::toggled,this,&DrawBSplineDialog::IsClicked);
   connect(inYButton.get(),&QRadioButton::toggled,this,&DrawBSplineDialog::IsClicked);
     connect(inZButton.get(),&QRadioButton::toggled,this,&DrawBSplineDialog::IsClicked);
    connect(negInXButton.get(),&QRadioButton::toggled,this,&DrawBSplineDialog::IsClicked);
    connect(negInYButton.get(),&QRadioButton::toggled,this,&DrawBSplineDialog::IsClicked);
    
    connect(negInZButton.get(),&QRadioButton::toggled,this,&DrawBSplineDialog::IsClicked);
    return;
}
void SetPointOfRotation(const gp_Pnt& pnt){
    startPoint=pnt;
    pointOfRotation=pnt;
    nextPoint=pnt;
    return;
}
void OnDisplay(){
     const float pie=3.14159265;
   DetermiveValues(); 
  gp_Ax1 axis=Axis();
  float ang=Angle();
  gp_Dir dir=Direction();
  float val=Length();

  if(ang>=0.1 && ang<=0.999999999){
    LoadMessage(tr(""),tr("Angle is not greater or equal to 1.0"));
    return;
  }
  if(val==0.000){
    LoadMessage(tr(""),tr("No Length is set"));
    return;
  }

  float convertedAngle=ang*(pie/180.0f);
  dir.Rotate(axis,convertedAngle);
  Handle(Geom_Line) line=new Geom_Line(NextPoint(),dir);
std::vector<gp_Pnt> pnts;
 for(int i=0;i<points.size();i++){
    pnts.emplace_back(points.at(i).X(),points.at(i).Y(),points.at(i).Z());
 }

 if(pnts.size()==0){
    cout<<"Points are empty"<<"\n";
 }
 gp_Pnt prevPoint=pnts.at(pnts.size()-1);
  gp_Pnt refpoint;
  
  line->D0((double)val,refpoint);
  
  pnts.push_back(refpoint);
  if(pnts.size()<=3){
    return;
  }
  if(pnts.size()>Geom_BSplineCurve::MaxDegree()+1){
    return;
  }
  NCollection_Array1<gp_Pnt> arrayOfPoints(pnts.front(),0,pnts.size()-1);
  GeomAPI_PointsToBSpline bsplineimpl;
  bsplineimpl.Init(arrayOfPoints); //
  if(!bsplineimpl.IsDone()){
    return;
  }
  BRepBuilderAPI_MakeEdge edgemaker;
  edgemaker.Init(bsplineimpl.Curve());
  if(!edgemaker.IsDone()){
    std::cout<<"Failed to initialize edge maker from bezier curve"<<"\n";
    return;
  }
  BRepBuilderAPI_MakeEdge edgemaker_1(prevPoint,refpoint);
  if(!edgemaker_1.IsDone()){
    std::cout<<"Failed to initialize edge from point"<<"\n";
     return;
     
  }
  else{
  if(!lineShape){
    lineShape=new CustomAIS_Shape(edgemaker_1.Edge());
    lineShape->SetColor(Quantity_NOC_ALICEBLUE);
    lineShape->SetZLayer(Graphic3d_ZLayerId_Topmost);
    context->Display(lineShape,true);
    }
  else{
     lineShape->Set(edgemaker_1.Edge());
     CheckDisplayStatus(lineShape,context->DisplayStatus(lineShape));
  }
  }
  if(!bsplineShape){
    bsplineShape=new CustomAIS_Shape(edgemaker.Edge());
    bsplineShape->SetZLayer(Graphic3d_ZLayerId_Topmost);
    bsplineShape->SetColor(Quantity_NOC_AQUAMARINE2);
    context->Display(bsplineShape,true);
    return;
  }
  
  bsplineShape->SetShape(edgemaker.Edge());
  CheckDisplayStatus(bsplineShape,context->DisplayStatus(bsplineShape));
  return;
}
std::vector<gp_Pnt> Points() const{
    return points;
}
std::vector<gp_Pnt>& GetPoints(){
    return points;
}
gp_Pnt PointOfRotation() const{
    return pointOfRotation;
}
gp_Pnt NextPoint() const{
    return nextPoint;
}

gp_Pnt StartPoint() const{
    return startPoint;
}

void SetNextPoint(const gp_Pnt& pnt){
    nextPoint=pnt;
    return;
}
void SetIsClosed(bool value){
   isClosed=value;
   
 return;
}
void SetContext(Handle(AIS_InteractiveContext) con){
    context=con;
    return;
}
void CheckDisplayStatus(Handle(AIS_InteractiveObject) obj,const PrsMgr_DisplayStatus& status){
    switch(status){
     case PrsMgr_DisplayStatus_Displayed:{
       context->Redisplay(obj,true);
       break;
     }
     case PrsMgr_DisplayStatus_Erased:{
        context->Display(obj,true);
        break;
     }
    }
    return;
}

void DetermiveValues(){
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

void SetNextPointOfRotation(){
    if(isNextPoint){
    pointOfRotation=nextPoint;
    }
    return;
}
void SetIsNextPoint(bool value){
    isNextPoint=value;
    return;
}

bool IsNextPoint() const{
    return isNextPoint;
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
void SetToDefault(){
    SetIsNextPoint(false);
    SetPointOfRotation(gp_Pnt());
    SetNextPoint(gp_Pnt());
    if(!points.empty()){
        points.clear();
    }
    
    return;
}
signals:
void OnBSplineDone();
public slots:
void IsClicked(bool value){
    OnDisplay();
    return;
}
void OnHandleCancel(){
    if(context->IsDisplayed(bsplineShape)){
        context->Erase(bsplineShape,true);
    }
    if(context->IsDisplayed(lineShape)){
        context->Erase(lineShape,true);
    }
    reject();
    return;
}
void OnHandleOk(){
    //this gets the relative angles,length,axis of rotation
    DetermiveValues();
    if(context->IsDisplayed(bsplineShape)){
        context->Erase(bsplineShape,true);
    }
    if(context->IsDisplayed(lineShape)){
        context->Erase(lineShape,true);
    }
    emit OnBSplineDone();

    accept();
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