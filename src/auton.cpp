#include "auton.h"
#include "globals.h"
#include "distance.h"

void soloAWP()
{
    /*************************
     * MATCH LOAD SETUP
     *************************/

    // Moving to match load and pointing towards it
    chassis.setPose(0, 0, 0);
    chassis.moveToPoint(0, 28.5, 800, {.maxSpeed = 70, .minSpeed = 60});
    chassis.turnToHeading(90, 500); // Reference heading toward match load (-4,31)


    /*************************
     * MATCH LOAD COLLECTION
     *************************/

    // Moving to match load and collecting balls
    lW.set_value(true);                 // Deploy left wing to guide balls
    intakeBottom.move(127);             // Start bottom intake

    chassis.moveToPoint(13, 28.5, 1000, {.maxSpeed = 70, .minSpeed = 60});
    pros::delay(900);

    // Reverse to finish collecting match load balls
    chassis.moveToPoint(-29, 28.5, 1250, {
        .forwards = false,
        .maxSpeed = 90,
        .minSpeed = 90,
        .earlyExitRange = 1
    });
    pros::delay(600);

    intakeTop.move(127);                // Engage top intake to secure balls
    pros::delay(1100);


    /*************************
     * TRANSITION TO FIELD BALLS
     *************************/

    // Moving back and going to next three balls on the field
    lW.set_value(false);                // Retract wing before moving
    pros::delay(250);

    chassis.moveToPoint(-5, 29, 500, {
        .maxSpeed = 70,
        .minSpeed = 60,
        .earlyExitRange = 1
    });

    intakeTop.move(0);                  // Stop top intake to avoid jamming
    chassis.turnToPoint(-31, 9, 1000, {.maxSpeed = 70, .minSpeed = 60});

    chassis.moveToPoint(-31, 9, 1000, {
        .maxSpeed = 90,
        .minSpeed = 60,
        .earlyExitRange = 1
    });

    // Brake hold test (disabled)
    // Purpose: tested holding position while intaking
    // chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);

    pros::delay(700);
    lW.set_value(true);                 // Redeploy wing for ball control


    /*************************
     * NEXT THREE FIELD BALLS
     *************************/

    // Moving to the next three balls
    chassis.turnToPoint(-32, -40, 500, {
        .maxSpeed = 90,
        .minSpeed = 60,
        .earlyExitRange = 1
    });
    pros::delay(250);

    lW.set_value(false);                // Retract wing before driving through balls

    chassis.moveToPoint(-34, -45, 1500, {
        .maxSpeed = 90,
        .minSpeed = 60,
        .earlyExitRange = 1
    });
    pros::delay(900);

    lW.set_value(true);                 // Enable wing to retain collected balls

    chassis.turnToHeading(126.7, 500);  // Align for reverse approach to middle goal
    chassis.moveToPoint(-48, -31, 1500, {
        .forwards = false,
        .maxSpeed = 70,
        .minSpeed = 60
    });

    // Alternate middle-goal approach (disabled)
    // Purpose: older tuning for reverse alignment
    // chassis.moveToPoint(-45, -26, 1500, {.forwards = false, .maxSpeed = 70, .minSpeed = 60});
    // pros::delay(500);


    /*************************
     * SCORING MIDDLE GOAL
     *************************/

    // Scoring middle goal
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);  // Stabilize robot

    intakeBottom.move(-120);           // Reverse intakes to score
    intakeTop.move(-120);
    pros::delay(500);

    intakeBottom.move(127);            // Resume bottom intake
    intakeTop.move(0);                 // Stop top intake
    pros::delay(2000);

    // Optional intake stop (disabled)
    // Purpose: tested stopping bottom intake after scoring
    // intakeBottom.move(0);


    /*************************
     * PREVIOUS MIDDLE GOAL CODE
     *************************/

    // The following comment below are the previous code for scoring the middle goal
    // Purpose: kept for reference and rollback if needed
    /*
    pros::delay(400);
    intakeTop.move(-80);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
    chassis.waitUntil(13);
    intakeBottom.move(127);
    intakeTop.move(0);
    pros::delay(1200);
    intakeBottom.move(0);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
    */


    /*************************
     * MOVE TO LONG GOAL
     *************************/

    // Moving to long goal
    chassis.moveToPoint(-8, -69, 1000, {.maxSpeed = 70, .minSpeed = 60});
    pros::delay(500);

    // Optional heading correction (disabled)
    // Purpose: tested manual heading alignment
    // chassis.turnToHeading(91, 500);

    // Extra delay test (disabled)
    // pros::delay(200);

    chassis.moveToPose(13, -69, 90, 1200, {.maxSpeed = 70, .minSpeed = 60});
    pros::delay(1500);

    intakeBottom.move(-10);             // Slight reverse intake for alignment

    chassis.moveToPoint(-26, -69, 1000, {
        .forwards = false,
        .maxSpeed = 70,
        .minSpeed = 60
    });
    pros::delay(500);

    intakeTop.move(127);                // Resume full intake
    intakeBottom.move(127);
}

