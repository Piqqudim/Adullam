#pragma once
#include<QtWidgets/QMenu>
#include<memory>
class FaceMenu:public QMenu{
public:
std::unique_ptr<QAction> showInfoAction;
std::unique_ptr<QAction> assumeFaceNormal;
std::unique_ptr<QAction> computeFacePlane;
std::unique_ptr<QAction> applyFillet;
std::unique_ptr<QAction> applyChamfer;
std::unique_ptr<QAction> convertAction;
std::unique_ptr<QAction> searchAction;
std::unique_ptr<QAction> DrawAction;

FaceMenu():QMenu(){
    showInfoAction=std::make_unique<QAction>(tr("Show Info"),nullptr);
    convertAction=std::make_unique<QAction>(tr("Convert To Face Node"),nullptr);
    convertAction->setCheckable(true);
    searchAction=std::make_unique<QAction>(tr("Find In NodeGraph"),nullptr);
    DrawAction=std::make_unique<QAction>(tr("Draw Line"),nullptr);
    assumeFaceNormal=std::make_unique<QAction>(tr("Assume Face Normal"),nullptr);
    applyFillet=std::make_unique<QAction>(tr("Apply Fillet"));
    applyFillet->setCheckable(true);
    applyChamfer=std::make_unique<QAction>(tr("Apply Chamfer"));
    applyChamfer->setCheckable(true);
    computeFacePlane=std::make_unique<QAction>(tr("Compute Face Plane"));
    addAction(searchAction.get());
    addAction(computeFacePlane.get());
    addAction(assumeFaceNormal.get());
    addAction(showInfoAction.get());
    addAction(applyFillet.get());
    addAction(applyChamfer.get());
    addAction(convertAction.get());
    addAction(DrawAction.get());
}
};

class ApplyFilletMenu:public QMenu{
 public:
 std::unique_ptr<QAction> chooseVertexAction; //set checkable 
 std::unique_ptr<QAction> SelectRadiusAction; //set checkable
 std::unique_ptr<QAction> BuildFilletAction; //normal click
 std::unique_ptr<QAction> endFilletOps;  //normal click

public:
ApplyFilletMenu(){
    chooseVertexAction=std::make_unique<QAction>(tr("Choose Vertex"));
    chooseVertexAction->setCheckable(true);
    SelectRadiusAction=std::make_unique<QAction>(tr("Choose Radius"));
    
    BuildFilletAction=std::make_unique<QAction>(tr("Build"));
    endFilletOps=std::make_unique<QAction>(tr("End Fillet Operations"));
    addAction(chooseVertexAction.get());
    addAction(SelectRadiusAction.get());
    addAction(BuildFilletAction.get());
    addAction(endFilletOps.get());
}
};

class ApplyChamferMenu:public QMenu{
public:
std::unique_ptr<QAction> chooseVertexAction;
std::unique_ptr<QAction> chooseEdgeAction;
std::unique_ptr<QAction> SelectOthersAction;
std::unique_ptr<QAction> BuildAction;
std::unique_ptr<QAction> endChamferOps;

ApplyChamferMenu(){
    chooseVertexAction=std::make_unique<QAction>(tr("Choose Vertex"));
    chooseVertexAction->setCheckable(true);
    chooseEdgeAction=std::make_unique<QAction>(tr("Choose Edge"));
    chooseEdgeAction->setCheckable(true);
    SelectOthersAction=std::make_unique<QAction>(tr("Select Other Value"));
    BuildAction=std::make_unique<QAction>(tr("Build "));
    endChamferOps=std::make_unique<QAction>(tr("End Chamfer Operation"));
    addAction(chooseVertexAction.get());
    addAction(chooseEdgeAction.get());
    addAction(SelectOthersAction.get());
    addAction(BuildAction.get());
    addAction(endChamferOps.get());
}
};


