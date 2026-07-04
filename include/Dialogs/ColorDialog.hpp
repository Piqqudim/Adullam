#pragma once
#include<Quantity_Color.hxx>
#include<ColourCollectionWidget.hpp>
#include<QtWidgets/QDialog>
#include<QtWidgets/QVBoxLayout>
#include<memory>
#include<QtWidgets/QScrollArea>
#include<QtWidgets/QDialogButtonBox>
using namespace std;
class ColorDialog:public QDialog{
private:
Q_OBJECT
bool isSpawned=false;
std::unique_ptr<ColorCollectionWidget> colorwidget;
std::unique_ptr<QScrollArea> scrollarea;
std::unique_ptr<QVBoxLayout> vlayout; 
std::unique_ptr<QDialogButtonBox> dialogButtons;
public:
ColorDialog(QWidget* parent=nullptr):QDialog(parent){
  setWindowTitle(tr("NodeCAD Color Dialog"));
  colorwidget=std::make_unique<ColorCollectionWidget>(nullptr);
  scrollarea=std::make_unique<QScrollArea>(this);
  scrollarea->setWidgetResizable(true);
  scrollarea->setVisible(true);
  dialogButtons=std::make_unique<QDialogButtonBox>(QDialogButtonBox::Cancel|QDialogButtonBox::Ok,nullptr);
  connect(dialogButtons.get(),&QDialogButtonBox::rejected,this,&ColorDialog::OnHandleCancel);
  connect(dialogButtons.get(),&QDialogButtonBox::accepted,this,&ColorDialog::OnHandleOk);
  vlayout=std::make_unique<QVBoxLayout>();
  vlayout->setAlignment(Qt::AlignTop|Qt::AlignLeft);
  scrollarea->setWidget(colorwidget.get());
  vlayout->addWidget(scrollarea.get());
  vlayout->addWidget(dialogButtons.get());
    setSizeGripEnabled(true);
  setLayout(vlayout.get());
   return;
}
ColorCollectionWidget* ColorWidget() const{
    return colorwidget.get();
}
Quantity_Color GetColor() const{
  return ColorWidget()->GetChosenColor();
}
void SetTitle(const QString& title){
    setWindowTitle(title);
    return;
}
void SetIsSpawned(bool value){
    isSpawned=value;
    return;
}
public slots:
void OnHandleCancel(){
    isSpawned=false;
    reject();
}
void OnHandleOk(){
     isSpawned=false;
    accept();
}
};