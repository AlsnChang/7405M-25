#include "autonSelector.h"
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

void pidTest() {
    chassis.moveToPoint(0, 20, 1000, {.earlyExitRange = 10});
}

void bottomControl(){
    flingBlue = false;
    //descore.set_value(false);
    storageIn();
    chassis.moveToPoint(0, 20, 1000, {.earlyExitRange = 10});
    
    pros::delay(20);
    chassis.moveToPoint(0, 35, 1000, { .maxSpeed = 40});
    chassis.turnToPoint(31.76, 17.53, 700, {.forwards = false});
    chassis.moveToPoint(31.76, 17.53, 2800,{.forwards = false, .maxSpeed = 75});
    //pros::delay(1000000);

    chassis.turnToHeading(-195.5, 1000);
    scraper.set_value(true);
    stopIntake();
    storageIn();

    chassis.moveToPoint(36.4,3.63, 1200, {}, false);

    chassis.cancelAllMotions();
    move(70, 0, false, 750);
    // pros::delay(750);
    //move(50, 0, false, 750);
    //pros::delay(1000);
    // move(50, 0.5,false, 500);
    // //back up
    // move(-75, 0, false, 300);
    
    chassis.moveToPoint(29.4, 29.9, 1000, {.forwards = false});
    // chassis.moveToPoint(29, 32.47, 1000, {.forwards = false});

    scoreTopAuto();
    scraper.set_value(false);

    pros::delay(2750);

    stopIntake();
    //move forward
    chassis.moveToPoint(31.7,22.54,700);
    chassis.turnToHeading(-73, 700);
    chassis.moveToPoint(9.7, 49.4, 700);



}

// void fastBottomGoals(){
//     flingBlue = false;
//     remover.set_value(true);
//     //descore.set_value(false);
//     storageIn();
//     chassis.moveToPoint(0, 20, 1000, {.earlyExitRange = 10});
    
//     pros::delay(20);
//     chassis.moveToPoint(0, 35, 1000, { .maxSpeed = 40});

//     chassis.turnToPoint(14.86, 51.4, 700);
//     //pros::delay(10000);
//     chassis.moveToPoint(14.86, 51.4, 1200,{});
//     pros::delay(350);
//     chassis.moveToPoint(-4.42, 29.63, 1000,{ .forwards = false});

//     chassis.turnToHeading(-63.55, 700);
//     // //chassis.turnToPoint(-10.5, 39.3, 700);
//     // // chassis.moveToPoint(-10.5, 39.3, 700,{},false);
//     chassis.moveToPoint(-10.43, 38.57, 700,{},false);

//     // //pros::delay(10000);
//     // fastBottomScore();
//     // pros::delay(1500);
//     // storageIn();

//     // // chassis.moveToPoint(32.5, 24.45, 2800,{.forwards = false, .maxSpeed = 75});
//     // chassis.moveToPoint(31.76, 17.53, 2800,{.forwards = false, .maxSpeed = 75});


//     // chassis.turnToHeading(-195.5, 1000);
//     // scraper.set_value(true);
//     // stopIntake();
//     // // chassis.moveToPoint(36.5,10.7, 1200, {}, false);
//     // chassis.moveToPoint(36.4,3.63, 1200, {}, false);


//     // chassis.cancelAllMotions();
//     // storageIn();
//     // move(50, 0, false, 825);
//     // // pros::delay(750);
//     // // //move(50, 0, false, 750);
//     // // //pros::delay(1000);
//     // // // move(50, 0.5,false, 500);
//     // // // //back up
//     // // // move(-75, 0, false, 300);

//     // // chassis.moveToPoint(28.6, 34.8, 1000, {.forwards = false});
//     // chassis.moveToPoint(29.4, 29.9, 1000, {.forwards = false}, false);
//     // scraper.set_value(false);    
//     // // pros::delay(500);
//     // scoreTopAuto();
// }
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

    // chassis.turnToHeading(-62, 700);
    chassis.turnToPoint(-9.9, 39.55, 700);
    // chassis.moveToPoint(-10.5, 39.3, 700,{},false);
    chassis.moveToPoint(-9.9, 39.55, 700,{},false);
    chassis.turnToHeading(-64.94, 700);


    //pros::delay(10000);
    fastBottomScore();
    pros::delay(1500);
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
    chassis.turnToPoint(29.33, 33, 1000, {.forwards = false});
    chassis.moveToPoint(29.33, 33, 1000, {.forwards = false}, false);
    scraper.set_value(false);    
    // pros::delay(500);
    scoreTopAuto();
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
    chassis.moveToPoint(-36.1, 18.13, 700,{.maxSpeed = 90});
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
        fastBottomGoals();
    }
    else if (getSelectedAuton() == 5 || getSelectedAuton() == 1)
    {
        fastTopGoals();
    }
    else if (getSelectedAuton() == 2 || getSelectedAuton() == 6)
    {
        bottomControl();
    }
}