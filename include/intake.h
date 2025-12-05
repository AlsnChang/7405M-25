#include "main.h"
#include <map>
#include "pros/optical.hpp"


#pragma once



//motor declarations
extern pros::Motor secondIn;
extern pros::Motor firstIn;
extern pros::Motor hopper;
extern bool flingBlue;
extern bool intaking;

extern pros::adi::DigitalOut hood;

extern pros::Optical opticalSensor;

void updateIntake(); 
void middleTimeOptical();
void colorSort();
void storageIn();
void bottomGoal();
void fastBottomScore();
void stopIntake();
void scoreTop();
void scoreMiddle();
void scoreTopAuto();
void middleTime(int time);
void slowerStorageIn();