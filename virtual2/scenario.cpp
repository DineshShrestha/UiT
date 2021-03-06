#include "scenario.h"

#include "testtorus.h"

#include"controller.h"
#include "texloader.h"
//// hidmanager
//#include "hidmanager/defaulthidmanager.h"

// gmlib
#include <gmOpenglModule>
#include <gmSceneModule>
#include <gmParametricsModule>

// qt
#include <QQuickItem>



void Scenario::initializeScenario() {

    // Insert a light
    GMlib::Point<GLfloat,3> init_light_pos( 2.0, 4.0, 10 );
    GMlib::PointLight *light = new GMlib::PointLight(  GMlib::GMcolor::White, GMlib::GMcolor::White,
                                                       GMlib::GMcolor::White, init_light_pos );
    light->setAttenuation(0.8, 0.002, 0.0008);
    scene()->insertLight( light, false );

    // Insert Sun
    // scene()->insertSun();

    // Default camera parameters
    int init_viewport_size = 600;
    GMlib::Point<float,3> init_cam_pos(  0.0f, 0.0f, 0.0f );
    GMlib::Vector<float,3> init_cam_dir( 1.0f, 0.0f, 0.0f );
    GMlib::Vector<float,3> init_cam_up(  0.0f, 0.0f, 1.0f );

    // Projection cam
    auto proj_rcpair = createRCPair("Projection");
    proj_rcpair.camera->set(init_cam_pos,init_cam_dir,init_cam_up);
    proj_rcpair.camera->setCuttingPlanes( 0.7f, 8000.0f );
    proj_rcpair.camera->rotateGlobal( GMlib::Angle(20), GMlib::Vector<float,3>( 0.0f, 1.0f, 0.0f ) );
    proj_rcpair.camera->translateGlobal( GMlib::Vector<float,3>( -25.0f, 0.0f, 10.0f ) );
    proj_rcpair.camera->enableCulling(false);
    scene()->insertCamera( proj_rcpair.camera.get() );
    proj_rcpair.renderer->reshape( GMlib::Vector<int,2>(init_viewport_size, init_viewport_size) );

    // Front cam
    auto front_rcpair = createRCPair("Front");
    front_rcpair.camera->set( init_cam_pos + GMlib::Vector<float,3>( 0.0f, -5.0f, 0.0f ), init_cam_dir, init_cam_up );
    front_rcpair.camera->setCuttingPlanes( 0.7f, 8000.0f );
    scene()->insertCamera( front_rcpair.camera.get() );
    front_rcpair.renderer->reshape( GMlib::Vector<int,2>(init_viewport_size, init_viewport_size) );

    // Side cam
    auto side_rcpair = createRCPair("Side");
    side_rcpair.camera->set( init_cam_pos + GMlib::Vector<float,3>( -5.0f, 0.0f, 0.0f ), GMlib::Vector<float,3>( 1.0f, 0.0f, 0.0f ), init_cam_up );
    side_rcpair.camera->setCuttingPlanes( 0.7f, 8000.0f );
    scene()->insertCamera( side_rcpair.camera.get() );
    side_rcpair.renderer->reshape( GMlib::Vector<int,2>(init_viewport_size, init_viewport_size) );

    // Top cam
    auto top_rcpair = createRCPair("Top");
    top_rcpair.camera->set( init_cam_pos + GMlib::Vector<float,3>( 0.0f, 0.0f, 5.0f ), -init_cam_up, init_cam_dir );
    top_rcpair.camera->setCuttingPlanes( 0.5f, 8000.0f );
    scene()->insertCamera( top_rcpair.camera.get() );
    top_rcpair.renderer->reshape( GMlib::Vector<int,2>(init_viewport_size, init_viewport_size) );




    // Quadcopter chase cam
    auto quad_chase_rcpair = createRCPair("Quadcopter View");
    quad_chase_rcpair.camera->set(init_cam_pos, init_cam_dir, init_cam_up);
    quad_chase_rcpair.camera->setCuttingPlanes( 0.7f, 8000.0f );
    quad_chase_rcpair.camera->rotateGlobal( GMlib::Angle(20), GMlib::Vector<float,3>( 0.0f, 1.0f, 0.0f ) );
    quad_chase_rcpair.camera->translateGlobal( GMlib::Vector<float,3>(-5.0f, 0.0f, 2.0f ) );
    scene()->insertCamera( quad_chase_rcpair.camera.get(), false);
    quad_chase_rcpair.renderer->reshape( GMlib::Vector<int,2>(init_viewport_size, init_viewport_size) );

    auto redLight = std::make_shared<GMlib::SpotLight>( GMlib::GMcolor::Red, GMlib::GMcolor::Red,
                                                        GMlib::GMcolor::Red, init_light_pos,
                                                        GMlib::Vector<float, 3>(0, -1, 0), GMlib::Angle(10));
    redLight->setAttenuation(0.5, 0.002, 0.0008);
    scene()->insertLight(redLight.get(), false);
    _controller = new ALLlib::Controller(quad_chase_rcpair.camera, redLight,this);
    scene()->insert(_controller);


    //
    // Surface visualizers
    ALLlib::TexLoader skybox;

    auto texture = skybox.loadTexture("img/skybox.JPG");
    _skybox = std::make_shared<GMlib::PSphere<float>>(1300.f);
    _skybox->insertVisualizer(texture);
    _skybox->rotate(GMlib::Angle(-90), GMlib::Vector<float, 3>(1, 0, 0));
    _skybox->replot(70, 70, 1, 1);
    _skybox->setMaterial(GMlib::GMmaterial::Obsidian);
    scene()->insert(_skybox.get());
}


void Scenario::controlUp() {
    // Physics control
    _controller->applySmother(.3f);

}

void Scenario::controlDown() {
    _controller->applySmother(-.3f);
}


void Scenario::controlPitchDown() {

    _controller->applyPitch(-1);
}


void Scenario::controlPitchUp() {

    _controller->applyPitch(1);
}

void Scenario::controlRollLeft(){
    _controller->applyRoll(-1);
}

void Scenario::controlRollRight(){
    _controller->applyRoll(1);
}

void Scenario::controlYawLeft() {

    _controller->applyYaw(-1);
}

void Scenario::controlYawRight() {
    _controller->applyYaw(1);
}

void Scenario::controlReleasePitch(){
    _controller ->applyPitch(0);
}


void Scenario::controlReleaseRoll() {

    _controller->applyRoll(0);
}

void Scenario::controlReleaseYaw() {
    _controller->applyYaw(0);
}

void Scenario::controlHover(){
    _controller ->toggleAutoAdjust();
}


void Scenario::cleanupScenario() {

}
