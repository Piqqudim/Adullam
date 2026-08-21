#pragma once
#include<QMenu>
#include<QAction>
#include<memory>
using namespace std;
class CreateAxisMenu:public QMenu{
public:
unique_ptr<QAction> ChooseEdge;
unique_ptr<QAction> ChooseFace;
unique_ptr<QAction> ChooseDefaultX;
unique_ptr<QAction> ChooseDefaultY;
unique_ptr<QAction> ChooseDefaultZ;
unique_ptr<QAction> ConvertToAxisNode;
unique_ptr<QAction> End;
public:
CreateAxisMenu():QMenu(){
    ChooseEdge=make_unique<QAction>(tr("Choose Edge"));
    ChooseFace=make_unique<QAction>(tr("Choose Face"));
    ChooseEdge->setCheckable(true);
    ChooseFace->setCheckable(true);
    ChooseDefaultX=make_unique<QAction>(tr("Use Default X"));
    ChooseDefaultY=make_unique<QAction>(tr("Use Default Y"));
    ChooseDefaultZ=make_unique<QAction>(tr("Use Default Z"));
    ChooseDefaultX->setCheckable(true);
    ChooseDefaultY->setCheckable(true);
    ChooseDefaultZ->setCheckable(true);
    ConvertToAxisNode=make_unique<QAction>(tr("Convert To Axis Node"));
    ConvertToAxisNode->setCheckable(true);
    End=make_unique<QAction>(tr("End"));
    addAction(ChooseEdge.get());
    addAction(ChooseFace.get());
    addAction(ChooseDefaultX.get());
    addAction(ChooseDefaultY.get());
    addAction(ChooseDefaultZ.get());
    addAction(ConvertToAxisNode.get());
    addAction(End.get());
}
};
class chooseEdgeMenu:public QMenu{
public:
unique_ptr<QAction> SetFixed;
unique_ptr<QAction> Compute;
unique_ptr<QAction> xDirection;
unique_ptr<QAction> yDirection;
unique_ptr<QAction> zDirection;
unique_ptr<QAction> end;
public:
chooseEdgeMenu(){
    SetFixed=make_unique<QAction>(tr("Set Fixed"));
    SetFixed->setCheckable(true);
    Compute=make_unique<QAction>(tr("Compute"));
    xDirection=make_unique<QAction>(tr("X Direction"));
    yDirection=make_unique<QAction>(tr("Y Direction"));
    zDirection=make_unique<QAction>(tr("Z Direction"));
    end=make_unique<QAction>(tr("End"));
    xDirection->setCheckable(true);
    yDirection->setCheckable(true);
    zDirection->setCheckable(true);
    addAction(SetFixed.get());
    addAction(Compute.get());
    addAction(xDirection.get());
    addAction(yDirection.get());
    addAction(zDirection.get());
    addAction(end.get());
}
};



class chooseFaceMenu:public QMenu{
public:
unique_ptr<QAction> SetFixed;
unique_ptr<QAction> Compute;
unique_ptr<QAction> xDirection;
unique_ptr<QAction> yDirection;
unique_ptr<QAction> zDirection;
unique_ptr<QAction> end;

public:
chooseFaceMenu():QMenu(){
    SetFixed=make_unique<QAction>(tr("Set Fixed"));
    SetFixed->setCheckable(true);
    Compute=make_unique<QAction>(tr("Compute"));
    xDirection=make_unique<QAction>(tr("X Direction"));
    yDirection=make_unique<QAction>(tr("Y Direction"));
    zDirection=make_unique<QAction>(tr("Z Direction"));
    end=make_unique<QAction>(tr("End"));
    xDirection->setCheckable(true);
    yDirection->setCheckable(true);
    zDirection->setCheckable(true);
    addAction(SetFixed.get());
    addAction(Compute.get());
    addAction(xDirection.get());
    addAction(yDirection.get());
    addAction(zDirection.get());
    addAction(end.get());
}

};