#include "sphere.h"

Sphere::~Sphere()
{
    if(_sphere) remove(_sphere.get());
}

//void
//Sphere::TestSphere() {

//    if(_sphere) return;
//    GMlib::Vector<float,3> d = evaluate(0.0f,0.0f,0,0)[0][0];
//    _sphere = std::make_unique<TestSphere,float,float,float>(1.5f,0.5f,0.5f);

//    _sphere->translate(d + d.getNormalized()*2.0f);
//    _sphere->rotate( GMlib::Angle(90), GMlib::Vector<float,3>( 0.0f, 1.0f, 0.0f) );
//    _sphere->toggleDefaultVisualizer();
//    _sphere->setRadius(100);
//    insert(_sphere.get());

//}
void Sphere::localSimulate(double dt) {

  rotate( GMlib::Angle(90) * dt, GMlib::Vector<float,3>( 0.0f, 0.0f, 1.0f ) );
  rotate( GMlib::Angle(180) * dt, GMlib::Vector<float,3>( 1.0f, 1.0f, 0.0f ) );
}
