#pragma once
#include<DrawLineDialog.hpp>
#include<QtWidgets/QColorDialog>
class DrawPolygonDialog:public QDialog{
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

bool isNextPoint=false;
bool isClosed=false;
bool isConvertedToWire=false;
bool isConvertedToFace=false;

public:
DrawPolygonDialog(QWidget* parent=nullptr):QDialog(parent){
    setWindowTitle(tr("Draw Polygon Dialog"));
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
     connect(okButton,&QPushButton::clicked,this,&DrawPolygonDialog::OnHandleOk);      
    }
    connect(relativeAngleEdit.get(),&DoubleEdit::GetValue,this,&DrawPolygonDialog:: OnGetValueFromRelativeAngleEdit);
    connect(lengthEdit.get(),&DoubleEdit::GetValue,this,&DrawPolygonDialog::OnGetValueFromLengthEdit);
    

    connect(dialogButtons.get(),&QDialogButtonBox::rejected,this,&QDialog::reject);
    vlayout->addWidget(dialogButtons.get());
    setLayout(vlayout.get());
    setSizeGripEnabled(true);
}
void SetPointOfRotation(const gp_Pnt& pnt){
    startPoint=pnt;
    pointOfRotation=pnt;
    nextPoint=pnt;
    return;
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
void SetIsConvertedToWire(bool value){
    isConvertedToWire=value;
    return;
}
void SetIsConvertedToFace(bool value){
    isConvertedToFace=value;
    return;
}
bool IsConvertedToFace() const{
    return isConvertedToFace;
}
bool IsConvertedToWire() const{
    return isConvertedToWire;
}
bool IsClosed() const{
    return isClosed;
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
    SetIsClosed(false);
    SetIsConvertedToWire(false);
    SetIsConvertedToFace(false);
    return;
}
signals:
void OnPolygonDone();
public slots:
void OnHandleOk(){
    //this gets the relative angles,length,axis of rotation
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
    emit OnPolygonDone();
    accept();
    return;
}
void OnGetValueFromLengthEdit(const float& value){
    length=value;
    return;
}
void OnGetValueFromRelativeAngleEdit(const float& value){
    relativeAngle=value;
    return;
}
};