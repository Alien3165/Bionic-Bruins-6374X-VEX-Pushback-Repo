//Develope Auton.cpp after globals integrates smoothly
#include "auton.h"
#include "globals.h"

void fourBallLeft()
{
	// ---------------------------------------------------------
	//   FOUR BALL AUTON – LEFT SIDE (PUSHBACK)
	//   Starting at left matchloader corner, facing upfield.
	//   Sequence:
	//   1. Collect 3 balls from the left lane
	//   2. Deploy Little Will for final pickup
	//   3. Drive to long goal on left side
	//   4. Back into matchload zone and score
	// ---------------------------------------------------------

	// ----- INITIAL SETUP -----
	chassis.setPose(0, 0, 0);       // Starting pose at left-side matchloader
	intakeBottom.move(127);         // Begin bottom intake to collect balls during movement

	// =====================================================================
	//   PART 1: COLLECT LEFT-LANE 3 BALLS
	// =====================================================================

	chassis.moveToPoint(-5, 35, 2500,
	                    { .maxSpeed = 60 }); // Drive up left lane to gather first 3 balls
	pros::delay(1000);                       // Allow intake time to secure balls

	// Deploy Little Will for improved feeding / ball control
	lW.set_value(true);

	// Pick up the final ball in the cluster
	chassis.moveToPoint(-7, 40, 1000,
	                    { .maxSpeed = 70 });

	// =====================================================================
	//   PART 2: TRANSITION TO LEFT LONG GOAL
	// =====================================================================

	chassis.turnToPoint(-37, 10, 1000);     // Face long goal alignment point
	lW.set_value(false);                    // Retract Little Will before scoring path

	chassis.moveToPoint(-37, 10, 2000,
	                    { .maxSpeed = 80 }); // Drive into scoring lane of long goal

	// =====================================================================
	//   PART 3: SCORE USING MATCHLOAD POSITIONING
	// =====================================================================

	chassis.turnToHeading(-180, 1000);      // Rotate to face downward toward matchloader

	// Back into matchload zone for scoring position
	chassis.moveToPoint(-37, 33, 2000,
	                    { .forwards = false });

	pros::delay(250);                        // Stabilize before scoring

	intakeTop.move(127);                     // Fire balls into long goal
}


void sevenBallLeft()
{
	// ---------------------------------------------------------
	//   SEVEN BALL AUTON – LEFT SIDE (PUSHBACK)
	//   Builds on fourBallLeft() by:
	//   1. Running the full 4-ball routine
	//   2. Transitioning to matchload area
	//   3. Matchloading + scoring 3 additional balls
	// ---------------------------------------------------------

	fourBallLeft();          // Execute the 4-ball autonomous routine
	pros::delay(1000);       // Ensure robot stabilizes after scoring cycle

	// =====================================================================
	//   PART 1: MATCHLOAD SEQUENCE
	// =====================================================================

	lW.set_value(true);      // Deploy Little Will for matchloading alignment
	intakeTop.brake();       // Stop top intake before repositioning

	// Move downward toward matchload collection area
	chassis.moveToPoint(-35, -7, 3000,
	                    { .maxSpeed = 60 }); // (Changing this in future tuning)

	pros::delay(500);        // Allow robot to settle

	// Move back upward into matchload scoring position
	chassis.moveToPoint(-38, 33, 3000,
	                    { .forwards = false, .maxSpeed = 75 });

	pros::delay(750);

	// =====================================================================
	//   PART 2: SCORE MATCHLOADED BALLS
	// =====================================================================

	intakeTop.move(127);     // Fire matchloaded balls into long goal

	pros::delay(1000);
	intakeTop.brake();       // Stop scoring
	intakeBottom.brake();    // Stop intake fully

	// =====================================================================
	//   PROTOTYPE MOTIONS (unused, for future tuning)
	// =====================================================================
	// chassis.moveToPoint(-38, 25, 3000, {.forwards = false, .maxSpeed = 150});
	// chassis.moveToPoint(-38, 30, 3000, {.forwards = false, .maxSpeed = 150});
}

