#include "intake.h"
#include "pros/motors.hpp"
#include "autonsSelector.h"
#include "main.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "lemlib/api.hpp"


void bottomGoalSide() {
    //Align with three blocks
    chassis.moveToPoint(0, 11, 1000);
    //50
    chassis.turnToPoint(13.4, 26.1, 1000, {.maxSpeed=80});
    storageIn();
    //Get blocks
    // chassis.moveToPoint(5.52, 18.7, 1000, {.maxSpeed = 25});
    chassis.moveToPoint(13.4, 26.1, 3000, {.maxSpeed = 25});
    chassis.turnToPoint(5.5,35.5, 1000, {.maxSpeed = 80});

    chassis.moveToPoint(5.5,35.5,5000);
    bottomGoal();
    pros::delay(2000);

    
   //loader
    hopper.move(-127);
    stopIntake();
    chassis.moveToPoint(39, 2.61, 2500, {.forwards = false, .maxSpeed = 80});

    chassis.turnToHeading(-180, 750, {.maxSpeed = 90});
    storageIn();

    scraper.set_value(true);
    chassis.moveToPoint(39, -11, 2000,{.minSpeed=100});
    pros::delay(1500);

    //move to long goal
    chassis.moveToPoint(39, 10,2000, {.forwards = false});
    scraper.set_value(false);
    chassis.turnToHeading(0,1000, {.maxSpeed = 90});
    pros::delay(1000);
    chassis.moveToPoint(39, 15.5,5000, {.forwards = true});
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
