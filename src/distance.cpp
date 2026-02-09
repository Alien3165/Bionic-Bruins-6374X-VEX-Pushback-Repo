#include "main.h"
#include "pros/optical.hpp"
#include "pros/rtos.hpp"
#include "lemlib/api.hpp"
#include "distance.h"

Distancee::Distancee()
  : distancer(6),      
    distancel(5),  // example: ADI port definitions
    distancef(7) 
    {
}



const double FIELD_WIDTH  = 144.0;
const double FIELD_HEIGHT = 144.0;

//to be edited
const double FRONT_OFFSET = 4.5;
const double LEFT_OFFSET  = 6;
const double RIGHT_OFFSET = 6;



double Distancee::mmToIn(double mm) { 
    return mm / 25.4; 
}

double Distancee::safeRead(pros::Distance& sensor) {
    int raw = sensor.get();

    // Reject invalid mm readings
    if (raw <= 0 || raw > 3000) return -1;

    double inches = mmToIn(raw);

    // Reject readings under 8 inches
    if (inches < 1) return -1;

    return inches;
}

void Distancee::resetcoord(int quadrant, int angle, lemlib::Chassis& chassis) {
    double front = safeRead(distancef) + FRONT_OFFSET;
    double left  = safeRead(distancel) + LEFT_OFFSET;
    double right = safeRead(distancer) + RIGHT_OFFSET;

    // Default to current pose if a reading is invalid
    lemlib::Pose current = chassis.getPose();
    double xPos = current.x;
    double yPos = current.y;

    double HALF_FIELD = 72;

    bool red = false;
    bool blue = false;
    bool leftd = false;
    bool rightd = false;

    switch (angle)
    {
    case 0:
        blue = true;
        break;
    case 90:
        rightd = true;
        break;
    case 180:
        red = true;
        break;
    case 270:
        leftd = true;
        break;
    default:
        break;
    }

    // QUAD 1

    if (quadrant == 1){
        if(red){
            xPos = (HALF_FIELD - left);
            yPos = (front - HALF_FIELD);

        }
        else if (blue){
            xPos = (HALF_FIELD - right);
            yPos = (HALF_FIELD - front);
        }
        else if (rightd){
            xPos = (HALF_FIELD - front);
            yPos = (HALF_FIELD - left);
        }

        else if (leftd){
            xPos = (front - HALF_FIELD);
            yPos = (HALF_FIELD - right);
        }
    
    }

    // QUAD 2

    if (quadrant == 2){
        if(red){
            xPos = -(HALF_FIELD - right);
            yPos = (front - HALF_FIELD);
        }
        else if (blue){
            xPos = -(HALF_FIELD - left);
            yPos = (HALF_FIELD - front);
        }
        else if (rightd){
            xPos = -(front - HALF_FIELD);
            yPos = (HALF_FIELD - left);
        }

        else if (leftd){
            xPos = -(HALF_FIELD - front);
            yPos = (HALF_FIELD - right);
        }
    
    }

    // QUAD 3

    if (quadrant == 3){
        if(red){
            xPos = -(HALF_FIELD - right);
            yPos = -(HALF_FIELD - front);
        }
        else if (blue){
            xPos = -(HALF_FIELD - left);
            yPos = -(front - HALF_FIELD);
        }
        else if (rightd){
            xPos = -(front - HALF_FIELD);
            yPos = -(HALF_FIELD - right);
        }

        else if (leftd){
            xPos = -(HALF_FIELD - front);
            yPos = -(HALF_FIELD - left);
        }
    
    }

    // QUAD 4

    if (quadrant == 4){
        if(red){
            xPos = (HALF_FIELD - left);
            yPos = -(HALF_FIELD - front);

        }
        else if (blue){
            xPos = (HALF_FIELD - right);
            yPos = -(front - HALF_FIELD);
        }
        else if (rightd){
            xPos = (HALF_FIELD - front);
            yPos = -(HALF_FIELD - right);
        }

        else if (leftd){
            xPos = (front - HALF_FIELD);
            yPos = -(HALF_FIELD - left);
        }
    
    }


    
    chassis.setPose(xPos, yPos, chassis.getPose().theta);
}
