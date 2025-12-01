#pragma once

// ============================================================================
// auton.h
// ============================================================================
// This header file declares all autonomous routines for the robot.
// Each function corresponds to a specific autonomous routine that can be
// called from main.cpp during autonomous mode.
//
// The actual implementation of these routines should be in auton.cpp.
// ============================================================================

// -------------------------------
// Main Autonomous Routines (Left Side)
// -------------------------------

// Executes a routine to score four balls starting from the left side.
void fourBallLeft();

// Executes a routine to score seven balls starting from the left side.
void sevenBallLeft();

// Executes a routine to score nine balls starting from the left side.
void nineBallLeft();

// Executes a seven-ball routine targeting the middle and long goals on the left.
void longMiddleLeftSeven();

// Executes a nine-ball routine targeting the middle and long goals on the left.
void longMiddleLeftNine();

// Executes a solo autonomous routine for AWP (specific task, e.g., one goal or skill).
void soloAWP();


// -------------------------------
// Optional Autonomous Routines (Right Side)
// -------------------------------
// Use these if you plan to have symmetrical autonomous routines for the right side.

// Executes a routine to score four balls starting from the right side.
void fourBallRight();

// Executes a routine to score seven balls starting from the right side.
void sevenBallRight();

// Executes a routine to score nine balls starting from the right side.
void nineBallRight();

// Executes a seven-ball routine targeting the bottom or long goal on the right.
void longBottomRightSeven();

// Executes a nine-ball routine targeting the bottom or long goal on the right.
void longBottomRightNine();
