#ifndef BEIZERCURVES_H
#define BEIZERCURVES_H
#include"beizevaluater.h"
#include<gmParametricsModule>

template<typename T>
class BeizerCurves: public GMlib::PCurve<T,3>
{
    GM_SCENEOBJECT(BeizerCurves)
    protected:
        void            eval(T t, int d, bool l);
    public:
        BeizerCurves(std::shared_ptr<GMlib::PCurve<T,3>>originalCurve, T startP, T center, T endP, int degree);
      GMlib::DVector<GMlib::Vector<T,3>>& getcontrolP(){return _controlPoint;}
    T               getEndP();
    T               getStartP();

    T               _dScale;//derivative scaling
    T               _cScale;//center scaling
    T               _startP;
    T               _endP;
    T               _center;
  int               _degree;
  void              localSimulate(double dt);

    GMlib::DMatrix<T> _MatrixEval;
    BeizEvaluater<float> _beizEval;
    GMlib::DVector<GMlib::Vector<T,3>> _controlPoint;
};

#include"beizercurves.c"

#endif // BEIZERCURVES_H
