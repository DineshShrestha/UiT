#ifndef KNOTVECTOR_H
#define KNOTVECTOR_H
#include <vector>
#include <core/containers/gmdvector.h>
#include "firstsubcurve.h"
#include"firstcurve.h"
#include <memory>

template <typename T>
class knotVector: public GMlib::DVector<T>{
public:
    knotVector(std::shared_ptr<firstCurve<T>> firstCurve,int number_of_local_curves);
   //knotVector( std::shared_ptr<GMlib::PCurve<T,3>> firstcurve, int number_of_local_curves );
     //void                            generateKnotVector( PCurve<T,3>* g, int n );
    int getSize();
    T getParam(int i);
    float step;
private:
     float startP;
     float endP;

    std::shared_ptr<firstCurve<T>> _firstCurve;
    GMlib::DVector<T> _knotVec;
    std::shared_ptr<GMlib::PCurve<T,3>>_curve;
    //std::vector<std::shared_ptr<firstSubCurve<T>>> _currentSubCurve;
    T _endParam;
    float _center;


};


#include "knotvector.c"
#endif // KNOTVECTOR_H
