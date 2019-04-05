#ifndef MOTOR_H
#define MOTOR_H

#include<cmath>

namespace ALLlib {

class Motor  {


public:

    Motor();

    ~Motor();

    void applysmother(float smother);
    void decreasesmother(float smother);
    float getAngularVel();

    void smotherUp();
    void smotherDown();
    void smotherUpYaw();
    void smotherDownYaw();
    void resetSmother();
    void resetSmotherYaw();

    void autoAdjust();
    float totalSmother();
private:
    float _smother;


    //std::shared_ptr<GMlib::PPlane<float>> _rotorBlade1;
    //std::shared_ptr<GMlib::PPlane<float>> _rotorBlade2;


    float _angular_vel;
    double _dt;

    //physics
    bool _autoD = false;
    float _smotherUp = 0;
    float _smotherUpYaw = 0;
    const double _fakedt=0.02;

    const float _smotherThresholdHigh = 23.4f;
    const float _smotherThresholdLow = 21.3f;

};

}

#endif // MOTOR_H
