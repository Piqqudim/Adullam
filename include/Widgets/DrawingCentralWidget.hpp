#ifndef DRAWINGCENTRALWIDGET_HPP
#define DRAWINGCENTRALWIDGET_HPP
#include<QtWidgets/QWidget>
#include<QtGui/QPainter>
#include<QtGui/QPalette>
#include<GraphicsLine.hpp>
#include<QtCore/Qt>
#include<DrawBezierDialog.hpp>
#include<vector>
#include<AIS_InteractiveContext.hxx>
#include<Prs3d_DatumAspect.hxx>
#include<V3d_View.hxx>
#include<Graphic3d_GraphicDriver.hxx>
#include<OpenGl_GraphicDriver.hxx>
#include<Aspect_DisplayConnection.hxx>
#include<AIS_ViewCube.hxx>
#include<AIS_ViewController.hxx>
#include<QtGui/QMouseEvent>
#include<QtGui/QWheelEvent>
#include<QtGui/QResizeEvent>
#include<QtWidgets/QMenu>
#include<V3d_TypeOfOrientation.hxx>
#include<Prs3d_LineAspect.hxx>
#include<Aspect_TypeOfLine.hxx>
#include<IntCurvesFace_ShapeIntersector.hxx>
#include<GeomAPI_IntCS.hxx>
#include<TopoDS.hxx>
#include<Geom_Curve.hxx>
#include<ElCLib.hxx>
#include<QtGui/QundoStack>
#include<WNT_Window.hxx>
#include<BRepPrimAPI_MakeBox.hxx>
#include<TopoDS_Shape.hxx>
#include<AIS_Shape.hxx>
#include<gp_Ax3.hxx>
#include<gp_Dir.hxx>
#include<V3d_RectangularGrid.hxx>
#include<memory>
#include<QtGui/QAction>
#include<ViewDirection.hpp>
#include<CameraAnimator.hpp>
#include<Sceneobject.hpp>
#include<AIS_Plane.hxx>
#include<WorkingPlane.hpp>
#include<SceneObject.hpp>
#include<gp_Lin.hxx>
#include<QtCore/QString>
#include<ViewCube.hpp>
#include<TopExp_Explorer.hxx>
#include<AIS_AnimationCamera.hxx>
#include<GraphicsCircle.hpp>
#include<BRepBuilderAPI_MakeEdge.hxx>
#include<Geom_Circle.hxx>
#include<gp_Pln.hxx>
#include<GeomAPI.hxx>
#include<algorithm>
#include<BRepPrimAPI_MakeSphere.hxx>
#include<QtWidgets/QMenu>
#include<BRepPrimAPI_MakeCone.hxx>
#include<BRepPrimAPI_MakeCylinder.hxx>
#include<AllCommand.hpp>
#include<AIS_Manipulator.hxx>
#include<MyCustomAIS_Shape.hxx>
#include<Graphic3d_Vec2.hxx>
#include<DeleteCommand.hpp>
#include<ShapeUtil.hpp>
#include<BRepBuilderAPI_Transform.hxx>
#include<BRepBuilderAPI_Copy.hxx>
#include<UndoTransformCommand.hpp>
#include<UndoCreationCommand.hpp>
#include<EventManager.hpp>
#include<NCollection_List.hxx>
#include<unordered_map>
#include<Point.hpp>
#include<SurfaceUtility.hpp>
#include<iostream>
#include<StdSelect_BRepOwner.hxx>
#include<ShadingTypeMap.hpp>
#include<AIS_Circle.hxx>
#include<AIS_Point.hxx >
#include<Geom_Point.hxx>
#include<Geom_CartesianPoint.hxx>
#include<TopoDS.hxx>
#include<gp_Vec.hxx>
#include<FaceMenu.hpp>
#include<TransientPolygon.hpp>
#include<EdgeMenu.hpp>
#include<QtWidgets/QMessageBox>
#include<PolygonMenu.hpp>
#include<TransientBeizerCurve.hpp>
#include<TransientBSplineCurve.hpp>
#include<Standard_DomainError.hxx>
#include<GeomAPI_PointsToBSpline.hxx>
#include<AIS_Axis.hxx>
#include<Geom_Axis1Placement.hxx>
#include<EdgeUtility.hpp>
#include<DrawLineDialog.hpp>
#include<GC_MakeCircle.hxx>
#include<DrawPolygonDialog.hpp>
#include<FilletDialog.hpp>
#include<ChamferDialog.hpp>
#include<FaceLineDialog.hpp>
#include<ChFi2d_FilletAPI.hxx>
#include<WireMenu.hpp>
#include<LineAIS_Shape.hpp>
#include<DrawCircleDialog.hpp>
#include<CircleAIS_Shape.hpp>
#include<BoxAIS_Shape.hpp>
#include<DrawArcDialog.hpp>
#include<BezierAIS_Shape.hpp>
#include<EditCircleRadiusDialog.hpp>
#include<ImageDialog.hpp>
#include<AIS_TexturedShape.hxx>
#include<BSplineAIS_Shape.hpp>
#include<DrawBSplineDialog.hpp>
#include<CollectiveAIS_Shape.hpp>
#include<EditArcDialog.hpp>
#include<ArcShape.hpp>
#include<TransientLineDialog.hpp>
#include<PrimLineMenu.hpp>
#include<TransientCircleDialog.hpp>
#include<PrimCircleMenu.hpp>
#include<cmath>
#include<CurveParam.hpp>
//This file will enter 10,000 LOC
//We have to create a dialog for viewport setting,Drawing widget is also a viewport
//On Object Creation,deletion,editing,Transform
using namespace Shape_Utility;
using namespace std;
using namespace SURFACE;
using namespace STM;
using namespace EDGE;
enum CHOOSE_MODE{
  CM_FACE,
  CM_EDGE,
  CM_NULL
};
enum SELECTED_STATE{
  SELECT,
  NULL_SELECT,
  EDGE_SELECT,
  FACE_SELECT,
  WIRE_SELECT,
  WIRES_SELECT
};
enum MANIP_CURVE{
 MC_NULL,
 MC_BEZIER,
 MC_LINE,
 MC_CIRCLE
};
enum TWOPOINT{
  TP_FIRST,
  TP_SECOND,
  TP_NULL
};
enum DRAWCURVE{
DC_NULL,
DC_MOVE,
DC_LINE,
DC_CIRCLE,
DC_SPLINE,
DC_BEZIER,
DC_STARTBEZIER,
DC_STARTBSPLINE,
DC_ARC,
DC_TRIM,
DC_POLYGON,
DC_FILLET,
DC_RADIUS,
DC_WIREFILLET,
DC_PRIMLINE,
DC_PRIMARC,
DC_PRIMCIRCLE,
DC_TWOPNT,
DC_TWOPNTARC,
DC_TWOPNTCIRCLE,
DC_EDGES,
DC_TRANSFORM,
DC_APPLYTRANS    //apply the transform after use 
};
enum GP_STATE{
 GPS_GATHER,
 GPS_BEZIER,
 GPS_BSPLINE,
 GPS_POINT,
 GPS_NULL
};
enum EDITSHAPE{
  ES_GIZMO,
  ES_NULL
};
enum ContextMenu{
CE_NULL, //by default,show scene menu
CE_EDGE,
CE_FACE,
CE_SHAPE,
CE_POINT,
CE_AXIS,
CE_CHAMFER, //for 2d
CE_FILLET, //for 2d
CE_DRAFT,
CE_CHAXIS
};
class DrawingCentralWidget:public QWidget{
private:
Q_OBJECT
public:
size_t QActionsNum;  //Number of QActions 
//For Drawing Cubes,basic primitives
bool DrawCube=false;
bool isDrawingCube=false;
bool DrawLine=false;
bool isDrawingLine=false;
bool DrawCircle=true;
bool isDrawingCircle=false;


bool canOrbit=false;
bool isPan=false; //it is panning
bool isPanningView=false;  //this is set when isPan is set
std::unique_ptr<QUndoStack> UndoStack;  //this will store all redo and undo commands of all operation and commands in this widget
bool m_KeepPreviousObject=false;  //PreviousShape Variable will be used to store object after the current object has been displayed,this will be useful to avoid redisplay
bool m_CanDisplayWireFrame=false;
bool m_CanDisplayShaded=false;
bool m_CanDisplayBoth=false;  //it can display both WireFrame and Shaded
bool canSetPlane=false;

bool canGatherPoints=false;   ///gather points using
Handle(Aspect_DisplayConnection) display;
Handle(OpenGl_GraphicDriver) driver;
Handle(V3d_View) view;
Handle(V3d_Viewer) Viewer;
Handle(AIS_InteractiveContext) context;
Handle(WNT_Window) Window;
gp_Pnt LineStart;
gp_Pnt LineEnd;
bool isLightOn=false;
bool UseWindowSize=true;
bool isObjectTransformed=false;

 TopoDS_Shape SphereShape;
 TopoDS_Shape ConeShape;
 TopoDS_Shape CylShape;

QMenu* SelectedMenu=nullptr;
QAction* DeleteAction=nullptr;
QAction* SelectAction=nullptr;
QAction* EditAction=nullptr;
QAction* UndoAction=nullptr;
QAction* RedoAction=nullptr;
QAction* ScaleAction=nullptr;
QAction* RotateAction=nullptr;
QAction* TranslateAction=nullptr;
std::unique_ptr<QAction> ShapeTypeAction;
QAction* ShapePrsAction=nullptr;
std::unique_ptr<DrawLineDialog> drawLineDialog;
std::unique_ptr<FaceLineDialog> faceDialog;
std::unique_ptr<QAction> ConstructPointNodeAction;
std::unique_ptr<QAction> ConstructTransformNodeAction;
std::unique_ptr<QAction> ConstructShapeNodeAction;
std::unique_ptr<QAction> ShowObjectInfo;
std::unique_ptr<QAction> convertPointAction; //this converts the face point to nodes
std::unique_ptr<QAction> ShowEdgeInfo;
std::unique_ptr<QAction> GatherPointAction; //
std::unique_ptr<QAction> GatherCurveAction;
std::unique_ptr<QAction> GatherBSplineAction;
std::unique_ptr<QAction> FindAction;
std::unique_ptr<QAction> transientPrimitiveAction=std::make_unique<QAction>(tr("Transient Primitives"));
std::unique_ptr<QMenu> transPrimMenu=std::make_unique<QMenu>();
std::unique_ptr<QAction> primLine=std::make_unique<QAction>(tr("Primitive Line"));
std::unique_ptr<QAction> primCircle=std::make_unique<QAction>(tr("Primitive Circle"));
std::unique_ptr<QAction> primArc=std::make_unique<QAction>(tr("Primitive Arc"));
std::unique_ptr<PrimLineMenu> primLineMenu=std::make_unique<PrimLineMenu>();
std::unique_ptr<PrimCircleMenu> primCircleMenu=std::make_unique<PrimCircleMenu>();

//This convert two set of points to a line 
std::unique_ptr<QAction> fLinePoint=make_unique<QAction>(tr("Select First Point"));
std::unique_ptr<QAction> sLinePoint=make_unique<QAction>(tr("Select Second Point"));
std::unique_ptr<QAction> convertToPrim=make_unique<QAction>(tr("Convert To Primitive Line"));
std::unique_ptr<QAction> endAction=std::make_unique<QAction>(tr("End"));
std::unique_ptr<QAction> build=make_unique<QAction>(tr("Build"));
std::unique_ptr<QAction> convertToAxis=make_unique<QAction>(tr("Convert To Axis Node"));
std::unique_ptr<QAction> convertToLength=make_unique<QAction>(tr("Convert To Length Node"));
std::unique_ptr<QAction> viewLength=make_unique<QAction>(tr("View Length"));
std::unique_ptr<QAction> viewAxis=make_unique<QAction>(tr("View Axis"));
std::unique_ptr<QAction> LineAction;
std::unique_ptr<QMenu> LineMenu;
//end
TWOPOINT tpoint=TP_NULL;
std::array<gp_Pnt,2> twoPointArray;

std::unique_ptr<QAction> shouldSetAction=std::make_unique<QAction>(tr("Should Set"),nullptr);
std::unique_ptr<QAction> CheckShapeIdAction=std::make_unique<QAction>(tr("Shape Id"),nullptr);
std::unique_ptr<QAction> deleteAxisObject=std::make_unique<QAction>(tr("Delete"));
std::unique_ptr<QAction> faceNormalAction=std::make_unique<QAction>(tr("Assume Face Centre Normal"));
std::unique_ptr<QAction> convertFacePointAction=std::make_unique<QAction>(tr("Convert To Point Node"));
std::unique_ptr<QAction> drawAction=std::make_unique<QAction>(tr("Draw Line"));
std::unique_ptr<QAction> gatherWire=std::make_unique<QAction>(tr("Select Wires"));
std::unique_ptr<WireFilletMenu> wireFilletMenu=std::make_unique<WireFilletMenu>();
std::unique_ptr<DrawCircleMenu> drawCircle=std::make_unique<DrawCircleMenu>();
std::unique_ptr<DrawPolygonDialog> drawPolygonDialog=std::make_unique<DrawPolygonDialog>();
std::unique_ptr<ChamferDialog> chamferDialog;
std::unique_ptr<FilletDialog> filletDialog;
std::unique_ptr<EditDialog> circleEditDialog=std::make_unique<EditDialog>();
std::unique_ptr<FaceMenu> faceMenu;
std::unique_ptr<EdgeMenu> edgeMenu; 
std::unique_ptr<PolygonMenu> polyMenu;
std::unique_ptr<QAction> moveToSelectedFaceAction=std::make_unique<QAction>(tr("Move To Face"));

Handle(AIS_InteractiveObject) chosenInteractive;
std::unique_ptr<QMenu> drawBezierMenu=std::make_unique<QMenu>();
std::unique_ptr<QAction> startBezier=std::make_unique<QAction>(tr("Start Bezier"));
std::unique_ptr<QAction> endBezier=std::make_unique<QAction>(tr("End Bezier"));
std::unique_ptr<QAction> continueBezier=std::make_unique<QAction>(tr("Continue Bezier"));
std::unique_ptr<DrawArcDialog> arcDialog=std::make_unique<DrawArcDialog>();
std::unique_ptr<DrawLineMenu> drawLineMenu=std::make_unique<DrawLineMenu>();
std::unique_ptr<PointMenu> pointMenu=std::make_unique<PointMenu>();
std::unique_ptr<QAction> convertPoint=std::make_unique<QAction>(tr("Convert To Point Node"));
std::unique_ptr<QAction> copyScaleAction=std::make_unique<QAction>(tr("Copy Scale"),nullptr);
std::unique_ptr<QAction> copyRotationAction=std::make_unique<QAction>(tr("Copy Rotation"),nullptr);
std::unique_ptr<QAction> copyTranslationAction=std::make_unique<QAction>(tr("Copy Translation"),nullptr);
std::unique_ptr<QAction> polygonAction=std::make_unique<QAction>(tr("Draw Polygon"));
std::unique_ptr<QAction> copyMaterial=std::make_unique<QAction>(tr("Convert To Material Node"));
std::unique_ptr<QAction> createMaterialNode=std::make_unique<QAction>(tr("Create Material Node"));
std::unique_ptr<QAction> findByAction=std::make_unique<QAction>(tr("Find By"));
std::unique_ptr<QMenu> findByMenu=std::make_unique<QMenu>(); 
std::unique_ptr<QAction> findByIndexer=std::make_unique<QAction>(tr("Find By Index Node"));
std::unique_ptr<QAction> findByShapeNode=std::make_unique<QAction>(tr("Find By Shape Node"));
std::unique_ptr<QAction> commitChanges=std::make_unique<QAction>(tr("Commit Change"));
std::unique_ptr<QAction> drawCircleAction=std::make_unique<QAction>(tr("Draw Circle"));
std::unique_ptr<QMenu> drawCircleMenu=std::make_unique<QMenu>();
std::unique_ptr<QAction> drawCircleByRadius=std::make_unique<QAction>(tr("Draw Circle By Radius and Centre"));
std::unique_ptr<QAction> circleDraw=std::make_unique<QAction>(tr("Draw Circle by three point"));
std::unique_ptr<QAction> startDrawCircle=std::make_unique<QAction>(tr("Start Draw Circle")); //this one spawns the circle draw dialog
std::unique_ptr<QAction> endDrawCircle=std::make_unique<QAction>(tr("End Draw Circle"));
std::unique_ptr<QMenu> circleByRadiusMenu=std::make_unique<QMenu>();
std::unique_ptr<QMenu> arcMenu=std::make_unique<QMenu>();
std::unique_ptr<QAction> arcMenuAction=std::make_unique<QAction>(tr("DrawArc"));
std::unique_ptr<QAction> arcStart=std::make_unique<QAction>(tr("Select Point For Arc"));
std::unique_ptr<QAction> arcDraw=std::make_unique<QAction>(tr("Execute Arc"));
std::unique_ptr<QMenu> editCircleMenu=std::make_unique<QMenu>();
std::unique_ptr<QAction> editCircleAction=std::make_unique<QAction>(tr("Edit Circle Radius"));//this shows the previous value
std::unique_ptr<QAction> cancelEditCircle=std::make_unique<QAction>(tr("Destroy"));
std::unique_ptr<QAction> convertToEdgeColl=make_unique<QAction> (tr("Convert To Edges Coll"))
std::unique_ptr<QMenu> groupCollectionMenu=std::make_unique<QMenu>();
std::unique_ptr<QAction> groupCollectionAction=std::make_unique<QAction>(tr("Group Selection"));
std::unique_ptr<QAction> selectEdges=std::make_unique<QAction>(tr("Select Edges"));
std::unique_ptr<QAction> selectFaces=std::make_unique<QAction>(tr("Select Faces"));
std::unique_ptr<QAction> selectShapes=std::make_unique<QAction>(tr("Select Shapes"));
std::unique_ptr<QMenu> groupWireMenu=std::make_unique<QMenu>();
std::unique_ptr<QAction> deleteGroupWire=std::make_unique<QAction>(tr("Delete"));
std::unique_ptr<QAction> endGroupWire=std::make_unique<QAction>(tr("End Wire Group Selection"));
std::unique_ptr<QAction> convertToWires=std::make_unique<QAction>(tr("Convert To Wire Nodes"));

std::unique_ptr<QAction> convertEdgesToWire=std::make_unique<QAction>(tr("Edges To Wire"));
std::unique_ptr<QAction> deleteAllEdges=std::make_unique<QAction>(tr("Delete Edges"));
std::unique_ptr<QAction> endGroupSelection=std::make_unique<QAction>(tr("End Selection"));
std::unique_ptr<QMenu> edgesMenu=make_unique<QMenu>(); 



std::unique_ptr<QAction> updateWithTransform=std::make_unique<QAction>(tr("Update"));
std::unique_ptr<DrawBezierDialog> drawBezierDialog=std::make_unique<DrawBezierDialog>();
std::unique_ptr<TransientPolygon> transPolygon;
std::unique_ptr<TransientBezierCurve> transCurve;
std::unique_ptr<TransientBSplineCurve> bspCurve;
std::unique_ptr<BezierMenu> bMenu;
std::unique_ptr<BSplineMenu> spMenu;
std::unique_ptr<AxisMenu> axisMenu;
std::unique_ptr<CircleDialog> circleDialog=std::make_unique<CircleDialog>();
std::unique_ptr<DrawPolygonMenu> drawPolyMenu=std::make_unique<DrawPolygonMenu>();
std::unique_ptr<ApplyChamferMenu> chamferMenu=std::make_unique<ApplyChamferMenu>();
std::unique_ptr<ApplyFilletMenu> filletMenu=std::make_unique<ApplyFilletMenu>();
std::unique_ptr<TrimMenu> trimMenu=std::make_unique<TrimMenu>();
std::unique_ptr<FilletMenu> edgeFilletMenu=std::make_unique<FilletMenu>();
unique_ptr<WireMenu> wireMenu=std::make_unique<WireMenu>();
std::unique_ptr<QAction> drawBezierByDialog=std::make_unique<QAction>(tr("Draw Bezier By Dialog"));
std::unique_ptr<QAction> drawBSplineByDialogAction=std::make_unique<QAction>(tr("Draw BSpline By Dialog"));
std::unique_ptr<QMenu> drawBSplineMenu=std::make_unique<QMenu>();
std::unique_ptr<QAction> startBSpline=std::make_unique<QAction>(tr("Start BSpline"));
std::unique_ptr<QAction> continueBSpline=std::make_unique<QAction>(tr("Continue BSpline"));
std::unique_ptr<QAction> endBSpline=std::make_unique<QAction>(tr("End BSpline"));
std::unique_ptr<QMenu> moveMenu=std::make_unique<QMenu>();

std::unique_ptr<QAction>startMove=std::make_unique<QAction>(tr("Select Face's Point"));
std::unique_ptr<QAction> executeMove=std::make_unique<QAction>(tr("Execute Move"));
std::unique_ptr<QAction> endMove=std::make_unique<QAction>(tr("End Move"));
std::unique_ptr<QAction> loadImage=std::make_unique<QAction>(tr("Load Image"));
std::unique_ptr<ImageDialog> imageDialog=std::make_unique<ImageDialog>();
std::unique_ptr<DrawBSplineDialog> bsplineDialog=std::make_unique<DrawBSplineDialog>();
std::unique_ptr<WireSelector> wireselector=std::make_unique<WireSelector>();
std::unique_ptr<ShapeSelector> shapeselector=std::make_unique<ShapeSelector>();
std::unique_ptr<EdgeSelector> edgeselector=std::make_unique<EdgeSelector>();
std::unique_ptr<FaceSelector> faceselector=std::make_unique<FaceSelector>();

std::unique_ptr<CollectiveWireSelector> wireselectors=std::make_unique<CollectiveWireSelector>();
std::unique_ptr<CollectiveEdgeSelector> edgeselectors=std::make_unique<CollectiveEdgeSelector>();
std::unique_ptr<CollectiveFaceSelector> faceselectors=std::make_unique<CollectiveFaceSelector>();
std::unique_ptr<CollectiveShapeSelector> shapeselectors=std::make_unique<CollectiveShapeSelector>();
std::unique_ptr<EditArcDialog> editarcDialog=std::make_unique<EditArcDialog>();
std::unique_ptr<TransientLineDialog> transLineDialog=std::make_unique<TransientLineDialog>();
std::unique_ptr<QAction> selectWires=std::make_unique<QAction>(tr("Select Wires"));
std::unique_ptr<TransientCircleDialog> transCircleDialog=std::make_unique<TransientCircleDialog>();
//For Special transform,whereby a user clicks a point on the selected object that is not the center and perform transformation about that selected point; (For geometry continutiy).
std::unique_ptr<QAction>  TransformAction;
std::unique_ptr<QMenu> TransformMenu;
std::unique_ptr<QAction> setFixed=std::make_unique<QAction>(tr("Set Fixed")); //this allows us to select a point on the object and perform transform about that object
std::unique_ptr<QAction> applyTransform;
std::unique_ptr<QAction> endTransform;
std::unique_ptr<QAction> redisplayGizmo=std::make_unique<QAction>(tr("Display Gizmo"));


//ZBuffer- depth;
std::unique_ptr<QMenu> zbufferMenu;
std::unique_ptr<QAction> zbufferAction;
std::unique_ptr<QAction> topMostAction;
std::unique_ptr<QAction> defaultAction;
std::unique_ptr<QAction> topAction;
//Z Buffer Depth end;

//my Transformation 

Handle(AIS_Shape) myTransShape;
std::unique_ptr<QMenu> transMenu;
std::unique_ptr<QAction> transAction;
std::unique_ptr<QAction> setShapeFixed;
std::unique_ptr<QAction> transStartPoint;
std::unique_ptr<QAction> transEndPoint;
std::unique_ptr<QAction> computeTrans;
std::unique_ptr<QAction> applyTransObject;
std::unique_ptr<QAction> endApply;

//Draw Arc by Specifying Two Points
std::unique_ptr<QMenu> twoPntArcMenu;
std::unique_ptr<QAction> twoPntArcAction;
std::unique_ptr<QAction> arcFirstPoint;
std::unique_ptr<QAction> arcSecondPoint;

std::unique_ptr<QAction> buildArc;
std::unique_ptr<QAction> endBuildArc;
//End Draw Arc by Specifying two points

//Draw Circle by specifying two points
std::unique_ptr<QMenu> twoPntCircleMenu;
std::unique_ptr<QAction> twoPntCircleAction;
std::unique_ptr<QAction> circleFirstPoint;
std::unique_ptr<QAction> circleSecondPoint;
std::unique_ptr<QAction> buildCircle;
std::unique_ptr<QAction> endBuildCircle;
std::unique_ptr<QAction> convertBuiltCircle; //convert the built circle to circle primitive node

//this one allows us to choose axis of direction,you can choose Axis from any selection entity like face and edge,or choose axis 
/*
we can either choose axis from 

*/
std::unique_ptr<QAction> chooseAxis; 
std::unique_ptr<QMenu> chooseAxisMenu;
std::unique_ptr<QAction> setFaceFixed;
std::unique_ptr<QAction> defaultX; //X direction(1,0,0)
std::unique_ptr<QAction> defaultY; //Y direction(0,1,0)
std::unique_ptr<QAction> defaultZ; //Z direction (0,0,1);
std::unique_ptr<QAction> chooseFace; //to compute surface normal
std::unique_ptr<QAction> chooseFaceNormal;
std::unique_ptr<QAction> endChooseAxis;//ce_chaxis
//gp_Dir chDir=SURFACE::GetFaceNormal(selFace,selFacePoint);

MANIP_CURVE manipcurve=MC_NULL;
bool IsShapePrsAdded=false;   //this is to keep track of whether shape presentation menu item has been added
 TopoDS_Face selFace;
 TopoDS_Edge selEdge;

QAction* LinePrsAction=nullptr;
bool IsLinePrsAdded=false;  //thus is to keep track of whether lineprsaction is added to SelectedMenu or not
gp_Pnt CircleFirstPoint;
gp_Pnt CircleSecondPoint;
gp_Pnt CircleThirdPoint;H
TopoDS_Shape SelectedShape;
QMenu* DockMenus=nullptr;
QAction* showSettingAction=nullptr;
QAction* DrawCubeAction=nullptr;
QAction* DeleteObjectGizmoAction=nullptr;
std::unique_ptr<QAction> refreshAction;
ContextMenu cm=CE_NULL;
DRAWCURVE dc=DC_NULL;
DRAWCURVE prevdc=DC_NULL;
TrimParam trimparam;
Handle(Graphic3d_AspectMarker3d) GridAspect=new Graphic3d_AspectMarker3d(Aspect_TOM_RING1,Quantity_NOC_LIGHTSTEELBLUE,2);
bool ShowGrid=true;
bool ShowPlane=true;
bool ShowDrawingPlane=true;
bool IsSeen=false; //this is initialized when an object is found in Shapes;
bool IsSelectedColorUsed=false;
int CurrentSelMode=-1; //Current Selection Mode
int PrevSelMode=-1; //previous selection mode before current selection mode...
int CurrentShadeMode=3;
int WindowHeight=0;  //This is for the binded window;
int WindowWidth=0;
int ShapeId=-1; //invalid index
size_t draftCount=0;
int prevCurrSelMode=-1;
Handle(AIS_Manipulator) ObjectGizmo;    //This is the object gizmo

Handle(ViewCube) viewcube=new ViewCube();
Handle(AIS_ViewCubeOwner) viewcubeowner=new AIS_ViewCubeOwner(viewcube,V3d_Xpos);
const double dpr=devicePixelRatioF();


Handle(CustomAIS_Shape) ChosenShape;   //This will be a template for all chosen shapes
Handle(CustomAIS_Shape) PreviousShape;
Handle(CustomAIS_Shape) selShape;
Handle(CustomAIS_Shape) surfaceWidgetShape;

Handle(CustomAIS_Shape) prevCurrentObject;
Handle(CustomAIS_Shape) currentObject;   //this is used when a node is clicked,it will store the object 
Handle(CurveAIS_Shape) curveShape;
Handle(CurveAIS_Shape) selCurveShape;
Handle(BezierAIS_Shape) bezierShape;
Handle(CustomAIS_Shape) drawnWireShape;
Handle(AIS_Axis) AxisObject;
Quantity_Color currentObjectColor;
std::vector<Handle(CustomAIS_Shape)> collectedLines;  //these are the lines that are collected when constructing a polygon

Handle(CustomAIS_Shape) emittedShape;  //this is to select subshapes of a shape
Handle(CustomAIS_Shape) prevEmittedShape;
Handle(CustomAIS_Shape)  currSelShape;
Handle(CustomAIS_Shape) currDetShape;
Handle(CustomAIS_Shape) firstTrimShape;
Handle(CustomAIS_Shape) secondTrimShape;
Handle(CustomAIS_Shape) wireShape;

Handle(LineAIS_Shape) lineShape; //for casted curved shape for line
Handle(CircleAIS_Shape) circShape; //for casted curved shape for circle
Handle(LineAIS_Shape) castedLineShape;  //for casted curve shape when we are performing transformation on a line
Handle(CircleAIS_Shape) castedCircleShape;
Handle(BezierAIS_Shape) castedBezierShape;
Handle(BSplineAIS_Shape) castedBsplineShape;
Handle(BezierAIS_Shape) bshape;
Handle(BSplineAIS_Shape) bsplineShape;
Handle(BSplineAIS_Shape) drawnBsplineShape;
Handle(EditCircleShape) editShape;
Handle(ArcAIS_Shape) arcShape;
Quantity_Color currentShapeColor;
gp_Pnt2d lastpoint; 
gp_Pnt2d panlastpoint;   //this will store the pan 
gp_Pnt selFacePoint;
gp_Pnt LineStartPoint;
bool LastPointIsSet=false;
WorkingPlane Plane;
float GridSize_X=0.0;
float GridSize_Y=0.0;
float Grid_Spacing=2.0f;

bool isScaleGizmoEnabled=false;
bool isTranslateGizmoEnabled=false;
bool isRotateGizmoEnabled=false;
bool isEditCircleShapeTransformed=false;

 
EventManager evt_manager;
Handle(Prs3d_Drawer) detected_drawer;

Handle(Prs3d_Drawer) selected_drawer;
Handle(AIS_Point) pointMarker=new AIS_Point(new Geom_CartesianPoint(0.0,0.0,0.0));
gp_Dir chosenDir;
double x_value=0.0;
double y_value=0.0;
double z_value=0.0;

double int_x=0.0; //intersection point
double int_y=0.0;
double int_z=0.0;
gp_Trsf PrevTrsf;
gp_Trsf CurrTrsf;
gp_Trsf SentTransform;  //this is the transform that is sent from drawing widget to nodegraph
size_t objectCount=0;
std::unordered_map<size_t,Handle(CustomAIS_Shape)> Shapes;
std::unordered_map<size_t,Handle(AIS_Shape)> DraftShapes; //for every 2d shapes that will be rendered in the scene...
std::vector<std::shared_ptr<CurveParam>> curveparams;
std::vector<TopoDS_Shape> LoadedShapes; //used by step file reader,iges reader, brep reader
Graphic3d_MaterialAspect prevChosenMat;
Graphic3d_MaterialAspect chosenShapeMaterial;
size_t ChosenId=0;

int faceIndex=-1; //invalid index
int edgeIndex=-1;
int ParentIndex=-1;

Quantity_Color chosenFaceColor;
Quantity_Color chosenEdgeColor;
Quantity_Color chosenVertexColor;

CHOOSE_MODE chmode=CM_NULL; //to select and isolate a particular subshape in the scene for intersection
SELECTED_STATE st;
SELECTED_STATE st1;//for per face selection and per edge selection
EDITSHAPE  Eshape=ES_NULL;
TopoDS_Face surfaceWidgetFace;
TopoDS_Face convertedEdgeFace;
TopoDS_Shape SentShape=TopoDS_Shape();
TopoDS_Shape selFaceShape=TopoDS_Shape();
TopoDS_Wire loopwire=TopoDS_Wire();
TopoDS_Edge chamferEdge=TopoDS_Edge();
TopoDS_Edge filletEdge=TopoDS_Edge();
TopoDS_Edge filletEdge_1=TopoDS_Edge();
TopoDS_Edge wiredEdge;
TopoDS_Edge wiredEdge_1;
TopoDS_Vertex chamferVertex=TopoDS_Vertex();
TopoDS_Vertex filletVertex=TopoDS_Vertex();
TopoDS_Wire selWire=TopoDS_Wire();
gp_Pnt currGizmoPos;
gp_Pnt nextGizmoPos;
std::vector<int> collectiveIndex;
gp_Pnt trimFirstPoint;
gp_Pnt trimSecondPoint;
int mainIndex=-1;
int subMainIndex=-1;
int SentShapeId=-1;
Handle(CustomAIS_Shape) polygonShape;
GP_STATE gpsstate=GPS_NULL;
Handle(Image_AlienPixMap) nodeImage;
Handle(AIS_TexturedShape) textureShape;
Handle(AIS_TexturedShape) selTextureShape;
bool isFixed=false; //this is used when we want the position tobe fixed when using transform
bool isTransFixed=false; //this is used to stop the user from clicking any other shape apart from the one selected 
//Parameters To Modify Object Transform at position that isn not the center of the object
gp_Trsf objectTrans=gp_Trsf();
gp_Pnt GizmoStartPosition=gp_Pnt();
gp_Pnt gottenPos;//this will be a point that is unchanged when isFixed is set to false;
int prevMode=-1;
//For choosing axis
gp_Dir gottenDir;
TopoDS_Face ChosenAxisFace;
bool isFaceFixed=false;
//end of choosen axis
gp_Ax2 gottenAxis;

public:
  DrawingCentralWidget(QWidget* parent_widget):QWidget(parent_widget){
    std::cout<<"I am in Drawing CentralWidget"<<"\n";
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_NoSystemBackground);
    setAutoFillBackground(false);
    setAttribute(Qt::WA_NativeWindow);
    setFocusPolicy(Qt::StrongFocus);
    setBackgroundRole(QPalette::NoRole);
    setMouseTracking(true);
     UndoStack.reset(new QUndoStack);  //Allocate memory for QUndoStack
    winId();
    show();
    convertPoint->setCheckable(true);
    drawLineDialog=std::make_unique<DrawLineDialog>(nullptr);
    faceDialog=std::make_unique<FaceLineDialog>();
    Shapes.reserve(100);   //maximum shapes in the scene to prevent rehashing
    edgeMenu=std::make_unique<EdgeMenu>();
    faceMenu=std::make_unique<FaceMenu>();
    faceMenu->addAction(faceNormalAction.get());
   
