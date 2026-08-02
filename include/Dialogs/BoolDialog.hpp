#pragma once 
#include<QtWidgets/QDialog>
#include<QtWidgets/QDialogButtonBox>
#include<QtWidgets/QFormLayout>
#include<memory>
#include<QtWidgets/QCheckBox>
#include<QtWidgets/QVBoxLayout>
#include<BoolNode.hpp>
using namespace std;
class BoolDialog:public QDialog{
private:
Q_OBJECT
std::unique_ptr<QCheckBox> checkbox=std::make_unique<QCheckBox>(tr(""));
std::unique_ptr<QCheckBox> cbox=make_unique<QCheckBox>(tr(""));
std::unique_ptr<QFormLayout> flayout=std::make_unique<QFormLayout>();
std::unique_ptr<QDialogButtonBox> buttons=std::make_unique<QDialogButtonBox>(QDialogButtonBox::Ok|QDialogButtonBox::Cancel,nullptr);
std::unique_ptr<QVBoxLayout> vlayout=std::make_unique<QVBoxLayout>();
bool value=false;
BoolNode* bnode=nullptr;
public:
BoolDialog():QDialog(){
 setWindowTitle(tr("Bool Dialog"));
 flayout->addRow(tr("Value"),checkbox.get());
 flayout->addRow(tr("Enable Dynamic Update"),cbox.get());
 vlayout->addLayout(flayout.get());
 vlayout->addWidget(buttons.get());
 connect(buttons.get(),&QDialogButtonBox::rejected,this,&BoolDialog::reject);
 connect(buttons.get(),&QDialogButtonBox::accepted,this,&BoolDialog::OnHandleOk);
 connect(checkbox.get(),&QCheckBox::toggled,this,&BoolDialog::isToggled);
 setLayout(vlayout.get());
}

void SetValue(bool val){
    checkbox->setChecked(val);
    return;
}
bool GetValue()const{
    return value;
}
void SetBoolNode(BoolNode* node){
    bnode=node;
    return;
}
signals:
void EmitDone();
public slots:
void isToggled(bool value_1){
   if(cbox->isChecked()){
      bnode->SetBoolData(value_1);
   bnode->UpdateData();
   }
   
   return;
}
void OnHandleOk(){
   value=checkbox->isChecked();
   
   if(cbox->isChecked()==false){  
   emit EmitDone();
   }
   accept();
    return;
}
};


