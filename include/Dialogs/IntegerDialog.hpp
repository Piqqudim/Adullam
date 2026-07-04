#pragma once
#include<QtWidgets/QDialog>
#include<QtWidgets/QFormLayout>
#include<QtWidgets/QVBoxLayout>
#include<QtWidgets/QLabel>
#include<IntegerEdit.hpp>
#include<QtWidgets/QDialogButtonBox>
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


public:
IntegerDialog():QDialog(){
 integerEdit=make_unique<IntegerEdit>();
 label=make_unique<QLabel>(QString::number(0));
 flayout=std::make_unique<QFormLayout>();
 vlayout=std::make_unique<QVBoxLayout>();
 buttons=std::make_unique<QDialogButtonBox>(QDialogButtonBox::Ok|QDialogButtonBox::Cancel);
 flayout->addRow(tr("Previous Value:"),label.get());
 flayout->addRow(tr("Input Value:"),integerEdit.get());
 vlayout->addLayout(flayout.get());
 vlayout->addWidget(buttons.get());
 connect(buttons.get(),&QDialogButtonBox::accepted,this,&IntegerDialog::OnHandleOk);
 connect(buttons.get(),&QDialogButtonBox::rejected,this,&IntegerDialog::reject);
 setLayout(vlayout.get());
}
void SetPrevValue(const int& val){
    label->setText(QString::number(val));
    return;
}
int Value() const{
    return integerEdit->Result();
}
signals:
void EmitDone();

public slots:
void OnHandleOk(){
    accept();
    emit EmitDone();
}
};

