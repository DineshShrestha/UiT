#include "guiapplication.h"

// qt
#include <QOpenGLContext>
#include<QInputEvent>
#include <QDebug>

// stl
#include <iostream>
#include <cassert>



GuiApplication::GuiApplication(int& argc, char **argv) : QGuiApplication(argc, argv) {

    setApplicationDisplayName( "Hello GMlib" );

    connect( &_window, &Window::sceneGraphInitialized,
             this,     &GuiApplication::onSceneGraphInitialized,
             Qt::DirectConnection );

    connect( this, &GuiApplication::signOnSceneGraphInitializedDone,
             this, &GuiApplication::afterOnSceneGraphInitialized );

    connect( &_window, &Window::sceneGraphInvalidated,
             this,     &GuiApplication::onSceneGraphInvalidated,
             Qt::DirectConnection );

    connect( this, &QGuiApplication::lastWindowClosed,
             this, &QGuiApplication::quit );


    connect( &_window, &Window::signKeyPressed,
             this,     &GuiApplication::handleKeyPress );

    connect( &_window, &Window::signWheelEventOccurred,
             this,     &GuiApplication::handleWheelEvents );

    // connect( &_window, &Window::beforeRendering,
    //       this,     &GuiApplication::handleGLInputEvents,
    //  Qt::DirectConnection );

    connect( &_window, &Window::signMousePressed,
             this,&GuiApplication::handleMouseMovementEvents);

    connect( &_window, &Window::signMousePressed,
             this,&GuiApplication::handleMouseButtonPressedEvents);


    connect( &_window, &Window::beforeRendering,
             this,&GuiApplication::handleGLKeyInputEvents,
             Qt::DirectConnection);

    //    connect( &_window, &Window::beforeRendering,
    //             this,&GuiApplication::handleGLInputEventsWithCtrlModifiers,
    //             Qt::DirectConnection);

    //    connect( &_window, &Window::beforeRendering,
    //             this,&GuiApplication::handleGLInputEventsWithShiftModifiers,
    //             Qt::DirectConnection);


    // Object selection
    connect( &_window, &Window::beforeRendering,
             this,&GuiApplication::handleGLMouseInputEvents,
             Qt::DirectConnection);





    _window.setSource(QUrl("qrc:///qml/main.qml"));
    _window.show();
}


GuiApplication::~GuiApplication() {

    _scenario.stopSimulation();

    _window.releasePersistence();
    _window.releaseResources();

    std::cout << "Oh GOD this GMLIB" << std::endl;
}

void
GuiApplication::onSceneGraphInitialized() {

    // Init the scene object and GMlibs OpenGL backend
    _scenario.initialize();

    // Pring surface format
    qDebug() << _window.format();

    // Init a scenario
    _scenario.initializeScenario();
    _scenario.prepare();

    emit signOnSceneGraphInitializedDone();
}

void
GuiApplication::afterOnSceneGraphInitialized() {

    // Start simulator
    _scenario.startSimulation();
}

void GuiApplication::onSceneGraphInvalidated() {

    _scenario.deinitialize();
}





