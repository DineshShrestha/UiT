#include "controller.h"
#include "scenario.h"
#include <QDebug>

namespace ALLlib {

Controller::Controller(std::shared_ptr<GMlib::Camera> chaseCamera,
                       std::shared_ptr<GMlib::SpotLight> redLight, Scenario *scenario) {

    _chaseCam = chaseCamera;
    _redLight = redLight;
    _scenario =scenario;

    _shadow = std::make_shared<GMlib::PCone<float>>(0.15f, 0.001f);
    _shadow->toggleDefaultVisualizer();
    _shadow->replot(30, 30, 1, 1);
    _shadow->setMaterial(GMlib::GMmaterial::Gold);
    insert(_shadow.get());
    this->setSurroundingSphere(GMlib::Sphere<float ,3>(100.0f));


    _quadcopter = std::make_shared<Quadcopter> ();
    insert(_quadcopter.get());


    _quadcopter->insert(_chaseCam.get());
    _quadcopter->insert(_fpsCam.get());



    _redLight->translate(GMlib::Vector<float, 3>(-0.5f, 0, 0.05f));
    _quadcopter->insert(_redLight.get());
    _frame = std::make_shared<Frame>();
    _quadcopter ->insert(_frame.get());


    // Terrain
    GMlib::DMatrix<GMlib::Vector<float,3>> Mat(3,3);
    Mat[0][0] = GMlib::Vector<float,3>(-20, -20, -0.04);
    Mat[0][1] = GMlib::Vector<float,3>(-20, 0, -0.04);
    Mat[0][2] = GMlib::Vector<float,3>(-20, 20, -0.04);


    Mat[1][0] = GMlib::Vector<float,3>(0, -20, -0.04);
    Mat[1][1] = GMlib::Vector<float,3>(0, 0, -0.04);
    Mat[1][2] = GMlib::Vector<float,3>(0, 20, -0.04);


    Mat[2][0] = GMlib::Vector<float,3>(20, -20, -0.04);
    Mat[2][1] = GMlib::Vector<float,3>(20, 0, -0.04);
    Mat[2][2] = GMlib::Vector<float,3>(20, 20, -0.04);



    TexLoader t;
    auto texture = t.loadTexture("img/skybox.JPG");

    _terrain = std::make_shared<Terrain>(Mat);
    _terrain->insertVisualizer(texture);
    _terrain->toggleDefaultVisualizer();
    _terrain->replot(50, 50, 1, 1);
    _terrain->setMaterial(GMlib::GMmaterial::Obsidian);
    insert(_terrain.get());


    // physics
    _step = GMlib::Vector<float, 3>(0, 0, 0);
    _pitchDir = 0;
    _rollDir = 0;
    _yawDir = 0;

    _inertiaMat = GMlib::SqMatrix<double,3>(GMlib::Vector<GMlib::Vector<double,3>, 3>(GMlib::Vector<double, 3>(0.047316, 0, 0),
                                                                                         GMlib::Vector<double, 3>(0, 0.47316, 0),
                                                                                         GMlib::Vector<double, 3>(0, 0, 0.539632)));


    _inertiaMatInverse = _inertiaMat;
    _inertiaMatInverse.invert();

    _rMat = GMlib::SqMatrix<double, 3>(
                GMlib::Vector<GMlib::Vector<double, 3>, 3>(
                    GMlib::Vector<double, 3>(1, 0, 0),
                    GMlib::Vector<double, 3>(0, 1, 0),
                    GMlib::Vector<double, 3>(0, 0, 1)));

    _rDotMat = GMlib::SqMatrix<double, 3>(
                GMlib::Vector<GMlib::Vector<double, 3>, 3>(
                    GMlib::Vector<double, 3>(0, 0, 0),
                    GMlib::Vector<double, 3>(0, 0, 0),
                    GMlib::Vector<double, 3>(0, 0, 0)));

    _oVector = GMlib::Vector<double, 3>(0.f, 0.f, 0.f);

    _oDotVector = GMlib::Vector<double, 3>(0.f, 0.f, 0.f);

    _tVector  = GMlib::Vector<double, 3>(0.f, 0.f, 0.f);
    _oXMat = GMlib::SqMatrix<double, 3>(
                GMlib::Vector<GMlib::Vector<double, 3>, 3>(
                    GMlib::Vector<double, 3>(0, 0, 0),
                    GMlib::Vector<double, 3>(0, 0, 0),
                    GMlib::Vector<double, 3>(0, 0, 0)));

    _bestConfig.distance = 1e10f;

}

Controller::~Controller() {

}

void Controller::applySmother(float smother){
    _quadcopter ->applysmother(smother);
}

void Controller::applyPitch(int dir) {

    _pitchDir = dir;
}

void Controller::applyRoll(int dir) {

    _rollDir = dir;
}


void Controller::applyYaw(int dir) {

    _yawDir = dir;
}

void Controller::toggleAutoAdjust(){
    _quadcopter ->autoSmother();
}


void Controller::computeStep(double dt) {

    float thrust = 0;

    auto motors = _quadcopter->motors();

    for (auto motor : motors) {

        thrust += _T * std::pow(motor->getAngularVel(), 2);
    }

    auto globMat = _quadcopter->getMatrixGlobal();
    globMat.invert();
    auto localGravVec = globMat * _gravityVec;

    _step = localGravVec + (1.f / _quadcopter->getMass()) * GMlib::Vector<float, 3>(0, 0, thrust);

    qDebug()<<thrust;

    _rMat += _rDotMat * dt;

    _oXMat[0][0] = 0;
    _oXMat[0][1] = -_oVector[2];
    _oXMat[0][2] = _oVector[1];

    _oXMat[1][0] = _oVector[2];
    _oXMat[1][1] = 0;
    _oXMat[1][2] = -_oVector[0];

    _oXMat[2][0] = -_oVector[1];
    _oXMat[2][1] = _oVector[0];
    _oXMat[2][2] = 0;

    _rDotMat = _rMat * _oXMat;

    _oVector += _oDotVector * dt;

    GMlib::Vector<double, 3> forRealsies = _inertiaMat * _oVector;
    GMlib::Vector<double, 3> cross = _oVector ^ forRealsies;

    _oDotVector = _inertiaMatInverse * (_tVector - cross);

    //torque1
    double t1 = _d * _T * (std::pow(motors[1]->getAngularVel(), 2)
            - std::pow(motors[3]->getAngularVel(), 2));

    // torque 2
    double t2 = _d * _T * (std::pow(motors[0]->getAngularVel(), 2)
            - std::pow(motors[2]->getAngularVel(), 2));

    // total torque
    double t3 = _Q * (-std::pow(motors[0]->getAngularVel(), 2)
            + std::pow(motors[1]->getAngularVel(), 2)
            - std::pow(motors[2]->getAngularVel(), 2)
            + std::pow(motors[3]->getAngularVel(), 2));

    _tVector[0] = t1;
    _tVector[1] = t2;
    _tVector[2] = t3;

}

void Controller::testBall(){


}

void Controller::mixPitch() {

    if (_pitchDir != 0) {

        if (_pitchDir == -1) {

            _quadcopter->motors()[0]->smotherUp();
            _quadcopter->motors()[2]->smotherDown();
        }
        else if (_pitchDir == 1){

            _quadcopter->motors()[0]->smotherDown();
            _quadcopter->motors()[2]->smotherUp();
        }
    }
    else if (_pitchDir == 0) {

        _quadcopter->motors()[0]->resetSmother();
        _quadcopter->motors()[2]->resetSmother();
    }
}

void Controller::mixRoll() {

    if (_rollDir != 0) {

        if (_rollDir == -1) {

            _quadcopter->motors()[1]->smotherUp();
            _quadcopter->motors()[3]->smotherDown();
        }
        else if (_rollDir == 1){

            _quadcopter->motors()[1]->smotherDown();
            _quadcopter->motors()[3]->smotherUp();
        }
    }
    else if (_rollDir == 0) {

        _quadcopter->motors()[1]->resetSmother();
        _quadcopter->motors()[3]->resetSmother();
    }
}

void Controller::mixYaw() {

    if (_yawDir != 0) {

        if (_yawDir == 1) {

            _quadcopter->motors()[0]->smotherDownYaw();
            _quadcopter->motors()[1]->smotherUpYaw();
            _quadcopter->motors()[2]->smotherDownYaw();
            _quadcopter->motors()[3]->smotherUpYaw();
        }
        else if (_yawDir == -1){

            _quadcopter->motors()[0]->smotherUpYaw();
            _quadcopter->motors()[1]->smotherDownYaw();
            _quadcopter->motors()[2]->smotherUpYaw();
            _quadcopter->motors()[3]->smotherDownYaw();
        }
    }
    else if (_yawDir == 0) {

        for (auto motor : _quadcopter->motors())
            motor->resetSmotherYaw();
    }
}

void Controller::localSimulate(double dt) {

    mixPitch();
    mixRoll();
    mixYaw();

    computeStep(dt);


    GMlib::Vector<float, 3> dir(_rMat[0][0], _rMat[0][1], _rMat[0][2]);
    GMlib::Vector<float, 3> up(_rMat[2][0], _rMat[2][1], _rMat[2][2]);

    _quadcopter->set(_quadcopter->getPos(), dir, up);

    auto gssd =_quadcopter->getPos();
    bool canTranslate =false;
    qDebug()<<_step[0]*dt<<" "<<_step[1]*dt<<" "<<_step[2]*dt;
    if ((_quadcopter->getPos() + _step * dt)[2] > 0.f || _step[2] > 0.f) {
        canTranslate =true;
    }
    else{
        _quadcopter->set(GMlib::Point<float,3>(gssd[0],gssd[1],0),dir,up);

    }

  _dtTimer += dt;
    if (_dtTimer >= 0.5) {
        _dtTimer = 0;
        _pathTraceQueue.push(_quadcopter->getPos());
    }

    if(canTranslate){
        _quadcopter ->translate(_step*dt);
        _shadow->set(GMlib::Point<float, 3>(gssd[0], gssd[1], 0), _shadow->getDir(), _shadow->getUp());
    }

    for(unsigned int i=0;i<_quadcopter->motors().size();i++)
        _frame->motorParts()[i]->setRotorSpeed(_quadcopter->motors()[i]->totalSmother());


    }
}