void sevenBallLeft()
{        
    /*************************
     * INITIAL SETUP
     *************************/
    chassis.setPose(0, 0, 0);       // Starting pose at left-side matchloader

    intakeBottom.move(127);         // Start bottom intake immediately


    /*************************
     * FIRST 3 FIELD BALLS
     *************************/

    // Moving to first 3 balls
    chassis.moveToPoint(-2, 27, 1500, {
        .maxSpeed = 90,
        .minSpeed = 90,
        .earlyExitRange = 1
    });
    pros::delay(500);

    lW.set_value(true);             // Deploy left wing for ball control

    chassis.turnToHeading(-110, 500); // Align toward long goal path


    /*************************
     * APPROACH LONG GOAL
     *************************/

    // Moving to long goal
    chassis.moveToPoint(-33, 7, 1350, {
        .minSpeed = 50,
        .earlyExitRange = 1
    });

    // Optional settling delay (disabled)
    // Purpose: tested letting chassis stabilize before backing in
    // pros::delay(75);

    chassis.turnToHeading(180, 500); // Face away from goal for reverse approach


    /*************************
     * MATCH LOADING
     *************************/

    // Match loading
    chassis.moveToPoint(-34, -10, 1000, {
        .maxSpeed = 70,
        .minSpeed = 60
    });
    pros::delay(375);


    /*************************
     * LONG GOAL SCORING
     *************************/

    // Moving to long goal and scoring
    chassis.moveToPoint(-34, 28, 1450, {
        .forwards = false,
        .maxSpeed = 90,
        .minSpeed = 90,
        .earlyExitRange = 1
    }); // 34.5 reference
    pros::delay(775);

    intakeTop.move(127);            // Eject balls into long goal
    pros::delay(1600);

    intakeTop.move(0);              // Stop intakes after scoring
    intakeBottom.move(0);
    lW.set_value(false);             // Retract wing

    // Abandoned reposition attempt (disabled)
    // Purpose: earlier adjustment for post-score alignment
    // chassis.moveToPoint(
    //     -32, 32, 1000, {.minSpeed = 10}
    // );


    /*************************
     * DESCORE + CONTROL ZONE SETUP
     *************************/

    // Descore tech to gain control zone
    chassis.swingToHeading(-120, DriveSide::RIGHT, 700);

    chassis.moveToPose(-43, 12, -180, 800); // Rotate and reposition near control zone

    chassis.moveToPoint(-43, 44, 1000, {
        .forwards = false,
        .maxSpeed = 80
    });


    /*************************
     * OLD PATHING IDEAS (DISABLED)
     *************************/

    // Previous pathing and alignment ideas (kept for reference)
    // chassis.turnToPoint(-25, 26, 800, {.minSpeed = 10});
    // chassis.moveToPoint(-25, 45, 700, {.maxSpeed = 100, .minSpeed = 10});
    // chassis.turnToHeading(35, 1000);
    // lW.set_value(false);


    /*************************
     * END STATE
     *************************/

    // Hold position at end of auton
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
}
void sevenBallRight()
{        
    /*************************
     * INITIAL SETUP
     *************************/
    chassis.setPose(0, 0, 0);       // Starting pose at left-side matchloader

    intakeBottom.move(127);         // Start bottom intake immediately


    /*************************
     * FIRST FIELD BALLS
     *************************/

    // Drive to first ball cluster
    chassis.moveToPoint(2, 27, 1500, {
        .maxSpeed = 90,
        .minSpeed = 90,
        .earlyExitRange = 1
    });
    pros::delay(500);

    lW.set_value(true);             // Deploy left wing for ball control

    chassis.turnToHeading(110, 500); // Align toward long-goal path


    /*************************
     * APPROACH LONG GOAL
     *************************/

    chassis.moveToPoint(28, 7, 1350, {
        .minSpeed = 50,
        .earlyExitRange = 1
    });

    // Optional settling delay (disabled)
    // Purpose: tested letting chassis stabilize before backing in
    // pros::delay(75);

    chassis.turnToHeading(180, 500); // Face away from goal for reverse approach


    /*************************
     * MATCH LOADING
     *************************/

    chassis.moveToPoint(27, -11, 1000, {
        .maxSpeed = 70,
        .minSpeed = 60
    });
    pros::delay(500);


    /*************************
     * LONG GOAL SCORING
     *************************/

    chassis.moveToPoint(27, 31, 1450, {
        .forwards = false,
        .maxSpeed = 90,
        .minSpeed = 90,
        .earlyExitRange = 1
    }); // 34.5 reference
    pros::delay(775);

    intakeTop.move(127);            // Eject balls into long goal
    pros::delay(1600);

    intakeTop.move(0);              // Stop intakes after scoring
    intakeBottom.move(0);
    lW.set_value(false);             // Retract wing

    // Abandoned reposition attempt (disabled)
    // Purpose: earlier adjustment for post-score alignment
    // chassis.moveToPoint(
    //     -32, 32, 1000, {.minSpeed = 10}
    // );


    /*************************
     * LEFT-SIDE-SPECIFIC CODE (DISABLED)
     *************************/

    // Bottom three lines have to be changed for left
    // Purpose: mirrored logic from left auton, disabled for right side
    // chassis.swingToHeading(-120, DriveSide::RIGHT, 700);

    // chassis.moveToPose(-43, 12, -180, 800);

    // chassis.moveToPoint(-43, 44, 1000, {.forwards = false, .maxSpeed = 80});


    /*************************
     * OLD PATHING IDEAS (DISABLED)
     *************************/

    // Previous pathing and alignment ideas (kept for reference)
    // chassis.turnToPoint(-25, 26, 800, {.minSpeed = 10});
    // chassis.moveToPoint(-25, 45, 700, {.maxSpeed = 100, .minSpeed = 10});
    // chassis.turnToHeading(35, 1000);
    // lW.set_value(false);


    /*************************
     * END STATE
     *************************/

      chassis.swingToHeading(217, DriveSide::LEFT, 700);

    chassis.moveToPose(17, 6, -180, 800); // Rotate and reposition near control zone

    chassis.moveToPoint(18, 37, 1000, {
        .forwards = false,
        .maxSpeed = 80
    });

    // Hold position at end of auton
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
}


