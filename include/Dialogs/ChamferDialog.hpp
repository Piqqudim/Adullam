#pragma once
#include<QtWidgets/QDialog>
#include<QtWidgets/QDialogButtonBox>
#include<memory>
#include<QtWidgets/QFormLayout>
#include<QtWidgets/QPushButton>
#include<QtWidgets/QVBoxLayout>
#include<DoubleLineEdit.hpp>

using namespace std;
class ChamferDialog:public QDialog{
private:
Q_OBJECT
unique_ptr<QVBoxLayout> vlayout;
unique_ptr<QFormLayout> formlayout;
unique_ptr<DoubleEdit> angleEdit;
unique_ptr<DoubleEdit> distanceEdit;
unique_ptr<QDialogButtonBox> dialogButtons;
float angle=0.0f;
float distance=0.0f;

public:
ChamferDialog(QWidget* parent=nullptr):QDialog(parent){
setWindowTitle(tr("Chamfer Dialog"));
formlayout=make_unique<QFormLayout>();
vlayout=make_unique<QVBoxLayout>();
vlayout->setAlignment(Qt::AlignTop|Qt::AlignLeft);
angleEdit=make_unique<DoubleEdit>(this,QString::number(1.0),8); //8 d.p
distanceEdit=make_unique<DoubleEdit>(this,QString::number(0.0),8);
formlayout->addRow(tr("Angle:"),angleEdit.get());
formlayout->addRow(tr("Distance:"),distanceEdit.get());
vlayout->addLayout(formlayout.get());
dialogButtons=make_unique<QDialogButtonBox>(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
vlayout->addWidget(dialogButtons.get());
 setSizeGripEnabled(true);
setLayout(vlayout.get());
connect(dialogButtons.get(),&QDialogButtonBox::rejected,this,&QDialog::reject);
connect(dialogButtons.get(),&QDialogButtonBox::accepted,this,&QDialog::accept);
connect(angleEdit.get(),&DoubleEdit::GetValue,this,&ChamferDialog::OnRequestValue);
connect(distanceEdit.get(),&DoubleEdit::GetValue,this,&ChamferDialog::OnGetValueForDistance);
}
float Angle() const{
    return angle;
}
float Distance() const{
    return distance;
}

public slots:
void OnRequestValue(const float& val){
    angle=val;
    return;
}
void OnGetValueForDistance(const float& val){
    distance=val;
    return;
}


};