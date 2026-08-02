#pragma once
#include<NodeDelegateModel>
#include<WireNodeData.hpp>
#include<ShapeNodeData.hpp>
#include<ShapeFix_Wire.hxx>
#include<FaceNodeData.hpp>
#include<InfoUtility.hpp>
#include<NodeInitializer.hpp>
#include<memory>
#include<Standard_Failure.hxx>
using namespace QtNodes;
using namespace std;
using namespace INFO;
//Fix Wire Functionality,Every RepairWireNode repairs every aspect of wire, 
class ReorderWireNode:public NodeDelegateModel,public NodeInitializer{
 private:
 std::shared_ptr<ShapeNodeData> outputData;
 std::weak_ptr<WireNodeData> inputWire;
 std::weak_ptr<FaceNodeData> inputFace;
 TopoDS_Face face;
 TopoDS_Wire wire;
 bool isFaceSet=false;
 bool isWireSet=false;
 public:
 ReorderWireNode(){
    return;
 }
 unsigned int nPorts(PortType portType) const override{
   switch(portType){
      case PortType::In:{
         return 2;
      }
      case PortType::Out:{
         return 1;
      }
   }
   return 0;
 }
 QString caption() const override{
    return tr("Reorder Wire Node");
}
QString name() const override{
    return caption();
}
void SetToFalse() override{
 isWireSet=false;
 isFaceSet=false;
 return;
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::In:{
            switch(portIndex){
                case 0:
                   return WireNodeData(tr("Input Wire")).type();
                case 1:{
                   return FaceNodeData(tr("Input Face")).type();
                }
            }
        }
        case PortType::Out:{
            switch(portIndex){
            case 0:{
               return ShapeNodeData(tr("Output Shape")).type();
            }
        }
        }
       
    }
     return {tr(""),tr("")};
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(outputData){
      return static_pointer_cast<NodeData>(outputData);
    }
    std::shared_ptr<NodeData> mptr;
    return mptr;
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
   if(!data){
      return;
   }
   switch(portIndex){
      case 0:{
         inputWire=dynamic_pointer_cast<WireNodeData>(data);
         if(inputWire.lock()){
            wire=inputWire.lock()->Data();
            isWireSet=true;
            break;
         }
      }
      case 1:{
         inputFace=dynamic_pointer_cast<FaceNodeData>(data);
         if(inputFace.lock()){
            face=inputFace.lock()->GetFaceData();
            isFaceSet=true;
            break;
         }
      }
      
   }
   if(outputData){
   if(isWireSet==false){
      LoadMessage(tr(""),tr("Wire is not set"));
      return;
   }

   ShapeFix_Wire wirefixer;
   wirefixer.Load(wire);
   if(isFaceSet){
      wirefixer.SetFace(face);
   }
    wirefixer.FixReorder();
    try{
      wirefixer.Perform();
    }
    catch(Standard_Failure& efailure){
      LoadMessage(tr(""),tr("Wire Fixer Failed to fix reorder mode"));
      return;
    }
    outputData->SetData(wirefixer.Wire());
   }
   else{
      outputData=make_shared<ShapeNodeData>(tr(""));
        if(isWireSet==false){
      LoadMessage(tr(""),tr("Wire is not set"));
      return;
   }

   ShapeFix_Wire wirefixer;
   wirefixer.Load(wire);
   if(isFaceSet){
      wirefixer.SetFace(face);
   }
    wirefixer.FixReorder();
    try{
      wirefixer.Perform();
    }
    catch(Standard_Failure& efailure){
      LoadMessage(tr(""),tr("Wire Fixer Failed to fix reorder mode"));
      return;
    }
    outputData->SetData(wirefixer.Wire()); 
   }
   emit dataUpdated(0);
   return;
}
QWidget* embeddedWidget() override{ 
   return nullptr;
 }
};


