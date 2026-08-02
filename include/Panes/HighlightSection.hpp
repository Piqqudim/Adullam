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
enum COLORPANE{
    CP_FACE,
    CP_EDGE,
    CP_BACKGROUND,
    CP_SHAPE,
    CP_WIRE,
    CP_NULL
};
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
std::unique_ptr<ColorPane> wireColorPane;
std::unique_ptr<ColorPane> shapeColorPane;
COLORPANE cp=CP_NULL;
public:
SelectedHighlightSection(const QString& pSec_Name,const size_t& psz,QWidget* pparent,const double& p_DEditValue):Section(pSec_Name,psz,pparent){
    myFormLayout.reset(new QFormLayout());
    myFaceColorLabel.reset(new QLabel(tr("Scene Color:")));
    myFaceColor.reset(new ColorPane(this));
    

    myFaceColor->setFixedSize(30,30);
    myLineColorLabel.reset(new QLabel(tr("Line Color:")));
    myLineColor.reset(new ColorPane(this));
    myLineColor->setFixedSize(30,30);
    myFaceColorPane->setFixedSize(30,30);
  
    wireColorPane=std::make_unique<ColorPane>();
    shapeColorPane=std::make_unique<ColorPane>();
    wireColorPane->setFixedSize(30,30);
    shapeColorPane->setFixedSize(30,30);
    myFormLayout->addRow(myFaceColorLabel.get(),myFaceColor.get());
    myFormLayout->addRow(myLineColorLabel.get(),myLineColor.get());
    myFormLayout->addRow(tr("Face Color:"),myFaceColorPane.get());
    myFormLayout->addRow(tr("Wire Color"),wireColorPane.get());
    myFormLayout->addRow(tr("Shape Color:"),shapeColorPane.get());
    setContentLayout(*myFormLayout.get());
}
void SetCP(const COLORPANE& p){
    cp=p;
    return;
}
COLORPANE cpState() const{
    return cp;
}
ColorPane* FaceColorWidget(){
    return static_cast<ColorPane*>(myFaceColor.get());
}
ColorPane* FaceColorPane() const{
    return myFaceColorPane.get();
}
ColorPane* WireColorPane() const{
    return wireColorPane.get();
}
ColorPane* EdgeColorPane() const{
    return static_cast<ColorPane*>(myLineColor.get());
}
ColorPane* ShapeColorPane() const{
    return shapeColorPane.get();
}
DoubleEdit* LineWidthEdit(){
    return myLineWidthEdit.get();
}



};





#endif