void longMiddleLeftSeven()
{
    // ---------------------------------------------------------
    //   LONG + MIDDLE + MATCHLOAD SEVEN BALL – LEFT SIDE
    //
    //   Autonomous sequence:
    //     1. Collect 3 balls on the left path
    //     2. Score on the Middle Goal
    //     3. Transition to Long Goal area
    //     4. Rotate + reposition for matchload sequence
    //     5. Matchload scoring for final triballs
    //
    //   NOTE: Motion profile visually corresponds to provided map
    // ---------------------------------------------------------

    // =====================================================================
    //   PART 0: INITIAL SETUP
    // =====================================================================

    chassis.setPose(0, 0, 0);      // Set starting pose on left tile
    intakeBottom.move(127);         // Begin bottom intake for first 3-ball sweep


    // =====================================================================
    //   PART 1: COLLECT FIRST 3 BALLS ON LEFT PATH
    // =====================================================================

    // Drive forward toward the first two triballs
    chassis.moveToPoint(-5, 35, 2500,
                        { .maxSpeed = 50 });
    pros::delay(1000);              // Allow intake to finish collecting

    // Deploy Little Will for alignment with final ball
    lW.set_value(true);

    // Small forward offset to secure 3rd ball
    chassis.moveToPoint(-7, 40, 1000,
                        { .maxSpeed = 50 });


    // =====================================================================
    //   PART 2: SCORE COLLECTED BALLS ON MIDDLE GOAL
    // =====================================================================

    // Rotate CPU toward middle goal alignment point
    chassis.turnToPoint(5, 52, 1000,
                        { .forwards = false });

    // Reverse into the middle goal with gentle speed to avoid bounce
    chassis.moveToPoint(5, 52, 1500,
                        { .forwards = false, .maxSpeed = 50 });

    pros::delay(1000);              // Settle before scoring
    intakeTop.move(60);             // Score into Middle Goal
    pros::delay(1000);
    intakeTop.brake();


    // =====================================================================
    //   PART 3: TRANSITION TO LONG GOAL ZONE
    // =====================================================================

    // Drive downward-left toward long goal approach vector
    chassis.moveToPoint(-37, 10, 2000,
                        { .maxSpeed = 60 });

    // Rotate 180° to orient toward matchload area side of the field
    chassis.turnToHeading(-180, 1000);


    // =====================================================================
    //   PART 4: PREP FOR MATCHLOAD + FINAL SCORING SEQUENCE
    // =====================================================================

    lW.set_value(true);         // Re-deploy Little Will for matchload funneling
    intakeTop.brake();          // Ensure top intake is off before repositioning

    // =====================================================================
    //   PART 5: MATCHLOAD PATHING + FINAL THREE BALLS
    // =====================================================================

    // Move down to intake matchloaded balls (entering from front)
    chassis.moveToPoint(-35, -7, 3000,
                        { .forwards = true, .maxSpeed = 60 });
    pros::delay(250);

    // Reverse upward into matchload scoring pocket
    chassis.moveToPoint(-38, 30, 3000,
                        { .forwards = false, .maxSpeed = 75 });

    pros::delay(750);           // Allow settling before firing
    intakeTop.move(127);        // Score matchloaded triballs
}



    // =====================================================================
    //   Nine Ball: Work in Progress
    // =====================================================================

