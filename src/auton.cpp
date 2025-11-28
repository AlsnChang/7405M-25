#include "intake.h"
#include "pros/motors.hpp"
#include "autonselector.h"
#include "main.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "lemlib/api.hpp"

// void skills() {
//     chassis.moveToPoint(0,15,1000);
//     chassis.turnToPoint(0,15,90);
//     chassis.moveToPoint(40,15,3000);
//     chassis.turnToPoint(40,15,90);
//     scraper.set_value(true);
//     storageIn();
//     chassis.moveToPoint(40, -10, 1000);


// }
void move(double power, double turn, bool swing=false, double time=10000) {
    int left = power + turn;
    int right = power - turn;
    // double t = time; 

    if (swing && left < 0) {left = 0;}
    if (swing && right < 0) {right = 0;}

    leftMotors.move(left);
    rightMotors.move(left);
    pros::delay(time);
    leftMotors.brake();
    rightMotors.brake();
    // left_center_motor.move(left);
    // left_back_motor.move(left);
    // right_front_motor.move(left);
    // right_center_motor.move(left);
    // right_back_motor.move(left);
}

void bottomGoalSideWPI() {
    flingBlue = false;
    pros::delay(3);
    chassis.moveToPoint(-0.5, 10, 800);
    chassis.turnToHeading(40, 1000);
    storageIn();
    chassis.moveToPoint(14, 26, 3000, {.maxSpeed = 40});  
    pros::delay(2100);

    //Go and outtake into bottom goal
    stopIntake(); 
    chassis.turnToHeading(-37, 1500);
    chassis.moveToPoint(5.3, 39, 1500);
    pros::delay(50);
    bottomGoal();
    pros::delay(3000);
    stopIntake();
    chassis.moveToPoint(40, 4, 3000, {.forwards = false, .maxSpeed = 40});  
    chassis.turnToHeading(-174, 1500);
    pros::delay(1000);
    //pros::delay(5000);
    scraper.set_value(true);
    //pros::delay(100);
    // chassis.moveToPoint(39, -7, 1500);

    //cancel motions (voltage thing), move continuously into loader,  move back a bit, ram again
    chassis.cancelAllMotions();
    pros::delay(500);
    storageIn();
    move(50, 0, false, 1000);
    pros::delay(1500);
    //chassis.moveToPoint(41.32, 18.84, 1500, {.forwards = false});
    pros::delay(500);
    chassis.moveToPoint(42, 17,5000, {.forwards = false, .maxSpeed = 35});
    colorSort();
    //pros::delay(1000);
    // chassis.moveToPoint(39, 0, 1500);
    // pros::delay(1000);
    //chassis.cancelAllMotions();
    //move(50,0);
    //chassis.moveToPoint(39, 15, 1500);

    //pros::delay(100000000);    

    // pros::delay(3000);
    // chassis.moveToPoint(39.9, 20, 3000, {.forwards = false, .maxSpeed = 50});
    // scoreTop();
}

void bottomGoalSide() {
    //Align with three blocks
    chassis.moveToPoint(0, 11, 1000);
    //50
    chassis.turnToPoint(13.4, 26.1, 2000, {.maxSpeed=90});
    storageIn();
    
    chassis.moveToPoint(13.4, 26.1, 3000, {.maxSpeed = 35});
    chassis.turnToPoint(5.5,35.5, 1000, {.maxSpeed = 80});

    chassis.moveToPoint(5.5,35.5,3500);
    bottomGoal();
    pros::delay(2000);
    
   //loader
    hopper.move(-127);
    stopIntake();
    chassis.moveToPoint(39, 2.61, 2500, {.forwards = false, .maxSpeed = 80});

    chassis.turnToHeading(-180, 750, {.maxSpeed = 90});
    storageIn();

    scraper.set_value(true);
    chassis.moveToPoint(40, -11, 2000,{.minSpeed=100});
    pros::delay(1500);

    //move to long goal
    scraper.set_value(false);
    chassis.moveToPoint(40, 20 ,5000, {.forwards = false});
    //scoreTop();

}

void topGoalSide()
{

}

void startAuton()
{
    if (getSelectedAuton() == 0 || getSelectedAuton() == 4)
    {
        bottomGoalSide();
    }
    else if (getSelectedAuton() == 5 || getSelectedAuton() == 1)
    {
        topGoalSide();
    }
}