void GuiApplication::handleKeyPress( QKeyEvent* e ) {
    switch (e->key()) {
    case Qt::Key_Q:
        _window.close();
        break;
    //change camera pos h,b,j,n,k,m

    case Qt::Key_H:
        _input_events.push(std::make_shared<QKeyEvent>(*e));
        break;

    case Qt::Key_B:
        _input_events.push(std::make_shared<QKeyEvent>(*e));
        break;


    case Qt::Key_J:
        _input_events.push(std::make_shared<QKeyEvent>(*e));
        break;


    case Qt::Key_N:
        _input_events.push(std::make_shared<QKeyEvent>(*e));
        break;

    case Qt::Key_K:
        _input_events.push(std::make_shared<QKeyEvent>(*e));
        break;

    case Qt::Key_M:
        _input_events.push(std::make_shared<QKeyEvent>(*e));
        break;
    case Qt::Key_R:
        _input_events.push(std::make_shared<QKeyEvent>(*e));
        break;
    case Qt::Key_T:
        _input_events.push(std::make_shared<QKeyEvent>(*e));
        break;
    case Qt::Key_Y:
        _input_events.push(std::make_shared<QKeyEvent>(*e));
        break;

    case Qt::Key_A:
        _input_events.push(std::make_shared<QKeyEvent>(*e));
        break;
    case Qt::Key_E:
        _input_events.push(std::make_shared<QKeyEvent>(*e));
        break;
    case Qt::Key_P:
        _input_events.push(std::make_shared<QKeyEvent>(*e));
        break;
    case Qt::Key_D:
        _input_events.push(std::make_shared<QKeyEvent>(*e));
        break;
    case Qt::Key_S:
        _input_events.push(std::make_shared<QKeyEvent>(*e));
        break;
    case Qt::Key_Up:
        _input_events.push(std::make_shared<QKeyEvent>(*e));
        break;
    case Qt::Key_Down:
        _input_events.push(std::make_shared<QKeyEvent>(*e));
        break;
    case Qt::Key_Left:
        _input_events.push(std::make_shared<QKeyEvent>(*e));
        break;
    case Qt::Key_Right:
        _input_events.push(std::make_shared<QKeyEvent>(*e));
        break;
    case Qt::Key_Z:
        _input_events.push(std::make_shared<QKeyEvent>(*e));
        break;
    case Qt::Key_X:
        _input_events.push(std::make_shared<QKeyEvent>(*e));
        break;
    case Qt::Key_U:
        _input_events.push(std::make_shared<QKeyEvent>(*e));
        break;
    case Qt::ControlModifier:
        _input_events.push(std::make_shared<QKeyEvent>(*e));
        break;
    case Qt::ShiftModifier:
        _input_events.push(std::make_shared<QKeyEvent>(*e));
        break;

    case Qt::Key_1:
        _input_events.push(std::make_shared<QKeyEvent>(*e));
        break;
    case Qt::Key_2:
        _input_events.push(std::make_shared<QKeyEvent>(*e));
        break;
    case Qt::Key_3:
        _input_events.push(std::make_shared<QKeyEvent>(*e));
        break;
    case Qt::Key_4:
        _input_events.push(std::make_shared<QKeyEvent>(*e));
        break;
    case Qt::Key_5:
        _input_events.push(std::make_shared<QKeyEvent>(*e));
        break;
    case Qt::Key_6:
        _input_events.push(std::make_shared<QKeyEvent>(*e));
        break;
    case Qt::Key_7:
        _input_events.push(std::make_shared<QKeyEvent>(*e));
        break;
    case Qt::Key_8:
        _input_events.push(std::make_shared<QKeyEvent>(*e));
        break;
    case Qt::Key_9:
        _input_events.push(std::make_shared<QKeyEvent>(*e));
        break;
    case Qt::Key_Delete:
        _input_events.push(std::make_shared<QKeyEvent>(*e));
        break;
    case Qt::Key_O:
        _input_events.push(std::make_shared<QKeyEvent>(*e));
        break;

    case Qt::Key_V:
        _input_events.push(std::make_shared<QKeyEvent>(*e));
        break;
    case Qt::Key_Space:
        _input_events.push(std::make_shared<QKeyEvent>(*e));
        break;
    default:
        break;
    }

}

void GuiApplication::handleKeyRelease(QKeyEvent *){
    //helloooo
}

