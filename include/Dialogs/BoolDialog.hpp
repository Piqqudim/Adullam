#pragma once 
#include<QtWidgets/QDialog>
#include<QtWidgets/QDialogButtonBox>
#include<QtWidgets/QFormLayout>
#include<memory>
#include<QtWidgets/QCheckBox>
#include<QtWidgets/QVBoxLayout>
using namespace std;
class BoolDialog:public QDialog{
private:
Q_OBJECT
std::unique_ptr<QCheckBox> checkbox=std::make_unique<QCheckBox>(tr(""));
std::unique_ptr<QFormLayout> flayout=std::make_unique<QFormLayout>();
std::unique_ptr<QDialogButtonBox> buttons=std::make_unique<QDialogButtonBox>(QDialogButtonBox::Ok|QDialogButtonBox::Cancel,nullptr);
std::unique_ptr<QVBoxLayout> vlayout=std::make_unique<QVBoxLayout>();
bool value=false;
public:
BoolDialog():QDialog(){
 setWindowTitle(tr("Bool Dialog"));
 flayout->addRow(tr("Value"),checkbox.get());
 vlayout->addLayout(flayout.get());
 vlayout->addWidget(buttons.get());
 connect(buttons.get(),&QDialogButtonBox::rejected,this,&BoolDialog::reject);
 connect(buttons.get(),&QDialogButtonBox::accepted,this,&BoolDialog::OnHandleOk);
 setLayout(vlayout.get());
}
void SetValue(bool val){
    checkbox->setChecked(val);
    return;
}
bool GetValue()const{
    return value;
}
signals:
void EmitDone();
public slots:
void OnHandleOk(){
   value=checkbox->isChecked();
   emit EmitDone();
    return;
}
};


