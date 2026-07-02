#ifndef IMAGE_PANE_HPP
#define IMAGE_PANE_HPP
#include<QtWidgets/QWidget>
#include<QtGui/QPainter>
#include<QtGui/QImage>
#include<ImageMenu.hpp>
#include<QtGui/QMouseEvent>
#include<QtWidgets/QFileDialog>
#include<QtGui/QPainterPath>
///This is to draw an image on a widget of a particular size.....
class ImagePane:public QWidget{
private: //by default 30 X 30 Image
Q_OBJECT
QImage loadedimage;
QString filePath;
QString Error;   //this will store the error result
int width=30;
int height=30;
std::unique_ptr<ImageMenu> imageMenu;
public:
ImagePane(QWidget* parent=nullptr):QWidget(parent){
    setAutoFillBackground(true);
    imageMenu=std::make_unique<ImageMenu>();
    connect(imageMenu->loadImageAction.get(),&QAction::triggered,this,&ImagePane::OnHandleLoadImage);
    setFixedSize(width,height);
    update();
}
ImagePane(const QString& file_name,QWidget* parent):QWidget(parent){
setAutoFillBackground(true);
 imageMenu=std::make_unique<ImageMenu>();
loadedimage.load(file_name,nullptr);

if(loadedimage.isNull()){
    Error=QString(tr("Failed to load image,check the supported file format or the file path"));
    return;
}
 connect(imageMenu->loadImageAction.get(),&QAction::triggered,this,&ImagePane::OnHandleLoadImage);
 update();
}
QImage LoadedImage() const{
  return loadedimage;
}
void SetWidth(const int& w){
  width=w;
}
void SetHeight(const int& h){
  height=h;
}
int Width() const{
  return width;
}
int Height() const{
  return height;
}
QString ErrorMessage() const{
  return Error;
}
void Update(){
  if(!loadedimage.isNull()){
     update();
  }
  return;
}
void LoadImage(const QString& imageFile){
  loadedimage.load(imageFile,nullptr);
  if(loadedimage.isNull()){

    SetErrorMessage(tr("Failed To load Image"));
    return;
  }
  filePath=imageFile;
  Update();
  return;
}
void SetErrorMessage(const QString& message){
  Error=message;
  return;
}
void SetFilePath(const QString& filename){
  filePath=filename;
  return;
}
QString FilePath() const{
  return filePath;
}
protected:
void paintEvent(QPaintEvent* event) override{
    QPainter painter(this);
    painter.setBackground(QBrush(Qt::white));
    if(!loadedimage.isNull()){
      
    
    painter.drawImage(QRect(0,0,width,height),loadedimage);
    }
    else{
      QPainterPath path;
   QPen pen(Qt::white); 
   painter.setBrush(QBrush(Qt::white));
   QRectF rectf(static_cast<float>(rect().x()),static_cast<float>(rect().y()),static_cast<float>(size().width()),static_cast<float>(size().height()));
  path.addRoundedRect(rectf,5.0,5.0);
  painter.fillPath(path,painter.brush());
  painter.setClipPath(path);
   painter.strokePath(path,pen);
  }
  return;  
}
void mousePressEvent(QMouseEvent* event) override{
  if(event->button()==Qt::RightButton){
     imageMenu->exec(event->globalPosition().toPoint());
     
  }

  return;
}
signals:
void EmitImageInfo(const QImage& image);
public slots:

void OnHandleLoadImage(){
   QFileDialog dialog(nullptr,tr("Node Image Selector"),QDir::homePath(),tr("Image Files (*.jpeg) (*.jpg) (*.png)"));
   dialog.setFileMode(QFileDialog::ExistingFiles);
   if(dialog.exec()){
    auto filename=dialog.selectedFiles().first(); //first chosen file
    LoadImage(filename);
    filePath=filename;
    emit EmitImageInfo(loadedimage);
   }
  return;
}
};







#endif