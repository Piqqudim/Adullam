#pragma once
#include<QtGui/QImage>
#include<Image_AlienPixMap.hxx>
#include<QtCore/QString>
#include<InfoUtility.hpp>
using namespace INFO;
namespace IMAGE{
inline Image_Format QFormatToNativeFormat(const QImage::Format& format){
    switch(format){
        case QImage::Format_Invalid:{
            return Image_Format_UNKNOWN;
        }
        case QImage::Format_RGB32:{
            return Image_Format_RGB32;
        }
        case QImage::Format_ARGB32:{
          break;
        }
       /* case QImage::Format_ARG32_Premultiplied:{
          break;
        } */
        case QImage::Format_RGB16:{
         break;
        }
        /*
        case QImage::Format_ARGB8586_Premultiplied:{
          break;
        }
        */ 
        case QImage::Format_RGB666:{
         break;
        }
        /*
        case QImage::Format_ARGB6666_Premultiplied:{
         break;
        }
        */
        case QImage::Format_RGB555:{
            break;
        }
        /*
        case QImage::Format_ARGB8555_Premultiplied:{
         break;
        }
        */
        case QImage::Format_RGB888:{
           return Image_Format_RGB;
        }
        case QImage::Format_RGB444:{
         break;
        }
        case QImage::Format_RGBX8888:{
          break;
        }
        case QImage::Format_RGBA8888:{
          return Image_Format_RGBA;
        }
    }
     return Image_Format_UNKNOWN;
  }
inline QString FromFormatToString(const Image_Format& format){
    switch(format){
        case Image_Format_Gray:{
            return QString("Image_Format_Gray");
        }
        case Image_Format_Alpha:{
            return QString("Image_Format_Alpha");
        }
        case Image_Format_RGB:{
            return QString("Image_Format_RGB");
        }
        case Image_Format_BGR:{
            return QString("Image_Format_BGR");
        }
        case Image_Format_RGB32:{
            return QString("Image_Format_RGB32");
        }
        case Image_Format_BGR32:{
            return QString("Image_Format_BGR32");
        }
        case Image_Format_RGBA:{
            return QString("Image_Format_RGBA");
        }
        case Image_Format_BGRA:{
            return QString("Image_Format_BGRA");
        }
        case Image_Format_GrayF:{
            return QString("Image_Format_GrayF");
        }
        case Image_Format_AlphaF:{
            return QString("Image_Format_AlphaF");
        }
        case Image_Format_RGF:{
            return QString("Image_Format_RGF");
        }
        case Image_Format_RGBF:{
            return QString("Image_Format_RGBF");
        }
        case Image_Format_BGRF:{
            return QString("Image_Format_BGRF");
        }
        case Image_Format_RGBAF:{
            return QString("Image_Format_RGBAF");
        }
        case Image_Format_BGRAF:{
            return QString("Image_Format_BGRAF");
        }
        case Image_Format_GrayF_half:{
            return QString("Image_Format_GrayF_half");
        }
        case Image_Format_RGF_half:{
            return QString("Image_Format_RGF_half");
        }
        case Image_Format_RGBAF_half:{
            return QString("Image_Format_RGBAF_half");
        }
        case Image_Format_Gray16:{
            return QString("Image_Format_Gray16");
        }
        default:{
            return QString("UNKNOWN");
        }
    }
    return QString();
}


}
class NodeCADImage:public Image_PixMap{
private:
QImage image;


public:
NodeCADImage(){
    return;
}
void SetImage(const QImage& im){
  image=im;
  InitNativePixmap();
  return;
}
QImage Image() const{
    return image;
} 
void InitNativePixmap(){
    if(image.isNull()){
        LoadMessage(QString(""),QString("We have an uninitialized image"));
        return;
    }
  InitWrapper(IMAGE::QFormatToNativeFormat(image.format()),image.bits(),image.width(),image.height(),image.bytesPerLine());
  SetTopDown(true);
    return;
}
};