    convertFacePointAction->setCheckable(true);
   
    faceMenu->addAction(convertFacePointAction.get());
    bMenu=std::make_unique<BezierMenu>();
    spMenu=std::make_unique<BSplineMenu>();
    axisMenu=std::make_unique<AxisMenu>();
    axisMenu->addAction(deleteAxisObject.get());
    AxisObject=new AIS_Axis(new Geom_Axis1Placement(gp_Pnt(0.0,0.0,0.0),gp_Dir(0.0,1.0,0.0)));
    SelectAction=new QAction(tr("Select"),nullptr); 
    filletDialog=make_unique<FilletDialog>();
    chamferDialog=make_unique<ChamferDialog>();
    UndoAction=UndoStack->createUndoAction(this,tr("&Undo"));
    
    RedoAction=UndoStack->createRedoAction(this,tr("&Redo"));
    UndoAction->setShortcut(Qt::CTRL|Qt::Key_S);
    RedoAction->setShortcut(Qt::CTRL|Qt::Key_K);

    pointMarker->SetColor(Quantity_NOC_PERU);
    pointMarker->SetMarker(Aspect_TOM_O);
    
    SelectedMenu=new QMenu;
    moveToSelectedFaceAction->setCheckable(true);
    TranslateAction=new QAction(tr("Translate"),nullptr);
    TranslateAction->setCheckable(true);
    TranslateAction->setChecked(true);

    RotateAction=new QAction(tr("Rotate"),nullptr);

    RotateAction->setCheckable(true);
    RotateAction->setChecked(true);
    ShowEdgeInfo=make_unique<QAction>(tr("Show Edge Info"),nullptr);
    ScaleAction=new QAction(tr("Scale"),nullptr);
    ScaleAction->setCheckable(true);
    ScaleAction->setChecked(true);
    DeleteObjectGizmoAction=new QAction(tr("Destroy Gizmo"),nullptr);
    
    ShapePrsAction=new QAction(tr("Object Presentation"),nullptr);
    LinePrsAction=new QAction(tr("Line Presentation"),nullptr);
    ShapeTypeAction=std::make_unique<QAction>(tr("Show Shape Type"),nullptr);
    //z buffer info
    zbufferMenu=std::make_unique<QMenu>();
    zbufferAction=std::make_unique<QAction>(tr("Depth Info"));
    zbufferAction->setMenu(zbufferMenu.get());
    topMostAction=std::make_unique<QAction>(tr("Top Most "));
    topMostAction->setCheckable(true);
    defaultAction=std::make_unique<QAction>(tr("Default Depth"));
    defaultAction->setCheckable(true);
    topAction=std::make_unique<QAction>(tr("Top Depth"));
    topAction->setCheckable(true);

    zbufferMenu->addAction(topMostAction.get());
    zbufferMenu->addAction(defaultAction.get());
    zbufferMenu->addAction(topAction.get());

  TransformAction=std::make_unique<QAction>("Apply Transform Relative To Point");
  TransformAction->setCheckable(true);
  TransformMenu=std::make_unique<QMenu>();
  applyTransform=std::make_unique<QAction>(tr("Apply Transform"));
  endTransform=std::make_unique<QAction>(tr("End Transform"));
  setFixed->setCheckable(true);
  TransformMenu->addAction(setFixed.get()); //this is used when we want to transform the object at that specified position  
  TransformMenu->addAction(applyTransform.get());
  TransformMenu->addAction(redisplayGizmo.get());
  TransformMenu->addAction(endTransform.get());


   ConstructTransformNodeAction=std::make_unique<QAction>(tr("Convert To TransformNode"),nullptr);
     ConstructTransformNodeAction->setCheckable(true);
      ConstructPointNodeAction=std::make_unique<QAction>(tr("Convert To Point Node"));
 ConstructPointNodeAction->setCheckable(true);
    ConstructShapeNodeAction=std::make_unique<QAction>(tr("Convert To ShapeNode"),nullptr);
    ConstructShapeNodeAction->setCheckable(true);
    ShowObjectInfo=make_unique<QAction>(tr("Show Object Info"),nullptr);
    convertPointAction=make_unique<QAction>(tr("Convert Intersect Point To Node"),nullptr);
    convertPointAction->setCheckable(true);
    copyScaleAction->setCheckable(true);
    copyTranslationAction->setCheckable(true);
    copyRotationAction->setCheckable(true);
    GatherPointAction=std::make_unique<QAction>(tr("Gather Point"),nullptr);
    GatherPointAction->setCheckable(true);
    FindAction=std::make_unique<QAction>(tr("Find In NodeGraph"));
    DeleteAction=new QAction(tr("Delete"),nullptr);
    findByAction->setMenu(findByMenu.get());
    findByMenu->addAction(findByIndexer.get());
    findByMenu->addAction(findByShapeNode.get());
    SelectedMenu->addAction(DeleteAction);
    SelectedMenu->addAction(moveToSelectedFaceAction.get());
    SelectedMenu->addAction(findByAction.get());
    SelectedMenu->addAction(UndoAction);
    SelectedMenu->addAction(RedoAction);
    SelectedMenu->addAction(ScaleAction);
    SelectedMenu->addAction(RotateAction);
    SelectedMenu->addAction(TranslateAction);
    SelectedMenu->addAction(zbufferAction.get());
    SelectedMenu->addAction(DeleteObjectGizmoAction);
     SelectedMenu->addAction(TransformAction.get());
    SelectedMenu->addAction(ShapeTypeAction.get());
    SelectedMenu->addAction(ConstructPointNodeAction.get());
    SelectedMenu->addAction(ConstructTransformNodeAction.get());
    SelectedMenu->addAction(ConstructShapeNodeAction.get());
    SelectedMenu->addAction(FindAction.get());
    SelectedMenu->addAction(copyScaleAction.get());
    SelectedMenu->addAction(copyRotationAction.get());
    SelectedMenu->addAction(copyTranslationAction.get());
    SelectedMenu->addAction(CheckShapeIdAction.get());
    copyMaterial->setCheckable(true);
    SelectedMenu->addAction(copyMaterial.get());
    shouldSetAction->setCheckable(true);
   polyMenu=std::make_unique<PolygonMenu>();
    pointMenu->addAction(convertPoint.get());
    groupWireMenu->addAction(deleteGroupWire.get());
    groupWireMenu->addAction(endGroupWire.get());
    convertToWires->setCheckable(true);
    groupWireMenu->addAction(convertToWires.get());
    DockMenus=new QMenu;
    drawAction->setCheckable(true);
    showSettingAction=new QAction(tr("Show SceneSettings"),nullptr);  
    showSettingAction->setCheckable(true);
    DrawCubeAction=new QAction(tr("Draw Cube"),nullptr);
    DeleteObjectGizmoAction=new QAction(tr("Destroy Gizmo"),nullptr);
    refreshAction=std::make_unique<QAction>(tr("Refresh"),nullptr);
    GatherCurveAction=std::make_unique<QAction>(tr("Gather Bezier Points"),nullptr);
    GatherCurveAction->setCheckable(true);
    GatherBSplineAction=make_unique<QAction>(tr("Gather BSPline Points"),nullptr);
    GatherBSplineAction->setCheckable(true);
    polygonAction->setCheckable(true);
    createMaterialNode->setCheckable(true);
    arcMenuAction->setMenu(arcMenu.get());
    arcMenu->addAction(arcStart.get());

    arcMenu->addAction(arcDraw.get());
    editCircleMenu->addAction(editCircleAction.get());
    editCircleMenu->addAction(cancelEditCircle.get());
    moveMenu->addAction(startMove.get());
    moveMenu->addAction(executeMove.get());
    moveMenu->addAction(endMove.get());
    drawBSplineByDialogAction->setCheckable(true);
    drawBSplineMenu->addAction(startBSpline.get());
    drawBSplineMenu->addAction(continueBSpline.get());
    drawBSplineMenu->addAction(endBSpline.get());
    drawBezierMenu->addAction(startBezier.get());
    drawBezierMenu->addAction(continueBezier.get());
    drawBezierMenu->addAction(endBezier.get());

   transientPrimitiveAction->setMenu(transPrimMenu.get());
   transPrimMenu->addAction(primLine.get());
   transPrimMenu->addAction(primCircle.get());
   transPrimMenu->addAction(primArc.get());
   primLine->setCheckable(true);
   primCircle->setCheckable(true);
   primArc->setCheckable(true);
  
  LineAction=std::make_unique<QAction>(tr("Two Point Line"));
  LineAction->setCheckable(true);
  LineMenu=std::make_unique<QMenu>();
  fLinePoint->setCheckable(true);
  LineMenu->addAction(fLinePoint.get());
  sLinePoint->setCheckable(true);
  LineMenu->addAction(sLinePoint.get());
  convertToPrim->setCheckable(true);
  LineMenu->addAction(convertToPrim.get());
  LineMenu->addAction(endAction.get());
  LineMenu->addAction(build.get());
  convertToAxis->setCheckable(true);
  convertToLength->setCheckable(true);
  LineMenu->addAction(viewLength.get());
  LineMenu->addAction(viewAxis.get());
  LineMenu->addAction(convertToAxis.get());
  LineMenu->addAction(convertToLength.get());
   
  edgesMenu->addAction(convertEdgesToWire.get());
  edgesMenu->addAction(endGroupSelection.get());
   
  transMenu=std::make_unique<QMenu>();
  transAction=std::make_unique<QAction>(tr("Apply Relative Transform"));
  transAction->setCheckable(true);
  setShapeFixed=std::make_unique<QAction>(tr("Set Fixed"));
  setShapeFixed->setCheckable(true);
  transStartPoint=std::make_unique<QAction>(tr("Select First Point"));
  transEndPoint=std::make_unique<QAction>(tr("Select Second Point"));
   transStartPoint->setCheckable(true);
   transEndPoint->setCheckable(true);
   computeTrans=std::make_unique<QAction>(tr("Compute"));
   applyTransObject=std::make_unique<QAction>(tr("Apply Transform To Object"));
   endApply=std::make_unique<QAction>(tr("End"));
  transMenu->addAction(setShapeFixed.get());
  transMenu->addAction(transStartPoint.get());
  transMenu->addAction(transEndPoint.get());
  transMenu->addAction(computeTrans.get());
  transMenu->addAction(applyTransObject.get());
  transMenu->addAction(endApply.get());
  

  twoPntArcMenu=std::make_unique<QMenu>();
  twoPntArcAction=std::make_unique<QAction>(tr("Two Point Arc"));
  arcFirstPoint=std::make_unique<QAction>(tr("First Point"));
  twoPntArcAction->setCheckable(true);
  arcFirstPoint->setCheckable(true);
  arcSecondPoint=std::make_unique<QAction>(tr("Second Point"));
  arcSecondPoint->setCheckable(true);
  buildArc=std::make_unique<QAction>(tr("Build Arc"));
  endBuildArc=std::make_unique<QAction>(tr("End Build"));
  
  twoPntArcMenu->addAction(arcFirstPoint.get());
  twoPntArcMenu->addAction(arcSecondPoint.get());
  twoPntArcMenu->addAction(buildArc.get());
  twoPntArcMenu->addAction(endBuildArc.get());

  twoPntCircleMenu=std::make_unique<QMenu>();
  twoPntCircleAction=make_unique<QAction>(tr("Two Point Circle"));
  twoPntCircleAction->setCheckable(true);
  circleFirstPoint=make_unique<QAction>(tr("First Point"));
  circleSecondPoint=make_unique<QAction>(tr("Second Point"));
   circleFirstPoint->setCheckable(true);
   circleSecondPoint->setCheckable(true);
  buildCircle=std::make_unique<QAction>(tr("Build"));
  endBuildCircle=std::make_unique<QAction>(tr("End"));
  convertBuiltCircle=std::make_unique<QAction>(tr("Convert To Primitive Circle"));
  convertBuiltCircle->setCheckable(true);
  twoPntCircleMenu->addAction(circleFirstPoint.get());
  twoPntCircleMenu->addAction(circleSecondPoint.get());
  twoPntCircleMenu->addAction(buildCircle.get());
  twoPntCircleMenu->addAction(endBuildCircle.get());
  twoPntCircleMenu->addAction(convertBuiltCircle.get());

  
  chooseAxis=std::make_unique<QAction>(tr("Choose Axis"));
  chooseAxis->setCheckable(true);
  chooseAxisMenu=make_unique<QMenu>();
  defaultX=std::make_unique<QAction>(tr("Use Default X axis"));
  defaultX->setCheckable(true);
  defaultY=make_unique<QAction>(tr("Use Default Y axis"));
  defaultY->setCheckable(true);
  defaultZ=make_unique<QAction>(tr("Use Default Z axis"));
  defaultZ->setCheckable(true);
  chooseFace=make_unique<QAction>(tr("Choose Face"));
  chooseFace->setCheckable(true);
  chooseAxisMenu->addAction(defaultX.get());
  chooseAxisMenu->addAction(defaultY.get());
  chooseAxisMenu->addAction(defaultZ.get());
  chooseAxisMenu->addAction(chooseFace.get());
  endChooseAxis=std::make_unique<QAction>(tr("End"));
  setFaceFixed=make_unique<QAction>(tr("Set Face Fixed"));
  setFaceFixed->setCheckable(true);
  //this should be used when choose axis menu has been called
  chooseFaceNormal=std::make_unique<QAction>("Compute Surface Normal");
  chooseAxisMenu->addAction(chooseFaceNormal.get());
  chooseAxisMenu->addAction(chooseFace.get());
  chooseAxisMenu->addAction(endChooseAxis.get());
  edgeFilletMenu->addAction(chooseAxis.get());
  wireFilletMenu->addAction(chooseAxis.get());
  wireMenu->addAction(convertToEdgeColl.get());
  convertToEdgeColl->setCheckable(true);
   twoPntCircleMenu->addAction(chooseAxis.get());
   twoPntArcMenu->addAction(chooseAxis.get());
    DockMenus->addAction(showSettingAction);
    DockMenus->addAction(transientPrimitiveAction.get());
    DockMenus->addAction(createMaterialNode.get());
    DockMenus->addAction(UndoAction);
    DockMenus->addAction(RedoAction);
    DockMenus->addAction(transAction.get());
    DockMenus->addAction(ConstructPointNodeAction.get());
    DockMenus->addAction(convertPointAction.get());
    DockMenus->addAction(twoPntArcAction.get());
    DockMenus->addAction(twoPntCircleAction.get());
    DockMenus->addAction(refreshAction.get());
    DockMenus->addAction(drawAction.get());
    DockMenus->addAction(arcMenuAction.get());
    drawCircleAction->setMenu(drawCircleMenu.get());
    drawCircleMenu->addAction(circleDraw.get());
    drawCircleMenu->addAction(drawCircleByRadius.get());
    drawCircleByRadius->setCheckable(true);
    circleByRadiusMenu->addAction(startDrawCircle.get());
    circleByRadiusMenu->addAction(endDrawCircle.get());
    drawBezierByDialog->setCheckable(true);
    DockMenus->addAction(drawCircleAction.get());
    DockMenus->addAction(LineAction.get());
    DockMenus->addAction(polygonAction.get());
    DockMenus->addAction(drawBezierByDialog.get());
    DockMenus->addAction(drawBSplineByDialogAction.get());
    DockMenus->addAction(GatherPointAction.get());
    
    gatherWire->setCheckable(true);
    selectEdges->setCheckable(true);
    selectFaces->setCheckable(true);
    selectShapes->setCheckable(true);
    groupCollectionMenu->addAction(gatherWire.get());
    groupCollectionMenu->addAction(selectEdges.get());
    groupCollectionMenu->addAction(selectFaces.get());
    groupCollectionMenu->addAction(selectShapes.get());
    groupCollectionAction->setMenu(groupCollectionMenu.get());
    
    DockMenus->addAction(groupCollectionAction.get());
    DockMenus->addAction(GatherCurveAction.get());
    DockMenus->addAction(loadImage.get());
    DockMenus->addAction(GatherBSplineAction.get());
    DockMenus->addAction(shouldSetAction.get());
    
    
 display=new Aspect_DisplayConnection();
 driver=new OpenGl_GraphicDriver(display);
 Viewer=new V3d_Viewer(driver);
 view =Viewer->CreateView();   //Create the view from the viewer
 //Now to generate an id that can embed Qt project  
 context=new AIS_InteractiveContext(Viewer);
 drawLineDialog->SetContext(context);
 faceDialog->SetContext(context);
 circleDialog->SetContext(context);
 arcDialog->SetContext(context);
 circleEditDialog->SetContext(context);
 transCircleDialog->SetContext(context);
 bsplineDialog->SetContext(context);
 faceselector->SetContext(context);
 wireselectors->SetContext(context);
 transLineDialog->SetContext(context);
 transPolygon=std::make_unique<TransientPolygon>(std::ref(context));
 
 transCurve=make_unique<TransientBezierCurve>(std::ref(context));
 bspCurve=make_unique<TransientBSplineCurve>(std::ref(context));
 WId winid=winId();
Window=new WNT_Window((Aspect_Handle)winid);
 
 Viewer->SetLightOn();
 Viewer->SetDefaultLights();
 view->SetWindow(Window);
    Window->Map();
 view->SetBackgroundColor(Quantity_Color(0.18,0.18,0.18,Quantity_TOC_RGB));
   CreateWorldGrid();
view->MustBeResized();
 view->TriedronDisplay(Aspect_TOTP_RIGHT_UPPER,Quantity_NOC_SNOW,0.1,V3d_ZBUFFER);
 evt_manager.SetAllowZooming(false);
 evt_manager.SetAllowPanning(false);
 evt_manager.SetAllowRotation(false);
 editarcDialog->SetContext(context);
 wireselector->SetContext(context);
 shapeselector->SetContext(context);
 SphereShape=BRepPrimAPI_MakeSphere(gp_Ax2(gp_Pnt(0.0,0.0,50.0),gp_Dir(0.0,0.0,1.0)),50.0).Shape();
 ConeShape=BRepPrimAPI_MakeCone(gp_Ax2(gp_Pnt(0.0,0.0,0.0),gp_Dir(1.0,0.0,0.0)),0.0,60.0,50.0).Shape();
 CylShape=BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0.0,0.0,50.0),gp_Dir(0.0,1.0,0.0)),50.0,80.0).Shape();
 
 Handle(CustomAIS_Shape) sphereShape=new CustomAIS_Shape(SphereShape);
 sphereShape->ShadeFace(1, Quantity_NOC_MEDIUMPURPLE1);
 sphereShape->SetVisualAspect(Quantity_NOC_STEELBLUE4);
  
  
  OnChangeSelectionColor(Quantity_NOC_SNOW);
  OnChangeDetectedColor(Quantity_NOC_SEASHELL);
  OnChangeSubShapeSelectedColor(Quantity_NOC_STEELBLUE);
  OnChangeSubShapeDetectedColor( Quantity_NOC_WHEAT);
   drawBezierDialog->SetContext(context);
   edgeselector->SetContext(context);
   edgeselectors->SetContext(context);
   faceselectors->SetContext(context);
   shapeselectors->SetContext(context);
    context->Display(sphereShape,CurrentShadeMode,0,true);
 context->Display(new CustomAIS_Shape(ConeShape),CurrentShadeMode,0,true);
 context->Display(new CustomAIS_Shape(CylShape),CurrentShadeMode,0,true);
  
 context->Display(viewcube,true);
 
 
 

 connect(DeleteAction,&QAction::triggered,this,&DrawingCentralWidget::OnDeleteObject);
 connect(UndoAction,&QAction::triggered,this,&DrawingCentralWidget::UndoStackContent);
 connect(RedoAction,&QAction::triggered,this,&DrawingCentralWidget::RedoStackContent);
 connect(showSettingAction,&QAction::toggled,this,&DrawingCentralWidget::OnShowSceneSetting);
 connect(RotateAction,&QAction::toggled,this,&DrawingCentralWidget::EnableRotation);
 connect(ScaleAction,&QAction::toggled,this,&DrawingCentralWidget::EnableScaling);
 connect(TranslateAction,&QAction::toggled,this,&DrawingCentralWidget::EnableTranslation);
 connect(DeleteObjectGizmoAction,&QAction::triggered,this,&DrawingCentralWidget::OnDestroyObjectGizmo);
 connect(ShapePrsAction,&QAction::triggered,this,&DrawingCentralWidget::OnSendRenderShapePrs);
 connect(convertPointAction.get(),&QAction::toggled,this,&DrawingCentralWidget::OnConvertToFacePoint);
 connect(refreshAction.get(),&QAction::triggered,this,&DrawingCentralWidget::OnRefreshView);
 connect(faceMenu->convertAction.get(),&QAction::toggled,this,&DrawingCentralWidget::OnConvertToFaceNode);
 connect(faceMenu->searchAction.get(),&QAction::triggered,this,&DrawingCentralWidget::OnHandleFaceSent);
 connect(edgeMenu->convertToFaceAction.get(),&QAction::toggled,this,&DrawingCentralWidget::OnConvertEdgeToFace);
 connect(polyMenu->deleteAction.get(),&QAction::triggered,this,&DrawingCentralWidget::OnDeletePoints);
 connect(polyMenu->removeLastAction.get(),&QAction::triggered,this,&DrawingCentralWidget::OnRemoveLastOne);
 connect(polyMenu->convertToBSpline.get(),&QAction::triggered,this,&DrawingCentralWidget::OnConvertToBSpline);
 connect(GatherPointAction.get(),&QAction::toggled,this,&DrawingCentralWidget::OnGatherPoint);
 connect(GatherCurveAction.get(),&QAction::toggled,this,&DrawingCentralWidget::OnGatherBezier);
 connect(bMenu->deleteAction.get(),&QAction::triggered,this,&DrawingCentralWidget::OnDeleteBezier);
 connect(spMenu->IsPeriodicAction.get(),&QAction::toggled,this,&DrawingCentralWidget::OnHandlePeriodic);
 connect(GatherBSplineAction.get(),&QAction::toggled,this,&DrawingCentralWidget::OnGatherBSpline);
 connect(spMenu->deleteAction.get(),&QAction::triggered,this,&DrawingCentralWidget::OnDeleteBSplinePoint);
 connect(FindAction.get(),&QAction::triggered,this,&DrawingCentralWidget::OnHandleSent);
 connect(findByShapeNode.get(),&QAction::triggered,this,&DrawingCentralWidget::OnHandleSent);
 connect(CheckShapeIdAction.get(),&QAction::triggered,this,&DrawingCentralWidget::OnKnowId);
 connect(convertPoint.get(),&QAction::toggled,this,&DrawingCentralWidget::OnSendPointValues);
 connect(pointMenu->DeleteAction.get(),&QAction::triggered,this,&DrawingCentralWidget::OnDestroyMarker);
 connect(edgeMenu->convertToWireAction.get(),&QAction::toggled,this,&DrawingCentralWidget::OnSendWire);
 connect(edgeMenu->convertAction.get(),&QAction::toggled,this,&DrawingCentralWidget::OnConvertToEdge);
 connect(copyTranslationAction.get(),&QAction::toggled,this,&DrawingCentralWidget::OnHandleSentTranslateTransform);
 connect(copyRotationAction.get(),&QAction::toggled,this,&DrawingCentralWidget::OnHandleSentRotateTransform);
 connect(copyScaleAction.get(),&QAction::toggled,this,&DrawingCentralWidget::OnHandleSentScaleTransform);
 connect(faceMenu->assumeFaceNormal.get(),&QAction::triggered,this,&DrawingCentralWidget::OnAssumeFaceNormal);
 connect(axisMenu->convertToAxisNode.get(),&QAction::toggled,this,&DrawingCentralWidget::OnHandleOriginAxis);
 connect(axisMenu->convertToPositionedAxis.get(),&QAction::toggled,this,&DrawingCentralWidget::OnHandlePositionedAxis);
 connect(deleteAxisObject.get(),&QAction::triggered,this,&DrawingCentralWidget::OnRemoveAxisObject);
 connect(faceNormalAction.get(),&QAction::triggered,this,&DrawingCentralWidget::AssumeFaceCenterNormal);
 connect(convertFacePointAction.get(),&QAction::toggled,this,&DrawingCentralWidget::OnGetFacePoint);
 connect(edgeMenu->showInfoAction.get(),&QAction::triggered,this,&DrawingCentralWidget::OnGetEdgeInfo);
 connect(drawAction.get(),&QAction::toggled,this,&DrawingCentralWidget::OnHandleDrawLine);
 connect(drawLineMenu->drawLineAction.get(),&QAction::triggered,this,&DrawingCentralWidget::InitializeDrawDialog);
 connect(drawLineMenu->stopLineAction.get(),&QAction::triggered,this,&DrawingCentralWidget::OnStopDrawingLine);
 connect(drawLineDialog.get(),&DrawLineDialog::OnEmitDone,this,&DrawingCentralWidget::OnHandleDone);
 connect(drawCircle->firstPoint.get(),&QAction::toggled,this,&DrawingCentralWidget::OnHandleFirstPoint);
 connect(drawCircle->secondPoint.get(),&QAction::toggled,this,&DrawingCentralWidget::OnHandleSecondPoint);
 connect(drawCircle->thirdPoint.get(),&QAction::toggled,this,&DrawingCentralWidget::OnHandleThirdPoint);
 connect(drawCircle->stopCircle.get(),&QAction::triggered,this,&DrawingCentralWidget::OnHandleStopCircle);
 connect(circleDraw.get(),&QAction::triggered,this,&DrawingCentralWidget::InitCircleDraw);
 connect(drawCircle->destroyCircleOps.get(),&QAction::triggered,this,&DrawingCentralWidget::OnDestroyCircle);
 connect(drawPolygonDialog.get(),&DrawPolygonDialog::OnPolygonDone,this,&DrawingCentralWidget::OnHandlePolygonDone);
 connect(drawPolyMenu->startPolygonAction.get(),&QAction::triggered,this,&DrawingCentralWidget::OnInitDrawPolygon);
 connect(drawPolyMenu->continueAction.get(),&QAction::triggered,this,&DrawingCentralWidget::OnContinuePolygon);
 connect(drawPolyMenu->endPolygonAction.get(),&QAction::triggered,this,&DrawingCentralWidget::OnEndPolygon);
 connect(drawPolyMenu->closeAction.get(),&QAction::triggered,this,&DrawingCentralWidget::ClosePolygon);
 connect(drawPolyMenu->convertToWireAction.get(),&QAction::triggered,this,&DrawingCentralWidget::OnConvertPolygonToWire);
 connect(drawPolyMenu->convertToFaceAction.get(),&QAction::triggered,this,&DrawingCentralWidget::OnConvertToFace);
 connect(polygonAction.get(),&QAction::toggled,this,&DrawingCentralWidget::OnStartPolygon);
 connect(faceMenu->applyChamfer.get(),&QAction::toggled,this,&DrawingCentralWidget::OnApplyChamfer);
 connect(faceMenu->applyFillet.get(),&QAction::toggled,this,&DrawingCentralWidget::OnApplyFillet);
 connect(chamferMenu->chooseVertexAction.get(),&QAction::toggled,this,&DrawingCentralWidget::OnChooseChamferVertex);
 connect(filletMenu->chooseVertexAction.get(),&QAction::toggled,this,&DrawingCentralWidget:: OnChooseFilletVertex);
 connect(chamferMenu->chooseEdgeAction.get(),&QAction::toggled,this,&DrawingCentralWidget::OnChooseEdgeForChamfer);
 connect(filletMenu->SelectRadiusAction.get(),&QAction::triggered,this,&DrawingCentralWidget::OnSelectRadiusForFillet);
 connect(chamferMenu->SelectOthersAction.get(),&QAction::triggered,this,&DrawingCentralWidget::OnSelectOthersForChamfer);
 connect(filletMenu->BuildFilletAction.get(),&QAction::triggered,this,&DrawingCentralWidget::BuildFillet);
 connect(chamferMenu->BuildAction.get(),&QAction::triggered,this,&DrawingCentralWidget::BuildChamfer);
 connect(chamferMenu->endChamferOps.get(),&QAction::triggered,this,&DrawingCentralWidget::EndChamfer);
 connect(filletMenu->endFilletOps.get(),&QAction::triggered,this,&DrawingCentralWidget::EndFillet); 
 connect(copyMaterial.get(),&QAction::toggled,this,&DrawingCentralWidget::OnHandleCopyMaterial);
 connect(edgeMenu->trimAction.get(),&QAction::toggled,this,&DrawingCentralWidget::OnHandleTrim);
 connect(edgeMenu->convertwireAction.get(),&QAction::triggered,this,&DrawingCentralWidget::OnHandleConvertEdgeToWire);
 connect(trimMenu->TrimAction(),&QAction::triggered,this,&DrawingCentralWidget::OnTrimCurve);
 connect(trimMenu->EndOps(),&QAction::triggered,this,&DrawingCentralWidget::OnEndTrim);
 connect(faceDialog.get(),&FaceLineDialog::Done,this,&DrawingCentralWidget::OnHandleFaceDone);
 connect(faceMenu->DrawAction.get(),&QAction::triggered,this,&DrawingCentralWidget::OnHandleFaceDrawAction);
 connect(edgeMenu->filletAction.get(),&QAction::toggled,this,&DrawingCentralWidget::OnSetToFillet);
 connect(edgeFilletMenu->chooseFirstEdge.get(),&QAction::toggled,this,&DrawingCentralWidget::OnHandleFirstEdge);
 connect(edgeFilletMenu->chooseSecondEdge.get(),&QAction::toggled,this,&DrawingCentralWidget::OnHandleSecondEdge);
 connect(edgeFilletMenu->chooseVertex.get(),&QAction::toggled,this,&DrawingCentralWidget::OnHandleChosenFilletVertex);
 connect(edgeFilletMenu->selectRadius.get(),&QAction::triggered,this,&DrawingCentralWidget::OnSelectRadiusForFillet);
 connect(edgeFilletMenu->buildAction.get(),&QAction::triggered,this,&DrawingCentralWidget::OnApplyFilletToEdges);
 connect(edgeFilletMenu->endFilletOps.get(),&QAction::triggered,this,&DrawingCentralWidget::OnHandleEndOps);
 connect(wireMenu->convertToNode.get(),&QAction::toggled,this,&DrawingCentralWidget::OnConvertToWireNode);
 connect(wireMenu->applyFillet.get(),&QAction::triggered,this,&DrawingCentralWidget::ApplyFilletToWire);
 connect(wireMenu->chooseVertex.get(),&QAction::triggered,this,&DrawingCentralWidget::OnChooseVertexForWire);
 connect(wireMenu->chooseRadius.get(),&QAction::triggered,this,&DrawingCentralWidget::OnSelectRadiusForFillet);
 connect(circleDialog.get(),&CircleDialog::Done,this,&DrawingCentralWidget::OnHandleDoneForCircleDialog);
 connect(wireMenu->convertToFace.get(),&QAction::triggered,this,&DrawingCentralWidget::OnConvertToFaceShape);
 connect(drawCircleByRadius.get(),QAction::toggled,this,&DrawingCentralWidget::DrawCircleOnBool);
 connect(startDrawCircle.get(),&QAction::triggered,this,&DrawingCentralWidget::OnHandleCircleDialog);
 connect(endDrawCircle.get(),&QAction::triggered,this,&DrawingCentralWidget::EndRadiusOps); 
 connect(trimMenu->PointAction(),&QAction::triggered,this,&DrawingCentralWidget::TrimByPoints); 
 connect(wireFilletMenu->selectFirstEdge.get(),&QAction::toggled,this,&DrawingCentralWidget::OnGetFirstEdgeOnWire);
 connect(wireFilletMenu->selectSecondEdge.get(),&QAction::toggled,this,&DrawingCentralWidget::OnGetSecondEdgeOnWire);
 connect(wireFilletMenu->selectRadius.get(),&QAction::triggered,this,&DrawingCentralWidget::OnSelectRadiusForFillet);
 connect(wireFilletMenu->build.get(),&QAction::triggered,this,&DrawingCentralWidget::OnApplyFilletToSetOfEdges);
 connect(wireFilletMenu->endOps.get(),&QAction::triggered,this,&DrawingCentralWidget::OnEndWireFilletOps);
 connect(wireMenu->applyFillet.get(),&QAction::toggled,this,&DrawingCentralWidget::SetOnApplyFilletToAllBool);
 connect(wireFilletMenu->selectPoint.get(),&QAction::toggled,this,&DrawingCentralWidget::OnChooseVertexForWire);
 connect(edgeMenu->editLine.get(),&QAction::triggered,this,&DrawingCentralWidget::OnHandleEditCircle);
 connect(edgeMenu->updateLineEdit.get(),&QAction::triggered,this,&DrawingCentralWidget::RecomputeLinePrs);
 connect(edgeMenu->removeLineEdit.get(),&QAction::triggered,this,&DrawingCentralWidget::RemoveLineEdit);
 connect(edgeMenu->nullify.get(),&QAction::triggered,this,&DrawingCentralWidget::OnDestroyLineShape);
 connect(edgeMenu->alignWithDir.get(),&QAction::triggered,this,&DrawingCentralWidget::AlignWithDirection);
 connect(arcStart.get(),&QAction::triggered,this,&DrawingCentralWidget::OnStartArcDraw);
 connect(arcDraw.get(),&QAction::triggered,this,&DrawingCentralWidget::OnInitiateArcDraw);
 connect(arcDialog.get(),&DrawArcDialog::Done,this,&DrawingCentralWidget::OnHandleArcDraw);
 connect(edgeMenu->update.get(),&QAction::triggered,this,&DrawingCentralWidget::OnUpdateWithTransform);
 connect(editCircleAction.get(),&QAction::triggered,this,&DrawingCentralWidget::OnEditCircle);
 connect(circleEditDialog.get(),&EditDialog::Done,this,&DrawingCentralWidget::OnHandleDoneForCircleEdit);
 connect(cancelEditCircle.get(),&QAction::triggered,this,&DrawingCentralWidget::OnHandleCircleEdit);
 connect(updateWithTransform.get(),&QAction::triggered,this,&DrawingCentralWidget::OnHandleForUpdateForTransform);
 connect(drawBezierByDialog.get(),&QAction::toggled,this,&DrawingCentralWidget::OnInitBezier);
 connect(drawBezierDialog.get(),&DrawBezierDialog::OnBezierDone,this,&DrawingCentralWidget::OnHandleBezierDone);
 connect(startBezier.get(),&QAction::triggered,this,&DrawingCentralWidget::OnStartPointForBezier);
 connect(endBezier.get(),&QAction::triggered,this,&DrawingCentralWidget::OnEndBezier);
 connect(continueBezier.get(),&QAction::triggered,this,&DrawingCentralWidget::OnContinueBezier);
 connect(startMove.get(),&QAction::triggered,this,&DrawingCentralWidget::OnHandleStartMove);
 connect(moveToSelectedFaceAction.get(),&QAction::toggled,this,&DrawingCentralWidget::OnMoveToFace);
 connect(executeMove.get(),&QAction::triggered,this,&DrawingCentralWidget::OnExecuteMove);
 connect(endMove.get(),&QAction::triggered,this,&DrawingCentralWidget::OnEndMove);
 connect(loadImage.get(),&QAction::triggered,this,&DrawingCentralWidget::OnExecuteImage);
 connect(imageDialog.get(),&ImageDialog::EmitDone,this,&DrawingCentralWidget::OnHandleImageDone);
 connect(bsplineDialog.get(),&DrawBSplineDialog::OnBSplineDone,this,&DrawingCentralWidget::OnHandleBSplineDone);
 connect(drawBSplineByDialogAction.get(),&QAction::toggled,this,&DrawingCentralWidget::OnInitBSpline);
 connect(startBSpline.get(),&QAction::triggered,this,&DrawingCentralWidget::OnStartPointForBSpline);
 connect(continueBSpline.get(),&QAction::triggered,this,&DrawingCentralWidget::OnContinueBSpline);
 connect(endBSpline.get(),&QAction::triggered,this,&DrawingCentralWidget::OnEndBSpline);
 connect(editarcDialog.get(),&EditArcDialog::EmitDone,this,&DrawingCentralWidget::OnHandleArcEditDialogDone);
 connect(gatherWire.get(),&QAction::toggled,this,&DrawingCentralWidget::OnGatherWire);
 connect(endGroupWire.get(),&QAction::triggered,this,&DrawingCentralWidget::EndSelectWires);
 connect(convertToWires.get(),&QAction::toggled,this,&DrawingCentralWidget::OnSelectWires);
 connect(faceMenu->showInfoAction.get(),&QAction::triggered,this,&DrawingCentralWidget::OnGetFaceInfo);
 connect(faceMenu->convertToPointNode.get(),QAction::toggled,this,&DrawingCentralWidget::OnSendPointValues);
 connect(edgeMenu->convertToPointNode.get(),&QAction::toggled,this,&DrawingCentralWidget::OnSendPointValues);
 connect(wireMenu->convertToPointNode.get(),&QAction::toggled,this,&DrawingCentralWidget::OnSendPointValues);
 connect(selectEdges.get(),&QAction::toggled,this,&DrawingCentralWidget::OnHandleGatheredEdges);
 connect(selectFaces.get(),&QAction::toggled,this,&DrawingCentralWidget::OnHandleGatheredFace);
 connect(selectShapes.get(),&QAction::toggled,this,&DrawingCentralWidget::OnHandleGatheredShape);
 connect(primLineMenu->Start(),&QAction::triggered,this,&DrawingCentralWidget::OnHandleStartForTransLineDialog);
 connect(primLineMenu->Continue(),&QAction::triggered,this,&DrawingCentralWidget::onHandleContinueForTransLineDialog);
 connect(primLineMenu->CopyAxis(),&QAction::toggled,this,&DrawingCentralWidget::OnHandleCopyAxis);
 connect(primLineMenu->CopyLength(),&QAction::toggled,this,&DrawingCentralWidget::OnHandleCopyLength);
 connect(primLineMenu->End(),&QAction::triggered,this,&DrawingCentralWidget::OnEndPrimLine);
 connect(primLineMenu->NullifyShape(),&QAction::triggered,this,&DrawingCentralWidget::OnHandleNullifyShape);
 connect(primLineMenu->Convert(),&QAction::toggled,this,&DrawingCentralWidget::OnHandleConvertPrimLine);
 connect(primLine.get(),&QAction::toggled,this,&DrawingCentralWidget::OnStartPrimLine);
 connect(primCircle.get(),&QAction::toggled,this,&DrawingCentralWidget::OnStartPrimCircle);
 connect(primCircleMenu->Start(),&QAction::triggered,this,&DrawingCentralWidget::OnHandlePrimCircle);
 connect(primCircleMenu->Continue(),&QAction::triggered,this,&DrawingCentralWidget::OnContinuePrimCircle);
 connect(primCircleMenu->End(),&QAction::triggered,this,&DrawingCentralWidget::OnEndPrimCircle);
 connect(primCircleMenu->Nullify(),&QAction::triggered,this,&DrawingCentralWidget::OnHandleNullifyCircleShape);
 connect(primCircleMenu->CopyAxis(),&QAction::toggled,this,&DrawingCentralWidget::OnHandleCopyCircleAxis);
 connect(primCircleMenu->CopyRadius(),&QAction::toggled,this,&DrawingCentralWidget::OnHandleCopyRadius);
 connect(LineAction.get(),&QAction::toggled,this,&DrawingCentralWidget::OnHandleTwoPointLine);
 connect(fLinePoint.get(),&QAction::toggled,this,&DrawingCentralWidget::OnHandleFirstTwoPoint);
 connect(sLinePoint.get(),&QAction::toggled,this,&DrawingCentralWidget::OnHandleSecondTwoPoint);
 connect(convertToPrim.get(),&QAction::toggled,this,&DrawingCentralWidget::OnConvertTwoPointToPrimLine);
 connect(endAction.get(),&QAction::triggered,this,&DrawingCentralWidget::EndTwoPointLine);
 connect(build.get(),&QAction::triggered,this,&DrawingCentralWidget::OnBuildAction);
 connect(convertToAxis.get(),&QAction::toggled,this,&DrawingCentralWidget::OnHandleTwoPointAxis);
 connect(viewLength.get(),&QAction::triggered,this,&DrawingCentralWidget::OnHandleViewLength);
 connect(viewAxis.get(),&QAction::triggered,this,&DrawingCentralWidget::OnHandleViewAxis);
 connect(convertEdgesToWire.get(),&QAction::triggered,this,&DrawingCentralWidget::OnConvertSetEdgesToWire);
 connect(endGroupSelection.get(),&QAction::triggered,this,&DrawingCentralWidget::OnHandleGroupSelectionForEdges);
 connect(TransformAction.get(),&QAction::toggled,this,&DrawingCentralWidget::OnStartTransform);
 connect(endTransform.get(),&QAction::triggered,this,&DrawingCentralWidget::OnHandleEndTransform);
 connect(applyTransform.get(),&QAction::triggered,this,&DrawingCentralWidget::OnHandleApplyTransform);
 connect(setFixed.get(),&QAction::toggled,this,&DrawingCentralWidget::SetFixedState);
 connect(redisplayGizmo.get(),&QAction::triggered,this,&DrawingCentralWidget::RedisplayGizmo);
 connect(defaultAction.get(),&QAction::toggled,this,&DrawingCentralWidget::OnHandleDefaultDepth);
 connect(topAction.get(),&QAction::toggled,this,&DrawingCentralWidget::OnHandleTopDepth);
 connect(topMostAction.get(),&QAction::toggled,this,&DrawingCentralWidget::OnHandleTopMostDepth);
 connect(transStartPoint.get(),&QAction::toggled,this,&DrawingCentralWidget::OnHandleTransFirstPoint);
 connect(transEndPoint.get(),&QAction::toggled,this,DrawingCentralWidget::OnHandleTransSecondPoint);
 connect(setShapeFixed.get(),&QAction::toggled,this,&DrawingCentralWidget::OnHandleTransFixed);
 connect(computeTrans.get(),&QAction::triggered,this,&DrawingCentralWidget::ComputeTransformForHandle);
 connect(applyTransObject.get(),&QAction::triggered,this,&DrawingCentralWidget::ApplyTransToTopoDS_Shape);
 connect(endApply.get(),&QAction::triggered,this,&DrawingCentralWidget::OnEndTransShape);
 connect(transAction.get(),&QAction::toggled,this,DrawingCentralWidget::OnStartTransShape);
 connect(twoPntArcAction.get(),&QAction::toggled,this,&DrawingCentralWidget::OnHandleTwoPntArc);
 connect(arcFirstPoint.get(),&QAction::toggled,this,&DrawingCentralWidget::OnHandleFirstArcPoint);
 connect(arcSecondPoint.get(),&QAction::toggled,this,&DrawingCentralWidget::OnHandleArcSecondPoint);
 connect(buildArc.get(),&QAction::triggered,this,&DrawingCentralWidget::OnHandleBuildArc);
 connect(endBuildArc.get(),&QAction::triggered,this,&DrawingCentralWidget::OnHandleEndBuildArc);
 connect(twoPntCircleAction.get(),&QAction::toggled,this,&DrawingCentralWidget::OnHandleTwoPointCircle);
 connect(circleFirstPoint.get(),&QAction::toggled,this,&DrawingCentralWidget::OnHandleCircleFirstPoint);
 connect(circleSecondPoint.get(),&QAction::toggled,this,&DrawingCentralWidget::OnHandleCircleSecondPoint);
 connect(buildCircle.get(),&QAction::triggered,this,&DrawingCentralWidget::OnHandleBuildCircle);
 connect(endBuildCircle.get(),&QAction::triggered,this,&DrawingCentralWidget::OnEndBuildCircle);
 connect(chooseFace.get(),&QAction::toggled,this,&DrawingCentralWidget::OnHandleSelectedFace);
 connect(endChooseAxis.get(),&QAction::triggered,this,&DrawingCentralWidget::EndChooseAxis);
 connect(setFaceFixed.get(),&QAction::toggled,this,&DrawingCentralWidget::OnHandleSetFixedFace);
 connect(defaultX.get(),&QAction::toggled,this,&DrawingCentralWidget::OnChooseDefaultX);
 connect(defaultY.get(),&QAction::toggled,this,&DrawingCentralWidget::OnChooseDefaultY);
 connect(defaultZ.get(),&QAction::toggled,this,&DrawingCentralWidget::OnChooseDefaultZ);
 connect(chooseFaceNormal.get(),&QAction::triggered,this,&DrawingCentralWidget::OnComputeSurfaceNormal);
 connect(chooseAxis.get(),&QAction::toggled,this,&DrawingCentralWidget::OnStartChooseAxis);
 connect(edgeMenu->endEdgeMenu.get(),QAction::triggered,this,&DrawingCentralWidget::EndEdgeMenu);
 connect(faceMenu->endFaceMenu.get(),&QAction::triggered,this,&DrawingCentralWidget::EndFaceMenu);
 connect(wireMenu->endWireMenu.get(),&QAction::triggered,this,&DrawingCentralWidget::EndWireMenu);
 return;

}

  
void OnHighlight(Handle(CustomAIS_Shape)& cshape,const TopoDS_Shape& selshape,const int& mode){
  if(!cshape){
     return;
  }
  if(selshape.IsSame(TopoDS_Shape()) && mode!=0){
     return;
  }
  switch(mode){
    case 0:{
      
      break;
    }
    case 2:{
      cshape->HighlightEdge(TopoDS::Edge(selshape), Quantity_NOC_BURLYWOOD);
      break;
    }
    case 4:{
      cshape->HighlightFace(TopoDS::Face(selshape), Quantity_NOC_BURLYWOOD);
      break;
    }
  }
}
void PrintTheTriples(const gp_Pnt& pnt){
  cout<<"X:"<<pnt.X()<<"\n";
  cout<<"Y:"<<pnt.Y()<<"\n";
  cout<<"Z:"<<pnt.Z()<<"\n";
  return;
}
void UnHighlight(Handle(CustomAIS_Shape)& cshape,const int& mode){
  if(!cshape){
  return;
}
   switch(mode){
    case 0:{
      
      break;
    }
    case 2:{
      cshape->UnhighlightEdge();
      break;
    }
    case 4:{
      cshape->UnhighlightFace();
      break;
    }
  }
}










