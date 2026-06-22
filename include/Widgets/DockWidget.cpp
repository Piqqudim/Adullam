
#include<DockWidget.hpp>

DockWidget::DockWidget(QWidget* parent_widget,const QString& WidgetTitle):QDockWidget(WidgetTitle,parent_widget){
    
    setMinimumSize(100,100);
    setFeatures(features());
    stack_widget=std::make_unique<QStackedWidget>(this);
    scrollarea=new QScrollArea(nullptr);
    scrollarea->setWidgetResizable(true);
    scrollarea->setVisible(true);
    stack_widget->addWidget(scrollarea);
    tabwidget=std::make_unique<TabWidget>(nullptr);
    stack_widget->addWidget(tabwidget.get());
    stack_widget->setCurrentWidget(scrollarea);
    setWidget(stack_widget.get());
    
} 
