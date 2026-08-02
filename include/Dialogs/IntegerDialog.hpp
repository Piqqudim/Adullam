#pragma once
#include<QtWidgets/QDialog>
#include<QtWidgets/QFormLayout>
#include<QtWidgets/QVBoxLayout>
#include<QtWidgets/QLabel>
#include<QCheckBox>
#include<IntegerEdit.hpp>
#include<QtWidgets/QDialogButtonBox>
#include<IntegerInputNode.hpp>
#include<memory>
using namespace std;
//Create an integer edit that holds the previous value and the recent value
class IntegerDialog:public QDialog{
private:
Q_OBJECT
std::unique_ptr<IntegerEdit> integerEdit;
std::unique_ptr<QLabel> label;
std::unique_ptr<QFormLayout> flayout;
std::unique_ptr<QDialogButtonBox> buttons;
std::unique_ptr<QVBoxLayout> vlayout;
std::unique_ptr<QCheckBox> checkbox;
IntegerInputNode* intnode=nullptr;

public:
IntegerDialog():QDialog(){
 integerEdit=make_unique<IntegerEdit>();
 label=make_unique<QLabel>(QString::number(0));
 flayout=std::make_unique<QFormLayout>();
 vlayout=std::make_unique<QVBoxLayout>();
 buttons=std::make_unique<QDialogButtonBox>(QDialogButtonBox::Ok|QDialogButtonBox::Cancel);
 flayout->addRow(tr("Previous Value:"),label.get());
 flayout->addRow(tr("Input Value:"),integerEdit.get());
 checkbox=make_unique<QCheckBox>(tr(""));
 flayout->addRow(tr("Enable Dynamic Update"),checkbox.get());
 vlayout->addLayout(flayout.get());
 vlayout->addWidget(buttons.get());
 
 
 connect(buttons.get(),&QDialogButtonBox::accepted,this,&IntegerDialog::OnHandleOk);
 connect(buttons.get(),&QDialogButtonBox::rejected,this,&IntegerDialog::reject);
 connect(integerEdit.get(),&IntegerEdit::GetValue,this,IntegerDialog::OnGetValue);
 setLayout(vlayout.get());
}
void SetPrevValue(const int& val){ 
    label->setText(QString::number(val));
    return;
}
void SetIntNode(IntegerInputNode* node){
    intnode=node;
    return;
}
int Value() const{
    return integerEdit->Result();
}
signals:
void EmitDone();

public slots:
void OnGetValue(const int& val){
    if(checkbox->isChecked()){
     intnode->SetIntData(val);
     intnode->DataUpdated();
    }
    return;
}
void OnHandleOk(){
    accept();
    if(checkbox->isChecked()==false){
    emit EmitDone();
    }
}
};

