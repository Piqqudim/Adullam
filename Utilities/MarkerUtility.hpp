#pragma once
#include<AIS_InteractiveContext.hxx>
#include<AIS_Point.hxx>
#include<TopoDS_Edge.hxx>
#include<Geom_CartesianPoint.hxx>
#include<EdgeUtility.hpp>
#include<vector>
using namespace std;
using namespace EDGE;
enum MARKERDISPLAYTYPE{
 MDT_NULL,
 MDT_ENDPOINT,
 MDT_MIDPOINT,
 MDT_SPECIAL
};


class Marker{
public:
virtual void Display(){
    return;
}
virtual void UnDisplay(){
    return;
}
};

class EdgeMarker:public Marker{
private:
std::vector<Handle(AIS_Point)> pointmarkers;
MARKERDISPLAYTYPE mdt=MDT_NULL;
TopoDS_Edge Edge;
Handle(AIS_InteractiveContext) context;
public:
EdgeMarker(){
    return;
}
void SetContext(Handle(AIS_InteractiveContext) con){
    context=con;
    return;
}
Handle(AIS_InteractiveContext) Context() const{
   return context;
}
void SetEdge(const TopoDS_Edge& ed){
    Edge=ed;
    return;
}
TopoDS_Edge MarkerEdge() const{
    return Edge;
}
void SetDisplayMarkerType(const MARKERDISPLAYTYPE& va){
    mdt=va;
    return;
}
 MARKERDISPLAYTYPE Type() const{
    return mdt;
 }

//Display Function displays all the marker on the Edge
void Display() override{
    switch(mdt){
        case MDT_MIDPOINT:{
            gp_Pnt pnt=GetEdgeMidPoint(Edge);
            if(!pointmarkers.empty()){
                for(auto marker:pointmarkers){
                    context->Remove(marker,false);
                }
                pointmarkers.clear();
            }
            Handle(AIS_Point) pointmarker=new AIS_Point(new Geom_CartesianPoint(pnt));
            pointmarker->SetMarker(Aspect_TOM_RING1);
            context->Activate(pointmarker,0); 
            
            pointmarkers.push_back(pointmarker);
            context->Display(pointmarker,true);
            break;
        }
    }
     
    return;
}
//unDisplay Function removes all the displayed marker
void UnDisplay() override{
   if(!pointmarkers.empty()){
      for(auto marker:pointmarkers){
        context->Remove(marker,false);
    }
    pointmarkers.clear();
    context->UpdateCurrentViewer();
}
   return;
}
};