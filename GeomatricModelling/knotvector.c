#include"knotvector.h"


template <typename T>
knotVector<T>::knotVector(std::shared_ptr<firstCurve<T>>firstcurve,int number_of_local_curves)
{

    _firstCurve =firstcurve;

    this->setDim(number_of_local_curves+2);
    startP = _firstCurve-> getParStart();
    endP= _firstCurve->getParEnd();
    if(_firstCurve->isClosed())
        step= (endP-startP)/(number_of_local_curves-1);
    else
        step =(endP-startP)/(number_of_local_curves-1);

 for(int i=0;i<2;i++)
    {
        (*this)[i]= startP;
        (*this)[number_of_local_curves +i] =endP;
    }
    for(int i=2;i<number_of_local_curves;i++)
    {
        (*this)[i]= startP+step*(i-1);
    }

   if(_firstCurve->isClosed()){
       (*this)[0]= startP -step;
       (*this)[number_of_local_curves+1]= endP+ step;
    }

}


template <typename T>
int knotVector<T>::getSize()
{
    return (*this).getDim();
}
template <typename T>
T knotVector<T>::getParam(int i)
{
 return (*this)[i];
}
