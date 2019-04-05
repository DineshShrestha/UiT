#ifndef DEFAULTHIDMANAGER_H
#define DEFAULTHIDMANAGER_H

#include "standardhidmanager.h"


#include <queue>

// local
class GMlibWrapper;


class DefaultHidManager : public StandardHidManager {
  Q_OBJECT
public:
  explicit DefaultHidManager( QObject* parent = Q_NULLPTR );
  virtual ~DefaultHidManager();

  static const unsigned int   OGL_TRIGGER {8};

  void                        setupDefaultHidBindings();

  void                        init( GMlibWrapper& gmlib );

public slots:
  void                        triggerOGLActions();

protected:
  void                        triggerAction(const HidAction *action, const HidInputEvent::HidInputParams &params) override;

signals:
  void signToggleSimulation();
  void signOpenCloseHidHelp();

  void signControlUp();
  void signControlDown();
  void signControlRollLeft();
  void signControlRollRight();
  void signControlPitchDown();
  void signControlPitchUp();
  void signControlYawLeft();
  void signControlYawRight();
  void signControlPitchStop();
  void signControlRollStop();
  void signControlYawStop();
  void signControlHover();


private slots:
  virtual void                      heDeSelectAllObjects();
  virtual void                      heEdit();
  virtual void                      heLockTo( const HidInputEvent::HidInputParams& params );
  virtual void                      heMoveCamera( const HidInputEvent::HidInputParams& params );
  virtual void                      heMoveSelectedObjects( const HidInputEvent::HidInputParams& params );
  virtual void                      hePanHorizontal( const HidInputEvent::HidInputParams& params );
  virtual void                      hePanVertical( const HidInputEvent::HidInputParams& params );
  virtual void                      heReplotQuick( int factor );
  virtual void                      heReplotQuickHigh();
  virtual void                      heReplotQuickLow();
  virtual void                      heReplotQuickMedium();
  virtual void                      heRotateSelectedObjects( const HidInputEvent::HidInputParams& params );
  virtual void                      heScaleSelectedObjects( const HidInputEvent::HidInputParams& params );
  virtual void                      heSelectAllObjects();
  virtual void                      heSelectObject( const HidInputEvent::HidInputParams& params );
  virtual void                      heSelectObjects( const HidInputEvent::HidInputParams& params );
  virtual void                      heSelectObjectTree( GMlib::SceneObject* obj );
  virtual void                      heToggleObjectDisplayMode();
  virtual void                      heToggleSimulation();
  virtual void                      heToggleSelectAllObjects();
//  virtual void                      heUnlockCamera();
  virtual void                      heZoom( const HidInputEvent::HidInputParams& params );

  virtual void                      heLeftMouseReleaseStuff();
  virtual void                      heOpenCloseHidHelp();

  // controls
    virtual void                      heControlUp();
    virtual void                      heControlDown();
    virtual void                      heControlRollLeft();
    virtual void                      heControlRollRight();
    virtual void                      heControlPitchDown();
    virtual void                      heControlPitchUp();
    virtual void                      heControlYawLeft();
    virtual void                      heControlYawRight();
    virtual void                      heControlPitchStop();
    virtual void                      heControlRollStop();
    virtual void                      heControlYawStop();

    virtual void                      heControlHover();
private:
  GMlib::Camera*                    findCamera( const QString& view_name ) const;
  float                             cameraSpeedScale( GMlib::Camera* cam ) const;
  GMlib::Scene*                     scene() const;
  GMlib::SceneObject*               findSceneObject(const QString& view_name, const GMlib::Point<int,2>& pos);

  GMlib::Point<int,2>               toGMlibViewPoint(const QString& view_name, const QPoint& pos);

  GMlibWrapper*                     _gmlib;

  std::queue<std::pair<const HidAction*,HidInputEvent::HidInputParams>>   _ogl_actions;


};

#endif // DEFAULTHIDMANAGER_H
