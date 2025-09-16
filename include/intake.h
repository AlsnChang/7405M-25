#include "main.h"
#include <map>
#pragma once

enum IntakeState {

    FAST, 
    SLOW, 
    OFF, 
    OUTTAKE
};

//motor declarations
extern pros::Motor secondIn;
extern pros::Motor firstIn;
extern pros::Motor hopper;
extern bool flingBlue;

extern pros::adi::DigitalOut hood;

extern pros::Optical opticalSensor;

void setIntakeState (IntakeState state);
void updateIntake(); 
void colorSort();
void storageIn();
void bottomGoal();
void stopIntake();
void scoreTop();
void scoreMiddle();