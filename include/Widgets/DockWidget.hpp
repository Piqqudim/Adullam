#ifndef DOCKWIDGET_HPP
#define DOCKWIDGET_HPP
#include<QtWidgets/QDockWidget>
#include<QtWidgets/QWidget>
#include<QtWidgets/QTextEdit>
#include"TitleBarWidget.hpp"
#include<CollaneWidget.hxx>
#include<QtWidgets/QCheckBox>
#include<QtWidgets/QScrollArea>
#include<QtWidgets/QRadioButton>
#include<QtWidgets/QStackedWidget>
#include<TabWidget.hpp>
#include<TreeWidget.hpp>
#include<Section.h>
#include<memory>
using namespace std;
//This is a DockWidget that will be inserted into the MainWindow...
class DockWidget:public QDockWidget{
private:
Q_OBJECT
std::unique_ptr<QStackedWidget> stack_widget;
std::unique_ptr<TabWidget> tabwidget;
QScrollArea* scrollarea=nullptr;

bool ContainsSplittedWidget=false;

size_t WidgetCount=0;
public:
DockWidget(QWidget* parent_widget,const QString& WidgetTitle);
void SetWidget(QWidget* widget){
    if(!scrollarea){
        return;
    }
    stack_widget->setCurrentWidget(scrollarea);
    scrollarea->setWidget(widget);
    return;
}
QWidget* GetScrolledWidget() const{
    return scrollarea->widget();
}
void SetTitle(const QString& val){
    setWindowTitle(val);
    return;
}
void RemoveWidget(){
    if(scrollarea){
        scrollarea->takeWidget();
        return;
    }
    return;
}

TabWidget* GetTabWidget() const{
    return tabwidget.get();
}
void AddTab(const QString& title,QWidget* widget){
   if(!widget){
    return;
   }
   if(stack_widget->currentWidget()!=tabwidget.get()){
     stack_widget->setCurrentWidget(tabwidget.get());
   }
   //we have to check if the widget has been added before so that we won't have duplicate
   if(tabwidget->indexOf(widget)==-1){
   tabwidget->addTab(widget,title);
   tabwidget->setCurrentWidget(widget);
   }
   else{
    tabwidget->setCurrentWidget(widget);
   }
   
   return;
}
~DockWidget(){
   
    if(scrollarea){
        delete scrollarea;
        scrollarea=nullptr;
    }
    
}

signals:
void OnChangeTitleBarWidget(QWidget* widget);
public slots:
void OnSetCurrentTitleBarWidget(QWidget* widget){
    return;
}


};






#endif