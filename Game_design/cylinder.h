#ifndef CYLINDER_H
#define CYLINDER_H

#include <parametrics/gmpcylinder>

#include <memory.h>

class Cylinder : public GMlib::PCylinder<float>
{
public:
    using PCylinder::PCylinder;

    ~Cylinder() override;

    //void TestSphere();
protected:
  void localSimulate(double dt) override;

private:
    std::unique_ptr<Cylinder>     _cylinder {nullptr};
};
#endif // CYLINDER_H
