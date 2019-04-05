#include"gerbscurve.h"

template<typename T>
inline
gerbsCurve<T>::gerbsCurve(std::shared_ptr<firstCurve<T>> originalCurve, int number_of_local_curves)
{
    _firstCurve= originalCurve;
    if(_firstCurve->isClosed())
    {
        number_of_local_curves++;

    }

    _knotVector = std::make_shared<knotVector<T>>(_firstCurve, number_of_local_curves);
   for(int i=0;i<number_of_local_curves-1;i++)
    {


        float s = _knotVector->getParam(i);
        float c = _knotVector->getParam(i + 1);
        float e = _knotVector->getParam(i + 2);
        auto curve =std::make_shared<firstSubCurve<T>>(_firstCurve,s,c,e);
        _firstSubCurve.push_back(curve);

    }

    if(_firstCurve->isClosed())
    {

        _firstSubCurve.push_back(_firstSubCurve[0]);

    }
    else
    {
        int last =_knotVector->getSize();
        float s = _knotVector->getParam(last-3);
        float c = _knotVector->getParam(last - 2);
        float e = _knotVector->getParam(last-1);
        auto curve =std::make_shared<firstSubCurve<T>>(_firstCurve,s,c,e);
        _firstSubCurve.push_back(curve);

    }
    for(unsigned int i=0;i<_firstSubCurve.size();i++)
    {
        _firstSubCurve[i]->toggleDefaultVisualizer();
        _firstSubCurve[i]->setColor(_colors[i]);
        _firstSubCurve[i]->replot(100,1);

           this->insert(_firstSubCurve[i].get());
    }
  /* GMlib::DMatrix<T> _MatrixEval;
    BeizEvaluater<float>  bspline;
    std::cout<<"matrix"<<_MatrixEval<<std::endl;
   // bspline.BSplineEvaluater(_MatrixEval,_knotVector,2,_knotVector->getParam(1));*/
      generateBeizer();
}
template<typename T>
void gerbsCurve<T>::generateBeizer()
{
   for(int i=0;i<_knotVector->getSize()-2;i++)
    {
        float s = _knotVector->getParam(i);
        float c = _knotVector->getParam(i+1);
        float e = _knotVector->getParam(i+2);
        auto curve = std::make_shared<BeizerCurves<T>>(_firstCurve,s,c,e,2);

        _BeizerCurve.push_back(curve);

    }
    if(_firstCurve->isClosed())
    {

        _BeizerCurve.push_back(_BeizerCurve[0]);

    }
    else
    {
        int last =_knotVector->getSize();
        float s = _knotVector->getParam(last-3);
        float t = _knotVector->getParam(last - 2);
        float e = _knotVector->getParam(last-1);
        auto curve =std::make_shared<BeizerCurves<T>>(_firstCurve,s,t,e,2);
        _BeizerCurve.push_back(curve);


    }

    for(unsigned int i=0;i<_BeizerCurve.size();i++)
    {

        _BeizerCurve[i]->toggleDefaultVisualizer();
        _BeizerCurve[i]->setColor(_colors[i]);
        _BeizerCurve[i]->replot(100,2);
        this->insert(_BeizerCurve[i].get());

    }

}



template<typename T>
void gerbsCurve<T>::eval(T t, int d, bool l)
{
      this->_p.setDim(d+1);
    beizerEval(t,d);


}
template<typename T>
inline
T gerbsCurve<T>::getEndP()
{
    return _knotVector->getParam(_knotVector->getSize()-2);
}
template<typename T>
inline
T gerbsCurve<T>::getStartP()
{
    return _knotVector->getParam(1);
}
template<typename T>
inline
T gerbsCurve<T>::Bfunction(T tp)
{
    return 3*std::pow(tp,2) - 2*std::pow(tp,3);
}
template<typename T>
inline
T gerbsCurve<T>::BfunctionDer1(T tp,T scale)
{
     return 6*(tp) - 6*std::pow(tp,2)*scale;
}
template<typename T>
inline
T gerbsCurve<T>::BfunctionDer2(T tp,T scale)
{
    return 6-12*tp*std::pow(scale,2);
}

template<typename T>
void gerbsCurve<T>::beizerEval(T t, int d)
{
 this->_p.setDim(d+1);
    //find knot interval
    int k=0;
    for ( k=1;k<_knotVector->getSize()-3;++k)
    {
        if(t<_knotVector->getParam(k+1))
            break;

     }


    T tk =(t-(_knotVector->getParam(k-1)))/(_knotVector->getParam(k+1)-_knotVector->getParam(k-1));
    T tk1=(t-(_knotVector->getParam(k)))/(_knotVector->getParam(k+2)-_knotVector->getParam(k));

    T scale=1/(_knotVector->getParam(k+1)-(_knotVector->getParam(k)));
    T scaleBasis = (t - _knotVector->getParam(k)) / (_knotVector->getParam(k+1)-_knotVector->getParam(k));

    auto ck=_BeizerCurve [k-1]->evaluateParent(tk,d);//location 0-1
      auto ck1=_BeizerCurve[k]->evaluateParent(tk1,d);//location 0

      //c(t)
       this->_p[0]= ck[0]+(ck1[0]-ck[0])*Bfunction(scaleBasis);

      //first derivaive of c(t)
        if(d > 0)
        {
              this->_p[1] = ck[1] + (ck1[1] - ck[1]) * Bfunction(scaleBasis) + (ck1[0] - ck[0]) *  BfunctionDer1(scaleBasis,scale);

   }
   // Second derivate of c(t)
         if(d > 1)
        {
            this->_p[2] = ck[2] + (ck1[2] - ck[2]) *  Bfunction(scaleBasis) + 2*(ck1[1] - ck[1]) *  BfunctionDer1(scaleBasis,scale)+
                       (ck1[0] - ck[0])*  BfunctionDer2(scaleBasis,scale);
          }

}
template<typename T>
inline
void gerbsCurve<T>::localSimulate(double dt)
{
    double sum=0;
    sum += dt;

    this->rotateGlobal(GMlib::Angle(dt),GMlib::Vector<float,3>(0.0f,0.0f,0.1f));

}


template <typename T>
inline
bool gerbsCurve<T>::isClosed() const {

  return true;
}
