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
#include <cstdio>
#include <source_location>


void middleTimed(){
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


void leftSide3Plus4(){
    leftMotors.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    rightMotors.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.setPose(0,0,-19.67);
    wing.set_value(true);
    storageIn();
    chassis.moveToPoint(-9.28, 29.41, 1000);
    chassis.turnToPoint(7.38, 44.30, 700, {.forwards = false});
    chassis.moveToPoint(7.38, 44.3, 1000, {.forwards = false}, false);

    //score middle goal
    scoreMiddle();
    pros::delay(1500);
    // stopIntake();
    flappier.set_value(false);
    flappy.set_value(false);
    // score();

    //go to match loader
    chassis.turnToHeading(-135, 700);
    chassis.moveToPoint(-36.5, 3.7, 2000, {.maxSpeed=60});
    chassis.turnToHeading(-177, 700, {}, false);
    scraper.set_value(true);
    pros::delay(750);
    storageIn();
    chassis.moveToPoint(-38.2, -4.5, 1000);

    // //empty match loader 1
    chassis.cancelAllMotions();
    move(50, 0, false, 1250);
    pros::delay(700);
    chassis.moveToPoint(-41.15, 3.2, 1000, {.forwards = false}, false);
    // chassis.moveToPoint(-39.15, 3.2, 1000, {.forwards = false}, false);
    scraper.set_value(false);

    chassis.moveToPoint(-50,15.1, 1000, {.forwards = false, .maxSpeed = 80});
    
    // move(-50,0,false,200);
    // scoreTop();
    // pros::delay(1500);
    // stopIntake();
    // move(50,0,false,200);
    // move(-70,0,false,200);
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


    chassis.moveToPoint(-50,15.1, 1000, {.forwards = false, .maxSpeed = 80});




}

void skills() {
    leftMotors.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    rightMotors.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.setPose(0,0,-19.67);
    wing.set_value(true);
    storageIn();
    chassis.moveToPoint(-9.28, 29.41, 1000);
    chassis.turnToPoint(7.38, 44.30, 700, {.forwards = false});
    chassis.moveToPoint(7.38, 44.3, 1000, {.forwards = false}, false);

    //score middle goal
    scoreMiddle();
    pros::delay(1500);
    // stopIntake();
    flappier.set_value(false);
    flappy.set_value(false);
    // score();

    //go to match loader
    chassis.turnToHeading(-135, 700);
    chassis.moveToPoint(-36.5, 3.7, 2000, {.maxSpeed=60});
    chassis.turnToHeading(-177, 700, {}, false);
    scraper.set_value(true);
    pros::delay(750);
    storageIn();
    chassis.moveToPoint(-38.2, -4.5, 1000);

    // //empty match loader 1
    chassis.cancelAllMotions();
    move(50, 0, false, 1250);
    pros::delay(700);
    chassis.moveToPoint(-41.15, 3.2, 1000, {.forwards = false}, false);
    // chassis.moveToPoint(-39.15, 3.2, 1000, {.forwards = false}, false);
    scraper.set_value(false);
    // chassis.turnToHeading((-205), 750);
    chassis.turnToPoint(-50,15.1, 750, {.forwards = false}, false);
    pros::delay(50);
    stopIntake();
    pros::delay(50);

    chassis.moveToPoint(-50,15.1, 1000, {.forwards = false, .maxSpeed = 80});
    
    // //go to other side
    chassis.turnToPoint(-45.73, 96.59, 750, {.forwards = false});
    chassis.moveToPoint(-45.73, 96.59, 2000, {.forwards = false, .maxSpeed = 80}, false);

    // chassis.turnToPoint(-45.73, 96.59, 750, {.forwards = true});
    // chassis.moveToPoint(-45.73, 96.59, 2000, {.forwards = true, .maxSpeed = 80}, false);

    // //score in long goal 1st time
    // chassis.turnToHeading(-90, 700);
    // chassis.turnToPoint(-30.1, 95, 1000, {.forwards = false});
    // chassis.moveToPoint(-30.1, 95, 1000, {.forwards = false});
    chassis.turnToPoint(-31.8, 95, 1000, {.forwards = false});
    chassis.moveToPoint(-31.8, 95, 1000, {.forwards = false});
    // chassis.turnToHeading(0, 700);
    chassis.turnToPoint(-35.3, 77, 750, {.forwards = false});
    chassis.moveToPoint(-35.3, 77, 1000, {.forwards = false}, false);
    move(-50,0,false,900);
    scoreTop();
    pros::delay(2000);

    // //unload match loader 2
    scraper.set_value(true);
    storageIn();
    chassis.moveToPoint(-33.82, 107, 1000, {}, false);
    pros::delay(250);
    chassis.cancelAllMotions();
    move(70,0,false, 1500);
    pros::delay(250);

    //score in long goal again
    chassis.moveToPoint(-35.3, 77, 1000, {.forwards = false}, false);
    stopIntake();     
    move(-50,0,false,200);
    pros::delay(500);
    scoreTop();
    pros::delay(3000);
    stopIntake();
    move(50,0,false,200);
    pros::delay(250);
    move(-50,0,false,200);

    chassis.moveToPoint(-33.4, 93.3, 1000);
    scraper.set_value(false);

    chassis.turnToHeading(90, 750);

    chassis.turnToPoint(67, 97.2, 750);
    //loooong
    chassis.moveToPoint(67, 97.2, 2750, {.maxSpeed = 90}, false);

    chassis.turnToHeading(0.83,750);
    scraper.set_value(true);
    storageIn();

    chassis.moveToPoint(67, 108, 1000);
    // // //unload match loader 3
    
    pros::delay(250);
    chassis.cancelAllMotions();
    move(50,0,false, 1250);
    pros::delay(700);


    stopIntake();
    chassis.moveToPoint(65.6, 98.36, 1000, {.forwards = false},false);
    scraper.set_value(false);


    // MAYBE CHANGE HERE
    // chassis.turnToPoint(79.7, 85.6, 750, {.forwards = false});
    // chassis.moveToPoint(79.7, 85.6, 1000, {.forwards = false}, false);
    chassis.turnToPoint(81.3, 87.5, 750, {.forwards = false});
    chassis.moveToPoint(81.3, 87.5, 1000, {.forwards = false}, false);


    //moving backwards to score in long goal
    chassis.turnToPoint(75.72, 10.5, 750, {.forwards = false});
    chassis.moveToPoint(75.72, 10.5, 3000, {.forwards = false,.maxSpeed = 80}, false);
    // chassis.turnToPoint(79.7, 25.5, 750, {.forwards = false});
    // chassis.moveToPoint(79.7, 25.5, 2500, {.forwards = false,.maxSpeed = 80}, false);
    
    
    chassis.turnToHeading(-90, 750);
    chassis.moveToPoint(65.4,10.4,1000);
    chassis.turnToPoint(65.4, 28.61, 750,{.forwards = false});
    chassis.moveToPoint(65.4, 28.61,1000,{.forwards = false}, false);
    
    //score top 
    move(-70,0,false,200);
    pros::delay(500);
    scoreTop();
    pros::delay(3000);
    stopIntake();

    //unload match loader 4
    scraper.set_value(true);
    storageIn();
    chassis.moveToPoint(63, -9.75, 1000, {}, false);
    pros::delay(250);
    chassis.cancelAllMotions();
    move(50,0,false, 1250);
    pros::delay(250);

    // //score in long goal again 2nd time
    chassis.moveToPoint(65.4, 28.61, 1000, {.forwards = false, .maxSpeed = 100}, false);
    stopIntake();     
    move(-50,0,false,200);
    pros::delay(500);
    scoreTop();
    pros::delay(3000);
    move(50,0,false,200);
    pros::delay(250);
    move(-50,0,false,200);

    scraper.set_value(false);    
    chassis.moveToPose(30, -17, -90, 1500, {.lead = .2});
    // move(120,0,false,2000);





}


void startAuton(){
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