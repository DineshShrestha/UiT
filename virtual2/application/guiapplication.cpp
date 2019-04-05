#include "guiapplication.h"

// local
#include "window.h"
#include "gmlibwrapper.h"

// hidmanager
#include "../hidmanager/defaulthidmanager.h"
#include "../hidmanager/hidmanagertreemodel.h"

// qt
#include <QQmlContext>
#include <QQuickItem>
#include <QStringListModel>
#include <QOpenGLContext>

// stl
#include <cassert>


std::unique_ptr<GuiApplication> GuiApplication::_instance {nullptr};


GuiApplication::GuiApplication(int& argc, char **argv) : QGuiApplication(argc, argv) {

  assert(!_instance);
  _instance = std::unique_ptr<GuiApplication>(this);


  qRegisterMetaType<HidInputEvent::HidInputParams> ("HidInputEvent::HidInputParams");

  connect( &_window, &Window::sceneGraphInitialized,
           this,     &GuiApplication::onSceneGraphInitialized,
           Qt::DirectConnection );

  connect( &_window, &Window::sceneGraphInvalidated,
           this,     &GuiApplication::onSceneGraphInvalidated,
           Qt::DirectConnection );

  connect( this, &GuiApplication::signOnSceneGraphInitializedDone,
           this, &GuiApplication::afterOnSceneGraphInitialized );

  connect( this, &QGuiApplication::lastWindowClosed,
           this, &QGuiApplication::quit );

  _window.rootContext()->setContextProperty( "rc_name_model", &_scenario.rcNameModel() );
  _window.rootContext()->setContextProperty( "hidmanager_model", _hidmanager.getModel() );
  _window.setSource(QUrl("qrc:///qml/main.qml"));

  _window.show();
}

GuiApplication::~GuiApplication() {

  _scenario.stop();
  _window.setPersistentOpenGLContext(false);
  _window.setPersistentSceneGraph(false);
  _window.releaseResources();
  _instance.release();

  qDebug() << "Bye bye ^^, ~~ \"emerge --oneshot life\"";
}

void
GuiApplication::onSceneGraphInitialized() {

  // Print format
  qDebug() << "Surface format: " << QOpenGLContext::currentContext()->format();

  // Init GMlibWrapper
  _scenario.initialize();
  _hidmanager.init(_scenario);
  connect( &_scenario,  &GMlibWrapper::signFrameReady,
           &_window,    &Window::update );

  // Init test scene of the GMlib wrapper
  _scenario.initializeScenario();
  _scenario.prepare();

  emit signOnSceneGraphInitializedDone();
}

void GuiApplication::onSceneGraphInvalidated() {

  _scenario.cleanUp();
}

void
GuiApplication::afterOnSceneGraphInitialized() {

  // Hidmanager setup
  _hidmanager.setupDefaultHidBindings();
  connect( &_window, &Window::signKeyPressed,         &_hidmanager, &StandardHidManager::registerKeyPressEvent );
  connect( &_window, &Window::signKeyReleased,        &_hidmanager, &StandardHidManager::registerKeyReleaseEvent );
  connect( &_window, &Window::signMouseDoubleClicked, &_hidmanager, &StandardHidManager::registerMouseDoubleClickEvent);
  connect( &_window, &Window::signMouseMoved,         &_hidmanager, &StandardHidManager::registerMouseMoveEvent );
  connect( &_window, &Window::signMousePressed,       &_hidmanager, &StandardHidManager::registerMousePressEvent );
  connect( &_window, &Window::signMouseReleased,      &_hidmanager, &StandardHidManager::registerMouseReleaseEvent );
  connect( &_window, &Window::signWheelEventOccurred, &_hidmanager, &StandardHidManager::registerWheelEvent );

  // Handle HID OpenGL actions; needs to have the OGL context bound;
  // QQuickWindow's beforeRendering singnal provides that on a DirectConnection
  connect( &_window, &Window::beforeRendering,        &_hidmanager, &DefaultHidManager::triggerOGLActions,
           Qt::DirectConnection );

  // Register an application close event in the hidmanager;
  // the QWindow must be closed instead of the application being quitted,
  // this is to make sure that GL exits gracefully
  QString ha_id_var_close_app =
  _hidmanager.registerHidAction( "Application", "Quit", "Close application!", &_window, SLOT(close()));
  _hidmanager.registerHidMapping( ha_id_var_close_app, new KeyPressInput( Qt::Key_Q, Qt::ControlModifier) );

  // Connect some application spesific inputs.
  connect( &_hidmanager, &DefaultHidManager::signToggleSimulation,
           &_scenario,   &GMlibWrapper::toggleSimulation );

  connect( &_hidmanager,          SIGNAL(signOpenCloseHidHelp()),
           _window.rootObject(),  SIGNAL(toggleHidBindView()) );
  // CONTROLS
   connect( &_hidmanager, &DefaultHidManager::signControlUp,
            &_scenario, &Scenario::controlUp );

   connect( &_hidmanager, &DefaultHidManager::signControlDown,
            &_scenario, &Scenario::controlDown );

   connect( &_hidmanager, &DefaultHidManager::signControlRollLeft,
            &_scenario, &Scenario::controlRollLeft );

   connect( &_hidmanager, &DefaultHidManager::signControlRollRight,
            &_scenario, &Scenario::controlRollRight );

   connect( &_hidmanager, &DefaultHidManager::signControlPitchDown,
            &_scenario, &Scenario::controlPitchDown );

   connect( &_hidmanager, &DefaultHidManager::signControlPitchUp,
            &_scenario, &Scenario::controlPitchUp );

   connect( &_hidmanager, &DefaultHidManager::signControlYawLeft,
            &_scenario, &Scenario::controlYawLeft );

   connect( &_hidmanager, &DefaultHidManager::signControlYawRight,
            &_scenario, &Scenario::controlYawRight );

   connect( &_hidmanager, &DefaultHidManager::signControlPitchStop,
             &_scenario, &Scenario::controlReleasePitch );

    connect( &_hidmanager, &DefaultHidManager::signControlRollStop,
             &_scenario, &Scenario::controlReleaseRoll );

   connect( &_hidmanager, &DefaultHidManager::signControlYawStop,
            &_scenario, &Scenario::controlReleaseYaw );

   connect( &_hidmanager, &DefaultHidManager::signControlHover,
              &_scenario, &Scenario::controlHover );

   auto qml_rootobject = _window.rootObject();

   connect( &_scenario, SIGNAL(signUpdateShipStats(QString)),
            qml_rootobject, SIGNAL(updateShipStats(QString)) );

  // Update RCPair name model
  _scenario.updateRCPairNameModel();

  // Start simulator
  _scenario.start();
}
void GuiApplication::addball(){


}

const GuiApplication& GuiApplication::instance() {  return *_instance; }