void nineBallLeft()
{
				// Set initial robot pose
		chassis.setPose(0, 0, 0);

		// Start bottom intake
		intakeBottom.move(127);

		// --- Collect the 3 balls ---
		chassis.moveToPoint(-5, 37, 2500, { .maxSpeed = 70 });
		pros::delay(1000);

		// Deploy little will
		lW.set_value(true);

		// Slight adjustment to pick up final ball
		chassis.moveToPoint(-7, 40, 1000, { .maxSpeed = 80});

		lW.set_value(false);

		chassis.turnToHeading(-70, 1000);
		chassis.moveToPoint(-20, 49, 1000, { .maxSpeed = 60 });
		chassis.moveToPoint(-25, 51, 500, { .maxSpeed = 30 });
		pros::delay(1000);
		lW.set_value(true);
		pros::delay(500);
		chassis.moveToPoint(-19, 48, 1500, { .maxSpeed = 50 });
		chassis.moveToPoint(-23, 51, 1500, { .maxSpeed = 60 });

		chassis.moveToPoint(-7, 40, 1000, { .forwards = false });

		// --- Drive to the long goal ---
		chassis.turnToPoint(-34, 10, 500);
		lW.set_value(false);

		chassis.moveToPoint(-34, 10, 1000, { .maxSpeed = 90 });

		// --- Rotate toward matchload zone ---
		chassis.turnToHeading(-180, 500);

		// Back into the matchload
		chassis.moveToPoint(-34, 33, 2000, { .forwards = false });

		pros::delay(250);
		// Run top intake to score
		intakeTop.move(127);


		//Matchload balls
		pros::delay(1750);
		lW.set_value(true);
		intakeTop.brake();
		intakeBottom.move(127);
		chassis.moveToPoint(-34, -9, 2000,{.maxSpeed = 80});
		pros::delay(1000);
		chassis.moveToPoint(-34, 33, 1000, {.forwards = false, .maxSpeed = 75});
		pros::delay(750);
		intakeTop.move(127);

			//Proto
			// chassis.moveToPoint(-38, 25, 3000, {.forwards = false, .maxSpeed = 150});
			// chassis.moveToPoint(-38, 30, 3000, {.forwards = false, .maxSpeed = 150});
}

void fourBallRight()
{
    // ---------------------------------------------------------
    //   FOUR BALL AUTON – RIGHT SIDE (PUSHBACK)
    //   Starting at right matchloader corner, facing upfield.
    //   Sequence:
    //   1. Collect 3 balls from the right lane
    //   2. Deploy Little Will for final pickup
    //   3. Drive to long goal on right side
    //   4. Back into matchload zone and score
    // ---------------------------------------------------------

    // ----- INITIAL SETUP -----
    chassis.setPose(0, 0, 0);       // Starting pose at right-side matchloader
    intakeBottom.move(127);         // Begin bottom intake to collect balls during motion


    // =====================================================================
    //   PART 1: COLLECT RIGHT-LANE 3 BALLS
    // =====================================================================

    // Drive up the right lane to pick up first 3 balls
    chassis.moveToPoint(5, 35, 2500,
                        { .maxSpeed = 60 });
    pros::delay(1000);              // Allow intake to secure all collected balls

    // Deploy Little Will for cleaner intake path
    lW.set_value(true);

    // Pick up the final ball in the top-right cluster
    chassis.moveToPoint(7, 40, 1000,
                        { .maxSpeed = 70 });


    // =====================================================================
    //   PART 2: TRANSITION TO RIGHT LONG GOAL
    // =====================================================================

    chassis.turnToPoint(31, 10, 1000);     // Turn toward long goal alignment point
    lW.set_value(false);                   // Retract Little Will before approach

    chassis.moveToPoint(31, 10, 2000,
                        { .maxSpeed = 80 }); // Drive into long goal scoring lane


    // =====================================================================
    //   PART 3: SCORE USING MATCHLOAD POSITIONING
    // =====================================================================

    chassis.turnToHeading(-180, 1000);      // Rotate to face matchload scoring direction

    // Reverse into matchload zone for scoring position
    chassis.moveToPoint(31, 33, 2000,
                        { .forwards = false });
    pros::delay(250);                        // Stabilize before firing

    intakeTop.move(127);                     // Score balls into long goal
}



 void sevenBallRight()
{
    // ---------------------------------------------------------
    //   SEVEN BALL AUTON – RIGHT SIDE (PUSHBACK)
    //   Builds on fourBallRight() by:
    //   1. Running the full 4-ball right-side routine
    //   2. Transitioning to matchload intake position
    //   3. Matchloading + scoring 3 additional balls
    // ---------------------------------------------------------

    fourBallRight();         // Execute the full right-side 4-ball routine
    pros::delay(1000);       // Allow robot to stabilize after long goal scoring


    // =====================================================================
    //   PART 1: MATCHLOAD SEQUENCE
    // =====================================================================

    lW.set_value(true);      // Deploy Little Will for matchload alignment
    intakeTop.brake();       // Ensure top intake is off before repositioning

    // Move downward toward right-side matchload collection point
    chassis.moveToPoint(29, -7, 3000,
                        { .maxSpeed = 60 });   // (Value to tune later)

    pros::delay(500);        // Let the chassis settle before backing in

    // Reverse upward into matchload scoring pocket
    chassis.moveToPoint(31, 33, 3000,
                        { .forwards = false, .maxSpeed = 75 });

    pros::delay(750);        // Stabilize before firing


    // =====================================================================
    //   PART 2: SCORE MATCHLOADED BALLS
    // =====================================================================

    intakeTop.move(127);     // Fire matchloaded balls into long goal

    pros::delay(1000);
    intakeTop.brake();       // Stop firing
    intakeBottom.brake();    // Stop full intake system
}