void GuiApplication::handleGLKeyInputEvents() {

    while(!_input_events.empty()) {


        const auto& e  = _input_events.front();
        const auto& v =std::dynamic_pointer_cast<const QMouseEvent> (e);
        const auto& ke = std::dynamic_pointer_cast<const QKeyEvent>(e);

        if(e and ke->key() == Qt::Key_R) {
            qDebug() << "Handling the r button";
            _scenario.replotTesttorus();
            _input_events.pop();
        }
        else if(e and ke->key() == Qt::Key_D){
            qDebug() << "Handling the D button";
            _scenario.toggleSimulation();
            _input_events.pop();
        }
        else if(e and ke->key() == Qt::Key_S){
            qDebug() << "Handling the S button";
            _scenario.save();
            _input_events.pop();

        }
        else if(e and ke->key() == Qt::Key_Up){
            qDebug() << "Handling the up button";
            _scenario.cameraUp();
            _input_events.pop();
        }
        else if(e and ke->key() == Qt::Key_Down){
            qDebug() << "Handling the Down button";
            _scenario.cameraDown();
            _input_events.pop();
        }
        else if(e and ke->key() == Qt::Key_Left){
            qDebug() << "Handling the Left button";
            _scenario.cameraLeft();
            _input_events.pop();
        }
        else if(e and ke->key() == Qt::Key_Space){
            qDebug() << "top camera";
            _scenario.Camfront();
            _input_events.pop();
        }
        else if(e and ke->key() == Qt::Key_8){
            qDebug() << "side camera";
            _scenario.CamSide();
            _input_events.pop();
        }
        else if(e and ke->key() == Qt::Key_9){
            qDebug() << "side camera";
            _scenario.CamTop();
            _input_events.pop();
        }

        else if(e and ke->key() == Qt::Key_U){

            _scenario.load(1);

        }

        else if(e and ke->key() == Qt::Key_T){

            _scenario.load(2);

        }

        else if(e and ke->key() == Qt::Key_Y){

            _scenario.load(3);

        }

        else if(e and ke->key() == Qt::Key_Backspace){

            _scenario.removeLast();

        }

        else if(e and ke->key() == Qt::Key_Right){
            qDebug() << "Handling the Right button";
            _scenario.cameraRight();
            _input_events.pop();
        }
        else if(e and ke->key() == Qt::Key_Z){
            qDebug() << "Handling the zoom button";
            _scenario.cameraZoom();
            _input_events.pop();
        }
        else if(e and ke->key() == Qt::Key_X){
            qDebug() << "Handling the Unzoom button";
            _scenario.cameraUnZoom();
            _input_events.pop();
        }
        else if(e and ke->key() == Qt::Key_1) {
            qDebug() <<"Inserting New object to scene mode";
            _scenario.insertTorus();
            _input_events.pop();
        }
        else if(e and ke->key() == Qt::Key_2) {
            qDebug() <<"Inserting Replotted new Torus object to scene mode";
            _scenario.insertSphere();
            _input_events.pop();
        }
        else if(e and ke->key() == Qt::Key_6) {
            qDebug() <<"Inserting Replotted new Torus object to scene mode";
            _scenario.insertCylinder();
            _input_events.pop();
        }
        else if(e and ke->key() == Qt::Key_7) {
            _scenario.insertCone();
            _input_events.pop();
        }
        else if( ke->key() == Qt::Key_V ) {
                      _scenario.setMaterialForAllObjects();
                        _input_events.pop();
                     }
//        else if(e and ke->key() == Qt::Key_7) {
//            qDebug() <<"Inserting Replotted new Torus object to scene mode";
//            _scenario.insertPlane();
//            _input_events.pop();
//        }
        else if(e and ke->key() == Qt::Key_3) {
            qDebug() <<"Inserting Replotted by value new Torus object to scene mode";
            //_scenario.replotTesttorusByValue();
            _scenario.insertPlane();
            _input_events.pop();
        }
        else if(e and ke->key() == Qt::Key_4) {
            qDebug() <<"Inserting New sphere to scene mode";

            //_scenario.replotTesttorusByValue();
            _scenario.replotTesttorusByValue();
            _input_events.pop();
        }
        else if(e and ke->key() == Qt::Key_5) {
            _scenario.replotTesttorus();
            _input_events.pop();
        }
        else if(e and ke->key() == Qt::Key_S) {
            qDebug() <<"Entering saving mode";
            _scenario.save();
            _input_events.pop();
        }
        else if(ke and ke->key() == Qt::Key_O) {
            qDebug() <<"Entering open mode";
            _scenario.load();
            _input_events.pop();
        }
        //replot
        else if(ke and ke->key() == Qt::Key_P) {

            _scenario.replotTesttorus();
            _input_events.pop();
        }
        else if(ke and ke->key() == Qt::Key_A) {

            _scenario.toggleSelectAllObject();
            _input_events.pop();
        }
        //Toggle Edit Mode
        else if(ke and ke->key() == Qt::Key_E) {

            qDebug() << "edit mode selected";

            _scenario.toggleEditMode(_scenario.findSceneObject( _coordinates ) );
            _input_events.pop();
        }

        else if(( ke and ke->key() == Qt::Key_P )&&(ke->modifiers().testFlag(Qt::ControlModifier))) {

            qDebug() << "Quick replot: high";

        }
        else if(( ke and ke->key() == Qt::Key_P )&&(ke->modifiers().testFlag(Qt::ShiftModifier))) {

            qDebug() << "Quick replot: low";

        }
        else if(ke and ke->key() == Qt::Key_Delete  ) {

            _scenario.deleteSelectedObject( _scenario.findSceneObject( _coordinates ) );
            _input_events.pop();

        }


             // changeCamPos()
             else if(ke and ke->key() == Qt::Key_H) {
                 qDebug() << "Handling the H button";
                 _scenario.changeCamPos('x');
             }

             else if(ke and ke->key() == Qt::Key_B) {
                 qDebug() << "Handling the B button";

            _scenario.changeCamPos('X');
             }

             // changeCamPos()
             else if(ke and ke->key() == Qt::Key_J) {
                 qDebug() << "Handling the J button";
                 _scenario.changeCamPos('z');
             }

             else if(ke and ke->key() == Qt::Key_N) {
                 qDebug() << "Handling the N button";
                 _scenario.changeCamPos('Z');

        }

             // changeCamPos()
             else if(ke and ke->key() == Qt::Key_K) {
                 qDebug() << "Handling the D button";
                 _scenario.changeCamPos('y');
             }
             else if(ke and ke->key() == Qt::Key_N) {
                   qDebug() << "Handling the C button";

                _scenario.changeCamPos('Y');

             }


    }
}

