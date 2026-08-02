#pragma once
#include<QtWidgets/QMenu>
#include<memory>
using namespace std;
class EdgeMenu:public QMenu{
 public:
 std::unique_ptr<QAction> showInfoAction;
std::unique_ptr<QAction> convertAction;
std::unique_ptr<QAction> convertToFaceAction;
std::unique_ptr<QAction> convertToWireAction;
std::unique_ptr<QAction> convertToPointNode=std::make_unique<QAction>(tr("Convert To Point Node"));
std::unique_ptr<QAction> trimAction=std::make_unique<QAction>(tr("Trim "));
std::unique_ptr<QAction> filletAction=std::make_unique<QAction>(tr("Apply Fillet"));
std::unique_ptr<QAction> editMenuAction=std::make_unique<QAction>(tr("Edit"));
std::unique_ptr<QMenu> editMenu=std::make_unique<QMenu>();
std::unique_ptr<QAction> editLine=std::make_unique<QAction>(tr("Edit Curve"));
std::unique_ptr<QAction> updateLineEdit=std::make_unique<QAction>(tr("Update Curve Edit Presentation"));
std::unique_ptr<QAction> removeLineEdit=std::make_unique<QAction>(tr("Remove Curve Edit"));
std::unique_ptr<QAction> nullify=std::make_unique<QAction>(tr("Nullify Curve Representation"));
std::unique_ptr<QAction> update=std::make_unique<QAction>(tr("Update With Transform"));
std::unique_ptr<QAction> alignWithDir=std::make_unique<QAction>(tr("Align With Direction"));
std::unique_ptr<QAction> convertwireAction=std::make_unique<QAction>(tr("Convert To Wire"));
std::unique_ptr<QAction> endEdgeMenu=std::make_unique<QAction>(tr("End"));
EdgeMenu():QMenu(){
    showInfoAction=std::make_unique<QAction>(tr("Show Info"),nullptr);
    convertAction=std::make_unique<QAction>(tr("Convert To Edge Node"),nullptr);
    convertToFaceAction=make_unique<QAction>(tr("Convert To Face Node"),nullptr);
    convertToWireAction=make_unique<QAction>(tr("Convert To Wire Node"),nullptr);
    editMenuAction->setMenu(editMenu.get());
    editMenu->addAction(editLine.get());
    editMenu->addAction(updateLineEdit.get());
    editMenu->addAction(removeLineEdit.get());
    editMenu->addAction(nullify.get());
    editMenu->addAction(update.get()); //this updates the corresponding marker with the transform
    editMenu->addAction(alignWithDir.get());
    filletAction->setCheckable(true);
    convertToWireAction->setCheckable(true);
    convertAction->setCheckable(true);
    convertToFaceAction->setCheckable(true);
    trimAction->setCheckable(true);
    convertToPointNode->setCheckable(true);
    
    addAction(showInfoAction.get());
    addAction(convertAction.get());
    addAction(trimAction.get());
    addAction(convertToPointNode.get());
    addAction(editMenuAction.get());
    addAction(convertToFaceAction.get());
    addAction(convertToWireAction.get());
    addAction(convertwireAction.get());
    addAction(endEdgeMenu.get());
    addAction(filletAction.get());
    
    return;
}


};

class PointMenu:public QMenu{
public:
std::unique_ptr<QAction> DeleteAction=std::make_unique<QAction>(tr("Delete"),nullptr);
PointMenu():QMenu()
{
  addAction(DeleteAction.get());
}
};
class AxisMenu:public QMenu{
public:
std::unique_ptr<QAction> convertToAxisNode;  //with respect to the origin
std::unique_ptr<QAction> convertToPositionedAxis; //with respect to the chosen origin

public:
AxisMenu(){
    
  convertToAxisNode=std::make_unique<QAction>(tr("Convert To Axis Node"),nullptr);
  convertToPositionedAxis=std::make_unique<QAction>(tr("Convert To Positioned Axis Node"),nullptr);
  convertToAxisNode->setCheckable(true);
  convertToPositionedAxis->setCheckable(true);
  addAction(convertToAxisNode.get());
  addAction(convertToPositionedAxis.get());
  return;
}

};

class DrawLineMenu:public QMenu{
public:
std::unique_ptr<QAction> drawLineAction=std::make_unique<QAction>(tr("Start Drawing"));
std::unique_ptr<QAction> stopLineAction=std::make_unique<QAction>(tr("Stop Drawing"));
public:
DrawLineMenu(){
  addAction(drawLineAction.get());
  stopLineAction->setCheckable(true);
  stopLineAction->setChecked(true);
  addAction(stopLineAction.get());
}
};

