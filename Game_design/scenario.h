#ifndef SCENARIO_H
#define SCENARIO_H

// local
class TestTorus;
class Sphere;
class Plane;
class Cylinder;
class Cone;
// gmlib
namespace GMlib {

class Scene;
class Camera;
class PointLight;
class DefaultRenderer;
class RenderTarget;


//Object Selection
class DefaultSelectRenderer;
class SceneObject;
template<typename T, int n>
class Point;
template <typename T>
  class PTorus;
  template <typename T>
  class PSphere;
  template <typename T>
  class PPlane;
  template<typename T>
  class PCylinder;
  template<typename T>
  class PCone;

}

// qt
#include <QObject>
#include <QRect>

// stl
#include <iostream>
#include <memory>
#include<queue>


class Scenario: public QObject {
    Q_OBJECT
public:
    explicit Scenario();
    virtual ~Scenario();

    void                                              initialize();
    void                                              deinitialize();
    virtual void                                      initializeScenario();

    void                                              startSimulation();
    void                                              stopSimulation();
    void                                              toggleSimulation();

    void                                              render( const QRect& viewport, GMlib::RenderTarget& target );
    void                                              prepare();
    void                                              replotTestsphere();
    void                                              replotTestCylinder();
    void                                              replotTesttorus();
    void                                              replotTesttorus1();
    void                                              replotTestPlane();
    void                                              insertTorus();
    void                                              insertPlane();
    void                                              insertSphere();
    void                                              insertCone();
    void                                              insertCylinder();
    void                                              replotTesttorusByValue();
    void                                              toggleEditMode(GMlib::SceneObject* _obj);
    void                                              toggleSelectAllObject();
    void                                              deleteSelectedObject(GMlib::SceneObject *_obj);
    void                                              load();
    std::string                                       chooseLoadFile( int choice );
    std::queue<std::shared_ptr<GMlib::SceneObject>>   _sceneObjectQueue;
    void                                              load( int selectedFile );
    bool                                              _GMlibCheck = false;
     bool                                              _doneLevelSix = false;
     bool                                              _doneLevelFive = false;
     bool                                              _doneLevelFour = false;
     bool                                              _doneLevelThree = false;
     bool                                              _doneLevelTwo = false;
     bool                                              _doneLevelOne = false;

     std::vector<double>                               _colorVector;               // Helper variable for loading in material for surfaces
      std::vector<double>                               _movementVector;
      std::vector<std::shared_ptr<GMlib::SceneObject>>  _sceneObjectKeepAliveVector;

    void                                              save();
    void                                              setMaterialForAllObjects();
    void                                              clearScene();
    void                                              scaleSelectedObject(const QPoint& p, const QPoint& c);


    // Object Selection
    GMlib::SceneObject*                               findSceneObject( const QPoint& pos);
    GMlib::SceneObject*                                _sceneObj;

    // Object Selection - helper methods and variables
    void                                              setSelected( GMlib::SceneObject* _obj);

    bool                                              _objSelected = false;
    bool                                              _setEditObject = false;
    GMlib::SceneObject*                               _selectedObject;

    //Move objects

    void                                              moveObject(const QPoint& p, const QPoint& c);
    void                                              rotateObject(const QPoint& p, const QPoint& c);
    //camera movement
    void                                             changeCamPos( char axis);
    void                                        CamTop();
    void                                        CamSide();
    void                                        Camfront();
    void                                        cameraUp();
    void                                        cameraDown();
    void                                        cameraLeft();
    void                                        cameraRight();
    void                                        cameraZoom();
    void                                        cameraUnZoom();
    void                                        cameraZoomScroll(float zvar);
    void                                        lockCameraToObject();
    void                                        rotateCameraByDeg( float angle );
    GMlib::Point<int, 2>                        fromQtToGMlibViewPoint(const GMlib::Camera& cam, const QPoint& pos);
    void                                        moveCamera(const QPoint& p, const QPoint& c);
    void                                        removeLast();
protected:
    void                                              timerEvent(QTimerEvent *e) override;

private:
    std::shared_ptr<GMlib::Scene>                     _scene;
    int                                               _timer_id;

    std::shared_ptr<GMlib::DefaultRenderer>           _renderer { nullptr };
    std::shared_ptr<GMlib::DefaultSelectRenderer>     _select_renderer { nullptr };
    std::shared_ptr<GMlib::Camera>                    _camera   { nullptr };
    QRect                                             _viewport { QRect(0,0,1,1) };

    std::shared_ptr<GMlib::PointLight>                _light;
    std::shared_ptr<TestTorus>                        _testtorus;
    std::shared_ptr<Plane>                            _testplane;
    std::shared_ptr<Sphere>                           _sphere;
    std::shared_ptr<Cylinder>                         _cylinder;
    std::vector<std::shared_ptr<GMlib::SceneObject>>                         _cone;


private:
    static std::unique_ptr<Scenario>                  _instance;
    //saving the file
    void                                              save( std::ofstream& os, const GMlib::SceneObject* obj);
    void                                              saveSO( std::ofstream& os, const GMlib::SceneObject* obj);
    void                                              savePT( std::ofstream& os, const GMlib::PTorus<float>* obj);
    void                                              savePSphere(std::ofstream& os, const GMlib::PSphere<float>* obj);
    void                                              savePCylinder(std::ofstream& os, const GMlib::PCylinder<float>* obj);
public:
    static Scenario&                                  instance();
};

#endif
