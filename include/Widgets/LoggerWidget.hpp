#pragma once
#include<QtCore/QString>
#include<QtWidgets/QTextEdit> 
#include<memory>
#include<QtGui/QAction>
#include<QtWidgets/QMenu>

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
    setTextColor(QColor(Qt::gray));
    AppendLog(info);
    return;
}
signals:

public slots:
 void Clear(){
    clear();
    return;
 }

};


