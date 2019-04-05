#include "terrain.h"

namespace ALLlib {

Terrain::Terrain(const GMlib::DMatrix<GMlib::Vector<float, 3>>& points) {

    _points = points;

    this->_dm = GMlib::GM_DERIVATION_EXPLICIT;
}

Terrain::Terrain(const Terrain &copy) : GMlib::PSurf<float, 3>(copy) {

    _points = copy._points;
}

Terrain::~Terrain() {

}

void Terrain::eval(float u, float v, int d1, int d2, bool lu, bool lv) {

    this->_p.setDim( d1+1, d2+1 );

    GMlib::DVector<float> u1(3);
    u1[0] = (1 - u) * (1 - u);
    u1[1] = 2 * u * (1 - u);
    u1[2] = u * u;

    GMlib::DVector<float> v1(3);
    v1[0] = (1 - v) * (1 - v);
    v1[1] = 2 * v * (1 - v);
    v1[2] = v * v;

    //this->_p[0][0] = _pt1 + u*(_pt2 - _pt1) + v*(_pt4 - _pt1 + u*(_pt1 - _pt2 + _pt3 - _pt4));
    this->_p[0][0] = u1 * (_points ^ v1);

    if( this->_dm == GMlib::GM_DERIVATION_EXPLICIT ) {

        GMlib::DVector<float> u2(3);
        u2[0] = -2 * (1 - u);
        u2[1] = 2 - 4 * u;
        u2[2] = 2 * u;
        //std::cout<<"hello"<<u2;

        GMlib::DVector<float> v2(3);
        v2[0] = -2 * (1 - v);
        v2[1] = 2 - 4 * v;
        v2[2] = 2 * v;

        // 1st
        if(d1)            this->_p[1][0] = u2 * (_points ^ v1); // S_u
        if(d2)            this->_p[0][1] = u1 * (_points ^ v2); // S_v
        if(d1>1 && d2>1)  this->_p[1][1] = u2 * (_points ^ v2); // S_uv

        // 2nd
        if(d1>1)          this->_p[2][0] = GMlib::Vector<float,3>(float(0)); // S_uu
        if(d2>1)          this->_p[0][2] = GMlib::Vector<float,3>(float(0)); // S_vv
        if(d1>1 && d2)    this->_p[2][1] = GMlib::Vector<float,3>(float(0)); // S_uuv
        if(d1   && d2>1)  this->_p[1][2] = GMlib::Vector<float,3>(float(0)); // S_uvv
        if(d1>1 && d2>1)  this->_p[2][2] = GMlib::Vector<float,3>(float(0)); // S_uuvv

        // 3rd
        if(d1>2)          this->_p[3][0] = GMlib::Vector<float,3>(float(0)); // S_uuu
        if(d2>2)          this->_p[0][3] = GMlib::Vector<float,3>(float(0)); // S_vvv
        if(d1>2 && d2)    this->_p[3][1] = GMlib::Vector<float,3>(float(0)); // S_uuuv
        if(d1   && d2>2)  this->_p[1][3] = GMlib::Vector<float,3>(float(0)); // S_uvvv
        if(d1>2 && d2>1)  this->_p[3][2] = GMlib::Vector<float,3>(float(0)); // S_uuuvv
        if(d1>1 && d2>2)  this->_p[2][3] = GMlib::Vector<float,3>(float(0)); // S_uuvvv
        if(d1>2 && d2>2)  this->_p[3][3] = GMlib::Vector<float,3>(float(0)); // S_uuuvvv
    }
}

float Terrain::getEndPU() {

    return float(1);
}

float Terrain::getEndPV() {

    return float(1);
}

float Terrain::getStartPU() {

    return float(0);
}

float Terrain::getStartPV() {

    return float(0);
}

}
