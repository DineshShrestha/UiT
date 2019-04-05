#include"firstsubcurve.h"



template <typename T>
inline
firstSubCurve<T>::firstSubCurve(std::shared_ptr<GMlib::PCurve<T,3>> originalCurve, T startPoint, T centerPoint, T endPoint)
{
    _oCurve= originalCurve;
    _cPoint =centerPoint;
    _sPoint =startPoint;
    _ePoint =endPoint;
   // std::cout<<"original curve:"<<_oCurve<<"center Point"<<_cPoint<<"start point"<<_sPoint<<"end point"<<_ePoint<<std::endl;
    GMlib::DVector<GMlib::Vector<T,3> > trans = _oCurve->evaluateParent(_cPoint, 0);
       _t = trans[0];
       this->translateParent( _t );

}

template <typename T>
firstSubCurve<T>::~firstSubCurve() {}


template <typename T>
void firstSubCurve<T>::eval(T t, int d, bool l)
{


    this->_p     = _oCurve->evaluateParent(t , d);
    this->_p[0] -= _t;
}


template <typename T>
inline
T firstSubCurve<T>::getEndP()
{
    return _ePoint;
}
template <typename T>
inline
T firstSubCurve<T>::getStartP()
{
    return _sPoint;
}
template <typename T>
inline
T firstSubCurve<T>::getCenterPoint()
{
    return _cPoint;
}
template <typename T>
inline
void firstSubCurve<T>::localSimulate(double dt)
{
//this->rotate(GMlib::Angle(M_PI/4 * dt), GMlib::Vector<float,3>( 0.0f, 0.0f, 1.0f ));
}

