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

    chassis.turnToPoint(14.86, 51.4, 700, { .maxSpeed = 30});
    //pros::delay(10000);
    chassis.moveToPoint(14.86, 51.4, 1200,{});
    pros::delay(350);
    chassis.moveToPoint(0.49, 32.5, 1200,{ .forwards = false}, false);
    
    //pros::delay(100);
    //bottomTime(300);

<<<<<<< HEAD

    chassis.turnToPoint(-14.5, 37, 700);
    chassis.moveToPoint(-14.5, 37, 700,{},false);
    // chassis.moveToPoint(-13.7, 38.4, 700,{},false);

    // // //pros::delay(10000);
    bottomGoal();
=======
    // chassis.turnToHeading(-62, 700);
    chassis.turnToPoint(-9.9, 39.55, 700);
    // chassis.moveToPoint(-10.5, 39.3, 700,{},false);
    chassis.moveToPoint(-9.9, 39.55, 700,{},false);
    chassis.turnToHeading(-64.94, 700);


    //pros::delay(10000);
    fastBottomScore();
>>>>>>> b1380e8ee784a60d2268c31af7e9524a0b01d2ff
    pros::delay(1500);
    storageIn();

    // chassis.moveToPoint(32.5, 24.45, 2800,{.forwards = false, .maxSpeed = 75});
    chassis.moveToPoint(31.76, 17.53, 1700,{.forwards = false, .maxSpeed = 75});


    chassis.turnToHeading(-195.5, 700);
    scraper.set_value(true);
    stopIntake();
    // chassis.moveToPoint(36.5,10.7, 1200, {}, false);
    chassis.moveToPoint(36.4,3.63, 1200, {}, false);


    chassis.cancelAllMotions();
    storageIn();
    move(50, 0, false, 825);
    pros::delay(750);
    // //move(50, 0, false, 750);
    // //pros::delay(1000);
    // // move(50, 0.5,false, 500);
    // // //back up
    // // move(-75, 0, false, 300);

    // chassis.moveToPoint(28.6, 34.8, 1000, {.forwards = false});
<<<<<<< HEAD
    //pros::Task time(longTime);
    chassis.turnToPoint(29.4, 29.9, 1000, {.forwards = false}, false);
    chassis.moveToPoint(29.4, 29.9, 1000, {.forwards = false}, false);
    
=======
    chassis.turnToPoint(29.33, 33, 1000, {.forwards = false});
    chassis.moveToPoint(29.33, 33, 1000, {.forwards = false}, false);
>>>>>>> b1380e8ee784a60d2268c31af7e9524a0b01d2ff
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
    chassis.turnToHeading(-32.6, 1000);
    chassis.moveToPoint(-12.54, 51.88, 1000, { .maxSpeed = 55}, false);
    storageIn();
    pros::delay(250);
    // // // MOVE BACK AND SCORE MIDDLe
    chassis.moveToPoint(-1.57, 32, 1000,{ .forwards = false});
    //pros::Task middle(middleTime);
    chassis.turnToPoint(11, 33.5, 700, {.forwards = false}, false);
    chassis.moveToPoint(11, 33.5, 700, {.forwards = false}, false);
    
    // SCORING MIDDLE
    scoreMiddle();
    pros::delay(1500);
    storageIn();


<<<<<<< HEAD
    // // // MOVE BACK SCRAPER TIME
    chassis.moveToPoint(-37.31, 15.5, 1000,{.maxSpeed = 70},false);
=======
    // MOVE BACK SCRAPER TIME
    chassis.moveToPoint(-36.1, 18.13, 700,{.maxSpeed = 90});
>>>>>>> b1380e8ee784a60d2268c31af7e9524a0b01d2ff
    scraper.set_value(true);


    // chassis.turnToHeading(-152,500);

    //move(50, false, false, 1000);

    // chassis.moveToPoint(-41, 4.73, 750, {}, false);
    
    // chassis.cancelAllMotions();
    // storageIn();
    // move(50, 0, false, 1000);
   

    // // chassis.moveToPoint(-30.7, 23.6, 1000, {.forwards = false, .maxSpeed = 50});
    // // scraper.set_value(false);
    // // pros::delay(1500);
    // // scraper.set_value(false);
    // // scoreTop();
}

void startAuton()
{
    if (getSelectedAuton() == 0 || getSelectedAuton() == 4)
    {
        //bottomGoalSide();
    }
    else if (getSelectedAuton() == 5 || getSelectedAuton() == 1)
    {
        
    }
}

void skillsPark()
{
    chassis.moveToPoint(15, 0, 750);
    move(-127, 0, false, 2000);
}