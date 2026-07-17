#pragma once 
enum CURVE_TYPE{
    CT_LINE,
    CT_CIRCLE,
    CT_ARC,
    CT_SPLINE,
    CT_BEZIER,
    CT_NULL
};
class CurveParam{
    private:
    CURVE_TYPE curvetype;
     
    public:
CurveParam(){
    return;
}
virtual  void SetCurveType(const CURVE_TYPE& ctype){
    curvetype=ctype;
    return;
}
CURVE_TYPE curveType() const{
    return curvetype;
}
};