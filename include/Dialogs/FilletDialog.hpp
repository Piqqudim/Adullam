#pragma once
#include<QtWidgets/QDialog>
#include<QtWidgets/QDialogButtonBox>
#include<memory>
#include<QtWidgets/QFormLayout>
#include<QtWidgets/QPushButton>
#include<QtWidgets/QVBoxLayout>
#include<DoubleLineEdit.hpp>
using namespace std;
class FilletDialog:public QDialog{
private:
Q_OBJECT
unique_ptr<QVBoxLayout> vlayout;
unique_ptr<QFormLayout> formlayout;
unique_ptr<DoubleEdit> radiusEdit;
unique_ptr<QDialogButtonBox> dialogButtons;
float radius=0.0f;
public:
FilletDialog(QWidget* parent=nullptr):QDialog(parent){
setWindowTitle(tr("Fillet Dialog"));
formlayout=make_unique<QFormLayout>();
vlayout=make_unique<QVBoxLayout>();
vlayout->setAlignment(Qt::AlignTop|Qt::AlignLeft);
radiusEdit=make_unique<DoubleEdit>(this,QString::number(1.0),8); //8 d.p
formlayout->addRow(tr("Radius:"),radiusEdit.get());
vlayout->addLayout(formlayout.get());
dialogButtons=make_unique<QDialogButtonBox>(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
vlayout->addWidget(dialogButtons.get());
 setSizeGripEnabled(true);
setLayout(vlayout.get());
connect(dialogButtons.get(),&QDialogButtonBox::rejected,this,&QDialog::reject);
connect(dialogButtons.get(),&QDialogButtonBox::accepted,this,&QDialog::accept);
connect(radiusEdit.get(),&DoubleEdit::GetValue,this,&FilletDialog::OnRequestValue);

return;
}
float Radius() const{
    return radius;
}
public slots:
void OnRequestValue(const float& val){
    radius=val;
    return;
}
};