void GuiApplication::handleMouseButtonPressedEvents(QMouseEvent *m) {
    //qDebug() << "Rotate object mouse";

    if( m->buttons() == Qt::LeftButton ) {

        if( QGuiApplication::queryKeyboardModifiers().testFlag(Qt::ControlModifier) == true) {

            qDebug() << "Rotate object";
            _endpos ={m->pos().x(), m->pos().y()};
            _scenario.rotateObject(_startpos, _endpos);
            _mouse_input_events.push(std::make_shared<QMouseEvent>(*m));


        }

        else if( QGuiApplication::queryKeyboardModifiers().testFlag(Qt::ShiftModifier) == true) {
            qDebug() << "Move object";
            _leftMousePressed = true;

            _scenario.stopSimulation();
             _startpos = { m->pos().x(), m->pos().y() };
                       _scenario.moveObject(_startpos, _endpos);
                       _mouse_input_events.push( std::make_shared<QMouseEvent>(*m) );

            }

        else {
            // Camera movement
            _leftMousePressed = true;
            _startpos = { m->pos().x(), m->pos().y() };
            _mouse_input_events.push( std::make_shared<QMouseEvent>(*m) );
        }
    }

    if( m->buttons() == Qt::RightButton ) {


        if(  QGuiApplication::queryKeyboardModifiers().testFlag(Qt::ControlModifier) == true ) {

            _scenario.stopSimulation();
            _scenario.lockCameraToObject();
            _mouse_input_events.push(std::make_shared<QMouseEvent>(*m));
            qDebug() << "Lock camera to...";

        }

        else if( QGuiApplication::queryKeyboardModifiers().testFlag(Qt::ShiftModifier) == true) {

            _scenario.toggleSelectAllObject();
            _mouse_input_events.push( std::make_shared<QMouseEvent>(*m) );

        }

        else {
            // Object selection
            _mouse_input_events.push( std::make_shared<QMouseEvent>(*m) );



        }

    }

    else if( m->buttons() == Qt::MiddleButton) {

        qDebug() << "Middle Mouse Button!";

    }

    if( m->buttons() == Qt::LeftButton and QGuiApplication::queryKeyboardModifiers().testFlag(Qt::ShiftModifier)==true and QGuiApplication::queryKeyboardModifiers().testFlag(Qt::AltModifier)==true){
            //_leftMousePressed = true;
            qDebug() << "Going to scale";
            _scenario.scaleSelectedObject( _startpos, _endpos );
            _mouse_input_events.push( std::make_shared<QMouseEvent>(*m) );
            //_mouse_input_events.pop();
        }


}


