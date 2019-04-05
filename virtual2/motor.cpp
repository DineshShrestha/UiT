#include "motor.h"

namespace ALLlib {

Motor::Motor() {


    _smother = 0;
    _angular_vel = 0.f;

}


Motor::~Motor() {

}

void Motor::applysmother(float smother) {
    if (smother > 0) {
        if (_smother + smother < _smotherThresholdHigh)
            _smother = _smotherThresholdHigh;
    }else if (_smother + smother < _smotherThresholdLow)
        _smother = 0;

    if (_smother + smother >= 0)

        _smother += smother;

    else

        _smother = 0;
}

void Motor::smotherUp() {

    _smotherUp = 0.8f;
}

void Motor::smotherDown() {

    _smotherUp = -0.2f;
}
void Motor::smotherUpYaw() {

    _smotherUpYaw = 6.8f;
}
void Motor::smotherDownYaw() {

    _smotherUpYaw = -10.f;
}
void Motor::resetSmother() {

    _smotherUp = 0.f;
}
void Motor::resetSmotherYaw() {

    _smotherUp = 0.f;
}

float Motor::totalSmother(){

    if (_autoD) {

        float f = (1.25f * 9.81f) / (4.f * 8.6e-6);
        float x = std::sqrt(f);

        _smother = (x * 2 * _fakedt);
    }
    return _smother + _smotherUp > 0.f ? _smother + _smotherUp : 0.0f;
}
float Motor::getAngularVel(){
    return _smother;

}

void Motor::autoAdjust(){
    _autoD= !_autoD;
}

}
