#ifndef SCENARIO_H
#define SCENARIO_H


#include "application/gmlibwrapper.h"

// qt
#include <QObject>
#include<memory>

namespace GMlib {
template<typename T>
class PSphere;
}

namespace ALLlib {
class Controller;
}

class Scenario : public GMlibWrapper {
    Q_OBJECT
public:
    using GMlibWrapper::GMlibWrapper;

    // Controls
    void controlUp();
    void controlDown();
    void controlPitchDown();
    void controlPitchUp();
    void controlRollLeft();
    void controlRollRight();
    void controlYawLeft();
    void controlYawRight();

    void controlReleasePitch();
    void controlReleaseYaw();
    void controlReleaseRoll();

    void controlHover();

    void    initializeScenario() override;
    void    cleanupScenario() override;

private:
    ALLlib::Controller* _controller;
    std::shared_ptr<GMlib::PSphere<float>> _skybox;
signals:
    void signUpdateShipStats(const QString& text);
};

#endif // SCENARIO_H
