#ifndef GERBSCURVE_H
#define GERBSCURVE_H
#include"firstcurve.h"
#include"firstsubcurve.h"
#include"knotvector.h"
#include"beizercurves.h"
#include <parametrics/gmpcurve>
#include<gmParametricsModule>
#include<memory>


template<typename T>
class gerbsCurve: public GMlib::PCurve<T,3> {
    GM_SCENEOBJECT(gerbsCurve)

    public:
        gerbsCurve(std::shared_ptr<firstCurve<T>> originalCurve, int number_of_local_curves);
        void generate();
        void generateBeizer();
        T               Bfunction(T tp);
        T               BfunctionDer1(T tp,T scale);
        T               BfunctionDer2(T tp,T scale);
        void           beizerEval(T t, int d);
        void           subCurveEval(T t, int d);
private:
    std::shared_ptr<knotVector<T>> _knotVector;
    std::shared_ptr<firstCurve<T>> _firstCurve;
    std::vector<std::shared_ptr<BeizerCurves<T>>>_BeizerCurve;
    std::vector<std::shared_ptr<firstSubCurve<T>>> _firstSubCurve;

     bool            isClosed() const;
protected:

  void	          eval(T t, int d, bool l);//evaluation of B function
  T               getEndP();
  T               getStartP();

   void         localSimulate(double dt);

  const GMlib::Color _colors [14] = {


         GMlib::GMcolor::YellowGreen,
         GMlib::GMcolor::Turquoise,
         GMlib::GMcolor::AliceBlue,
         GMlib::GMcolor::Chocolate,
         GMlib::GMcolor::Black,
         GMlib::GMcolor::DarkGreen,
         GMlib::GMcolor::Gold,
         GMlib::GMcolor::Magenta,
         GMlib::GMcolor::Red,
         GMlib::GMcolor::Aqua,
         GMlib::GMcolor::Yellow,
         GMlib::GMcolor::White,
         GMlib::GMcolor::Green,
         GMlib::GMcolor::BlanchedAlamond,
     };


};

#include"gerbscurve.c"
#endif // GERBSCURVE_H
