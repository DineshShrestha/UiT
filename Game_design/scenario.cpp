#include "scenario.h"
#include "testtorus.h"
#include "sphere.h"
#include"cylinder.h"
#include"plane.h"
// gmlib
#include <gmOpenglModule>
#include <gmSceneModule>
#include <gmParametricsModule>
#include "gmlibsceneloader/gmlibsceneloaderdatadescription.h"

#include<QDebug>
// qt
#include <QTimerEvent>

// stl
#include <cassert>

Scenario::Scenario() : QObject(), _timer_id{0}, _select_renderer{nullptr} {

    if(_instance != nullptr) {

        std::cerr << "This version of the Scenario only supports a single instance of the GMlibWraper..." << std::endl;
        std::cerr << "Only one of me(0x" << this << ") please!! ^^" << std::endl;
        assert(!_instance);
        exit(666);
    }

    _instance = std::unique_ptr<Scenario>(this);
}

Scenario::~Scenario() {

    _instance.release();
}

void
Scenario::deinitialize() {

    stopSimulation();

    _scene->remove(_testtorus.get());
    _testtorus.reset();

    _scene->removeLight(_light.get());
    _light.reset();


    _renderer->releaseCamera();
    _scene->removeCamera(_camera.get());

    //object selection
    _select_renderer ->releaseCamera();

    _renderer.reset();
    _camera.reset();

    _scene->clear();
    _scene.reset();

    // Clean up GMlib GL backend
    GMlib::GL::OpenGLManager::cleanUp();
}

void
Scenario::initialize() {

    // Setup and initialized GMlib GL backend
    GMlib::GL::OpenGLManager::init();

    // Setup and init the GMlib GMWindow
    _scene = std::make_shared<GMlib::Scene>();
}

void
Scenario::initializeScenario() {

    // Insert a light
    auto init_light_pos = GMlib::Point<GLfloat,3>( 2.0, 4.0, 10 );
    _light = std::make_shared<GMlib::PointLight>( GMlib::GMcolor::White, GMlib::GMcolor::White,
                                                  GMlib::GMcolor::White, init_light_pos );
    _light->setAttenuation(0.8, 0.002, 0.0008);
    _scene->insertLight( _light.get(), false );



    // Insert Sun
    _scene->insertSun();




    // Default camera parameters
    auto init_viewport_size = 600;
    auto init_cam_pos       = GMlib::Point<float,3>(  0.0f, 0.0f, 0.0f );
    auto init_cam_dir       = GMlib::Vector<float,3>( 0.0f, 1.0f, 0.0f );
    auto init_cam_up        = GMlib::Vector<float,3>(  0.0f, 0.0f, 1.0f );

    // Projection cam
    _renderer = std::make_shared<GMlib::DefaultRenderer>();

    //_select_renderer= std::make_shared<GMlib::DefaultSelectRenderer>();
    _camera = std::make_shared<GMlib::Camera>();
    _renderer->setCamera(_camera.get());

    _camera->set(init_cam_pos,init_cam_dir,init_cam_up);
    _camera->setCuttingPlanes( 1.0f, 8000.0f );
    _camera->rotateGlobal( GMlib::Angle(-45), GMlib::Vector<float,3>( 1.0f, 0.0f, 0.0f ) );
    _camera->translateGlobal( GMlib::Vector<float,3>( 0.0f, -20.0f, 20.0f ) );
    _scene->insertCamera( _camera.get() );
    _renderer->reshape( GMlib::Vector<int,2>(init_viewport_size, init_viewport_size) );



    //Scene object selection

    // Surface
    _testtorus = std::make_shared<TestTorus>();
    _testtorus->toggleDefaultVisualizer();
    _testtorus->replot(100,100,1,1);
    GMlib::Color c1 ( 1, 0, 0);
    GMlib::Color c2 ( 0, 1, 0);
    GMlib::Color c3 ( 0, 0, 1);
    c1.setRed(1.0f);
    c2.setBlue(1.0f);
    c3.setGreen(1.0f);
    double shinyness = 1;

    GMlib::Material mat ( c1, c2, c3, shinyness);
    _testtorus->setMaterial(mat);
    _scene->insert(_testtorus.get());

    _testtorus->test01();

    _testtorus->test02();
}

std::unique_ptr<Scenario> Scenario::_instance {nullptr};

Scenario&
Scenario::instance() { return *_instance; }

void
Scenario::prepare() { _scene->prepare(); }

void
Scenario::render( const QRect& viewport_in, GMlib::RenderTarget& target ) {
    _renderer ->setCamera(_camera.get());
    // Update viewport
    if(_viewport != viewport_in) {

        _viewport = viewport_in;

        const auto& size = _viewport.size();
        _renderer->reshape( GMlib::Vector<int,2>(size.width(),size.height()));
        _camera->reshape( 0, 0, size.width(), size.height() );
    }

    // Render and swap buffers
    _renderer->render(target);
    _renderer->releaseCamera();
}

void
Scenario::startSimulation() {

    if( _timer_id || _scene->isRunning() )
        return;

    _timer_id = startTimer(16, Qt::PreciseTimer);
    _scene->start();
}

void
Scenario::stopSimulation() {

    if( !_timer_id || !_scene->isRunning() )
        return;

    _scene->stop();
    killTimer(_timer_id);
    _timer_id = 0;
}

void
Scenario::timerEvent(QTimerEvent* e) {

    e->accept();

    _scene->simulate();
    prepare();
}


void
Scenario::toggleSimulation() { _scene->toggleRun(); }

void
Scenario::replotTesttorus() {

    _testtorus->replot(4, 4, 1, 1); }


//void
//Scenario::replotTesttorus1() { _testtorus->replot(5, 5, 1, 1); }

void Scenario::replotTesttorusByValue()
{
    _testtorus->toggleDefaultVisualizer();

    GMlib::Color c1 ( 1, 0, 0);
    GMlib::Color c2 ( 0, 1, 0);
    GMlib::Color c3 ( 0, 0, 1);
    c1.setRed(1.0f);
    c2.setBlue(1.0f);
    c3.setGreen(1.0f);
    double shinyness = 1;

    GMlib::Material mat ( c1, c2, c3, shinyness);

    _testtorus->setMaterial(mat);

    _testtorus->replot(200,200,1,1);

}

