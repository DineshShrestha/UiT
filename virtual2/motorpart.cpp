#include "motorpart.h"
namespace ALLlib {
MotorPart::MotorPart(RotorDirection rotordirection) {
    _rotorDirection = rotordirection;
    this->setSurroundingSphere(GMlib::Sphere<float,3>(100.0f));

    auto motorCasing = std::make_shared<GMlib::PCylinder<float>>(0.01, 0.01, 0.06);
    motorCasing->toggleDefaultVisualizer();
    motorCasing->replot(50, 50, 1, 1);
    motorCasing->setMaterial(GMlib::GMmaterial::Emerald);
    insert(motorCasing.get());
    _motorParts.push_back(motorCasing);
    auto SpinHead = std::make_shared<GMlib::PCone<float>>(0.005, 0.005);
    SpinHead->toggleDefaultVisualizer();
    SpinHead->translate( GMlib::Vector<float,3>(0, 0, 0.035));
    SpinHead->replot(50, 50, 1, 1);
    SpinHead->setMaterial(GMlib::GMmaterial::Copper);
    insert(SpinHead.get());
    _motorParts.push_back(SpinHead);

    for (int i = 0; i < 3; i++) {

        auto rotor = std::make_shared<GMlib::PPlane<float>>(GMlib::Point<float, 3>(0, -0.002, 0.03),
                                                                 GMlib::Vector<float, 3>(0.009, 0, 0.004),
                                                                 GMlib::Vector<float, 3>(0, 0.1, 0));
        rotor->toggleDefaultVisualizer();
        rotor->rotate(GMlib::Angle(120 * i), GMlib::Vector<float, 3>(0, 0, 1));
        rotor->replot(1, 1, 1, 1);
        rotor->setMaterial(GMlib::GMmaterial::Copper);
        insert(rotor.get());
        _rotor.push_back(rotor);
    }
}
MotorPart::~MotorPart() {
    _motorParts.clear();
    _rotor.clear();
}

void MotorPart::setRotorSpeed(float speed) {
    _rotorSpeed = speed;
}
void MotorPart::localSimulate(double dt) {
    for (auto rb : _rotor) {
        rb->rotate(GMlib::Angle(_rotorSpeed * dt * (int)_rotorDirection), GMlib::Vector<float, 3>(0, 0, 1));
    }
}
}
