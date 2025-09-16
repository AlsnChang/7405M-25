#include "intake.h"
#include "pros/motors.hpp"


pros::Motor secondIn (-18);
pros::Motor firstIn (17);
pros::Motor hopper (5);

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
        firstIn.move(-160);
        secondIn.move(-160);
        hood.set_value(true);
    }
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2))
    {
        //Score in middle goal
        firstIn.move(-160);
        secondIn.move(160);
        hopper.move(160);
        hood.set_value(false);  
    }
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
    {
        //Score in long goal
        firstIn.move(-160);
        secondIn.move(-160);
        hopper.move(160);
        hood.set_value(false);
    }
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
    {
        //Outake into bottom goal
        firstIn.move(160);
        hopper.move(160); 
    }
    else
    {
        secondIn.brake();
        hopper.brake();
        firstIn.brake();
    }
}

void storageIn()
{
    //Put in storage
    firstIn.move_velocity(-200);
    secondIn.move_velocity(-200);
    hood.set_value(true);
}

void bottomGoal()
{
    firstIn.move(80);
    hopper.move(75); 
}
void stopIntake() {
    firstIn.move(0);
    secondIn.move(0);
    hopper.move(0);

}
void scoreTop() {
    firstIn.move(-127);
    secondIn.move(-127);
    hopper.move(127);

    double actualVel = secondIn.get_actual_velocity();
    if (actualVel==0) {
        pros::lcd::print(0, "uhoh!");
    }


}
void scoreMiddle() {
    firstIn.move(-100);
    secondIn.move(100);
    hopper.move(127);
       
    
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