void fourBallLeft()
{
    /*************************
     * INITIAL SETUP
     *************************/
    chassis.setPose(0, 0, 0);       // Starting pose at left-side matchloader

    intakeBottom.move(127);         // Start bottom intake immediately


    /*************************
     * FIRST FIELD BALLS
     *************************/

    // Drive to first ball cluster
    chassis.moveToPoint(-2, 27, 1500, {
        .maxSpeed = 90,
        .minSpeed = 90,
        .earlyExitRange = 1
    });
    pros::delay(500);

    lW.set_value(true);             // Deploy left wing for ball control

    chassis.turnToHeading(-110, 500); // Align toward long-goal path


    /*************************
     * APPROACH LONG GOAL
     *************************/

    chassis.moveToPoint(-33, 7, 1350, {
        .minSpeed = 50,
        .earlyExitRange = 1
    });

    // Optional settling delay (disabled)
    // Purpose: tested letting chassis stabilize before backing in
    // pros::delay(75);

    chassis.turnToHeading(180, 500); // Face away from goal for reverse approach


    /*************************
     * LONG GOAL SCORING
     *************************/

    chassis.moveToPoint(-34, 28, 1450, {
        .forwards = false,
        .maxSpeed = 90,
        .minSpeed = 90,
        .earlyExitRange = 1
    }); // 34.5 reference
    pros::delay(775);

    intakeTop.move(127);            // Eject balls into long goal
    pros::delay(1600);

    intakeTop.move(0);              // Stop intakes after scoring
    intakeBottom.move(0);
    lW.set_value(false);             // Retract wing


    /*************************
     * DESCORE + CONTROL ZONE SETUP
     *************************/

    // Descore tech to gain control zone
    chassis.swingToHeading(-120, DriveSide::RIGHT, 700);

    chassis.moveToPose(-43, 12, -180, 800); // Rotate and reposition near control zone

    chassis.moveToPoint(-43, 44, 1000, {
        .forwards = false,
        .maxSpeed = 80
    });
}

