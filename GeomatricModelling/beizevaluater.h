#ifndef BEIZEVALUATER_H
#define BEIZEVALUATER_H
#include<gmParametricsModule>
#include"knotvector.h"
template <typename T>
class BeizEvaluater:  public GMlib::DMatrix<T>
{
public:
     BeizEvaluater();
     void BeizerEvaluater(GMlib::DMatrix<T> &B, int d, T scale, T tp);
     void BSplineEvaluater(GMlib::DMatrix<T>&B, const std::shared_ptr<knotVector<T>> knotVector, int d, T tp);//matrix of original curve,degree,scale,center point
     std::shared_ptr<knotVector<T>> _knotVector;



private:

//     DVector<T>      _t;

    void            eval( T t, int d = 0, bool l = false );
//     T               getEndP();
//     T               getStartP();

     T               W(T tp, int d, int i);
     T               Wder(T tp, int d, int i);//w derivative with center degree and index
     T               delta(T scale, int d, int i);
    // void            makeMat(DMatrix<T>& mat, int i, int d, T t, T scale);
     int             findIndex(T tp, int i);



};
#include"beizevaluater.c"
#endif // BEIZEVALUATER_H
