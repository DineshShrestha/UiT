#include"firstcurve.h"





template <typename T>
inline
firstCurve<T>::firstCurve() {

}


template <typename T>
inline
firstCurve<T>::firstCurve( const firstCurve<T>& copy ) : GMlib::PCurve<T,3>(copy) {}


template <typename T>
firstCurve<T>::~firstCurve() {}


template <typename T>
inline
void firstCurve<T>::eval( T t, int d, bool /*l*/ ) {

  this->_p.setDim( d + 1 );

  const T x = 3*cos(3*t);//ct
  const T y = 4*sin(t);//st
  const T xd = -9*sin(3*t);
  const T xdd= -27*cos(3*t);
  const T xddd= -81*sin(3*t);
  const T xdddd= -243*cos(3*t);

  const T yd = 4*cos(t);
  const T ydd = -4*sin(t);
  const T yddd= -4*cos(t);
  const T ydddd= 4*sin(t);
  const T z = T(0);



  //non derivates
  this->_p[0][0] = x;
  this->_p[0][1] = y;
  this->_p[0][2] = z;

  if( this->_dm == GMlib::GM_DERIVATION_EXPLICIT ) {

    if( d > 0 ) {

      this->_p[1][0] = xd;
      this->_p[1][1] = yd;
      this->_p[1][2] =  T(0);
    }

    if( d > 1 ) {

      this->_p[2][0] = xdd;
      this->_p[2][1] = ydd;
      this->_p[2][2] =  T(0);
    }

    if( d > 2 ) {

      this->_p[3][0] = xddd;
      this->_p[3][1] = yddd;
      this->_p[3][2] =  T(0);
    }

    if( d > 3 ) {

      this->_p[4][0] =  xdddd;
      this->_p[4][1] =  ydddd;
      this->_p[4][2] =  T(0);
    }

/*    if( d > 4 ) {

      this->_p[5][0] = -st;
      this->_p[5][1] =  ct;
      this->_p[5][2] =  T(0);
    }

    if( d > 5 ) {

      this->_p[6][0] = -ct;
      this->_p[6][1] = -st;
      this->_p[6][2] =  T(0);
    }

    if( d > 6 ) {

      this->_p[7][0] =  st;
      this->_p[7][1] = -ct;
      this->_p[7][2] =  T(0);
    }*/
  }
}



template <typename T>
inline
T firstCurve<T>::getStartP() {

  return T(0);
}

template <typename T>
inline
T firstCurve<T>::getEndP() {

  return T(M_2PI);
}


template <typename T>
inline
bool firstCurve<T>::isClosed() const {

  return true;
}









