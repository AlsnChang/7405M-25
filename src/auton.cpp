#include "autonSelector.h"
#include "autons.h"
#include "intake.h"
//#include "intake.cpp"
#include "pros/motors.h"
#include "pros/motors.hpp"
#include "autonselector.h"
#include "main.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "lemlib/api.hpp"
#include <source_location>


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
    chassis.cancelAllMotions();

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

void soloAWPCedar() {
    chassis.moveToPoint(0, 34, 1000);
    chassis.turnToPoint(10, 37.2, 650);
    scraper.set_value(true);
    chassis.moveToPoint(10, 37.2, 700);

    chassis.cancelAllMotions();
    flappier.set_value(true);
    storageIn();
    move(50, 0, false, 1000);
    

    //pros::delay(100000);
    //chassis.turnTo
    chassis.moveToPoint(-18, 37.2, 1000, {.forwards=false}, false);

    scoreTop();
    scraper.set_value(false);
    pros::delay(1500);

    chassis.moveToPoint(-10, 36.9, 400);

    chassis.turnToHeading(208.4,750);
    flappier.set_value(true);

    chassis.moveToPoint(-22.62, 11.38, 750, {.maxSpeed = 50});

    chassis.turnToHeading(180, 850);
    //chassis.moveToPoint(-24.0, -36.08, 1200, {.maxSpeed = 60});
    chassis.moveToPoint(-22.06, -38.39, 1500, {.maxSpeed = 60});
    //chassis.turnToHeading(155,750);
    chassis.turnToPoint(-32.00, -22.7, 750, {.forwards = false}); 
    chassis.moveToPoint(-35.82, -22.71, 750, {.forwards = false}, false); 
    flappy.set_value(true);
    flappier.set_value(true);
    chassis.moveToPoint(3.17,-66.7, 1500);
    

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


void soloAWP(){

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

void skills() {
    leftMotors.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    rightMotors.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.setPose(0,0,-19.67);
    storageIn();
    chassis.moveToPoint(-9.28, 29.41, 1000);
    chassis.turnToPoint(7.38, 44.30, 700, {.forwards = false});
    chassis.moveToPoint(7.38, 44.3, 1000, {.forwards = false}, false);

    //score middle goal
    scoreMiddle();
    pros::delay(1500);
    stopIntake();
    flappier.set_value(false);
    flappy.set_value(false);

    //go to match loader
    chassis.turnToHeading(-135, 700);
    chassis.moveToPoint(-36.5, 3.7, 2000, {.maxSpeed=60});
    chassis.turnToHeading(-177, 700, {}, false);
    scraper.set_value(true);
    storageIn();
    chassis.moveToPoint(-38.2, -4.5, 1000);

    // //empty match loader 1
    chassis.cancelAllMotions();
    move(50, 0, false, 1250);
    pros::delay(700);
    chassis.moveToPoint(-38.15, 3.2, 1000, {.forwards = false}, false);
    scraper.set_value(false);
    chassis.turnToHeading((-205), 750);
    pros::delay(50);
    stopIntake();
    pros::delay(50);
    chassis.moveToPoint(-51.4, 30.5, 1000, {.forwards = false, .maxSpeed = 80});
    
    //go to other side
    chassis.turnToPoint(-48, 87, 750, {.forwards = false});
    chassis.moveToPoint(-48, 92, 2000, {.forwards = false, .maxSpeed = 80}, false);

    // //score in long goal 1st time
    chassis.turnToHeading(-90, 700);
    chassis.moveToPoint(-34.8, 89.5, 1000, {.forwards = false});
    chassis.turnToHeading(0, 700);

    chassis.moveToPoint(-36.5, 79.5, 1000, {.forwards = false}, false);
    move(-50,0,false,900);
    chassis.setPose(0, 0, 0);
    scoreTop();
    pros::delay(2000);

    //unload match loader 2
    scraper.set_value(true);
    storageIn();
    chassis.moveToPoint(1.5, 29.5, 1000, {}, false);
    pros::delay(250);
    chassis.cancelAllMotions();
    move(70,0,false, 1250);
    pros::delay(250);

    //score in long goal again
    chassis.moveToPoint(0, 0, 1000, {.forwards = false, .maxSpeed = 100}, false);
    scoreTop();
    pros::delay(3000);
    stopIntake();

    //go to 3rd match loader
    chassis.moveToPoint(0, 16, 1000);
    scraper.set_value(false);
    // chassis.turnToPoint(103.25, 15, 750);
    // //loooong
    // chassis.moveToPoint(103.25, 15, 2700, {.maxSpeed = 90}, false);

    // //unload match loader 3
    // chassis.turnToPoint(103.25, 29.92, 700);
    // scraper.set_value(true);
    // storageIn();
    // chassis.moveToPoint(103.25, 29.92, 1000, {}, false);

    // pros::delay(250);
    // chassis.cancelAllMotions();
    // move(70,0,false, 1250);
    // pros::delay(250);

    // stopIntake();
    // chassis.moveToPoint(103.25, 20, 1000, {.forwards = false});
    // scraper.set_value(false);
}

void skillsBad() {
    storageIn();
    chassis.moveToPoint(-1.11, 28.9, 1000, {.maxSpeed = 50}, false);
    scraper.set_value(true);
    chassis.turnToPoint(18, 38.43, 700, {.forwards = false});
    chassis.moveToPoint(18, 38.43, 800, {.forwards = false}, false);

    flappier.set_value(true);
    flappy.set_value(true);
    pros::delay(1500);
    flappier.set_value(false);
    flappy.set_value(false);
    scraper.set_value(false);

    chassis.moveToPoint(-34.1, 15.83, 1200);
    chassis.turnToHeading(-160.73, 750);
    scraper.set_value(true);
    flappier.set_value(true);
    flappy.set_value(true);

    chassis.moveToPoint(-35.33, 1.8, 800);

    chassis.cancelAllMotions();
    move(50, 0, false, 825);

}

void fastBottomGoals(){
    flingBlue = false;
    descore.set_value(true);
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