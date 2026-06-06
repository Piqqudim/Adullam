#pragma once
#include<QtWidgets/QWidget>
#include<MaterialNodeSection.hpp>
#include<QtWidgets/QVBoxLayout>
#include<memory>
using namespace std;
class MaterialNodeWidget:public QWidget{
private:
unique_ptr<QVBoxLayout> vlayout;
unique_ptr<MaterialNodeSection> matSection;


public:
MaterialNodeWidget(QWidget* parent=nullptr){
    matSection=std::make_unique<MaterialNodeSection>(this);
    vlayout=std::make_unique<QVBoxLayout>();
    vlayout->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    vlayout->addWidget(matSection.get());
    setLayout(vlayout.get());
    return;
}
MaterialNodeSection* MatSection() const{
    return matSection.get();
}
};