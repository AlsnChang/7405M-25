#include "main.h"
#include "intake.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "pros/motors.hpp"
#include "lemlib/api.hpp"
#include "autons.h"
#include "autonSelector.h"

pros::Controller controller(pros::E_CONTROLLER_MASTER);

// motor groups
// pros::MotorGroup leftMotors({-20, -18, -10},
//                             pros::MotorGearset::blue); // left motor group - ports 3 (reversed), 4, 5 (reversed)
// pros::MotorGroup rightMotors({12, 5, 6}, pros::MotorGearset::blue); // right motor group - ports 6, 7, 9 (reversed)

pros::MotorGroup leftMotors({-10, -15, -20},
                            pros::MotorGearset::blue); // left motor group - ports 3 (reversed), 4, 5 (reversed)
pros::MotorGroup rightMotors({4, 5, 11}, pros::MotorGearset::blue); // right motor group - ports 6, 7, 9 (reversed)


lemlib::Drivetrain drivetrain(&leftMotors, // left motor group
                              &rightMotors, // right motor group
                              12, // 10 inch track width
                              lemlib::Omniwheel::NEW_325,
                              450, // drivetrain rpm is 450
                              2 // horizontal drift is 2 (for now)
);

pros::Imu imu(12);

pros::Rotation horizontal_encoder(-3); //odom sensor
lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_encoder, lemlib::Omniwheel::NEW_2, -1);

pros::Rotation vertical_encoder(17); //odom sensor
lemlib::TrackingWheel vertical_tracking_wheel(&vertical_encoder, lemlib::Omniwheel::NEW_2, -0.5);

lemlib::OdomSensors sensors(&vertical_tracking_wheel, nullptr, &horizontal_tracking_wheel, nullptr, &imu);


lemlib::ControllerSettings lateral(8.9, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              17.6, // derivative gain (kD)
                                              3, // anti windup
                                              .5, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              1, // large error range, in inches
                                              2000, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);

lemlib::ControllerSettings angular(1.1, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              8, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in degrees
                                              1000, // small error range timeout, in milliseconds
                                              2, // large error range, in degrees
                                              2000, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);
lemlib::ExpoDriveCurve throttle(3, 10, 1.019);
lemlib::ExpoDriveCurve steer(3, 10, 1.019);

// Chassis with dummy settings
lemlib::Chassis chassis(drivetrain, lateral, angular, sensors, &throttle, &steer);

//Scraper
pros::ADIDigitalOut scraper ('A', false);

bool hoodActivated = false;
bool scraperActivated = false;

//flingBlue = false;
bool hoodPressedLast = false;
bool scraperPressedLast = false;

void coord()
{
    // loop forever
    while (true) {
        lemlib::Pose pose = chassis.getPose();
        pros::lcd::print(0, "x: %.2f | y: %.2f | H: %.2f", pose.x, pose.y, pose.theta);
        pros::lcd::print(1, "theta: %.2f", pose.theta);

        // lemlib::Pose pose = chassis.getPose(); // get the current position of the robot
        // pros::lcd::print(0, "x: %f | y: %f", pose.x, pose.y, pose.theta); // print the x position
        // //pros::lcd::print(0, "x: %f | y: %f", horizontal_encoder.get_position(), vertical_encoder.get_position(), pose.theta); // print the x position
        // pros::lcd::print(1, "H: %f", pose.theta); // print the x position
        // // printf("x: %f | y: %f | H: %f | rot: %d \n", pose.x, pose.y, pose.theta, vertical_rot.get_position());
        pros::delay(100);
    }

    // while (true)
    // {
    //     lemlib::Pose pose = chassis.getPose();
    //     pros::lcd::print(1, "x: %f | y: %f", pose.x, pose.y);
    //     pros::lcd::print(2, "Theta: %f", pose.theta);
    //     // if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_A))
    //     // {
    //     //     printf("x: %f | y: %f | Theta: %f", pose.x, pose.y);
    //     //     printf("Theta: %f", pose.theta);
    //     // }

    //     pros::delay(50);
    // }

}
// drivetrain settings
/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void screen() {
    // loop forever
    while (true) {
        lemlib::Pose pose = chassis.getPose(); // get the current position of the robot
        pros::lcd::print(0, "x: %f | y: %f", pose.x, pose.y, pose.theta); // print the x position
        pros::lcd::print(1, "H: %f", pose.theta); // print the x position
        // printf("x: %f | y: %f | H: %f | rot: %d \n", pose.x, pose.y, pose.theta, vertical_rot.get_position());
        pros::delay(10);
    }
}

void initialize() {
    pros::lcd::initialize();
    chassis.calibrate();
    chassis.setPose(0,0,0);
    horizontal_encoder.reset_position();
    vertical_encoder.reset_position();
    pros::lcd::initialize(); // initialize brain screen
    leftMotors.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    rightMotors.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    opticalSensor.set_led_pwm(100);

    pros::delay(1000);
    //autonSelectorStart();
    pros::Task screenTask(screen);
   
    
    //pros::Task updateScreen (coord);
}

/**
 * Runs while the robot is disabled
 */
void disabled() {}

/**
 * runs after initialize if the robot is connected to field control
 */
void competition_initialize() {}

// get a path used for pure pursuit
// this needs to be put outside a function

/**
 * Runs during auto
 *
 * This is an example autonomous routine which demonstrates a lot of the features LemLib has to offer
 */
void skills() {
    pros::delay(3);
    chassis.moveToPoint(0,11,1000);
    chassis.turnToHeading(90, 750, {.maxSpeed = 90});
    storageIn();
    chassis.moveToPoint(40, 11,1000);
    chassis.turnToHeading(180, 750, {.maxSpeed = 90});
    
    scraper.set_value(true);
    chassis.moveToPoint(44, -7, 2000,{.minSpeed=100});
    pros::delay(1500);
}

void blueRight() {
    //storageIn();
    chassis.moveToPoint(0, 20, 3000);
    //chassis.turnToHeading(-80, 750, {.maxSpeed = 50});
    // chassis.moveToPoint();
    // bottomGoal();
}

void autonomous() 
{

    blueRight();
    //startAuton();

    


}



void opcontrol() 
{
    //skills
    blueRight();
    


    // chassis.moveToPoint(40,15,3000);
    // chassis.turnToPoint(40,15,90);
    // scraper.set_value(true);
    // storageIn();
    // chassis.moveToPoint(40, -10, 1000);   
//     while (true)
//     {
//         int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
//         int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

// 		chassis.arcade(leftY, rightX);
// /*
//         bool hoodPressedNow = controller.get_digital(pros::E_CONTROLLER_DIGITAL_A);

//         if (hoodPressedNow && !hoodPressedLast) {
//             // Toggle hood
//             hoodActivated = !hoodActivated;
//             hood.set_value(hoodActivated);
//         } 

//         hoodPressedLast = hoodPressedNow; */

//         bool scraperPressedNow = controller.get_digital(pros::E_CONTROLLER_DIGITAL_A);

//         if (scraperPressedNow && !scraperPressedLast) {
//             // Toggle hood
//             scraperActivated = !scraperActivated;
//             scraper.set_value(scraperActivated);
//         }

//         scraperPressedLast = scraperPressedNow;
        
//         updateIntake();
//         pros::delay(20);
//     }
}
