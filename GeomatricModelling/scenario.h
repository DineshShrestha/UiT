#ifndef SCENARIO_H
#define SCENARIO_H


#include "application/gmlibwrapper.h"

// qt
#include <QObject>


template <typename T>
class firstCurve;

template<typename T>
class firstSubCurve;

template<typename T>
class gerbsCurve;

class Scenario : public GMlibWrapper {
  Q_OBJECT
public:
  using GMlibWrapper::GMlibWrapper;

  void    initializeScenario() override;
  void    cleanupScenario() override;
  void      replotScene();
private:
  std::shared_ptr<firstCurve<float>> _firstcurve;
  std::vector<std::shared_ptr<firstSubCurve<float>>> _subcurve;
  std::shared_ptr<gerbsCurve<float>> _gerbs;
};

#endif // SCENARIO_H
