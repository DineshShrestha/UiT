#include "frame.h"

namespace ALLlib {

Frame::Frame() {

    this->setSurroundingSphere(GMlib::Sphere<float, 3>(100.0f));

    // BODY
    auto Top = std::make_shared<GMlib::PPlane<float>>(GMlib::Point<float, 3>(-0.025, -0.025, 0.025),
                                                      GMlib::Vector<float, 3>(0.05, 0, 0),
                                                      GMlib::Vector<float, 3>(0, 0.05, 0));
    Top->toggleDefaultVisualizer();
    Top->replot(1, 1, 1, 1);
    Top->setMaterial(GMlib::GMmaterial::Chrome);
    insert(Top.get());
    _parts.push_back(Top);

    auto Bottom = std::make_shared<GMlib::PPlane<float>>(GMlib::Point<float, 3>(-0.025, -0.025, -0.025),
                                                         GMlib::Vector<float, 3>(0.05, 0, 0),
                                                         GMlib::Vector<float, 3>(0, 0.05, 0));
    Bottom->toggleDefaultVisualizer();
    Bottom->replot(1, 1, 1, 1);
    Bottom->setMaterial(GMlib::GMmaterial::Chrome);
    insert(Bottom.get());
    _parts.push_back(Bottom);

    auto Front = std::make_shared<GMlib::PPlane<float>>(GMlib::Point<float, 3>(-0.025, -0.025, -0.025),
                                                        GMlib::Vector<float, 3>(0.05, 0, 0),
                                                        GMlib::Vector<float, 3>(0, 0, 0.05));
    Front->toggleDefaultVisualizer();
    Front->replot(1, 1, 1, 1);
    Front->setMaterial(GMlib::GMmaterial::Chrome);
    insert(Front.get());
    _parts.push_back(Front);

    auto Back = std::make_shared<GMlib::PPlane<float>>(GMlib::Point<float, 3>(-0.025, 0.025, -0.025),
                                                       GMlib::Vector<float, 3>(0.05, 0, 0),
                                                       GMlib::Vector<float, 3>(0, 0, 0.05));
    Back->toggleDefaultVisualizer();
    Back->replot(1, 1, 1, 1);
    Back->setMaterial(GMlib::GMmaterial::Chrome);
    insert(Back.get());
    _parts.push_back(Back);

    auto Right = std::make_shared<GMlib::PPlane<float>>(GMlib::Point<float, 3>(-0.025, -0.025, -0.025),
                                                        GMlib::Vector<float, 3>(0, 0.05, 0),
                                                        GMlib::Vector<float, 3>(0, 0, 0.05));
    Right->toggleDefaultVisualizer();
    Right->replot(1, 1, 1, 1);
    Right->setMaterial(GMlib::GMmaterial::Chrome);
    insert(Right.get());
    _parts.push_back(Right);

    auto Left = std::make_shared<GMlib::PPlane<float>>(GMlib::Point<float, 3>(0.05, -0.05, -0.05),
                                                       GMlib::Vector<float, 3>(0, 0.05, 0),
                                                       GMlib::Vector<float, 3>(0, 0, 0.05));
    Left->toggleDefaultVisualizer();
    Left->replot(1, 1, 1, 1);
    Left->setMaterial(GMlib::GMmaterial::Chrome);
    insert(Left.get());
    _parts.push_back(Left);


    //cylinder

    auto c1 = std::make_shared<GMlib::PCylinder<float>>(0.004, 0.004, 0.5);
    c1->toggleDefaultVisualizer();
    c1->rotate( GMlib::Angle(90), GMlib::Vector<float,3>(1, 0, 0));
    c1->replot(5, 5, 1, 1);
    c1->setMaterial(GMlib::GMmaterial::Gold);
    insert(c1.get());
    _parts.push_back(c1);

    auto c2 = std::make_shared<GMlib::PCylinder<float>>(0.004, 0.004, 0.5);
    c2->toggleDefaultVisualizer();
    c2->rotate( GMlib::Angle(90), GMlib::Vector<float,3>(0, 1, 0));
    c2->replot(5, 5, 1, 1);
    c2->setMaterial(GMlib::GMmaterial::Gold);
    insert(c2.get());
    _parts.push_back(c2);

    // Motor Parts
    auto motor1 = std::make_shared<MotorPart>();
    motor1->translate(GMlib::Vector<float, 3>(0.25, 0, 0));
    insert(motor1.get());
    _motorParts.push_back(motor1);
    auto motor2 = std::make_shared<MotorPart>(RotorDirection::CCW);
    motor2->translate(GMlib::Vector<float, 3>(0, 0.25, 0));
    insert(motor2.get());
    _motorParts.push_back(motor2);
    auto motor3 = std::make_shared<MotorPart>();
    motor3->translate(GMlib::Vector<float, 3>(-0.25, 0, 0));
    insert(motor3.get());
    _motorParts.push_back(motor3);
    auto motor4 = std::make_shared<MotorPart>(RotorDirection::CCW);
    motor4->translate(GMlib::Vector<float, 3>(0, -0.25, 0));
    insert(motor4.get());
    _motorParts.push_back(motor4);

    assert(_motorParts.size() == 4);

}

Frame::~Frame() {
    _parts.clear();
    _motorParts.clear();

}

std::vector<std::shared_ptr<MotorPart>> Frame::motorParts() const {
    return _motorParts;

}

}
