#pragma once
#include<FaceSection.hpp>
#include<QtWidgets/QDialog>
#include<memory>
#include<QtWidgets/QDialogButtonBox>
#include<QtWidgets/QVBoxLayout>
#include<DoubleLineEdit.hpp>
#include<QtWidgets/QFormLayout>
#include<AIS_InteractiveContext.hxx>
#include<MyCustomAIS_Shape.hxx>
#include<BRepBuilderAPI_MakeEdge.hxx>
#include<Geom_Line.hxx>
#include<ColorDialog.hpp>
#include<ColorPane.hpp>
#include<gp_Ax2.hxx>
#include<gp_Pnt.hxx>
#include<gp_Dir.hxx>
#include<gp_Ax1.hxx>
class FaceLineDialog:public QDialog{
private:
Q_OBJECT
std::unique_ptr<DoubleEdit> angleEdit;
std::unique_ptr<DoubleEdit> lengthEdit;
std::unique_ptr<QFormLayout> flayout;
unique_ptr<FaceDirectionOfDrawSection> faceSection;
unique_ptr<FaceDirectionOfRotationSection> rotateSection;
unique_ptr<QDialogButtonBox> buttons;
unique_ptr<QVBoxLayout> vlayout;
Handle(AIS_InteractiveContext) context;
Handle(CustomAIS_Shape) lineShape;
std::unique_ptr<ColorDialog> colorDialog;
std::unique_ptr<ColorPane> lineColorPane;
Quantity_Color output;
gp_Ax2 faceAxis;
gp_Dir direction;
gp_Ax1 axis;
gp_Pnt poi;
float ang=0.0f;
float len=0.0f;
float pie;
public:
FaceLineDialog(QWidget* parent=nullptr):QDialog(parent){
setWindowTitle(tr("Face Line Dialog"));
vlayout=std::make_unique<QVBoxLayout>();
  pie=3.14159265;
flayout=std::make_unique<QFormLayout>();
colorDialog=make_unique<ColorDialog>();
lineColorPane=make_unique<ColorPane>(nullptr);
vlayout->setAlignment(Qt::AlignTop|Qt::AlignLeft);
angleEdit=make_unique<DoubleEdit>(nullptr,QString::number(0.0),8);
lengthEdit=make_unique<DoubleEdit>(nullptr,QString::number(0.0),8);
faceSection=make_unique<FaceDirectionOfDrawSection>();
rotateSection=make_unique<FaceDirectionOfRotationSection>();
buttons=make_unique<QDialogButtonBox>(QDialogButtonBox::Ok|QDialogButtonBox::Cancel,nullptr);
flayout->addRow(tr("Angle"),angleEdit.get());
flayout->addRow(tr("Length"),lengthEdit.get());
flayout->addRow(tr("Line Color"),lineColorPane.get());
vlayout->addLayout(flayout.get());
vlayout->addWidget(faceSection.get());
vlayout->addWidget(rotateSection.get());
vlayout->addWidget(buttons.get());
setLayout(vlayout.get());
connect(buttons.get(),&QDialogButtonBox::rejected,this,&FaceLineDialog::OnHandleCancel);
connect(buttons.get(),&QDialogButtonBox::accepted,this,&FaceLineDialog::OnHandleOk);
connect(angleEdit.get(),&DoubleEdit::GetValue,this,&FaceLineDialog::OnGetValue);
connect(lengthEdit.get(),&DoubleEdit::GetValue,this,&FaceLineDialog::OnGetValueForLength);
connect(lineColorPane.get(),&ColorPane::IsDoubleClicked,this,&FaceLineDialog::IsClicked);
connect(colorDialog->ColorWidget(),&ColorCollectionWidget::GetSelectedColor,this,&FaceLineDialog::OnGetColor);
return;
}
void SetContext(Handle(AIS_InteractiveContext) con){
    context=con;
    return;
}
void InitAxis(const gp_Pnt& pnt,const gp_Dir& dir){
    faceAxis=gp_Ax2(pnt,dir);
    poi=pnt;
    return;
}
gp_Ax2 FaceAxis() const{
    return faceAxis;
}
gp_Ax1 Axis() const{
    return axis;
}
gp_Pnt PointOfInterest() const{
    return poi;
}
gp_Dir Direction() const{
    return direction;
}
float Length() const{
    return len;
}
float Angle() const{
    return ang;
}
Quantity_Color outputColor() const{
    return output;
}
void OnDisplay(){
     if(!context){
        return;
    }
    if(Angle()>=0 && Angle()<=0.99){
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
    TopoDS_Edge edge;
    BRepBuilderAPI_MakeEdge edgeMaker;
    Handle(Geom_Line) line=new Geom_Line(poi,dir);
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
void DetermineValue(){
    if(faceSection->faceNormalButton->isChecked()){
        direction=faceAxis.Direction();
    }
    if(faceSection->faceXButton->isChecked()){
        direction=faceAxis.XDirection();
    }
    if(faceSection->faceYButton->isChecked()){
        direction=faceAxis.YDirection();
    }
    if(faceSection->negFaceNormalButton->isChecked()){
        direction=gp_Dir(-faceAxis.Direction().X(),-faceAxis.Direction().Y(),-faceAxis.Direction().Z());
    }
    if(faceSection->negFaceXButton->isChecked()){
        direction=gp_Dir(-faceAxis.XDirection().X(),-faceAxis.XDirection().Y(),-faceAxis.XDirection().Z());
    }
    if(faceSection->negFaceYButton->isChecked()){
        direction=gp_Dir(-faceAxis.YDirection().X(),-faceAxis.YDirection().Y(),-faceAxis.YDirection().Z());
    }
    if(rotateSection->xRotate->isChecked()){
        axis=gp_Ax1(poi,faceAxis.XDirection());
    }
    if(rotateSection->yRotate->isChecked()){
        axis=gp_Ax1(poi,faceAxis.YDirection());
    }
    if(rotateSection->zRotate->isChecked()){
        axis=gp_Ax1(poi,faceAxis.Direction());
    }
    return;
}
signals:
void Done();


public slots:
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
void OnHandleCancel(){
    if(lineShape){
        context->Erase(lineShape,true);
    }
    reject();
    return;
}
void OnHandleOk(){
    DetermineValue();
    accept();
    emit Done();
     if(lineShape){
        context->Erase(lineShape,true);
    }
    return;
}
void OnGetValue(const float& val){
    //for angle
    if(val>=0.1 && val<=0.99999999){
        return;
    }
    ang=val;
    OnDisplay();
    return;
}
void OnGetValueForLength(const float& val){
    if(val==0.000){
        return;
    }
    //for length
    len=val;
    OnDisplay();
    return;
}
};


