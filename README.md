# ryde-auton-select
an vex v5 auton selector made by ryde secondary collage for LemLib: 0.5.6, kernel: 4.2.2, liblvgl: 9.2.0. 


Instructions(open read me in code mode or raw as lines dont load properly in preveiw or idk how to):
 1. create 2 new files being the same as the ones attached, auton_selector.cpp and auton_selector.h by righclicking on src and create new file for .cpp and rightclicking on include for .header (.h)
  
 2. copy and paste the contents of each file attached exculding main.cpp

 3. in main.cpp add #include "auton_selector.h" at the top

 4. in main.cpp again, replace initilize with this code and replace intake, middle, outtake with the motor names from your robot or code:

		void update_telemetry(lemlib::Chassis &chassis, pros::MotorGroup &left_mg, pros::MotorGroup &right_mg, pros::Motor &intake, pros::Motor 		   &middle, pros::Motor &outtake) {
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

 5. replace void auton with: and insert your own auton routes into the code(recomended to create a duplicate copy without auton selector for testing)

		void autonomous() {
    	if (selected_auton_id < 0) return;
    
   		 printf("[AUTO] Running %d: %s\n", selected_auton_id, AUTON_NAMES[selected_auton_id]);

    	switch (selected_auton_id) {
        case 0: //1
            // Add your autonomous code here
            break;
        case 1: // 2
            break;
        case 2: // 3
            break;
        case 3: // 4
            break;
        case 4: // 5
            break;
        case 5: // 6
            break;
        case 6: // 7
            break;
  		  }
		}
 7. to change auton names look for:const char* AUTON_NAMES[7] = { in auton_selector.cpp and replace
  
 9. save and upload to brain
