#include "object.h"
namespace ALLlib {
Object::Object(float size, float mass, GMlib::Vector<float, 3> velocity)
     : GMlib::PSphere<float>(size) {

  _mass = mass;
   _velocity = velocity;
   _step = GMlib::Vector<float, 3>(0, 0, 0);



     _time_to_live = 0;
    _time_alive = 0;
    // _is_expired = false;

}
Object::~Object() {
}
GMlib::Vector<float, 3> Object::calculateStep(double dt) {


    _velocity += dt * (_force / _mass);
    return _velocity;
}

GMlib::Vector<float, 3> Object::getStep() const {
    return _step;
}
 void Object::setStep(GMlib::Vector<float, 3> step) {
    _step = step;
}
void Object::setVelocity(GMlib::Vector<float, 3> newVelocity) {
    _velocity = newVelocity;
}
GMlib::Vector<float, 3> Object::getVelocity() const {
    return _velocity;
}
float Object::getMass() const {
    return _mass;
}
void Object::setDespawnTime(float lifespan) {
    _time_to_live = lifespan;
 }
 bool Object::isExpired() const {
    return _is_expired;
 }
 void Object::localSimulate(double dt) {
    // Oject has limited lifespan
     if (_time_to_live != 0) {
         _time_alive += dt;
         if (_time_alive >= _time_to_live)
             _is_expired = true;
     }
    this->translateGlobal(_step*dt);
 }
}
