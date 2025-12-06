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
void skillsTest() {
    flingBlue = false;
    //descore.set_value(false);
    storageIn();
    chassis.moveToPoint(0, 20, 1000, {.earlyExitRange = 10});
    
    pros::delay(20);
    chassis.moveToPoint(0, 35, 1000, { .maxSpeed = 40});

    chassis.turnToPoint(14.86, 51.4, 700);
    chassis.moveToPoint(14.86, 51.4, 1200,{});
    pros::delay(350);
    chassis.moveToPoint(0.49, 32.5, 1000,{ .forwards = false});
    //pros::delay(100000);

    chassis.turnToHeading(-64, 700);
    //chassis.turnToPoint(-10.5, 39.3, 700);
    chassis.moveToPoint(-10.5, 39.3, 700,{},false);
    //pros::delay(10000);
    fastBottomScore();
    pros::delay(1500);
    storageIn();

    chassis.moveToPoint(35.44, 16.38, 2800,{.forwards = false, .maxSpeed = 75});
    //pros::delay(1000000);

    chassis.turnToHeading(-185, 1000);
    scraper.set_value(true);
    stopIntake();
    chassis.moveToPoint(36.82,10.7, 1200, {}, false);

    chassis.cancelAllMotions();
    storageIn();
    move(50, 0, false, 750);
    pros::delay(250);
    move(50,0,false,750);
    pros::delay(1000);
    move(50,0.2,false,750);

    chassis.moveToPoint(30.41, 31.12, 1000, {.forwards = false});
    scoreTopAuto();

}
void middleTimed()
{
    scoreMiddle();
    pros::delay(500);
    stopIntake();
}

void middleTimeOptical() {
    intaking = true;
    while(intaking) {
        scoreMiddle();
        if(opticalSensor.get_proximity() > 50) { //need to tune this value - 0 (far) & 255 (near)
            stopIntake();
            intaking = false;
        }
    }
}



void pidTest() {
    chassis.moveToPoint(0, 20, 1000, {.earlyExitRange = 10});
}


void fastBottomGoals(){
    flingBlue = false;
    remover.set_value(true);
    //descore.set_value(false);
    storageIn();
    chassis.moveToPoint(0, 20, 1000, {.earlyExitRange = 10});
    
    pros::delay(20);
    chassis.moveToPoint(0, 35, 1000, { .maxSpeed = 40});

    chassis.turnToPoint(14.86, 51.4, 700);
    //pros::delay(10000);
    chassis.moveToPoint(14.86, 51.4, 1200,{});
    pros::delay(350);
    chassis.moveToPoint(0.49, 32.5, 1000,{ .forwards = false});

    chassis.turnToHeading(-62, 700);
    //chassis.turnToPoint(-10.5, 39.3, 700);
    // chassis.moveToPoint(-10.5, 39.3, 700,{},false);
    chassis.moveToPoint(-13.7, 38.4, 700,{},false);

    // //pros::delay(10000);
    fastBottomScore();
    pros::delay(1000);
    storageIn();

    // chassis.moveToPoint(32.5, 24.45, 2800,{.forwards = false, .maxSpeed = 75});
    chassis.moveToPoint(31.76, 17.53, 2800,{.forwards = false, .maxSpeed = 75});


    chassis.turnToHeading(-195.5, 1000);
    scraper.set_value(true);
    stopIntake();
    // chassis.moveToPoint(36.5,10.7, 1200, {}, false);
    chassis.moveToPoint(36.4,3.63, 1200, {}, false);


    chassis.cancelAllMotions();
    storageIn();
    move(50, 0, false, 825);
    // pros::delay(750);
    // //move(50, 0, false, 750);
    // //pros::delay(1000);
    // // move(50, 0.5,false, 500);
    // // //back up
    // // move(-75, 0, false, 300);

    // chassis.moveToPoint(28.6, 34.8, 1000, {.forwards = false});
    chassis.moveToPoint(29.4, 29.9, 1000, {.forwards = false}, false);
    scraper.set_value(false);    
    // pros::delay(500);
    scoreTopAuto();
}


