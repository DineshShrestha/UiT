#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "quadcopter.h"
#include "terrain.h"
#include "texloader.h"
#include<queue>
#include <memory>
#include<parametrics/gmpcone>
#include<parametrics/gmpsphere>
#include<scene/gmspotlight>
#include <scene/gmsceneobject>

class Scenario;
namespace ALLlib {

class Controller : public GMlib::SceneObject {
    GM_SCENEOBJECT(Controller)

    public:
        Controller(std::shared_ptr<GMlib::Camera> chaseCamera,
                   std::shared_ptr<GMlib::SpotLight> redLight, Scenario* scenario);
    ~Controller();
    void applySmother(float smother);
    void applyPitch(int dir);
    void applyRoll(int dir);
    void applyYaw(int dir);
    void toggleAutoAdjust();
    void testBall();

private:
    std::shared_ptr<Quadcopter> _quadcopter;
    std::shared_ptr<GMlib::Camera> _chaseCam;
    std::shared_ptr<GMlib::Camera> _fpsCam;
    std::shared_ptr<Terrain> _terrain;
    std::shared_ptr<GMlib::SpotLight> _redLight;
        std::shared_ptr<GMlib::Arrow<float, 3>> _arrow;
    std::vector<GMlib::Point<float, 3>> _pathTrace;
    std::queue<GMlib::Point<float, 3>> _pathTraceQueue;
    std::vector<std::shared_ptr<GMlib::PSphere<float>>> _pathBalls;
    std::shared_ptr<GMlib::PCone<float>>_shadow;
    std::shared_ptr<Frame>_frame;
    void computeStep(double dt);
    Scenario* _scenario;

    GMlib::SqMatrix<double, 3> computeRDotMat;

    void mixPitch();
    void mixRoll();
    void mixYaw();
    //simulalation elements
    const GMlib::Vector<float ,3> _gravityVec = GMlib::Vector<float ,3>(0,0,-9.8f);
    const double _T = 8.6e-6;
    const double _Q = 1.8e-7;
    const double _d = 0.25f;
    GMlib::SqMatrix<double, 3> _inertiaMat;
    GMlib::SqMatrix<double, 3> _inertiaMatInverse;
    GMlib::SqMatrix<double, 3> _rMat;
    GMlib::SqMatrix<double, 3> _rDotMat;
    GMlib::SqMatrix<double, 3> _oXMat;
    GMlib::Vector<double, 3> _oVector;
    GMlib::Vector<double, 3> _oDotVector;
    GMlib::Vector<double, 3> _tVector;
    GMlib::Vector<float, 3> _step;

    int _pitchDir;
    int _rollDir;
    int _yawDir;
    double _dtTimer;

    struct config {
        int m1_smother;
        int m2_smother;
        int m3_smother;
        int m4_smother;
        float distance;
    } _bestConfig;
protected:
    void localSimulate(double dt) override;
    ALLlib::Controller* _controller;
    std::shared_ptr<GMlib::PSphere<float>> _skybox;

};

}
#endif // CONTROLLER_H
