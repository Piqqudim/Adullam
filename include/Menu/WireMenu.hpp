#pragma once
#include<QtWidgets/QMenu>
#include<memory>
using namespace std;


class WireMenu:public QMenu{
public:
std::unique_ptr<QAction> convertToNode;
std::unique_ptr<QAction> convertToFace;
std::unique_ptr<QAction> applyFillet; //this allows you select two edges of the wire and apply fillet to it
std::unique_ptr<QAction> applyFilletToAll; //this applies to all edges of all wire..
std::unique_ptr<QAction> chooseVertex;
std::unique_ptr<QAction> chooseRadius;

public:
WireMenu(){
    convertToNode=std::make_unique<QAction>(tr("Convert"));
    convertToNode->setCheckable(true);
    applyFillet=std::make_unique<QAction>(tr("Apply Fillet"));
    applyFilletToAll=std::make_unique<QAction>(tr("Apply Fillet To all"));
    convertToFace=std::make_unique<QAction>(tr("Convert To Face"));
    applyFilletToAll->setCheckable(true);
    chooseVertex=std::make_unique<QAction>(tr("Choose Vertex"));
    chooseVertex->setCheckable(true);
    chooseRadius=std::make_unique<QAction>(tr("Choose Radius"));

    addAction(convertToNode.get());
    addAction(convertToFace.get());
    addAction(applyFillet.get());
    addAction(applyFilletToAll.get());
    addAction(chooseVertex.get());
    addAction(chooseRadius.get());
}
};