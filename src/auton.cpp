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

void fastBottomGoals(){
    flingBlue = false;
    storageIn();
    chassis.moveToPoint(0, 20, 1000, {.earlyExitRange = 10});
    pros::delay(20);
    chassis.moveToPoint(0, 35, 1000, { .maxSpeed = 40});
    chassis.turnToPoint(14.3, 54, 700);
    chassis.moveToPoint(14.3, 54, 1000,{});
    pros::delay(350);
    chassis.moveToPoint(-1, 33.14, 1000,{ .forwards = false});
    // chassis.moveToPoint(-5.24, 34.70, 1000,{ .forwards = false});

    chassis.turnToPoint(-14.05, 40.44, 700);
    chassis.moveToPoint(-10.45, 37.5, 1000,{},false);
    // chassis.turnToHeading(-65, 1000);
    fastBottomScore();
    pros::delay(1000);
    stopIntake();
    storageIn();
    pros::delay(150);
    chassis.moveToPoint(33.14, 18.8, 3000,{.forwards = false, .maxSpeed = 90});
    // chassis.turnToPoint(37.3, 8.9, 700, {}, false);
    chassis.turnToHeading(-190,1000);

    scraper.set_value(true);

    stopIntake();
    chassis.moveToPoint(36.5,10.2, 1000, {}, false);

    chassis.cancelAllMotions();
    storageIn();
    move(50, 0, false, 500);
    pros::delay(1000);

    chassis.turnToPoint(27.92, 37.21, 1000, {.forwards = false});
    chassis.moveToPoint(27.92, 37.21, 1000, {.forwards = false});

    
    // chassis.moveToPoint(27.8, 34, 1000, {.forwards = false});
    pros::delay(1500);
    scoreTop();
}

void fastTopGoals() {
    flingBlue = false;
    storageIn();
    chassis.moveToPoint(0, 20, 1000, {.earlyExitRange = 10});
    pros::delay(20);
    chassis.moveToPoint(0, 35, 1000, { .maxSpeed = 40});
    chassis.turnToPoint(-15, 55, 700);
    chassis.moveToPoint(-11, 53.7, 1000);
    pros::delay(350);

    chassis.moveToPoint(2, 33, 1000,{ .forwards = false});

    chassis.turnToPoint(12, 37.3, 700, {.forwards = false});
    chassis.moveToPoint(12, 37.3, 1000,{.forwards = false},false);

    scoreMiddle();
    pros::delay(1500);
    stopIntake();
    storageIn();
    pros::delay(150);
    
    chassis.moveToPoint(-36.7, 18, 1000,{.maxSpeed = 80});
    chassis.turnToHeading(-153,1000);

    scraper.set_value(true);

    stopIntake();
    chassis.moveToPoint(-36.5,-10.2, 1000, {}, false);

    chassis.cancelAllMotions();
    storageIn();
    move(10, 0, false, 500);
    pros::delay(1000);

    chassis.moveToPoint(-26.6, 37, 1000, {.forwards = false, .maxSpeed = 60});

    pros::delay(1500);
    scoreTop();
    // chassis.moveToPoint(-27.92, -37.21, 1000, {.forwards = false});

    // pros::delay(1500);
    // scoreTop();
}

void bottomGoalSide() {
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
