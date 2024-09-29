#include "main.h"

// Controller and Motor Initialization
pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Motor leftDriveMotor1(18, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor leftDriveMotor2(19, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor leftDriveMotor3(20, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor rightDriveMotor1(8, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor rightDriveMotor2(9, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor rightDriveMotor3(10, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor liftMotor(11, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor intakeMotor(12, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);

void initialize() {
    // Motor reversals and other initialization settings
    leftDriveMotor1.set_reversed(true);
    leftDriveMotor2.set_reversed(true);
    leftDriveMotor3.set_reversed(true);
    // Set the brake mode to hold when the motors are stopped
    liftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    intakeMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
    // Example autonomous code
    liftMotor.move_absolute(100, 50); // Move lift motor to position 100 with speed 50
}

void opcontrol() {
    while (true) {
        int forward = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int turn = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);

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

        // Lift motor control with R1 and L1 buttons
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
            liftMotor.move_velocity(100);
        } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
            liftMotor.move_velocity(-100);
        } else {
            liftMotor.move_velocity(0);
        }

        // Intake motor control with R2 and L2 buttons
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            intakeMotor.move_velocity(100);
        } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
            intakeMotor.move_velocity(-100);
        } else {
            intakeMotor.move_velocity(0);
        }

        // Check motor temperatures and adjust if necessary
        if (liftMotor.get_temperature() > 50 || intakeMotor.get_temperature() > 50) {
            liftMotor.set_current_limit(1500); // Reduce current to prevent overheating
            intakeMotor.set_current_limit(1500); // Same for the intake motor
        }

        pros::delay(20); // Delay to prevent wasting CPU cycles
    }
}