void LoadInfo(const QString& info,const QString& title){
  auto ret=QMessageBox::information(nullptr,title,info);

  return;
}
void OnHandleWireError(const BRepBuilderAPI_WireError& error,int& success){
  switch(error){
    case BRepBuilderAPI_WireDone:{
      LoadInfo(tr("Loop is successfully Created"),tr("Wire Info"));
      success=1;
      break;
    }
    case BRepBuilderAPI_EmptyWire:{
      LoadInfo(tr("Empty Wire was Formed"),tr("Wire Error"));
      success=-1;
      break;
    }
    case BRepBuilderAPI_DisconnectedWire:{
      LoadInfo(tr("The Wire is not Fully Connected"),tr("Wire Error"));
      success=-1;
      break;
    }
    case BRepBuilderAPI_NonManifoldWire:{
      LoadInfo(tr("A Non Manifold Wire was created"),tr("Wire Error"));
      success=-1;
      break;
    }
  }
  return;
}
void OnHandleFaceError(const BRepBuilderAPI_FaceError& error,int& success){
    switch(error){
    case BRepBuilderAPI_FaceDone:{
      LoadInfo(tr("Face Is Successfully Constructed"),tr("Face Info"));
      success=1;
      break;
    }
    case BRepBuilderAPI_NoFace:{
      LoadInfo(tr("No Face Is Created"),tr("Face Error"));
      success=-1;
      break;
    }
    case BRepBuilderAPI_NotPlanar:{
      LoadInfo(tr("The Face Formed Is Not Planar"),tr("Face Error"));
      success=-1;
      break;
    }
    case BRepBuilderAPI_CurveProjectionFailed:{
      LoadInfo(tr("Curve Projection Failed"),tr("Face Error"));
      success=-1;
      break;
    }
    case BRepBuilderAPI_ParametersOutOfRange:{
      LoadInfo(tr("The Parameters Supplied to limit the surface are out of bounds"),tr("Face Error"));
      success=-1;
      break;
    }
    default:{
     LoadInfo(tr("Don't Know"),tr("Face Error"));
    }
    }
    return;
}
void FindSubShapeIndex(const Handle(CustomAIS_Shape)& cshape,const int& mode){
  //0 for edge,
  //1 for face
  //2 for the shape

  switch(mode){
    case 0:{
      edgeIndex=cshape->FindEdge(selEdge);
      break;
    }
    case 1:{
      faceIndex=cshape->FindFace(selFace);
      subMainIndex=faceIndex;
      break;
    }
    default:
     break;
  }
  return;
}
void ConvertEdgeToWire(){
  if(selEdge.IsNull()){
    return;
  }
  int success;
  BRepBuilderAPI_MakeWire wireBuilder(selEdge);
  OnHandleWireError(wireBuilder.Error(),success);
  if(success==-1){
    LoadInfo(tr("Failed"),tr("Wire Error"));
    return;
  }
  selWire=wireBuilder.Wire();
  return;
}
void ConvertEdgeToFace(){
  if(selEdge.IsNull()){
    return;
  }
  int success;
  BRepBuilderAPI_MakeWire wireBuilder(selEdge);
  OnHandleWireError(wireBuilder.Error(),success);
  if(success==-1){
    LoadInfo(tr("Failed"),tr("Wire Error"));
    return;
  }
  TopoDS_Wire wire=wireBuilder.Wire();
  BRepBuilderAPI_MakeFace faceBuilder(wire);
  OnHandleFaceError(faceBuilder.Error(),success);
  if(!faceBuilder.IsDone()){
    LoadInfo(tr("Failed To Build Face"),tr("Face Error"));
    return;
  }
  convertedEdgeFace=faceBuilder.Face();
  return;
}
Handle(ViewCube) viewCube() {
  return viewcube;
}

void OnGetEmitShape(const TopoDS_Shape& shape){
   if(context.IsNull()){
       emit QueryDebugMessage(tr("Context Cannot be Null"));
        return;
      }
      if(Shapes.empty()){
         return;
    }
    for(auto iter=Shapes.begin();iter!=Shapes.end();++iter){
        if(iter->second->Shape().IsSame(shape)){
           emittedShape=iter->second;
           std::cout<<"Face found"<<"\n";
           break;
        }
    }
  return;
}
//highlight an edge
void HighlightEdge(const TopoDS_Shape& edge){
   if(emittedShape.IsNull()){
     return;
  }
  if(edge.IsSame(TopoDS_Shape())){
    return;
  }
 
  
  
  return;
}
void DisplayObjectFromSuccessfullRead(const TopoDS_Shape& shape){
  Handle(CustomAIS_Shape) displayedshape=new CustomAIS_Shape(shape);
  context->Display(displayedshape,true);
  
  return;
}
void DisplayObjectsFromSuccessfullRead(const std::vector<TopoDS_Shape>& shapes_1){
  if(shapes_1.empty()){
     return;
  }
  for(int i=0;i<shapes_1.size();i++){
    DisplayObjectFromSuccessfullRead(shapes_1.at(i));
  }
  return;
}

/*
void OnChangeSelectionAspect();
void OnChangeSubShapeSelectionAspect();
void OnChangeDynamicAspect();
void OnChangeSubShapeDynamicAspect();





*/
//highlight a face
void HighlightFace(const int& id){
  if(emittedShape.IsNull()){
     return;
  }
  if(prevEmittedShape.IsNull()){
    std::cout<<"Current Shaded Face Index "<<id<<"\n";
    emittedShape->ShadeFace(id,Quantity_NOC_ORANGE);
    faceIndex=id;
    prevEmittedShape=emittedShape;
    if(!context.IsNull()){
      context->Redisplay(emittedShape,true);
    }
    return;
  }
  if(prevEmittedShape==emittedShape){
    if(faceIndex==id){
       context->Redisplay(emittedShape,true);
       return;
    }
    else{
      emittedShape->UnShadeFace(faceIndex);
      context->Redisplay(emittedShape,false);
      faceIndex=id;
      emittedShape->ShadeFace(faceIndex,Quantity_NOC_ORANGE);
       context->Redisplay(emittedShape,true);
      return;
    }
    
  }
  if(prevEmittedShape!=emittedShape){
      prevEmittedShape->UnShadeFace(faceIndex);
       context->Redisplay(prevEmittedShape,true);
       emittedShape->ShadeFace(id,Quantity_NOC_ORANGE);
       faceIndex=id;
       prevEmittedShape=emittedShape;
       context->Redisplay(emittedShape,true);

  }
  
  
  return;
}

/*
Algorithm For Highlighting Subshapes
compare a sub part of shape with every object in the scene
we will check if the shape is either a vertex,edge,edge loop(Wire),Face,Shell,Solid Or CompoSolid...
we will then loop through the shapes in the scene,After Finding it, we will highlight the section
shape.IsSame(for every [either vertex,edge,wire loop,face,shell,solid, CompoSolid])

*/

void HighlightSubShapes(const TopoDS_Shape& shape){
     if(context.IsNull()){
       emit QueryDebugMessage(tr("Context Cannot be Null"));
        return;
      }
      if(Shapes.empty()){
         return;
         }
         cout<<"Shape Size:"<<Shapes.size()<<endl;
     
      for(auto iter=Shapes.begin();iter!=Shapes.end();++iter){
           currentObject=iter->second;
           if(currentObject.IsNull()){
             emit QueryDebugMessage(tr("No Successful Casting"));
             std::cout<<"Object Is Currently Null "<<std::endl;
             continue;
           }
          if(!prevCurrentObject.IsNull()){
            if(prevCurrentObject->Shape().IsSame(shape)){ //it is possible to refer to the same pointer Object
              currentObject->SetVisualAspect( Quantity_NOC_STEELBLUE);
              context->Redisplay(currentObject,true);
              std::cout<<"Previous Object is Equal to CurrentObject"<<std::endl;
              break;
            }
            else{
              if(currentObject->Shape().IsSame(shape)){
              prevCurrentObject->SetVisualAspect(currentObjectColor);
              context->Redisplay(prevCurrentObject,true);
              prevCurrentObject=currentObject;
              currentObject->Color(currentObjectColor);
              currentObject->SetVisualAspect( Quantity_NOC_STEELBLUE);
              context->Redisplay(currentObject,true);
              std::cout<<"Another Object when Previous Shape Is Null Is Currently Selected "<<std::endl;
              break;
              }
              else{
                std::cout<<"Continue Searching"<<std::endl;

                continue;
              }
              
              }
             
            }
           else{
          if(currentObject->Shape().IsSame(shape)){   //this algorithm is wrong
              prevCurrentObject=currentObject;
              currentObject->Color(currentObjectColor);
              currentObject->SetVisualAspect(Quantity_NOC_STEELBLUE);
              context->Redisplay(currentObject,true);
              std::cout<<"Object Is Currently Selected"<<std::endl;
              break;
            }
         }
         }
         return;
      }

 void OnDebugGizmo(const Handle(AIS_Manipulator)& manip){
  
  if(manip.IsNull()){
    std::cout<<"Gizmo is Empty"<<"\n";
    return;
  }
  gp_Trsf trsf=manip->Object()->LocalTransformation();
  gp_Pnt pos=manip->Position().Location();

  switch(trsf.Form()){
    case gp_Identity:{
     std::cout<<"Identity Matrix"<<"\n";
     break;
    }

   case gp_Rotation:{
    std::cout<<"Rotation Matrix"<<"\n";
     break;
    }

   case gp_Translation:{
   std::cout<<"Translational Matrix"<<"\n";
     break;
    }

    case gp_Scale:{
    std::cout<<"Scale Matrix"<<"\n";
     break;
    }

    case gp_CompoundTrsf:{
      std::cout<<"Compound Matrix"<<"\n";
     break; 
    }

  }
  std::cout<<"Gizmo Position_X:"<<pos.X()<<"\n";
  std::cout<<"Gizmo Position_Y:"<<pos.Y()<<"\n";
   std::cout<<"Gizmo Position_Z:"<<pos.Z()<<"\n";
  return;
 } 
  




void OnChangeSelectionColor(const Quantity_Color& color){
  if(context.IsNull()){
    emit QueryDebugMessage(tr("Context Cannot be Null"));
    return;
  }
  //For both vertex,edge and face......,This is called when ever a or face is selected
   Handle(Prs3d_Drawer)& dynColor=const_cast<Handle(Prs3d_Drawer)&>(context->SelectionStyle());
   auto& sh_aspect=const_cast<Handle(Prs3d_ShadingAspect)&>(dynColor->ShadingAspect());
   dynColor->SetColor(color);
   sh_aspect->SetColor(color);
 
   dynColor->SetShadingAspect(sh_aspect);
   context->SetSelectionStyle(dynColor);
     view->Redraw();
   return;
}

void OnChangeDetectedColor(const Quantity_Color& color){
  if(context.IsNull()){
    emit QueryDebugMessage(tr("Context Cannot be Null"));
    return;
  }
  //For both vertex,edge and face......,This is called when ever a or face is selected
   Handle(Prs3d_Drawer)& dynColor=const_cast<Handle(Prs3d_Drawer)&>(context->HighlightStyle(Prs3d_TypeOfHighlight_Dynamic));
   
   auto& sh_aspect=const_cast<Handle(Prs3d_ShadingAspect)&>(dynColor->ShadingAspect());
   dynColor->SetColor(color);
   sh_aspect->SetColor(color);
 
   dynColor->SetShadingAspect(sh_aspect);
   context->SetHighlightStyle(Prs3d_TypeOfHighlight_Dynamic,dynColor);
      view->Redraw();
  return;
}
void OnChangeSubShapeSelectedColor(const Quantity_Color& color){
  if(context.IsNull()){
    emit QueryDebugMessage(tr("Context Cannot be Null"));
    return;
  }
  //For both vertex,edge and face......,This is called when ever a or face is selected
   Handle(Prs3d_Drawer)& dynColor=const_cast<Handle(Prs3d_Drawer)&>(context->HighlightStyle(Prs3d_TypeOfHighlight_LocalSelected));
   dynColor->SetFaceBoundaryDraw(true);
   auto& sh_aspect=const_cast<Handle(Prs3d_ShadingAspect)&>(dynColor->ShadingAspect());
   
   dynColor->SetColor(color);
   sh_aspect->SetColor(color);
 
   dynColor->SetShadingAspect(sh_aspect);
   context->SetHighlightStyle(Prs3d_TypeOfHighlight_LocalSelected,dynColor);
   view->Redraw();
  return;
}
void OnChangeSubShapeDetectedColor(const Quantity_Color& color){
  if(context.IsNull()){
    emit QueryDebugMessage(tr("Context Cannot be Null"));
    return;
  }
  //For both vertex,edge and face......,This is called when ever a or face is selected
   Handle(Prs3d_Drawer)& dynColor=const_cast<Handle(Prs3d_Drawer)&>(context->HighlightStyle(Prs3d_TypeOfHighlight_LocalDynamic));
   dynColor->SetFaceBoundaryDraw(true);
   auto& sh_aspect=const_cast<Handle(Prs3d_ShadingAspect)&>(dynColor->ShadingAspect());
   
   dynColor->SetColor(color);
   sh_aspect->SetColor(color);
 
   dynColor->SetShadingAspect(sh_aspect);
   context->SetHighlightStyle(Prs3d_TypeOfHighlight_LocalDynamic,dynColor);
   view->Redraw();
  return;
}

Aspect_VKeyMouse ToQtMouseButton(const Qt::MouseButton& btn){
    switch(btn){
        case Qt::LeftButton:
            return Aspect_VKeyMouse_LeftButton;
        case Qt::RightButton:
            return Aspect_VKeyMouse_RightButton;
        case Qt::MiddleButton:
           return Aspect_VKeyMouse_MiddleButton;
        default:
          return Aspect_VKeyMouse_NONE;
    }
}
Aspect_VKeyFlags ToNativeModifiers(const Qt::KeyboardModifiers& mod){
   switch(mod){
    case Qt::NoModifier:
       return Aspect_VKeyFlags_NONE;
    case Qt::ShiftModifier:
      return Aspect_VKeyFlags_SHIFT;
    case Qt::ControlModifier:
      return Aspect_VKeyFlags_CTRL;
    case Qt::AltModifier:
      return Aspect_VKeyFlags_ALT;
    case Qt::MetaModifier:
      return Aspect_VKeyFlags_META;
   }
}

QPaintEngine* paintEngine() const override{
    return nullptr;
}
void SetUseWindowSize(const bool& value){
  UseWindowSize=value;
  return;
}
void HighlightSensitiveEntities(){
  switch(CurrentSelMode){
    case 6:
    case 5:
    case 4:
    case 3:
    case 2:
    case 1:
    case 0:
        {
      if(context->IsSelected(context->SelectedInteractive())){
      context->HilightSelected(true);
      context->SetToHilightSelected(true);
      context->UpdateSelected(true);
      emit QueryDebugMessage(tr("Object Is Currently Selected"));
      return;
      }
    }
    default:
      return;
  }
}
void DeactivateWorldGrid(){
  Viewer->DeactivateGrid();
  view->Redraw();
  return;
}
void CreateWorldGrid(){
  if(ShowGrid){
  if(Viewer.IsNull()){
     return;
    }
  if(!UseWindowSize){
      Viewer->SetGridEcho(GridAspect);
      Viewer->SetRectangularGridGraphicValues(GridSize_X,GridSize_Y,Grid_Spacing);
      Viewer->ActivateGrid(Aspect_GT_Rectangular,Aspect_GDM_Lines);
       Viewer->Redraw();
       return;
  }
  Viewer->SetGridEcho(GridAspect);
  int x=0,y=0;
  view->Window()->Size(x,y);
  Viewer->SetRectangularGridGraphicValues(x,y,Grid_Spacing);
  Viewer->ActivateGrid(Aspect_GT_Rectangular,Aspect_GDM_Lines);

  Viewer->Redraw();
  
  }
  return;
   
}
//it runs in an iteration,For One shape
void DisplayObject(const Handle(CustomAIS_Shape)& object){
  if(context.IsNull()){
    return;
  }
  if(Shapes.find(object->ID())!=Shapes.end()){
    if(object->Shape().ShapeType()<=TopAbs_FACE){
    Shapes.at(object->ID())->SetShape(object->Shape()); 
    Shapes.at(object->ID())->SetMaterialAspect(object->Mat());
    context->Redisplay(Shapes.at(object->ID()),true);
  }
  else{
     Shapes.at(object->ID())->SetShape(object->Shape()); 
    Shapes.at(object->ID())->SetColor(object->Mat().DiffuseColor());
    context->Redisplay(Shapes.at(object->ID()),true);
  }
  }
  else{
    if(object->ID()==-1){
      LoadMessage(tr("Invalid ID"),tr("There is no assigned index"));
      return;
    }
    if(object->Shape().IsSame(TopoDS_Shape())){
      LoadMessage(tr(""),tr("Sent Shape Is Empty"));
      return;
    }
    if(object->Shape().ShapeType()<=TopAbs_FACE){
    Shapes[object->ID()]=object;
    Shapes.at(object->ID())->SetID(object->ID());
    Shapes.at(object->ID())->SetMaterialAspect(object->Mat());
    context->Display(Shapes.at(object->ID()),true);
    }
    else{
      Shapes[object->ID()]=object;
    Shapes.at(object->ID())->SetColor(object->Mat().DiffuseColor());
    Shapes.at(object->ID())->SetID(object->ID());
    context->Display(Shapes.at(object->ID()),true);
    }

  }
    return;
}
  /*
  A shape will be redislpayed or display
  
  
  */
 void DisplayObjects(const std::vector<Handle(CustomAIS_Shape)>& shapes){
  if(shapes.empty()){
    LoadMessage(tr(""),tr("There are/is no loaded shape(s) from NodeGraph"));
    return;
  }
  
   
 
   if(context->IsDisplayed(viewcube)){
    context->Redisplay(viewcube,false);
   }
  for(const auto& shape: shapes){
   switch(shape->dt){
   case DP_MIRROR:{
  if(shape->Shape().ShapeType()<=TopAbs_FACE){
    if(Shapes.find(shape->ID())==Shapes.end()){
       Shapes[shape->ID()]=shape;
       context->Display(Shapes.at(shape->ID()),false);
    }
   Shapes.at(shape->ID())->SetShape(shape->Shape()); 
   Shapes.at(shape->ID())->SetMaterialAspect(shape->Mat());
   Shapes.at(shape->ID())->SetColor(shape->Mat().DiffuseColor());
   Shapes.at(shape->ID())->dt=shape->dt;
   context->Redisplay(Shapes.at(shape->ID()),false);
   }
   else{
    if(Shapes.find(shape->ID())==Shapes.end()){
       Shapes[shape->ID()]=shape;
       context->Display(Shapes.at(shape->ID()),false);
    }
    Shapes.at(shape->ID())->SetShape(shape->Shape());
    Shapes.at(shape->ID())->SetColor(shape->Mat().DiffuseColor());
    Shapes.at(shape->ID())->dt=shape->dt; //set display type to dp_mirror(that is, the shape is a mirror);
    context->Redisplay(Shapes.at(shape->ID()),false);
   }
   }
   case DP_NULL:{
   if(Shapes.find(shape->ID())!=Shapes.end()){
   if(shape->Shape().ShapeType()<=TopAbs_FACE){
   Shapes.at(shape->ID())->SetShape(shape->Shape()); 
   Shapes.at(shape->ID())->SetMaterialAspect(shape->Mat());
   Shapes.at(shape->ID())->SetColor(shape->Mat().DiffuseColor());
    context->Redisplay(Shapes.at(shape->ID()),false);
   }
   else{
    Shapes.at(shape->ID())->SetShape(shape->Shape());
    Shapes.at(shape->ID())->SetColor(shape->Mat().DiffuseColor());
    context->Redisplay(Shapes.at(shape->ID()),false);
   }
   }
   else{
    if(shape->ID()!=-1){
    if(shape->Shape().ShapeType()<=TopAbs_FACE){
    Shapes[shape->ID()]=shape;
    Shapes.at(shape->ID())->SetID(shape->ID());
    Shapes.at(shape->ID())->SetMaterialAspect(shape->Mat());
    Shapes.at(shape->ID())->SetColor(shape->Mat().DiffuseColor());
    context->Display(Shapes.at(shape->ID()),false);
    }
    else{
    Shapes[shape->ID()]=shape;
    Shapes.at(shape->ID())->SetID(shape->ID());
    Shapes.at(shape->ID())->SetColor(shape->Mat().DiffuseColor());
    context->Display(Shapes.at(shape->ID()),false);
    }
    }
    else{
      LoadMessage(tr(""),tr("ID is negative"));
    }
   }
   break;
  }
  }
 }
  view->Redraw();

  return;
 }
  
   
  
 
  
 