class FixConnectedWireNode:public NodeDelegateModel,public NodeInitializer{
 private:
 std::shared_ptr<ShapeNodeData> outputData;
 std::weak_ptr<WireNodeData> inputWire;
 std::weak_ptr<FaceNodeData> inputFace;
 TopoDS_Face face;
 TopoDS_Wire wire;
 bool isFaceSet=false;
 bool isWireSet=false;
 public:
 FixConnectedWireNode(){
    return;
 }
 unsigned int nPorts(PortType portType) const override{
   switch(portType){
      case PortType::In:{
         return 2;
      }
      case PortType::Out:{
         return 1;
      }
   }
   return 0;
 }
 QString caption() const override{
    return tr("FixConnected Wire Node");
}
QString name() const override{
    return caption();
}
void SetToFalse() override{
 isWireSet=false;
 isFaceSet=false;
 return;
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::In:{
            switch(portIndex){
                case 0:
                   return WireNodeData(tr("Input Wire")).type();
                case 1:{
                   return FaceNodeData(tr("Input Face")).type();
                }
            }
        }
        case PortType::Out:{
            switch(portIndex){
            case 0:{
               return ShapeNodeData(tr("Output Shape")).type();
            }
        }
        }
       
    }
     return {tr(""),tr("")};
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(outputData){
      return static_pointer_cast<NodeData>(outputData);
    }
    std::shared_ptr<NodeData> mptr;
    return mptr;
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
   if(!data){
      return;
   }
   switch(portIndex){
      case 0:{
         inputWire=dynamic_pointer_cast<WireNodeData>(data);
         if(inputWire.lock()){
            wire=inputWire.lock()->Data();
            isWireSet=true;
            break;
         }
      }
      case 1:{
         inputFace=dynamic_pointer_cast<FaceNodeData>(data);
         if(inputFace.lock()){
           face=inputFace.lock()->GetFaceData();
            isFaceSet=true;
            break;
         }
      }
      
   }
   if(outputData){
   if(isWireSet==false){
      LoadMessage(tr(""),tr("Wire is not set"));
      return;
   }

   ShapeFix_Wire wirefixer;
   wirefixer.Load(wire);
   wirefixer.ClosedWireMode()=true;
   if(isFaceSet){
      wirefixer.SetFace(face);
   }
    wirefixer.FixConnected();
    try{
      wirefixer.Perform();
    }
    catch(Standard_Failure& efailure){
      LoadMessage(tr(""),tr("Wire Fixer Failed to fix connected"));
      return;
    }
    outputData->SetData(wirefixer.Wire());
   }
   else{
      outputData=make_shared<ShapeNodeData>(tr(""));
        if(isWireSet==false){
      LoadMessage(tr(""),tr("Wire is not set"));
      return;
   }

   ShapeFix_Wire wirefixer;
   wirefixer.Load(wire);
   if(isFaceSet){
      wirefixer.SetFace(face);
   }
    wirefixer.ClosedWireMode()=true;
    wirefixer.FixConnected();
    try{
      wirefixer.Perform();
    }
    catch(Standard_Failure& efailure){
      LoadMessage(tr(""),tr("Wire Fixer Failed to fix connected"));
      return;
    }
    outputData->SetData(wirefixer.Wire()); 
   }
   emit dataUpdated(0);
   return;
}
QWidget* embeddedWidget() override{ 
   return nullptr;
 }
};