class DrawCircleMenu:public QMenu{
public:
std::unique_ptr<QAction> firstPoint;
std::unique_ptr<QAction> secondPoint;
std::unique_ptr<QAction> thirdPoint;
std::unique_ptr<QAction> stopCircle;
std::unique_ptr<QAction> destroyCircleOps;
public:
DrawCircleMenu(){
  firstPoint=std::make_unique<QAction>(tr("first Point"));
  firstPoint->setCheckable(true);
  secondPoint=std::make_unique<QAction>(tr("second Point"));
  secondPoint->setCheckable(true);
  thirdPoint=std::make_unique<QAction>(tr("third Point"));
  thirdPoint->setCheckable(true);
  stopCircle=std::make_unique<QAction>(tr("Stop Circle"));
  destroyCircleOps=make_unique<QAction>(tr("Terminate Circle Operation"));
  addAction(firstPoint.get());
  addAction(secondPoint.get());
  addAction(thirdPoint.get());
  addAction(stopCircle.get());
  addAction(destroyCircleOps.get());
}
void SetThreeValues(bool value,bool value_1,bool value_2){
  firstPoint->setChecked(value);
  secondPoint->setChecked(value_1);
  thirdPoint->setChecked(value_2);
  return;
}
};
class FilletMenu:public QMenu{
public:
unique_ptr<QAction> chooseFirstEdge;
unique_ptr<QAction> chooseSecondEdge;
unique_ptr<QAction> chooseVertex;
unique_ptr<QAction> selectRadius;
unique_ptr<QAction> buildAction=std::make_unique<QAction>(tr("Build"));
unique_ptr<QAction> endFilletOps=make_unique<QAction>(tr("End Fillet Operation"));
FilletMenu(){
  chooseFirstEdge=make_unique<QAction>(tr("First Edge"));
  chooseFirstEdge->setCheckable(true);
  chooseSecondEdge=make_unique<QAction>(tr("Second Edge"));
  chooseSecondEdge->setCheckable(true);
  chooseVertex=std::make_unique<QAction>(tr("Choose Vertex"));
  chooseVertex->setCheckable(true);
  selectRadius=make_unique<QAction>(tr("Select Radius"));
  
  addAction(chooseFirstEdge.get());
  addAction(chooseSecondEdge.get());
  addAction(chooseVertex.get());
  addAction(selectRadius.get());
  addAction(buildAction.get());
  addAction(endFilletOps.get());
  
  return;
}
void SetBoolValues(const bool& value_1,const bool& value_2,const bool& value_3){
  chooseFirstEdge->setChecked(value_1);
  chooseSecondEdge->setChecked(value_2);
  chooseVertex->setChecked(value_3);
  return;
}

};

class TrimMenu:public QMenu{
private:
std::unique_ptr<QAction> firstpoint;
std::unique_ptr<QAction> secondpoint;
std::unique_ptr<QAction> trimAction;
std::unique_ptr<QMenu> trimOptionMenu;

std::unique_ptr<QAction> Trim;
std::unique_ptr<QAction> trimByPointAction;
std::unique_ptr<QAction> endTrimOps;

public:
TrimMenu(){
 firstpoint=make_unique<QAction>(tr("Choose First Point"));
 firstpoint->setCheckable(true);
 secondpoint=make_unique<QAction>(tr("Choose Second Point"));
 secondpoint->setCheckable(true);
 trimAction=std::make_unique<QAction>(tr("Build Trim Operation"));
 trimOptionMenu=std::make_unique<QMenu>();
 trimAction->setMenu(trimOptionMenu.get());
 trimByPointAction=std::make_unique<QAction>(tr("Trim By Point"));
 Trim=std::make_unique<QAction>(tr("Trim By Parametric Values"));
 trimOptionMenu->addAction(Trim.get());
 trimOptionMenu->addAction(trimByPointAction.get());
 endTrimOps=std::make_unique<QAction>(tr("End Trim Operations"));
 addAction(firstpoint.get());
 addAction(secondpoint.get());

 addAction(trimAction.get());
 addAction(endTrimOps.get());
}
QAction* First() const{
  return firstpoint.get();
}
QAction* EndOps() const{
  return endTrimOps.get();
}
QAction* Second() const{
  return secondpoint.get();
}
QAction* TrimAction() const{
  return Trim.get();
}
QAction* PointAction() const{
  return trimByPointAction.get();
}
void SetValues(bool first,bool second){
  firstpoint->setChecked(first);
  secondpoint->setChecked(second);
  return;
}
};