void fourBallRight()
{
          
    /*************************
     * INITIAL SETUP
     *************************/
    chassis.setPose(0, 0, 0);       // Starting pose at left-side matchloader

    intakeBottom.move(127);         // Start bottom intake immediately


    /*************************
     * FIRST FIELD BALLS
     *************************/

    // Drive to first ball cluster
    chassis.moveToPoint(2, 27, 1500, {
        .maxSpeed = 90,
        .minSpeed = 90,
        .earlyExitRange = 1
    });
    pros::delay(500);

    lW.set_value(true);             // Deploy left wing for ball control

    chassis.turnToHeading(110, 500); // Align toward long-goal path


    /*************************
     * APPROACH LONG GOAL
     *************************/

    chassis.moveToPoint(25, 7, 1350, {
        .minSpeed = 50,
        .earlyExitRange = 1
    });

    // Optional settling delay (disabled)
    // Purpose: tested letting chassis stabilize before backing in
    // pros::delay(75);

    chassis.turnToHeading(180, 500); // Face away from goal for reverse approach

    pros::delay(500);


    /*************************
     * LONG GOAL SCORING
     *************************/

    chassis.moveToPoint(24, 31, 1450, {
        .forwards = false,
        .maxSpeed = 90,
        .minSpeed = 90,
        .earlyExitRange = 1
    }); // 34.5 reference
    pros::delay(775);

    intakeTop.move(127);            // Eject balls into long goal
    pros::delay(1600);

    intakeTop.move(0);              // Stop intakes after scoring
    intakeBottom.move(0);
    lW.set_value(false);             // Retract wing

    chassis.swingToHeading(217, DriveSide::LEFT, 700);

    chassis.moveToPose(13, 6, -180, 800); // Rotate and reposition near control zone

    chassis.moveToPoint(14, 37, 1000, {
        .forwards = false,
        .maxSpeed = 80
    });

    // Hold position at end of auton
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);

}

