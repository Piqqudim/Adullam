#pragma once
#include<QtWidgets/QDialog>
#include<QtWidgets/QDialogButtonBox>
#include<memory>
#include<DoubleLineEdit.hpp>
#include<QtWidgets/QFormLayout>
#include<QtWidgets/QVBoxLayout>
#include<QtWidgets/QLabel>
#include<FloatNode.hpp>
#include<QCheckBox>
using namespace std;
class FloatDialog:public QDialog{
private:
Q_OBJECT
std::unique_ptr<QVBoxLayout> vlayout;
std::unique_ptr<QFormLayout> flayout;
std::unique_ptr<DoubleEdit> floatEdit;
std::unique_ptr<QCheckBox> checkbox;
std::unique_ptr<QLabel> label;
unique_ptr<QDialogButtonBox> dialogButtons;
float output=0.0f;
FloatNode* floatnode=nullptr;
public:
FloatDialog():QDialog(){
    setWindowTitle(tr("Float Dialog"));
    flayout=std::make_unique<QFormLayout>();
    floatEdit=std::make_unique<DoubleEdit>(nullptr,QString::number(1.0),8);
    vlayout=std::make_unique<QVBoxLayout>();
    vlayout->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    dialogButtons=make_unique<QDialogButtonBox>(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
    label=std::make_unique<QLabel>(tr("No Value"));
    checkbox=make_unique<QCheckBox>(tr(""));
    flayout->addRow(tr("Previous Value"),label.get());
    flayout->addRow(tr("Input:"),floatEdit.get());
    flayout->addRow(tr("Enable Dynamic Update"),checkbox.get());
    vlayout->addLayout(flayout.get());
    vlayout->addWidget(dialogButtons.get());
    setLayout(vlayout.get());
    connect(dialogButtons.get(),&QDialogButtonBox::rejected,this,&FloatDialog::OnHandleCancel);
    connect(dialogButtons.get(),&QDialogButtonBox::accepted,this,&FloatDialog::OnHandleOk);
    connect(floatEdit.get(),&DoubleEdit::GetValue,this,&FloatDialog::OnGetFloat);
}
float GetData() const{
    return output;
}
void SetFloat(const float& val){
    label->setText(QString::number(val));
    return;
}
void SetFloatNode(FloatNode* node){
    floatnode=node;
    return;
}


signals:
void EmitDone();

public slots:
void OnHandleOk(){
    if(checkbox->isChecked()==false){
    emit EmitDone();
    }
    accept();
    return;
}
void OnHandleCancel(){
    reject();
    return;
}
void OnGetFloat(const float& data){
    if(checkbox->isChecked()==true){
      if(floatnode){
        floatnode->SetFloatData(data);
        floatnode->UpdateData();
      }      
    }
    output=data;

    return;
}
};