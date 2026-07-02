#pragma once
#include<QtWidgets/QLineEdit>
#include<QtGui/QIntValidator>
#include<memory>
using namespace std;

class IntegerEdit:public QLineEdit{
private:
Q_OBJECT
std::unique_ptr<QIntValidator> validator;
int result=0;
public:
IntegerEdit(){
    validator=std::make_unique<QIntValidator>(-90000000,90000000);
    setValidator(validator.get());
    setAlignment(Qt::AlignHCenter);
    connect(this,&IntegerEdit::textEdited,this,&IntegerEdit::OnConvertToInteger);
    connect(this,&IntegerEdit::textChanged,this,&IntegerEdit::OnConvertToInteger);
    return;
} 
void SetRange(const int& min,const int& max){
    validator->setRange(min,max);
    return;
}
int Result() const{
    return result;
}
signals:
void GetValue(const int& value);

public slots:
void OnConvertToInteger(const QString& str){
    if(str.isEmpty()){
        return;
    }
    int value=validator->locale().toInt(str);
    emit GetValue(value);
    result=value;
    return;
}
};