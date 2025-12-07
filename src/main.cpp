#include "main.h"
#include "autons.h"
#include "autonselector.h"
#include "intake.h"
#include "lemlib/api.hpp"
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "pros/motors.hpp"
#include "pros/optical.hpp"

pros::Controller controller(pros::E_CONTROLLER_MASTER);

// motor groups
// pros::MotorGroup leftMotors({-20, -18, -10},
//                             pros::MotorGearset::blue); // left motor group -
//                             ports 3 (reversed), 4, 5 (reversed)
// pros::MotorGroup rightMotors({12, 5, 6}, pros::MotorGearset::blue); // right
// motor group - ports 6, 7, 9 (reversed)

pros::MotorGroup
    leftMotors({-10, -15, -20},
               pros::MotorGearset::blue); // left motor group - ports 3
                                          // (reversed), 4, 5 (reversed)
pros::MotorGroup rightMotors(
    {4, 5, 11},
    pros::MotorGearset::blue); // right motor group - ports 6, 7, 9 (reversed)

lemlib::Drivetrain drivetrain(&leftMotors,  // left motor group
                              &rightMotors, // right motor group
                              12,           // 10 inch track width
                              lemlib::Omniwheel::NEW_325,
                              450, // drivetrain rpm is 450
                              2    // horizontal drift is 2 (for now)
);

pros::Imu imu(12);
pros::Distance distance_sensor(7);


pros::Rotation horizontal_encoder(-3); // odom sensor
lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_encoder,
                                                lemlib::Omniwheel::NEW_2, -1);

pros::Rotation vertical_encoder(16); // odom sensor
lemlib::TrackingWheel vertical_tracking_wheel(&vertical_encoder,
                                              lemlib::Omniwheel::NEW_2, -0.5);

lemlib::OdomSensors sensors(&vertical_tracking_wheel, nullptr,
                            &horizontal_tracking_wheel, nullptr, &imu);

                        

lemlib::ControllerSettings
    lateral(7.25, // proportional gain (kP)
            0,    // integral gain (kI)
            50,   // derivative gain (kD)
            3,    // anti windup
            .5,   // small error range, in inches
            100,  // small error range timeout, in milliseconds
            1,    // large error range, in inches
            2000, // large error range timeout, in milliseconds
            20    // maximum acceleration (slew)
    );

lemlib::ControllerSettings
    angular(1.1,  // proportional gain (kP)
            0,    // integral gain (kI)
            5,    // derivative gain (kD)
            3,    // anti windup
            1,    // small error range, in degrees
            1000, // small error range timeout, in milliseconds
            2,    // large error range, in degrees
            2000, // large error range timeout, in milliseconds
            0     // maximum acceleration (slew)
    );
lemlib::ExpoDriveCurve throttle(3, 10, 1.019);
lemlib::ExpoDriveCurve steer(3, 10, 1.019);

// Chassis with dummy settings
lemlib::Chassis chassis(drivetrain, lateral, angular, sensors, &throttle,
                        &steer);

// Scraper
pros::adi::DigitalOut scraper('A', false);
pros::adi::DigitalOut aligner('F', false);
pros::adi::DigitalOut remover('G', false);
pros::adi::DigitalOut odomlift('D', false);

// wing
bool removerActivated = false;
bool hoodActivated = false;
bool scraperActivated = false;

// flingBlue = false;
bool removerPressedLast = false;
bool hoodPressedLast = false;
bool scraperPressedLast = false;

void coord() {
  // loop forever
  while (true) {
    lemlib::Pose pose = chassis.getPose();
    pros::lcd::print(0, "x: %.2f | y: %.2f | H: %.2f", pose.x, pose.y,
                     pose.theta);
    pros::lcd::print(1, "theta: %.2f", pose.theta);

    // lemlib::Pose pose = chassis.getPose(); // get the current position of the
    // robot pros::lcd::print(0, "x: %f | y: %f", pose.x, pose.y, pose.theta);
    // // print the x position
    // //pros::lcd::print(0, "x: %f | y: %f", horizontal_encoder.get_position(),
    // vertical_encoder.get_position(), pose.theta); // print the x position
    // pros::lcd::print(1, "H: %f", pose.theta); // print the x position
    // // printf("x: %f | y: %f | H: %f | rot: %d \n", pose.x, pose.y,
    // pose.theta, vertical_rot.get_position());
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
    lemlib::Pose pose =
        chassis.getPose(); // get the current position of the robot
    pros::lcd::print(0, "x: %f | y: %f", pose.x, pose.y,
                     pose.theta);             // print the x position
    pros::lcd::print(1, "H: %f", pose.theta); // print the x position
    // printf("x: %f | y: %f | H: %f | rot: %d \n", pose.x, pose.y, pose.theta,
    // vertical_rot.get_position());
    pros::delay(10);
  }
}

void initialize() {
  pros::lcd::initialize();
  chassis.calibrate();
  pros::delay(1000);
  chassis.setPose(0, 0, 0);
  horizontal_encoder.reset_position();
  vertical_encoder.reset_position();
  pros::lcd::initialize(); // initialize brain screen
  leftMotors.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  rightMotors.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  opticalSensor.set_led_pwm(100);

  pros::delay(1000);
  autonSelectorStart();
  pros::Task screenTask(screen);
  

  // pros::Task updateScreen (coord);
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
 * This is an example autonomous routine which demonstrates a lot of the
 * features LemLib has to offer
 */

void skills() {
  
}

void autonomous() {

  odomlift.set_value(true);
  //Just park in the parking zone
  //skillsPark();
  
  //Actually tries to do stuff in skilla
  //skillsTest();

  // GOOOD AUTON FOR THE RIGHT SIDE
  fastBottomGoals();

  // BAD AUTON FOR THE LEFT SIDE
 //fastTopGoal();

  // 7 BALLS AUTON BOTTOM GOAL
  // bottomControl();
}

void opcontrol() {

  aligner.set_value(false);
  flingBlue = false;

  while (true) {
    int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    chassis.arcade(leftY, rightX);

    bool removerPressedNow =
        controller.get_digital(pros::E_CONTROLLER_DIGITAL_A);

    if (removerPressedNow && !removerPressedLast) {
      // Toggle remover
      removerActivated = !removerActivated;
      remover.set_value(removerActivated);
    }

    removerPressedLast = removerPressedNow;

    bool scraperPressedNow =
        controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP);

    if (scraperPressedNow && !scraperPressedLast) {
      // Toggle hood
      scraperActivated = !scraperActivated;
      scraper.set_value(scraperActivated);
      aligner.set_value(!scraperActivated);
    }

    scraperPressedLast = scraperPressedNow;

    updateIntake();

    pros::delay(20);
  }
}