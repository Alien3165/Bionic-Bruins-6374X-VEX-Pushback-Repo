#include "globals.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include <cmath>

// ============================================================================
// Motor Groups
// ============================================================================

// Left motor group: motors on the left side of the drivetrain
pros::MotorGroup left_motor_group({-11, -12, -13}, pros::MotorGears::blue);

// Right motor group: motors on the right side of the drivetrain
pros::MotorGroup right_motor_group({18, 19, 20}, pros::MotorGears::blue);

// ============================================================================
// Other Motors
// ============================================================================

// Bottom and top intake motors
pros::Motor intakeBottom(16, pros::MotorGearset::blue);
pros::Motor intakeTop(17, pros::MotorGearset::blue);

// ============================================================================
// Pneumatics
// ============================================================================

// Pneumatic actuators for mechanisms (Little Will and Doinker)
pros::adi::DigitalOut lW(1);
pros::adi::DigitalOut lB(3);

// ============================================================================
// IMU and Tracking
// ============================================================================

// Inertial Measurement Unit for angular positioning
pros::Imu imu(14);

// Vertical encoder (tracking wheel)
pros::Rotation vertical_encoder(-1);

// Vertical tracking wheel for odometry
lemlib::TrackingWheel vertical_tracking_wheel(&vertical_encoder, lemlib::Omniwheel::NEW_2, -2.5);

// ============================================================================
// Drivetrain and Odometry
// ============================================================================

// Drivetrain settings
lemlib::Drivetrain drivetrain(
    &left_motor_group,       // left motor group
    &right_motor_group,      // right motor group
    14,                      // 10 inch track width
    lemlib::Omniwheel::NEW_325, // using new 4" omni wheels
    450,                     // drivetrain RPM
    2                        // horizontal drift (adjust as needed)
);

// Odometry sensor configuration
lemlib::OdomSensors sensors(
    &vertical_tracking_wheel, // vertical tracking wheel
    nullptr,                  // vertical tracking wheel 2 (not used)
    nullptr,                  // horizontal tracking wheel 1 (not used)
    nullptr,                  // horizontal tracking wheel 2 (not used)
    &imu                      // inertial sensor
);

// ============================================================================
// PID Controllers
// ============================================================================

// Lateral PID controller for straight-line movement
lemlib::ControllerSettings lateral_controller(
    12, // proportional gain (kP)
    0,  // integral gain (kI)
    36, // derivative gain (kD)
    0,  // anti windup
    0,  // small error range (inches)
    0,  // small error range timeout (ms)
    0,  // large error range (inches)
    0,  // large error range timeout (ms)
    0   // maximum acceleration (slew)
);

// Angular PID controller for rotation
lemlib::ControllerSettings angular_controller(
    2,    // proportional gain (kP)
    0,    // integral gain (kI)
    10,   // derivative gain (kD)
    3,    // anti windup
    1,    // small error range (inches)
    100,  // small error range timeout (ms)
    3,    // large error range (inches)
    500,  // large error range timeout (ms)
    0     // maximum acceleration (slew)
);

// ============================================================================
// Chassis
// ============================================================================

// Create the chassis object that combines drivetrain, PID controllers, and sensors
lemlib::Chassis chassis(
    drivetrain,         // drivetrain settings
    lateral_controller, // lateral PID controller
    angular_controller, // angular PID controller
    sensors             // odometry sensors
);
