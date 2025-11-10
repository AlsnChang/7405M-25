#include "intake.h"
#include "pros/motors.hpp"


pros::Motor intake (15); //top & middle
pros::Motor hopper (2); //self explanatory 

pros::adi::DigitalOut flippy ('H', false);
pros::Optical opticalSensor(11);

bool flingBlue = false;

void updateIntake() 
{
    extern pros::Controller controller;
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
    {
        //Put in storage
        storageIn();
        
    }
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2))
    {
        //Score in middle goal
        scoreMiddle();
      
    }
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
    {
        colorSort();
        //Score in long goal
        scoreTop();
       
    }
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
    {
        //Outake into bottom goal
        bottomGoal();       
    }
    else
    {
        intake.brake();
        hopper.brake();
    }
}

void storageIn()
{
    //Put in storage
    flippy.set_value(false);
    hopper.move (-127);
    
}

void bottomGoal()
{
    flippy.set_value(false);
    hopper.move(127);
     
}

void stopIntake() {
    hopper.brake();
    intake.brake();
}

void scoreTop() {
    flippy.set_value(true);
    hopper.move(127);
    intake.move(127);
}

void scoreMiddle() {
    flippy.set_value(true);
    intake.move(-127); 
    hopper.move(127);
}

void load()
{
    
}

void colorSort()
{
    if (flingBlue)
    {
        if (opticalSensor.get_hue() > 75)
        {
            intake.move(-127);
            pros::lcd::set_text(1, "BLUE: " + std::to_string(opticalSensor.get_hue()));
            pros::delay(450);
        }
        else if (opticalSensor.get_hue() < 30)
        {
            intake.move(127);
            pros::lcd::set_text(1, "RED: " + std::to_string(opticalSensor.get_hue()));
        }
        else
        {
            pros::lcd::set_text(1, "NONE: " + std::to_string(opticalSensor.get_hue()));
        }
    }
    else
    {
        if (opticalSensor.get_hue() > 50)
        {
            intake.move(127);
            pros::lcd::set_text(1, "BLUE: " + std::to_string(opticalSensor.get_hue()));
        }
        else if (opticalSensor.get_hue() < 45)
        {
            intake.move(-127);
            pros::lcd::set_text(1, "RED: " + std::to_string(opticalSensor.get_hue()));
            pros::delay(450);
        }
        else
        {
            pros::lcd::set_text(1, "NONE: " + std::to_string(opticalSensor.get_hue()));
        }
    }
}
