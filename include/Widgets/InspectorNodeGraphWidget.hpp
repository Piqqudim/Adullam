#pragma once
#include<AllNodes.hpp>
#include<InfoUtility.hpp>
#include<BasicGraphicsScene>
#include<DataFlowGraphicsScene.hpp>
#include<GraphicsView>
#include<QJsonDocument>
#include<QJsonArray>
#include<QJsonObject>
#include<NodeGraphModel.hpp>
using namespace std;
using namespace QtNodes;
class InspectorNodeWidget:public GraphicsView{
private:
Q_OBJECT
shared_ptr<NodeRegistry> Registry;
shared_ptr<DataFlowGraphicsScene> scene_1;
DataFlowGraphModel* graph_model=nullptr;
QJsonObject acceptedNodeArray;
public:
InspectorNodeWidget(QWidget* widget=nullptr):GraphicsView(widget){
    Registry=make_shared<NodeRegistry>();
   
   
 Registry->registerModel<OutputShapeNode>([this]()->std::shared_ptr<OutputShapeNode>{
    auto ptr=make_shared<OutputShapeNode>();
    QObject::connect(ptr.get(),&OutputShapeNode::EmitDrawnShape,this,InspectorNodeWidget::OnHandleShape);
    return ptr;
 },tr("Output"));
Registry->registerModel<ConvertToAIS_ShapeNode>("Conversion");
   
 Registry->registerModel<ConvertToFace>(tr("Conversion"));
Registry->registerModel<IntegerInputNode>("DataTypes");
   Registry->registerModel<StringInputNode>("DataTypes");
   Registry->registerModel<SinglyWireVector>(tr("Primitives Collection"));
   Registry->registerModel<SinglyShapeVector>(tr("Primitives Collection"));
   Registry->registerModel<DirectionNode>("Direction");
   Registry->registerModel<Point3dNode>("Points");
   Registry->registerModel<AxisNode>("Axis");
   Registry->registerModel<SinglyAxisNode>("Axis");
   Registry->registerModel<PrimitiveCubeNode>("Primitive Shapes");
   Registry->registerModel<PrimitiveCuboidNode>("Primitive Shapes");
    Registry->registerModel<PrimitiveSphereNode>("Primitive Shapes");
   Registry->registerModel<PrimitiveShapeNode>(tr("Primitive Shapes"));
   Registry->registerModel<PrimitiveConeNode>(tr("Primitive Shapes"));
Registry->registerModel<PrimitiveTorusNode>(tr("Primitive Shapes"));

Registry->registerModel<CommandEntryShapeNode>(tr("Command"));
   Registry->registerModel<SinglyPointNode>(tr("Points"));
   Registry->registerModel<ShapeArrayNode>("Array");
   Registry->registerModel<VectorToVectorNode>("Conversion");
   Registry->registerModel<ArrayToVectorNode>("Conversion");
   Registry->registerModel<SingleArrayToVectorNode>("Conversion");
   Registry->registerModel<BooleanNode>("Condition");
   Registry->registerModel<BoolNode>(tr("Condition"));
   Registry->registerModel<SinglyTransformNode>("Transform");
   Registry->registerModel<SinglyShapeNode>("Primitive Shapes");
   Registry->registerModel<SinglyWireNode>("Primitive Shapes");
   Registry->registerModel<FiveShapeNode>("Array");
   Registry->registerModel<TenSizedArrayNode>("Array");
   Registry->registerModel<ArrayToVectorNode>("Array");
   Registry->registerModel<ArrayVectorNode>("Array");
   Registry->registerModel<PrimitiveCylinderNode>(tr("Primitive Shapes"));
   Registry->registerModel<ColorNode>("Shading");
   Registry->registerModel<RGBColorNode>("Shading");
   Registry->registerModel<SinglyMaterialNode>(tr("Shading"));
   Registry->registerModel<RotationNode>("Transform");
   Registry->registerModel<ScaleNode>("Transform");
   Registry->registerModel<TranslateNode>("Transform");
   Registry->registerModel<CombinedTransformNode>(tr("Transform"));
   Registry->registerModel<DirXNode>(tr("Predefined Values"));
   Registry->registerModel<DirYNode>(tr("Predefined Values"));
   Registry->registerModel<DirZNode>(tr("Predefined Values"));
   Registry->registerModel<PolynomialFilletShape>(tr("Fillet Shape Type"));
   Registry->registerModel<QuasiAngularFilletShape>(tr("Fillet Shape Type"));
   Registry->registerModel<PositionedDirXNode>(tr("Predefined Values"));
   Registry->registerModel<PositionedDirYNode>(tr("Predefined Values"));
   Registry->registerModel<PositionedDirZNode>(tr("Predefined Values"));
   Registry->registerModel<NegatedPositionedDirXNode>(tr("Predefined Values"));
   Registry->registerModel<NegatedPositionedDirYNode>(tr("Predefined Values"));
   Registry->registerModel<NegatedPositionedDirZNode>(tr("Predefined Values"));
   Registry->registerModel<FaceNode>(tr("Sub Shape"));
   Registry->registerModel<FuseNode>(tr("Boolean Operation"));
   Registry->registerModel<CutNode>(tr("Boolean Operation"));
   Registry->registerModel<IndexNode>(tr("Indexing"));
    Registry->registerModel<CommonNode>(tr("Boolean Operation"));
    Registry->registerModel<SectionNode>(tr("Boolean Operation"));
   Registry->registerModel<TransformedShapeNode>(tr("Transform"));
   Registry->registerModel<MaterialNode>(tr("Shading"));
   Registry->registerModel<EdgeNode>(tr("Sub Shape"));
   Registry->registerModel<SinglyEdgeNode>(tr("Sub Shape"));
   Registry->registerModel<GoldMaterialNode>(tr("Predefined Material"));
   Registry->registerModel<BoundedLineNode>(tr("2D Shapes"));
   Registry->registerModel<SketchLineNode>(tr("2D Shapes"));
   Registry->registerModel<SketchCircleNode>(tr("2D Shapes"));
    Registry->registerModel<SinglyFaceNode>(tr("Sub Shape"));
   Registry->registerModel<ExtrusionNode>(tr("CAD operations"));
   Registry->registerModel<RevolveNode>(tr("CAD operations"));
   Registry->registerModel<ClassOneChamferNode>(tr("CAD operations"));
   Registry->registerModel<ClassOneFilletNode>(tr("CAD operations"));
   Registry->registerModel<ClassOneSurfaceSweepNode>(tr("CAD operations"));
   Registry->registerModel<ClassOneSolidSweepNode>(tr("CAD operations"));
   Registry->registerModel<MakeDraftNode>(tr("CAD operations"));
   Registry->registerModel<FloatNode>(tr("DataTypes"));
   Registry->registerModel<InvertDirectionNode>(tr("Direction"));
   Registry->registerModel<MakeDraftAngleNode>(tr("CAD operations"));
   Registry->registerModel<MakeEvolvedNode>(tr("CAD operations"));
   Registry->registerModel<LoftNode>(tr("CAD operations"));
   Registry->registerModel<MakeOffsetShapeNode>(tr("CAD operations"));
   Registry->registerModel<ToWireNode>(tr("Casting"));
   Registry->registerModel<ToEdgeNode>(tr("Casting"));
   Registry->registerModel<ToFaceNode>(tr("Casting"));
   Registry->registerModel<ConvertToWire>(tr("Casting"));
   Registry->registerModel<MakeOffsetFace>(tr("CAD operations"));
   Registry->registerModel<MakeOffsetWire>(tr("CAD operations"));
   Registry->registerModel<PrimitiveLineNode>(tr("2D Primitive"));
   Registry->registerModel<PrimitiveCircleNode>(tr("2D Primitive"));
   //For Wire Repairs
   Registry->registerModel<ReorderWireNode>(tr("Wire Repair"));
   Registry->registerModel<FixConnectedWireNode>(tr("Wire Repair"));
   Registry->registerModel<FixEdgeCurvesWireNode>(tr("Wire Repair"));
   Registry->registerModel<FixDegeneratedWireNode>(tr("Wire Repair"));
   Registry->registerModel<SelfIntersectWireNode>(tr("Wire Repair"));
   Registry->registerModel<FixGapWireNode>(tr("Wire Repair"));
   //MirrorNode
   Registry->registerModel<AboutPlaneMirrorNode>(tr("Mirror"));
   Registry->registerModel<AboutPointMirrorNode>(tr("Mirror"));
   Registry->registerModel<AboutAxisMirrorNode>(tr("Mirror"));
   
    //Conversion from wire,edge and face to Shape
   Registry->registerModel<ConvertWireToShape>(tr("Conversion"));
   Registry->registerModel<ConvertFaceToShape>(tr("Conversion"));
   Registry->registerModel<ConvertEdgeToShape>(tr("Conversion"));
   //end.......
   
   //Conversion from shell to solid
   Registry->registerModel<ConvertToMakeSolid>(tr("Conversion"));
   //end
    graph_model=new DataFlowGraphModel(Registry);
    scene_1=make_shared<DataFlowGraphicsScene>(*graph_model);
    GraphicsView::setScene(scene_1.get());
    return;
}
void AppendSceneJson(const QJsonDocument& jsondoc){
    QJsonObject Object=jsondoc.object();
    QJsonArray nodeJson=Object["nodes"].toArray();
    nodeJson=RemoveOutputNode(Object);
    Object["nodes"]=nodeJson;
    nodeJson=RemoveFloatInputNode(Object);
    Object["nodes"]=nodeJson;
    nodeJson=RemoveMultipleOutputNode(Object);
    Object["nodes"]=nodeJson;

    auto gscene=dynamic_cast<DataFlowGraphicsScene*>(nodeScene());
    if(!gscene){
        return;
    }
    if(gscene->GraphModel()->Models().size()!=0){
       gscene->clearScene();
    }
    gscene->GraphModel()->load(Object);
    gscene->update();
    return;
}
QJsonArray RemoveOutputNode(const QJsonObject& object){
    QJsonArray nodeArray=object["nodes"].toArray();
    for(int i=0;i<nodeArray.size();i++){
        auto njsonobject=nodeArray.at(i).toObject();
        if(njsonobject["model-name"].toString()==tr("OutputNode")){
            nodeArray.removeAt(i);
        }
    }
  return nodeArray;
}
QJsonArray RemoveFloatInputNode(const QJsonObject& object){
     QJsonArray nodeArray=object["nodes"].toArray();
     
    for(int i=0;i<nodeArray.size();i++){
        auto njsonobject=nodeArray.at(i).toObject();
        if(njsonobject["model-name"].toString()==tr("Float Node")){
            nodeArray.removeAt(i);
        }
    }
  return nodeArray;
}
QJsonArray RemoveMultipleOutputNode(const QJsonObject& object){
      QJsonArray nodeArray=object["nodes"].toArray();
    for(int i=0;i<nodeArray.size();i++){
        auto njsonobject=nodeArray.at(i).toObject();
        if(njsonobject["model-name"].toString()==tr("Multiple Output Node")){
            nodeArray.removeAt(i);
        }
    }
  return nodeArray;
}

~InspectorNodeWidget(){
    if(graph_model){
        delete graph_model;
        graph_model=nullptr;
    }
    return;
}
signals:
void OnSendShape(const Handle(CustomAIS_Shape)& sh);
public slots:
void OnHandleShape(const Handle(CustomAIS_Shape)& sh){
    emit OnSendShape(sh);
    return;
}
};