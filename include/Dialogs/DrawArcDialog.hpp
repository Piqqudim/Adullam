#pragma once
#include<BRepBuilderAPI_MakeEdge.hxx>
#include<MyCustomAIS_Shape.hxx>
#include<gp_Ax2.hxx>
#include<gp_Pnt.hxx>
#include<AIS_InteractiveContext.hxx>
#include<Geom_Circle.hxx>
#include<GC_MakeArcOfCircle.hxx>
#include<MyCustomAIS_Shape.hxx>
#include<Section.h>
#include<QtWidgets/QFormLayout>
#include<InfoUtility.hpp>
#include<QtWidgets/QDialog>
#include<QtWidgets/QVBoxLayout>
#include<QtWidgets/QDialogButtonBox>
#include<DoubleLineEdit.hpp>
#include<QtWidgets/QCheckBox>
#include<QtWidgets/QRadioButton>
#include<ColorDialog.hpp>
#include<gp_Circ.hxx>
#include<memory>
using namespace std;
using namespace INFO;
//Draw An Arc such that the arc is a part of the circle
class DrawArcDialog:public QDialog{
private:
Q_OBJECT
Handle(CustomAIS_Shape) circleShape;
Handle(CustomAIS_Shape) arcShape;
std::unique_ptr<DoubleEdit> radiusEdit;
std::unique_ptr<DoubleEdit> angleEdit;
std::unique_ptr<DoubleEdit> arcU1ParamEdit;
std::unique_ptr<DoubleEdit> arcU2ParamEdit;
std::unique_ptr<Section> axisSection;
std::unique_ptr<Section> rotateSection;
std::unique_ptr<QCheckBox> useFaceAxis;
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
std::unique_ptr<ColorPane> circColorPane=std::make_unique<ColorPane>();
std::unique_ptr<ColorPane> arcColorPane=std::make_unique<ColorPane>();
std::unique_ptr<ColorDialog> colorDialog=std::make_unique<ColorDialog>(nullptr);
Handle(AIS_InteractiveContext) context;
bool isSetArc=false;
bool isSetCircle=false;
Handle(Geom_Circle) circle;
gp_Ax1 axisOfRotation;
gp_Ax2 faceAxis;
gp_Ax2 axisOfDraw; //if useFaceAxis is chosen
gp_Pnt pnt;
float radius=0.0f;
float angle=0.0f;
float U1=0.0;
float U2=0.0;
float pie;
bool valueIsSet=false;
Quantity_Color arcColor;
Quantity_Color circColor;
public:
DrawArcDialog():QDialog(){
    setWindowTitle(tr("Arc Dialog"));
    pie=3.14159265;
   radiusEdit=std::make_unique<DoubleEdit>(this,QString::number(0.0),8);
   angleEdit=std::make_unique<DoubleEdit>(this,QString::number(0.0),8);
   arcU1ParamEdit=std::make_unique<DoubleEdit>(this,QString::number(0.0),8); //no starting angle
   arcU2ParamEdit=std::make_unique<DoubleEdit>(this,QString::number(0.0),8);
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
    useFaceAxis=std::make_unique<QCheckBox>(tr(""));
    vlayout_1=std::make_unique<QVBoxLayout>();
    vlayout_2=std::make_unique<QVBoxLayout>();
    flayout=std::make_unique<QFormLayout>();
    vlayout->setAlignment(Qt::AlignTop| Qt::AlignLeft);
    vlayout_1->setAlignment(Qt::AlignTop| Qt::AlignLeft);
    vlayout_2->setAlignment(Qt::AlignTop| Qt::AlignLeft);
    flayout->addRow(tr("Radius:"),radiusEdit.get());
    flayout->addRow(tr("Angle:"),angleEdit.get());
    flayout->addRow(tr("Arc U1"),arcU1ParamEdit.get());
    flayout->addRow(tr("Arc U2"),arcU2ParamEdit.get());
    flayout->addRow(tr("Use Face Axis "),useFaceAxis.get());
    flayout->addRow(tr("Arc Color Pane:"),arcColorPane.get());
    flayout->addRow(tr("Circle Color Pane"),circColorPane.get());
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
    connect(radiusEdit.get(),&DoubleEdit::GetValue,this,&DrawArcDialog::OnGetRadius);
    connect(angleEdit.get(),&DoubleEdit::GetValue,this,&DrawArcDialog::OnGetAngle);
    connect(dialogButtons.get(),&QDialogButtonBox::rejected,this,&DrawArcDialog::HandleCancel);
    connect(dialogButtons.get(),&QDialogButtonBox::accepted,this,&DrawArcDialog::HandleOk);
    connect(xDirect.get(),&QRadioButton::toggled,this,&DrawArcDialog::OnHandleChecked);
    connect(yDirect.get(),&QRadioButton::toggled,this,&DrawArcDialog::OnHandleChecked);
    connect(zDirect.get(),&QRadioButton::toggled,this,&DrawArcDialog::OnHandleChecked);
    connect(negXDirect.get(),&QRadioButton::toggled,this,&DrawArcDialog::OnHandleChecked);
    connect(negYDirect.get(),&QRadioButton::toggled,this,&DrawArcDialog::OnHandleChecked);
    connect(negZDirect.get(),&QRadioButton::toggled,this,&DrawArcDialog::OnHandleChecked);
    connect(axisX.get(),&QRadioButton::toggled,this,&DrawArcDialog::OnHandleChecked);
    connect(axisY.get(),&QRadioButton::toggled,this,&DrawArcDialog::OnHandleChecked); 
   connect(axisZ.get(),&QRadioButton::toggled,this,&DrawArcDialog::OnHandleChecked);
   connect(arcU1ParamEdit.get(),&DoubleEdit::GetValue,this,&DrawArcDialog::OnGetU1);
   connect(arcU2ParamEdit.get(),&DoubleEdit::GetValue,this,&DrawArcDialog::OnGetU2);
   connect(arcColorPane.get(),&ColorPane::IsDoubleClicked,this,&DrawArcDialog::DoubleClickForArc);
   connect(circColorPane.get(),&ColorPane::IsDoubleClicked,this,&DrawArcDialog::DoubleClick);
   connect(colorDialog->ColorWidget(),&ColorCollectionWidget::GetSelectedColor,this,&DrawArcDialog::OnGetColor);
    return;
}
void SetContext(Handle(AIS_InteractiveContext) con){
    context=con;
    return;
}
Quantity_Color ArcColor(){
  return arcColor;

}
void SetFaceAxis(const gp_Ax2& axis,const gp_Pnt& p){
    faceAxis=axis;
    pnt=p;
    return;
}
float GetU1()const{
    return U1;
}
float GetU2() const{
   return U2;
}
gp_Pnt GetPoint() const{
    return pnt;
}
gp_Ax2 AxisOfDraw() const{
    return axisOfDraw;
}
gp_Ax1 rotateAxis() const{
    return axisOfRotation;
}
float Radius() const{
    return radius;
}
float Angle() const{
    return angle;
}
Handle(Geom_Circle) Circle() const{
    return circle;
}
void SetPoint(const gp_Pnt& p){
    pnt=p;
    return;
}
void OnDisplay(){
    if(!context){
        return;
    }
     DetermineValue();
    if(angle>=0.0000 && angle<=0.99999){
        return;
    }
    if(radius<=0.0){
        return;
    }
    
   
    if(valueIsSet==false){
    LoadMessage(tr(""),tr("All values are not set"));
        return;
    } 
    float rad=angle*(pie/180.0f);
    auto drawAxis=axisOfDraw;
    drawAxis.Rotate(axisOfRotation,rad);
    
     BRepBuilderAPI_MakeEdge edgeMaker;
    if(!circle){
     circle=new Geom_Circle(drawAxis,radius);
     }
     else{
      gp_Circ circ(drawAxis,radius);
      circle->SetCirc(circ);
     }
     
     
     edgeMaker.Init(circle);
     if(!edgeMaker.IsDone()){
        LoadMessage(tr(""),tr("Failed To Create Circle"));
        return;
     }
     if(circleShape.IsNull()){
        circleShape=new CustomAIS_Shape(edgeMaker.Edge());
        circleShape->SetColor(circColor);
        context->Display(circleShape,true);
        
     }
     else{
     circleShape->SetShape(edgeMaker.Edge());
      circleShape->SetColor(circColor);
    CheckDisplayStatus(circleShape,context->DisplayStatus(circleShape));
    context->UpdateCurrentViewer();
     }
     if(U1==U2){
        return;
     }
     float rad1=U1*(pie/180.0f);
     float rad2=U2*(pie/180.0f);

     GC_MakeArcOfCircle arcmaker(circle->Circ(),rad1,rad2,true);
     if(!arcmaker.Value()){
        LoadMessage(tr(""),tr("Failed To Create Arc"));
        return;
     }
     edgeMaker.Init(arcmaker.Value());
     if(!edgeMaker.IsDone()){
      LoadMessage(tr(""),tr("Failed to initialize edge of an arc"));
      return;
     }
     if(!arcShape){
        arcShape=new CustomAIS_Shape(edgeMaker.Edge());
        arcShape->SetZLayer(Graphic3d_ZLayerId_Topmost);
        arcShape->SetColor(arcColor);
        context->Display(arcShape,true);
        return;
     }
     else{
        arcShape->SetShape(edgeMaker.Edge());
        arcShape->SetColor(arcColor);
        CheckDisplayStatus(arcShape,context->DisplayStatus(arcShape));
        context->UpdateCurrentViewer();
     }
    return;
}
void DetermineValue(){
    if(useFaceAxis->isChecked()){
      if(xDirect->isChecked()){
       axisOfDraw=gp_Ax2(pnt,faceAxis.XDirection());
      }
      else if(yDirect->isChecked()){
        axisOfDraw=gp_Ax2(pnt,faceAxis.YDirection());
      }
      else if(zDirect->isChecked()){
        axisOfDraw=gp_Ax2(pnt,faceAxis.Direction());
      }
      else if(negXDirect->isChecked()){
        axisOfDraw=gp_Ax2(pnt,gp_Dir(-faceAxis.XDirection().X(),-faceAxis.XDirection().Y(),-faceAxis.XDirection().Z()));
      }
     else if(negYDirect->isChecked()){
         axisOfDraw=gp_Ax2(pnt,gp_Dir(-faceAxis.YDirection().X(),-faceAxis.YDirection().Y(),-faceAxis.YDirection().Z()));
     }
    else if(negZDirect->isChecked()){
         axisOfDraw=gp_Ax2(pnt,gp_Dir(-faceAxis.Direction().X(),-faceAxis.Direction().Y(),-faceAxis.Direction().Z()));
    }
   
    }
    else{
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
    valueIsSet=true;
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


signals:
void Done();


public slots:
void DoubleClick(const int val){
  isSetArc=false;
  isSetCircle=true;
  colorDialog->SetTitle(tr("Circle Color Dialog"));
  colorDialog->exec();
 return;
}
void DoubleClickForArc(const int val){
  isSetArc=true;
  isSetCircle=false;
  colorDialog->SetTitle(tr("Arc Color Dialog"));
  colorDialog->exec();
return;
}
void OnGetColor(){
if(isSetCircle){
circColor=colorDialog->ColorWidget()->GetChosenColor();
circColorPane->SetColorFromOC(circColor);

OnDisplay();
return;
}
if(isSetArc){
    OnGetColorForArc();
}

return;
}
void OnGetColorForArc(){
arcColor=colorDialog->ColorWidget()->GetChosenColor();
arcColorPane->SetColorFromOC(arcColor);
OnDisplay();
return;
}

void HandleCancel(){
    if(circleShape){
        context->Erase(circleShape,false);
    }
    if(arcShape){
      context->Erase(arcShape,false);

    }
    context->UpdateCurrentViewer();
    reject();
    return;
}
void HandleOk(){
    DetermineValue();
     if(circleShape){
        context->Erase(circleShape,false);
    }
    if(arcShape){
        context->Erase(arcShape,false);
    }
    context->UpdateCurrentViewer();
    accept();
    emit Done();
    return;
}
void OnGetRadius(const float& val){
    if(val<=0.0){
        return;
    }
    radius=val;
    OnDisplay();
    return;
}
void OnGetAngle(const float& ang){
    if(ang>=0.0 && ang<=0.999999){
        return;
    }
    angle=ang;
    OnDisplay();
    return;
}
void OnGetU1(const float& val){
   U1=val;
   OnDisplay();
   return;
}
void OnGetU2(const float& val){
    U2=val;
    OnDisplay();
    return;
}
void OnHandleChecked(bool value){
    OnDisplay();
    return;
}
};






