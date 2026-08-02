#pragma once
#include<QtWidgets/QTextEdit>
#include<memory>
#include<QtGui/QAction>
#include<QtWidgets/QMenu>
#include<QtWidgets/QFileDialog>
#include<QApplication>
#include<QtCore/QFile>
#include<QtGui/QContextMenuEvent>
#include<QtWidgets/QInputDialog>
#include<InfoUtility.hpp>
#include<QFontDialog>
#include<QJsonObject>
#include<QJsonDocument>
#include<iostream>
using namespace std;
using namespace INFO;
enum StyleEditMode{
SEM_VIEW,
SEM_CONN,
SEM_NODE,
SEM_NULL
};
class StyleSheetEditor:public QTextEdit{
   Q_OBJECT
public:
 QString FileContent;
 QString defaultStyleSheet;
 QString connStyleString;
 QString nodeStyleString;
 QString viewStyleString;
StyleEditMode sem=SEM_NULL;
 std::unique_ptr<QAction> clearAction;
 std::unique_ptr<QAction> compile;
 std::unique_ptr<QAction> compileAction;
 std::unique_ptr<QMenu> compileMenu;
 std::unique_ptr<QAction> compileNodeStyle;
 std::unique_ptr<QAction> compileConnStyle;
 std::unique_ptr<QAction> compileViewStyle;
 std::unique_ptr<QMenu> loadMenu;
 std::unique_ptr<QAction>load;
 std::unique_ptr<QAction> loadNodeStyle;
 std::unique_ptr<QAction> loadConnStyle;
 std::unique_ptr<QAction> loadViewStyle;
 std::unique_ptr<QAction> loadAction;
 std::unique_ptr<QMenu> saveMenu;
 std::unique_ptr<QAction> saveNodeStyle;
 std::unique_ptr<QAction> saveConnStyle;
 unique_ptr<QAction> saveViewStyle;
 std::unique_ptr<QAction> save;
 std::unique_ptr<QAction> saveAction;
 std::unique_ptr<QAction> loadDefaultStyle;
 std::unique_ptr<QAction> changeFont;
 std::unique_ptr<QAction> show;
 std::unique_ptr<QMenu> showMenu;
 std::unique_ptr<QAction> showViewStyleTemplate;
 std::unique_ptr<QAction> showConnStyleTemplate;
 std::unique_ptr<QAction> showNodeStyleTemplate;
 std::unique_ptr<QAction> showPrevNode;//this shows the previous node style
 std::unique_ptr<QAction> showPrevConn;
 std::unique_ptr<QAction> showPrevView;
 std::unique_ptr<QAction> showPrevStyle;
 std::unique_ptr<QAction> showCurrentCompileMode;
 QMenu* menu=nullptr;
 

 
 public:
 StyleSheetEditor(QWidget* widget=nullptr):QTextEdit(widget){
    setLineWrapMode(QTextEdit::NoWrap);
    QApplication* app=dynamic_cast<QApplication*>(QApplication::instance());
    if(app){
      defaultStyleSheet=app->styleSheet();
      append(app->styleSheet());
    }
    compile=std::make_unique<QAction>(tr("Compile"));
    compileAction=std::make_unique<QAction>(tr("Compile Style Sheet"));
    compileNodeStyle=std::make_unique<QAction>(tr("Compile Node Style"));
    compileConnStyle=make_unique<QAction>(tr("Compile Connection Style"));
    compileViewStyle=make_unique<QAction>(tr("Compile View Style"));
    compileMenu=std::make_unique<QMenu>();
   compileMenu->addAction(compileAction.get());
   compileMenu->addAction(compileNodeStyle.get());
   compileMenu->addAction(compileConnStyle.get());
   compileMenu->addAction(compileViewStyle.get());
   compile->setMenu(compileMenu.get());

    load=std::make_unique<QAction>(tr("Load"));
    loadMenu=make_unique<QMenu>();
    loadNodeStyle=make_unique<QAction>(tr("Load NodeStyle"));
    loadConnStyle=make_unique<QAction>(tr("Load ConnectionStyle"));
    loadAction=std::make_unique<QAction>(tr("Load StyleSheet"));
    loadViewStyle=make_unique<QAction>(tr("Load View Style"));
    loadNodeStyle->setCheckable(true);
    loadConnStyle->setCheckable(true);
    loadViewStyle->setCheckable(true);
    loadMenu->addAction(loadNodeStyle.get());
    loadMenu->addAction(loadConnStyle.get());
    loadMenu->addAction(loadAction.get());
    loadMenu->addAction(loadViewStyle.get());
    load->setMenu(loadMenu.get());
    
   saveMenu=make_unique<QMenu>();
   save=std::make_unique<QAction>(tr("Save"));
   saveAction=std::make_unique<QAction>(tr("Save StyleSheet"));
   saveNodeStyle=std::make_unique<QAction>(tr("Save Node Style"));
   saveConnStyle=std::make_unique<QAction>(tr("Save Connection Style"));
   saveViewStyle=std::make_unique<QAction>(tr("Save View Style"));
   saveMenu->addAction(saveAction.get());
   saveMenu->addAction(saveNodeStyle.get());
   saveMenu->addAction(saveConnStyle.get());
   saveMenu->addAction(saveViewStyle.get());
   save->setMenu(saveMenu.get());

   show=make_unique<QAction>(tr("Show"));
   showMenu=make_unique<QMenu>();
   showViewStyleTemplate=std::make_unique<QAction>(tr("Show View Style Template"));
   showConnStyleTemplate=std::make_unique<QAction>(tr("Show Connection Style Template"));
   showNodeStyleTemplate=std::make_unique<QAction>(tr("Show Node Style Template"));
   showPrevNode=std::make_unique<QAction>(tr("Show Previous Node Style")); 
   showPrevConn=std::make_unique<QAction>(tr("Show Previous Connection Style"));
   showPrevView=std::make_unique<QAction>(tr("Show Previous View Style"));
   showPrevStyle=make_unique<QAction>(tr("Show Previous Widget Style"));
   showViewStyleTemplate->setCheckable(true);
    showConnStyleTemplate->setCheckable(true);
    showNodeStyleTemplate->setCheckable(true);
    showCurrentCompileMode=std::make_unique<QAction>(tr("Show Compile Mode"));
   showMenu->addAction(showViewStyleTemplate.get());
   showMenu->addAction(showConnStyleTemplate.get());
   showMenu->addAction(showNodeStyleTemplate.get());
   showMenu->addAction(showPrevNode.get());
   showMenu->addAction(showPrevConn.get());
   showMenu->addAction(showPrevView.get());
   showMenu->addAction(showPrevStyle.get());
   
   show->setMenu(showMenu.get());
    clearAction=std::make_unique<QAction>(tr("Clear"));
    
    QFont font=currentFont();
    font.setPointSizeF(17.0f);
    setCurrentFont(font);

   changeFont=std::make_unique<QAction>(tr("Modify Font"));
   loadDefaultStyle=std::make_unique<QAction>(tr("Load Default Style"));
   menu=createStandardContextMenu();
   menu->addAction(clearAction.get());
   menu->addAction(compile.get());
   menu->addAction(load.get());
   menu->addAction(save.get());
   menu->addAction(show.get());
   menu->addAction(loadDefaultStyle.get());
   menu->addAction(changeFont.get());
   menu->addAction(showCurrentCompileMode.get());
    connect(clearAction.get(),&QAction::triggered,this,&StyleSheetEditor::Clear);
    connect(compileAction.get(),&QAction::triggered,this,&StyleSheetEditor::Compile);
    connect(loadAction.get(),&QAction::triggered,this,&StyleSheetEditor::Load);
    connect(saveAction.get(),&QAction::triggered,this,&StyleSheetEditor::SaveFile);
    connect(loadDefaultStyle.get(),&QAction::triggered,this,&StyleSheetEditor::LoadDefault);
    connect(changeFont.get(),&QAction::triggered,this,&StyleSheetEditor::OnModifyFont);
    connect(showCurrentCompileMode.get(),QAction::triggered,this,&StyleSheetEditor::ShowCompileMode);
    connect(compileConnStyle.get(),&QAction::triggered,this,&StyleSheetEditor::CompileConnectionStyle);
    connect(compileNodeStyle.get(),&QAction::triggered,this,&StyleSheetEditor::CompileNodeStyle);
    connect(compileViewStyle.get(),&QAction::triggered,this,&StyleSheetEditor::CompileViewStyle);
    connect(loadNodeStyle.get(),&QAction::toggled,this,&StyleSheetEditor::LoadNodeStyle);
    connect(loadConnStyle.get(),&QAction::toggled,this,&StyleSheetEditor::LoadConnStyle);
    connect(loadViewStyle.get(),&QAction::toggled,this,&StyleSheetEditor::LoadViewStyle);
    connect(saveNodeStyle.get(),&QAction::triggered,this,&StyleSheetEditor::SaveNodeStyle);
   connect(saveConnStyle.get(),&QAction::triggered,this,&StyleSheetEditor::SaveNodeStyle);
   connect(saveViewStyle.get(),&QAction::triggered,this,&StyleSheetEditor::SaveNodeStyle);
   connect(showPrevNode.get(),&QAction::triggered,this,&StyleSheetEditor::ShowPrevNodeStyle);
   connect(showPrevConn.get(),&QAction::triggered,this,&StyleSheetEditor::ShowPrevConnStyle);
   connect(showPrevView.get(),QAction::triggered,this,&StyleSheetEditor::ShowPrevView);
   connect(showPrevStyle.get(),&QAction::triggered,this,StyleSheetEditor::ShowPrevStyle);
   
    return;
 }
 void SetToBoolValue(bool val,bool val1,bool val2){
   showViewStyleTemplate->setChecked(val);
   showConnStyleTemplate->setChecked(val1);
   showNodeStyleTemplate->setChecked(val2);
   return;
 }
 void SetLoadBoolValue(bool val,bool val1,bool val2){
   loadNodeStyle->setChecked(val);
   loadConnStyle->setChecked(val1);
   loadViewStyle->setChecked(val2);
   return;
 }
void SetFileContent(const QString& str){
   FileContent=str;
   return;
}
void SetFileContentBasedOnMode(){
   switch(sem){
      case SEM_VIEW:{
         viewStyleString=toPlainText();
         break;
      }
      case SEM_CONN:{
         connStyleString=toPlainText();
         break;
      }
      case SEM_NODE:{
         nodeStyleString=toPlainText();
         break;
      }
      case SEM_NULL:{
         FileContent=toPlainText();
         break;
      }
      default:
      break;
   }
   return;
}
void SetStyleEditMode(const StyleEditMode& mode){
   sem=mode;
   return;
}
void LoadFile(const QString& filestring){
   SetFileContentBasedOnMode();
   clear(); //clear before appending string
   setText(filestring);
   
   return;
 }
~StyleSheetEditor(){
   if(menu){
      delete menu;
      menu=nullptr;
   }
}
protected:
void contextMenuEvent(QContextMenuEvent* event){
   if(menu){
      menu->exec(event->globalPos());
   }
   return;
}
signals:
void EmitViewStyle(const QJsonObject& object);
void EmitConnectionStyle(const QJsonObject& object);
void EmitNodeStyle(const QJsonObject& object);
public slots:
void OnModifyFont(){
   bool Ok;
   QFont font=QFontDialog::getFont(&Ok,currentFont(),nullptr,tr("Node Font Dialog"));
   if(!Ok){
      return;
   }
   setCurrentFont(font);
   return;
}
void LoadDefault(){
   QApplication* app=dynamic_cast<QApplication*>(QApplication::instance());
   if(app){
     app->setStyleSheet(defaultStyleSheet);
     LoadFile(defaultStyleSheet);
   }
   SetStyleEditMode(SEM_NULL);
   SetToBoolValue(false,false,false);
   return;
}
void SaveFile(){
   //firstly write the name of the file that you want to save
   //choose a directory to which you want to save
   //after choosing a directory
   //append the results to it
   bool Ok;
   QString filename=QInputDialog::getText(nullptr,tr("Save QStyleSheet"),tr("FileName"),QLineEdit::Normal,tr(""),&Ok);
   if(!Ok){
      return;
   }
   if(filename.isEmpty()){
      return;
   }
   LoadMessage(tr(""),tr("Select Folder in which you will store the named file"));
   //at this point,i have gotten the file name,
   QFileDialog dialog(nullptr,tr("Save StyleSheet"),QString(),tr(""));
   dialog.setFileMode(QFileDialog::Directory);
   QString FileDir;
   if(dialog.exec()){
    FileDir=dialog.selectedFiles().first();
   }
   if(FileDir.isEmpty()){
      return;
   }
   QFile file(FileDir+"/"+filename);
   FileContent=toPlainText();
   QByteArray contentArray=QByteArray::fromRawData(FileContent.toStdString().c_str(),FileContent.toStdString().size());
   if(contentArray.isEmpty()){
    LoadMessage(tr(""),tr("Failed to write content of stylesheeteditor"));
      return;
   }
   if(file.open(QIODevice::Truncate|QIODevice::WriteOnly)){
      file.write(contentArray);
      file.close();
   }
   return;
}
void Load(){
  QFileDialog dialog(nullptr,tr("Open StyleSheet"),QString(),tr(""));
  dialog.setFileMode(QFileDialog::ExistingFiles);
  QString filePath;
  if(dialog.exec()){
   filePath=dialog.selectedFiles().first();
  }
  if(filePath.isEmpty()){
   return;
  }
  QFile file(filePath);
  if(file.open(QIODevice::ReadOnly)){
   auto bytearray=file.readAll();
  
   LoadFile(bytearray.toStdString().c_str());
   SetStyleEditMode(SEM_NULL);
   file.close();
  }
  return;
}
 void Compile(){
  if(sem!=SEM_NULL){
     LoadMessage(tr(""),tr("The Content of the Style Editor is not a Widget Style Sheet,So cannot compile"));
     return;
  }
  QApplication* app=dynamic_cast<QApplication*>(QApplication::instance());
  
  FileContent=toPlainText();
  if(app){
   app->setStyleSheet(FileContent);
  }
   return; 
 }
 void CompileNodeStyle(){
   if(sem!=SEM_NODE){
      LoadMessage(tr(""),tr("The Content of the Style Editor is not a Node Style Sheet,So cannot compile")); 
      return;
   }
    if(toPlainText().isEmpty()){
      LoadMessage(tr(""),tr("Style Sheet Editor is Empty"));
      return;
   }
   nodeStyleString=toPlainText();
   QByteArray bytearray;
   bytearray=QByteArray::fromStdString(nodeStyleString.toStdString());
   QJsonDocument jsondoc=QJsonDocument::fromJson(bytearray);
    cout<<"Before Sending"<<"\n";
    PrintToCout(jsondoc.object());
      emit EmitNodeStyle(jsondoc.object());
   
   return;
 }
  void CompileConnectionStyle(){
  if(sem!=SEM_CONN){
   LoadMessage(tr(""),tr("The Content is not connection styl sheet,therefore, cannot compile"));
   return;
  }
  if(toPlainText().isEmpty()){
      LoadMessage(tr(""),tr("Style Sheet Editor is Empty"));
      return;
   }
   connStyleString=toPlainText();
   QByteArray bytearray;
   bytearray=QByteArray::fromStdString(connStyleString.toStdString());
   QJsonDocument jsondoc=QJsonDocument::fromJson(bytearray);
   cout<<"Before Sending"<<"\n";
    PrintToCout(jsondoc.object());
      emit EmitConnectionStyle(jsondoc.object());
   
   return;
 }
  void CompileViewStyle(){
   if(sem!=SEM_VIEW){
       LoadMessage(tr(""),tr("The Content of the Style Editor is not a View Style Sheet,So cannot compile"));
      return;
   }
   if(toPlainText().isEmpty()){
      LoadMessage(tr(""),tr("Style Sheet Editor is Empty"));
      return;
   }
   viewStyleString=toPlainText();
   QByteArray bytearray;
   bytearray=QByteArray::fromStdString(viewStyleString.toStdString());
   QJsonDocument jsondoc=QJsonDocument::fromJson(bytearray);
      cout<<"Before Sending"<<"\n";
    PrintToCout(jsondoc.object());
      emit EmitViewStyle(jsondoc.object());
   
   return;
 }
 void PrintToCout(const QJsonObject& object){
  QJsonDocument jsondoc(object);
  std::cout<<"\n";
  std::cout<<jsondoc.toJson().toStdString()<<"\n";
 

return;
}
 void LoadNodeStyle(bool value){
  if(value){
  QFileDialog dialog(nullptr,tr("Open Json File"),QString(),tr("*.json"));
  dialog.setFileMode(QFileDialog::ExistingFiles);
  QString filePath;
  if(dialog.exec()){
   filePath=dialog.selectedFiles().first();
  }
  if(filePath.isEmpty()){
   return;
  }
  QFile file(filePath);
  if(file.open(QIODevice::ReadOnly)){
   auto bytearray=file.readAll();
   
   SetLoadBoolValue(true,false,false);
   LoadFile(bytearray.toStdString().c_str());
   SetStyleEditMode(SEM_NODE);
   file.close();
  }
  }
   //Load
   
   return;
 }

void LoadConnStyle(bool value){
  if(value){
  QFileDialog dialog(nullptr,tr("Open Json File"),QString(),tr("*.json"));
  dialog.setFileMode(QFileDialog::ExistingFiles);
  QString filePath;
  if(dialog.exec()){
   filePath=dialog.selectedFiles().first();
  }
  if(filePath.isEmpty()){
   return;
  }
  QFile file(filePath);
  if(file.open(QIODevice::ReadOnly)){
   auto bytearray=file.readAll();
   SetLoadBoolValue(false,true,false);
   LoadFile(bytearray.toStdString().c_str());
   SetStyleEditMode(SEM_CONN);
   file.close();
  }
  }
   //Load
   
   return;
 }

void LoadViewStyle(bool value){
  if(value){
  QFileDialog dialog(nullptr,tr("Open Json File"),QString(),tr("*.json"));
  dialog.setFileMode(QFileDialog::ExistingFiles);
  QString filePath;
  if(dialog.exec()){
   filePath=dialog.selectedFiles().first();
  }
  if(filePath.isEmpty()){
   return;
  }
  QFile file(filePath);
  if(file.open(QIODevice::ReadOnly)){
   auto bytearray=file.readAll();
   
   SetLoadBoolValue(false,false,true);
   LoadFile(bytearray.toStdString().c_str());
   SetStyleEditMode(SEM_VIEW);
   file.close();
  }
  }
   //Load
   
   return;
 }
 