void Scenario::toggleEditMode(GMlib::SceneObject* _obj)
{
    if( _obj ) {

        if( _objSelected == true and _selectedObject) {
            stopSimulation();
            _setEditObject = true;
            qDebug() << "Object Selected and Entering into Editing Mode";
        }
        else {
            _setEditObject = false;
            qDebug () <<"object not selected";
        }

    }
}

// Editing objects
void
Scenario::setMaterialForAllObjects() {

    if( !_sceneObjectKeepAliveVector.empty() ) {

        GMlib::Color c1 ( 1, 0, 0);
        GMlib::Color c2 ( 0, 1, 0);
        GMlib::Color c3 ( 0, 0, 1);
        double shinyness = 1;

        GMlib::Material mat ( c1, c2, c3, shinyness);

        for( unsigned int i = 0; i < _sceneObjectKeepAliveVector.size(); i++ ) {

            _sceneObjectKeepAliveVector[i]->setMaterial(mat);
        }
    }
}
void Scenario::replotTestsphere()

{
    //std::shared_ptr<GMlib::PSphere<float>> _testsphere = std::make_shared<GMlib::PSphere<float>>();
    _sphere= std::make_shared<Sphere>();
    _sphere->toggleDefaultVisualizer();

    GMlib::Color c1 ( 1, 0, 0);
    GMlib::Color c2 ( 0, 1, 0);
    GMlib::Color c3 ( 0, 0, 1);
    double shinyness = 1;

    GMlib::Material mat ( c1, c2, c3, shinyness);


    _sphere->setMaterial(mat);
    _sphere->setRadius(2);
    _sphere->replot(50, 25, 10, 10);


    //_sceneObjectKeepAliveVector.push_back( sphere );

    _scene->insert(_sphere.get());
}

void Scenario::replotTestCylinder()
{
    _cylinder= std::make_shared<Cylinder>();
    _cylinder->toggleDefaultVisualizer();
    GMlib::Material m(100.0f,0.0f,200.0f,0.0f);
    _cylinder->setMaterial(m);
    _cylinder->setConstants(5.0f,2.0f,6.0f);
    _cylinder->replot(25,12,10,10);
    _scene->insert(_cylinder.get());
}
void Scenario::replotTestPlane()
{
    _testplane= std::make_shared<Plane,float,float,float>(1.5f,0.5f,0.5f);
    _testplane->toggleDefaultVisualizer();
    GMlib::Material m(100.0f,0.0f,200.0f,0.0f);
    _testplane->setMaterial(m);
    _testplane->replot(25,12,10,10);
    _scene->insert(_testplane.get());
}

void Scenario::insertTorus()

{
    _scene->clear();
    _testtorus = std::make_shared<TestTorus>();
    _testtorus->toggleDefaultVisualizer();
    GMlib::Color c1 ( 1, 0, 0);
    GMlib::Color c2 ( 0, 1, 0);
    GMlib::Color c3 ( 0, 0, 1);
    double shinyness = 1;

    GMlib::Material mat ( c1, c2, c3, shinyness);


    _testtorus->replot(100,100,1,1);

    //GMlib::Material m(0.0f,0.0f,1.0f,2.0f);
     _testtorus->setMaterial(mat);
    _scene->insert(_testtorus.get());
}

void Scenario::insertPlane()
{
    qDebug() << "Inserting a plane";
    //_scene->clear();
    _testplane = std::make_shared<Plane,float,float,float>(1.5f,0.5f,0.5f);
    _testplane->toggleDefaultVisualizer();
    _testplane->replot(25, 12, 10, 10);
    GMlib::Material m(0.0f,0.0f,1.0f,2.0f);
    _testplane->setMaterial(m);
    _scene->insert(_testplane.get());
}
void Scenario::insertSphere()
{
    _sphere= std::make_shared<Sphere>();
    _sphere->toggleDefaultVisualizer();
    _sphere->setRadius(2);
    _sphere->replot(25, 12, 10, 10);
    GMlib::Color c1 ( 1, 0, 0);
    GMlib::Color c2 ( 0, 1, 0);
    GMlib::Color c3 ( 0, 0, 1);
    c1.setRed(1.0f);
    c2.setBlue(1.0f);
    c3.setGreen(1.0f);
    double shinyness = 1;

    GMlib::Material mat ( c1, c2, c3, shinyness);
    _sphere->setMaterial(mat);
    _scene->insert(_sphere.get());

}

void Scenario::insertCylinder()
{
    _cylinder= std::make_shared<Cylinder>();
    _cylinder->toggleDefaultVisualizer();
    _cylinder->setConstants(2.0f,2.0f,6.0f);
    _cylinder->replot(50, 50, 10, 10);
    GMlib::Color c1 ( 1, 0, 0);
    GMlib::Color c2 ( 0, 1, 0);
    GMlib::Color c3 ( 0, 0, 1);
    c1.setAlpha(1.0f);
    c2.setBlue(1.0f);
    c3.setGreen(1.0f);
    double shinyness = 1;

    GMlib::Material mat ( c1, c2, c3, shinyness);
    _cylinder->setMaterial(mat);
    _scene->insert(_cylinder.get());
}

void Scenario::insertCone(){
    std::shared_ptr<GMlib::PCone<float>> cone = std::make_shared<GMlib::PCone<float>>();
      cone->toggleDefaultVisualizer();

      GMlib::Color c1 ( 1, 0, 0);
      GMlib::Color c2 ( 0, 1, 0);
      GMlib::Color c3 ( 0, 0, 1);
      c1.setRed(1.0f);
      c2.setBlue(1.0f);
      c3.setGreen(1.0f);

      double shinyness = 1;

      GMlib::Material mat ( c1, c2, c3, shinyness);


      cone->replot(100,100,1,1);

      //GMlib::Material m(0.0f,0.0f,1.0f,2.0f);
       cone->setMaterial(mat);
      _cone.push_back(cone);
      _scene->insert(cone.get());
}


