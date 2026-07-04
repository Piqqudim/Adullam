#pragma once 
#include<CurveAIS_Shape.hpp>
#include<Geom_Circle.hxx>

class ArcAIS_Shape:public CurveAIS_Shape{
private:
double u1=0.0;
double u2=0.0;
Handle(Geom_Circle) circle;


public:
ArcAIS_Shape(const TopoDS_Shape& sh):CurveAIS_Shape(sh){
    return;
}
void SetCircle(const Handle(Geom_Circle) circ){
    circle=circ;
    return;
}
void SetU1(const double& u){
    u1=u;
    return;
}
void SetU2(const double& u){
    u2=u;
    return;
}
double U1() const{
    return u1;
}
double U2() const{
    return u2;
}
Handle(Geom_Circle) Circle() const{
    return circle;
}

};