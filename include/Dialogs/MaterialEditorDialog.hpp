#pragma once
#include<QtWidgets/QDialog>
#include<ColorDialog.hpp>
#include<MaterialNodeSection.hpp>
#include<QtWidgets/QScrollArea>
#include<QtWidgets/QCheckBox>
#include<memory>
#include<InfoUtility.hpp>
using namespace INFO;
using namespace std;
class MaterialEditorDialog:public QDialog{
private:
Q_OBJECT
unique_ptr<ColorDialog> colorDialog=make_unique<ColorDialog>();
unique_ptr<MaterialNodeSection> matsection=make_unique<MaterialNodeSection>(1,nullptr);
unique_ptr<QScrollArea> scrollarea=make_unique<QScrollArea>();
unique_ptr<QDialogButtonBox> dialogButtons=make_unique<QDialogButtonBox>(QDialogButtonBox::Cancel|QDialogButtonBox::Ok,nullptr);
std::unique_ptr<QVBoxLayout> vlayout=make_unique<QVBoxLayout>();
std::unique_ptr<QCheckBox> enableCheckBox=make_unique<QCheckBox>(tr("Enable dynamic update"));
SinglyMaterialNode* matnode=nullptr;


public:
MaterialEditorDialog(QWidget* parent=nullptr):QDialog(parent){
    setWindowTitle(tr("Material Editor"));
    vlayout->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    scrollarea->setWidget(matsection.get());
    vlayout->addWidget(scrollarea.get());
    vlayout->addWidget(enableCheckBox.get());
    vlayout->addWidget(dialogButtons.get());
    setLayout(vlayout.get());
    setSizeGripEnabled(true);
   connect(dialogButtons.get(),&QDialogButtonBox::rejected,this,&QDialog::reject);
   connect(dialogButtons.get(),&QDialogButtonBox::accepted,this,&MaterialEditorDialog::OnHandleOk);
   connect(matsection->specularColorPane.get(),&ColorPane::IsDoubleClicked,this,&MaterialEditorDialog::OnHandleSpecularColor);
   connect(matsection->diffuseColorPane.get(),&ColorPane::IsDoubleClicked,this,&MaterialEditorDialog::OnHandleDiffuseColor);
   connect(matsection->ambientColorPane.get(),&ColorPane::IsDoubleClicked,this,&MaterialEditorDialog::OnHandleAmbientColor);
   connect(matsection->emissiveColorPane.get(),&ColorPane::IsDoubleClicked,this,&MaterialEditorDialog::OnHandleEmissiveColor);
   connect(matsection->baseColorPane.get(),&ColorPane::IsDoubleClicked,this,&MaterialEditorDialog::OnHandleBaseColor);
   connect(matsection->transparencyEdit.get(),&DoubleEdit::GetValue,this,&MaterialEditorDialog::OnHandleTransparency);
    connect(matsection->refractiveIndexEdit.get(),&DoubleEdit::GetValue,this,&MaterialEditorDialog::OnHandleRefract);
   connect(colorDialog->ColorWidget(),&ColorCollectionWidget::GetSelectedColor,this,&MaterialEditorDialog::OnHandleColorWidget);
}
void SetMatNode(SinglyMaterialNode* matnode1){
    matnode=matnode1;
    matsection->InitFromMaterialNode(matnode);
    return;
}
public slots:
void OnHandleOk(){
    accept();
  return;
}
void OnHandleColorWidget(){
    matsection->SetColor(colorDialog->ColorWidget()->GetChosenColor());
    matnode->Material()=matsection->GetMaterial();
    if(enableCheckBox->isChecked()){
        matnode->OnUpdate();
    }
    
    return;
}
void OnHandleSpecularColor(const size_t& ind){
   matsection->SetMaterialSelect(MS_SPECULAR);
   colorDialog->SetTitle(tr("Specular Color Dialog"));
   colorDialog->exec();
   return;
 }
void OnHandleDiffuseColor(const size_t& ind){
   matsection->SetMaterialSelect(MS_DIFFUSE);
   colorDialog->SetTitle(tr("Diffuse Color Dialog"));
   colorDialog->exec();
   return;
 }
 void OnHandleAmbientColor(const size_t& ind){
   matsection->SetMaterialSelect(MS_AMBIENT);
   colorDialog->SetTitle(tr("Ambient Color Dialog"));
   colorDialog->exec();
   return;
 }
void OnHandleEmissiveColor(const size_t& ind){
   matsection->SetMaterialSelect(MS_EMISSIVE);
   colorDialog->SetTitle(tr("Emissive Color Dialog"));
   colorDialog->exec();
   return;
 }
 void OnHandleBaseColor(const size_t& ind){
   matsection->SetMaterialSelect(MS_BASE);
   colorDialog->SetTitle(tr("Base Color Dialog"));
   colorDialog->exec();
   return;
 }
  void OnHandleTransparency(const float& value){
  if(value>1.0f){
    LoadMessage(tr(""),tr("Transparency value is greater than 1.0"));
    return;
  }
  if(value<0.0){
    LoadMessage(tr(""),tr("Transparency value is less than 0.0"));
    return;
  }
  if(!matnode){
    LoadMessage(tr(""),tr("An object of singly material node is not selected"));
    return;
  }
  matsection->Material().SetTransparency(value);
  matnode->Material().SetTransparency(value);
  if(enableCheckBox->isChecked()){
     matnode->OnUpdate();
  }
  return;

 }
 void OnHandleRefract(const float& value){
  
  if(value<=0.0){
    LoadMessage(tr(""),tr("Refractive value is less than 0.0"));
    return;
  }
  if(!matnode){
    LoadMessage(tr(""),tr("An object of singly material node is not selected"));
    return;
  }
  matsection->Material().SetRefractionIndex(value);
  matnode->Material().SetRefractionIndex(value);
  if(enableCheckBox->isChecked()){
     matnode->OnUpdate();
  }
  return;

 }
};
