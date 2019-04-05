#include "quadcopter.h"

// gmlib
#include <gmOpenglModule>
#include <gmSceneModule>
#include <gmParametricsModule>

namespace ALLlib {

Quadcopter::Quadcopter() {

    this->setSurroundingSphere(GMlib::Sphere<float,3>(100.0f));


    _smother = 0;
    // Motors
    for(int i=0;i<4;i++){
        auto motor =std::make_shared<Motor>();
        _motors.push_back(motor);
    }
}

Quadcopter::~Quadcopter() {

    _motors.clear();
}

void Quadcopter::applysmother(float smother) {
    for(auto motor: _motors)
        motor->applysmother(smother);
}

void Quadcopter::autoSmother() {

    for (auto motor : _motors) {

        motor->autoAdjust();
    }
}

std::vector<std::shared_ptr<Motor>> Quadcopter::motors() const {

    return _motors;
}

float Quadcopter::getMass() const {

    return _mass;
}


void Quadcopter::localSimulate(double dt) {
}

}
