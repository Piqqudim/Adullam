#ifndef HIGHLIGHTSECTION_HPP
#define HIGHLIGHTSECTION_HPP
#include<Section.h>
#include<memory>
#include<DoubleLineEdit.hpp>
#include<QtWidgets/QFormLayout>
#include<QtWidgets/QDialog>
#include<QtWidgets/QTextEdit>
#include<QtWidgets/QLabel>
#include<QtWidgets/QWidget>
#include<ColorPane.hpp>
#include<QtWidgets/QCheckBox>
//For Selected Object
class SelectedHighlightSection:public Section{
private:
std::unique_ptr<QFormLayout> myFormLayout; //This will arrange the widgets side by side
std::unique_ptr<QLabel> myFaceColorLabel; //This is my label for my face
std::unique_ptr<QWidget> myFaceColor;   //this will be a little widget that will be displayed by the side of myFaceColorLabel
std::unique_ptr<QLabel> myLineColorLabel; 
std::unique_ptr<ColorPane> myFaceColorPane=std::make_unique<ColorPane>();
std::unique_ptr<QWidget> myLineColor;
std::unique_ptr<QLabel> myLineWidthLabel;
std::unique_ptr<DoubleEdit> myLineWidthEdit;
std::unique_ptr<DoubleEdit> myTranspar_Edit;
std::unique_ptr<QLabel> myTranspar_Label;


public:
SelectedHighlightSection(const QString& pSec_Name,const size_t& psz,QWidget* pparent,const double& p_DEditValue):Section(pSec_Name,psz,pparent){
    myFormLayout.reset(new QFormLayout());
    myFaceColorLabel.reset(new QLabel(tr("Background Color:")));
    myFaceColor.reset(new ColorPane(this));
    

    myFaceColor->setFixedSize(50,50);
    myLineColorLabel.reset(new QLabel(tr("Line Selection Color:")));
    myLineColor.reset(new ColorPane(this));
    myLineColor->setFixedSize(50,50);
    myFaceColorPane->setFixedSize(50,50);
  
    
    myFormLayout->addRow(myFaceColorLabel.get(),myFaceColor.get());
    myFormLayout->addRow(myLineColorLabel.get(),myLineColor.get());
    myFormLayout->addRow(tr("Face Color:"),myFaceColorPane.get());
   
    setContentLayout(*myFormLayout.get());
}
ColorPane* FaceColorWidget(){
    return static_cast<ColorPane*>(myFaceColor.get());
}
ColorPane* FaceColorPane() const{
    return myFaceColorPane.get();
}
DoubleEdit* LineWidthEdit(){
    return myLineWidthEdit.get();
}



};





#endif
