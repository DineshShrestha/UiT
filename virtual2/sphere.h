#ifndef SPHERE_H
#define SPHERE_H
#include <parametrics/gmpapple>


class Sphere: public GMlib::PApple<float>{
public:
    using PApple::PApple;
    ~Sphere() override{
        if(m_test01)
            remove(test_01_sphere.get());

    }

    void test01() {

        GMlib::Vector<float,3> d = evaluate(0.0f,0.0f,0,0)[0][0];
        test_01_sphere = std::make_shared<TestTorus,float,float,float>(1.5f,0.5f,0.5f);

        test_01_sphere->translate(d + d.getNormalized()*2.0f);
        test_01_sphere->rotate( GMlib::Angle(90), GMlib::Vector<float,3>( 0.0f, 1.0f, 0.0f) );
        test_01_sphere->toggleDefaultVisualizer();
        test_01_sphere->replot(200,10,1,1);
        insert(test_01_sphere.get());

        m_test01 = true;
    }

protected:
    void localSimulate(double dt) override {

        // rotate( GMlib::Angle(90) * dt, GMlib::Vector<float,3>( 0.0f, 0.0f, 1.0f ) );
        // rotate( GMlib::Angle(180) * dt, GMlib::Vector<float,3>( 1.0f, 1.0f, 0.0f ) );
    }

private:
    bool m_test01 {false};
    std::shared_ptr<TestTorus> test_01_sphere {nullptr};

};
#endif // SPHERE_H
