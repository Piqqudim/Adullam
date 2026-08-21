#pragma once
#include<QMenu>
#include<memory>
#include<QAction>
using  namespace std;
class CreatePlaneMenu:public QMenu{
public:
unique_ptr<QAction> choosePoint;
unique_ptr<QAction> setX;
unique_ptr<QAction> setY;
unique_ptr<QAction> setTrans;
unique_ptr<QAction> setColor;
unique_ptr<QAction> Build; //this helps us to build and rebuild plane
unique_ptr<QAction> end;

public:
CreatePlaneMenu(){
    choosePoint=make_unique<QAction>(tr("Choose Point")); //this calculates from the midpoint to the chosen position
    choosePoint->setCheckable(true);
    setX=make_unique<QAction>(tr("Set X"));
    setX->setCheckable(true);
    setY=make_unique<QAction>(tr("Set Y"));
    setY->setCheckable(true);
    setTrans=make_unique<QAction>(tr("Set Transparency"));
    setColor=make_unique<QAction>(tr("Set Color"));
    Build=make_unique<QAction>(tr("Build"));
    end=make_unique<QAction>(tr("End"));
    addAction(choosePoint.get());
    addAction(setX.get());
    addAction(setY.get());
    addAction(setTrans.get());
    addAction(setColor.get());
    addAction(Build.get());
    addAction(end.get());
    return;
}

};