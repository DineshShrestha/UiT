#ifndef OBJECT_H
#define OBJECT_H

#include <parametrics/gmpsphere>
#include <scene/gmsceneobject>
 namespace ALLlib {
class Object : public GMlib::PSphere<float> {
     GM_SCENEOBJECT(Object)
    private:
         float _mass;

        float _time_to_live;
        float _time_alive;
       bool _is_expired;
        GMlib::Vector<float, 3> _velocity;
          GMlib::Vector<float, 3> _step;
        const GMlib::Vector<float, 3> _force = GMlib::Vector<float, 3>(0, 0, -0.0981);

     public:
        Object(float size, float mass, GMlib::Vector<float, 3> velocity);
        ~Object();
         GMlib::Vector<float, 3> calculateStep(double dt);
         void setStep(GMlib::Vector<float, 3> step);
         GMlib::Vector<float, 3> getStep() const;
         float getMass() const;
        void setVelocity(GMlib::Vector<float, 3> newVelocity);
         GMlib::Vector<float, 3> getVelocity() const;

        // Used for objects added while running the program
         void setDespawnTime(float lifespan);
        bool isExpired() const;
     protected:
        void localSimulate(double dt) override;

 };
}


#endif // OBJECT_H
