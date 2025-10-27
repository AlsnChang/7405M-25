#include "intake.h"
#include "pros/motors.hpp"


pros::Motor intake (19); //top & middle
pros::Motor hopper (1); //self explanatory 

pros::adi::DigitalOut hood ('H', false);
pros::Optical opticalSensor(2);

bool flingBlue = false;

void updateIntake() 
{
    extern pros::Controller controller;
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
    {
        //Put in storage
        //colorSort();
        storageIn();
        
    }
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2))
    {
        //Score in middle goal
        scoreMiddle();
      
    }
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
    {
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
    hopper.move (-100);
    
}

void bottomGoal()
{
    hopper.move(100);
     
}
void stopIntake() {
    hopper.brake();
    intake.brake();
    

}
void scoreTop() {
    hopper.move(100);
    intake.move(-100);
}
void scoreMiddle() {
    intake.move(100); 
    hopper.move(100);
}

void colorSort()
{
    if (flingBlue)
    {
        if (opticalSensor.get_hue() > 75)
        {
            secondIn.move(150);
            pros::lcd::set_text(1, "BLUE: " + std::to_string(opticalSensor.get_hue()));
            pros::delay(450);
        }
        else if (opticalSensor.get_hue() < 30)
        {
            secondIn.move(-150);
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
            secondIn.move(-255);
            pros::lcd::set_text(1, "BLUE: " + std::to_string(opticalSensor.get_hue()));
        }
        else if (opticalSensor.get_hue() < 45)
        {
            secondIn.move(255);
            pros::lcd::set_text(1, "RED: " + std::to_string(opticalSensor.get_hue()));
            pros::delay(450);
        }
        else
        {
            pros::lcd::set_text(1, "NONE: " + std::to_string(opticalSensor.get_hue()));
        }
    }
}