void badBottomGoal(){
    flingBlue = false;
    remover.set_value(true);
    //descore.set_value(false);
    storageIn();
    chassis.moveToPoint(0, 20, 1000, {.earlyExitRange = 10});
    
    pros::delay(20);
    chassis.moveToPoint(0, 35, 1000, { .maxSpeed = 40});

    chassis.turnToPoint(14.86, 51.4, 700);
    chassis.moveToPoint(14.86, 51.4, 1200,{});
    pros::delay(350);
    chassis.moveToPoint(0.49, 32.5, 1000,{ .forwards = false});
    //pros::delay(100000);

    chassis.turnToHeading(-64, 700);
    //chassis.turnToPoint(-10.5, 39.3, 700);
    chassis.moveToPoint(-10.5, 39.3, 700,{},false);
    //pros::delay(10000);
    fastBottomScore();
    pros::delay(1050);
    storageIn();
    pros::delay(500);

    chassis.moveToPoint(32.5, 24.45, 1500,{.forwards = false, .maxSpeed = 75});
    //pros::delay(1000000);
    pros::delay(250);

    //chassis.turnToHeading(-193, 1000);
    scraper.set_value(true);
    stopIntake();
    chassis.turnToPoint(36.73, 5.76, 1200);
    chassis.moveToPoint(36.73, 5.76, 1200, {}, false);

    chassis.cancelAllMotions();
    storageIn();
    move(40, 0, false, 1200);
    pros::delay(500);
    // move(50, 0, false, 750);
    // pros::delay(1000);
    // move(50, 0.5,false, 500);
    // //back up
    // move(-75, 0, false, 300);

    chassis.moveToPoint(37.04, 8.22, 1000, {.forwards = false});
    scraper.set_value(false);
    pros::delay(250);
    // chassis.moveToPoint(28.6, 34, 1000, {.forwards = false});

    // pros::delay(1500);
    scoreTopAuto();

    // chassis.moveToPoint(); 
}

void fastTopGoals() {
    flingBlue = false;
    storageIn();
    chassis.moveToPoint(0, 20, 1000, {.earlyExitRange = 10});
    pros::delay(20);
    chassis.moveToPoint(0, 35, 1000, { .maxSpeed = 40});
    chassis.turnToPoint(-15.5, 52, 700);
    chassis.moveToPoint(-15.5, 52, 1000, { .maxSpeed = 55});

    // MOVE BACK AND SCORE MIDDLE
    chassis.moveToPoint(0.55, 34.1, 1000,{ .forwards = false});
    chassis.turnToPoint(10.98, 37.12, 700, {.forwards = false});
    chassis.moveToPoint(10.98, 37.12, 700, {.forwards = false});  



    
    // SCORING MIDDLE
    // scoreMiddle();
    // pros::delay(2000);
    // storageIn();


    // MOVE BACK SCRAPER TIME
    chassis.moveToPoint(-36.1, 18.13, 1000,{.maxSpeed = 90});
    scraper.set_value(true);
    chassis.turnToHeading(-160,700, {}, false);




    // //chassis.turnToPoint(-35.7, 7.8, 750, {}, false);
    // chassis.moveToPoint(-39.27, 7.93, 750, {}, false);
    
    // chassis.cancelAllMotions();
    // storageIn();
    // move(50, 0, false, 1000);
   

    // chassis.moveToPoint(-28, 37, 1000, {.forwards = false, .maxSpeed = 50});

    // pros::delay(1500);
    // scraper.set_value(false);
    // scoreTop();
}



void topGoalSide()
{

}

void startAuton()
{
    if (getSelectedAuton() == 0 || getSelectedAuton() == 4)
    {
        //bottomGoalSide();
    }
    else if (getSelectedAuton() == 5 || getSelectedAuton() == 1)
    {
        topGoalSide();
    }
}