#ifndef QUADCOPTER_H
#define QUADCOPTER_H

#include "motor.h"
#include "frame.h"
#include <memory>
#include <scene/gmsceneobject>


namespace ALLlib {

class Quadcopter : public GMlib::SceneObject {
    GM_SCENEOBJECT(Quadcopter)

    private:
        //std::vector<std::shared_ptr<GMlib::SceneObject>> _parts;
        float _smother;
    // motors
    std::vector<std::shared_ptr<Motor>> _motors;
    const float _mass= 1.25f;


public:
    Quadcopter();
    ~Quadcopter();
    float getMass() const;
    void applysmother(float smother);
    void autoSmother();
    std::vector<std::shared_ptr<Motor>> motors() const;
protected:
    void localSimulate(double dt) override;
};
}

#endif // QUADCOPTER_H