//Object Selection
GMlib::SceneObject* Scenario::findSceneObject(const QPoint &pos){
    if(!_select_renderer)
        _select_renderer =std::make_shared<GMlib::DefaultSelectRenderer>();

    _select_renderer->setCamera(_camera.get());
    {

        /*select_renderer->setCamera(_camera.get());
        {*/
        GMlib::Vector<int,2> size { _viewport.width(), _viewport.height() };
        _select_renderer->reshape( size );
        _select_renderer->prepare();
        _select_renderer->select(0);    // Still GL error

        auto coord = fromQtToGMlibViewPoint(*_camera, pos);

        _sceneObj = _select_renderer->findObject( coord(0), coord(1) );

    }
    _select_renderer->releaseCamera();

    if( _sceneObj != 0) {

        return _sceneObj;
    }

    else return nullptr;

}
void Scenario::setSelected( GMlib::SceneObject* _obj) {

    if( _obj ) {

        if( _objSelected == true and _selectedObject) {

            _selectedObject->setSelected( false );
            _objSelected = false;
        }
        else {

            _selectedObject = _obj;
            _selectedObject->setSelected( true );
            _objSelected = true;
            std::cout <<_selectedObject->getDir() << std::endl;

        }
    }
    else if( _objSelected == true and _obj == 0 ) {
        _selectedObject->setSelected( false );
        _objSelected = false;
    }
}


void Scenario::toggleSelectAllObject()
{

    if ( _selectedObject and _objSelected == true){
        _selectedObject->toggleSelected();
        qDebug() << "No object selected";
    }
}
void Scenario::moveObject(const QPoint &p, const QPoint &c)
{
    if(_selectedObject and _objSelected== true){
        auto previous = fromQtToGMlibViewPoint(*_camera.get(), p);
        auto current = fromQtToGMlibViewPoint(*_camera.get(),c);

        auto tmp = previous -current;
        GMlib::Vector<float, 3> d(tmp(0), tmp(1),0);
        d= d*0.0001;

        _selectedObject->translateGlobal(d,true);
    }
    else
        qDebug()<<"object not selected";
}

void Scenario::rotateObject(const QPoint &p, const QPoint &c)
{
    if( _selectedObject and _objSelected == true ) {
        auto previous       = fromQtToGMlibViewPoint(*_camera.get(), p);
        auto current        = fromQtToGMlibViewPoint(*_camera.get(), c);
        auto tmp = previous - current;
        // Compute rotation axis and angle in respect to the camera and view.
        const GMlib::UnitVector<float,3> rot_v =
                float( tmp(0) ) * _camera->getUp() -
                float( tmp(1) ) * _camera->getSide();
        const GMlib::Angle ang(
                    M_2PI * sqrt(
                        pow( double( tmp(0) ) / _camera->getViewportW(), 2 ) +
                        pow( double( tmp(1) ) / _camera->getViewportH(), 2 ) ) );

        _selectedObject->rotateGlobal( ang, rot_v);
        qDebug() <<"Rotating selected object in scenario";

    }

}


void Scenario::deleteSelectedObject(GMlib::SceneObject *_obj)
{
    if( _obj ) {

        if( _objSelected == true and _selectedObject and _setEditObject==true) {

            //_sceneObj->remove(_obj);
            _sceneObj->setVisible(false,0);

            qDebug() <<"Selected Object removed";
            _setEditObject=false;
        }
        else {

            qDebug () <<"Edit Mode not activated or object not selected";
        }
    }
}

// Camera movement

void   Scenario::moveCamera(const QPoint& c, const QPoint& p) {
    auto previous       = fromQtToGMlibViewPoint(*_camera.get(), p);
    auto current        = fromQtToGMlibViewPoint(*_camera.get(), c);
    auto tmp = previous - current;
    GMlib::Vector<float,2> d (tmp(0),-tmp(1) ); // Negativ for Ã¥ fÃ¥ rett "inverted y"
    d = d * 0.01;
    _camera->move(d);


}

void Scenario::removeLast()
{
    if( !_sceneObjectKeepAliveVector.empty() ) {

          qDebug() << "Clearing the last inserted object from the scene";
          auto o = _sceneObjectKeepAliveVector.back();
          _scene->remove( o.get() );
          _sceneObjectKeepAliveVector.pop_back();
      }
      else qDebug() << "No object to remove";
}
// Camera movement
float x_pos = 0.0f;
float y_pos = -20.0f;
float z_pos = 0.0f;
float pos_change = 1.0f;
void
Scenario::changeCamPos(char axis) {



    if (axis == 'x') {
        x_pos += pos_change;
    }

    else if (axis == 'y') {
        y_pos += pos_change;
    }

    else if (axis == 'z') {
        z_pos += pos_change;
    }

    else if (axis == 'X') {
        x_pos -= pos_change;
    }

    else if (axis == 'Y') {
        y_pos -= pos_change;
    }

    else if (axis == 'Z') {
        z_pos -= pos_change;
    }

    else {
        qDebug() << "what is wrong";
    }

    auto new_cam_pos = GMlib::Point<float,3>(  x_pos, y_pos, z_pos );

    _camera->set (
                new_cam_pos,
                GMlib::Vector<float,3>( 0.0f, 1.0f, 0.0f ),
                GMlib::Vector<float,3>( 0.0f, 0.0f, 1.0f ) );
    //qDebug() << "cameraPos (x, y, z): (" << x_pos << "\t" << y_pos << "\t" << z_pos ")";

    qDebug() << "cameraPos\nx\t" << x_pos;
    qDebug() << "y\t" << y_pos;
    qDebug() << "z\t" << z_pos;

}
// Makes a point for camera movement

GMlib::Point<int, 2>

Scenario::fromQtToGMlibViewPoint(const GMlib::Camera& cam, const QPoint& pos) {
    int h = cam.getViewportH(); // Height of the camera's viewport



    // QPoint

    int q1 {pos.x()};
    int q2 {pos.y()};



    // GMlib Point

    int p1 = q1;
    int p2 = h - q2 - 1;
    return GMlib::Point<int, 2> {p1, p2};

}

