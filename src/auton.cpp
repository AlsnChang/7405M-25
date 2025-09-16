#include "intake.h"
#include "pros/motors.hpp"
#include "autonSelector.h"
#include "main.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "lemlib/api.hpp"


void bottomGoalSide() {
    //Align with three blocks
    chassis.moveToPoint(0, 11, 900);
    //50
    chassis.turnToPoint(13.4, 26.1, 800, {.maxSpeed=80});
    storageIn();
    //Get blocks
    // chassis.moveToPoint(5.52, 18.7, 1000, {.maxSpeed = 25});
    chassis.moveToPoint(13.4, 26.1, 2000, {.maxSpeed = 25});
    chassis.turnToPoint(5.5,35.5, 1000, {.maxSpeed = 80});

    chassis.moveToPoint(4.23,35.53,1000);
    //pros::delay(40);
    bottomGoal();
    pros::delay(1800);
    hopper.move(-127);
    pros::delay(500);
    hopper.move(0);
    storageIn();
    hopper.move(0);
    
    chassis.moveToPoint(39.5, 2.61, 1500, {.forwards = false, .maxSpeed = 80});

    chassis.turnToHeading(-180, 600, {.maxSpeed = 70});

    scraper.set_value(true);
    chassis.moveToPoint(40.4, -9.5, 2000,{.maxSpeed=90});
    pros::delay(100);

    // //move to long goal
    chassis.moveToPoint(39.5, 3,1000, {.forwards = false});
    scraper.set_value(false);
    chassis.turnToHeading(0,1000, {.maxSpeed = 70});
    pros::delay(900);
    hood.set_value(hoodActivated);
    chassis.moveToPoint(40.15, 15.75,900, {.forwards = true});
    scoreTop();


}
void topGoal() {
    //Align with three blocks
    chassis.moveToPoint(0, 11, 900);
    //50
    chassis.turnToPoint(-13.4, 26.1, 800, {.maxSpeed=80});
    storageIn();
    //Get blocks
    chassis.moveToPoint(-13.4, 26.1, 2000, {.maxSpeed = 25});
    chassis.turnToPoint(-5.5, 35.5, 1000, {.maxSpeed = 70});

    //move towards center goal
    scraper.set_value(true);
    chassis.moveToPoint(-0.5, 36.53, 1000);
    pros::delay(100);
    scoreMiddle();
    pros::delay(1500);
    hopper.move(-127);
    pros::delay(500);
    hopper.move(0);
    storageIn();
    hopper.move(0);

    chassis.moveToPoint(-39.5, 2.61, 1500, {.forwards = false, .maxSpeed = 80});

    chassis.turnToHeading(180, 600, {.maxSpeed = 70}); // -180 mirrored → 180

    scraper.set_value(true);
    chassis.moveToPoint(-39.5, -11.75, 1200, {.maxSpeed=80});
    pros::delay(50);

    //move to long goal
    // chassis.moveToPoint(-39.5, 10, 1000, {.forwards = false});
    chassis.moveToPoint(-39.5, 4, 700, {.forwards = false, .maxSpeed = 90});

    scraper.set_value(false);
    chassis.turnToHeading(0, 1000, {.maxSpeed = 70}); // stays the same
    pros::delay(800);
    hood.set_value(hoodActivated);
    chassis.moveToPoint(-39.5, 15.75, 900, {.forwards = true});
    pros::delay(200);
    scoreTop();
    
}



void startAuton() {
    int auton = getSelectedAuton();

    if (auton == 0) {
        bottomGoalSide();
    }
    else if (auton ==1) {
        topGoal();
    }

    else if (auton == 4) {
        bottomGoalSide(); 
    }
    else if (auton ==5) {
        topGoal();
    }
    else {
        pros::delay(1);
    }
    
    
}
