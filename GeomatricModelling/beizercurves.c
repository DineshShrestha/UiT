#include"beizercurves.h"
template <typename T>
BeizerCurves<T>::BeizerCurves(std::shared_ptr<GMlib::PCurve<T,3>>originalCurve, T startP, T center, T endP, int degree ) {


    _startP= startP;
    _endP= endP;
    _center = center;
    _degree =degree;
    GMlib::DVector<GMlib::Vector<T,3>>evaluateCurve= originalCurve->evaluateParent(_center, _degree);


    _cScale = (_center -_startP)/(_endP-_startP);
    _dScale = 1/(_endP-_startP);
      _beizEval.BeizerEvaluater(_MatrixEval, evaluateCurve.getDim()-1,1/_dScale, _cScale);
   _MatrixEval.invert();
   _controlPoint= _MatrixEval * evaluateCurve;   
 for(int i=0;i<=evaluateCurve.getDim()-1;i++)
      {  _controlPoint[i] -= evaluateCurve(0);

    }
this->translateParent(evaluateCurve(0));
}
template <typename T>
void BeizerCurves<T>::eval(T t, int d, bool l)
{
    this->_p.setDim(_degree+1);
    _beizEval.BeizerEvaluater(_MatrixEval, _degree, _dScale, t);
    this->_p = _MatrixEval*_controlPoint;
}

template <typename T>
T BeizerCurves<T>::getEndP()
{
    return T(1);
}
template <typename T>
T BeizerCurves<T>::getStartP()
{
    return T(0);
}
template <typename T>
void BeizerCurves<T>::localSimulate(double dt)
{
   //this->translate(GMlib::Vector<T,3>(0.1f,0.0,0.0));
  this->rotate(GMlib::Angle(M_PI/4 * dt), GMlib::Vector<float,3>( 0.0f, 0.0f, 1.0f ));
}

