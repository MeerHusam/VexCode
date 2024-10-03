#include "main.h"
// #include "robot-config.h"

#include "pros/apix.h"  
using namespace pros;

#define DIGITAL_SENSOR_PORT 'B'

pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Motor leftDriveMotor1(18); 
pros::Motor leftDriveMotor2(19); 
pros::Motor leftDriveMotor3(20); 
pros::Motor rightDriveMotor1(8);
pros::Motor rightDriveMotor2(9);
pros::Motor rightDriveMotor3(10);
pros::Motor intake(5);
pros::ADIDigitalOut piston (DIGITAL_SENSOR_PORT);

void initialize() {
    leftDriveMotor1.set_reversed(true);
    leftDriveMotor2.set_reversed(true);
    leftDriveMotor3.set_reversed(true);

    intake.set_reversed(true);
}

void disabled() {
    // Code for when the robot is disabled
}

void competition_initialize() {
    // Code for initializing the robot for competition
}

void autonomous() {
    // Autonomous code
}

void opcontrol() {
    bool pistonOn = false;
    while (true) {
        // Retrieve joystick values from the controller
        int forward = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int turn = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);

        int forwardIntake = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

        // Calculate the motor speeds based on joystick inputs
        int leftMotorSpeed = forward + turn;
        int rightMotorSpeed = forward - turn;

        // Set the motors to run at calculated speeds
        leftDriveMotor1.move(leftMotorSpeed);
        leftDriveMotor2.move(leftMotorSpeed);
        leftDriveMotor3.move(leftMotorSpeed);
        rightDriveMotor1.move(rightMotorSpeed);
        rightDriveMotor2.move(rightMotorSpeed);
        rightDriveMotor3.move(rightMotorSpeed);


        // Intake
        intake.move(forwardIntake);

        // Pneumatics
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
            pros::delay(200);
            if (pistonOn){
                pistonOn = false;
                piston.set_value(false);
            }
            else{
                pistonOn = true;
                piston.set_value(true);
            }

        // Wait for a short time to prevent wasting CPU cycles
        pros::delay(20);
    }
}
}