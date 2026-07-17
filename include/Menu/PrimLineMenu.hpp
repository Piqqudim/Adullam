#pragma once 
#include<QtWidgets/QMenu>
#include<memory>
using namespace std;
class PrimLineMenu:public QMenu{
private:
unique_ptr<QAction> startAction;
unique_ptr<QAction> continueAction; //continue, editing 
unique_ptr<QAction> copyAxis;  //copy Axis node
unique_ptr<QAction> copyLength; // copy Length
std::unique_ptr<QAction> endAction; //end 
std::unique_ptr<QAction> convertToPrim; // convert to prim line
std::unique_ptr<QAction> nullifyShape;
public:
PrimLineMenu(){
    startAction=make_unique<QAction>(tr("Start"));
    continueAction=make_unique<QAction>(tr("Continue"));
    copyAxis=make_unique<QAction>(tr("Copy Axis"));
    copyAxis->setCheckable(true);
    copyLength=make_unique<QAction>(tr("Copy Length"));
    copyLength->setCheckable(true);
    endAction=make_unique<QAction>(tr("End"));
    nullifyShape=make_unique<QAction>(tr("Nullify Shape"));
    convertToPrim=make_unique<QAction>(tr("Convert To Primitive Line"));
    convertToPrim->setCheckable(true);
    addAction(startAction.get());
    addAction(continueAction.get());
    addAction(copyAxis.get());
    addAction(nullifyShape.get());
    addAction(copyLength.get());
    addAction(endAction.get());
    addAction(convertToPrim.get());
}
QAction* Start() const{
    return startAction.get();
}
QAction* Continue() const{
    return continueAction.get();
}
QAction* CopyAxis() const{
    return copyAxis.get();
}
QAction* CopyLength() const{
    return copyLength.get();
}
QAction* End() const{
    return endAction.get();
}
QAction* NullifyShape() const{
    return nullifyShape.get();
}
QAction* Convert() const{
    return convertToPrim.get();
}
};