 void SaveNodeStyle(){
   bool Ok;
    QString filename=QInputDialog::getText(nullptr,tr("Save Json File"),tr("FileName"),QLineEdit::Normal,tr(""),&Ok);
   if(!Ok){
      return;
   }
   if(filename.isEmpty()){
      return;
   }
   if(!filename.endsWith(".json")){
      filename=filename+QString(".json");
   }
   LoadMessage(tr(""),tr("Select Folder in which you will store the named file"));
   //at this point,i have gotten the file name,
   QFileDialog dialog(nullptr,tr("Save Json File"),QString(),tr(""));
   dialog.setFileMode(QFileDialog::Directory);
   QString FileDir;
   if(dialog.exec()){
    FileDir=dialog.selectedFiles().first();
   }
   if(FileDir.isEmpty()){
      return;
   }
   QFile file(FileDir+"/"+filename);
    QByteArray contentArray;
    switch(sem){
      case SEM_VIEW:{
      viewStyleString=toPlainText();
      contentArray=QByteArray::fromStdString(viewStyleString.toStdString());
      break;
      }
      case SEM_CONN:{
         connStyleString=toPlainText();
         contentArray=QByteArray::fromStdString(connStyleString.toStdString());
         break;
      } 
      case SEM_NODE:{
         viewStyleString=toPlainText();
         contentArray=QByteArray::fromStdString(nodeStyleString.toStdString());

         break;
      }
      default:
       break;
    }
  
   if(contentArray.isEmpty()){
    LoadMessage(tr(""),tr("Failed to write the content of stylesheeteditor"));
      return;
   }
   if(file.open(QIODevice::Truncate|QIODevice::WriteOnly)){
      file.write(contentArray);
      file.close();
   }
   return;
 }
 void ShowCompileMode(){
  switch(sem){
  case SEM_NULL:{
     LoadMessage(tr(""),tr("Widget Style Sheet"));
     break;
  }
  case SEM_VIEW:{
   LoadMessage(tr(""),tr("View Style Sheet"));
   break;
  }
   case SEM_CONN:{
     LoadMessage(tr(""),tr("Connection Style Sheet"));
     break;
  }
   case SEM_NODE:{
     LoadMessage(tr(""),tr("Node Style Sheet"));
     break;
  }
  return;
 }
 }
 void Clear(){
   clear();
   return;
 }
 void ShowPrevNodeStyle(){
    LoadFile(nodeStyleString);
    SetStyleEditMode(SEM_NODE);
    return;
 }
void ShowPrevConnStyle(){
   LoadFile(connStyleString);
   SetStyleEditMode(SEM_CONN);
   return;
 }
void ShowPrevView(){
  LoadFile(viewStyleString);
  SetStyleEditMode(SEM_VIEW);
  return;
}
void ShowPrevStyle(){
   LoadFile(FileContent);
  SetStyleEditMode(SEM_NULL);
   return;
}

};