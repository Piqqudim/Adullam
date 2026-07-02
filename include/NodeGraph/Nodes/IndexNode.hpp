#pragma once
#include<ShapeNodeData.hpp>
#include<NodeDelegateModel>
#include<InfoUtility.hpp>
#include<QtCore/QJsonObject>
#include<memory>
using namespace std;
using namespace QtNodes;
using namespace INFO;
class IndexNode:public NodeDelegateModel{
private:
shared_ptr<ShapeNodeData> outputData;
std::weak_ptr<ShapeNodeData> inputData;
TopoDS_Shape outputShape;
Graphic3d_MaterialAspect mat;
int Index=-1;
public:
IndexNode(){
    return;
}

TopoDS_Shape GetShape() const{
    return outputShape;
}
void SetIndex(const int& ind){
    Index=ind;
    return;
}
QJsonObject save() const override{
    QJsonObject object=NodeDelegateModel::save();
    object["Indexer_ID"]=index();
    return object;
}
void load(const QJsonObject& object) override{
    int id=object["Indexer_ID"].toInt();
    SetIndex(id);
    return;
}
int index() const{
    return Index;
}
unsigned int nPorts(PortType portType) const override{
    switch(portType){
        case PortType::In:{
            return  1;
        }
        case PortType::Out:{
            return 1;
        }
        default:
         break;
    }
    return 0;
}
QString caption() const override{
    return tr("Indexer");
}
QString name() const override{
    return caption();
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::In:{
            switch(portIndex){
                case 0:
                    return ShapeNodeData(tr("Input")).type();
              
               
            }
        }
        case PortType::Out:{
             switch(portIndex){
                case 0:
                 return ShapeNodeData(tr("Output")).type();
               
             }
        }
        
    }
}
void EmitEmptyShape(){
    outputShape=TopoDS_Shape();
    if(outputData){
        outputData->SetData(outputShape);
    }
    emit dataUpdated(0);
    return;
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
   if(!data){
    return;
   }
   switch(portIndex){
    case 0:{
        inputData=dynamic_pointer_cast<ShapeNodeData>(data);
        if(inputData.lock()){
            outputShape=inputData.lock()->Data();
            mat=inputData.lock()->aspect();

        }
        break;
    }
   }
   if(outputData){
    if(index()==-1){
     LoadMessage(tr(""),tr("Cannot assign an invalid index"));
     return;
    }
    outputData->SetIndex(index());
    outputData->SetData(outputShape);
    outputData->SetAspect(mat);
   }
   else{
    outputData=make_shared<ShapeNodeData>(tr(""));
     if(index()==-1){
     LoadMessage(tr(""),tr("Cannot assign an invalid index"));
     return;
    }
    outputData->SetIndex(index());
    outputData->SetData(outputShape);
     outputData->SetAspect(mat);
   }
   emit dataUpdated(0);
   return;
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
  if(outputData){
    return static_pointer_cast<NodeData>(outputData);
  } 

std::shared_ptr<NodeData> mptr;
    return static_pointer_cast<NodeData>(mptr);
}
QWidget* embeddedWidget() override{
    return nullptr;
}
};