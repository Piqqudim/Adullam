#ifndef STEPFILEREADER_HPP
#define STEPFILEREADER_HPP
#include<STEPControl_Reader.hxx>
#include<IGESControl_Reader.hxx>
#include<IFSelect_ReturnStatus.hxx>
#include<BRepTools.hxx>
#include<TopoDS_Shape.hxx>
#include<QtCore/QString>
namespace FileReader{
inline TopoDS_Shape GetShape(const QString& filename){
    return TopoDS_Shape();
}


}
//normal reading without setting the .step parameters;










#endif