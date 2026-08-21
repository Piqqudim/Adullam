#pragma once
#include<V3d_View.hxx>
#include<InfoUtility.hpp>
#include<QContextMenuEvent>
#include<QtGui/QPainter>
#include<AIS_InteractiveContext.hxx>
#include<MyCustomAIS_Shape.hxx>
#include<Graphic3d_GraphicDriver.hxx>
#include<OpenGl_GraphicDriver.hxx>
#include<Aspect_DisplayConnection.hxx>
#include<QMouseEvent>
#include<QResizeEvent>
#include<unordered_map>
#include<ViewCube.hpp>
#include<WNT_Window.hxx>
#include<memory>
#include<QAction>
#include<EventManager.hpp>
#include<Graphic3d_Vec2.hxx>
#include<Aspect_VKey.hxx>
#include<QtCore/Qt>
#include<QMenu>
using namespace std;
class InspectorWidget:public QWidget{
private:
Q_OBJECT
Handle(Aspect_DisplayConnection) display;
Handle(OpenGl_GraphicDriver) graphicDriver;
Handle(V3d_View) view;
Handle(V3d_Viewer) Viewer;
Handle(AIS_InteractiveContext) context;
Handle(WNT_Window) Window;
Handle(ViewCube) viewcube;
Handle(CustomAIS_Shape) chosenShape;
EventManager evt_manager; 
unique_ptr<QAction> deleteAction;
unique_ptr<QMenu> widgetMenu;
const double dpr=devicePixelRatioF();


public:
InspectorWidget(QWidget* widget):QWidget(widget){
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_NoSystemBackground);
    setAutoFillBackground(false);
    setAttribute(Qt::WA_NativeWindow);
    setFocusPolicy(Qt::StrongFocus);
    setBackgroundRole(QPalette::NoRole);
    setMouseTracking(true);
    display=new Aspect_DisplayConnection();
    graphicDriver=new OpenGl_GraphicDriver(display);
    Viewer=new V3d_Viewer(graphicDriver);
    context=new AIS_InteractiveContext(Viewer);
    viewcube=new ViewCube();
    view=Viewer->CreateView();
    WId winid=winId();
    Window=new WNT_Window((Aspect_Handle)winid);
    Viewer->SetLightOn();
    Viewer->SetDefaultLights();
    view->SetWindow(Window);
    Window->Map();
    view->SetBackgroundColor(Quantity_Color(0.18,0.18,0.18,Quantity_TOC_RGB));
    view->MustBeResized();
    view->TriedronDisplay(Aspect_TOTP_RIGHT_UPPER,Quantity_NOC_SNOW,0.1,V3d_ZBUFFER);
    widgetMenu=make_unique<QMenu>();
    deleteAction=make_unique<QAction>(tr("Clear All"));
    widgetMenu->addAction(deleteAction.get());
    context->Activate(viewcube,0);
    context->Display(viewcube,true);
    connect(deleteAction.get(),&QAction::triggered,this,&InspectorWidget::ClearAll);
}
/*
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
      return Aspect_VKeyMouse_NONE; 
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
    return Aspect_VKeyFlags_NONE;
}





*/
protected:
QPaintEngine* paintEngine() const override{
    return nullptr;
}
void contextMenuEvent(QContextMenuEvent* event) override{
    QWidget::contextMenuEvent(event);
    widgetMenu->exec(event->globalPos());
    return;
}
void mousePressEvent(QMouseEvent* event) override{
    QWidget::mousePressEvent(event);
    /*if(evt_manager.UpdateMouseButtons(Graphic3d_Vec2i(static_cast<int>(std::lround(event->pos().x()*dpr)),static_cast<int>(std::lround(event->pos().y()*dpr))),ToQtMouseButton(event->button()),ToNativeModifiers(Qt::NoModifier),false)){
     
    }*/
    return;
}
void mouseMoveEvent(QMouseEvent* event) override{
    QWidget::mouseMoveEvent(event);
    return;
}


void mouseReleaseEvent(QMouseEvent* event) override{
    QWidget::mouseReleaseEvent(event);
    return;
}
void resizeEvent(QResizeEvent* event) override{
    QWidget::resizeEvent(event);
    if(view){
        view->MustBeResized();
    }
    return;
}
signals:

public slots:
void OnDisplayShape(const Handle(CustomAIS_Shape)& shape){
    Handle(CustomAIS_Shape) inputShape=shape;
    if(inputShape){
        context->Display(inputShape,false);
        view->Redraw();
    }
   return;
}
void ClearAll(){
    context->RemoveAll(false);
    context->Display(viewcube,false);
     view->Redraw();
    return;
}

};