void skills(Distancee distancee)
{
    //-15, -50
    chassis.setPose(-15, -50, 0);

    pros::delay(100);
    // chassis.moveToPoint(-18, -29, 1000, {.maxSpeed = 90, .earlyExitRange = 2});
    chassis.moveToPoint(-22, -18.5, 1500, {.maxSpeed = 70});
    intakeBottom.move(127);
    chassis.turnToHeading(-135, 1000);
    intakeBottom.move(0);
    chassis.moveToPose(-9, -2, -135, 3500, {.forwards = false, .maxSpeed = 60, .minSpeed = 60});
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
    chassis.waitUntil(13);
    intakeBottom.move(127);
    intakeTop.move(0);
    pros::delay(1200);
    intakeBottom.move(0);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
    chassis.moveToPoint(-51, -46, 2000, {.maxSpeed = 100, .minSpeed = 10, .earlyExitRange = 1});
    intakeTop.move(127);
    intakeBottom.move(127);
    chassis.turnToHeading(180, 1000, {.minSpeed = 20, .earlyExitRange = 2});
    
    lW.set_value(true);
    
    chassis.moveToPoint(-50.5, -66, 2600, {.maxSpeed = 45});
    intakeTop.move(0);
    intakeBottom.move(127);
    pros::delay(800);
    chassis.moveToPose(-50.5, -46, 180, 1000, {.forwards = false, .maxSpeed = 60, .minSpeed = 30});
    chassis.waitUntilDone();
    pros::delay(100);
    distancee.resetcoord(3, 180, chassis);
    pros::delay(100);
    chassis.moveToPoint(-59, -45, 1000, {.forwards = false, .minSpeed = 30, .earlyExitRange = 3});
    chassis.waitUntil(10);
    
    lW.set_value(false);
    
    chassis.turnToHeading(0, 1000, {.minSpeed = 30, .earlyExitRange = 5});
    intakeTop.move(0);
    intakeBottom.move(0);
    chassis.moveToPoint(-61, 40, 3500, {.maxSpeed = 110, .minSpeed = 30, .earlyExitRange = 3});
    chassis.turnToHeading(-90, 1000, {.minSpeed = 10, .earlyExitRange = 2});
    chassis.moveToPoint(-54, 44, 1000, {.forwards = false, .maxSpeed = 100, .minSpeed = 20, .earlyExitRange = 1});
    chassis.turnToHeading(0, 1000, {.minSpeed = 10, .earlyExitRange = 2});
    chassis.moveToPoint(-50, 20, 2000, {.forwards = false, .maxSpeed = 110});
    chassis.waitUntil(6);
    intakeTop.move(-127);
    intakeBottom.move(-127);
    pros::delay(50);
    intakeTop.move(127);
    intakeBottom.move(127);
    pros::delay(2500);
    chassis.moveToPoint(-51.5, 60, 3000, {.maxSpeed = 70});
    
    lW.set_value(true);
    
    intakeTop.move(0);
    chassis.waitUntilDone();
    pros::delay(100);
    chassis.moveToPoint(-50, 19, 2000, {.forwards = false, .maxSpeed = 100});
    chassis.waitUntil(21);
    intakeTop.move(-127);
    intakeBottom.move(-127);
    pros::delay(100);
    intakeTop.move(127);
    intakeBottom.move(127);
    pros::delay(2500);
    // intakeTop.move(127);
    // intakeBottom.move(127);
    
    // lW.set_value(false);
    
    // pros::delay(1900);
    // chassis.moveToPose(-50, 38, 0, 1000, {.maxSpeed = 100, .minSpeed = 10});
    // chassis.waitUntilDone();
    // distancee.resetcoord(2, 0, chassis);
    // pros::delay(50);
    // chassis.turnToHeading(-250, 1000, {.minSpeed = 10, .earlyExitRange = 3});
    // chassis.moveToPoint(30, 23, 3000, {.maxSpeed = 90});
    // intakeBottom.move(127);
    // intakeTop.move(0);
    // chassis.waitUntil(53);
    // lW.set_value(true);
    // chassis.turnToHeading(-315, 1000, {.minSpeed = 10, .earlyExitRange = 3});
    
    // chassis.moveToPose(7, 3.5, -315, 2300,  {.forwards = false, .maxSpeed = 60, .minSpeed = 55});
    // chassis.waitUntil(11);
    // chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    // intakeTop.move(-127);
    // intakeBottom.move(-127);
    // pros::delay(100);
    // intakeBottom.move(127);
    // intakeTop.move(0);
    // pros::delay(3000);
    // chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);




    // chassis.moveToPoint(50, 52, 2500, {.maxSpeed = 60, .minSpeed = 30, .earlyExitRange = 3});
    // intakeBottom.move(127);
    // chassis.turnToHeading(0, 1000, {.minSpeed = 10, .earlyExitRange = 2});
    // // 48 , 70
    // // 62 , 50
    // // 180
    // // 68 -33
    // // 
    // // lw.set_value(true);
    
    // chassis.moveToPoint(48, 72, 3200, {.maxSpeed = 70, .minSpeed = 20});
    // intakeBottom.move(127);
    // intakeTop.move(0);
    // chassis.moveToPoint(63, 50, 1000, {.forwards = false, .minSpeed = 30, .earlyExitRange = 3});
    // chassis.waitUntil(10);
    
    // lW.set_value(false);
    
    // chassis.turnToHeading(180, 1000, {.minSpeed = 30, .earlyExitRange = 5});
    // intakeTop.move(0);
    // intakeBottom.move(0);
    // chassis.moveToPose(67, -30, 180, 4000, {.maxSpeed = 90, .minSpeed = 40, .earlyExitRange =1});
    // chassis.turnToHeading(90, 1500);
    // chassis.waitUntilDone();
    // pros::delay(50);
    
    // //61 -30
    // // 180
    // // 56 -13
    // // 59 -15


    // chassis.moveToPoint(61.5, -30, 1000, {.forwards = false, .maxSpeed = 100, .minSpeed = 20, .earlyExitRange = 1});
    // chassis.turnToHeading(180, 1000, {.minSpeed = 10, .earlyExitRange = 2});
    // chassis.moveToPoint(57.5, -10, 2000, {.forwards = false, .maxSpeed = 70});
    // chassis.waitUntil(4);
    // intakeTop.move(127);
    // intakeBottom.move(127);
    // pros::delay(2000);

    // pros::delay(50);
    
    // lW.set_value(true);
    
    // intakeTop.move(0);
    // chassis.moveToPoint(61.5, -50, 2500, {.maxSpeed = 55});
    // pros::delay(3000);
    // chassis.moveToPoint(57, -10, 2000, {.forwards = false, .maxSpeed = 70});
    // chassis.waitUntil(20);
    // intakeTop.move(127);
    // intakeBottom.move(127);
    // pros::delay(2800);
    
    // lW.set_value(false);
    
    // chassis.moveToPose(57, -20, 180, 1000, {.maxSpeed = 70});
    // chassis.waitUntilDone();
    // pros::delay(50);
    // distancee.resetcoord(4, 180, chassis);

    // chassis.moveToPose(21.3, -66, 260, 2000, {.lead = 0.3, .maxSpeed = 100});
    // chassis.waitUntilDone();
    
    // lW.set_value(true);
    // pros::delay(500);
    // chassis.tank(70, 70);
	// while (true){
	// 	intakeTop.move(127);
    // 	intakeBottom.move(127);
    //     if(distancee.distancef.get() > 1500 && distancee.distancef.get() < 1700){
    //         chassis.tank(0, 0);
    //         break;
    //     }
    // }  
    // lW.set_value(false);
    
    // pros::delay(30);
    // chassis.moveToPose(5, -64, 270, 6000, {.maxSpeed = 90, .minSpeed = 50});
    // chassis.waitUntil(13);





    // chassis.setPose(0, 0, 0); 
    // intakeBottom.move(127);

    // //Move to four balls
    // chassis.moveToPoint(-6,25,800);

    // //Turn and move to Middle Goal and score
    // chassis.turnToPoint(2,43,2000,{.forwards = false});
    // chassis.moveToPoint(2,43,100,{.forwards = false});


    // pros::delay(1000); 

    // //Move to Long Goal
    
    // chassis.turnToPoint(-38,-5,800,{.forwards = true});
    // chassis.moveToPoint(-38,-5,1200,{.forwards = true});

    // lW.set_value(true); 

    // //Matchload(turn, move and score)
    
    // chassis.turnToPoint(-36,-24,2000,{.forwards = true});
    // chassis.moveToPoint(-36,-24,2500,{.forwards = true});




    // pros::delay(500);

    // //Move Back a bit
    // chassis.moveToPoint(-36,-5,2500,{.forwards = false});

    // //Move to the wall side
    //  chassis.turnToPoint(-47,-5,2000,{.forwards = false});
    //  chassis.moveToPoint(-47,-5,2000,{.forwards = false,.maxSpeed = 60});

    // lW.set_value(false); 

    // //Move to the otherside of field
    // chassis.moveToPoint(-47.5,85,2000,{.forwards = false});

    // //Motion for going to long goal alignment
    // chassis.turnToHeading(-90,500);
    
    // chassis.moveToPoint(-29,84,2000,{.forwards = false,.maxSpeed = 60});

    // chassis.turnToHeading(0,500);


    // chassis.moveToPoint(-29,65,2000,{.forwards = false,.maxSpeed = 60});

    // pros::delay(750);


    // //Scoring on Long Goal #1
    // intakeTop.move(127);
















}

