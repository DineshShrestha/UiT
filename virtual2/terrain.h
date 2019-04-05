#ifndef TERRAIN_H
#define TERRAIN_H

#include <gmParametricsModule>

namespace ALLlib {

class Terrain : public GMlib::PSurf<float, 3> {

    GM_SCENEOBJECT(Terrain)

    public:
        Terrain(const GMlib::DMatrix<GMlib::Vector<float, 3>>& points);
    Terrain(const Terrain& copy);
    virtual ~Terrain();


protected:
    GMlib::DMatrix<GMlib::Vector<float, 3>> _points;

    void eval(float u, float v, int d1, int d2, bool lu = true, bool lv = true);
    float getEndPU();
    float getEndPV();
    float getStartPU();
    float getStartPV();
};

}

#endif // TERRAIN_H