gp_Lin GetProjectedRay(const int& mouseX,const int& mouseY){
  double pointx=0.0,pointy=0.0,pointz=0.0,rayx=0.0,rayy=0.0,rayz=0.0;
  if(view.IsNull()){
    return gp_Lin();
  }

  view->ConvertWithProj(mouseX,mouseY,pointx,pointy,pointz,rayx,rayy,rayz);
  gp_Pnt origin(pointx,pointy,pointy);
  gp_Dir raydirection(rayx,rayy,rayz);
  return gp_Lin(origin,raydirection);
}
gp_Pnt Get3dPointFrom2D(const int& x,const int y){
  double p_x,p_y,p_z;
   //view->ConvertToGrid(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().y()*dpr)),projX,projY,projZ);

   view->ConvertToGrid(x,y,p_x,p_y,p_z);
  return gp_Pnt(p_x,p_y,p_z);
}
//This design method can allow you to perform test with every surface in the scene.





void DisplayGizmoOnObject(Handle(AIS_InteractiveObject) shape){
   if(ObjectGizmo.IsNull()){
    ObjectGizmo=new AIS_Manipulator();
   }
   if(isTranslateGizmoEnabled){
     if(!ObjectGizmo.IsNull()){
          if(context->IsDisplayed(ObjectGizmo)){
             context->Erase(ObjectGizmo,false);
          }
          ObjectGizmo->Detach();
       
          EnableManipulatorPart(AIS_MM_Rotation,shape);
          EnableManipulatorPart(AIS_MM_Scaling,shape);
          if(ObjectGizmo->HasActiveMode()){
            ObjectGizmo->DeactivateCurrentMode();
          }
           ObjectGizmo->SetModeActivationOnDetection(false);
          ObjectGizmo->EnableMode(AIS_MM_Translation);
            emit QueryDebugMessage(tr("The Translation Gizmo Enabled"));
          return;
       
     }
   }
   else if(isRotateGizmoEnabled){
     if(!ObjectGizmo.IsNull()){
          if(context->IsDisplayed(ObjectGizmo)){
             context->Erase(ObjectGizmo,false);
          }
          ObjectGizmo->Detach();
       
          EnableManipulatorPart(AIS_MM_Translation,shape);
          EnableManipulatorPart(AIS_MM_Scaling,shape);
          if(ObjectGizmo->HasActiveMode()){
            ObjectGizmo->DeactivateCurrentMode();
          }
           ObjectGizmo->SetModeActivationOnDetection(false);
          ObjectGizmo->EnableMode(AIS_MM_Rotation);
            emit QueryDebugMessage(tr("The Rotation Gizmo Enabled"));
          return;
       
     }
   }
  else if(isScaleGizmoEnabled){
       if(!ObjectGizmo.IsNull()){
          if(context->IsDisplayed(ObjectGizmo)){
             context->Erase(ObjectGizmo,false);
          }
          ObjectGizmo->Detach();
       
          EnableManipulatorPart(AIS_MM_Translation,shape);
          EnableManipulatorPart(AIS_MM_Rotation,shape);
          if(ObjectGizmo->HasActiveMode()){
            ObjectGizmo->DeactivateCurrentMode();
          }
           ObjectGizmo->SetModeActivationOnDetection(false);
          ObjectGizmo->EnableMode(AIS_MM_Scaling);
            emit QueryDebugMessage(tr("The Scale Gizmo Enabled"));
          return;
       
     }
  }
  ObjectGizmo->SetModeActivationOnDetection(false);
   ObjectGizmo->Attach(shape);
   ObjectGizmo->SetZoomPersistence(true);
   
   if(!context.IsNull()){
    if(!context->IsDisplayed(ObjectGizmo)){
        context->Display(ObjectGizmo,true);
        return;
    }
   
   
   emit QueryDebugMessage(tr("New Gizmo Created"));

   }
   emit QueryDebugMessage(tr("No Initialized Context"));
  return;
}
void RemoveObjectGizmo(){
  context->Remove(ObjectGizmo,false);
  view->Redraw();
  return;
}

void EnableManipulatorPart(const AIS_ManipulatorMode& theMode,Handle(AIS_InteractiveObject) shape){
  if(!ObjectGizmo.IsNull()){
    if(ObjectGizmo->HasActiveMode()){
        ObjectGizmo->DeactivateCurrentMode();
    }
    if(ObjectGizmo->IsAttached()){
      ObjectGizmo->Detach();
     }
     ObjectGizmo->SetPart(theMode,false);
     
     //re attach it again
     ObjectGizmo->Attach(shape);
     if(context->IsDisplayed(ObjectGizmo)){
      context->Redisplay(ObjectGizmo,true);
     }
     else{
      context->Display(ObjectGizmo,AIS_Shaded,0,false);
      view->Redraw();
     }
    return;
  }
  
  ObjectGizmo=new AIS_Manipulator();
  ObjectGizmo->SetPart(theMode,false);
 
  
  ObjectGizmo->Attach(shape);
  if(!context.IsNull()){
   context->Display(ObjectGizmo,AIS_Shaded,0,false);
   view->Redraw();
   }
   return;
}
void OnClearView(){
  for(auto iter=Shapes.begin();iter!=Shapes.end();++iter){
      if(context->IsDisplayed(iter->second)){
         context->Remove(iter->second,false);
      }
  }
  if(!Shapes.empty()){
    Shapes.clear();
  }
  view->Redraw();
  return;
}
//this searches for an object that matches the chosen object,and store  it's ID
void OnSearch(const Handle(CustomAIS_Shape)& shape){
  bool isFound=false;
  for(auto iter=Shapes.begin();iter!=Shapes.end();++iter){
           if(iter->second==shape){
               ShapeId=iter->first;
               LoadMessage(tr("Shape Found Message"),tr("Shape Found"));
               isFound=true;
               break;
           }
        }
      if(isFound==false){
      LoadMessage(tr("Shape Not Found Error"),tr("Shape Not Found"));
       }
    
    return;
}
void MatrixInspector(const gp_Trsf& mat){
  std::cout<<"Matrix Form: "<<mat.Form()<<"\n";

  std::cout<<"Scale Factor: "<<mat.ScaleFactor()<<"\n";
  std::cout<<"Rotational Aspect:"<<"\n";
  gp_Mat rotMat=mat.GetRotation().GetMatrix();
  for(int i=1;i<=3;i++){
    for(int j=1;j<=3;j++){
    std::cout<<rotMat(i,j)<<" ";
  }
  cout<<"\n";
  }
  gp_XYZ transPart=mat.TranslationPart();
  cout<<"X: "<<transPart.X()<<" "<<"Y: "<<transPart.Y()<<" "<<"Z: "<<transPart.Z()<<"\n";
 return;
}
void CheckDisplayStatus(Handle(AIS_InteractiveObject) object,const PrsMgr_DisplayStatus& status){
  switch(status){
    case PrsMgr_DisplayStatus_Displayed:{
      context->Redisplay(object,false);
      break;
    }
   case PrsMgr_DisplayStatus_Erased:{
     context->Display(object,1,4,false);
     break;
   }
 
  }
 return;  
}
void OnHighlight(const int id){
if(id==-1){
  LoadMessage(tr("Negative Id"),tr("Cannot access shape using negative id"));
   return;
}
if(Shapes.find(id)==Shapes.end()){
  LoadMessage(tr("Invalid Id"),tr("Cannot Find Shape with this specific Id"));
  return;
}
  if(currSelShape){
         currSelShape->UseColor();
         context->Redisplay(currSelShape,false);
         context->Remove(currSelShape,false);
        }
      
       currSelShape=new CustomAIS_Shape(Shapes.at(id)->TransShape());
       if(!currSelShape){
        LoadMessage(tr("Current Selected Shape Error"),tr("No Current Selected Object"));
        return;
       }
        
        currSelShape->SetColor(Quantity_NOC_YELLOW2);
        currSelShape->SetTransparency(0.6);
        currSelShape->SetZLayer(Graphic3d_ZLayerId_Top);
        context->Display(currSelShape,1,CurrentSelMode,true);
  return;
}
~DrawingCentralWidget(){
  if(SelectedMenu){
    delete SelectedMenu;
    SelectedMenu=nullptr;
  }
  if(DeleteAction){
    delete DeleteAction;
    DeleteAction=nullptr;
  }
  if(SelectAction){
    delete SelectAction;
    SelectAction=nullptr;
  }
  if(UndoAction){
    delete UndoAction;
    UndoAction=nullptr;
  }
  if(RedoAction){
    delete RedoAction;
    RedoAction=nullptr;
  }
  if(DockMenus){
    delete DockMenus;
    DockMenus=nullptr;
  }
  if(showSettingAction){
    delete showSettingAction;
    showSettingAction=nullptr;
  }
  if(DrawCubeAction){
    delete DrawCubeAction;
    DrawCubeAction=nullptr;
  }
  if(ScaleAction){
    delete ScaleAction;
    ScaleAction=nullptr;
  }
  if(RotateAction){
    delete RotateAction;
    RotateAction=nullptr;
  }
  if(TranslateAction){
    delete TranslateAction;
    TranslateAction=nullptr;
  }
  if(ShapePrsAction){
    delete ShapePrsAction;
    ShapePrsAction=nullptr;
  }
  if(LinePrsAction){
    delete LinePrsAction;
    LinePrsAction=nullptr;
  }
 
}  


void FlushViewEvent(){ //flush all the view events
  evt_manager.FlushViewEvents(context,view,true);
  return;
}




protected:
//On Selecting Objects,we must have knowledge of the selection mode that was chosen
void mousePressEvent(QMouseEvent* event) override{
 if(evt_manager.UpdateMouseButtons(Graphic3d_Vec2i(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().y()*dpr))),ToQtMouseButton(event->button()),ToNativeModifiers(Qt::NoModifier),false)){
   

 
 if(event->button()==Qt::LeftButton){
    
    if(context->MoveTo(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().y()*dpr)),view,false)==AIS_SOD_Nothing){
     if(dc!=DC_TRANSFORM){
     curveShape.Nullify();
     }
     lineShape.Nullify();
     circShape.Nullify();
     editShape.Nullify();
     bshape.Nullify();
     Eshape=ES_NULL;
     edgeselector->Nullify();
     faceselector->Nullify();
     arcShape.Nullify();
     wireselector->Nullify();
     shapeselector->Nullify();
     
        /*
        we have to find the intersection of the ray and the surface in question
        using surfaceWidgetShape
        
        */
      
       if(dc==DC_RADIUS){
        double projX,projY,projZ=0.0;
         view->ConvertToGrid(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().y()*dpr)),projX,projY,projZ);
        LineStartPoint=gp_Pnt(projX,projY,projZ);
        return;
       }
       if(dc==DC_POLYGON){
        double projX,projY,projZ=0.0;
         view->ConvertToGrid(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().y()*dpr)),projX,projY,projZ);
        LineStartPoint=gp_Pnt(projX,projY,projZ);
        return;
       }
       if(dc==DC_LINE){
        double projX,projY,projZ=0.0;
         view->ConvertToGrid(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().y()*dpr)),projX,projY,projZ);
        LineStartPoint=gp_Pnt(projX,projY,projZ);
        return;
       }
       if(dc==DC_CIRCLE){
        if(drawCircle->firstPoint->isChecked()){
         double projX,projY,projZ=0.0;
         view->ConvertToGrid(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().y()*dpr)),projX,projY,projZ);
        CircleFirstPoint=gp_Pnt(projX,projY,projZ);
        return;
        }
        if(drawCircle->secondPoint->isChecked()){
          double projX,projY,projZ=0.0;
         view->ConvertToGrid(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().y()*dpr)),projX,projY,projZ);
        CircleSecondPoint=gp_Pnt(projX,projY,projZ);
        return;
        }
        if(drawCircle->thirdPoint->isChecked()){
           double projX,projY,projZ=0.0;
         view->ConvertToGrid(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().y()*dpr)),projX,projY,projZ);
        CircleThirdPoint=gp_Pnt(projX,projY,projZ);
        return;
        }
       }
      if(gpsstate==GPS_BSPLINE){
        LoadMessage(tr("B Spline Status"),tr("Spline In Progress"));
         double projX,projY,projZ=0.0;
         view->ConvertToGrid(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().y()*dpr)),projX,projY,projZ);
         bspCurve->AddBSplinePoles(gp_Pnt(projX,projY,projZ));
         FlushViewEvent();
         return;
      }
      if(gpsstate==GPS_BEZIER){
         double projX,projY,projZ=0.0;
         view->ConvertToGrid(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().y()*dpr)),projX,projY,projZ);
         transCurve->AddBezierPoles(gp_Pnt(projX,projY,projZ));
         transCurve->BuildShape();
         FlushViewEvent();
         return;
      }
      if(gpsstate==GPS_GATHER){
        double projX,projY,projZ=0.0;
         view->ConvertToGrid(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().y()*dpr)),projX,projY,projZ);

        transPolygon->AddPoint(gp_Pnt(projX,projY,projZ));
        transPolygon->BuildShape();
        FlushViewEvent();
        return;
      }
        double projX,projY,projZ=0.0;
        view->ConvertToGrid(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().y()*dpr)),projX,projY,projZ);
        LineStartPoint=gp_Pnt(projX,projY,projZ);
         SelectPoint(LineStartPoint);
      if(!ChosenShape.IsNull()){
         
          IsSelectedColorUsed=false;
          SentTransform=gp_Trsf();
          if(dc!=DC_TRANSFORM){
          ChosenShape.Nullify();
          }
      }
      
      if(!ObjectGizmo.IsNull()){
       if(dc==DC_TRANSFORM){
         if(context->IsDisplayed(ObjectGizmo)){
          context->Redisplay(ObjectGizmo,true);
         }
       }
       else{
       ObjectGizmo->Detach();
      if(context->IsDisplayed(ObjectGizmo)){
        context->Erase(ObjectGizmo,true);
      }
      }
     }
     emit OnDestroyMaterialProp();
     emit QueryDebugMessage(tr("No Object Is Chosen"));
     emit OnSetPreviousColor();
        
      
     
     PrevSelMode=-1;
   if(context->IsDisplayed(pointMarker)){
    context->Remove(pointMarker,true);
   }
   if(context->IsDisplayed(currSelShape)){
    currSelShape->UseColor();
    context->Remove(currSelShape,true);
   }
   if(CurrentSelMode!=2){
   selEdge=TopoDS_Edge();
   }
   if(CurrentSelMode!=4){
   selFace=TopoDS_Face();
   }
   st=NULL_SELECT;
   st1=NULL_SELECT;
   cm=CE_NULL;
   context->Activate(viewcube,0);
   FlushViewEvent();
      return;
    }
    else{
    context->SelectDetected();
    
    
    context->InitSelected();
    while(context->MoreSelected()){
      if(CurrentSelMode==3){ //wire selection
      if(gatherWire->isChecked()){
      
        Handle(SelectMgr_EntityOwner) owner=context->SelectedOwner();
        if(!owner){
          LoadMessage(tr(""),tr("Failed To Cast to Wire(Loop)"));
          return;
        }
        Handle(StdSelect_BRepOwner) entity=Handle(StdSelect_BRepOwner)::DownCast(owner);
         if(!entity){
          LoadMessage(tr(""),tr("Failed To Cast to Point"));
          return;
        }
         Handle(AIS_InteractiveObject) obShape=Handle(AIS_InteractiveObject)::DownCast(owner->Selectable());
        if(!obShape){
          cout<<"Failed To Cast"<<"\n";
          return;
        } 
        selShape=Handle(CustomAIS_Shape)::DownCast(obShape);
         wireShape=selShape;
        
        if(!owner){
           std::cout<<"Failed To Cast To an object of SelectMgr_EntityOwner"<<"\n";
          return;
        }
        TopoDS_Shape entShape=entity->Shape();
        if(entShape.ShapeType()!=TopAbs_WIRE){
            LoadMessage(tr(""),tr("The Selected Shape is not a wire(loop)"));
            return;
        }
        selWire=TopoDS::Wire(entShape);
        if(selWire.IsNull()){
          LoadMessage(tr(""),tr("Cannot Cast to wire"));
          return;
        }
        wireselectors->AddToSelection(wireShape,selWire);
        auto pnt=context->MainSelector()->PickedPoint(1);
        LineStartPoint=pnt;
        st1=WIRES_SELECT;
        x_value=LineStartPoint.X();
        y_value=LineStartPoint.Y();
        z_value=LineStartPoint.Z();
        return;
      }
      else{
         wireselector->UnSelectWire();
         Handle(SelectMgr_EntityOwner) owner=context->SelectedOwner();
        if(!owner){
          LoadMessage(tr(""),tr("Failed To Cast to Wire(Loop)"));
          return;
        }
        Handle(StdSelect_BRepOwner) entity=Handle(StdSelect_BRepOwner)::DownCast(owner);
         if(!entity){
          LoadMessage(tr(""),tr("Failed To Cast to Point"));
          return;
        }
         Handle(AIS_InteractiveObject) obShape=Handle(AIS_InteractiveObject)::DownCast(owner->Selectable());
        if(!obShape){
          cout<<"Failed To Cast"<<"\n";
          return;
        } 
        selShape=Handle(CustomAIS_Shape)::DownCast(obShape);
         wireShape=selShape;
        wireselector->SetSelectedShape(wireShape);
        if(!owner){
           std::cout<<"Failed To Cast To an object of SelectMgr_EntityOwner"<<"\n";
          return;
        }
        TopoDS_Shape entShape=entity->Shape();
        if(entShape.ShapeType()!=TopAbs_WIRE){
            LoadMessage(tr(""),tr("The Selected Shape is not a wire(loop)"));
            return;
        }
        selWire=TopoDS::Wire(entShape);
        if(selWire.IsNull()){
          LoadMessage(tr(""),tr("Cannot Cast to wire"));
          return;
        }
        try{
        wireselector->SetSelectedWire(selWire);
        auto pnt=context->MainSelector()->PickedPoint(1);
        LineStartPoint=pnt;
         SelectPoint(LineStartPoint);
         if(dc==DC_TRANSFORM){
         OnPositionGizmo();
         }
        st1=WIRE_SELECT;
        wireselector->SelectWire();
        x_value=LineStartPoint.X();
        y_value=LineStartPoint.Y();
        z_value=LineStartPoint.Z();
        return;
      }
      catch(const Standard_OutOfRange& r){
        cout<<"Did not intersect with the wire"<<"\n";
         FlushViewEvent();
       return;
       }
      }
      return;
      }
     if(CurrentSelMode==1){
        Handle(SelectMgr_EntityOwner) owner=context->SelectedOwner();
        if(!owner){
          LoadMessage(tr(""),tr("Failed To Cast to Point"));
          return;
        }
        Handle(StdSelect_BRepOwner) entity=Handle(StdSelect_BRepOwner)::DownCast(owner);
         if(!entity){
          LoadMessage(tr(""),tr("Failed To Cast to Point"));
          return;
        }
      TopoDS_Shape vertexShape=entity->Shape();
      if(vertexShape.ShapeType()==TopAbs_VERTEX){
        TopoDS_Vertex vertex=TopoDS::Vertex(vertexShape);
        if(vertex.IsNull()){
          LoadMessage(tr(""),tr("Failed to cast to an object of TopoDS_Vertex"));
          return;
        }
        chamferVertex=vertex;
        filletVertex=vertex;
        auto pnt=context->MainSelector()->PickedPoint(1);
        if(!pointMarker){
        pointMarker=new AIS_Point(new Geom_CartesianPoint(0.0,0.0,0.0));
        pointMarker->SetColor(Quantity_NOC_PERU);
        pointMarker->SetMarker(Aspect_TOM_O);
      }
      LineStartPoint=pnt;
       SelectPoint(LineStartPoint);
        if(dc==DC_TRANSFORM){
         OnPositionGizmo();
         }
      Handle(Geom_Point) geom_pnt=new Geom_CartesianPoint(pnt.X(),pnt.Y(),pnt.Z());
      pointMarker->SetComponent(geom_pnt);

      }
      if(context->IsDisplayed(pointMarker)){
         context->Remove(pointMarker,true);
         context->Display(pointMarker,true); 
      }
      else{
      context->Display(pointMarker,true);
      }
      LoadMessage(tr(""),tr("Successful Casting"));
        return;
     }
     if(CurrentSelMode==4){  //When currentSelMode is 4,it is a face
       if(selectFaces->isChecked()){
        Handle(SelectMgr_EntityOwner) owner=context->SelectedOwner();
        Handle(AIS_InteractiveObject) obShape=Handle(AIS_InteractiveObject)::DownCast(owner->Selectable());
        if(!obShape){
          cout<<"Failed To Cast"<<"\n";
          return;
        } 
        selShape=Handle(CustomAIS_Shape)::DownCast(obShape);
       
        if(!owner){
           std::cout<<"Failed To Cast To an object of SelectMgr_EntityOwner"<<"\n";
          return;
        }
       Handle(StdSelect_BRepOwner) selectedEntity=Handle(StdSelect_BRepOwner)::DownCast(owner);
        if(!selectedEntity){
          std::cout<<"Failed To Cast To an object of StdSelect_BRepOwner"<<"\n";
          return;
        }
        
        if(selectedEntity->Shape().ShapeType()==TopAbs_FACE){
            selFace=TopoDS::Face(selectedEntity->Shape());
            faceselector->SetSelectedFace(selFace);
            if(selFace.IsNull()){
               std::cout<<"Failed To Cast To Face"<<"\n";
               return;
            }
           selFaceShape=selectedEntity->Shape();
          std::cout<<"It is a Face"<<"\n";
        }
        else{
            std::cout<<"It is not a Face"<<"\n";
            QString str= shapetypemap.at(selectedEntity->Shape().ShapeType());
           std::cout<<"Shape's Type :"<<str.toUtf8().toStdString()<<"\n ";

            return;
        }
        faceselectors->AddToSelection(selShape,selFace);
       try{
       gp_Pnt selectedPoint=context->MainSelector()->PickedPoint(1);
       selFacePoint=selectedPoint;
       LineStartPoint=selectedPoint;
        int_x=selectedPoint.X();
        int_y=selectedPoint.Y();
        int_z=selectedPoint.Z();
       std::cout<<"Surface Points: "<<int_x<<","<<int_y<<","<<int_z<<"\n";
      gp_Pnt centroid=GetSurfaceCentre(selFace);
      if(!pointMarker){
        pointMarker=new AIS_Point(new Geom_CartesianPoint(0.0,0.0,0.0));
        pointMarker->SetColor(Quantity_NOC_PERU);
        pointMarker->SetMarker(Aspect_TOM_O);
      }
      Handle(Geom_Point) geom_pnt=new Geom_CartesianPoint(centroid.X(),centroid.Y(),centroid.Z());
      pointMarker->SetComponent(geom_pnt);
      x_value=centroid.X();
      y_value=centroid.Y();
      z_value=centroid.Z();
      if(context->IsDisplayed(pointMarker)){
         context->Remove(pointMarker,true);
         context->Display(pointMarker,0,0,true); 
      }
      else{
      context->Display(pointMarker,0,0,true);
      }
      
        x_value=LineStartPoint.X();
        y_value=LineStartPoint.Y();
        z_value=LineStartPoint.Z();
       
       }
       catch(const Standard_OutOfRange& r){
        cout<<"Did not intersect with the face"<<"\n";
         FlushViewEvent();
       return;
       }
       return;
       }
       else{
        faceselector->UnSelectFace();
    
        Handle(SelectMgr_EntityOwner) owner=context->SelectedOwner();
        Handle(AIS_InteractiveObject) obShape=Handle(AIS_InteractiveObject)::DownCast(owner->Selectable());
        if(!obShape){
          cout<<"Failed To Cast"<<"\n";
          return;
        } 
        selShape=Handle(CustomAIS_Shape)::DownCast(obShape);
        if(selShape){
          faceselector->SetSelectedShape(selShape);
        }
        if(!owner){
           std::cout<<"Failed To Cast To an object of SelectMgr_EntityOwner"<<"\n";
          return;
        }
       Handle(StdSelect_BRepOwner) selectedEntity=Handle(StdSelect_BRepOwner)::DownCast(owner);
        if(!selectedEntity){
          std::cout<<"Failed To Cast To an object of StdSelect_BRepOwner"<<"\n";
          return;
        }
        
        if(selectedEntity->Shape().ShapeType()==TopAbs_FACE){
            selFace=TopoDS::Face(selectedEntity->Shape());
            faceselector->SetSelectedFace(selFace);
            if(selFace.IsNull()){
               std::cout<<"Failed To Cast To Face"<<"\n";
               return;
            }
           selFaceShape=selectedEntity->Shape();
          std::cout<<"It is a Face"<<"\n";
        }
        else{
            std::cout<<"It is not a Face"<<"\n";
            QString str= shapetypemap.at(selectedEntity->Shape().ShapeType());
           std::cout<<"Shape's Type :"<<str.toUtf8().toStdString()<<"\n ";

            return;
        }
        st1=FACE_SELECT;
       try{
       gp_Pnt selectedPoint=context->MainSelector()->PickedPoint(1);
       selFacePoint=selectedPoint;
       SetFaceFixed(selFace);
       LineStartPoint=selectedPoint;
        SelectPoint(LineStartPoint);
         if(dc==DC_TRANSFORM){
         OnPositionGizmo();
         }
        int_x=selectedPoint.X();
        int_y=selectedPoint.Y();
        int_z=selectedPoint.Z();
       std::cout<<"Surface Points: "<<int_x<<","<<int_y<<","<<int_z<<"\n";
      gp_Pnt centroid=GetSurfaceCentre(selFace);
      if(!pointMarker){
        pointMarker=new AIS_Point(new Geom_CartesianPoint(0.0,0.0,0.0));
        pointMarker->SetColor(Quantity_NOC_PERU);
        pointMarker->SetMarker(Aspect_TOM_O);
      }
      Handle(Geom_Point) geom_pnt=new Geom_CartesianPoint(centroid.X(),centroid.Y(),centroid.Z());
      pointMarker->SetComponent(geom_pnt);
      x_value=centroid.X();
      y_value=centroid.Y();
      z_value=centroid.Z();
      if(context->IsDisplayed(pointMarker)){
         context->Remove(pointMarker,true);
         context->Display(pointMarker,0,0,true); 
      }
      else{
      context->Display(pointMarker,0,0,true);
      }
      
        x_value=LineStartPoint.X();
        y_value=LineStartPoint.Y();
        z_value=LineStartPoint.Z();
       faceselector->SelectFace();
       }
       catch(const Standard_OutOfRange& r){
        cout<<"Did not intersect with the face"<<"\n";
         FlushViewEvent();
       return;
       }
       }
    


        //Get3dPointFrom2D
      
       
       FlushViewEvent();
       return;

    }
    if(CurrentSelMode==2){ //for edge
        if(selectEdges->isChecked()){
        try{
        Handle(SelectMgr_EntityOwner) owner=context->SelectedOwner();
        if(!owner){
           std::cout<<"Failed To Cast To an object of SelectMgr_EntityOwner"<<"\n";
          return;
        }
         Handle(AIS_InteractiveObject) obShape=Handle(AIS_InteractiveObject)::DownCast(owner->Selectable());
        if(!obShape){
          cout<<"Failed To Cast"<<"\n";
        } 
      selShape=Handle(CustomAIS_Shape)::DownCast(obShape);
      if(!selShape){
        
        std::cout<<"Failed to cast to an object of CustomAIS_Shape"<<"\n";
      return;
      }
      else{
      selCurveShape=Handle(CurveAIS_Shape)::DownCast(obShape);
      if(!selCurveShape){
        
        std::cout<<"Converted To an object of CurveAIS_Shape"<<"\n";
        return;
      }
      }
       Handle(StdSelect_BRepOwner) selectedEntity=Handle(StdSelect_BRepOwner)::DownCast(owner);
       if(!selectedEntity){
        std::cout<<"Failed To Cast To an object of StdSelect_BRepOwner"<<"\n";
          return;
       }
       
       if(selectedEntity->Shape().ShapeType()==TopAbs_EDGE){
            selEdge=TopoDS::Edge(selectedEntity->Shape());
            if(selEdge.IsNull()){
               std::cout<<"Failed To Cast To an Edge"<<"\n";
               return;
            }
           
          std::cout<<"It is an Edge"<<"\n";
        }
        else{
          std::cout<<"It is not an edge"<<"\n";
            QString str= shapetypemap.at(selectedEntity->Shape().ShapeType());
           std::cout<<"Shape's Type :"<<str.toUtf8().toStdString()<<"\n ";

            return;
        }
      if(selShape){
        edgeselectors->AddToSelection(selShape,selEdge);
      }
      else{
        edgeselectors->AddToSelection(selCurveShape,selEdge);
      }
      dc=DC_EDGES;
        }
        catch(const Standard_OutOfRange& errorrange){
          return;
        }
      return;
      }
      else{
        try{
        edgeselector->UnSelectEdge();
         Handle(SelectMgr_EntityOwner) owner=context->SelectedOwner();
        if(!owner){
           std::cout<<"Failed To Cast To an object of SelectMgr_EntityOwner"<<"\n";
          return;
        }
         Handle(AIS_InteractiveObject) obShape=Handle(AIS_InteractiveObject)::DownCast(owner->Selectable());
        if(!obShape){
          cout<<"Failed To Cast"<<"\n";
        } 
      selShape=Handle(CustomAIS_Shape)::DownCast(obShape);
      
      if(selShape){
         edgeselector->SetSelectedShape(selShape);
        std::cout<<"Failed to cast to an object of CustomAIS_Shape"<<"\n";
      }
      else{
      selCurveShape=Handle(CurveAIS_Shape)::DownCast(obShape);
      if(selCurveShape){
        edgeselector->SetSelectedShape(selCurveShape);
        std::cout<<"Converted To an object of CurveAIS_Shape"<<"\n";
      }
      }
       Handle(StdSelect_BRepOwner) selectedEntity=Handle(StdSelect_BRepOwner)::DownCast(owner);
       if(!selectedEntity){
        std::cout<<"Failed To Cast To an object of StdSelect_BRepOwner"<<"\n";
          return;
       }
       
       if(selectedEntity->Shape().ShapeType()==TopAbs_EDGE){
            selEdge=TopoDS::Edge(selectedEntity->Shape());
            if(selEdge.IsNull()){
               std::cout<<"Failed To Cast To an Edge"<<"\n";
               return;
            }
           
          std::cout<<"It is an Edge"<<"\n";
        }
        else{
          std::cout<<"It is not an edge"<<"\n";
            QString str= shapetypemap.at(selectedEntity->Shape().ShapeType());
           std::cout<<"Shape's Type :"<<str.toUtf8().toStdString()<<"\n ";

            return;
        }
        selFaceShape=selectedEntity->Shape();
        edgeselector->SetSelectedEdge(TopoDS::Edge(selectedEntity->Shape()));
        chamferEdge=TopoDS::Edge(selectedEntity->Shape());
        if(wireFilletMenu->selectFirstEdge->isChecked()){
          wiredEdge=chamferEdge;
        }
        if(wireFilletMenu->selectSecondEdge->isChecked()){
          wiredEdge_1=chamferEdge;
        }
        if(edgeFilletMenu->chooseFirstEdge->isChecked()){
        filletEdge=chamferEdge;
        std::cout<<"First Edge Chosen"<<endl;
        }
        if(edgeFilletMenu->chooseSecondEdge->isChecked()){
        filletEdge_1=chamferEdge;
        std::cout<<"Second Edge Chosen"<<endl;
        }
        st1=EDGE_SELECT;
        
         gp_Pnt selectedPoint=context->MainSelector()->PickedPoint(1);
         LineStartPoint=selectedPoint;
         SelectPoint(LineStartPoint);
        if(dc==DC_TRANSFORM){
           OnPositionGizmo();
         }
         int_x=selectedPoint.X();
         int_y=selectedPoint.Y();
         int_z=selectedPoint.Z();
          if(trimMenu->First()->isChecked()){
          firstTrimShape=selShape;
          trimFirstPoint=LineStartPoint;
        }
        if(trimMenu->Second()->isChecked()){
          secondTrimShape=selShape;
          trimSecondPoint=LineStartPoint;
        }
        x_value=LineStartPoint.X();
        y_value=LineStartPoint.Y();
        z_value=LineStartPoint.Z();
        edgeselector->SelectEdge();
         FlushViewEvent();
         return;
         }
         catch(const Standard_OutOfRange& r){
        cout<<"Did not intersect with the edge"<<"\n";
         FlushViewEvent();
       return;
       }
        }
    }
      
    PrintSelection(CurrentSelMode);
    shapeselector->UnSelectShape();
   Handle(SelectMgr_EntityOwner) owner=context->SelectedOwner();
   Handle(AIS_Axis) axisObject=Handle(AIS_Axis)::DownCast(owner->Selectable());
   if(axisObject){
    if(axisObject==AxisObject){
      cm=CE_AXIS;
      return;
    }
   }
   Handle(AIS_Point) pmaker=Handle(AIS_Point)::DownCast(owner->Selectable());
   if(pmaker){
    if(pmaker==pointMarker){
      cm=CE_POINT;
      return;
    }
   }
   Handle(AIS_Manipulator) chmanip=Handle(AIS_Manipulator)::DownCast(owner->Selectable());
   if(chmanip){
     if(chmanip==ObjectGizmo){
       if(ObjectGizmo->HasActiveMode()){
        editShape=Handle(EditCircleShape)::DownCast(ObjectGizmo->Object());
        if(editShape){
          evt_manager.UpdateMousePosition(Graphic3d_Vec2i(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().y()*dpr))),ToQtMouseButton(event->button()),ToNativeModifiers(Qt::NoModifier),false);
        std::cout<<"Before Transform"<<"\n";
        SetGizmoStateForEditShape();
        try{
        ObjectGizmo->StartTransform(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().y()*dpr)),view);
         OnUpdateTransformForEditCircleShape(editShape);
         
         cout<<"Gizmo Position before Drag:"<<"\n";
         OnDebugGizmo(ObjectGizmo);
         cout<<"\n";
         if(castedLineShape){
        castedLineShape->UpdateShape(editShape->PartEdit(),ObjectGizmo->Position().Location()); 
         return;
         }
         if(castedCircleShape){
          Eshape=ES_GIZMO;
          castedCircleShape->UpdateShape(editShape->PartEdit(),ObjectGizmo->Position().Location());
          return;
         }
         if(castedBezierShape){
          //beziershapes modification

          castedBezierShape->GetEditShapeHandle(editShape->Index());
          if(!castedBezierShape->IsFound()){
            LoadMessage(tr("Markers Not Found"),tr("It cannot find a marker that corresponds with the chosen position"));
              return;
          }
          castedBezierShape->UpdateShape(editShape->Index(),currGizmoPos);
          return;
         }
         if(castedBsplineShape){
          castedBsplineShape->GetHandle(editShape->Index());
          if(!castedBsplineShape->IsFound()){
            LoadMessage(tr(""),tr("Marker For BSpline not found"));
            return;
          }
          castedBsplineShape->UpdateShape(editShape->Index(),currGizmoPos);
          return;
         }
        }
        catch(Standard_Failure& error){
        LoadMessage(tr(""),tr("Invalid Index,Choose a part close the sphere to perform translation"));
        return;
        }
        std::cout<<"After Transform"<<"\n";
        view->Invalidate(); //force the redraw;
        return;
        }
        else{
        evt_manager.UpdateMousePosition(Graphic3d_Vec2i(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().y()*dpr))),ToQtMouseButton(event->button()),ToNativeModifiers(Qt::NoModifier),false);
        std::cout<<"Before Transform"<<"\n";
        try{
        
        ObjectGizmo->StartTransform(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().y()*dpr)),view);
        if(dc==DC_TRANSFORM){
        OnPositionGizmo();
        objectTrans=GetObjectTransform();
         GizmoStartPosition=ConvertToObjectSpace(gottenPos);
        isObjectTransformed=true;
          return;
        }
        
        
        }
        catch(Standard_Failure& error){
        LoadMessage(tr(""),tr("Invalid Index,Choose a part close the sphere to perform translation"));
        return;
        }
        std::cout<<"After Transform"<<"\n";
        view->Invalidate(); //force the redraw;
        isObjectTransformed=true;
        return;
       }
       }
     }
   }
   //For the manipulator On the screen
  
    
  
   Handle(AIS_InteractiveObject) object=Handle(AIS_InteractiveObject)::DownCast(owner->Selectable());
  chosenInteractive=object;
     if(!object.IsNull()){
      QString str=QString(tr("Object is Selected"));
      if(dc==DC_TRANSFORM){
        DisplayAtPivot();
      }
      else{
      SetGizmoForWholeObject();
      DisplayGizmoOnObject(object); //
      CheckDisplayStatus(ObjectGizmo,context->DisplayStatus(ObjectGizmo));
      }
      Handle(AIS_Shape) tmpshape=Handle(AIS_Shape)::DownCast(object);
      if(selectShapes->isChecked()){
        if(tmpshape){
          shapeselectors->AddToSelection(tmpshape);
        }
      }
      else{
      if(tmpshape){
        shapeselector->SetSelectedShape(tmpshape);
      }
      shapeselector->SelectShape();
      }
      view->Redraw(); //flushes all the arrays of floating points
      emit QueryDebugMessage(str);
}    
        
     Handle(CustomAIS_Shape) OShape=Handle(CustomAIS_Shape)::DownCast(object);
    if(!OShape.IsNull()){
     //ChosenShape still points to the same object as owner->Selectable()
       ChosenShape=OShape;    //Single Selection for Object
      SetTransShape(ChosenShape);
      GetDepthInfo(ChosenShape);
     cm=CE_SHAPE;
     IsSelectedColorUsed=true;
     view->Redraw();
     emit QueryDebugMessage(tr("Assignment Successful"));
      FlushViewEvent();
      return;
    }
    else{
      curveShape=Handle(CurveAIS_Shape)::DownCast(object);
      if(curveShape){
        SetTransShape(curveShape);
        GetDepthInfo(curveShape);
        cm=CE_SHAPE;
        return;
      }
      else{
      Handle(EditCircleShape) cleShape=Handle(EditCircleShape)::DownCast(object);
      if(cleShape){
        
        return;
      }
      selTextureShape=Handle(AIS_TexturedShape)::DownCast(object);
      if(selTextureShape){
      SetTransShape(selTextureShape);
      GetDepthInfo(selTextureShape);
      cm=CE_SHAPE;
       return;
      }
      
    }
    }
    context->NextSelected();
    }
 }
}     
else if(event->button()==Qt::RightButton){
  if(dc==DC_TWOPNTARC){
     if(cm==CE_CHAXIS){
      chooseAxisMenu->exec(event->globalPosition().toPoint());
      return;
     }
    twoPntArcMenu->exec(event->globalPosition().toPoint());
    return;
  }
  if(dc==DC_TWOPNTCIRCLE){
     if(cm==CE_CHAXIS){
      chooseAxisMenu->exec(event->globalPosition().toPoint());
      return;
     }
     twoPntCircleMenu->exec(event->globalPosition().toPoint());
     return;
  }
  if(dc==DC_APPLYTRANS){
    transMenu->exec(event->globalPosition().toPoint());
    return;
  }
  if(dc==DC_TRANSFORM){
    TransformMenu->exec(event->globalPosition().toPoint());
    return;
  }
  if(dc==DC_EDGES){
    edgesMenu->exec(event->globalPosition().toPoint());
    return;
  }
  if(dc==DC_TWOPNT){
    LineMenu->exec(event->globalPosition().toPoint());
    return;
  }
  if(dc==DC_PRIMCIRCLE){
    primCircleMenu->exec(event->globalPosition().toPoint());
    return;
  }
  if(dc==DC_PRIMLINE){
    primLineMenu->exec(event->globalPosition().toPoint());
    return;
  }
  if(st1==WIRES_SELECT){
    groupWireMenu->exec(event->globalPosition().toPoint());
    return;
  }
  if(dc==DC_MOVE){
   moveMenu->exec(event->globalPosition().toPoint());
   return;
}
if(Eshape==ES_GIZMO){
  if(editShape){
     if(ObjectGizmo){
      if(editShape->PartEdit()==PE_CIRCLEMIDPOINT){
        editCircleMenu->exec(event->globalPosition().toPoint());
        return;
      }
     }

  }
  }
  if(dc==DC_STARTBSPLINE){
    drawBSplineMenu->exec(event->globalPosition().toPoint());
    return;
  }
  if(dc==DC_STARTBEZIER){
    drawBezierMenu->exec(event->globalPosition().toPoint());
    return;
  }
  if(dc==DC_WIREFILLET){
     if(cm==CE_CHAXIS){
      chooseAxisMenu->exec(event->globalPosition().toPoint());
      return;
     }
    wireFilletMenu->exec(event->globalPosition().toPoint());
    return;
  }
  if(dc==DC_RADIUS){
    circleByRadiusMenu->exec(event->globalPosition().toPoint());
    return;
  }
  if(st1==WIRE_SELECT){
    wireMenu->exec(event->globalPosition().toPoint());
    return;
  }
  if(dc==DC_FILLET){
    if(cm==CE_CHAXIS){
      chooseAxisMenu->exec(event->globalPosition().toPoint());
      return;
     }
    edgeFilletMenu->exec(event->globalPosition().toPoint());
    return;
  }
  if(dc==DC_TRIM){
    trimMenu->exec(event->globalPosition().toPoint());
    return;
  }
  if(cm==CE_CHAMFER){
    chamferMenu->exec(event->globalPosition().toPoint());
    return;
  }
  if(cm==CE_FILLET){
    filletMenu->exec(event->globalPosition().toPoint());
    return;
  }
  if(dc==DC_POLYGON){
    drawPolyMenu->exec(event->globalPosition().toPoint());
    return;
  }
  if(dc==DC_LINE){
    drawLineMenu->exec(event->globalPosition().toPoint());
    return;
  }
  if(dc==DC_CIRCLE){
    drawCircle->exec(event->globalPosition().toPoint());
    return;
  }
   if(cm==CE_AXIS){
     axisMenu->exec(event->globalPosition().toPoint());
     return;
   }
   if(cm==CE_POINT){
     pointMenu->exec(event->globalPosition().toPoint());
     return;
   }
  if(gpsstate==GPS_BSPLINE){
    spMenu->exec(event->globalPosition().toPoint());
    return;
  }
  if(gpsstate==GPS_BEZIER){
    bMenu->exec(event->globalPosition().toPoint());
    return;
  }
  if(gpsstate==GPS_GATHER){
   polyMenu->exec(event->globalPosition().toPoint());
    return;
  }
  if(st1==FACE_SELECT){
    faceMenu->exec(event->globalPosition().toPoint());
    return;
  }
 if(st1==EDGE_SELECT){
  edgeMenu->exec(event->globalPosition().toPoint());
  return;
 }

if(cm==CE_SHAPE){
      if(ConstructPointNodeAction->isChecked()){
       if(context->MoveTo(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().y()*dpr)),view,false)==AIS_SOD_Nothing){
      if(CurrentSelMode==4){
       std::cout<<"Successfully Integrated"<<std::endl;
       emit OnSendConvertValue(Point(x_value,y_value,z_value));
       return;
  }
  double projX=0.0,projY=0.0,projZ=0.0;
  view->ConvertToGrid(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().y()*dpr)),projX,projY,projZ);
    //Move it to node graph
   x_value=projX;
   y_value=projY;
   z_value=projZ;
   std::cout<<"Current X Value: "<<x_value<<std::endl;
   std::cout<<"Current Y Value: "<<y_value<<std::endl;
   std::cout<<"Current Z Value: "<<z_value<<std::endl;
   emit OnSendConvertValue(Point(x_value,y_value,z_value));
  return;
  }
      }
      if(ChosenShape.IsNull()){
        if(curveShape){
          SelectedMenu->removeAction(ShapePrsAction);
          SelectedMenu->removeAction(ShowObjectInfo.get());
          IsShapePrsAdded=false;
        }
        
         SelectedMenu->addAction(LinePrsAction);
        IsLinePrsAdded=true;
         SelectedMenu->exec(event->globalPosition().toPoint());
        return;
      }
      if(ChosenShape->Shape().ShapeType()>=5 && ChosenShape->Shape().ShapeType()<=7){
        if(IsShapePrsAdded){
          SelectedMenu->removeAction(ShapePrsAction);
          SelectedMenu->removeAction(ShowObjectInfo.get());
          IsShapePrsAdded=false;
        }
        SelectedMenu->addAction(LinePrsAction);
        SelectedMenu->addAction(ShowEdgeInfo.get());
        IsLinePrsAdded=true;
      }

    else if(ChosenShape->Shape().ShapeType()>=0 && ChosenShape->Shape().ShapeType()<=4){
      if(IsLinePrsAdded){
         SelectedMenu->removeAction(LinePrsAction);
         SelectedMenu->removeAction(ShowEdgeInfo.get());
         SelectedMenu->removeAction(updateWithTransform.get());
         IsLinePrsAdded=false;
      }
      SelectedMenu->addAction(ShapePrsAction);
      SelectedMenu->addAction(ShowObjectInfo.get());
      IsShapePrsAdded=true;
    }
    //After adding,render at a particular position
    SelectedMenu->exec(event->globalPosition().toPoint());
    
    return;
    
}
if(cm==CE_NULL){
  if(ChosenShape.IsNull()){
    DockMenus->exec(event->globalPosition().toPoint());
  if(ConstructPointNodeAction->isChecked()){
  if(context->MoveTo(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().y()*dpr)),view,false)==AIS_SOD_Nothing){
 
  double projX=0.0,projY=0.0,projZ=0.0;
  view->ConvertToGrid(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().y()*dpr)),projX,projY,projZ);
    //Move it to node graph
   x_value=projX;
   y_value=projY;
   z_value=projZ;
   std::cout<<"Current X Value: "<<x_value<<std::endl;
   std::cout<<"Current Y Value: "<<y_value<<std::endl;
   std::cout<<"Current Z Value: "<<z_value<<std::endl;
   emit OnSendConvertValue(Point(x_value,y_value,z_value));
  return;
  }
  else{
    double projX=0.0,projY=0.0,projZ=0.0;
  view->ConvertToGrid(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().y()*dpr)),projX,projY,projZ);
    //Move it to node graph
   x_value=projX;
   y_value=projY;
   z_value=projZ;
   std::cout<<"Current X Value: "<<x_value<<std::endl;
   std::cout<<"Current Y Value: "<<y_value<<std::endl;
   std::cout<<"Current Z Value: "<<z_value<<std::endl;
   emit OnSendConvertValue(Point(x_value,y_value,z_value));
   return; 
  }
}


    return;
  }
  
  }
  


}

