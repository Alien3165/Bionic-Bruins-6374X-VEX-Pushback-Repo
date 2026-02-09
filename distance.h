#pragma once
#include "main.h"
#include "api.h"
#include "lemlib/api.hpp"

class Distancee {
public:

    // Sensors

    pros::Distance distancer;
    pros::Distance distancel;
    pros::Distance distancef;

    Distancee();

    // Functions
    void resetcoord(int quadrant, int angle, lemlib::Chassis& chassis);
    double mmToIn(double mm);
    double safeRead(pros::Distance& sensor);


private:

};