// =====================================================================
    //   LongBottomRightSeven: Work in Progress
// =====================================================================
 void longBottomRightSeven() //Work in Progress need aligner
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

		lW.set_value(false);

		//Score on Middle Goal
		chassis.turnToPoint(-3, 46, 1000,{.forwards = true});
		chassis.moveToPoint(-3, 46, 1500, {.forwards=true, .maxSpeed = 50 });
		pros::delay(1000);
		intakeBottom.move(-127);
		pros::delay(1000);
		intakeTop.brake();
	

		// // --- Drive to the long goal ---
		// chassis.moveToPoint(-37, 10, 2000, { .maxSpeed = 60 });
			

		//  // --- Rotate toward matchload zone ---
		//  chassis.turnToHeading(-180, 1000);

		// // // Back into the matchload
		// // chassis.moveToPoint(-35, 33, 2000, { .forwards = false });
		// // pros::delay(500);
		// // // Run top intake to score
		
		// // intakeTop.move(127);

		// //sevenBallLeft();

		// //pros::delay(750);
		// lW.set_value(true);
		// intakeTop.brake();

		// //Sore matchloaded balls
		// chassis.moveToPoint(-35, -7, 3000,{ .forwards = true, .maxSpeed = 60});
		// pros::delay(250);
		// chassis.moveToPoint(-38, 30, 3000, {.forwards = false, .maxSpeed = 75});
		// pros::delay(750);
		// intakeTop.move(127);


 }


// =====================================================================
    //   Nine Ball: Work in Progress
// =====================================================================
void nineBallRight()
{
					// Set initial robot pose
		chassis.setPose(0, 0, 0);

		// Start bottom intake
		intakeBottom.move(127);

		// --- Collect the 3 balls ---
		chassis.moveToPoint(5, 37, 2500, { .maxSpeed = 50 });
		pros::delay(1000);

		// Deploy little will
		lW.set_value(true);

		// Slight adjustment to pick up final ball
		chassis.moveToPoint(7, 40, 1000, { .maxSpeed = 80});

		lW.set_value(false);

		chassis.turnToHeading(-70, 1000);
		chassis.moveToPoint(20, 49, 1000, { .maxSpeed = 40 });
		chassis.moveToPoint(25, 51, 500, { .maxSpeed = 10 });
		pros::delay(1000);
		lW.set_value(true);
		pros::delay(500);
		chassis.moveToPoint(19, 48, 1500, { .maxSpeed = 30 });
		chassis.moveToPoint(23, 51, 1500, { .maxSpeed = 40 });

		chassis.moveToPoint(7, 40, 1000, { .forwards = false });

		// --- Drive to the long goal ---
		chassis.turnToPoint(34, 10, 500);
		lW.set_value(false);

		chassis.moveToPoint(34, 10, 1000, { .maxSpeed = 70 });

		// --- Rotate toward matchload zone ---
		chassis.turnToHeading(-180, 500);

		// Back into the matchload
		chassis.moveToPoint(34, 33, 2000, { .forwards = false });

		pros::delay(250);
		// Run top intake to score
		intakeTop.move(127);


		//Matchload balls
		pros::delay(1750);
		lW.set_value(true);
		intakeTop.brake();
		intakeBottom.move(127);
		chassis.moveToPoint(34, -9, 2000,{.maxSpeed = 60});
		pros::delay(1000);
		chassis.moveToPoint(34, 33, 1000, {.forwards = false, .maxSpeed = 75});
		pros::delay(750);
		intakeTop.move(127);

			//Proto
			// chassis.moveToPoint(-38, 25, 3000, {.forwards = false, .maxSpeed = 150});
			// chassis.moveToPoint(-38, 30, 3000, {.forwards = false, .maxSpeed = 150});

}