void Scenario::save(std::ofstream &os, const GMlib::SceneObject *obj)
{
    auto cam_obj = dynamic_cast<const GMlib::Camera*>(obj);
    if(cam_obj) return;


    os << obj->getIdentity() << std::endl
       << "{" << std::endl << std::endl;

    saveSO(os,obj);

    auto ptorus_obj = dynamic_cast<const GMlib::PTorus<float>*>(obj);
    if(ptorus_obj)
        savePT(os,ptorus_obj);

    const auto& children = obj->getChildren();
    for(auto i = 0; i < children.getSize(); ++i )
        save(os,children(i));

    os << "}"
       << std::endl;

}

void Scenario::saveSO(std::ofstream &os, const GMlib::SceneObject *obj)
{
    os << "SceneObjectData" << std::endl
       << "{" << std::endl <<std::endl;
    os << "Set" << std::endl;

    os << "setCollapsed{ bool {"
       << "" << (obj->isCollapsed()?"true":"false")
       << "} }"<<std::endl<<std::endl;
    os << "setLighted{ bool {"
       << "" << (obj->isLighted()?"true":"false")
       << "} }"<<std::endl<<std::endl;
    os << "setVisible{ bool {"
       << "" << (obj->isVisible()?"true":"false")
       << "} }"<<std::endl<<std::endl;
    os << "}"<<std::endl;
    os << "}"
       << std::endl <<std::endl;
    os << "  setMaterial \n";
        os << "  { \n";
        os << "      Material \n";
        os << "      { \n";
        os << "          Color { double { " << static_cast<int>( obj->getMaterial().getAmb().getRedC() ) << ", " << static_cast<int>( obj->getMaterial().getAmb().getGreenC() ) << ", " << static_cast<int>( obj->getMaterial().getAmb().getBlueC() ) << " } }\n";
        os << "          Color { double { " << static_cast<int>( obj->getMaterial().getDif().getRedC() ) << ", " << static_cast<int>( obj->getMaterial().getDif().getGreenC() ) << ", " << static_cast<int>( obj->getMaterial().getDif().getBlueC() ) << " } }\n";
        os << "          Color { double { " << static_cast<int>( obj->getMaterial().getSpc().getRedC() ) << ", " << static_cast<int>( obj->getMaterial().getSpc().getGreenC() ) << ", " << static_cast<int>( obj->getMaterial().getSpc().getBlueC() ) << " } }\n";
        os << "          double { " << static_cast<int>( obj->getMaterial().getShininess() ) << " } \n";
        os << "      } \n";
        os << "  } \n";
    os << "  setPosition \n";
          os << "  { \n";
          os << "      double { " << (obj->getPos()(0)) << ", " << (obj->getPos()(1)) << ", " << (obj->getPos()(2)) << "} \n";
          os << "  } \n";
          os << "} \n";

}

void Scenario::savePT(std::ofstream &os, const GMlib::PTorus<float> *obj)
{
    os << "PTorusData" << std::endl
       << "{" << std::endl;

    os <<"setTubeRadius1 { "<<std::endl;
    os <<"setTubeRadius2 { "<<std::endl;
    os <<"setWheelRadius { "<<std::endl;
    os << "}" <<std::endl
       << std::endl;

}

void Scenario::savePSphere(std::ofstream &os, const GMlib::PSphere<float> *obj)
{
    os << "PSphereData" << std::endl     // Start of data for PSphere
       << "{" << std::endl;

    os << "}" << std::endl;             // End of data for PSphere
}

void Scenario::savePCylinder(std::ofstream &os, const GMlib::PCylinder<float> *obj)
{
    os << "PCylinderData" << std::endl     // Start of data for PCylinder
       << "{" << std::endl;

    os << "}" << std::endl;             // End of data for PCylinder
}

std::string
Scenario::chooseLoadFile(int choice){
    switch( choice ) {

    case 1:
        return "gmlib_save1.openddl";
        break;
    case 2:
        return "gmlib_save2.openddl";
        break;
    case 3:
        return "gmlib_save3.openddl";
        break;
    default:
        return "gmlib_save.openddl";
    }

}

void  Scenario::save() {
    qDebug()<<"saving the file"<<endl;
    stopSimulation();
    {
        auto filename = std::string("gmlib_save.openddl");

        auto os = std::ofstream(filename,std::ios_base::out);
        if(!os.is_open()) {
            std::cerr << "Unable to open " << filename << " for writing..."
                      << std::endl;
            return;
        }
        os << "GMlibVersion { int32 { 0x"
           << std::setw(6) << std::setfill('0')
           << std::hex << GM_VERSION << " } }" << std::endl;

        for( auto i = 0; i < _scene->getSize(); i++ ) {

            const auto obj = (*_scene)[i];
            save( os, obj );
        }
    }
    startSimulation();
    //save(os,_sceneObj);
}

//clear the scene object
void Scenario::clearScene()
{
    _scene->clear();


}

void Scenario::scaleSelectedObject(const QPoint &p, const QPoint &c)
{
    stopSimulation();

    if( _selectedObject and _objSelected == true ) {

        auto previous       = fromQtToGMlibViewPoint(*_camera.get(), p);
        auto current        = fromQtToGMlibViewPoint(*_camera.get(), c);
        auto tmp = previous - current;
        double dh = _camera->deltaTranslate(_selectedObject);
        const GMlib::Vector<float,3> d
                (dh*(float( tmp(0) ) * _camera->getSide()) +
                 dh*(float( tmp(1) ) * _camera->getUp()));

        _selectedObject->scale( GMlib::Vector<float,3>( 1.0f + d(1) ) );


    }

    else
    {
        qDebug()<<"Cant scale selected object";
        return;
    }



}



void
Scenario::CamTop(){
    auto camPosition=_camera->getPos().getLength();
    auto init_cam_pos = GMlib::Vector<float,3>(camPosition,0.0f,0.0f);
    auto init_cam_dir =GMlib::Vector<float,3>( -1.0f, 0.0f,0.0f ) ;
    auto init_cam_up =GMlib::Vector<float,3>( .0f, .0f,1.0f ) ;
    _camera->set(init_cam_pos,init_cam_dir,init_cam_up);
    _camera->updateCameraOrientation();
}