return;
 }
}





void mouseMoveEvent(QMouseEvent* event) override{
  if(!view.IsNull() && evt_manager.UpdateMousePosition(Graphic3d_Vec2i(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().y()*dpr))),ToQtMouseButton(event->button()),ToNativeModifiers(Qt::NoModifier),false)){
    if(isEditCircleShapeTransformed && ObjectGizmo->HasActiveMode()){
       ObjectGizmo->Transform(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().y()*dpr)),view);
      
     if(castedBezierShape){
      
       gp_Vec delta(currGizmoPos,ObjectGizmo->Position().Location());
       castedBezierShape->UpdateShape(editShape->Index(),currGizmoPos.Translated(delta));
       context->Redisplay(castedBezierShape,false);
       view->Redraw();
       return;
     }
     if(castedBsplineShape){
      gp_Vec delta(currGizmoPos,ObjectGizmo->Position().Location());
       castedBsplineShape->UpdateShape(editShape->Index(),currGizmoPos.Translated(delta));
       context->Redisplay(castedBsplineShape,false);
       view->Redraw();
      return;
     }
      if(castedLineShape){
        if(editShape->PartEdit()==PE_LINEMIDPOINT){
           nextGizmoPos=ObjectGizmo->Position().Location();
           gp_Vec delta(currGizmoPos,nextGizmoPos);
           castedLineShape->SetBothPoint(LineStart.Translated(delta),LineEnd.Translated(delta));
           castedLineShape->UpdateShape(editShape->PartEdit(),gp_Pnt());

        }
      else{
      nextGizmoPos=ObjectGizmo->Position().Location();
       gp_Vec delta(currGizmoPos,nextGizmoPos);
      castedLineShape->UpdateShape(editShape->PartEdit(),currGizmoPos.Translated(delta));
      }
      context->Redisplay(castedLineShape,true);
      }
      if(castedCircleShape){
        nextGizmoPos=ObjectGizmo->Position().Location();
        gp_Vec delta(currGizmoPos,nextGizmoPos);
        castedCircleShape->UpdateShape(editShape->PartEdit(),currGizmoPos.Translated(delta));
        context->Redisplay(castedCircleShape,true);
      }
      view->Invalidate();
      return;
    }
    if(isObjectTransformed && ObjectGizmo->HasActiveMode()){
      if(dc==DC_TRANSFORM){
      ObjectGizmo->Transform(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().y()*dpr)),view);
      OnUpdateObjectPosition();
      view->Invalidate(); 
      return;
      }
      
      ObjectGizmo->Transform(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().y()*dpr)),view);
      context->Redisplay(ObjectGizmo->Object(),true);
      view->Invalidate(); //force the redraw of the scene...
      return;
    }
  
 
if(context->MoveTo(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().y()*dpr)),view,false)==AIS_SOD_Nothing){
//Still Same as viewer->Grid->IsActive;
Viewer->SetGridEcho(true);
if(Viewer->Grid()->IsActive()){
    double projX=0.0,projY=0.0,projZ=0.0;
    view->ConvertToGrid(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().y()*dpr)),projX,projY,projZ);
    Viewer->ShowGridEcho(view,Graphic3d_Vertex(projX,projY,projZ));
    view->RedrawImmediate();
  }
    if(context->IsDisplayed(currDetShape)){
      currDetShape->UseColor();
    context->Remove(currDetShape,false);
  }
  return;
 view->Redraw();
}


}
}
   

void ComputeTransform(const TopoDS_Shape& prevShape,const TopoDS_Shape& currShape,gp_Trsf& outMat){
   cout<<"PrevShape's Transform:"<<"\n";
  MatrixInspector(prevShape.Location().Transformation());
  cout<<"CurrShape's Transform:"<<"\n";
  MatrixInspector(prevShape.Location().Transformation());
  
  if(currShape.Location().IsIdentity()){
     LoadMessage(tr("Identity Transform"),tr("The Current Transform is an identity matrix"));
     return;
  }
 
  TopLoc_Location prevLoc=currShape.Location();
  TopLoc_Location prevInvLoc=prevLoc.Inverted();
  TopLoc_Location currLoc=currShape.Location();
  auto currTrans=currLoc.Multiplied(prevInvLoc);
  outMat=currTrans.Transformation();
  return;
}
void PrintSelection(const int& mode){
  switch(mode){
    case 0:{
      std::cout<<"A Shape Is Chosen"<<std::endl;
      break;
    }
   case 1:{
       std::cout<<"A Vertex Is Chosen"<<std::endl;
      break;
   }
   case 2:{
     std::cout<<"An Edge Is Chosen"<<std::endl;
      break; 
   }
   case 4:{
      std::cout<<"A Face Is Chosen"<<std::endl;
      break; 
   }
   case 5:{
     std::cout<<"A Shell Is Chosen"<<std::endl;
      break;
   }
   case 6:{
     std::cout<<"A Solid Is Chosen"<<std::endl;
      break;
   }
   default:{
     std::cout<<"A Default Mode"<<std::endl;
      return;
   }
  }
  return;
}


void mouseReleaseEvent(QMouseEvent* event) override{
    if(evt_manager.UpdateMouseButtons(Graphic3d_Vec2i(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().y()*dpr))),ToQtMouseButton(event->button()),ToNativeModifiers(Qt::NoModifier),false)){
     if(event->button()==Qt::LeftButton){
      if(isEditCircleShapeTransformed && ObjectGizmo->HasActiveMode()){
       if(castedBezierShape){
        gp_Vec delta(currGizmoPos,ObjectGizmo->Position().Location());
       castedBezierShape->UpdateShape(editShape->Index(),currGizmoPos.Translated(delta));
       context->Redisplay(castedBezierShape,false);
       ObjectGizmo->StopTransform();
       castedBezierShape.Nullify();
       view->Redraw();
       }
       if(castedBsplineShape){
         gp_Vec delta(currGizmoPos,ObjectGizmo->Position().Location());
       castedBsplineShape->UpdateShape(editShape->Index(),currGizmoPos.Translated(delta));
       context->Redisplay(castedBsplineShape,false);
       ObjectGizmo->StopTransform();
       castedBsplineShape.Nullify();
       view->Redraw();
       }
         if(castedLineShape){
          if(editShape->PartEdit()==PE_LINEMIDPOINT){
          nextGizmoPos=ObjectGizmo->Position().Location();
           gp_Vec delta(currGizmoPos,nextGizmoPos);
           castedLineShape->SetBothPoint(LineStart.Translated(delta),LineEnd.Translated(delta));  
             castedLineShape->UpdateShape(editShape->PartEdit(),gp_Pnt());
          ObjectGizmo->StopTransform(); 
          }

        else{
         nextGizmoPos=ObjectGizmo->Position().Location();
         cout<<"Gizmo Position After Drag:"<<"\n";
         OnDebugGizmo(ObjectGizmo);
         cout<<"\n";
        ObjectGizmo->StopTransform();
         gp_Vec delta(currGizmoPos,nextGizmoPos);
         castedLineShape->UpdateShape(editShape->PartEdit(),currGizmoPos.Translated(delta));
        }
         MatrixInspector(ObjectGizmo->Object()->LocalTransformation());
         
         context->Redisplay(castedLineShape,true); 
        castedLineShape.Nullify();
        }
        else if(castedCircleShape){
          nextGizmoPos=ObjectGizmo->Position().Location();
          gp_Vec delta(currGizmoPos,nextGizmoPos);
        ObjectGizmo->StopTransform();
        castedCircleShape->UpdateShape(editShape->PartEdit(),currGizmoPos.Translated(delta));
        context->Redisplay(castedCircleShape,true); 
        castedCircleShape.Nullify();
}
        view->Invalidate();
       
        isEditCircleShapeTransformed=false;
       
        return;
      }
      if(isObjectTransformed && ObjectGizmo->HasActiveMode()){
        ObjectGizmo->StopTransform();
        view->Invalidate();
        SentTransform=ObjectGizmo->Object()->LocalTransformation();
        SentTransform.SetScaleFactor(ObjectGizmo->Object()->LocalTransformation().ScaleFactor());
        isObjectTransformed=false;
        OnDebugGizmo(ObjectGizmo);
        cout<<"\n";
        MatrixInspector(ObjectGizmo->Object()->LocalTransformation());
        
        Handle(CustomAIS_Shape) chosenShape=Handle(CustomAIS_Shape)::DownCast(ObjectGizmo->Object());
        if(chosenShape){
          chosenShape->SetTransformedShape(SentTransform);
        }
       return;
      }
     }
    
    return;
    }
}


void resizeEvent(QResizeEvent* event) override{
    QWidget::resizeEvent(event);
    if(!view.IsNull()){
        if(UseWindowSize){
        view->MustBeResized();
          int x=0,y=0;
          view->Window()->Size(x,y);
          Viewer->SetRectangularGridGraphicValues(x,y,Grid_Spacing);
          WindowHeight=y;
          WindowWidth=x;
          view->Redraw();
        }
    }
        else{
          int x=0,y=0;
          view->Window()->Size(x,y);
          WindowHeight=y;
          WindowWidth=x;
           view->Redraw();
        }
       
    
    return;
}

void wheelEvent(QWheelEvent* event){
  auto value=event->angleDelta().y();
  
 double steps=value>0 ? 1.10 :-1.0;

  double factor=std::pow(1.1,steps);
  ZoomAtPosition(static_cast<int>(std::lround(event->position().x()*dpr)),static_cast<int>(std::lround((height()-event->position().y())*dpr)),factor);
   
   return;
}

//We can zoom at a point such that we use the view's camera's scale(view->camera()->scale()) and pan the view to still be at that position.
void ZoomAtPosition(const int& mouseX,const int& mouseY,const double& zoomfactor){
  if(zoomfactor<=0.0){
    return;
  }
  //Get the 3d point on the projection plane
  double x,y,z=0.0;
  view->Convert(mouseX,mouseY,x,y,z);
  Handle(Graphic3d_Camera) camera=view->Camera(); //we need to access the camera to access the scale
  const double scale=camera->Scale()/zoomfactor;
  UndoStack->push(new ZoomCommand(view,camera->Scale(),scale));
  camera->SetScale(scale);  //set the scale
  int newPX,newPY=0;

  view->Convert(x,y,z,newPX,newPY); //get the new position from the x,y,z on the projected plane
  int dx=mouseX-newPX;
  int dy=mouseY-newPY;
  if(dx!=0 || dy!=0){
    view->Pan(dx,dy); //Pan the view
    view->Redraw();
    return;
  }
  view->Redraw();
  return;
}


signals:
  void QueryDebugMessage(const QString& message);
  void OnOpenSceneSettings(bool truth);
  void OnRenderShapePrsWidget();
  void OnSendCubeEvent();
  void OnDestroyMaterialProp();
  void OnSetPreviousColor();
  void EmitShape(const TopoDS_Shape& shape);
  void EmitTransformedShape(const TopoDS_Shape& shape);
  void OnSendConvertValue(const Point& pt);
  void OnEmitBoolValue(bool value);
  void OnEmitFaceBool(bool value);
  void OnEmitEdgeBool(bool value);
  void OnEmitFace(const TopoDS_Face& face);
  void OnEmitEdge(const TopoDS_Edge& edge);
  void OnEmitWire(const TopoDS_Wire& wire); //On Send Wire.
  void OnEmitSent();
  void OnSentFalseValue();
  void EmitGatherWire(bool truth);
  void EmitAxis(const gp_Ax2& axis);
  void OnSendScaleTransform(const gp_Trsf& scaletransform);
  void OnEmitIndicies(const int a,const int b);
  void OnEmitPointCollections(const NCollection_Array1<gp_Pnt>& pnts);
  void OnEmitEdgeInfo(const EdgeInfo& edgeinfo);
  void OnEmitSurfaceInfo(const SurfaceInfo& surfaceinfo);
  void EmitMaterial();
  void UnEmitMaterial();
  void EmitFloatValue(const float& val);
  void EmitLineValue(const gp_Dir& dir,const gp_Pnt& point,const float& val);
  void EmitCircleValue(const gp_Ax2& axis,const float& radius);
   void EmitEdgeColl();
public slots:
//This returns the top view
void SetDrawCircleAction(bool toggled){
    DrawCircle=true;
    return;
}
void OnDeleteObject(bool toggled=false){
  if(!ChosenShape.IsNull()){
    if(ChosenShape->dt==DP_MIRROR){
      UndoStack->push(new DeleteCommand(ChosenShape,context,0,3));

    }
    UndoStack->push(new DeleteCommand(ChosenShape,context,0,3));
    if(!Shapes.empty()){
    for(auto iter=Shapes.begin();iter!=Shapes.end();++iter){
       if(ChosenShape==iter->second){
        Shapes.erase(iter);
       }
    }
    }
    context->Remove(ChosenShape,false);
    UndoStack->push(new DeleteCommand(ChosenShape,context,0,1));
    if(context->IsDisplayed(currSelShape)){
      context->Remove(currSelShape,false);
    }
    if(context->IsDisplayed(currDetShape)){
      context->Remove(currDetShape,false);
    }
    if(!ObjectGizmo.IsNull()){
       if(context->IsDisplayed(ObjectGizmo)){
        context->Erase(ObjectGizmo,false);

       }
       
    }
    ChosenShape.Nullify();
    view->Redraw();

    return;
  }
  else{
    if(curveShape){
      if(!DraftShapes.empty()){
        for(auto iter=DraftShapes.begin();iter!=DraftShapes.end();++iter){
          if(iter->second==curveShape){
            DraftShapes.erase(iter);
          }
        }
      }
        if(context->IsDisplayed(curveShape)){
          context->Remove(curveShape,true);
          UndoStack->push(new DeleteCommand(curveShape,context,0,1));
          lineShape=Handle(LineAIS_Shape)::DownCast(curveShape);
          if(lineShape){
            lineShape->DeleteMarkers();
          }
        }
        else if(!lineShape){
          circShape=Handle(CircleAIS_Shape)::DownCast(curveShape);
          if(circShape){
            circShape->DeleteMarkers();
          }
        }
       if(!ObjectGizmo.IsNull()){
       if(context->IsDisplayed(ObjectGizmo)){
        context->Erase(ObjectGizmo,false);

       }
       
    }
        curveShape.Nullify();
        view->Redraw();
      }
      if(selTextureShape){
       
        context->Remove(selTextureShape,false);
        UndoStack->push(new DeleteCommand(selTextureShape,context,0,3));
        if(ObjectGizmo->IsAttached()){
           ObjectGizmo->Detach();
           context->Erase(ObjectGizmo,false);
        }
        view->Redraw();
       
       }
    }
    if(chosenInteractive){
      Handle(EditCircleShape) edshape=Handle(EditCircleShape)::DownCast(chosenInteractive);
      if(edshape){
        context->Remove(edshape,true);
         UndoStack->push(new DeleteCommand(edshape,context,0,1));
      }
    }
  
  return;
}
void OnShowSceneSetting(bool truth){
  emit OnOpenSceneSettings(truth);
  return;
}
void UndoStackContent(){
  if(!UndoStack.get()){
    return;
  }
  UndoStack->undo();
  return;
}
void RedoStackContent(){
  if(!UndoStack.get()){
    return;
  }
  UndoStack->redo();
  return;
}
void OnSendDrawCubeFn(){
  emit OnSendCubeEvent();
  return;
}
void EnableRotation(bool isChecked){
    if(isChecked && ChosenShape.IsNull()){
     emit QueryDebugMessage(tr("No Object is Chosen,Please Select an object in Scene"));
     return;     
    }
    if(isChecked){
      if(ScaleAction->isChecked()){
        ScaleAction->setChecked(false);
      }
      if(TranslateAction->isChecked()){
        TranslateAction->setChecked(false);
      }
      EnableManipulatorPart(AIS_MM_Scaling,ChosenShape);
      EnableManipulatorPart(AIS_MM_Translation,ChosenShape); 
      isScaleGizmoEnabled=false;
      isTranslateGizmoEnabled=false;
      isRotateGizmoEnabled=true;
      if(!ObjectGizmo.IsNull()){

          ObjectGizmo->EnableMode(AIS_MM_Rotation);
         emit QueryDebugMessage(tr("Rotation Gizmo Enabled"));
      }
      return;
    }
    else{
       if(ObjectGizmo.IsNull()){
        isScaleGizmoEnabled=false;
      isTranslateGizmoEnabled=false;
      isRotateGizmoEnabled=false;
           return;
       }
       RemoveObjectGizmo();
       ObjectGizmo->Detach();
       ObjectGizmo->DeactivateCurrentMode();
       ObjectGizmo.Nullify();
    }
    return;
}
void EnableScaling(bool isChecked){
  if(isChecked && ChosenShape.IsNull()){
     emit QueryDebugMessage(tr("No Object is Chosen,Please Select an object in Scene"));
     return;     
    }
    if(isChecked){
      if(TranslateAction->isChecked()){
        TranslateAction->setChecked(false);
      }
      if(RotateAction->isChecked()){
        RotateAction->setChecked(false);
      }
      EnableManipulatorPart(AIS_MM_Rotation,ChosenShape);
       EnableManipulatorPart(AIS_MM_Translation,ChosenShape);
      isScaleGizmoEnabled=true;
      isTranslateGizmoEnabled=false;
      isRotateGizmoEnabled=false;
      if(!ObjectGizmo.IsNull()){
          ObjectGizmo->EnableMode(AIS_MM_Scaling);
         emit QueryDebugMessage(tr("Scaling Gizmo Enabled"));
      }
      return;
    }
    else{
       if(ObjectGizmo.IsNull()){
        isScaleGizmoEnabled=false;
      isTranslateGizmoEnabled=false;
      isRotateGizmoEnabled=false;
           return;
       }
       RemoveObjectGizmo();
       ObjectGizmo->Detach();
       ObjectGizmo->DeactivateCurrentMode();
       ObjectGizmo.Nullify();
    }
    return;
}
  void EnableTranslation(bool isChecked){
     if(isChecked && ChosenShape.IsNull()){
     emit QueryDebugMessage(tr("No Object is Chosen,Please Select an object in Scene"));
     return;     
    }
    if(isChecked){
      if(RotateAction->isChecked()){
        RotateAction->setChecked(false);

      }
      if(ScaleAction->isChecked()){
        ScaleAction->setChecked(false);
      }
      EnableManipulatorPart(AIS_MM_Rotation,ChosenShape);
      EnableManipulatorPart(AIS_MM_Scaling,ChosenShape);
      isScaleGizmoEnabled=false;
      isTranslateGizmoEnabled=true;
      isRotateGizmoEnabled=false;
      if(!ObjectGizmo.IsNull()){
          ObjectGizmo->EnableMode(AIS_MM_Translation);
         emit QueryDebugMessage(tr("Translation Gizmo Enabled"));
      }
      return;
    }
    else{
       if(ObjectGizmo.IsNull()){
        isScaleGizmoEnabled=false;
      isTranslateGizmoEnabled=false;
      isRotateGizmoEnabled=false;
           return;
       }
       RemoveObjectGizmo();
       ObjectGizmo->Detach();
       ObjectGizmo->DeactivateCurrentMode();
      
    }
  return;
  }