void soloUpdatedAWP()
{
    
    chassis.setPose(0,0,0);
    chassis.moveToPoint(0,28.5,800, {.maxSpeed = 70, .minSpeed = 60});
    chassis.turnToHeading(90,500); // -4,31

    lW.set_value(true);
    intakeBottom.move(127);
    chassis.moveToPoint(13,28.5,1000, {.maxSpeed = 70, .minSpeed = 60});
    pros::delay(900);
   chassis.moveToPoint(-29,28.5,1250, {.forwards = false, .maxSpeed = 90, .minSpeed = 90, .earlyExitRange = 1});
    pros::delay(600);
    intakeTop.move(127);
    pros::delay(1100);


    lW.set_value(false);
    pros::delay(250); 
    chassis.moveToPoint(-5,29,500, {.maxSpeed = 70, .minSpeed = 60, .earlyExitRange = 1});
    intakeTop.move(0);
    chassis.turnToPoint(-31,9,1000, {.maxSpeed = 70, .minSpeed = 60});

    chassis.moveToPoint(-31,9,1000, {.maxSpeed = 90, .minSpeed = 60, .earlyExitRange = 1});
        // chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);

     pros::delay(700);
    lW.set_value(true);

    chassis.turnToPoint(-32,-40,500, {.maxSpeed = 90, .minSpeed = 60,.earlyExitRange = 1});
    pros::delay(250);
    lW.set_value(false);
    chassis.moveToPoint(-34,-45,1500, {.maxSpeed = 90, .minSpeed = 60,.earlyExitRange = 1});
    pros::delay(900);
    lW.set_value(true);
    chassis.turnToHeading(126.7, 500);
    chassis.moveToPoint(-48,-31,1500, {.forwards = false, .maxSpeed = 70, .minSpeed = 60});

    //chassis.moveToPoint(-45,-26,1500, {.forwards = false, .maxSpeed = 70, .minSpeed = 60});
    //pros::delay(500);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
    intakeBottom.move(-120);
    intakeTop.move(-120);
    pros::delay(500);
    intakeBottom.move(127);
    intakeTop.move(0);
    pros::delay(2000);
    //intakeBottom.move(0);



   /*pros::delay(400);
    intakeTop.move(-80);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
    chassis.waitUntil(13);
    intakeBottom.move(127);
    intakeTop.move(0);
     pros::delay(1200);
     intakeBottom.move(0);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);*/ 

    //check
    chassis.moveToPoint(-8,-69,1000, {.maxSpeed = 70, .minSpeed = 60});
    pros::delay(500);
    //chassis.turnToHeading(91, 500);

    // pros::delay(200);

    chassis.moveToPose(13, -69, 90,  1200, {.maxSpeed = 70, .minSpeed = 60});

    pros::delay(1500);
    intakeBottom.move(-10);
    chassis.moveToPoint(-26,-69,1000, {.forwards = false,.maxSpeed = 70, .minSpeed = 60});
    pros::delay(500);
    intakeTop.move(127);
    intakeBottom.move(127);


}
