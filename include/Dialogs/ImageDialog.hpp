#pragma once
#include<QtWidgets/QDialog>
#include<ImageUtil.hpp>
#include<QtWidgets/QFormLayout>
#include<QtWidgets/QDialogButtonBox>
#include<Section.h>
#include<ImagePane.hpp>
#include<QtWidgets/QLabel>
#include<QtWidgets/QLineEdit>
#include<QtWidgets/QPushButton>
#include<Image_AlienPixMap.hxx>
#include<memory>
using namespace std;
using namespace IMAGE;
class ImageDialog:public QDialog{
private:
Q_OBJECT
std::unique_ptr<ImagePane> imagepane;
std::unique_ptr<QFormLayout> flayout;
std::unique_ptr<QFormLayout> flayout_1;
std::unique_ptr<QVBoxLayout> vlayout;
std::unique_ptr<QLabel> FormatType;
std::unique_ptr<QLabel> heightLabel;
std::unique_ptr<QLabel> widthLabel;
std::unique_ptr<QLabel> depthLabel;
std::unique_ptr<QLabel> sizeLabel;
std::unique_ptr<QLabel> aspectratiolabel;
std::unique_ptr<QLineEdit> filenameEdit;
std::unique_ptr<Section> imagePropSection;
std::unique_ptr<Section> imageSection;
std::unique_ptr<QDialogButtonBox> buttons;
std::unique_ptr<QPushButton> loadbutton;
Handle(Image_AlienPixMap) pixmapImage;
QImage outputImage;
QString filePath;
int h=-1;
int w=-1;
public:
ImageDialog():QDialog(){
setWindowTitle(tr("Image Dialog"));
pixmapImage=new Image_AlienPixMap();
imagepane=std::make_unique<ImagePane>();
flayout=std::make_unique<QFormLayout>();
flayout_1=std::make_unique<QFormLayout>();
vlayout=std::make_unique<QVBoxLayout>();
vlayout->setAlignment(Qt::AlignTop|Qt::AlignTop);
FormatType=std::make_unique<QLabel>(tr("Image_Format_Unknown"));
heightLabel=std::make_unique<QLabel>(tr("0"));
widthLabel=std::make_unique<QLabel>(tr("0"));
depthLabel=std::make_unique<QLabel>(tr("0"));
sizeLabel=std::make_unique<QLabel>(tr("0"));
aspectratiolabel=std::make_unique<QLabel>(tr("0.0"));
filenameEdit=std::make_unique<QLineEdit>(tr("...."));
filenameEdit->setReadOnly(true);
filenameEdit->setPlaceholderText(tr("Image File name"));
imagePropSection=std::make_unique<Section>(tr("Image Property"));
flayout->addRow(tr("Format Type:"),FormatType.get());
flayout->addRow(tr("Height:"),heightLabel.get());
flayout->addRow(tr("Width:"),widthLabel.get());
flayout->addRow(tr("Depth:"),depthLabel.get());
flayout->addRow(tr("Size:"),sizeLabel.get());
flayout->addRow(tr("Aspect Ratio"),aspectratiolabel.get());
loadbutton=std::make_unique<QPushButton>(tr("Load"));

imagePropSection->setContentLayout(*flayout.get());
imageSection=std::make_unique<Section>(tr("Image Preview"));
flayout_1->addRow(tr("Image:"),imagepane.get());
flayout_1->addRow(tr("File Path:"),filenameEdit.get());
flayout_1->addRow(tr("Load Image"),loadbutton.get());
imageSection->setContentLayout(*flayout_1.get());
vlayout->addWidget(imageSection.get());
vlayout->addWidget(imagePropSection.get());
buttons=std::make_unique<QDialogButtonBox>(QDialogButtonBox::Ok|QDialogButtonBox::Cancel);
vlayout->addWidget(buttons.get());
connect(buttons.get(),QDialogButtonBox::rejected,this,&ImageDialog::OnHandleCancel);
connect(buttons.get(),QDialogButtonBox::accepted,this,&ImageDialog::OnHandleOk);
connect(imagepane.get(),&ImagePane::EmitImageInfo,this,&ImageDialog::OnHandleSentImage);
connect(loadbutton.get(),&QPushButton::clicked,this,&ImageDialog::OnHandlePushButton);
setLayout(vlayout.get());
// current text and current
}
void LoadImage(const QString& filename){
    if(imagepane){
        imagepane->LoadImage(filename);
    }
   pixmapImage->Load(filename.toStdString().c_str());

    return;
}
Handle(Image_AlienPixMap) Pixmap() const{
     return pixmapImage;
}
QImage OutputImage() const{
    return outputImage;
}
int Height() const{
    return h;
}
int Width() const{
    return w;
}
signals:
void EmitDone();



public slots:
void OnHandleOk(){
   emit EmitDone();
   accept();
    return;
}
void OnHandleCancel(){
    reject();
    return;
}
void OnHandlePushButton(){
    QFileDialog fdialog(this,tr("Node Image Selector"),QDir::homePath(),tr("Image Files (*.jpeg)(*.jpg) (*.png)"));
    fdialog.setFileMode(QFileDialog::ExistingFiles);
    if(fdialog.exec()){
     QString filename=fdialog.selectedFiles().first(); 
     LoadImage(filename);
    }
    if(!imagepane->LoadedImage().isNull()){
        OnHandleSentImage(imagepane->LoadedImage());
        outputImage=imagepane->LoadedImage();
    }
    return;
}
void OnHandleSentImage(const QImage& im){
    heightLabel->setText(QString::number(im.height()));
    widthLabel->setText(QString::number(im.width()));
    depthLabel->setText(QString::number(im.depth()));
    FormatType->setText(FromFormatToString(pixmapImage->Format()));
    int multiplicity=im.height()*im.width();
    sizeLabel->setText(QString::number(multiplicity)+QString("pixels"));
    filenameEdit->setText(imagepane->FilePath());
    aspectratiolabel->setText(QString::number(pixmapImage->Ratio()));
    h=im.height();
    w=im.width();
    outputImage=im;
    return;
}

};