void OnDestroyObjectGizmo(){
  if(ObjectGizmo.IsNull()){
    emit QueryDebugMessage(tr("Cannot Destroy An Empty Gizmo Object"));
    return;
  }
 
  if(ObjectGizmo->IsAttached()){
    ObjectGizmo->Detach();
  }
  if(ObjectGizmo->HasActiveMode()){
    ObjectGizmo->DeactivateCurrentMode();
  }
  if(ObjectGizmo){
    context->Erase(ObjectGizmo,true);
  }
  
  return;
}
void OnSendRenderShapePrs(){
  emit OnRenderShapePrsWidget(); 
  return;
}
//on convert Face Centre to point node
void OnConvertToFacePoint(bool value){
  if(value){
    emit OnEmitBoolValue(value);
    emit OnSendConvertValue(Point(int_x,int_y,int_z)); 
    return;
  }
  else{
    emit OnEmitBoolValue(value);
    }
  
  
  return;
}

void OnConvertEdgeToFace(bool value){
  if(value){
    ConvertEdgeToFace();
    if(!convertedEdgeFace.IsNull()){
      emit OnEmitFace(convertedEdgeFace);
    }
  }
  else{
    emit OnEmitFaceBool(value);
  }
  return;
}

void OnGatherPoint(bool value){
    if(value){
      gpsstate=GPS_GATHER;
      
    }
    return;
}
void OnGatherBezier(bool value){
    if(value){
      gpsstate=GPS_BEZIER;
      
    }
    return;
}
void OnDeleteBezier(){
  if(!transCurve->Polygon()->Points().empty()){
    transCurve->Polygon()->Clear();
    transCurve->Polygon()->OnDestroy();
    transCurve->OnDestroy();
    gpsstate=GPS_NULL;
    GatherCurveAction->setChecked(false);
  }
}
void OnDeletePoints(){
   if(!transPolygon->Points().empty()){
    transPolygon->Clear();
    transPolygon->OnDestroy();
    gpsstate=GPS_NULL;
    GatherPointAction->setChecked(false);
   }
  
  return;
}
void OnRemoveLastOne(){
  if(!transPolygon->Points().empty()){
     transPolygon->RemoveLastPoint();
  }
  return;
}
void OnRefreshView(){
  view->Redraw(); //cause a redraw;
  return;
}
void OnHandlePeriodic(bool Value){
  bspCurve->SetIsPeriodic(Value);
  return;
}
void OnGatherBSpline(bool value){
   if(value){
     gpsstate= GPS_BSPLINE;
   }
   return;
}
void OnDeleteBSplinePoint(){
  if(!bspCurve->Polygon()->Points().empty()){
    bspCurve->Polygon()->Clear();
    bspCurve->Polygon()->OnDestroy();
    bspCurve->OnDestroy();
    gpsstate=GPS_NULL;
    GatherBSplineAction->setChecked(false);
  }
  return;
}
void OnHandleSent(){
  if(!ChosenShape){
  LoadMessage(tr("Chosen Shape Message"),tr("No Shape Selected"));
  return;
  }
  for(auto iter=Shapes.begin();iter!=Shapes.end();++iter){
    if(iter->second==ChosenShape){
      SentShapeId=iter->first;
      SentShape=iter->second->Shape();
      LoadMessage(tr("Shape Found"),tr("Shape And Id Found"));
      emit OnEmitSent();
      break;
    }
  }
  return;
}
void OnKnowId(){
  if(!ChosenShape){
    return;
  }
  bool isFound=false;
  for(auto iter=Shapes.begin();iter!=Shapes.end();++iter){
           if(iter->second==ChosenShape){
               ShapeId=iter->first;
               LoadMessage(tr("ID Found"),QString("Current Id")+QString::number(iter->first));
               isFound=true;
               break;
           }
        }
      if(isFound==false){
      LoadMessage(tr("ID message"),tr("ID not found"));

       }
    return;
}
void OnSendPointValues(const bool value){
  if(value){
    emit OnSendConvertValue(Point(x_value,y_value,z_value));
  }
  else{
    emit OnSentFalseValue();
  }
}
void OnDestroyMarker(){
if(context->IsDisplayed(pointMarker)){
  context->Remove(pointMarker,true);

}
   if(pointMarker){
   pointMarker.Nullify();
   }
   return;
}
void OnSendWire(bool value){
  if(value){
    emit OnEmitWire(selWire);
    return;
  }
  else{
   emit OnEmitFaceBool(value);
  }
  return;
}
void OnConvertToFaceNode(bool value){
  if(value){
  if(selShape){
    OnSearch(selShape);
    FindSubShapeIndex(selShape,1);
    ParentIndex=ShapeId;

    emit OnEmitFace(selFace);
    return;
  }
   emit OnEmitFace(selFace);

} 
  else{
  emit OnEmitFaceBool(value);
  }

  return;
}
void OnConvertToEdge(bool value){
  if(value){
    if(selShape){
        OnSearch(selShape);
    FindSubShapeIndex(selShape,0); //search for edge index
    ParentIndex=ShapeId;
    emit OnEmitEdge(selEdge);
    return;
    }
    emit OnEmitEdge(selEdge);
  }
  else{
    emit OnEmitEdgeBool(value);
  }
  return;
}
//p for parent index and c for child index
void OnShadeFaceWithIndex(const int& p,const int&c){
  if(p==-1 || c==-1){
     LoadMessage(tr(""),tr("It is either the parent index or the child index is negative"));
     return;
  }
  if(Shapes.find(p)==Shapes.end()){
     LoadMessage(tr(""),tr("Object with this index does not exist"));
     return;
  }
  selShape=Shapes.at(p);
  if(!selShape){
    LoadMessage(tr(""),tr("Failed On Assigning a copy of an object of CustomAIS_Shape"));
    return;
  }
  selFaceShape=selShape->GetFace(c);
  PrevSelMode=4;
  selShape->ShadeFace(c, Quantity_NOC_CHARTREUSE2);
  if(context->IsDisplayed(selShape)){
    context->Redisplay(selShape,true);
  }
  return;
}
void UnShadeFaceWithIndex(const int& p,const int& c){
  if(p==-1 || c==-1){
     LoadMessage(tr(""),tr("It is either the parent index or the child index is negative"));
     return;
  }
  if(Shapes.find(p)==Shapes.end()){
     LoadMessage(tr(""),tr("Object with this index does not exist"));
     return;
  }
  selShape=Shapes.at(p);
  if(!selShape){
    LoadMessage(tr(""),tr("Failed On Assigning a copy of an object of CustomAIS_Shape"));
    return;
  }
  
  PrevSelMode=-1;
  selShape->UnShadeFace(c);
  if(context->IsDisplayed(selShape)){
    context->Redisplay(selShape,true);
  }
  return;
}
void OnConvertToBSpline(){
  if(transPolygon){
    GeomAPI_PointsToBSpline geomSpline(transPolygon->To_Array_One());
    if(geomSpline.IsDone()){
       BRepBuilderAPI_MakeEdge edge(geomSpline.Curve());
       if(edge.IsDone()){
        Handle(CustomAIS_Shape) shape=new CustomAIS_Shape(edge.Edge());
        if(shape){
           context->Display(shape,true);
           Shapes.insert(std::pair<size_t,Handle(CustomAIS_Shape)>(objectCount,shape));
           ++objectCount;
           context->Remove(transPolygon->DisplayedShape(),true);
        }
       }
       return;
    }
    else{
    LoadMessage(tr(""),tr("Failed To Convert To BSpline"));
    return;
    }
    
  }
  return;
}
void OnHandleFaceSent(){
  if(!selShape){
    LoadMessage(tr(""),tr("No Parent Shape own this selected entity"));
    return;
  }
  //mainIndex helps us to locate the main's shape  
   OnSearch(selShape);
    FindSubShapeIndex(selShape,1);
    mainIndex=ShapeId;
   emit  OnEmitIndicies(mainIndex,subMainIndex);
  return;
}

void OnHandleSentScaleTransform(bool value){
  if(value){
    gp_Trsf scaleTrans;
    scaleTrans.SetScale(gp_Pnt(0.0,0.0,0.0),SentTransform.ScaleFactor());
    MatrixInspector(scaleTrans);
    emit OnSendScaleTransform(scaleTrans);
    
  }
  else{
     emit OnEmitFaceBool(value);
  }
  return;
}
void OnHandleSentRotateTransform(bool value){
  if(value){
   gp_Trsf rotateTrans;
   rotateTrans.SetRotationPart(SentTransform.GetRotation());
   MatrixInspector(rotateTrans);
    emit OnSendScaleTransform(rotateTrans);

  }
  else{
    emit OnEmitFaceBool(value);
  }
  return;
}
void OnHandleSentTranslateTransform(bool value){
  if(value){
    gp_Trsf translate;
    translate.SetTranslationPart(SentTransform.TranslationPart());
     MatrixInspector(translate);
    emit OnSendScaleTransform(translate);
  }
  else{
     emit OnEmitFaceBool(value);
  }
  return;
}
//this assumes the face normal on the face
void OnAssumeFaceNormal(){
  if(selFace.IsNull()){
     LoadMessage(tr(""),tr("No Selected Face"));
     return;
  }
  gp_Dir chDir=SURFACE::GetFaceNormal(selFace,selFacePoint);
  chosenDir=chDir;
  if(!AxisObject){
    AxisObject=new AIS_Axis(new Geom_Axis1Placement(gp_Pnt(0.0,0.0,0.0),gp_Dir(0.0,1.0,0.0)));
  }
  AxisObject->SetAxis1Placement(new Geom_Axis1Placement(selFacePoint,chDir));
  if(context->IsDisplayed(AxisObject)){
    context->Activate(AxisObject,0);
    context->Redisplay(AxisObject,true);
  
  }
  else{
    context->Activate(AxisObject,0);
    context->Display(AxisObject,true);
  }
  
  return;
}
void OnHandlePositionedAxis(bool value){
 if(value){
  EmitAxis(gp_Ax2(selFacePoint,chosenDir));
 }
 else{
   emit OnEmitFaceBool(value);
 }
 return;
}
void OnHandleOriginAxis(bool value){
   if(value){
    EmitAxis(gp_Ax2(gp_Pnt(0.0,0.0,0.0),chosenDir));
 }
 else{
   emit OnEmitFaceBool(value);
 }
  return;
}
void OnRemoveAxisObject(){
  if(AxisObject){
        if(context->IsDisplayed(AxisObject)){
          context->Remove(AxisObject,true);
          view->Redraw();
        }

      }
      return;
}
void AssumeFaceCenterNormal(){
  if(selFace.IsNull()){
    return;
  }
  gp_Dir chDir=SURFACE::GetFaceNormal(selFace,SURFACE::GetSurfaceCentre(selFace));
  chosenDir=chDir;
  selFacePoint=SURFACE::GetSurfaceCentre(selFace);
  if(!AxisObject){
    AxisObject=new AIS_Axis(new Geom_Axis1Placement(gp_Pnt(0.0,0.0,0.0),gp_Dir(0.0,1.0,0.0)));
  }
  AxisObject->SetAxis1Placement(new Geom_Axis1Placement(SURFACE::GetSurfaceCentre(selFace),chDir));
  if(context->IsDisplayed(AxisObject)){
    context->Activate(AxisObject,0);
    context->Redisplay(AxisObject,true);
  
  }
  else{
    context->Activate(AxisObject,0);
    context->Display(AxisObject,true);
  }
  return;
}
//selFacePoint
void OnGetFacePoint(bool value){
if(value){
    emit OnEmitBoolValue(value);
    emit OnSendConvertValue(Point(selFacePoint.X(),selFacePoint.Y(),selFacePoint.Z())); 
    return;
  }
  else{
    emit OnEmitBoolValue(value);
    }
  return;
}
void OnGetFaceInfo(){
  if(selFace.IsNull()){
    LoadMessage(tr(""),tr("No face is selected"));
    return;
  }
  SurfaceInfo info;
  GetSurfaceInfo(selFace,info);
  emit OnEmitSurfaceInfo(info);
  return;
}
void OnGetEdgeInfo(){
  if(selEdge.IsNull()){
    LoadMessage(tr(""),tr("No edge is selected"));
    return;
  }
  EdgeInfo info;
  GetEdgeInfo(selEdge,info);
  emit OnEmitEdgeInfo(info);
  return;
}
void OnHandleDrawLine(bool value){
  if(value){
    dc=DC_LINE;
    LoadMessage(tr(""),tr("Click a point before clicking on start drawing menu option"));
    drawLineMenu->stopLineAction->setChecked(false);
  }
  return;
}
void OnStopDrawingLine(bool value){
  if(value){
    dc=DC_NULL;
    drawAction->setChecked(false);
  }
}
void InitializeDrawDialog(){
  if(drawLineDialog){
    drawLineDialog->SetPointOfRotation(LineStartPoint);
    drawLineDialog->exec();
  }
  return;
}
void OnHandleFaceDrawAction(){
  if(selFace.IsNull()){
    LoadMessage(tr(""),tr("No Face is Selected"));
    return;
  }
  auto dir=SURFACE::GetFaceNormal(selFace,selFacePoint);
  faceDialog->InitAxis(selFacePoint,dir);
  faceDialog->exec();
  return;
}
void OnHandleFaceDone(){
  if(!faceDialog){
    LoadMessage(tr(""),tr("FaceLineDialog failed to be created"));
    return;
  }
  const float pie=3.14159265;
  gp_Ax1 axis=faceDialog->Axis();
  float ang=faceDialog->Angle();
  gp_Dir dir=faceDialog->Direction();
  float val=faceDialog->Length();
  float convertedAngle=ang*(pie/180.0f);
  dir.Rotate(axis,convertedAngle);
  

  Handle(Geom_Line) line=new Geom_Line(faceDialog->PointOfInterest(),dir);
  BRepBuilderAPI_MakeEdge edgemaker;
  TopoDS_Edge edge;
  edgemaker.Init(line,0,val);
  if(!edgemaker.IsDone()){
    LoadMessage(tr(""),tr("Failed To Create Line"));
    return;
  }

  edge=edgemaker.Edge();
  
  Handle(LineAIS_Shape) lineShape=new LineAIS_Shape(edge);
  lineShape->SetColor(faceDialog->outputColor());
  lineShape->SetCurve(line);
  lineShape->SetStartPoint(faceDialog->PointOfInterest());
  gp_Pnt refPoint;
  line->D0((double)val,refPoint);
  lineShape->SetEndPoint(refPoint);
  lineShape->SetDir(dir);

  DraftShapes.emplace(draftCount,lineShape);
   context->Display(lineShape,true);
   ++draftCount;
  UndoStack->push(new UndoCreationCommand(context,lineShape));
return;
}
void OnHandleDone(){
  if(!drawLineDialog){
     LoadMessage(tr(""),tr("DrawLineDialog failed to be created"));
     return;
  }
  
  const float pie=3.14159265;
  gp_Ax1 axis=drawLineDialog->Axis();
  float ang=drawLineDialog->Angle();
  gp_Dir dir=drawLineDialog->Direction();
  float val=drawLineDialog->Length();
  if(val==0.000){
    LoadMessage(tr(""),tr("No Length is set"));
    return;
  }
  float convertedAngle=ang*(pie/180.0f);
  dir.Rotate(axis,convertedAngle);
  TopoDS_Edge edge=TopoDS_Edge();
  Handle(Geom_Line) line=new Geom_Line(LineStartPoint,dir);
  BRepBuilderAPI_MakeEdge edgeMaker;
  edgeMaker.Init(line,0,val);
  if(edgeMaker.IsDone()){
    edge=edgeMaker.Edge();
  }
  else{
    LoadMessage(tr(""),tr("Failed To Create Line"));
    return;
  }
  Handle(LineAIS_Shape) lineShape=new LineAIS_Shape(edge);
  lineShape->SetColor(drawLineDialog->OutputColor());

  lineShape->SetCurve(line);
  lineShape->SetStartPoint(LineStartPoint);
  gp_Pnt refPoint;
  line->D0((double)val,refPoint);
  lineShape->SetEndPoint(refPoint);
  lineShape->SetDir(dir);
  DraftShapes.emplace(draftCount,lineShape);
  context->Display(lineShape,false);
  view->Redraw();
  ++draftCount;
  return;
}
void OnHandleFirstPoint(bool value){
  if(value){
    LoadMessage(tr(""),tr("Choose thie first point of the circle"));
    drawCircle->SetThreeValues(value,false,false);
  }
  return;
}
void OnHandleSecondPoint(bool value){
  if(value){
    LoadMessage(tr(""),tr("Choose the second point of the circle,this second point is the centre of the circle"));
    drawCircle->SetThreeValues(false,value,false);
  }
  return;
}
void OnHandleThirdPoint(bool value){
  if(value){
    LoadMessage(tr(""),tr("Choose the third point of the circle"));
    drawCircle->SetThreeValues(false,false,value);
  }
  return;
}
void OnHandleStopCircle(){
  dc=DC_NULL;
  drawCircle->SetThreeValues(false,false,false);
  GC_MakeCircle circleMaker(CircleFirstPoint,CircleSecondPoint,CircleThirdPoint);
  
  Handle(Geom_Circle) geom_circle=circleMaker.Value();
  if(!geom_circle){
    LoadMessage(tr(""),tr("Failed to create a circle"));
  }
  BRepBuilderAPI_MakeEdge edgeMaker(geom_circle);
  TopoDS_Edge edge=TopoDS_Edge();
  if(edgeMaker.IsDone()){
    edge=edgeMaker.Edge();
  }
  else{
    LoadMessage(tr(""),tr("Failed to create an edge"));
    return;
  }
  Handle(CircleAIS_Shape) edgeShape=new CircleAIS_Shape(edge);
  edgeShape->SetCenter(geom_circle->Circ().Location());
  edgeShape->SetDir(geom_circle->Circ().Position().Direction());
  edgeShape->SetRadius(geom_circle->Circ().Radius());
  edgeShape->SetCurve(geom_circle);
  edgeShape->SetContext(context);
  DraftShapes.emplace(draftCount,edgeShape);
  ++draftCount;
  context->Display(edgeShape,false);
  UndoStack->push(new UndoCreationCommand(context,edgeShape));
  view->Redraw();
  return;

}
void InitCircleDraw(){
  dc=DC_CIRCLE;
  return;
}
void OnDestroyCircle(){
  drawCircle->SetThreeValues(false,false,false);
  dc=DC_NULL;
  return;
}
void OnInitDrawPolygon(){
  if(drawPolygonDialog){
    drawPolygonDialog->SetPointOfRotation(LineStartPoint);
    drawPolygonDialog->exec();
  }
  return;
}
void OnContinuePolygon(){
  if(drawPolygonDialog){
    drawPolygonDialog->SetNextPointOfRotation();
    drawPolygonDialog->exec();
  }
  return;
}
void OnStartPolygon(bool value){
if(value){
  dc=DC_POLYGON;
  LoadMessage(tr(""),tr("Select a starting point in the view \n To Continue Drawing the polygon, click  continue menu item \n"));
  return;
 }
 return;
}
void OnHandlePolygonDone(){

  const float pie=3.14159265;
  gp_Ax1 axis=drawPolygonDialog->Axis();
  float ang=drawPolygonDialog->Angle();
  gp_Dir dir=drawPolygonDialog->Direction();
  float val=drawPolygonDialog->Length();
 
  if(val==0.000){
    LoadMessage(tr(""),tr("No Length is set"));
    return;
  }
  float convertedAngle=ang*(pie/180.0f);
  dir.Rotate(axis,convertedAngle);
  TopoDS_Edge edge=TopoDS_Edge();
  Handle(Geom_Line) line=new Geom_Line(drawPolygonDialog->PointOfRotation(),dir);
  gp_Pnt refPoint;
  line->D0((double)val,refPoint);
  drawPolygonDialog->SetNextPoint(refPoint);
  BRepBuilderAPI_MakeEdge edgeMaker;
  edgeMaker.Init(line,0,val);
  if(edgeMaker.IsDone()){
    edge=edgeMaker.Edge();
  }
  else{
    LoadMessage(tr(""),tr("Failed To Create Line"));
    return;
  }
  drawPolygonDialog->SetIsNextPoint(true);
  Handle(LineAIS_Shape) lineShape=new LineAIS_Shape(edge);
  lineShape->SetCurve(line);
  lineShape->SetStartPoint(drawPolygonDialog->PointOfRotation());
   line->D0((double)val,refPoint);
  lineShape->SetEndPoint(refPoint);
  lineShape->SetDir(dir);
  collectiveIndex.push_back(draftCount);
  DraftShapes.emplace(draftCount,lineShape);
  UndoStack->push(new UndoCreationCommand(context,lineShape));
  
  context->Display(lineShape,false);
  view->Redraw();
  ++draftCount;
  return;
}

void OnEndPolygon(){
  drawPolygonDialog->SetToDefault();
  collectiveIndex.clear();
  loopwire=TopoDS_Wire();
  polygonAction->setChecked(false);
  dc=DC_NULL;
  return;
}
void ClosePolygon(){
  if(drawPolygonDialog->IsClosed()){
    LoadMessage(tr(""),tr("Drawn Object is closed"));
    return;
  }
  if(drawPolygonDialog->IsNextPoint()){
     BRepBuilderAPI_MakeEdge edgeMaker(drawPolygonDialog->StartPoint(),drawPolygonDialog->NextPoint());
     TopoDS_Edge edge;
     if(edgeMaker.IsDone()){
       edge=edgeMaker.Edge();
     }
     else{
       LoadMessage(tr(""),tr("Failed To Construct Line"));
       return;
     }
     
     gp_Vec dirVec(drawPolygonDialog->NextPoint(),drawPolygonDialog->StartPoint());
     dirVec.Normalize();
  Handle(Geom_Line) line=new Geom_Line(drawPolygonDialog->NextPoint(),dirVec);
  Handle(LineAIS_Shape) lineShape=new LineAIS_Shape(edge);
  
  lineShape->SetCurve(line);
  lineShape->SetStartPoint(drawPolygonDialog->StartPoint());
  lineShape->SetEndPoint(drawPolygonDialog->NextPoint());
  lineShape->SetDir(dirVec);
  collectiveIndex.push_back(draftCount);
  DraftShapes.emplace(draftCount,lineShape);
  context->Display(lineShape,false);
     drawPolygonDialog->SetIsClosed(true);
  UndoStack->push(new UndoCreationCommand(context,lineShape));
     view->Redraw();
     ++draftCount;
     return;
  }
  return;
}

void OnConvertPolygonToWire(){
  if(drawPolygonDialog->IsConvertedToWire()){
    LoadMessage(tr(""),tr("Object has been converted to wire"));
    return;
  }
  if(collectiveIndex.empty()){
    LoadMessage(tr(""),tr("There are no source edge(s)"));
    return;
  }

  int success;
  BRepBuilderAPI_MakeWire wireMaker;
  for(int i=0;i<collectiveIndex.size();i++){
    wireMaker.Add(TopoDS::Edge(DraftShapes.at(collectiveIndex.at(i))->Shape()));
    context->Remove(DraftShapes.at(collectiveIndex.at(i)),false);
    DraftShapes.erase(collectiveIndex.at(i));
  }
  OnHandleWireError(wireMaker.Error(),success);
  if(success==-1){
    return;
  }
  loopwire=wireMaker.Wire();
  polygonShape=new CustomAIS_Shape(wireMaker.Wire());
  context->Display(polygonShape,false);
  UndoStack->push(new UndoCreationCommand(context,polygonShape));
  drawPolygonDialog->SetIsConvertedToWire(true);
  view->Redraw();
  return;
}

void OnConvertToFace(){
  if(drawPolygonDialog->IsConvertedToFace()){
    LoadMessage(tr(""),tr("It has been converted to face"));
    return;
  }
  if(!drawPolygonDialog->IsConvertedToWire()){
   OnConvertPolygonToWire();
  }
  if(loopwire.IsSame(TopoDS_Wire())){
    LoadMessage(tr(""),tr("Failed to convert to loop"));
    return;
  }
  BRepBuilderAPI_MakeFace facemaker(loopwire);
  if(!facemaker.IsDone()){
    LoadMessage(tr(""),tr("Failed To Convert To Face"));
    return;
  }
  if(context->IsDisplayed(polygonShape)){
    context->Remove(polygonShape,false);
  }
  Handle(CustomAIS_Shape) faceShape=new CustomAIS_Shape(facemaker.Face());
  
  context->Display(faceShape,false);
  UndoStack->push(new UndoCreationCommand(context,faceShape));
  view->Redraw();
  drawPolygonDialog->SetIsConvertedToFace(true);
  return;
}
void OnInitBezier(bool value){
  if(value){
    dc=DC_STARTBEZIER;
    LoadMessage(tr(""),tr("Select a point in space to start drawing,\n click on start menu to start drawing \n click on continue menu item to continue"));

  }
  return;
}
void OnStartPointForBezier(){
  if(drawBezierDialog){
    drawBezierDialog->SetPointOfRotation(LineStartPoint);
    drawBezierDialog->points.push_back(LineStartPoint);
    drawBezierDialog->exec();
  }
  return;
}
void OnContinueBezier(){
  if(drawBezierDialog){
    drawBezierDialog->SetNextPointOfRotation();
    drawBezierDialog->exec();
  }
  return;
}
void OnEndBezier(){
  drawBezierDialog->SetToDefault();
  if(bezierShape){
    bezierShape->SetContext(context);
  DraftShapes.emplace(draftCount,bezierShape);
  ++draftCount;
  }
  drawnWireShape.Nullify();
  bezierShape.Nullify();
  dc=DC_NULL;
  drawBezierByDialog->setChecked(false);
  return;
}
void OnHandleBezierDone(){
  if(!drawBezierDialog){
     return;
  }
   const float pie=3.14159265;
  gp_Ax1 axis=drawBezierDialog->Axis();
  float ang=drawBezierDialog->Angle();
  gp_Dir dir=drawBezierDialog->Direction();
  float val=drawBezierDialog->Length();
  if(val==0.000){
    LoadMessage(tr(""),tr("No Length is set"));
    return;
  }
  float convertedAngle=ang*(pie/180.0f);
  dir.Rotate(axis,convertedAngle);
  Handle(Geom_Line) line=new Geom_Line(drawBezierDialog->NextPoint(),dir);
 
  gp_Pnt refpoint;
  
  line->D0((double)val,refpoint);

  drawBezierDialog->SetNextPoint(refpoint);
   drawBezierDialog->points.push_back(drawBezierDialog->NextPoint());
  drawBezierDialog->SetIsNextPoint(true);
 BRepBuilderAPI_MakeWire wiremaker;
 
  std::cout<<"Size of Points for drawBezierDialog's Points "<<drawBezierDialog->GetPoints().size()<<"\n";

 if(drawBezierDialog->points.size()>=2){
 for(int i=1;i<drawBezierDialog->points.size();i++){
     BRepBuilderAPI_MakeEdge edgemaker_2(drawBezierDialog->GetPoints().at(i-1),drawBezierDialog->GetPoints().at(i));
     if(edgemaker_2.IsDone()){
     wiremaker.Add(edgemaker_2.Edge());
     }
 }
 
 if(!wiremaker.IsDone()){
     LoadMessage(tr("Wire Error"),tr("Error in creating edges"));
    
     return;
 }
 }
 if(!wiremaker.IsDone()){
  return;
 }
 if(!drawnWireShape){
   drawnWireShape=new CustomAIS_Shape(wiremaker.Wire());
   context->Display(drawnWireShape,true);
 }
 else{
  drawnWireShape->SetShape(wiremaker.Wire());
  CheckDisplayStatus(drawnWireShape,context->DisplayStatus(drawnWireShape));

 }
if(drawBezierDialog->GetPoints().size()<2){
    LoadMessage(tr("Bezier Error "),tr("The number of points for bezier is less than 2"));
    return;
    //if the size of the array is 2
  }
  if(drawBezierDialog->GetPoints().size()>Geom_BezierCurve::MaxDegree()+1){
    LoadMessage(tr("Bezier Error"),tr("The number of points is greaterr than the max degree +1"));
    return;
  }
  NCollection_Array1<gp_Pnt> pointarray(drawBezierDialog->GetPoints().front(),0,drawBezierDialog->GetPoints().size()-1);
  
  Handle(Geom_BezierCurve) bezierCurve=new Geom_BezierCurve(pointarray);
  if(!bezierCurve){
      return;
  } 
  BRepBuilderAPI_MakeEdge edgemaker;
  edgemaker.Init(bezierCurve);
  if(!edgemaker.IsDone()){
      return;
  }
  if(bezierShape.IsNull()){
    bezierShape=new BezierAIS_Shape(edgemaker.Edge());
    bezierShape->SetCurve(bezierCurve);
    context->Display(bezierShape,true);
    return;
  }
  bezierShape->SetShape(edgemaker.Edge());
  bezierShape->SetCurve(bezierCurve);
  UndoStack->push(new UndoCreationCommand(context,bezierShape));
   context->Redisplay(bezierShape,true);
  return;
}




void OnApplyFillet(bool value){
  if(value){
    cm=CE_FILLET;
    faceMenu->applyChamfer->setChecked(false);
  }
  return;
}
void OnApplyChamfer(bool value){
  if(value){
    cm=CE_CHAMFER;
    faceMenu->applyFillet->setChecked(false);
  }
  return;
}
void OnChooseFilletVertex(bool value){
  if(value){
   context->Deactivate();
   CurrentSelMode=1;
   context->Activate(1);
   LoadMessage(tr(""),tr("You can now select a vertex of the edge of the selected face for fillet"));

  }
  else{
   context->Deactivate();
   CurrentSelMode=4;
   context->Activate(4);
  }
  return;
}
void OnChooseChamferVertex(bool value){
  if(value){
  context->Deactivate();
   CurrentSelMode=1;
   context->Activate(1);
    LoadMessage(tr(""),tr("You can now select a vertex of the edge of the selected face for chamfer operation"));
  }
  else{
    context->Deactivate();
   CurrentSelMode=4;
   context->Activate(4);
  }
  return;
}

void OnChooseEdgeForChamfer(bool value){
   if(value){
  context->Deactivate();
   CurrentSelMode=2;
   context->Activate(2);
    LoadMessage(tr(""),tr("You can now select a vertex of the edge of the selected face for chamfer operation"));
  }
  else{
    context->Deactivate();
   CurrentSelMode=4;
   context->Activate(4);
  }
return;
}


void EndFillet(){
  cm=CE_NULL;
  faceMenu->applyFillet->setChecked(false);
  return;
}
void EndChamfer(){
  cm=CE_NULL;
  faceMenu->applyChamfer->setChecked(false);
  return;
}
void BuildFillet(){
  if(selFace.IsNull()){
    LoadMessage(tr(""),tr("No Face is selected"));
    return;
  }
  //check the validity of the parameters
  if(filletVertex.IsNull()){
    LoadMessage(tr(""),tr("No point is selected"));
    return;
  }
  std::unique_ptr<ChFi2d_Builder> filletBuilder;
  filletBuilder=std::make_unique<ChFi2d_Builder>(selFace);
  filletBuilder->AddFillet(filletVertex,filletDialog->Radius());
  int success=0;
  EDGE::ChFiErrorHandler(filletBuilder->Status(),success);
  if(success==-1){
    LoadMessage(tr(""),tr("Cannot Complete Build"));
    return;
  }
  TopoDS_Face filletFace=filletBuilder->Result();
  selShape->SetShape(filletFace);
  context->Redisplay(selShape,false);
  view->Redraw();
  return;
}
void BuildChamfer(){
  if(selFace.IsNull()){
    LoadMessage(tr(""),tr("No Face is selected"));
    return;
  }
  //check the validity of the parameters
  if(chamferVertex.IsNull()){
    LoadMessage(tr(""),tr("No point is selected"));
    return;
  }
  std::unique_ptr<ChFi2d_Builder> chamferBuilder;
  chamferBuilder=std::make_unique<ChFi2d_Builder>(selFace);
  float pie=3.14159265;
  float ang=chamferDialog->Angle()*(pie/180.0f);
  chamferBuilder->AddChamfer(chamferEdge,chamferVertex,ang,chamferDialog->Distance());
  int success=0;
  EDGE::ChFiErrorHandler(chamferBuilder->Status(),success);
  if(success==-1){
    LoadMessage(tr(""),tr("Cannot Complete Build"));
    return;
  }
  TopoDS_Face chamferedFace=chamferBuilder->Result();
  selShape->SetShape(chamferedFace);
  context->Redisplay(selShape,false);
  view->Redraw();
  return;
}


