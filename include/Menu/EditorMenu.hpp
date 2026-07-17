#pragma once 
#include<QtWidgets/QMenu>
#include<QtWidgets/QWidget>
#include<memory>
using namespace std;
class EditorMenu:public QMenu{
public:
std::unique_ptr<QAction> enableCADView;
std::unique_ptr<QAction> enableNodeGraph;
std::unique_ptr<QAction> enableFileSystem;
std::unique_ptr<QAction> enableChildCADView;
std::unique_ptr<QAction>enableChildNodeGraph;
std::unique_ptr<QAction> enableConsoleLog;
std::unique_ptr<QAction> themeSettings;

EditorMenu():QMenu(){
    enableCADView=make_unique<QAction>(tr("CAD View"),nullptr);
    enableNodeGraph=make_unique<QAction>(tr("NodeGraph"),nullptr);
    enableFileSystem=make_unique<QAction>(tr("File System"),nullptr);
    enableChildCADView=make_unique<QAction>(tr("Other View"),nullptr);
    enableChildNodeGraph=make_unique<QAction>(tr("Other Node Graph"),nullptr);
    enableConsoleLog=std::make_unique<QAction>(tr("Console Log"));
    themeSettings=std::make_unique<QAction>(tr("Theme"));
    enableCADView->setCheckable(true);
    enableNodeGraph->setCheckable(true);
    enableFileSystem->setCheckable(true);
    enableChildCADView->setCheckable(true);
    enableChildNodeGraph->setCheckable(true);
    enableConsoleLog->setCheckable(true);
    addAction(enableCADView.get());
    addAction(enableNodeGraph.get());
    addAction(enableFileSystem.get());
    addAction(enableChildCADView.get());
    addAction(enableChildNodeGraph.get());
    addAction(enableConsoleLog.get());
    addAction(themeSettings.get());
}

};