class FixEdgeCurvesWireNode:public NodeDelegateModel,public NodeInitializer{
 private:
 std::shared_ptr<ShapeNodeData> outputData;
 std::weak_ptr<WireNodeData> inputWire;
 std::weak_ptr<FaceNodeData> inputFace;
 TopoDS_Face face;
 TopoDS_Wire wire;
 bool isFaceSet=false;
 bool isWireSet=false;
 public:
 FixEdgeCurvesWireNode(){
    return;
 }
 unsigned int nPorts(PortType portType) const override{
   switch(portType){
      case PortType::In:{
         return 2;
      }
      case PortType::Out:{
         return 1;
      }
   }
   return 0;
 }
 QString caption() const override{
    return tr("FixEdgeCurves Wire Node");
}
QString name() const override{
    return caption();
}
void SetToFalse() override{
 isWireSet=false;
 isFaceSet=false;
 return;
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::In:{
            switch(portIndex){
                case 0:
                   return WireNodeData(tr("Input Wire")).type();
                case 1:{
                   return FaceNodeData(tr("Input Face")).type();
                }
            }
        }
        case PortType::Out:{
            switch(portIndex){
            case 0:{
               return ShapeNodeData(tr("Output Shape")).type();
            }
        }
        }
       
    }
     return {tr(""),tr("")};
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(outputData){
      return static_pointer_cast<NodeData>(outputData);
    }
    std::shared_ptr<NodeData> mptr;
    return mptr;
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
   if(!data){
      return;
   }
   switch(portIndex){
      case 0:{
         inputWire=dynamic_pointer_cast<WireNodeData>(data);
         if(inputWire.lock()){
            wire=inputWire.lock()->Data();
            isWireSet=true;
            break;
         }
      }
      case 1:{
         inputFace=dynamic_pointer_cast<FaceNodeData>(data);
         if(inputFace.lock()){
            face=inputFace.lock()->GetFaceData();
            isFaceSet=true;
            break;
         }
      }
      
   }
   if(outputData){
   if(isWireSet==false){
      LoadMessage(tr(""),tr("Wire is not set"));
      return;
   }

   ShapeFix_Wire wirefixer;
   wirefixer.Load(wire);
   if(isFaceSet){
      wirefixer.SetFace(face);
   }
    wirefixer.FixEdgeCurves();
    try{
      wirefixer.Perform();
    }
    catch(Standard_Failure& efailure){
      LoadMessage(tr(""),tr("Wire Fixer Failed to fix connected"));
      return;
    }
    outputData->SetData(wirefixer.Wire());
   }
   else{
      outputData=make_shared<ShapeNodeData>(tr(""));
        if(isWireSet==false){
      LoadMessage(tr(""),tr("Wire is not set"));
      return;
   }

   ShapeFix_Wire wirefixer;
   wirefixer.Load(wire);
   if(isFaceSet){
      wirefixer.SetFace(face);
   }
    wirefixer.FixEdgeCurves();
    try{
      wirefixer.Perform();
    }
    catch(Standard_Failure& efailure){
      LoadMessage(tr(""),tr("Wire Fixer Failed to fix connected"));
      return;
    }
    outputData->SetData(wirefixer.Wire()); 
   }
   emit dataUpdated(0);
   return;
}
QWidget* embeddedWidget() override{ 
   return nullptr;
 }
};


class FixDegeneratedWireNode:public NodeDelegateModel,public NodeInitializer{
 private:
 std::shared_ptr<ShapeNodeData> outputData;
 std::weak_ptr<WireNodeData> inputWire;
 std::weak_ptr<FaceNodeData> inputFace;
 TopoDS_Face face;
 TopoDS_Wire wire;
 bool isFaceSet=false;
 bool isWireSet=false;
 public:
 FixDegeneratedWireNode(){
    return;
 }
 unsigned int nPorts(PortType portType) const override{
   switch(portType){
      case PortType::In:{
         return 2;
      }
      case PortType::Out:{
         return 1;
      }
   }
   return 0;
 }
 QString caption() const override{
    return tr("FixDegenerated Wire Node");
}
QString name() const override{
    return caption();
}
void SetToFalse() override{
 isWireSet=false;
 isFaceSet=false;
 return;
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::In:{
            switch(portIndex){
                case 0:
                   return WireNodeData(tr("Input Wire")).type();
                case 1:{
                   return FaceNodeData(tr("Input Face")).type();
                }
            }
        }
        case PortType::Out:{
            switch(portIndex){
            case 0:{
               return ShapeNodeData(tr("Output Shape")).type();
            }
        }
        }
       
    }
     return {tr(""),tr("")};
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(outputData){
      return static_pointer_cast<NodeData>(outputData);
    }
    std::shared_ptr<NodeData> mptr;
    return mptr;
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
   if(!data){
      return;
   }
   switch(portIndex){
      case 0:{
         inputWire=dynamic_pointer_cast<WireNodeData>(data);
         if(inputWire.lock()){
            wire=inputWire.lock()->Data();
            isWireSet=true;
            break;
         }
      }
      case 1:{
         inputFace=dynamic_pointer_cast<FaceNodeData>(data);
         if(inputFace.lock()){
            face=inputFace.lock()->GetFaceData();
            isFaceSet=true;
            break;
         }
      }
      
   }
   if(outputData){
   if(isWireSet==false){
      LoadMessage(tr(""),tr("Wire is not set"));
      return;
   }

   ShapeFix_Wire wirefixer;
   wirefixer.Load(wire);
   if(isFaceSet){
      wirefixer.SetFace(face);
   }
   wirefixer.ClosedWireMode()=true;
    wirefixer.FixDegenerated();
    try{
      wirefixer.Perform();
    }
    catch(Standard_Failure& efailure){
      LoadMessage(tr(""),tr("Wire Fixer Failed to fix degenerated"));
      return;
    }
    outputData->SetData(wirefixer.Wire());
   }
   else{
      outputData=make_shared<ShapeNodeData>(tr(""));
        if(isWireSet==false){
      LoadMessage(tr(""),tr("Wire is not set"));
      return;
   }

   ShapeFix_Wire wirefixer;
   wirefixer.Load(wire);
   if(isFaceSet){
      wirefixer.SetFace(face);
   }
    wirefixer.ClosedWireMode()=true;
    wirefixer.FixDegenerated();
    try{
      wirefixer.Perform();
    }
    catch(Standard_Failure& efailure){
      LoadMessage(tr(""),tr("Wire Fixer Failed to fix degenerate"));
      return;
    }
    outputData->SetData(wirefixer.Wire()); 
   }
   emit dataUpdated(0);
   return;
}
QWidget* embeddedWidget() override{ 
   return nullptr;
 }
};




