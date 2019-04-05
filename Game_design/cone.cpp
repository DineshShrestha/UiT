#include "cone.h"

Cone::~Cone()
{
    if(_cone) remove(_cone.get());
}

void Cone::localSimulate(double dt) {

    rotate( GMlib::Angle(90) * dt, GMlib::Vector<float,3>( 0.0f, 0.0f, 1.0f ) );
    rotate( GMlib::Angle(180) * dt, GMlib::Vector<float,3>( 1.0f, 1.0f, 0.0f ) );
}
