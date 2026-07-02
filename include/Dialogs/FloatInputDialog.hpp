#pragma once
#include<QtWidgets/QDialog>
#include<QtWidgets/QDialogButtonBox>
#include<memory>
#include<DoubleLineEdit.hpp>
#include<QtWidgets/QFormLayout>
#include<QtWidgets/QVBoxLayout>
#include<QtWidgets/QLabel>
using namespace std;
class FloatDialog:public QDialog{
private:
Q_OBJECT
std::unique_ptr<QVBoxLayout> vlayout;
std::unique_ptr<QFormLayout> flayout;
std::unique_ptr<DoubleEdit> floatEdit;
std::unique_ptr<QLabel> label;
unique_ptr<QDialogButtonBox> dialogButtons;
float output=0.0f;

public:
FloatDialog():QDialog(){
    setWindowTitle(tr("Float Dialog"));
    flayout=std::make_unique<QFormLayout>();
    floatEdit=std::make_unique<DoubleEdit>(nullptr,QString::number(1.0),8);
    vlayout=std::make_unique<QVBoxLayout>();
    vlayout->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    dialogButtons=make_unique<QDialogButtonBox>(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
    label=std::make_unique<QLabel>(tr("No Value"));
    flayout->addRow(tr("Previous Value"),label.get());
    flayout->addRow(tr("Input:"),floatEdit.get());
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



signals:
void EmitDone();

public slots:
void OnHandleOk(){
    emit EmitDone();
    accept();
    return;
}
void OnHandleCancel(){
    reject();
    return;
}
void OnGetFloat(const float& data){
    output=data;
    return;
}
};