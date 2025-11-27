//Develope Auton.cpp after globals integrates smoothly
#include "auton.h"
#include "globals.h"

void fourBallLeft()
{
	// Set initial robot pose
chassis.setPose(0, 0, 0);

// Start bottom intake
intakeBottom.move(127);

// --- Collect the 3 balls ---
chassis.moveToPoint(-5, 35, 2500, { .maxSpeed = 50 });
pros::delay(1000);

// Deploy little will
lW.set_value(true);

// Slight adjustment to pick up final ball
chassis.moveToPoint(-7, 40, 1000, { .maxSpeed = 50 });

// --- Drive to the long goal ---
chassis.turnToPoint(-37, 10, 1000);
lW.set_value(false);

chassis.moveToPoint(-37, 10, 2000, { .maxSpeed = 60 });

// --- Rotate toward matchload zone ---
chassis.turnToHeading(-180, 1000);

// Back into the matchload
chassis.moveToPoint(-37, 33, 2000, { .forwards = false });
pros::delay(500);
// Run top intake to score
intakeTop.move(127);


}

void sevenBallLeft()
{
	fourBallLeft();
	pros::delay(2000);
	lW.set_value(true);
	intakeTop.brake();
	chassis.moveToPoint(-35, -7, 3000,{.maxSpeed = 60});
	pros::delay(500);
	chassis.moveToPoint(-38, 30, 3000, {.forwards = false, .maxSpeed = 75});
	pros::delay(750);
	intakeTop.move(127);

	//Proto
	// chassis.moveToPoint(-38, 25, 3000, {.forwards = false, .maxSpeed = 150});
	// chassis.moveToPoint(-38, 30, 3000, {.forwards = false, .maxSpeed = 150});


	
	
}

void longMiddleLeft()
{

		// Set initial robot pose
		chassis.setPose(0, 0, 0);
		// Start bottom intake
		intakeBottom.move(127);

		
		// --- Collect the 3 balls ---
		chassis.moveToPoint(-5, 35, 2500, { .maxSpeed = 50 });
		pros::delay(1000);

		// Deploy little will
		lW.set_value(true);

		// Slight adjustment to pick up final ball
		chassis.moveToPoint(-7, 40, 1000, { .maxSpeed = 50 });

		//Score on Middle Goal
		chassis.turnToPoint(5, 52, 1000,{.forwards = false});
		chassis.moveToPoint(5, 52, 1500, {.forwards=false, .maxSpeed = 50 });
		pros::delay(1000);
		intakeTop.move(80);
		pros::delay(400);
		intakeTop.brake();

		// --- Drive to the long goal ---
		chassis.moveToPoint(-37, 10, 2000, { .maxSpeed = 60 });
			

		 // --- Rotate toward matchload zone ---
		 chassis.turnToHeading(-180, 1000);

		// // Back into the matchload
		// chassis.moveToPoint(-35, 33, 2000, { .forwards = false });
		// pros::delay(500);
		// // Run top intake to score
		
		// intakeTop.move(127);

		//sevenBallLeft();

		// //Proto
		pros::delay(750);
		lW.set_value(true);
		intakeTop.brake();
		chassis.moveToPoint(-35, -7, 3000,{ .forwards = true, .maxSpeed = 60});
		pros::delay(500);
		chassis.moveToPoint(-38, 30, 3000, {.forwards = false, .maxSpeed = 75});
		pros::delay(750);
		intakeTop.move(127);

		

}


void nineBallLeft() // Work in Progress
{
			// Set initial robot pose
	chassis.setPose(0, 0, 0);

	// Start bottom intake
	intakeBottom.move(127);

	// --- Collect the 3 balls ---
	chassis.moveToPoint(-5, 35, 2500, { .maxSpeed = 50 });
	pros::delay(1000);

	// Deploy little will
	lW.set_value(true);

	// Slight adjustment to pick up final ball
	chassis.moveToPoint(-7, 40, 1000, { .maxSpeed = 50 });
	
	// --- Drive to the long goal ---
	chassis.turnToPoint(-27, 51, 1000);
	lW.set_value(false);
	chassis.moveToPoint(-27, 51, 2000, { .maxSpeed = 60 });
	chassis.waitUntilDone();
	lW.set_value(true);


	// --- Rotate toward matchload zone ---
	// Slight adjustment to pick up final ball
	chassis.moveToPoint(-7, 40, 1000, { .forwards=false,.maxSpeed = 50 });

	// --- Drive to the long goal ---
	chassis.turnToPoint(-37, 10, 1000);
	lW.set_value(false);

	chassis.moveToPoint(-37, 10, 2000, { .maxSpeed = 60 });

	// --- Rotate toward matchload zone ---
	chassis.turnToHeading(-180, 1000);

	// Back into the matchload
	chassis.moveToPoint(-37, 33, 2000, { .forwards = false });
	pros::delay(500);
	// Run top intake to score
	intakeTop.move(127);


	//Matchloading(Work in Progress)

	pros::delay(750);
	lW.set_value(true);
	intakeTop.brake();
	chassis.moveToPoint(-35, -7, 3000,{ .forwards = true, .maxSpeed = 60});
	pros::delay(500);
	chassis.moveToPoint(-38, 30, 3000, {.forwards = false, .maxSpeed = 75});
	pros::delay(750);
	intakeTop.move(127);



}
 

void fourBallRight()//Work in Progress
{
		// Set initial robot pose
	chassis.setPose(0, 0, 0);

	// Start bottom intake
	intakeBottom.move(127);

	// --- Collect the 3 balls ---
	chassis.moveToPoint(5, 35, 2500, { .maxSpeed = 50 });
	pros::delay(1000);

	// Deploy little will
	lW.set_value(true);

	// Slight adjustment to pick up final ball
	chassis.moveToPoint(7, 40, 1000, { .maxSpeed = 50 });

	// --- Drive to the long goal ---
	chassis.turnToPoint(37, 10, 1000);
	lW.set_value(false);

	chassis.moveToPoint(37, 10, 2000, { .maxSpeed = 60 });

	// --- Rotate toward matchload zone ---
	chassis.turnToHeading(-180, 1000);

	// Back into the matchload
	chassis.moveToPoint(37, 33, 2000, { .forwards = false });
	pros::delay(500);
	// Run top intake to score
	intakeTop.move(127);
}

