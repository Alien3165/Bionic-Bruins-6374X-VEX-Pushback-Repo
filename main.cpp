#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}
// left motor group
pros::MotorGroup left_motor_group({-11, -12, -13}, pros::MotorGears::blue);
// right motor group
pros::MotorGroup right_motor_group({18, 19, 20}, pros::MotorGears::blue);

//Other Motors

// drivetrain settings
lemlib::Drivetrain drivetrain(&left_motor_group, // left motor group
                              &right_motor_group, // right motor group
                              14, // 10 inch track width
                              lemlib::Omniwheel::NEW_325, // using new 4" omnis
                              450, // drivetrain rpm is 360
                              2 // horizontal drift is 2 (for now)
);
pros::Motor intakeBottom(16,pros::MotorGearset::blue );
pros::Motor intakeTop(17,pros::MotorGearset::blue);

pros::adi::DigitalOut lW(1);
pros::adi::DigitalOut lB(3);

// imu
pros::Imu imu(14);
pros::Rotation vertical_encoder(-1);
// vertical tracking wheel
lemlib::TrackingWheel vertical_tracking_wheel(&vertical_encoder, lemlib::Omniwheel::NEW_2, -2.5);

// odometry settings
lemlib::OdomSensors sensors(&vertical_tracking_wheel, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            nullptr, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

// lateral PID controller
lemlib::ControllerSettings lateral_controller(12, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              36, // derivative gain (kD)
                                              0, // anti windup
                                              0, // small error range, in inches
                                              0, // small error range timeout, in milliseconds
                                              0, // large error range, in inches
                                              0, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);


// lemlib::ControllerSettings angular_controller(4, // proportional gain (kP)
//                                               0, // integral gain (kI)
//                                               35, // derivative gain (kD)
//                                               0, // anti windup
//                                               0, // small error range, in inches
//                                               0, // small error range timeout, in milliseconds
//                                               0, // large error range, in inches
//                                               0, // large error range timeout, in milliseconds
//                                               0 // maximum acceleration (slew)
// );
lemlib::ControllerSettings angular_controller(2, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              10, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);


// create the chassis
lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors // odometry sensors
);

// initialize function. Runs on program startup
void initialize() {
    pros::lcd::initialize(); // initialize brain screen
    chassis.calibrate(); // calibrate sensors
    // print position to brain screen
    pros::Task screen_task([&]() {
        while (true) {
            // print robot location to the brain screen
            pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
            // delay to save resources
			 // print measurements from the rotation sensor
            pros::delay(20);
        }
    });
}



/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

 
void autonomous() {

	
    chassis.setPose(0, 0, 0);
	//Starts Intake Bottom
	intakeBottom.move(127);

	//Moves to the 3 balls
	chassis.moveToPoint(-5, 35,2500,{.maxSpeed = 50});

	//Moves to the long goal
	chassis.turnToPoint(-35,10,1000);
	chassis.moveToPoint(-35, 10, 2000);
	//Turns to face the matchload
	chassis.turnToHeading(-180, 1000);
	//Moves to the goal
	chassis.moveToPoint(-35, 30, 1500, {.forwards = false});
	pros::delay(500);

	// chassis.moveToPose(-35,10,-180,3000,{.maxSpeed = 60});
	//Intake moves forward
	intakeTop.move(127);
	// pros::delay(1000);
	// lW.set_value(true);
	// intakeTop.brake();
	// pros::delay(500);
	// chassis.moveToPoint(-35, -5, 3000);
	// pros::delay(1000);
	// chassis.moveToPoint(-36, 32, 3000, {.forwards = false});
	// intakeTop.move(127);
	// pros::delay(1000);
	// intakeTop.brake();
	// pros::delay(500);
	// intakeTop.move(127);
	
	//chassis.turnToPoint(-35, 0, 4000, {.forwards = false});

	

	
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
pros::Controller controller(pros::E_CONTROLLER_MASTER);

void opcontrol() {
    // loop forever
	bool state = true;
	bool stateTwo = true;

    while (true) {
        // get left y and right x positions
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

        // move the robot
        chassis.curvature(leftY, rightX);

		
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) { 
			intakeBottom.move(127);
		} 
		else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
			intakeBottom.move(127);
			intakeTop.move(127);
		}
		else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
			intakeBottom.move(-127);
		} else if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
			lW.set_value(state);
			state = !state;
		} else if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
			lB.set_value(stateTwo);
			stateTwo = !stateTwo;
		}else {
			intakeBottom.move(0);
			intakeTop.move(0);
		}

        // delay to save resources
        pros::delay(25);
    }
}