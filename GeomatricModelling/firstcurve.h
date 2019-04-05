
#ifndef FIRSTCURVE_H
#define FIRSTCURVE_H


#include <parametrics/gmpcurve>
#include<gmParametricsModule>


template <typename T>
    class firstCurve : public GMlib::PCurve<T,3> {
      GM_SCENEOBJECT(firstCurve)
    public:
      firstCurve();
      firstCurve( const firstCurve<T>& copy );
      virtual ~firstCurve();

      bool            isClosed() const;



    protected:

      void	          eval(T t, int d, bool l);
      T               getEndP();
      T               getStartP();

    private:


  }; // END class firstcurve

#include "firstcurve.c"
#endif // FIRSTCURVE_H