void Scenario::CamSide()
{
    auto camPosition=_camera->getPos().getLength();
     auto init_cam_pos = GMlib::Vector<float,3>( 0.0f,camPosition ,0.0f) ;
     auto init_cam_dir =GMlib::Vector<float,3>( 0.0f, -1.0f,0.0f ) ;
     auto init_cam_up =GMlib::Vector<float,3>( 0.0f, 0.0f,1.0f ) ;
     _camera->set(init_cam_pos,init_cam_dir,init_cam_up);
     _camera->updateCameraOrientation();
}

void Scenario::Camfront()
{
    auto camPosition=_camera->getPos().getLength();
      auto init_cam_pos = GMlib::Vector<float,3>( 0.0f, 0.0f,camPosition) ;
      auto init_cam_dir =GMlib::Vector<float,3>( 0.0f, 0.0f,-2.0f ) ;
      auto init_cam_up =GMlib::Vector<float,3>( 0.0f, 1.0f,0.0f ) ;
      _camera->set(init_cam_pos,init_cam_dir,init_cam_up);
      _camera->updateCameraOrientation();
}
void Scenario::cameraUp()
{
    _camera->rotateGlobal( GMlib::Angle(-1),GMlib::Vector<float,3>( 1.0f, 1.0f, 0.0f ) );
    qDebug()<<"UP movement"<<endl;
}

void Scenario::cameraDown()
{
    _camera->rotateGlobal( GMlib::Angle(1),GMlib::Vector<float,3>( 1.0f, .0f, 0.0f ) );
    qDebug()<<"Down movement"<<endl;
}

void Scenario::cameraLeft()
{
    _camera->rotateGlobal( GMlib::Angle(-1),GMlib::Vector<float,3>( 0.0f, 1.0f, 0.0f ) );
    qDebug()<<"Left movement"<<endl;
}

void Scenario::cameraRight()
{
    _camera->rotateGlobal( GMlib::Angle(1),GMlib::Vector<float,3>( 0.0f, 1.0f, 0.0f ) );
    qDebug()<<"Right movement"<<endl;
}

void Scenario::cameraZoom()
{
    _camera->translateGlobal( GMlib::Vector<float,3>( 0.0f, 1.0f, -1.0f ) );
    qDebug()<<"Zoom movement"<<endl;
}

void Scenario::cameraUnZoom()
{
    _camera->translateGlobal( GMlib::Vector<float,3>( 0.0f, -1.0f, 1.0f ) );
    qDebug()<<"UnZoom movement"<<endl;
}

void Scenario::cameraZoomScroll(float zvar)
{
    _camera->zoom(zvar);
}

void Scenario::lockCameraToObject()
{
    if( _selectedObject and _objSelected == true)
    {
        qDebug()<<"cannot select object";
        _camera->lock(_selectedObject);
        _camera->deltaTranslate(_selectedObject);
    }
    else
        qDebug()<<"cannot select object";
}


//load saved scene from openddl saved data file
void Scenario::load() {

    qDebug() << "Open scene...";
    stopSimulation();
    Scenario::clearScene();
    {

        auto filename = std::string("gmlib_save.openddl");

        auto is = std::ifstream(filename,std::ios_base::in);
        if(!is.is_open()) {
            std::cerr << "Unable to open " << filename << " for reading..."
                      << std::endl;
            return;
        }

        is.seekg( 0, std::ios_base::end );
        auto buff_length = is.tellg();
        is.seekg( 0, std::ios_base::beg );

        std::vector<char> buffer(buff_length);
        is.read(buffer.data(),buff_length);

        std::cout << "Buffer length: " << buff_length << std::endl;

        GMlibSceneLoaderDataDescription gsdd;

        ODDL::DataResult result = gsdd.ProcessText(buffer.data());
        if(result != ODDL::kDataOkay) {
            std::cerr << "Data result not OK" << std::endl;
            return;
        }
        std::cout << "Data result OK" << std::endl;
        auto numberofelements=0;
        auto structure = gsdd.GetRootStructure()->GetFirstSubnode();
        while(structure) {
            numberofelements++;



            structure = structure->Next();
        }
        std::cout<<"number of main elements:"<<numberofelements<<std::endl;
        // Load GMlib::SceneObjects into the scene.


    } startSimulation();

}