class SelfIntersectWireNode:public NodeDelegateModel,public NodeInitializer{
 private:
 std::shared_ptr<ShapeNodeData> outputData;
 std::weak_ptr<WireNodeData> inputWire;
 std::weak_ptr<FaceNodeData> inputFace;
 TopoDS_Face face;
 TopoDS_Wire wire;
 bool isFaceSet=false;
 bool isWireSet=false;
 public:
 SelfIntersectWireNode(){
    return;
 }
 unsigned int nPorts(PortType portType) const override{
   switch(portType){
      case PortType::In:{
         return 2;
      }
      case PortType::Out:{
         return 1;
      }
   }
   return 0;
 }
 QString caption() const override{
    return tr("Self Intersect Wire Node");
}
QString name() const override{
    return caption();
}
void SetToFalse() override{
 isWireSet=false;
 isFaceSet=false;
 return;
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::In:{
            switch(portIndex){
                case 0:
                   return WireNodeData(tr("Input Wire")).type();
                case 1:{
                   return FaceNodeData(tr("Input Face")).type();
                }
            }
        }
        case PortType::Out:{
            switch(portIndex){
            case 0:{
               return ShapeNodeData(tr("Output Shape")).type();
            }
        }
        }
       
    }
     return {tr(""),tr("")};
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(outputData){
      return static_pointer_cast<NodeData>(outputData);
    }
    std::shared_ptr<NodeData> mptr;
    return mptr;
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
   if(!data){
      return;
   }
   switch(portIndex){
      case 0:{
         inputWire=dynamic_pointer_cast<WireNodeData>(data);
         if(inputWire.lock()){
            wire=inputWire.lock()->Data();
            isWireSet=true;
            break;
         }
      }
      case 1:{
         inputFace=dynamic_pointer_cast<FaceNodeData>(data);
         if(inputFace.lock()){
            face=inputFace.lock()->GetFaceData();
            isFaceSet=true;
            break;
         }
      }
      
   }
   if(outputData){
   if(isWireSet==false){
      LoadMessage(tr(""),tr("Wire is not set"));
      return;
   }

   ShapeFix_Wire wirefixer;
   wirefixer.Load(wire);
   if(isFaceSet){
      wirefixer.SetFace(face);
   }
   
    wirefixer.FixSelfIntersection();
    try{
      wirefixer.Perform();
    }
    catch(Standard_Failure& efailure){
      LoadMessage(tr(""),tr("Wire Fixer Failed to fix Self Intersection Edge"));
      return;
    }
    outputData->SetData(wirefixer.Wire());
   }
   else{
      outputData=make_shared<ShapeNodeData>(tr(""));
        if(isWireSet==false){
      LoadMessage(tr(""),tr("Wire is not set"));
      return;
   }

   ShapeFix_Wire wirefixer;
   wirefixer.Load(wire);
   if(isFaceSet){
      wirefixer.SetFace(face);
   }
    
    wirefixer.FixSelfIntersection();
    try{
      wirefixer.Perform();
    }
    catch(Standard_Failure& efailure){
      LoadMessage(tr(""),tr("Wire Fixer Failed to fix self intersected edges"));
      return;
    }
    outputData->SetData(wirefixer.Wire()); 
   }
   emit dataUpdated(0);
   return;
}
QWidget* embeddedWidget() override{ 
   return nullptr;
 }
};





