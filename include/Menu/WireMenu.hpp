#pragma once
#include<QtWidgets/QMenu>
#include<memory>
using namespace std;


class WireMenu:public QMenu{
public:
std::unique_ptr<QAction> convertToNode;
std::unique_ptr<QAction> convertToFace;
std::unique_ptr<QAction> convertToPointNode;
std::unique_ptr<QAction> applyFillet; //this allows you select two edges of the wire and apply fillet to it
std::unique_ptr<QAction> applyFilletToAll; //this applies to all edges of all wire..
std::unique_ptr<QAction> chooseVertex;
std::unique_ptr<QAction> chooseRadius;
std::unique_ptr<QAction> endWireMenu;
public:
WireMenu(){
    convertToNode=std::make_unique<QAction>(tr("Convert"));
    convertToNode->setCheckable(true);
    applyFillet=std::make_unique<QAction>(tr("Apply Fillet"));
    applyFilletToAll=std::make_unique<QAction>(tr("Apply Fillet To all"));
    convertToFace=std::make_unique<QAction>(tr("Convert To Face"));
    applyFillet->setCheckable(true);
    applyFilletToAll->setCheckable(true);
    chooseVertex=std::make_unique<QAction>(tr("Choose Vertex"));
    chooseVertex->setCheckable(true);
    convertToPointNode=std::make_unique<QAction>(tr("Convert To Point Node"));
    chooseRadius=std::make_unique<QAction>(tr("Choose Radius"));
    convertToPointNode->setCheckable(true);
    endWireMenu=std::make_unique<QAction>(tr("End Wire Menu"));
    addAction(convertToNode.get());
    addAction(convertToFace.get());
    addAction(convertToPointNode.get());
    addAction(applyFillet.get());
    addAction(applyFilletToAll.get());
    addAction(chooseVertex.get());
    addAction(chooseRadius.get());
    addAction(endWireMenu.get());
}
};

class WireFilletMenu:public QMenu{
public:
std::unique_ptr<QAction> selectFirstEdge=std::make_unique<QAction>(tr("Select First Edge"));
std::unique_ptr<QAction> selectSecondEdge=std::make_unique<QAction>(tr("Select Second Edge"));
std::unique_ptr<QAction> endOps=std::make_unique<QAction>(tr("End Operation"));
std::unique_ptr<QAction> build=std::make_unique<QAction>(tr("Build"));
std::unique_ptr<QAction> selectRadius=std::make_unique<QAction>(tr("Select Radius"));
std::unique_ptr<QAction> selectPoint=std::make_unique<QAction>(tr("Select Vertex"));
WireFilletMenu(){
    selectFirstEdge->setCheckable(true);
    selectSecondEdge->setCheckable(true);
    selectPoint->setCheckable(true);
    addAction(selectFirstEdge.get());
    
    addAction(selectSecondEdge.get());
    addAction(selectPoint.get());
    addAction(selectRadius.get());
    addAction(endOps.get());
    addAction(build.get());
    return;
}
};