void OnSelectRadiusForFillet(){
   if(filletDialog){
    filletDialog->exec();
   }
   return;
}
void OnSelectOthersForChamfer(){
  if(chamferDialog){
    chamferDialog->exec();
  }
  return;
}

void OnHandleCopyMaterial(bool value){
  if(value){
  if(ChosenShape){
   chosenShapeMaterial=ChosenShape->Attributes()->ShadingAspect()->Material();
   emit EmitMaterial();
  }
  }
  else{
    emit UnEmitMaterial();
  }
  return;
}
void OnHandleTrim(bool value){
  if(value){
    LoadMessage(tr(""),tr("Select Portion of Curve That You want to keep"));
   prevdc=dc;
   dc=DC_TRIM;
  }
  else{
    dc=prevdc;
  }
}
void OnEndTrim(){
  dc=DC_NULL;
  st1=EDGE_SELECT;
  return;
}
void OnTrimCurve(){
  if(!selShape){
    LoadMessage(tr(""),tr("No Parent Shape"));
    return;
  }
  
  if(selEdge.IsNull()){
    LoadMessage(tr(""),tr("No Selected Edge"));
    return;
  }
  EDGE::OnGetParameterOnCurve(selEdge,trimFirstPoint,trimparam.Umin);
  EDGE::OnGetParameterOnCurve(selEdge,trimSecondPoint,trimparam.Umax);
  double dummyUmin;
  double dummyUmax;
  Handle(Geom_Curve) curve=BRep_Tool::Curve(selEdge,dummyUmin,dummyUmax);
  if(!curve){
    LoadMessage(tr(""),tr("Failed To Convert To Convert To it's underlying curve"));
    return;
  }
  if(trimparam.Umin==trimparam.Umax){
      LoadMessage(tr(""),tr("Same Points were clicked"));
      return;
  }
  BRepBuilderAPI_MakeEdge edgemaker;
  if(trimparam.Umin<trimparam.Umax){
    edgemaker.Init(curve,trimparam.Umin,trimparam.Umax);
  }
  else{
    edgemaker.Init(curve,trimparam.Umax,trimparam.Umin);
  }
  if(!edgemaker.IsDone()){
    LoadMessage(tr(""),tr("Failed To Trim Curve"));
    return;
  }
  UndoStack->push(new UndoCreationCommand(context,selShape));
  selShape->SetShape(edgemaker.Edge());
  context->Redisplay(selShape,false);
  view->Redraw();
  
  return;
}

void TrimByPoints(){
  if(!selShape){
    LoadMessage(tr(""),tr("No Shape Selected"));
    return;
  }
   
  if(selEdge.IsNull()){
    LoadMessage(tr(""),tr("No Selected Edge"));
    return;
  }
  double dummyUmin;
  double dummyUmax;
  Handle(Geom_Curve) curve=BRep_Tool::Curve(selEdge,dummyUmin,dummyUmax);
  if(!curve){
    LoadMessage(tr(""),tr("Failed To Convert To Convert To it's underlying curve"));
    return;
  }
  BRepBuilderAPI_MakeEdge edgeMaker;
  edgeMaker.Init(curve,trimFirstPoint,trimSecondPoint);
  if(!edgeMaker.IsDone()){
   LoadMessage(tr(""),tr("Failed to trim the selected edge"));
   return;
  }
  UndoStack->push(new UndoCreationCommand(context,selShape));
  selShape->SetShape(edgeMaker.Edge());
  context->Redisplay(selShape,true);
  return;
}
void OnHandleFirstEdge(bool value){
  if(value){
    context->Deactivate();
    context->Activate(2); 
    CurrentSelMode=2;
    LoadMessage(tr(""),tr("Choose the first edge"));
    edgeFilletMenu->SetBoolValues(value,false,false);
  }
  return;
}
void OnHandleSecondEdge(bool value){
  if(value){
    context->Deactivate();
    context->Activate(2);
    CurrentSelMode=2;
    LoadMessage(tr(""),tr("Choose the second edge"));
      edgeFilletMenu->SetBoolValues(false,value,false);
  }
  return;
}
void OnHandleChosenFilletVertex(bool value){
  if(value){
    LoadMessage(tr(""),tr("Choose the vertex \nHint:Choose the point of intersection of the two edge"));
    context->Deactivate();
    context->Activate(1); //for vertex;
    CurrentSelMode=1;
    edgeFilletMenu->SetBoolValues(false,false,value);
  }
  else{
    context->Deactivate();
    context->Activate(2);
    CurrentSelMode=2;
  }
  return;
}
void OnSetToFillet(bool value){
  if(value){
    dc=DC_FILLET;
  }
  else{
    dc=DC_NULL;
  }
  return;
}
void OnHandleEndOps(){
  dc=DC_NULL;
  edgeMenu->filletAction->setChecked(false);
  return;
}
void OnApplyFilletToEdges(){
   std::unique_ptr<ChFi2d_FilletAPI> filletAPI=make_unique<ChFi2d_FilletAPI>();
   filletAPI->Init(filletEdge,filletEdge_1,gp_Pln(LineStartPoint,gottenDir)); //on the xoy plane
   if(filletDialog->Radius()<=0.0){
    LoadMessage(tr(""),tr("Radius is less than or equal to zero"));
    return;
   }
   if(!filletAPI->Perform(filletDialog->Radius())){
      LoadMessage(tr(""),tr("Failed To Compute Fillet for selected edges"));
      return;
   }
   int n=filletAPI->NbResults(LineStartPoint);
   TopoDS_Edge Edge_1;
   TopoDS_Edge Edge_2;
   auto fi_edge=filletAPI->Result(LineStartPoint,Edge_1,Edge_2,n);

   BRepBuilderAPI_MakeWire wiremaker;
   wiremaker.Add(Edge_1);
   wiremaker.Add(fi_edge);
   wiremaker.Add(Edge_2);
   
   TopoDS_Wire wire;
   if(!wiremaker.IsDone()){
      LoadMessage(tr(""),tr("Failed to combine the edges"));
      return;
   }
   wire=wiremaker.Wire();
   Handle(CustomAIS_Shape) wireshape=new CustomAIS_Shape(wire);
   gp_Trsf trsf;
   trsf.SetTranslation(gp_Vec(LineStartPoint.X(),LineStartPoint.Y(),LineStartPoint.Z()));
   context->SetLocation(wireshape,TopLoc_Location(trsf));
   UndoStack->push(new UndoCreationCommand(context,wireshape));
   context->Display(wireshape,false);
   view->Redraw();
   


   return;
}
void OnConvertToWireNode(bool value){
   if(value){
    if(!selWire.IsNull()){
    emit OnEmitWire(selWire);
    }
    return;
  }
  else{
   emit OnEmitFaceBool(value);
  }
}
//for the fillet to be applied to wire,the wire must consist of two edges
void ApplyFilletToWire(){
  if(selWire.IsNull()){
     LoadMessage(tr(""),tr("The Selected Wire is empty,failed to cast"));
     return;
  }
  if(filletDialog->Radius()<=0.0000){
    LoadMessage(tr(""),tr("Radius is less than or equal to zero"));
    return; //to avoid unexpected results
  }
  TopExp_Explorer wireExplorer;
  wireExplorer.Init(selWire,TopAbs_EDGE);
  int i=0;
  for(;wireExplorer.More();wireExplorer.Next()){
    ++i;
  }
  if(i>2){
    LoadMessage(tr(""),tr("Loop has more than two edges"));
    return;
  }
  std::unique_ptr<ChFi2d_FilletAPI> filletAPI=std::make_unique<ChFi2d_FilletAPI>();
  filletAPI->Init(selWire,gp_Pln(LineStartPoint,gottenDir));
  if(!filletAPI->Perform(filletDialog->Radius())){
    LoadMessage(tr(""),tr("Failed to perform fillet operation on the set of edges of the wire(loop)"));
    return;
  }
  TopoDS_Edge edge;
  TopoDS_Edge edge_1;
  int n=filletAPI->NbResults(LineStartPoint);
  auto fi_edge=filletAPI->Result(LineStartPoint,edge,edge_1,n);

  BRepBuilderAPI_MakeWire wiremaker;
  wiremaker.Add(edge);
  wiremaker.Add(fi_edge);
  wiremaker.Add(edge_1);

  if(!wiremaker.IsDone()){
     LoadMessage(tr(""),tr("Failed to Build Loop from edges after fillet operation"));
     return;
  }
  if(!selShape){
    LoadMessage(tr(""),tr("No Selected Shape"));
    return;
  }
  if(selShape->Shape().ShapeType()!=TopAbs_WIRE){
    LoadMessage(tr(""),tr("The Selected Shape is not a wire"));
    return;
  }
  UndoStack->push(new UndoCreationCommand(context,selShape));
  selShape->SetShape(wiremaker.Wire());
  context->Redisplay(selShape,false);
  view->Redraw();
  return;

}
void OnChooseVertexForWire(bool value){
  if(value){
    LoadMessage(tr(""),tr("Choose the vertex \nHint:Choose the point of intersection of the two edge"));
    context->Deactivate();
    context->Activate(1); //for vertex;
    CurrentSelMode=1;
  }
  else{
    context->Deactivate();
    context->Activate(3);
    CurrentSelMode=3;
  }
  return;
}
void OnConvertToFaceShape(){
  if(selWire.IsNull()){
    LoadMessage(tr(""),tr("No Selected Wire"));
    return;
  }
  BRepBuilderAPI_MakeFace facemaker(selWire);
  if(!facemaker.IsDone()){
   LoadMessage(tr(""),tr("Failed To Create Face From Wire"));
   return;
  }
  if(selShape){
     selShape->SetShape(facemaker.Face());
     context->Redisplay(selShape,true);
  }
  else{
    LoadMessage(tr(""),tr("No Shape Is Selected"));
  }

  return;
}
void DrawCircleOnBool(bool value){
  if(value){
    LoadMessage(tr(""),tr("Select a point at which you want to draw the circle\n to start drawing circle,click start drawing menu item \n To end circle operation,click end circle operation \n CLICK_TYPE FOR POINT SELECTION: left mouse button"));
    dc=DC_RADIUS;
  }
  else{
    dc=DC_NULL;

  }
  return;
}
void EndRadiusOps(){
  drawCircleByRadius->setChecked(false);
  dc=DC_NULL;
  return;
}
void OnHandleCircleDialog(){
  circleDialog->SetPoint(LineStartPoint);
  circleDialog->exec();
  return;
}
void OnHandleDoneForCircleDialog(){
  if(!circleDialog){
    LoadMessage(tr(""),tr("Failed to initialize an object of circle dialog"));
    return;
  }
    if(circleDialog->Radius()<=0.0){
        return;
    }
    float pie=3.14159265;
   
    float rad=circleDialog->Angle()*(pie/180.0f);
    auto drawAxis=circleDialog->AxisOfDraw();
    drawAxis.Rotate(circleDialog->rotateAxis(),rad);
    
     BRepBuilderAPI_MakeEdge edgeMaker;
     Handle(Geom_Circle) circle=new Geom_Circle(drawAxis,circleDialog->Radius());
     edgeMaker.Init(circle);
     if(!edgeMaker.IsDone()){
        return;
     }
     Handle(CircleAIS_Shape) circleShape=new CircleAIS_Shape(edgeMaker.Edge());
     circleShape->SetContext(context);
     circleShape->SetRadius(circle->Circ().Radius());
     circleShape->SetCenter(circle->Circ().Location());
     circleShape->SetDir(circle->Circ().Position().Direction());
     circleShape->SetCurve(circle);
     DraftShapes.emplace(draftCount,circleShape);
     ++draftCount;
      context->Display(circleShape,true);
     UndoStack->push(new UndoCreationCommand(context,circleShape));
  return;

}
void SetOnApplyFilletToAllBool(bool value){
  if(value){
    prevdc=dc;
    dc=DC_WIREFILLET;
    return;
  }
  else{
    dc=prevdc;
  }
  return;
}
void OnGetFirstEdgeOnWire(bool value){
  if(value){
    LoadMessage(tr(""),tr("Select The First Edge of the loop"));
    context->Deactivate();
    context->Activate(2);
    CurrentSelMode=2;
     wireFilletMenu->selectSecondEdge->setChecked(false);

  }
  else{
    context->Deactivate();
    context->Activate(3);
    CurrentSelMode=3;
  }
  return;
}
void OnGetSecondEdgeOnWire(bool value){
   if(value){
    LoadMessage(tr(""),tr("Select the Second Edge Of the loop"));
    context->Deactivate();
    context->Activate(2);
    CurrentSelMode=2;
    wireFilletMenu->selectFirstEdge->setChecked(false);

  }
  else{
    context->Deactivate();
    context->Activate(3);
    CurrentSelMode=3;
  }
  return;
  
}
void OnEndWireFilletOps(){
   dc=DC_NULL;
   wireFilletMenu->selectFirstEdge->setChecked(false);
   wireFilletMenu->selectSecondEdge->setChecked(false);
   return;
}
void OnApplyFilletToSetOfEdges(){
  if(!wireShape){
    LoadMessage(tr(""),tr("Failed to get parent shape"));
    return;
  }
  if(wiredEdge.IsNull()){
    LoadMessage(tr(""),tr("Failed to get first edge"));
    return;
  }
  if(wiredEdge_1.IsNull()){
    LoadMessage(tr(""),tr("Failed to get second edge"));
    return;
  }
  if(selWire.IsNull()){
    LoadMessage(tr(""),tr("No Selected Wire(loop)"));
    return;
  }
   TopExp_Explorer wireExplorer;
   wireExplorer.Init(selWire,TopAbs_EDGE);
   std::vector<TopoDS_Edge> edges;
   int i=0;
   int firstIndex=-1;
   int secondIndex=-1;
   for(;wireExplorer.More();wireExplorer.Next()){
       if(TopoDS::Edge(wireExplorer.Current()).IsSame(wiredEdge)){
        firstIndex=i;
       }
       if(TopoDS::Edge(wireExplorer.Current()).IsSame(wiredEdge_1)){
        secondIndex=i;
       }
       edges.push_back(TopoDS::Edge(wireExplorer.Current()));
       ++i;
   }
   if(firstIndex==-1){
     LoadMessage(tr(""),tr("No matching index for the first edge"));
     return;
   }
   if(secondIndex==-1){
    LoadMessage(tr(""),tr("No matching index for the second edge"));
    return;
   }
   std::vector<TopoDS_Edge>::iterator iter;
   if(firstIndex<secondIndex){
     iter=edges.begin()+secondIndex;
   }
   else{
    iter=edges.begin()+firstIndex;
   }
   if(iter==edges.end()){
     LoadMessage(tr(""),tr("Failed to get an handle"));
     return;
   }
   std::unique_ptr<ChFi2d_FilletAPI> filletAPI=std::make_unique<ChFi2d_FilletAPI>();
   filletAPI->Init(wiredEdge,wiredEdge_1,gp_Pln(LineStartPoint,gp_Dir(0.0,0.0,1.0))); //on the xoy plane
   if(filletDialog->Radius()<=0.0){
    LoadMessage(tr(""),tr("Radius is less than or equal to zero"));
    return;
   }
   if(!filletAPI->Perform(filletDialog->Radius())){
      LoadMessage(tr(""),tr("Failed To Compute Fillet for selected edges"));
      return;
   }
   int n=filletAPI->NbResults(LineStartPoint);
   TopoDS_Edge Edge_1;
   TopoDS_Edge Edge_2;
   auto fi_edge=filletAPI->Result(LineStartPoint,Edge_1,Edge_2,n);
    if(firstIndex<secondIndex){
    edges[firstIndex]=Edge_1;
    edges[secondIndex]=Edge_2;
    }
    else{
      edges[secondIndex]=Edge_1;
      edges[firstIndex]=Edge_2;
    }
   edges.insert(iter,std::move(fi_edge));
   BRepBuilderAPI_MakeWire wiremaker;
   for(int i=0;i<edges.size();++i){
    wiremaker.Add(edges.at(i));
   }
   if(!wiremaker.IsDone()){
     LoadMessage(tr(""),tr("Failed To Build Loop"));
     return;
   }
   wireShape->SetShape(wiremaker.Wire());
   context->Redisplay(wireShape,true);
  return;  
}
void OnHandleEditCircle(){
  if(!selCurveShape){
    LoadMessage(tr(""),tr("No Clicked Object Of Draft Shape"));
    return;
  }
  lineShape=Handle(LineAIS_Shape)::DownCast(selCurveShape);
  if(lineShape){
    if(!lineShape->context){
      lineShape->context=context;
    }
    lineShape->OnDisplayEditComp(lineShape);
    CurrentSelMode=0;
    context->Activate(0);
    cout<<"Casted To an object of LineAIS_Shape"<<"\n";
    return;
  }
   circShape=Handle(CircleAIS_Shape)::DownCast(selCurveShape);

   if(circShape){
     if(!circShape->context){
       circShape->context=context;
     }
     circShape->OnDisplayComponent(circShape);
      CurrentSelMode=0;
      context->Activate(0);
      cout<<"Casted to an object of CircleAIS_Shape"<<"\n";
      return;
   }
   bshape=Handle(BezierAIS_Shape)::DownCast(selCurveShape);
  if(bshape){
    bshape->SetContext(context);
    bshape->ComputeEditShape(bshape);
    return;
  }
  bsplineShape=Handle(BSplineAIS_Shape)::DownCast(selCurveShape);
  if(bsplineShape){
    if(!bsplineShape->Context()){
      bsplineShape->SetContext(context);
    }
    bsplineShape->SetDir(view->Camera()->Direction());
    bsplineShape->ComputeEditShape(bsplineShape);

    return;
  }
  arcShape=Handle(ArcAIS_Shape)::DownCast(selCurveShape);
  if(arcShape){
    Quantity_Color color;
    arcShape->Color(color);
    editarcDialog->SetColor(color);
    editarcDialog->SetGeomCircle(arcShape->Circle());
    editarcDialog->SetPrevRadius((double)arcShape->Circle()->Radius());
    editarcDialog->SetPrevValues(arcShape->U1(),arcShape->U2());
    editarcDialog->exec();
    return;
  }
  else{
    std::cout<<"Could not find a suitable cast"<<"\n";
    return;
  }
  return;
}
void OnUpdateTransformForEditCircleShape(Handle(EditCircleShape) edshape){
  if(!edshape){
    return;
  }
  switch(edshape->EditType()){
    case ET_LINE:{
      switch(edshape->PartEdit()){
        case PE_LINESTART:{
          castedLineShape=Handle(LineAIS_Shape)::DownCast(edshape->AttachedObject());
          isEditCircleShapeTransformed=true;
           currGizmoPos=castedLineShape->Start();
           cout<<"Before LINESTART"<<"\n";
           PrintTheTriples(currGizmoPos);
          return;
        }
        case PE_LINEEND:{
          castedLineShape=Handle(LineAIS_Shape)::DownCast(edshape->AttachedObject());
          isEditCircleShapeTransformed=true;
           currGizmoPos=castedLineShape->End();
           cout<<"Before LINEEND"<<"\n";
           PrintTheTriples(currGizmoPos);
          return;
        }
        case PE_LINEMIDPOINT:{
          castedLineShape=Handle(LineAIS_Shape)::DownCast(edshape->AttachedObject());
          isEditCircleShapeTransformed=true;
          currGizmoPos=castedLineShape->UpdateMidpoint();
          LineStart=castedLineShape->Start();
          LineEnd=castedLineShape->End();
          cout<<"LINE START"<<"\n";
          PrintTheTriples(LineStart);
          cout<<"\n";
          cout<<"LINE END"<<"\n";
          PrintTheTriples(LineEnd);
          cout<<"\n";
          return;
        }
      }
    }
    case ET_CIRCLE:{
       switch(edshape->PartEdit()){
        case PE_CIRCLEMIDPOINT:{
          castedCircleShape=Handle(CircleAIS_Shape)::DownCast(edshape->AttachedObject());
          currGizmoPos=castedCircleShape->Center();
          isEditCircleShapeTransformed=true;
          break;
        }
       
       }
    }
    case ET_BEZIER:{
        castedBezierShape=Handle(BezierAIS_Shape)::DownCast(edshape->AttachedObject());
        currGizmoPos=castedBezierShape->GetPointAtIndex(edshape->Index());
        isEditCircleShapeTransformed=true;
        break;
    }
    case ET_BSPLINE:{
      castedBsplineShape=Handle(BSplineAIS_Shape)::DownCast(edshape->AttachedObject());
      currGizmoPos=castedBsplineShape->GetPointAtIndex(edshape->Index());
       isEditCircleShapeTransformed=true;
    }
    break;
  }
  return;
}
void RecomputeLinePrs(){
  if(lineShape){
    lineShape->UpdatePresentation();
}
  if(circShape){
    circShape->UpdatePresentation();
  }
  return;
}
void RemoveLineEdit(){
  if(lineShape){
    lineShape->RemoveEdit();
  }
  if(circShape){
   circShape->RemovePrs();
  }
  if(bshape){
    bshape->RemoveEdit();
  }
  if(bsplineShape){
    bsplineShape->RemoveEdit();
  }
  return;
}
void OnDestroyLineShape(){
  if(lineShape){
    lineShape.Nullify();
  }
  if(circShape){
    circShape.Nullify();
  }
  if(bshape){
    bshape.Nullify();
  }
  if(bsplineShape){
    bsplineShape.Nullify();
  }
  return;
}
void OnStartArcDraw(){
  LoadMessage(tr(""),tr("Kindly Select a point in space"));
  dc=DC_NULL;
  return;
}
void OnInitiateArcDraw(){
  if(arcDialog){
    arcDialog->SetPoint(LineStartPoint);
    arcDialog->exec();
  }
  return;
}
void OnHandleArcDraw(){
  if(!arcDialog){
    cout<<"Cannot Initialize dialog"<<"\n";
    return;
  }
  float pie=3.14159265;
  float rad1=arcDialog->GetU1()*(pie/180.0f);
  float rad2=arcDialog->GetU2()*(pie/180.0f);
  GC_MakeArcOfCircle arcmaker(arcDialog->Circle()->Circ(),(double)rad1,(double)rad2,true);
  if(!arcmaker.Value()){
    return;
  }
  BRepBuilderAPI_MakeEdge edgeMaker;
  edgeMaker.Init(arcmaker.Value());
  if(!edgeMaker.IsDone()){
    return;
  }
  Handle(ArcAIS_Shape) arcshape=new ArcAIS_Shape(edgeMaker.Edge());
  if(!arcshape){
    return;
  }
  arcshape->SetColor(arcDialog->ArcColor());
  arcshape->SetU1((double)arcDialog->GetU1());
  arcshape->SetU2((double)arcDialog->GetU2());
  arcshape->SetCircle(arcDialog->Circle());
  context->Display(arcshape,true);
  DraftShapes.emplace(draftCount,arcshape);
  UndoStack->push(new UndoCreationCommand(context,arcshape));
  ++draftCount;
  return;
}
void OnUpdateWithTransform(){
 if(circShape){
  circShape->UpdateWithTransform(context->Location(circShape).Transformation());
}
  if(lineShape){
   lineShape->UpdateWithTransform(context->Location(lineShape).Transformation());
  }

 return;
}
void OnEditCircle(){
if(!circleEditDialog){
    return;
}
if(editShape){
  circShape=Handle(CircleAIS_Shape)::DownCast(editShape->AttachedObject());
  if(circShape){
    circleEditDialog->SetCircleInfo(circShape->GetCircle());
    circleEditDialog->SetPreviousRadius(circShape->GetCircle()->Circ().Radius());

  }
  
}
circleEditDialog->exec();
 return;
}
void OnHandleDoneForCircleEdit(){
  if(!editShape){
    return;
  }
  if(editShape->PartEdit()==PE_CIRCLEMIDPOINT){
    if(!circShape){
      return;
    }
    BRepBuilderAPI_MakeEdge edgemaker;
    edgemaker.Init(circleEditDialog->CircleInfo());
    if(!edgemaker.IsDone()){
      return;
    }
    circShape->SetShape(edgemaker.Edge());
    context->Redisplay(circShape,true);
  }
  circShape.Nullify();
   return;
}
void OnHandleCircleEdit(){
  if(editShape){
    editShape.Nullify();
    if(ObjectGizmo){
      RemoveObjectGizmo();
      ObjectGizmo.Nullify();
    }
    return;
  }
}
void SetGizmoStateForEditShape(){
   if(ObjectGizmo){
     ObjectGizmo->SetPart(AIS_MM_Rotation,false);
     ObjectGizmo->SetPart(AIS_MM_Scaling,false);
     context->Redisplay(ObjectGizmo,true);
   }
    return;
}
void SetGizmoForWholeObject(){
  if(ObjectGizmo){
    ObjectGizmo->SetPart(AIS_MM_Rotation,true);
    ObjectGizmo->SetPart(AIS_MM_Scaling,true);
    ObjectGizmo->SetPart(AIS_MM_Translation,true);
    if(context->IsDisplayed(ObjectGizmo)){
      context->Redisplay(ObjectGizmo,true);
    }
  }
   return;
}
void OnHandleForUpdateForTransform(){
 if(!curveShape){
     return;
 }
 lineShape=Handle(LineAIS_Shape)::DownCast(curveShape);
 
 if(lineShape){
   auto ret=QMessageBox::information(nullptr,tr("info"),tr("Kindly move tho object to the desired position before Updating with transform"));
   if(ret==QMessageBox::Ok){
    auto ret_1=QMessageBox::question(nullptr,tr("Transform Question"),tr("Will you like to perform the transform now"));
    if(ret_1==QMessageBox::Cancel){
       return;
    }
    if(ret_1==QMessageBox::Ok){
     if(ObjectGizmo){
     lineShape->UpdateWithGizmoPos(ObjectGizmo->Position().Location());
     view->Redraw();
     return;
    }
    }

   }
 return;
 }
 circShape=Handle(CircleAIS_Shape)::DownCast(curveShape);
 if(circShape){
        return;
   
 }
 return;
}
void OnMoveToFace(bool isSelected){
  if(isSelected){
      dc=DC_MOVE;
      prevCurrSelMode=CurrentSelMode;
      CurrentSelMode=4;

      context->Deactivate();
      context->Activate(4);
      if(context->IsDisplayed(ObjectGizmo)){
        context->Erase(ObjectGizmo,false);
      }
  }
  else{
    moveToSelectedFaceAction->setChecked(true);
  }
  return;
}
void OnHandleStartMove(){ //Select Point
  LoadMessage(tr(""),tr("Select an object in space that you want to move\n NB: the object should not contain the face to which you want to move the object"));
  LoadMessage(tr(""),tr("Select a point on a face to position the selected object"));
  
  return;
}
void OnExecuteMove(){
  if(ChosenShape){
  gp_Vec delta(gp_Pnt(0.0,0.0,0.0),LineStartPoint);
  gp_Trsf trsf=context->Location(ChosenShape).Transformation();
  trsf.SetTranslationPart(delta);
  BRepBuilderAPI_Transform trans(ChosenShape->Shape(),trsf);
  if(trans.IsDone()){
    ChosenShape->SetShape(trans.Shape());
    context->SetLocation(ChosenShape,TopLoc_Location(gp_Trsf()));
    context->Redisplay(ChosenShape,true);
  }
  }
  else if(curveShape){
  gp_Vec delta(gp_Pnt(0.0,0.0,0.0),LineStartPoint);
  gp_Trsf trsf=context->Location(curveShape).Transformation();
  trsf.SetTranslationPart(delta);
  BRepBuilderAPI_Transform trans(curveShape->Shape(),trsf);
  if(trans.IsDone()){
    curveShape->SetShape(trans.Shape());
    context->SetLocation(curveShape,TopLoc_Location(gp_Trsf()));
    context->Redisplay(curveShape,true);
  }
  }
  return;
}
void OnEndMove(){
  moveToSelectedFaceAction->setChecked(false);
  context->Deactivate();
  context->Activate(prevCurrSelMode);
  CurrentSelMode=prevCurrSelMode;
  dc=DC_NULL;
  return;
}
void OnExecuteImage(){
  if(imageDialog){
    imageDialog->exec();
  }
  return;
}
void OnHandleImageDone(){
   if(!imageDialog){
    LoadMessage(tr(""),tr("Failed to initialize dialog"));
    return;
   }
   
   if(!imageDialog->Pixmap().IsNull()){
      
      nodeImage=imageDialog->Pixmap();
      nodeImage->SetTopDown(true);
      if(!textureShape){
        textureShape=new AIS_TexturedShape(TopoDS_Shape());
        textureShape->SetTextureMapOn();
        cout<<"Textured Shape Set"<<"\n";
      }
      TopoDS_Face face=SURFACE::BuildRectFace(static_cast<float>(imageDialog->Width()),static_cast<float>(imageDialog->Height()));
      if(!face.IsSame(TopoDS_Face())){
         textureShape->SetShape(face);
         cout<<"Face Set"<<"\n";
      }
      if(nodeImage){
        
    
      textureShape->SetTexturePixMap(nodeImage);
      textureShape->SetColor(Quantity_NOC_WHITE);
      cout<<"Texture map is on"<<"\n";
      
      }
      context->Display(textureShape,3,0,true);
   }
  return;
}
void OnInitBSpline(bool value){
  if(value){
    dc=DC_STARTBSPLINE;
    LoadMessage(tr(""),tr("Select a point in space to start drawing,\n click on start menu to start drawing \n click on continue menu item to continue"));

  }
  return;
}

