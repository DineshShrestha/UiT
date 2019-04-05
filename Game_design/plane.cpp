#include "plane.h"




Plane::~Plane()
{
    if(_plane) remove(_plane.get());
}

//void Plane::PlaneTest()
//{
//    if( _plane ) return;

//        _plane = std::make_unique<TestPlane,float,float,float>(1.5f,0.5f,0.5f);

//        _plane->toggleDefaultVisualizer();

//        insert(_plane.get());
//}


void Plane::localSimulate(double dt) {

    rotate( GMlib::Angle(90) * dt, GMlib::Vector<float,3>( 0.0f, 0.0f, 1.0f ) );
    rotate( GMlib::Angle(180) * dt, GMlib::Vector<float,3>( 1.0f, 1.0f, 0.0f ) );
}