void GuiApplication::handleMouseMovementEvents(QMouseEvent *m) {

    if( _leftMousePressed == true) {
        //camera movement
        if(_leftMousePressed== true and QGuiApplication::queryKeyboardModifiers().testFlag(Qt::ShiftModifier)==false){

            _endpos = { m->pos().x(), m->pos().y() };


        }
        //object movement
        else if ( _leftMousePressed == true and QGuiApplication::queryKeyboardModifiers().testFlag(Qt::ShiftModifier) == true ) {

            qDebug()<<"Move Object here";
            _endpos = { m->pos().x(), m->pos().y() };
            _scenario.moveObject( _startpos, _endpos );

        }

    }

}

void GuiApplication::handleMouseButtonReleasedEvents(QMouseEvent *m) {

    if( m->type() == QEvent::MouseButtonRelease ) {
        if( QGuiApplication::queryKeyboardModifiers().testFlag(Qt::ShiftModifier) == true) {


            _leftMousePressed = false;
        }
        else _leftMousePressed = false;


    }

}

void GuiApplication::handleWheelEvents(QWheelEvent *w)
{

    if( w->type() == QEvent::Wheel and QGuiApplication::queryKeyboardModifiers().testFlag(Qt::ControlModifier) == true )
    {

        if(w->delta()<0)
        {

            qDebug() << "Pan horizontally left";
            _scenario.cameraLeft();
            _wheel_input_events.push( std::make_shared<QWheelEvent>(*w) );
        }
        else
        {
            qDebug() << "Right Pan";
            _scenario.cameraRight();

        }

    }
    if(w->type()==QEvent::Wheel and QGuiApplication::queryKeyboardModifiers().testFlag(Qt::ShiftModifier) == true )
    {
        if(w->delta()<0)
        {
            qDebug() << "Pan vertically";
            _scenario.cameraUp();
        }

        if (w->delta()>0)
        {
            qDebug() << "Down Pan";
            _scenario.cameraDown();

        }
    }
    if(w->type()==QEvent::Wheel)
    {
        if(w->delta()>0)
        {
            _scenario.cameraZoom();
            _wheel_input_events.push( std::make_shared<QWheelEvent>(*w) );

            qDebug() << "Zoom";
        }

        else
        {
            _scenario.cameraUnZoom();
        _wheel_input_events.push( std::make_shared<QWheelEvent>(*w) );
        }

    }

return;
handleGLMouseInputEvents();
}

void GuiApplication::handleGLMouseInputEvents() {
    while(!_mouse_input_events.empty()) {

        const auto& m = _mouse_input_events.front();
        const auto& me = std::dynamic_pointer_cast<const QMouseEvent>(m);


        if( me->buttons() == Qt::RightButton ) {
            if( QGuiApplication::queryKeyboardModifiers().testFlag(Qt::ShiftModifier) == true) {




            }
            else if( me->buttons() == Qt::RightButton ) {

                // Object selection
                _leftMousePressed=false;

                _coordinates = { me->pos() };

                _scenario.setSelected( _scenario.findSceneObject( _coordinates ) );

            }

        }
        _mouse_input_events.pop();
    }
}




