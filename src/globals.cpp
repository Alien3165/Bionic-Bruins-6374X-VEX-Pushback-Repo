#include "globals.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include <cmath>
// left motor group
pros::MotorGroup left_motor_group({-11, -12, -13}, pros::MotorGears::blue);
// right motor group
pros::MotorGroup right_motor_group({18, 19, 20}, pros::MotorGears::blue);
// drivetrain settings
lemlib::Drivetrain drivetrain(&left_motor_group, // left motor group
                              &right_motor_group, // right motor group
                              14, // 10 inch track width
                              lemlib::Omniwheel::NEW_325, // using new 4" omnis
                              450, // drivetrain    rpm is 360
                              2 // horizontal drift is 2 (for now)
);
pros::Motor intakeBottom(3,pros::MotorGearset::blue);
pros::Motor intakeTop(-2,pros::MotorGearset::blue);

pros::adi::DigitalOut lW(7); 
pros::adi::DigitalOut lB(8);
pros::adi::DigitalOut MD(6);
pros::Imu imu(17);

pros::Rotation horizontal_encoder(-16);
pros::Rotation vertical_encoder(9);

lemlib::TrackingWheel vertical_tracking_wheel(&vertical_encoder, lemlib::Omniwheel::NEW_2, -1);
// lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_encoder, lemlib::Omniwheel::NEW_2, 4);


lemlib::OdomSensors sensors(&vertical_tracking_wheel, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            nullptr,// &horizontal_tracking_wheel // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

lemlib::ControllerSettings lateral_controller(7.5, // proportional gain (kP) 4,38
                                              0, // integral gain (kI)
                                              51, // derivative gain (kD)
                                              0, // a8nti wind5p
                                              1, // small error range, in inches
                                            75, // small error range timeout, in milliseconds
                                              2, // large error range, in inches
                                              150, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);
lemlib::ControllerSettings angular_controller(3.2, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              32, // derivative gain (kD)
                                              0, // anti windup
                                              1, // small error range, in inches
                                              50, // small error range timeout, in milliseconds
                                              2, // large error range, in inches
                                              100, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// create the chassis
lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors // odometry sensors
);
