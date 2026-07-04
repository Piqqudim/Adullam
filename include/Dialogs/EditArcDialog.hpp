#pragma once 
#include<QtWidgets/QLabel>
#include<QtWidgets/QFormLayout>
#include<MyCustomAIS_Shape.hxx>
#include<QtWidgets/QDialog>
#include<GC_MakeArcOfCircle.hxx>
#include<Geom_Circle.hxx>
#include<DoubleLineEdit.hpp>
#include<AIS_InteractiveContext.hxx>
#include<BRepBuilderAPI_MakeEdge.hxx>
#include<memory>
#include<QtWidgets/QDialogButtonBox>
#include<QtWidgets/QVBoxLayout>
#include<gp_Circ.hxx>
#include<InfoUtility.hpp>
#include<TopoDS_Edge.hxx>
#include<ColorDialog.hpp>
using namespace INFO;
using namespace std;
class EditArcDialog:public QDialog{
private:
Q_OBJECT
unique_ptr<QFormLayout> flayout;
unique_ptr<DoubleEdit> U1edit;
unique_ptr<DoubleEdit> U2edit;
unique_ptr<DoubleEdit> radiusEdit;
unique_ptr<QDialogButtonBox> buttons;
unique_ptr<QLabel> prevU1Edit;
unique_ptr<QLabel> prevU2Edit;
unique_ptr<QLabel> prevRadius;

unique_ptr<ColorDialog> clrdialog;
unique_ptr<ColorPane> colorpane;
unique_ptr<QVBoxLayout> vlayout;
Handle(CustomAIS_Shape) circleShape;
Handle(CustomAIS_Shape) arcShape;
Handle(AIS_InteractiveContext) context;
Handle(Geom_Circle) circleCurve;
TopoDS_Edge edge;
float pi=3.141593;
public:
EditArcDialog(){
flayout=std::make_unique<QFormLayout>();
U1edit=make_unique<DoubleEdit>(nullptr,QString::number(0),8);
U2edit=make_unique<DoubleEdit>(nullptr,QString::number(0),8);
prevU1Edit=std::make_unique<QLabel>(QString::number(0));
prevU2Edit=std::make_unique<QLabel>(QString::number(0));
buttons=std::make_unique<QDialogButtonBox>(QDialogButtonBox::Ok|QDialogButtonBox::Cancel);
radiusEdit=std::make_unique<DoubleEdit>(nullptr,QString::number(0),8);
prevRadius=std::make_unique<QLabel>(QString::number(0));
clrdialog=std::make_unique<ColorDialog>();
colorpane=std::make_unique<ColorPane>();
vlayout=std::make_unique<QVBoxLayout>();
flayout->addRow(tr("Previous U1: "),prevU1Edit.get());
flayout->addRow(tr("Previous U2: "),prevU2Edit.get());
flayout->addRow(tr("Previous Radius:"),prevRadius.get());
flayout->addRow(tr("Current U1: "),U1edit.get());
flayout->addRow(tr("Current U2: "),U2edit.get());
flayout->addRow(tr("Current Radius:"),radiusEdit.get());
flayout->addRow(tr("Arc Color Pane:"),colorpane.get());
vlayout->addLayout(flayout.get());
vlayout->addWidget(buttons.get());
setLayout(vlayout.get());
connect(buttons.get(),&QDialogButtonBox::rejected,this,&EditArcDialog::HandleCancel);
connect(buttons.get(),&QDialogButtonBox::accepted,this,&EditArcDialog::HandleOk);
connect(U1edit.get(),&DoubleEdit::GetValue,this,&EditArcDialog::OnHandleUParam);
connect(U2edit.get(),&DoubleEdit::GetValue,this,&EditArcDialog::OnHandleUParam);
connect(colorpane.get(),&ColorPane::IsDoubleClicked,this,&EditArcDialog::OnHandleClick);
connect(clrdialog->ColorWidget(),&ColorCollectionWidget::GetSelectedColor,this,&EditArcDialog::OnHandleSelectedColor);
connect(radiusEdit.get(),&DoubleEdit::GetValue,this,&EditArcDialog::OnHandleUParam);

return;
}
void SetColor(const Quantity_Color& col){
    colorpane->SetColorFromOC(col);
    return;
}
float U1() const{
    return U1edit->Result();
}
float U2() const{
    return U2edit->Result();
}
void SetContext(Handle(AIS_InteractiveContext) con){
    context=con;
    return;
}
Handle(AIS_InteractiveContext) Context() const{
    return context;
}
void SetGeomCircle(const Handle(Geom_Circle)& circle){
    circleCurve=circle;
    return;
}
//val serves as U1,while val2 serves as U2
void SetPrevValues(const double& val,const double& val2){
    prevU1Edit->setText(QString::number(val));
    prevU2Edit->setText(QString::number(val2));
    return;
}
Handle(Geom_Circle) CircleCurve() const{
    return circleCurve;
}
void SetPrevRadius(const float& value){
    prevRadius->setText(QString::number(value));
    radiusEdit->setText(QString::number(value));
    return;
}
void OnDisplay(){
    if(circleCurve.IsNull()){
        return;
    }
    circleCurve->SetRadius((double)radiusEdit->Result());
     BRepBuilderAPI_MakeEdge edgemaker_1;
     edgemaker_1.Init(circleCurve);
     if(!edgemaker_1.IsDone()){
         return;
     }
     if(!circleShape){
        circleShape=new CustomAIS_Shape(edgemaker_1.Edge());
        circleShape->SetZLayer(Graphic3d_ZLayerId_Topmost);
        context->Display(circleShape,true);
        
     }
     else{
        circleShape->SetShape(edgemaker_1.Edge());
        CheckDisplayStatus(circleShape,context->DisplayStatus(circleShape));       
     } 
     double val1=(double)U1edit->Result();
     double val2=(double)U2edit->Result();
     if(val1==val2){
        LoadMessage(tr("U1 and U2 Values"),tr("They are equal,Select two seperate values"));
        return;
     }
     val1=(pi*val1)/180.0000;
     val2=(pi*val2)/180.0000;

     GC_MakeArcOfCircle arcmaker(circleCurve->Circ(),val1,val2,true);
     if(!arcmaker.Value()){
        LoadMessage(tr(""),tr("Failed to create an Arc"));
        return;
     }
     BRepBuilderAPI_MakeEdge edgemaker;
     edgemaker.Init(arcmaker.Value());
     if(!edgemaker.IsDone()){
        LoadMessage(tr(""),tr("Failed to Initialize an edge"));
        return;
     }
     edge=edgemaker.Edge();
     if(!arcShape){
        arcShape=new CustomAIS_Shape(edgemaker.Edge());
        arcShape->SetColor(clrdialog->GetColor());
        arcShape->SetZLayer(Graphic3d_ZLayerId_Topmost);
        context->Display(arcShape,true);
     }
     else{
        arcShape->SetShape(edgemaker.Edge());
        arcShape->SetColor(clrdialog->GetColor());
        CheckDisplayStatus(arcShape,context->DisplayStatus(arcShape));
        context->UpdateCurrentViewer();
     }
    return;
}
TopoDS_Edge GetEdge() const{
    return edge;
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
signals:
void EmitDone();


public slots:
void HandleOk(){
    if(circleShape){
        context->Erase(circleShape,false);
    }
    if(arcShape){
        context->Erase(arcShape,false);
    }
    context->UpdateCurrentViewer();
    emit EmitDone();
    accept();
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
void OnHandleUParam(const float& val){
    OnDisplay();
    return;
}
void OnHandleSelectedColor(){
    colorpane->SetColorFromOC(clrdialog->GetColor());
    OnDisplay();
    return;
}
void OnHandleClick(size_t ind){
    clrdialog->setWindowTitle(tr("Arc Color Dialog"));
    clrdialog->exec();
    return;
}
};