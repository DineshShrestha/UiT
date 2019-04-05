#ifndef CONE_H
#define CONE_H

#include <parametrics/gmpcone>

#include <memory.h>

class Cone: public GMlib::PCone<float>
{
public:
    using PCone::PCone;

    ~Cone() override;


protected:
    void localSimulate(double dt) override;

private:
    std::unique_ptr<PCone>     _cone {nullptr};
};

#endif // CONE_H
