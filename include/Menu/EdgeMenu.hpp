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
std::unique_ptr<QAction> filletAction=std::make_unique<QAction>(tr("Apply Fillet"));
EdgeMenu():QMenu(){
    showInfoAction=std::make_unique<QAction>(tr("Show Info"),nullptr);
    convertAction=std::make_unique<QAction>(tr("Convert To Edge Node"),nullptr);
    convertToFaceAction=make_unique<QAction>(tr("Convert To Face Node"),nullptr);
    convertToWireAction=make_unique<QAction>(tr("Convert To Wire Node"),nullptr);
    filletAction->setCheckable(true);
    convertToWireAction->setCheckable(true);
    convertAction->setCheckable(true);
    convertToFaceAction->setCheckable(true);
    addAction(showInfoAction.get());
    addAction(convertAction.get());
    addAction(convertToFaceAction.get());
    addAction(convertToWireAction.get());
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
  
  return;
}
void SetBoolValues(const bool& value_1,const bool& value_2,const bool& value_3){
  chooseFirstEdge->setChecked(value_1);
  chooseSecondEdge->setChecked(value_2);
  chooseVertex->setChecked(value_3);
  return;
}
};