// =====================================================================
    //  Solo AWP: Work in Progress
// =====================================================================
void soloAWP()
{
	// ---------------------------------------------------------
	//   SOLO AWP – RED SIDE (PUSHBACK)
	//   Starting at bottom-left matchloader, facing upfield.
	//   Sequence:
	//   1. Right long goal score + matchload using Little Will
	//   2. Collect all 6 lower-center blocks
	//   3. Score on middle goal
	//   4. Transition toward left long goal corridor
	// ---------------------------------------------------------

	// ----- INITIAL SETUP -----
	chassis.setPose(0, 0, 0);       // Starting pose at red matchloader corner
	intakeBottom.move(127);         // Start bottom intake to collect during movement

	// ----- MOVE TOWARD RIGHT LONG GOAL -----
	chassis.moveToPoint(0, 31, 1000, { .maxSpeed = 60 });  // Drive straight up the right lane
	chassis.turnToHeading(90, 700);                        // Face right toward long goal scoring lane

	// ----- MATCHLOAD USING LITTLE WILL -----
	lW.set_value(true);                                      // Deploy Little Will for matchloading
	chassis.moveToPoint(14, 31, 2000, { .forwards = true }); // Move into matchload position

	pros::delay(1000);                                       // Time to feed matchload balls

	// ----- SCORE ON RIGHT LONG GOAL -----
	chassis.moveToPoint(-22, 31, 1000, { .forwards = false }); // Back into long goal to score
	pros::delay(750);

	intakeTop.move(127);                                     // Fire balls into long goal
	pros::delay(500);
	intakeTop.brake();                                       // Stop top intake
	lW.set_value(false);                                     // Retract Little Will

	// =====================================================================
	//   PART 2: COLLECT ALL 6 LOWER CENTER BLOCKS
	// =====================================================================

	chassis.setPose(0, 0, 0);          // Reset odom to eliminate accumulated drift

	chassis.moveToPoint(0, 10, 1000,
	                    { .maxSpeed = 120 }); // Move away from long goal and re-center

	chassis.turnToPoint(18, -7, 1000);         // Face toward first lower-center triple (left side)

	chassis.moveToPoint(18, -7, 1500,
	                    { .forwards = true, .maxSpeed = 100 }); // Collect left 3 blocks
	chassis.waitUntilDone();

	// Sweep across the lower center to collect the remaining 3 blocks
	chassis.turnToHeading(90, 1000);   // Rotate to drive horizontally across center
	chassis.moveToPoint(75, -9, 2000,
	                    { .forwards = true, .maxSpeed = 90 }); // Collect right 3 blocks
	chassis.waitUntilDone();

	// =====================================================================
	//   PART 3: SCORE ON MIDDLE GOAL
	// =====================================================================

	chassis.turnToPoint(59, -24, 500, { .forwards = false }); // Rotate to face middle goal
	chassis.moveToPoint(59, -24, 1000,
	                    { .forwards = false, .maxSpeed = 80 }); // Back into scoring alignment

	intakeTop.move(60);      // Gentle feed to place balls in middle goal
	pros::delay(200);
	intakeTop.brake();

	// =====================================================================
	//   PART 4: TRANSITION TO LEFT LONG GOAL LANE
	// =====================================================================

	chassis.turnToPoint(103, 10, 1000);        // Turn toward left-side long goal lane
	chassis.moveToPoint(103, 10, 2000,
	                    { .forwards = true }); // Drive into corridor between long goal & matchloader

	chassis.turnToHeading(180, 1000);          // Face downfield (toward matchloader) for next action

	//Rest is work in porgress
}
