#include "testtorus.h"

TestTorus::~TestTorus() {

  if(_torus) remove(_torus.get());
}

void
TestTorus::test01() {

  if(_torus) return;

  GMlib::Vector<float,3> d = evaluate(0.0f,0.0f,0,0)[0][0];
  _torus = std::make_unique<TestTorus,float,float,float>(1.5f,0.5f,1.5f);
  GMlib::Color c1 ( 1, 0, 0);
  GMlib::Color c2 ( 0, 1, 0);
  GMlib::Color c3 ( 0, 0, 1);
  c1.setRed(1.0f);
  c2.setBlue(1.0f);
  c3.setGreen(1.0f);
  double shinyness = 1;

  GMlib::Material mat ( c1, c2, c3, shinyness);
  _torus->setMaterial(mat);
  _torus->translate(d + d.getNormalized()*2.0f);

  _torus->rotate( GMlib::Angle(90), GMlib::Vector<float,3>( 0.0f, 1.0f, 0.0f) );
  _torus->toggleDefaultVisualizer();
  _torus->replot(200,200,1,1);
  insert(_torus.get());
}

void
TestTorus::test02() {

  if(_torus) return;

  GMlib::Vector<float,3> d = evaluate(0.0f,0.0f,0,0)[0][0];
  _torus = std::make_unique<TestTorus,float,float,float>(1.5f,0.5f,1.5f);

  _torus->translate(d + d.getNormalized()*2.0f);
  _torus->rotate( GMlib::Angle(180), GMlib::Vector<float,3>( 0.0f, 1.0f, 0.0f) );
  _torus->toggleDefaultVisualizer();
  _torus->replot(300,300,1,1);
  insert(_torus.get());
}

void
TestTorus::localSimulate(double dt) {

  rotate( GMlib::Angle(90) * dt, GMlib::Vector<float,3>( 0.0f, 0.0f, 1.0f ) );
  rotate( GMlib::Angle(180) * dt, GMlib::Vector<float,3>( 1.0f, 1.0f, 0.0f ) );
}
