#ifndef PLANE_H
#define PLANE_H



#include <parametrics/gmpplane>

#include <memory>

class Plane: public GMlib::PPlane<float>
{
public:
    using PPlane<float>::PPlane;
    //Plane();
    ~Plane() override;
    //void set(const Point<float, _Tp2> &pos, const Vector<float, _Tp2> &dir, const Vector<float, _Tp2> &up);
    void PlaneTest();
protected:
    void localSimulate(double dt) override;


private:
    std::shared_ptr<Plane>     _plane {nullptr};
};

#endif // PLANE_H
