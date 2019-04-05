#ifndef GUIAPPLICATION_H
#define GUIAPPLICATION_H

#include "scenario.h"
#include "window.h"

// qt
#include <QGuiApplication>
#include<QInputEvent>


// stl
#include <memory>
#include <queue>




class GuiApplication : public QGuiApplication {
    Q_OBJECT
public:
    explicit GuiApplication(int& argc, char** argv);
    ~GuiApplication();

private:
    Window                                      _window;
    Scenario                                    _scenario;

    //Mouse--------camera movement
    bool                                        _leftMousePressed;
    QPoint                                      _startpos;
    QPoint                                      _endpos;


    //Object Selection
    QPoint                                      _coordinates;


    std::queue<std::shared_ptr<QInputEvent>>    _input_events;
    std::queue<std::shared_ptr<QInputEvent>>    _mouse_input_events;
    std::queue<std::shared_ptr<QInputEvent>>    _wheel_input_events;


    //Modifiers
    std::queue<std::shared_ptr<QInputEvent>>    _input_events_ctrl_modifier;
    std::queue<std::shared_ptr<QInputEvent>>    _input_events_shift_modifier;


private slots:
    //void                                        handleGLInputEvents();
    void                                        handleKeyPress( QKeyEvent* );
    void                                        handleKeyRelease( QKeyEvent* );
    // void                                        handleGLInputEventsWithCtrlModifiers();
    // void                                        handleGLInputEventsWithShiftModifiers();
    void                                        handleGLKeyInputEvents();
    void                                        handleGLMouseInputEvents();
    virtual void                                onSceneGraphInitialized();
    virtual void                                afterOnSceneGraphInitialized();

    virtual void                                onSceneGraphInvalidated();
    void                                        handleMouseButtonPressedEvents(QMouseEvent *);
    void                                        handleMouseMovementEvents(QMouseEvent *);
    void                                        handleMouseButtonReleasedEvents(QMouseEvent*);
    void                                        handleWheelEvents(QWheelEvent *);


signals:
    void                                        signOnSceneGraphInitializedDone();
};

#endif // GUIAPPLICATION_H
