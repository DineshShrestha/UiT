#ifndef FRAME_H
#define FRAME_H
#include <memory>
#include "motorpart.h"
#include <scene/gmsceneobject>
#include <parametrics/gmpcylinder>
#include <parametrics/gmpsphere>
#include <parametrics/gmpcone>
#include <parametrics/gmpplane>

namespace ALLlib {

class Frame : public GMlib::SceneObject {
    GM_SCENEOBJECT(Frame)

    private:
        std::vector<std::shared_ptr<GMlib::PSurf<float, 3>>> _parts;
    std::vector<std::shared_ptr<MotorPart>> _motorParts;
public:
    Frame();
    ~Frame();
    std::vector<std::shared_ptr<MotorPart>> motorParts() const;
};

}

#endif // FRAME_H
