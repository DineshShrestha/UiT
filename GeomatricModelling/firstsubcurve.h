#ifndef FIRSTSUBCURVE_H
#define FIRSTSUBCURVE_H
#include<parametrics/gmpline>
#include <parametrics/gmpcurve>
#include <core/containers/gmdvector.h>
#include<memory>
#include<vector>




    template <typename T>
    class firstSubCurve : public GMlib::PCurve<T,3> {

        GM_SCENEOBJECT(firstSubCurve)
    public:
      firstSubCurve( std::shared_ptr<GMlib::PCurve<T,3>> originalCurve, T startPoint, T centerPoint , T endPoint);
      //firstSubCurve (const firstSubCurve<T>& copy);
      virtual ~firstSubCurve();

     // bool            isClosed() const;

    protected:


      void            eval(T t, int d, bool /*l*/);
      T               getEndP();
      T               getStartP();
      T               getCenterPoint();
      void          localSimulate(double dt);

    private:
      T _cPoint;
      T _sPoint;
      T _ePoint;
      std::shared_ptr<GMlib::PCurve<T,3>> _oCurve;
      GMlib::Vector<float, 3> _t;

     

};


#include "firstsubcurve.c"
#endif // FIRSTSUBCURVE_H
