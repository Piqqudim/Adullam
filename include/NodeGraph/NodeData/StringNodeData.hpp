//Check difference between Qt's String and c++ std::string
#ifndef STRING_NODE_DATA_HPP
#define STRING_NODE_DATA_HPP
#include<NodeData>
#include<QtCore/QString>
using namespace QtNodes;
class StringNodeData:public NodeData{
private:
QString m_Data;
QString m_Name;


public:
StringNodeData(const QString& name=QString()){
    m_Name=name;
    return;
}
StringNodeData(const QString& data,const QString& name):m_Data{data},m_Name{name}{

}
QString Data() const{
    return m_Data;
}
void SetData(const QString& data){
    m_Data=data;
    return;
}
NodeDataType type() const override{
    return {"String",m_Name};
}
};












#endif