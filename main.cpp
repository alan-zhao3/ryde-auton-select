#include "main.h"
#include "auton_selector.h"
#include "lemlib/api.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/rtos.h"
#include "pros/rtos.hpp"

using namespace pros;

	pros::Controller controller(pros::E_CONTROLLER_MASTER);
	pros::MotorGroup left_mg({-11, -12, 13});    
	pros::MotorGroup right_mg({-18, 19, 20});  

	pros::Motor intake(-1);
    pros::Motor middle(-2);
    pros::Motor outtake(3);
	pros::Optical optical(10);
	pros::adi::DigitalOut gate('C');//high is down
    pros::adi::DigitalOut matchLoader('B');//high is down
    pros::adi::DigitalOut descoreWing('A');//low is down
	pros::adi::Ultrasonic distanceReset ('G', 'H');

	lemlib::Drivetrain drivetrain(&left_mg, // left motor group
                             &right_mg, // right motor group
                             11.9,
                             lemlib::Omniwheel::NEW_325,
                             450, // drivetrain rpm is 450
                             2
   );

   pros::Imu imu(16);


// horizontal tracking wheel

// vertical tracking wheel


   lemlib::OdomSensors sensors(nullptr, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            nullptr, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

   // lateral PID controller
lemlib::ControllerSettings lateral_controller(6, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              8.5, // derivative gain (kD)
                                              0, // anti windup
                                              0, // small error range, in inches
                                              0, // small error range timeout, in milliseconds
                                              0, // large error range, in inches
                                              0, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// angular PID controller
lemlib::ControllerSettings angular_controller(2, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              13, // derivative gain (kD)
                                              0, // anti windup
                                              0, // small error range, in degrees
                                              0, // small error range timeout, in milliseconds
                                              0, // large error range, in degrees
                                              0, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors // odometry sensors
);

void update_telemetry(lemlib::Chassis &chassis, pros::MotorGroup &left_mg, pros::MotorGroup &right_mg, pros::Motor &intake, pros::Motor &middle, pros::Motor &outtake) {
    // populate telemetry display as needed
}

static void telemetry_timer_cb(lv_timer_t* timer) {
    update_telemetry(chassis, left_mg, right_mg, intake, middle, outtake);
}

// ---------------- PROS Hooks ----------------
void initialize() {
    chassis.calibrate();
    while (imu.is_calibrating()) pros::delay(10);

    create_selector_ui();
    lv_timer_create(telemetry_timer_cb, 200, nullptr);
}

void autonomous() {
    if (selected_auton_id < 0) return;
    
    printf("[AUTO] Running %d: %s\n", selected_auton_id, AUTON_NAMES[selected_auton_id]);

    switch (selected_auton_id) {
        case 0: 
            chassis.setPose(0, 0, 0);
            intake.move(127);
            middle.move(127);
            chassis.moveToPose(16.32, 25,90, 5000);
            chassis.turnToPoint(41.32, 0.098, 5000);
            middle.brake();
            chassis.moveToPoint(41.32, 0.098, 5000);
            chassis.turnToHeading(180, 5000);
            matchLoader.set_value(true);
            chassis.moveToPoint(41.32, -14.988, 5000);
            pros::delay(1000);
            chassis.moveToPoint(41.32, 18.291, 5000, {.forwards = false});
            chassis.waitUntilDone();
            middle.move(127);
            outtake.move(127);
            gate.set_value(true);
            matchLoader.set_value(false);
            pros::delay(1000);
            chassis.swingToHeading(0, DriveSide::LEFT, 5000);
            descoreWing.set_value(true);
            chassis.moveToPoint(30.32, 40, 5000);
            intake.brake();
            middle.brake();
            outtake.brake();
            gate.set_value(false);

            // Add your autonomous code here
            break;
        case 1: // Auto Left 2
            chassis.setPose(0, 0, 0);
            intake.move(127);
            middle.move(127);
            chassis.moveToPose(16.32, 25,90, 5000);
            chassis.turnToPoint(41.32, 0.098, 5000);
            middle.brake();
            chassis.moveToPoint(41.32, 0.098, 5000);
            chassis.turnToHeading(180, 5000);
            matchLoader.set_value(true);
            chassis.moveToPoint(41.32, -14.988, 5000);
            pros::delay(1000);
            chassis.moveToPoint(41.32, 18.291, 5000, {.forwards = false});
            chassis.waitUntilDone();
            middle.move(127);
            outtake.move(127);
            gate.set_value(true);
            matchLoader.set_value(false);
            pros::delay(1000);
            chassis.swingToHeading(0, DriveSide::LEFT, 5000);
            descoreWing.set_value(true);
            chassis.moveToPoint(30.32, 40, 5000);
            intake.brake();
            middle.brake();
            outtake.brake();
            gate.set_value(false);


            break;
        case 2: // Auto Right 1
            chassis.setPose(0, 0, 0);
            intake.move(127);
            middle.move(127);
            chassis.moveToPoint(0, 41.32, 5000);
            chassis.turnToHeading(90, 5000);
            matchLoader.set_value(true);
            chassis.moveToPoint(14.767, 41.32, 5000);
            chassis.moveToPoint(-20.748, 41.32, 5000, {.forwards = false});
            chassis.waitUntilDone();
            outtake.move(127);
            gate.set_value(true);
            pros::delay(1000);
            chassis.moveToPoint(0, 41.32, 5000);
            gate.set_value(false);
            outtake.brake();
            chassis.turnToPoint(-25, 16.32, 5000);
            chassis.moveToPoint(-25, 16.32, 5000);
            chassis.moveToPoint(-32, 9.32, 5000);
            chassis.waitUntilDone();
            intake.move(-127);
            middle.move(-127);
            pros::delay(1000);
            chassis.moveToPoint(-10, 31.32, 5000, {.forwards = false});
            chassis.turnToHeading(-270, 1000);
            descoreWing.set_value(true);
            chassis.moveToPoint(-24.541, 31.32, 5000);

            break;
        case 3: // Auto Right 2
            chassis.setPose(0, 0, 0);
            intake.move(127);
            middle.move(127);
            chassis.moveToPoint(0, -41.32, 5000);
            chassis.turnToHeading(90, 5000);
            matchLoader.set_value(true);
            chassis.moveToPoint(-14.767, -41.32, 5000);
            chassis.moveToPoint(20.748, -41.32, 5000, {.forwards = false});
            chassis.waitUntilDone();
            outtake.move(127);
            gate.set_value(true);
            pros::delay(1000);
            chassis.moveToPoint(0, -41.32, 5000);
            gate.set_value(false);
            outtake.brake();
            chassis.turnToPoint(25, -16.32, 5000);
            chassis.moveToPoint(25, -16.32, 5000);
            chassis.moveToPoint(32, -9.32, 5000);
            chassis.waitUntilDone();
            intake.move(-127);
            middle.move(-127);
            pros::delay(1000);
            chassis.moveToPoint(10, -31.32, 5000, {.forwards = false});
            chassis.turnToHeading(-270, 1000);
            descoreWing.set_value(true);
            chassis.moveToPoint(24.541, -31.32, 5000);


            break;
        case 4: // Center Score
            chassis.setPose(0, 0, 0);
            intake.move(127);
            middle.move(127);
            chassis.moveToPoint(0, 39.24, 5000);
            chassis.turnToHeading(90, 5000);
            matchLoader.set_value(true);
            chassis.moveToPoint(12.76, 39.24, 5000);
            pros::delay(1000);
            chassis.moveToPoint(-18.975, 39.24, 5000, {.forwards = false});
            chassis.waitUntilDone();
            outtake.move(127);
            gate.set_value(true);
            pros::delay(1000);
            gate.set_value(false);
            outtake.brake();
            chassis.swingToPoint(-24.62, 15.62, DriveSide::LEFT, 5000);
            chassis.moveToPoint(-24.62, 15.62, 5000);
            chassis.moveToPoint(-24.62, -31.62, 5000);
            chassis.turnToHeading(135, 5000);
            chassis.moveToPoint(-35.62, -20.62, 5000, {.forwards = false});
            chassis.waitUntilDone();
            middle.move(127);
            outtake.move(-127);
            pros::delay(1000);
            outtake.brake();
            chassis.moveToPoint(12.76, -55.24, 5000);
            chassis.moveToPoint(-18.975, -55.24, 5000, {.forwards = false});
            chassis.waitUntilDone();
            outtake.move(127);
            gate.set_value(true);



            break;
        case 5: // Defense
            break;
        case 6: // DEBUG TEST
            break;
    }
}

void opcontrol() {
	bool matchloader = false;
	bool r2_pressed = false;
	unsigned long r2_press_time = 0;
	bool object_detected = false;
	unsigned long detect_start_time = 0;
	bool descoreWingDeployed = true;

	while (true) {

		
		// get left y and right x positions
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
		chassis.arcade(leftY, rightX);
		if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
		intake.move(127);
		int proximity = optical.get_proximity();
		if (proximity > 150) {  // object detected
			if (!object_detected) {
				object_detected = true;
				detect_start_time = pros::millis();
			}
			if (pros::millis() - detect_start_time >= 500) { // 500 ms
				middle.brake();
			} else {
				middle.move(127);
			}
		} else {  // no object detected
			object_detected = false;
			middle.move(127);
		}
		} else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
			descoreWingDeployed = !descoreWingDeployed;   // toggle the bool
    		descoreWing.set_value(descoreWingDeployed);
		} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
			gate.set_value(true);
			intake.move(127);
			middle.move(127);
			outtake.move(127);

		} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
			if (!r2_pressed) {
				r2_pressed = true;
				r2_press_time = pros::millis();
				gate.set_value(true);
				intake.move(-127);
				middle.move(-127);
				outtake.move(-50);
			} else if (pros::millis() - r2_press_time >= 200) {
				intake.move(127);
				middle.move(127);
				outtake.move(-50);
			}
		} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {
			intake.move(-127);
			middle.move(-127);
		} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
			intake.move(127);
			middle.move(127);
		}else {
			r2_pressed = false;
			intake.brake();
			middle.brake();
			outtake.brake();
			gate.set_value(false);
		}

		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)){
			if(matchloader == false) {
		matchLoader.set_value(true);
		matchloader = true;
		} else if (matchloader == true) {
		matchLoader.set_value(false);
		matchloader = false;
			}
		}

        // move the robot
        chassis.arcade(leftY, rightX);
		// Arcade control scheme
		pros::delay(20);                               // Run for 20 ms then update
	}
}

void disabled() {}
void competition_initialize() {}