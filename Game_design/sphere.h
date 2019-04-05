#ifndef SPHERE_H
#define SPHERE_H


#include <parametrics/gmpsphere>

#include <memory.h>

class Sphere : public GMlib::PSphere<float>
{
public:
    using PSphere::PSphere;

    ~Sphere() override;

    //void TestSphere();
protected:
  void localSimulate(double dt) override;

private:
    std::unique_ptr<Sphere>     _sphere {nullptr};
};


#endif // SPHERE_H
