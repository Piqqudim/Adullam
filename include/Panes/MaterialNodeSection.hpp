#pragma once
#include<DoubleLineEdit.hpp>
#include<QtWidgets/QLabel>
#include<Graphic3d_MaterialAspect.hxx>
#include<ColorPane.hpp>
#include<QtWidgets/QCheckBox>
#include<SinglyMaterialNode.hpp>
#include<Section.h>
#include<QtWidgets/QFormLayout>
#include<memory>
using namespace std;
enum MaterialSelect{
MS_BASE,
MS_DIFFUSE,
MS_SPECULAR,
MS_AMBIENT,
MS_EMISSIVE,
MS_NULL
};
class MaterialNodeSection:public Section{
public:
std::unique_ptr<ColorPane> baseColorPane;
std::unique_ptr<ColorPane> diffuseColorPane;
std::unique_ptr<ColorPane> ambientColorPane;
std::unique_ptr<ColorPane> specularColorPane;
std::unique_ptr<ColorPane> emissiveColorPane;
std::unique_ptr<DoubleEdit> refractiveIndexEdit;
std::unique_ptr<DoubleEdit> transparencyEdit;
Graphic3d_MaterialAspect outputMaterial;
unique_ptr<QFormLayout> formlayout;
unique_ptr<QCheckBox> checkBox;
MaterialSelect mselect=MS_NULL;
public:
MaterialNodeSection(const int& dummyvalue=0,QWidget*parent=nullptr):Section(tr("Material Creator"),2,parent){
     baseColorPane=make_unique<ColorPane>(this);
    formlayout=std::make_unique<QFormLayout>();
    formlayout->addRow(tr("Base Color"),baseColorPane.get());
    diffuseColorPane=make_unique<ColorPane>(this);
    formlayout->addRow(tr("Diffuse Color"),diffuseColorPane .get());
    ambientColorPane=std::make_unique<ColorPane>(this);
    formlayout->addRow(tr("Ambient Color"),ambientColorPane.get());
    specularColorPane=make_unique<ColorPane>(this);
    formlayout->addRow(tr("Specular Color"),specularColorPane.get());
    emissiveColorPane=std::make_unique<ColorPane>(this);
    formlayout->addRow(tr("Emissive Color"),emissiveColorPane.get());
    refractiveIndexEdit=make_unique<DoubleEdit>(this,QString::number(0.0),8);
    formlayout->addRow(tr("Refractive Index"),refractiveIndexEdit.get());
    transparencyEdit=make_unique<DoubleEdit>(this,QString::number(0.0),8);
    formlayout->addRow(tr("Transparency"),transparencyEdit.get());
    setContentLayout(*formlayout.get());
}
MaterialNodeSection(QWidget* parent=nullptr):Section(tr("Material Creator"),2,parent){
    baseColorPane=make_unique<ColorPane>(this);
    formlayout=std::make_unique<QFormLayout>();
    formlayout->addRow(tr("Base Color"),baseColorPane.get());
    diffuseColorPane=make_unique<ColorPane>(this);
    formlayout->addRow(tr("Diffuse Color"),diffuseColorPane.get());
    ambientColorPane=std::make_unique<ColorPane>(this);
    formlayout->addRow(tr("Ambient Color"),ambientColorPane.get());
    specularColorPane=make_unique<ColorPane>(this);
    formlayout->addRow(tr("Specular Color"),specularColorPane.get());
    emissiveColorPane=std::make_unique<ColorPane>(this);
    formlayout->addRow(tr("Emissive Color"),emissiveColorPane.get());
    refractiveIndexEdit=make_unique<DoubleEdit>(this,QString::number(0.0),8);
    formlayout->addRow(tr("Refractive Index"),refractiveIndexEdit.get());
    transparencyEdit=make_unique<DoubleEdit>(this,QString::number(0.0),8);
    formlayout->addRow(tr("Transparency"),transparencyEdit.get());
    checkBox=make_unique<QCheckBox>(nullptr);
    formlayout->addRow(tr("Convert To Node"),checkBox.get());
    setContentLayout(*formlayout.get());
}
Graphic3d_MaterialAspect& Material(){
    return outputMaterial;
}
Graphic3d_MaterialAspect GetMaterial() const{
    return outputMaterial;
}
void InitFromMaterialNode(SinglyMaterialNode* node){
    if(node==nullptr){
        return;
    }
    baseColorPane->SetColorFromOC(node->output().DiffuseColor());
    ambientColorPane->SetColorFromOC(node->output().AmbientColor());
    diffuseColorPane->SetColorFromOC(node->output().DiffuseColor());
    specularColorPane->SetColorFromOC(node->output().SpecularColor());
    emissiveColorPane->SetColorFromOC(node->output().EmissiveColor());
    refractiveIndexEdit->setText(QString::number(node->output().RefractionIndex()));
    transparencyEdit->setText(QString::number(node->output().Transparency()));
    outputMaterial=node->output();
    return;
    
}
void SetMaterialSelect(const MaterialSelect& select){
    mselect=select;
    return;
}
void SetColor(const Quantity_Color& col){
    switch(mselect){
        case MS_BASE:{
            diffuseColorPane->SetColorFromOC(col);
            baseColorPane->SetColorFromOC(col);
            outputMaterial=Material();
            outputMaterial.SetDiffuseColor(col);
            break;
        }
        case MS_DIFFUSE:{
            diffuseColorPane->SetColorFromOC(col);
            baseColorPane->SetColorFromOC(col);
             outputMaterial=Material();
            outputMaterial.SetDiffuseColor(col);
            break;
        }
        case MS_SPECULAR:{
            specularColorPane->SetColorFromOC(col);
             outputMaterial=Material();
            outputMaterial.SetSpecularColor(col);
            break;
        }
        case MS_AMBIENT:{
            ambientColorPane->SetColorFromOC(col);
             outputMaterial=Material();
            outputMaterial.SetAmbientColor(col);
            break;
        }
        case MS_EMISSIVE:{
            emissiveColorPane->SetColorFromOC(col);
             outputMaterial=Material();
            outputMaterial.SetEmissiveColor(col);
            break;
        }
    }
    return;
}

};