class FixGapWireNode:public NodeDelegateModel,public NodeInitializer{
 private:
 std::shared_ptr<ShapeNodeData> outputData;
 std::weak_ptr<WireNodeData> inputWire;
 std::weak_ptr<FaceNodeData> inputFace;
 TopoDS_Face face;
 TopoDS_Wire wire;
 bool isFaceSet=false;
 bool isWireSet=false;
 public:
 FixGapWireNode(){
    return;
 }
 unsigned int nPorts(PortType portType) const override{
   switch(portType){
      case PortType::In:{
         return 2;
      }
      case PortType::Out:{
         return 1;
      }
   }
   return 0;
 }
 QString caption() const override{
    return tr("Fix Gap Wire Node");
}
QString name() const override{
    return caption();
}
void SetToFalse() override{
 isWireSet=false;
 isFaceSet=false;
 return;
}
NodeDataType dataType(PortType portType,PortIndex portIndex) const override{
    switch(portType){
        case PortType::In:{
            switch(portIndex){
                case 0:
                   return WireNodeData(tr("Input Wire")).type();
                case 1:{
                   return FaceNodeData(tr("Input Face")).type();
                }
            }
        }
        case PortType::Out:{
            switch(portIndex){
            case 0:{
               return ShapeNodeData(tr("Output Shape")).type();
            }
        }
        }
       
    }
     return {tr(""),tr("")};
}
std::shared_ptr<NodeData> outData(PortIndex port) override{
    if(outputData){
      return static_pointer_cast<NodeData>(outputData);
    }
    std::shared_ptr<NodeData> mptr;
    return mptr;
}
void setInData(std::shared_ptr<NodeData> data,PortIndex portIndex) override{
   if(!data){
      return;
   }
   switch(portIndex){
      case 0:{
         inputWire=dynamic_pointer_cast<WireNodeData>(data);
         if(inputWire.lock()){
            wire=inputWire.lock()->Data();
            isWireSet=true;
            break;
         }
      }
      case 1:{
         inputFace=dynamic_pointer_cast<FaceNodeData>(data);
         if(inputFace.lock()){
            face=inputFace.lock()->GetFaceData();
            isFaceSet=true;
            break;
         }
      }
      
   }
   if(outputData){
   if(isWireSet==false){
      LoadMessage(tr(""),tr("Wire is not set"));
      return;
   }

   ShapeFix_Wire wirefixer;
   wirefixer.Load(wire);
   if(isFaceSet){
      wirefixer.SetFace(face);
   }
   
    wirefixer.FixGaps3d();
    try{
      wirefixer.Perform();
    }
    catch(Standard_Failure& efailure){
      LoadMessage(tr(""),tr("Wire Fixer Failed to fix 3d Gaps"));
      return;
    }
    outputData->SetData(wirefixer.Wire());
   }
   else{
      outputData=make_shared<ShapeNodeData>(tr(""));
        if(isWireSet==false){
      LoadMessage(tr(""),tr("Wire is not set"));
      return;
   }

   ShapeFix_Wire wirefixer;
   wirefixer.Load(wire);
   if(isFaceSet){
      wirefixer.SetFace(face);
   }
    
    wirefixer.FixGaps3d();
    try{
      wirefixer.Perform();
    }
    catch(Standard_Failure& efailure){
      LoadMessage(tr(""),tr("Wire Fixer Failed to fix 3d Gaps"));
      return;
    }
    outputData->SetData(wirefixer.Wire()); 
   }
   emit dataUpdated(0);
   return;
}
QWidget* embeddedWidget() override{ 
   return nullptr;
 }
};


