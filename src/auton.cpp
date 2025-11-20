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
    chassis.moveToPoint(40, 20,5000, {.forwards = false});
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