void
Scenario::load( int selectedFile )
{

    stopSimulation();
    {
        auto test = chooseLoadFile(selectedFile);
        std::cout << test << std::endl;

        auto filename = std::string("gmlib_save.openddl");

        auto is = std::ifstream( filename, std::ios_base::in );
        if( !is.is_open()) {

            std::cerr << "Unable to open " << filename << " for reading" << std::endl;

            return;
        }

        is.seekg( 0, std::ios_base::end );
        auto buff_length = is.tellg();
        is.seekg( 0, std::ios_base::beg );

        std::vector<char> buffer( buff_length );
        is.read( buffer.data(), buff_length );

        std::cout << "Buffer length: " << buff_length << std::endl;

        GMlibSceneLoaderDataDescription gsdd;       // ODDL::Structure object

        ODDL::DataResult result = gsdd.ProcessText( buffer.data() );

        // Error help
        auto b = 0xff;
        auto a = 8;

        char c0 = char((( b << (0*a))& result) >> (0*a) );
        char c1 = char((( b << (1*a))& result) >> (1*a) );
        char c2 = char((( b << (2*a))& result) >> (2*a) );
        char c3 = char((( b << (3*a))& result) >> (3*a) );


        if( result != ODDL::kDataOkay ) {

            std::cout << "Data result is not Ok: " << std::endl;
            std::cout << c3 << c2 << c1 << c0 << std::endl;
            return;
        }

        std::cout << "Data result is Ok" << std::endl;

        auto root = gsdd.GetRootStructure();                                    // Start of top layer
        std::cout << root->GetSubnodeCount() << std::endl;
        auto children = root->GetSubnodeCount();
        auto node = root->GetFirstSubnode();
        _doneLevelSix = false;
        _doneLevelFive = false;
        _doneLevelFour = false;
        _doneLevelThree = false;
        _doneLevelTwo = false;
        _doneLevelOne = false;



        // Clear the list over objects in the scene already, and the helper vectors
        if( !_sceneObjectKeepAliveVector.empty() ) {

            _scene->clear();
            _sceneObjectKeepAliveVector.clear();
            _colorVector.clear();
            _movementVector.clear();
        }

        while( !_doneLevelOne )
        {
            std::shared_ptr<GMlib::SceneObject> firstLevelObject = nullptr;   // Creating a sceneobject that will be pushed to a queue later
            for( auto i = 0; i < children; i++) {

                if( node->GetFirstSubnode() ) _doneLevelTwo = false;    // If there are subnodes, then we are not "done" with sublevel 2

                // Do something for level 1 nodes

                if( node->GetStructureType() == int( GMStructTypes::PTorus)) {

                    std::shared_ptr<GMlib::PTorus<float>> torus = std::make_shared<GMlib::PTorus<float>>();
                    torus->toggleDefaultVisualizer();
                    torus->replot(200,200,1,1);
                    firstLevelObject = torus;
                }
                else if( node->GetStructureType() == int( GMStructTypes::PSphere)) {

                    std::shared_ptr<GMlib::PSphere<float>> sphere = std::make_shared<GMlib::PSphere<float>>();
                    sphere->toggleDefaultVisualizer();
                    sphere->replot(50, 50, 10, 10);
                    firstLevelObject = sphere;

                }
                else if( node->GetStructureType() == int( GMStructTypes::PCylinder)) {

                    std::shared_ptr<GMlib::PCylinder<float>> cylinder = std::make_shared<GMlib::PCylinder<float>>();
                    cylinder->toggleDefaultVisualizer();
                    cylinder->replot(50, 50, 10, 10);
                    firstLevelObject = cylinder;

                }
                else if( node->GetStructureType() == int( GMStructTypes::GMlibVersion ) and _GMlibCheck == false )
                {
                    if( node->GetFirstSubnode() ) {
                        auto child = node->GetFirstSubnode();

                        if( child->GetStructureType() == int( ODDL::kDataInt32)) {

                            auto data = static_cast<ODDL::DataStructure<ODDL::Int32DataType>*>(child);
                            std::cout << data << std::endl;

                            if( data->GetDataElement(0) == GM_VERSION) {

                                std::cout << "Valid GMlibVersion" << std::endl;
                                _GMlibCheck = true;

                            }
                            else std::cout << "Non-valid GMlibVersion" << std::endl;

                        }
                        else std::cout << "Not a GMlibVersion node" << std::endl;
                    }
                }


                while( node != nullptr and node->GetFirstSubnode() != nullptr and _doneLevelTwo == false ) {   // First while, checking for sublevel

                    auto secondLevelChildren = node->GetSubnodeCount();             // Start of second layer
                    std::cout << secondLevelChildren << std::endl;
                    node = node->GetFirstSubnode();

                    for( auto j = 0; j < secondLevelChildren; j++) {

                        if( node->GetFirstSubnode() ) _doneLevelThree = false;

                        std::shared_ptr<GMlib::SceneObject> secondLevelObject = nullptr;    // Creating a sceneobjectpointer for a potential second object

                        // Do something for level 2 nodes

                        if( node->GetStructureType() == int( GMStructTypes::PTorus ) ) {

                            std::shared_ptr<GMlib::PTorus<float>> torus = std::make_shared<GMlib::PTorus<float>>();
                            torus->toggleDefaultVisualizer();
                            torus->replot(200,200,1,1);
                            secondLevelObject = torus;
                        }
                        else if( node->GetStructureType() == int( GMStructTypes::PSphere)) {

                            std::shared_ptr<GMlib::PSphere<float>> sphere = std::make_shared<GMlib::PSphere<float>>();
                            sphere->toggleDefaultVisualizer();
                            sphere->replot(50, 50, 10, 10);
                            secondLevelObject = sphere;
                        }
                        else if( node->GetStructureType() == int( GMStructTypes::PCylinder)) {

                            std::shared_ptr<GMlib::PCylinder<float>> cylinder = std::make_shared<GMlib::PCylinder<float>>();
                            cylinder->toggleDefaultVisualizer();
                            cylinder->replot(50, 50, 10, 10);
                            secondLevelObject = cylinder;
                        }
                        // TODO - add check/implementation for constructors

                        while( node != nullptr and node->GetFirstSubnode() != nullptr and _doneLevelThree == false) {   // Second while, checking for sublevel

                            auto thirdLevelChildren = node->GetSubnodeCount();      //Start of third layer
                            std::cout << thirdLevelChildren << std::endl;
                            node = node->GetFirstSubnode();

                            for( auto k = 0; k < thirdLevelChildren; k++ ) {    // Start of 3rd level child nodes

                                if( node->GetFirstSubnode() ) _doneLevelFour = false;

                                // Do something for level 3 nodes, and level 2 checks in case of neste surface
                                if( node->GetStructureType() == int( GMStructTypes::SetCollapsed ) ) {

                                    if( node->GetFirstSubnode() ) {
                                        auto child = node->GetFirstSubnode();
                                        auto data = static_cast<ODDL::DataStructure<ODDL::BoolDataType>*>(child);
                                        auto b = data->GetDataElement(0);
                                        firstLevelObject->setCollapsed( b );
                                    }
                                }
                                else if( node->GetStructureType() == int( GMStructTypes::SetVisible ) ) {

                                    if( node->GetFirstSubnode() ) {
                                        auto child = node->GetFirstSubnode();
                                        auto data = static_cast<ODDL::DataStructure<ODDL::BoolDataType>*>(child);
                                        auto b = data->GetDataElement(0);
                                        firstLevelObject->setVisible( b );
                                    }
                                }
                                else if( node->GetStructureType() == int( GMStructTypes::SetPosition ) ){

                                    if( node->GetFirstSubnode() ) {
                                        auto child = node->GetFirstSubnode();
                                        auto data = static_cast<ODDL::DataStructure<ODDL::DoubleDataType>*>(child);

                                        for( auto i = 0; i < 3; i++ ) {

                                            auto b = data->GetDataElement(i);
                                            _movementVector.push_back(b);
                                        }
                                        if( ! _movementVector.empty() ) {
                                            auto m1 = _movementVector[0];
                                            auto m2 = _movementVector[1];
                                            auto m3 = _movementVector[2];
                                            firstLevelObject->translateGlobal(GMlib::Vector<float,3>(m1, m2, m3));
                                        }

                                        _movementVector.clear();

                                    }
                                }
                                // Other methods not implemented for time but would be similar, others like setMaterial can be handeled further down in the code


                                while( node != nullptr and node->GetFirstSubnode() != nullptr and _doneLevelFour == false) {   // Third while, checking for sublevel

                                    auto fourthLevelChildren = node->GetSubnodeCount();     // Start of fourth layer
                                    std::cout << fourthLevelChildren << std::endl;
                                    node = node->GetFirstSubnode();

                                    for( auto l = 0; l < fourthLevelChildren; l++ ) {   // Start of 4'th level child nodes

                                        if( node->GetFirstSubnode() ) _doneLevelFive = false;

                                        // Do something for level 4 nodes, and level 3 checks in case of neste surface
                                        if( node->GetStructureType() == int( GMStructTypes::SetCollapsed ) ) {

                                            if( node->GetFirstSubnode() ) {
                                                auto child = node->GetFirstSubnode();
                                                auto data = static_cast<ODDL::DataStructure<ODDL::BoolDataType>*>(child);
                                                auto b = data->GetDataElement(0);
                                                secondLevelObject->setCollapsed( b );
                                            }
                                        }
                                        else if( node->GetStructureType() == int( GMStructTypes::SetVisible ) ) {

                                            if( node->GetFirstSubnode() ) {
                                                auto child = node->GetFirstSubnode();
                                                auto data = static_cast<ODDL::DataStructure<ODDL::BoolDataType>*>(child);
                                                auto b = data->GetDataElement(0);
                                                secondLevelObject->setVisible( b );
                                            }
                                        }
                                        else if( node->GetStructureType() == int( GMStructTypes::SetPosition ) ){

                                            if( node->GetFirstSubnode() ) {
                                                auto child = node->GetFirstSubnode();
                                                auto data = static_cast<ODDL::DataStructure<ODDL::DoubleDataType>*>(child);

                                                for( auto i = 0; i < 3; i++ ) {

                                                    auto b = data->GetDataElement(i);
                                                    _movementVector.push_back(b);
                                                }
                                                if( ! _movementVector.empty() ) {
                                                    auto m1 = _movementVector[0];
                                                    auto m2 = _movementVector[1];
                                                    auto m3 = _movementVector[2];
                                                    secondLevelObject->translateGlobal(GMlib::Vector<float,3>(m1, m2, m3));
                                                }

                                                _movementVector.clear();

                                            }
                                        }

                                        while( node != nullptr and node->GetFirstSubnode() != nullptr and _doneLevelFive == false) {      // Fourth while, checking for sublevel

                                            auto fifthLevelChildren = node->GetSubnodeCount();
                                            std::cout << fifthLevelChildren << std::endl;
                                            node = node->GetFirstSubnode();

                                            for( auto m = 0; m < fifthLevelChildren; m++ ) {    // Start of 5'th level child nodes

                                                if( node->GetFirstSubnode() ) _doneLevelSix = false;

                                                // Do something for level 5 nodes
                                                if( node->GetStructureType() == int( GMStructTypes::Color ) ) {

                                                    std::cout << node->GetSubnodeCount() << std::endl;

                                                    while( node->GetStructureType() == int( GMStructTypes::Color ) ) {  // Get all the color values

                                                        auto colornode = node->GetFirstSubnode();   // Down to the "double" values

                                                        auto data = static_cast<ODDL::DataStructure<ODDL::DoubleDataType>*>(colornode);

                                                        for( auto i = 0; i < 3; i++ ) {

                                                            auto b = data->GetDataElement(i);
                                                            _colorVector.push_back(b);
                                                        }

                                                        node = node->Next();
                                                        m++;
                                                    }

                                                    auto dataMaterial = static_cast<ODDL::DataStructure<ODDL::DoubleDataType>*>(node);

                                                    auto shinyness = dataMaterial->GetDataElement(0);
                                                    m++;

                                                    // Get the color values back and make a material

                                                    GMlib::Color c1 (_colorVector[0], _colorVector[1], _colorVector[2]);
                                                    GMlib::Color c2 (_colorVector[3], _colorVector[4], _colorVector[5]);
                                                    GMlib::Color c3 (_colorVector[6], _colorVector[7], _colorVector[8]);

                                                    GMlib::Material mat ( c1, c2, c3, shinyness);

                                                    firstLevelObject->setMaterial( mat );
                                                    _colorVector.clear();

                                                }

                                                while( node != nullptr and node->GetFirstSubnode() != nullptr and _doneLevelSix == false) {    // Fifth while, checking for sublevel

                                                    auto sixthLevelChildren = node->GetSubnodeCount();
                                                    std::cout << sixthLevelChildren << std::endl;
                                                    node = node->GetFirstSubnode();

                                                    for( auto n = 0; n < sixthLevelChildren; n++ ) {    // Start of 6'th level child nodes

                                                        //if( node != nullptr ) _doneLevelSix = false;

                                                        while( node != nullptr and node->GetFirstSubnode() != nullptr ) {    // Sixth level, no more subnodes!

                                                            qDebug() << "Nodes shouldn't have any more subnodes!";
                                                            node = node->GetSuperNode();
                                                            node = node->Next();
                                                        }                           // End of 6'th while

                                                        // Do something for level 6 nodes

                                                        if( _doneLevelSix == false ) {

                                                            std::cout << "Sixth level entries are last!" << std::endl;

                                                            if( node->Next() )  {

                                                                node = node->Next();
                                                            }
                                                            else {
                                                                n++;
                                                                _doneLevelSix = true;
                                                                node = node->GetSuperNode();

                                                                if( node->Next() ) {

                                                                    node = node->Next();

                                                                }
                                                                else {
                                                                    m++;
                                                                    _doneLevelFive = true;
                                                                    node = node->GetSuperNode();

                                                                    if( node->Next() ) {

                                                                        node = node->Next();

                                                                    }
                                                                    else {
                                                                        l++;
                                                                        _doneLevelFour = true;
                                                                        node = node->GetSuperNode();

                                                                        if( node->Next() ) {

                                                                            node = node->Next();

                                                                        }
                                                                        else {
                                                                            k++;
                                                                            _doneLevelThree = true;
                                                                            node = node->GetSuperNode();

                                                                            if( node->Next() ) {

                                                                                node = node->Next();
                                                                            }
                                                                            else {
                                                                                j++;
                                                                                _doneLevelTwo = true;
                                                                                node = node->GetSuperNode(); // Standing at level 1

                                                                                if( node->Next() ) {
                                                                                    // Moves on to the next level 1 subnode
                                                                                    // Not using node->Next() here because it
                                                                                    // makes the code skip a node
                                                                                    i++;
                                                                                }
                                                                                else {
                                                                                    i++;
                                                                                    _doneLevelOne = true;
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }

                                                    }       // End of 6'th level child nodes


                                                }   // End of 5'th while

                                                // Do something for level 5 nodes

                                                if( _doneLevelFive == false ) {

                                                    std::cout << "Fifth level entries are cooler" << std::endl;

                                                    if( node->Next() )  {

                                                        //                                                        node = node->Next();
                                                    }
                                                    else {
                                                        m++;
                                                        _doneLevelFive = true;
                                                        node = node->GetSuperNode();

                                                        if( node->Next() ) {

                                                            //                                                            node = node->Next();

                                                        }
                                                        else {
                                                            l++;
                                                            _doneLevelFour = true;
                                                            node = node->GetSuperNode();

                                                            if( node->Next() ) {

                                                                //                                                                node = node->Next();

                                                            }
                                                            else {
                                                                k++;
                                                                _doneLevelThree = true;
                                                                node = node->GetSuperNode();

                                                                if( node->Next() ) {

                                                                    node = node->Next();

                                                                }
                                                                else {
                                                                    j++;
                                                                    _doneLevelTwo = true;
                                                                    node = node->GetSuperNode(); // Standing at level 1

                                                                    if( node->Next() ) {

                                                                        //                                                                        i++;
                                                                        //                                                                        node = node->Next();
                                                                    }
                                                                    else {
                                                                        i++;
                                                                        _doneLevelOne = true;
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }

                                            }   // End of Fifth level child nodes

                                        }   // End of Fourth while

                                        // Do something for level 4 nodes

                                        if( _doneLevelFour == false ) {

                                            std::cout << "Fourth level entries are cool" << std::endl;

                                            if( node->Next() )  {

                                                node = node->Next();
                                            }
                                            else {
                                                l++;
                                                _doneLevelFour = true;
                                                node = node->GetSuperNode();

                                                if( node->Next() ) {

                                                    //                                                    node = node->Next();

                                                }
                                                else {
                                                    k++;
                                                    _doneLevelThree = true;
                                                    node = node->GetSuperNode();

                                                    if( node->Next() ) {

                                                        //                                                        node = node->Next();

                                                    }
                                                    else {
                                                        j++;
                                                        _doneLevelTwo = true;
                                                        node = node->GetSuperNode();    // Standing at level 1

                                                        if( node->Next() ) {

                                                            //                                                            node = node->Next();
                                                            //                                                            i++;

                                                        }
                                                        else {
                                                            i++;
                                                            _doneLevelOne = true;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }       // End of 4'th level child node
                                }   // End of third while

                                // Do something for level 3 node

                                if( _doneLevelThree == false ) {

                                    std::cout << "Third level entries rule!" << std::endl;

                                    if( node->Next() )  {

                                        node = node->Next();
                                    }
                                    else {
                                        k++;
                                        _doneLevelThree = true;
                                        node = node->GetSuperNode();

                                        if( node->Next() ) {

                                            node = node->Next();

                                        }
                                        else {
                                            j++;
                                            _doneLevelTwo = true;
                                            node = node->GetSuperNode();    // Standing at level 1

                                            if( node->Next() ) {

                                                //                                                i++;
                                                //                                                node = node->Next();

                                            }
                                            else {
                                                i++;
                                                _doneLevelOne = true;

                                            }
                                        }
                                    }
                                }

                            }   // End of 3'rd level child node


                        }   // End of second while

                        // Do something for level 2 nodes

                        _sceneObjectQueue.push( secondLevelObject );

                        if( _doneLevelTwo == false ) {

                            std::cout << "Second level entries representin'!" << std::endl;

                            if( node->Next() )  {

                                node = node->Next();
                            }
                            else {
                                j++;
                                _doneLevelTwo = true;
                                node = node->GetSuperNode();        // Standing at level 1

                                if( node->Next() ) {

                                    //                                    i++;
                                    //node = node->Next();

                                }
                                else {
                                    i++;
                                    _doneLevelOne = true;
                                }
                            }
                        }
                    }       // End of 2'nd order child node

                }   // End of first while

                // Do something for level 1 nodes

                _sceneObjectQueue.push( firstLevelObject );   // Pusing object onto queue
                std::cout << "Top level entries!" << std::endl;

                if( node != nullptr and _doneLevelOne == false ) {            // Next node / Eventual end of top layer

                    if( node->Next() ) node = node->Next();
                    else _doneLevelOne = true;
                }

            }

        }

        std::cout << "Reached the end of the loading loop" << std::endl;

        // Load GMlib::SceneObjects into the scene

        while( !_sceneObjectQueue.empty() ) {

            auto o = _sceneObjectQueue.front();

            if( o != nullptr ) {

                _sceneObjectKeepAliveVector.push_back( o );

                _scene->insert( o.get() );
            }

            _sceneObjectQueue.pop();
        }


    }

    startSimulation();
}
