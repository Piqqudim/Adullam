#pragma once
#include<QtCore/QString>
#include<QtWidgets/QTextEdit> 
#include<memory>
#include<QtGui/QAction>
using namespace std;

class LoggerWidget:public QTextEdit{
private:
Q_OBJECT
std::unique_ptr<QAction> clearAction;

public:
LoggerWidget(QWidget* widget=nullptr):QTextEdit(widget){
    setReadOnly(true);
    setLineWrapMode(QTextEdit::NoWrap);
    clearAction=std::make_unique<QAction>(tr("Clear"));
    saveLogAction=std::make_unique<QAction>(tr("Save Log"));
    createStandardContextMenu()->addAction(clearAction.get());
    
    connect(clearAction.get(),&QAction::triggered,this,&LoggerWidget::Clear);
  return;
}
void AppendLog(const QString& text){
    QTextCursor cursor=textCursor();
    cursor.movePosition(QTextCursor::End);
    setTextCursor(cursor);
    ensureCursorVisible();
    append(text);
    return;
}
void AppendWarning(const QString& text){
    setTextColor(QColor(Qt::red));
    AppendLog(text);
  return;
}
void AppendInfo(const QString& info){
    setTextCursor(QColor(Qt::gray));
    AppendLog(text);
    return;
}
signals:

public slots:
 void Clear(){
    clear();
    return;
 }

};