void OnStartPointForBSpline(){
  if(bsplineDialog){
    bsplineDialog->SetPointOfRotation(LineStartPoint);
    bsplineDialog->points.push_back(LineStartPoint);
    bsplineDialog->exec();
  }
  return;
}
void OnContinueBSpline(){
  if(bsplineDialog){
    bsplineDialog->SetNextPointOfRotation();
    bsplineDialog->exec();
  }
  return;
}
//drawnBsplineShape
void OnEndBSpline(){
  bsplineDialog->SetToDefault();
  if(drawnBsplineShape){
    drawnBsplineShape->SetContext(context);
  DraftShapes.emplace(draftCount,drawnBsplineShape);
  ++draftCount;
  }
  UndoStack->push(new UndoCreationCommand(context,drawnBsplineShape));
  drawnWireShape.Nullify();
  drawnBsplineShape.Nullify();
  drawBSplineByDialogAction->setChecked(false);
  dc=DC_NULL;
  return;
}
void OnHandleBSplineDone(){
  if(!bsplineDialog){
     return;
  }
   const float pie=3.14159265;
  gp_Ax1 axis=bsplineDialog->Axis();
  float ang=bsplineDialog->Angle();
  gp_Dir dir=bsplineDialog->Direction();
  float val=bsplineDialog->Length();

  if(ang>=0.1 && ang<=0.999999999){
    LoadMessage(tr(""),tr("Angle is not greater or equal to 1.0"));
    return;
  }
  if(val==0.000){
    LoadMessage(tr(""),tr("No Length is set"));
    return;
  }
  float convertedAngle=ang*(pie/180.0f);
  dir.Rotate(axis,convertedAngle);
  Handle(Geom_Line) line=new Geom_Line(bsplineDialog->NextPoint(),dir);
  
  gp_Pnt refpoint;
  
  line->D0((double)val,refpoint);

  bsplineDialog->SetNextPoint(refpoint);
  bsplineDialog->points.push_back(bsplineDialog->NextPoint());
  bsplineDialog->SetIsNextPoint(true);
 BRepBuilderAPI_MakeWire wiremaker;
 
  std::cout<<"Size of Points for bsplineDialog's Points "<<bsplineDialog->GetPoints().size()<<"\n";

 if(bsplineDialog->points.size()>=2){
 for(int i=1;i<bsplineDialog->points.size();i++){
     BRepBuilderAPI_MakeEdge edgemaker_2(bsplineDialog->GetPoints().at(i-1),bsplineDialog->GetPoints().at(i));
     if(edgemaker_2.IsDone()){
     wiremaker.Add(edgemaker_2.Edge());
     }
 }
 
 if(!wiremaker.IsDone()){
     LoadMessage(tr("Wire Error"),tr("Error in creating edges"));
    
     return;
 }
 }
  if(!wiremaker.IsDone()){
    return;
  }
 
 if(!drawnWireShape){
   drawnWireShape=new CustomAIS_Shape(wiremaker.Wire());
   context->Display(drawnWireShape,true);
 }
 else{
  drawnWireShape->SetShape(wiremaker.Wire());
  CheckDisplayStatus(drawnWireShape,context->DisplayStatus(drawnWireShape));

 }
 //if the size of the array is less than the 3
if(bsplineDialog->GetPoints().size()<=3){
    LoadMessage(tr("BSpline Error "),tr("The number of points for bspline is less than 2"));
    return;
    
  }
  if(bsplineDialog->GetPoints().size()>Geom_BSplineCurve::MaxDegree()+1){
    LoadMessage(tr("BSpline Error"),tr("The number of points is greater than the max degree +1"));
    return;
  }
  NCollection_Array1<gp_Pnt> pointarray(bsplineDialog->GetPoints().front(),0,bsplineDialog->GetPoints().size()-1);
  
  GeomAPI_PointsToBSpline bsplinecurve;
  bsplinecurve.Init(pointarray);
  if(!bsplinecurve.IsDone()){
    LoadMessage(tr("BSpline Construction Error"),tr("Failed to construct BSpline"));
    return;
  }
  BRepBuilderAPI_MakeEdge edgemaker;
  edgemaker.Init(bsplinecurve.Curve());
  if(!edgemaker.IsDone()){
      return;
  }
  if(drawnBsplineShape.IsNull()){
    drawnBsplineShape=new BSplineAIS_Shape(edgemaker.Edge());
    drawnBsplineShape->SetCurve(bsplinecurve.Curve());
    context->Display(drawnBsplineShape,true);
    return;
  }
  drawnBsplineShape->SetShape(edgemaker.Edge());
  drawnBsplineShape->SetCurve(bsplinecurve.Curve());
  drawnBsplineShape->SetDir(view->Camera()->Direction());
   context->Redisplay(drawnBsplineShape,true);
  
  return;
}
void AlignWithDirection(){
  if(lineShape){
    lineShape->AlignWithDir(view->Camera()->Direction());
    return;
  }
  if(circShape){
    circShape->AlignWithDir(view->Camera()->Direction());
    return;
  }
  if(bshape){
    bshape->AlignMarkerWithDir(view->Camera()->Direction());
    return;
  }
  if(bsplineShape){
    bsplineShape->AlignMarkerWithDir(view->Camera()->Direction());
    return;
  }
  return;
}
void OnHandleArcEditDialogDone(){
  if(!arcShape){
    return;
  }
  arcShape->SetShape(editarcDialog->GetEdge());
  arcShape->SetCircle(editarcDialog->CircleCurve());
  arcShape->SetU1((double)editarcDialog->U1());
  arcShape->SetU2((double)editarcDialog->U2());
  context->Redisplay(arcShape,true);
  return;
}
void OnGatherWire(bool checked){
  if(checked){
    context->Deactivate(); 
    CurrentSelMode=3;
    context->Activate(3);
    wireselectors->UnSelectAll();   
  }
  else{
    context->Deactivate();
    context->Activate(0);
   CurrentSelMode=0;
   wireselectors->Nullify();
  }
 return;
}
void OnSelectWires(bool checked){
  if(checked){
    emit EmitGatherWire(checked);
  }
  else{
  emit EmitGatherWire(checked);
  }
  return;
}
//for ending the selection of wires 
void EndSelectWires(){
 st1=NULL_SELECT;
 gatherWire->setChecked(false);
 CurrentSelMode=0;
 context->Deactivate();
 context->Activate(0);
 wireselectors->Nullify();
return;
}
void DeleteWires(){
return;
}
void OnHandleGatheredEdges(bool value){
  if(value){
    context->Deactivate();
    context->Activate(2);
    CurrentSelMode=2;
    edgeselectors->UnSelectAll();
  }
  else{
    context->Deactivate();
    CurrentSelMode=0;
    context->Activate(0);
    edgeselectors->Nullify();
  }
  return;
}
void OnHandleGatheredFace(bool check){
  if(check){
    context->Deactivate();
    CurrentSelMode=4;
    context->Activate(0);
    faceselectors->UnSelectAll();
  }
  else{
    context->Deactivate();
    context->Activate(0);
    CurrentSelMode=0;
    faceselectors->Nullify();
  }
  return;
}
void OnHandleGatheredShape(bool check){
  if(check){
    
    context->Deactivate();
    context->Activate(0);
    CurrentSelMode=0;
    shapeselectors->UnSelectAll();
  }
  else{
    shapeselectors->Nullify();
  }
  return; 
}
void OnHandleConvertEdgeToWire(){
  if(selShape){
     ConvertEdgeToWire();
     if(!selWire.IsNull()){
       selShape->SetShape(selWire);
       context->Redisplay(selShape,true);
     }
  }
  else{
    if(selCurveShape){
      if(!selEdge.IsNull()){
          ConvertEdgeToWire();
          if(!selWire.IsNull()){
            Handle(CustomAIS_Shape) hshape=new CustomAIS_Shape(selWire);
            context->SetLocation(hshape,context->Location(selCurveShape));
            context->Display(hshape,true);
            curveShape=selCurveShape;
            OnDeleteObject();
          }
      }
    }
  }
  return;
}
void OnHandleStartForTransLineDialog(){
  transLineDialog->SetPoint(LineStartPoint);
  transLineDialog->exec();
  
  return;
}
void onHandleContinueForTransLineDialog(){
  //also known as editing
  transLineDialog->exec();
  return;
}
void OnHandleCopyLength(bool value){
  if(value){
    emit EmitFloatValue(transLineDialog->Length());
  }
  else{
   emit OnEmitFaceBool(value);
  }
  return;
}
void OnHandleCopyRadius(bool value){
  if(value){
    emit EmitFloatValue(transCircleDialog->Radius());
    return;
  }
  else{
   emit OnEmitFaceBool(value);
  }
  return;
}
/*
void OnHandleOriginAxis(bool value){
   if(value){
    EmitAxis(gp_Ax2(gp_Pnt(0.0,0.0,0.0),chosenDir));
 }
 else{
   emit OnEmitFaceBool(value);
 }
  return;
}*/
void OnHandleCopyAxis(bool value){
  if(value){
    emit EmitAxis(gp_Ax2(gp_Pnt(0.0,0.0,0.0),transLineDialog->ChangedDir())); 
  }
  else{
    emit OnEmitFaceBool(value);
  }
   return;
}
void OnHandleCopyCircleAxis(bool value){
  if(value){
    emit EmitAxis(transCircleDialog->ChangedAxis());
  }
  else{
    emit OnEmitFaceBool(value);
  }
  return;
}
void OnHandleNullifyShape(){
  transLineDialog->NullifyShape();
  return;
}
void OnHandleNullifyCircleShape(){
 transCircleDialog->NullifyShape();
return;
}
void OnHandleConvertPrimLine(bool value){
  if(value){
   emit EmitLineValue(transLineDialog->ChangedDir(),LineStartPoint,transLineDialog->Length());
  }
  else{
    emit OnEmitFaceBool(value);
  }
  return;
}

void OnHandleConvertPrimCircle(bool value){
 if(value){
     emit EmitCircleValue(transCircleDialog->ChangedAxis(),transCircleDialog->Radius());

 }
 else{
 emit OnEmitFaceBool(value);
 }

return;
}
void OnStartPrimLine(bool value){
  if(value){
    dc=DC_PRIMLINE;
  }
  else{
  dc=DC_NULL;
  }
return;
}
void OnEndPrimLine(){
  dc=DC_NULL;
  transLineDialog->EraseShape();
  primLine->setChecked(false);
  return;
}
void OnEndPrimCircle(){
dc=DC_NULL;
transCircleDialog->EraseShape();
primCircle->setChecked(false);
return;
}
void OnStartPrimCircle(bool value){
if(value){
  dc=DC_PRIMCIRCLE;
}
else{
 dc==DC_NULL;
}
return;
}

void OnHandlePrimCircle(){
  transCircleDialog->SetPoint(LineStartPoint);
  transCircleDialog->exec();
  return;
}
void OnContinuePrimCircle(){
transCircleDialog->exec();
  return;
}
void OnHandleTwoPointLine(bool value){
  if(value){
    dc=DC_TWOPNT;
  }
  else{
    dc=DC_NULL;
  }
  return;
}
void OnHandleFirstTwoPoint(bool value){
  if(value){
    LoadMessage(tr(""),tr("Select The First Point,\n Hint: You can select the point within any Selection mode"));
    tpoint=TP_FIRST;
    sLinePoint->setChecked(false);
  }
  else{
    tpoint=TP_NULL;
  }
  return;
}
void OnHandleFirstArcPoint(bool value){
  if(value){
    LoadMessage(tr(""),tr("Select The First Point,\n Hint: You can select the point within any Selection mode"));
    tpoint=TP_FIRST;
    arcSecondPoint->setChecked(false);
  }
  else{
    tpoint=TP_NULL;
  }
  return;
}
void OnHandleCircleFirstPoint(bool value){
  if(value){
    LoadMessage(tr(""),tr("Select The First Point,\n Hint: You can select the point within any Selection mode"));
    tpoint=TP_FIRST;
    circleSecondPoint->setChecked(false);
  }
  else{
    tpoint=TP_NULL;
  }
  return;
}
void OnHandleTransFirstPoint(bool value){
  if(value){
     LoadMessage(tr(""),tr("Select The First Point,\n Hint: You can select the point within any Selection mode\n And this selected point must be part of the selected object to get a reasonable result"));
    tpoint=TP_FIRST;
    transEndPoint->setChecked(false);
  }
  else{
    tpoint=TP_NULL;
  }
  return;
}
void OnHandleSecondTwoPoint(bool value){
  if(value){
    LoadMessage(tr(""),tr("Select The second Point,\n Hint: You can select the point within any Selection mode"));
    tpoint=TP_SECOND;
    fLinePoint->setChecked(false);
  }
  else{
    tpoint=TP_NULL;
  }
  return;
}
void OnHandleArcSecondPoint(bool value){
  if(value){
    LoadMessage(tr(""),tr("Select The second Point,\n Hint: You can select the point within any Selection mode"));
    tpoint=TP_SECOND;
    arcFirstPoint->setChecked(false);
  }
  else{
    tpoint=TP_NULL;
  }
  return;
}

void OnHandleTransSecondPoint(bool value){
  if(value){
     LoadMessage(tr(""),tr("Select The First Point,\n Hint: You can select the point within any Selection mode"));
    tpoint=TP_SECOND;
    transStartPoint->setChecked(false);
  }
  else{
    tpoint=TP_NULL;
  }
  return;
}
void OnHandleCircleSecondPoint(bool value){
  if(value){
     LoadMessage(tr(""),tr("Select The First Point,\n Hint: You can select the point within any Selection mode"));
    tpoint=TP_SECOND;
    circleFirstPoint->setChecked(false);
  }
  else{
    tpoint=TP_NULL;
  }
  return;
}
void SelectPoint(const gp_Pnt& pnt){
  switch(tpoint){
    case TP_FIRST:{
      twoPointArray[0]=pnt;
      break;
    }
    case TP_SECOND:{
      twoPointArray[1]=pnt;
      break;
    }
  }
  return;
}
void OnConvertTwoPointToPrimLine(bool value){
  if(value){
  gp_Vec disVec(twoPointArray[0],twoPointArray[1]);
  emit EmitLineValue(gp_Dir(disVec),twoPointArray[0],(double)disVec.Magnitude());
  }
  else{
  emit OnEmitFaceBool(value);
  }
 return;
}
void EndTwoPointLine(){
  dc=DC_NULL;
  LineAction->setChecked(false);
  return;
}

void OnBuildAction(){
  BRepBuilderAPI_MakeEdge edgemaker(twoPointArray[0],twoPointArray[1]);
  TopoDS_Edge edge;
  if(edgemaker.IsDone()){
   edge=edgemaker.Edge();
  }
  else{
    LoadMessage(tr(""),tr("Failed To Construct Line"));
    return;
  }
  Handle(CustomAIS_Shape) shape=new CustomAIS_Shape(edge);
  shape->SetZLayer(Graphic3d_ZLayerId_Topmost);
  UndoStack->push(new UndoCreationCommand(context,shape));
  context->Display(shape,true);
  return;
}
void OnHandleTwoPointAxis(bool value){
  if(value){
    gp_Vec disVec(twoPointArray[0],twoPointArray[1]);
    gp_Ax2 axis(gp_Pnt(0.0,0.0,0.0),gp_Dir(disVec));
     emit EmitAxis(axis); 
    return;
  }
  else{
     emit OnEmitFaceBool(value);
  }
  return;
}
void OnHandleTwoPointLength(bool value){
  if(value){
    gp_Vec disVec(twoPointArray[0],twoPointArray[1]);
     emit EmitFloatValue(disVec.Magnitude());
    return;
  }
  else{
     emit OnEmitFaceBool(value);
  }
  return;
}
void OnHandleViewLength(){
   gp_Vec disVec(twoPointArray[0],twoPointArray[1]);
   LoadMessage(tr("Length Info"),QString("Current Line's Length: ")+QString::number(disVec.Magnitude()));
  return;
}
void OnHandleViewAxis(){
  gp_Vec disVec(twoPointArray[0],twoPointArray[1]);
  gp_Dir dir(disVec);
  QString str=QString("X: ")+QString::number(dir.X())+QString("\n");
  QString str1=QString("Y: ")+QString::number(dir.Y())+QString("\n");
  QString str2=QString("Z: ")+QString::number(dir.Z())+QString("\n");
  LoadMessage(tr("Axis Info"),str+str1+str2);
  return;
}
//for the edges to be connected, they must be gemoetrically continued,To make sure that they are geometrically continued,we have to make them that way(geometrically continued) manually
//void OnHandleWireError(const BRepBuilderAPI_WireError& error,int& success){
void OnConvertSetEdgesToWire(){
   if(edgeselectors->Edges().empty()){
      LoadMessage(tr(""),tr("No Selected Edges"));
      return;
   }
   if(edgeselectors->Edges().size()==1){
    LoadMessage(tr(""),tr("There is only one selected edge"));
    return;
   }
   BRepBuilderAPI_MakeWire wiremaker;
   TopoDS_Wire wireobject;
   TopoDS_Edge currEdge;
   for(int i=0;i<edgeselectors->Edges().size();i++){
    currEdge=edgeselectors->Edges().at(i);
    if(currEdge.Orientation()==TopAbs_REVERSED){
      currEdge.Reverse();
    }
    wiremaker.Add(currEdge);
   }
   if(wiremaker.IsDone()){
     wireobject=wiremaker.Wire();
   }
   else{
    int success=0;
    OnHandleWireError(wiremaker.Error(),success);
    return;
}
 Handle(AIS_Shape) currShape=edgeselectors->edgeSelectors().at(0).GetSelectedShape();

 Handle(CustomAIS_Shape) wireObjectShape=new CustomAIS_Shape(wireobject);
 wireObjectShape->SetZLayer(Graphic3d_ZLayerId_Topmost);
  context->SetLocation(wireObjectShape,context->Location(currShape));
 
  
 if(context->IsDisplayed(wireObjectShape)){
   context->Redisplay(wireObjectShape,true);
 }
 else{
  context->Display(wireObjectShape,true);
 }
 edgeselectors->Nullify();
 return;
}
void OnHandleGroupSelectionForEdges(){
  dc=DC_NULL;
  selectEdges->setChecked(false);
  edgeselectors->Nullify();
  return;
}
void OnPositionGizmo(){
  if(isFixed==true){
    if(context->IsDisplayed(ObjectGizmo)){
      ObjectGizmo->SetPosition(gp_Ax2(gottenPos,gp_Dir()));
      context->Redisplay(ObjectGizmo,true);
    }
    else{
      if(context->DisplayStatus(ObjectGizmo)==PrsMgr_DisplayStatus_Erased){
        ObjectGizmo->SetPosition(gp_Ax2(gottenPos,gp_Dir()));
        context->Display(ObjectGizmo,true);
      }
    }
    return;
  }
   if(context->IsDisplayed(ObjectGizmo)){
    
    gp_Ax2 ax(LineStartPoint,gp_Dir());
    gottenPos=LineStartPoint;
     ObjectGizmo->SetPosition(ax);
     context->Redisplay(ObjectGizmo,true);
     return;
   }
   if(context->DisplayStatus(ObjectGizmo)==PrsMgr_DisplayStatus_Erased){
    gp_Ax2 ax(LineStartPoint,gp_Dir());
    gottenPos=LineStartPoint;
    ObjectGizmo->SetPosition(ax);
    context->Display(ObjectGizmo,true);
   }

   return;
}
void OnStartTransform(bool value){
  if(value){
  LoadMessage(tr(""),tr("Select the point within any selection mode\n NB: The point selected should be part of the object,and will be used as center of pivot for Transformation")); 
  dc=DC_TRANSFORM;
  }
  else{
    dc=DC_NULL;
  }
  return;
}
gp_Pnt ConvertToObjectSpace(const gp_Pnt& pnt){
  if(ChosenShape){
    gp_Trsf trsf=context->Location(ChosenShape).Transformation(); //get the world space transform
    if(trsf.Form()!=gp_Identity){
      gp_Pnt pnt_1=pnt.Transformed(trsf.Inverted());
      return pnt_1;
    }
    return pnt; //return the untransformed position
  }
  if(curveShape){
    gp_Trsf trsf=context->Location(curveShape).Transformation(); //get the world space transform
    if(trsf.Form()!=gp_Identity){
      gp_Pnt pnt_1=pnt.Transformed(trsf.Inverted());
      return pnt_1;
    }
    return pnt;
  }
  return pnt;
}
//this should be used after AIS_Manipulator has transformed the object about the pivot position
void OnHandleApplyTransform(){
  if(ChosenShape){
    gp_Trsf trsf=context->Location(ChosenShape).Transformation();
    TopoDS_Shape sh=ChosenShape->Shape();
    BRepBuilderAPI_Transform trans(sh,trsf);
    if(trans.IsDone()){
      ChosenShape->SetShape(trans.Shape());
      context->SetLocation(ChosenShape,TopLoc_Location(gp_Trsf()));
      context->Redisplay(ChosenShape,true);
    }
    else{
      LoadMessage(tr("Transformation Error"),tr("Transformation Failed"));
    }
  }
  else{
    if(curveShape){
    gp_Trsf trsf=context->Location(curveShape).Transformation();
    TopoDS_Shape sh=curveShape->Shape();
    BRepBuilderAPI_Transform trans(sh,trsf);
    if(trans.IsDone()){
      curveShape->SetShape(trans.Shape());
      context->SetLocation(curveShape,TopLoc_Location(gp_Trsf()));
      context->Redisplay(curveShape,true);
    }
    else{
      LoadMessage(tr("Transformation Error"),tr("Transformation Failed"));
    }
    }
  }
  return;
}
void SetFixedState(bool value){
  if(value){
    isFixed=value;
  }
  else{
    isFixed=value;
  }
  return;
}
void OnHandleEndTransform(){
  dc=DC_NULL;
  TransformAction->setChecked(false);
  if(ChosenShape){
    ChosenShape.Nullify();
  }
  if(curveShape){
    curveShape.Nullify();
  }
  return;
}
//onMousepress,OnMouseMove and OnMouseRelease
//per frame of draw
//this updates both the object position and orientation
void OnUpdateGizmoPosition(const gp_Trsf& trsf){
  
  gp_Pnt worldPivot=GizmoStartPosition.Transformed(trsf);
  gp_Dir xDir=gp_Dir(1.0,0.0,0.0);
  gp_Dir zDir=gp_Dir(0.0,0.0,1.0);
  xDir=xDir.Transformed(trsf);
  zDir=zDir.Transformed(trsf);
  gp_Ax2 ax(worldPivot,zDir,xDir);
  ObjectGizmo->SetPosition(ax);
  context->Redisplay(ObjectGizmo,true);
  return;
}
void DisplayAtPivot(){
  if(!ObjectGizmo){
    return;
  }
  if(context->IsDisplayed(ObjectGizmo)){
    ObjectGizmo->SetPosition(gp_Ax2(gottenPos,gp_Dir()));
    context->Redisplay(ObjectGizmo,true);
  }
  else{
    if(context->DisplayStatus(ObjectGizmo)==PrsMgr_DisplayStatus_Erased){
      ObjectGizmo->SetPosition(gp_Ax2(gottenPos,gp_Dir()));
      context->Display(ObjectGizmo,true);
    }
  }
   return;
}
//update both the object position and orientation
void OnUpdateObjectPosition(){
  
  gp_Trsf delta=ObjectGizmo->Transformation(); //stores it's transformation 
  gp_Trsf newTransform=delta* objectTrans;
  if(ChosenShape){
   context->SetLocation(ObjectGizmo->Object(),TopLoc_Location(newTransform));
   context->Redisplay(ObjectGizmo->Object(),true);
   OnUpdateGizmoPosition(newTransform);
  }
  else{
    if(curveShape){
      context->SetLocation(ObjectGizmo->Object(),TopLoc_Location(newTransform));
      context->Redisplay(ObjectGizmo->Object(),true);
      OnUpdateGizmoPosition(newTransform);
    }
    return;
  }
   
  return;
}
gp_Trsf GetObjectTransform(){
  if(ChosenShape){
    return context->Location(ChosenShape).Transformation();
  }
  else{
    if(curveShape){
      return context->Location(curveShape).Transformation();
    }
  }
  return gp_Trsf();
}
void RedisplayGizmo(){
  if(context->IsDisplayed(ObjectGizmo)){
      context->Redisplay(ObjectGizmo,true);
    }
    else{
      if(context->DisplayStatus(ObjectGizmo)==PrsMgr_DisplayStatus_Erased){
        context->Display(ObjectGizmo,true);
      }
    }
  return;
}
void OnHandleDefaultDepth(bool value){
  if(value){
    if(ChosenShape){
      topAction->setChecked(false);
    topMostAction->setChecked(false);
    
      SetDepthInfo(ChosenShape,Graphic3d_ZLayerId_Default);
    }
    else{
      if(!curveShape){
        return;
      }
    topAction->setChecked(false);
    topMostAction->setChecked(false);
      SetDepthInfo(curveShape,Graphic3d_ZLayerId_Default);
    }
  }
  else{
    return;
  }
  return;
}
void OnHandleTopDepth(bool value){
  if(value){
    if(ChosenShape){
     
    topMostAction->setChecked(false);
    defaultAction->setChecked(false);
      SetDepthInfo(ChosenShape,Graphic3d_ZLayerId_Top);
    }
    else{
      if(!curveShape){
        return;
      }
       topMostAction->setChecked(false);
    defaultAction->setChecked(false);
      SetDepthInfo(curveShape,Graphic3d_ZLayerId_Top);
    }
  }
  else{
    return;
  }
  return;
}

void OnHandleTopMostDepth(bool value){
  if(value){
    if(ChosenShape){
      
    topMostAction->setChecked(false);
    defaultAction->setChecked(false);
      SetDepthInfo(ChosenShape,Graphic3d_ZLayerId_Topmost);
    }
    else{
      if(!curveShape){
        return;
      }
      topMostAction->setChecked(false);
    defaultAction->setChecked(false);
      SetDepthInfo(ChosenShape,Graphic3d_ZLayerId_Topmost);
      
    }
  }
  else{
    return;
  }
  return;
}

void SetDepthInfo(Handle(AIS_Shape) shape,const Graphic3d_ZLayerId& zlayer){
   shape->SetZLayer(zlayer);
   view->Redraw();
  return;
}
void GetDepthInfo(Handle(AIS_Shape) shape){
  switch(shape->ZLayer()){
   case Graphic3d_ZLayerId_Top:{
    topAction->setChecked(true);
    topMostAction->setChecked(false);
    defaultAction->setChecked(false);
    break;
   }
   case Graphic3d_ZLayerId_Topmost:{
    topAction->setChecked(false);
    topMostAction->setChecked(true);
    defaultAction->setChecked(false);
    break;
   }
   case Graphic3d_ZLayerId_Default:{
    topAction->setChecked(false);
    topMostAction->setChecked(false);
    defaultAction->setChecked(true);
    break;
   }
   default:
    break;
  }
  view->Redraw();
  return;
}
void OnHandleTransFixed(bool value){
  if(value){
    isTransFixed=value;
  }
  else{
    isTransFixed=value;
  }
  return;
}
void SetTransShape(Handle(AIS_Shape) shape){
  if(isTransFixed){
    return;
  }
  myTransShape=shape;
  return;
}
void ComputeTransformForHandle(bool value=false){
  if(!myTransShape){
   LoadMessage(tr(""),tr("No Shape is Selected"));
   return;
  }
  gp_Vec vec(twoPointArray[0],twoPointArray[1]);
  gp_Trsf trsf=context->Location(myTransShape).Transformation();
  trsf.SetTranslationPart(vec);
  context->SetLocation(myTransShape,TopLoc_Location(trsf));
  view->Redraw();
  return;
}
void ApplyTransToTopoDS_Shape(){
  if(!myTransShape){
    LoadMessage(tr(""),tr("Cannot Apply Transform because the selected object is empty"));
    return;
  }
   gp_Trsf trsf=context->Location(myTransShape).Transformation();
   BRepBuilderAPI_Transform trans(myTransShape->Shape(),trsf);
   if(trans.IsDone()){
    myTransShape->SetShape(trans.Shape());
    myTransShape->SetZLayer(Graphic3d_ZLayerId_Topmost);
    context->SetLocation(myTransShape,TopLoc_Location(gp_Trsf()));
    UndoStack->push(new UndoCreationCommand(context,myTransShape));
    context->Redisplay(myTransShape,true);
   }
  
  return;
}
void OnEndTransShape(){
  myTransShape=nullptr;
  dc=DC_NULL;
  transAction->setChecked(false);
  return;
}
void OnStartTransShape(bool value){
  if(value){
  dc=DC_APPLYTRANS;
  }
  else{
    dc=DC_NULL;
  }
  return;
}
//DC_TWOPNTARC
//DC_TWOPNTCIRCLE
void OnHandleTwoPntArc(bool value){
  if(value){
    dc=DC_TWOPNTARC;
  }
  else{
    dc=DC_NULL;
  }
  return;
}
void OnHandleTwoPointCircle(bool value){
  if(value){
    dc=DC_TWOPNTCIRCLE;
  }
  else{
    dc=DC_NULL;
  }
  return;
}
double GetAngleFromPoint(const gp_Pnt& pnt){
  double ratio=pnt.Y()/pnt.X();
  return atan(ratio); //by default atan() gives the angle in radians
}
gp_Pnt GetLineMidPoint(const gp_Pnt& pnt1,const gp_Pnt& pnt2){
  double mid_x=(pnt1.X()+pnt2.X())/2.0;
  double mid_y=(pnt1.Y()+pnt2.Y())/2.0;
  double mid_z=(pnt1.Z()+pnt2.Z())/2.0;
  return gp_Pnt(mid_x,mid_y,mid_z);
}
void OnHandleBuildArc(){
   gp_Vec disVec(twoPointArray[0],twoPointArray[1]);
   double diameter=disVec.Magnitude();
   double radius=diameter/2.0;
   float pie=3.14159265;
   gp_Pnt midPoint=GetLineMidPoint(twoPointArray[0],twoPointArray[1]);
   Handle(Geom_Circle) circle=new Geom_Circle(gp_Ax2(midPoint,gottenDir),radius);
   if(!circle){
    return;
   }
   try{
   GC_MakeArcOfCircle arcmaker(circle->Circ(),twoPointArray[0],twoPointArray[1],true);
   if(!arcmaker.Value()){
    return;
   }
  BRepBuilderAPI_MakeEdge edgeMaker;
  edgeMaker.Init(arcmaker.Value());
  if(!edgeMaker.IsDone()){
    return;
  }
  Handle(CustomAIS_Shape) arcshape=new CustomAIS_Shape(edgeMaker.Edge());
  if(!arcshape){
    return;
  }
  arcshape->SetZLayer(Graphic3d_ZLayerId_Topmost);
  UndoStack->push(new UndoCreationCommand(context,arcshape));
  context->Display(arcshape,true);
}
catch(Standard_ConstructionError error){
  LoadMessage(tr(""),tr("Failed to construct two point arc"));
  return;
}
   return;
}

void OnHandleBuildCircle(){
  gp_Vec disVec(twoPointArray[0],twoPointArray[1]);
   double diameter=disVec.Magnitude();
   double radius=diameter/2.0;
   gp_Pnt midPoint=GetLineMidPoint(twoPointArray[0],twoPointArray[1]);
   Handle(Geom_Circle) circle=new Geom_Circle(gp_Ax2(midPoint,gottenDir),radius);

   if(!circle){
    return;
   }
   BRepBuilderAPI_MakeEdge edgeMaker;
   edgeMaker.Init(circle);
   if(!edgeMaker.IsDone()){
    return;
   }
   Handle(CustomAIS_Shape) cshape=new CustomAIS_Shape(edgeMaker.Edge());
   if(!cshape){
    return;
   }
   cshape->SetZLayer(Graphic3d_ZLayerId_Topmost);
   UndoStack->push(new UndoCreationCommand(context,cshape));
   context->Display(cshape,true);
  return;
}
void OnEndBuildCircle(){
  dc=DC_NULL;
  circleFirstPoint->setChecked(false);
  circleSecondPoint->setChecked(false);
  twoPntCircleAction->setChecked(false);
  return;
}
void OnHandleEndBuildArc(){
  dc=DC_NULL;
  twoPntArcAction->setChecked(false);
  arcFirstPoint->setChecked(false);
  arcSecondPoint->setChecked(false);
  return; 
}
void OnHandleConvertToPrimCircle(bool value){
  if(value){
    gp_Vec disVec(twoPointArray[0],twoPointArray[1]);
    double diameter=disVec.Magnitude();
    double radius=diameter/2.0;
     gp_Pnt midPoint=GetLineMidPoint(twoPointArray[0],twoPointArray[1]);
     emit EmitCircleValue(gp_Ax2(midPoint,gp_Dir()),radius);

 }
 else{
 emit OnEmitFaceBool(value);
 }
 return;
}
void OnStartChooseAxis(bool value){
  if(value){
    cm=CE_CHAXIS;
  }
  else{
    cm=CE_NULL;
  }
  return;
}
void OnHandleSelectedFace(bool value){
  if(value){
   prevMode=CurrentSelMode;
   context->Deactivate();
   context->Activate(4);
   CurrentSelMode=4;

  }
  else{
  CurrentSelMode=prevMode;
  context->Deactivate();
   context->Activate(prevMode);
  }
  return;
}
void SetFaceFixed(const TopoDS_Face& face){
  if(isFaceFixed==true){
    return;
  }
  ChosenAxisFace=face;
  return;
}


void OnHandleSetFixedFace(bool value){
  if(value){
    isFaceFixed=value;
  }
  else{
    isFaceFixed=value;
  }
  return;
}
void OnChooseDefaultX(bool value){
   if(value){
    gottenDir=gp_Dir(1.0,0.0,0.0);
    defaultY->setChecked(false);
    defaultZ->setChecked(false);
   }
   else{
    return;
   }
   return;
}
void OnChooseDefaultY(bool value){
   if(value){
    gottenDir=gp_Dir(0.0,1.0,0.0);
    defaultX->setChecked(false);
    defaultZ->setChecked(false);
   }
   else{
    return;
   }
   return;
}
void OnChooseDefaultZ(bool value){
   if(value){
    gottenDir=gp_Dir(0.0,0.0,1.0);
    defaultX->setChecked(false);
    defaultY->setChecked(false);
   }
   else{
    return;
   }
   return;
}
void OnComputeSurfaceNormal(){
  if(ChosenAxisFace.IsNull()){
    return;
  }
  gottenDir=SURFACE::GetFaceNormal(ChosenAxisFace,selFacePoint);

  return;
}
//endChooseAxis
void EndChooseAxis(){
 cm=CE_NULL;
 chooseFace->setChecked(false);
 defaultX->setChecked(false);
 chooseAxis->setChecked(false);
 defaultY->setChecked(false);
 defaultZ->setChecked(false);
  return;
}
void EndEdgeMenu(){
  st1=NULL_SELECT;
  edgeMenu->filletAction->setChecked(false);
  edgeMenu->convertToWireAction->setChecked(false);
  edgeMenu->convertAction->setChecked(false);
  edgeMenu->convertToFaceAction->setChecked(false);
  edgeMenu->trimAction->setChecked(false);
  edgeMenu->convertToPointNode->setChecked(false);
  dc=DC_NULL;
  cm=CE_NULL;
  return;
}
void EndFaceMenu(){
  st1=NULL_SELECT;
  faceMenu->convertAction->setChecked(false);
  faceMenu->applyFillet->setChecked(false);
  faceMenu->applyChamfer->setChecked(false);
  faceMenu->convertToPointNode->setChecked(false);
  dc=DC_NULL;
  cm=CE_NULL;
  return;
}
void EndWireMenu(){
  st1=NULL_SELECT;
  wireMenu->convertToNode->setChecked(false);
  wireMenu->applyFillet->setChecked(false);
  wireMenu->applyFilletToAll->setChecked(false);
  wireMenu->chooseVertex->setChecked(false);
  wireMenu->convertToPointNode->setChecked(false);
  dc=DC_NULL;
  cm=CE_NULL;
  return;
}

void OnConvertToEdgeColl(bool value){
  if(value){
  if(selWire.isNull()){
   LoadMessage(tr(""),tr("No wire is selected"));
   return;
  }
  int i=0;
  TopExp_Explorer explorer(selWire,TopAbs_EDGE);
  for(;explorer.More();explorer.Next()){
    TopoDS_Edge edge=TopoDS::Edge(explorer.Current());
    if(edge.IsNull()){
      continue;
    }
    ++i;
    DetermineEdgeType(edge);
  }
  if(i<=1){
    LoadMessage(tr(""),tr("The Wire only contains one edge"));
    return;
  }
  
  emit EmitEdgeColl();
}
else{
  emit OnEmitFaceBool(value);
}
  return;
}
void DetermineEdgeType(const TopoDS_Edge& edge){
  BRepAdaptor_Curve adaptorcurve(edge);
  switch(adaptorcurve.GetType()){
    case GeomAbs_Line:{
      
      cout<<"This is a line"<<"\n";
      break;
    }
    case GeomAbs_Circle:{
      
      cout<<"This is either an arc or a circle"<<"\n";
      break;
    }
  }
  return;
}
};






#endif