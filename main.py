#region VEXcode Generated Robot Configuration
from vex import *
import urandom

# Brain should be defined by default
brain=Brain()

# Robot configuration code
digital_out_b = DigitalOut(brain.three_wire_port.b)


# wait for rotation sensor to fully initialize
wait(30, MSEC)


# Make random actually random
def initializeRandomSeed():
    wait(100, MSEC)
    random = brain.battery.voltage(MV) + brain.battery.current(CurrentUnits.AMP) * 100 + brain.timer.system_high_res()
    urandom.seed(int(random))
      
# Set random seed 
initializeRandomSeed()


def play_vexcode_sound(sound_name):
    # Helper to make playing sounds from the V5 in VEXcode easier and
    # keeps the code cleaner by making it clear what is happening.
    print("VEXPlaySound:" + sound_name)
    wait(5, MSEC)

# add a small delay to make sure we don't print in the middle of the REPL header
wait(200, MSEC)
# clear the console to make sure we don't have the REPL in the console
print("\033[2J")

#endregion VEXcode Generated Robot Configuration

# ----------------------------------------------------------------------------- #
#                                                                               #             
# 	Project:        Drivetrain Sensing                                          #
#   Module:         main.py                                                     #
#   Author:         VEX                                                         #
#   Created:        Fri Aug 05 2022                                             #
#	Description:    This example will show all of the available commands        #
#                   for using the Drivetrain                                    #
#                                                                               #                                                                          
#   Configuration:  V5 Speedbot (Drivetrain 4-motor, No Gyro)                   #
#                                                                               #                                                                          
# ----------------------------------------------------------------------------- #

# Library imports
from vex import *

# Brain should be defined by default
brain = Brain()

# Robot configuration code with 6 motors (3 on each side)
left_drive_motor_1 = Motor(Ports.PORT1, GearSetting.RATIO_36_1, True)
left_drive_motor_2 = Motor(Ports.PORT2, GearSetting.RATIO_36_1, True)
left_drive_motor_3 = Motor(Ports.PORT3, GearSetting.RATIO_36_1, True)
right_drive_motor_1 = Motor(Ports.PORT11, GearSetting.RATIO_36_1, False)
right_drive_motor_2 = Motor(Ports.PORT12, GearSetting.RATIO_36_1, False)
right_drive_motor_3 = Motor(Ports.PORT13, GearSetting.RATIO_36_1, False)

# Group the left and right motors together
left_drive = MotorGroup(left_drive_motor_1, left_drive_motor_2, left_drive_motor_3)
right_drive = MotorGroup(right_drive_motor_1, right_drive_motor_2, right_drive_motor_3)

# Define the drivetrain with the motors and updated gear ratio
drivetrain = DriveTrain(left_drive, right_drive, 319.19, 295, 40, MM, 1)

# Define the controller
controller = Controller()
# Function to control the drivetrain and the piston
def control_drivetrain_and_piston():
    piston_state = False  # Keep track of the piston state (True = activated, False = deactivated)
    
    while True:
        # Get the values from the right analog stick
        forward_backward = controller.axis2.position()
        turn = controller.axis1.position()

        # Set the velocities of the left and right motors based on joystick input
        left_speed = forward_backward + turn
        right_speed = forward_backward - turn

        left_drive.spin(FORWARD, left_speed, PERCENT)
        right_drive.spin(FORWARD, right_speed, PERCENT)

        # Check if the B button is pressed to toggle the piston
        if controller.buttonB.pressing():
            piston_state = not piston_state  # Toggle the state
            digital_out_b.set(piston_state)  # Set the digital output
            wait(300, MSEC)  # Add a small delay to prevent rapid toggling

        # A brief delay to prevent spamming the CPU
        wait(20, MSEC)

# Start the drivetrain and piston control
control_drivetrain_and_piston()
