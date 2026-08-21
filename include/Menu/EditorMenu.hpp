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
std::unique_ptr<QAction> enableStyleEditor;
std::unique_ptr<QAction> enableConsoleLog;
 

EditorMenu():QMenu(){
    enableCADView=make_unique<QAction>(tr("CAD View"),nullptr);
    enableNodeGraph=make_unique<QAction>(tr("NodeGraph"),nullptr);
    enableFileSystem=make_unique<QAction>(tr("File System"),nullptr);
    enableChildCADView=make_unique<QAction>(tr("Show Inspector Widget"),nullptr);
    enableChildNodeGraph=make_unique<QAction>(tr("Show Inspector Graph"),nullptr);
    enableConsoleLog=std::make_unique<QAction>(tr("Console Log"));
    enableStyleEditor=std::make_unique<QAction>(tr("Style Editor"));
    
    enableCADView->setCheckable(true);
    enableNodeGraph->setCheckable(true);
    enableFileSystem->setCheckable(true);
    enableChildCADView->setCheckable(true);
    enableChildNodeGraph->setCheckable(true);
    enableStyleEditor->setCheckable(true);
    enableConsoleLog->setCheckable(true);
    addAction(enableCADView.get());
    addAction(enableNodeGraph.get());
    addAction(enableFileSystem.get());
    addAction(enableChildCADView.get());
    addAction(enableStyleEditor.get());
    addAction(enableChildNodeGraph.get());
    addAction(enableConsoleLog.get());
  
}

};






