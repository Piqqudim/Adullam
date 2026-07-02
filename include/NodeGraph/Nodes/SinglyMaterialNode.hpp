#pragma once
#include<NodeDelegateModel>
#include<MaterialNodeData.hpp>
#include<JsonShapeConverter.hpp>
#include<memory>
using namespace std;
using namespace QtNodes;
using namespace JsonConverter;
//so we can not apply material properties to objects of type 5 to 7
class SinglyMaterialNode:public NodeDelegateModel{
private:
shared_ptr<MaterialNodeData> output_data;
Graphic3d_MaterialAspect mat;

public:
SinglyMaterialNode(){
    return;
}
QJsonObject save() const override{
    QJsonObject object=NodeDelegateModel::save();
    object["Diffuse"]=ToJsonColorFormat(mat.DiffuseColor());
    object["Specular"]=ToJsonColorFormat(mat.SpecularColor());
    object["Emissive"]=ToJsonColorFormat(mat.EmissiveColor());
    object["Ambient"]=ToJsonColorFormat(mat.AmbientColor());
    object["Transparency"]=mat.Transparency();
    object["Refractive_Index"]=mat.RefractionIndex();
    return object;
}
void load(const QJsonObject& object) override{
    mat.SetDiffuseColor(ToColor(object["Diffuse"].toObject()));
    mat.SetAmbientColor(ToColor(object["Ambient"].toObject()));
    mat.SetSpecularColor(ToColor(object["Specular"].toObject()));
    mat.SetEmissiveColor(ToColor(object["Emissive"].toObject()));
    mat.SetTransparency(object["Transparency"].toDouble(1.0));
    mat.SetRefractionIndex(object["Refractive_Index"].toDouble(1.0));
    SetMaterial(mat);
}
void SetMaterial(const Graphic3d_MaterialAspect& mat1){
  mat=mat1;
  if(output_data){
    output_data->SetData(mat);
  }
  else{
    output_data=std::make_unique<MaterialNodeData>(tr(""));
    output_data->SetData(mat);
  }
   emit dataUpdated(0);
   return;
}
Graphic3d_MaterialAspect output() const{
    return mat;
}
Graphic3d_MaterialAspect& Material(){
    return mat;
}
unsigned int nPorts(PortType portType) const override{
    switch(portType){
        case PortType::In:{
            return 0;
        }
        case PortType::Out:{
            return 1;
        } 
       
    }
    return 0;
}
void OnUpdate(){
    emit dataUpdated(0);
}
QString caption() const override{
    return tr("Singly Material Node");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::Out:{
            switch(portIndex){
                case 0:
                   return MaterialNodeData(tr("Output Material")).type();

            }
        }
    }
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(output_data){
        output_data->SetData(mat);
    }
    return std::static_pointer_cast<NodeData>(output_data);
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
   return;
}
QWidget* embeddedWidget() override{ 
   return nullptr;
 }
};