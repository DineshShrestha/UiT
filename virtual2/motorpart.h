#ifndef MOTORPART_H
#define MOTORPART_H

#include <memory>
#include <scene/gmsceneobject>
#include <parametrics/gmpcylinder>
#include <parametrics/gmpsphere>
#include <parametrics/gmpcone>
#include <parametrics/gmpplane>
namespace ALLlib {
enum RotorDirection {
    CW = 1,
    CCW = -1,
};
class MotorPart : public GMlib::SceneObject {
    GM_SCENEOBJECT(MotorPart)
    public:
        MotorPart(RotorDirection rotorDirection = CW);
    ~MotorPart();
    void setRotorSpeed(float speed);


private:

    std::vector<std::shared_ptr<GMlib::PSurf<float, 3>>> _motorParts;
    std::vector<std::shared_ptr<GMlib::PPlane<float>>> _rotor;

    RotorDirection _rotorDirection;
    float _rotorSpeed;
protected:
    void localSimulate(double dt) override;
};

}

#endif // MOTORPART_H
