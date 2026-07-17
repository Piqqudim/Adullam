#pragma once 
#include<QtWidgets/QMenu>
#include<memory>
using namespace std;
class PrimCircleMenu:public QMenu{
private:
unique_ptr<QAction> startAction;
unique_ptr<QAction> continueAction;
unique_ptr<QAction> copyAxis;
unique_ptr<QAction> copyRadius;
unique_ptr<QAction> endAction;
unique_ptr<QAction> convertToPrim;
unique_ptr<QAction> nullifyShape;
public:
PrimCircleMenu():QMenu(){
    startAction=std::make_unique<QAction>(tr("Start"));
    continueAction=std::make_unique<QAction>(tr("Edit"));
    copyAxis=std::make_unique<QAction>(tr("Copy Axis"));
    copyRadius=std::make_unique<QAction>(tr("Copy Radius"));
    copyAxis->setCheckable(true);
    copyRadius->setCheckable(true);
    endAction=std::make_unique<QAction>(tr("End"));
    convertToPrim=std::make_unique<QAction>(tr("Convert To Prim Circle"));
    convertToPrim->setCheckable(true);
    nullifyShape=std::make_unique<QAction>(tr("Nullify Shape"));
    addAction(startAction.get());
    addAction(continueAction.get());
    addAction(copyRadius.get());
    addAction(copyAxis.get());
    addAction(endAction.get());
    addAction(convertToPrim.get());
    addAction(nullifyShape.get());
    return;
}
QAction* Start() const{
    return startAction.get();
}
QAction* End() const{
    return endAction.get();
}
QAction* CopyAxis() const{
    return copyAxis.get();
}
QAction* CopyRadius() const{
    return copyRadius.get();
}
QAction* Continue() const{
    return continueAction.get();
}
QAction* Convert() const{
    return convertToPrim.get();
}
QAction* Nullify() const{
    return nullifyShape.get();
}
};