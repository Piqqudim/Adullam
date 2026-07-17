#ifndef FILEMENU_HPP
#define FILEMENU_HPP
#include<QtWidgets/QMenu>
#include<memory>
#include<StepFileReader.hpp>
using namespace std;
class FileMenu:public QMenu{
Q_OBJECT
public:
unique_ptr<QAction> createNewFolder;
unique_ptr<QAction> openFolderAction;  //open the current working folder
unique_ptr<QAction> openNCADFile; //open .nCAD file(this stores the nodes)
unique_ptr<QAction>saveIGESModel; //save IGES model
unique_ptr<QAction>closeFolderAction; //close the current working folder
std::unique_ptr<QAction> createNewFile; //open a new file and we will save the name using 
std::unique_ptr<QAction> autoSave;
std::unique_ptr<QAction> openIGESFile;
std::unique_ptr<QAction> openStepFile;
std::unique_ptr<QAction> openSTLFile;
std::unique_ptr<QAction> saveSTLFile;
std::unique_ptr<QAction> saveSTEPFile;
std::unique_ptr<QAction> openBRepFile;
std::unique_ptr<QAction> saveBRepFile;
std::unique_ptr<QAction> openGltfFile;
std::unique_ptr<QAction> saveGltfFile;
std::unique_ptr<QAction> openObjFile;
std::unique_ptr<QAction> saveObjFile;
std::unique_ptr<QAction> openAction;
std::unique_ptr<QAction> saveAction;
std::unique_ptr<QMenu> saveMenu; 
std::unique_ptr<QMenu> openMenu;
public:
bool isStepFile=false;  //This will be used when we want to create a step file
bool isIgesFile=false;  //This will be used when we want an Iges File

FileMenu():QMenu(){
 openFolderAction=std::make_unique<QAction>(tr("Open Folder"),nullptr);
 openNCADFile=std::make_unique<QAction>(tr("Open .nCAD file"),nullptr);
 saveIGESModel=std::make_unique<QAction>(tr("Save .IGES file"),nullptr); 
 closeFolderAction=std::make_unique<QAction>(tr("Close Folder"),nullptr);
 createNewFolder=std::make_unique<QAction>(tr("Create New Folder"),nullptr);
 createNewFile=std::make_unique<QAction>(tr("Create New File"),nullptr);
 autoSave=std::make_unique<QAction>(tr("Auto Save"),nullptr);
 openIGESFile=std::make_unique<QAction>(tr("Open IGES file"));
 openStepFile=std::make_unique<QAction>(tr("Open .step/.stp file"));
 saveSTEPFile=std::make_unique<QAction>(tr("save .step/.stp file"));
 openBRepFile=std::make_unique<QAction>(tr("Open .brep file"));
 saveBRepFile=std::make_unique<QAction>(tr("save .brep file"));
 openGltfFile=std::make_unique<QAction>(tr("Open .gltf file"));
 saveGltfFile=std::make_unique<QAction>(tr("Save .gltf file"));
 openObjFile=std::make_unique<QAction>(tr("Open .Obj file"));
 saveObjFile=std::make_unique<QAction>(tr("Save .Obj file"));
 openSTLFile=std::make_unique<QAction>(tr("Open .stl file"));
 saveSTLFile=std::make_unique<QAction>(tr("Save .stl file"));
 openAction=std::make_unique<QAction>(tr("Open"));
 saveAction=std::make_unique<QAction>(tr("Save"));
 saveMenu=std::make_unique<QMenu>();
 saveAction->setMenu(saveMenu.get());
 saveMenu->addAction(saveIGESModel.get());
 saveMenu->addAction(saveSTEPFile.get());
 saveMenu->addAction(saveBRepFile.get());
 saveMenu->addAction(saveObjFile.get());
 saveMenu->addAction(saveGltfFile.get());
 saveMenu->addAction(saveSTLFile.get());

 openMenu=std::make_unique<QMenu>();
 openAction->setMenu(openMenu.get());
 openMenu->addAction(openNCADFile.get());
 openMenu->addAction(openIGESFile.get());
 openMenu->addAction(openStepFile.get());
 openMenu->addAction(openBRepFile.get());
 openMenu->addAction(openGltfFile.get());
 openMenu->addAction(openObjFile.get());
 openMenu->addAction(openSTLFile.get());
 addAction(createNewFolder.get());
 addAction(createNewFile.get());
 addAction(openFolderAction.get());
 addAction(openAction.get());
 addAction(saveAction.get());
 addAction(autoSave.get());
 addAction(closeFolderAction.get());
 return;
}
signals:
void CanOpenFileDialog(bool CanOpenFile);
void CanCreateNewFile(bool CanSaveFile);
void CanAutoSaveFile(bool CanAutoSave);

public slots:

};








#endif