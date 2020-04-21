/*
 * Created: 4/19/2020 1:29:45 AM
 *  Author: vivek
 */ 
#include <pololu/3pi.h>

void PID_handling(){
	long integral_value = 0;
	int final_proportional = 0;
	
	
	//basically line following code 
	while(){
		unsigned int sensors[5];
		unsigned int position  = read_line(sensors, IR_EMITTERS_ON);
		
		//Computing the P in PID
		//Should be zero when on line. 
		int current_proportional = ((int)position) - 2000;
		
		//Computing the D in PID
		int current_deriviative = current_proportional - final_proportional;
		
		//Computing I in PID
		integral_value = integral_value + current_proportional;
		
		//Store the final position
		final_proportional = current_proportional;
		
		//Speed Handling among the motors
		int power_difference = current_proportional/20 + integral_value/10000 + current_deriviative*3/2;
		
		//Motor settings
		const int max_speed = 60; //max speed
		if(power_difference > max_speed)
			power_difference = max_speed;
		if(power_difference < -max_speed)
			power_difference = -max_speed;
			
		if(power_difference < 0)
			set_motors(max_speed+power_difference, max_speed);
		else 
			set_motors(max_speed, max_speed-power_difference);
		
		// Inner Sensors, 2,3,4 (basically sensors[1], sensors[2], sensor[3])will be used to detect if the line is straight
		// and sensors 1(sensors[0]) and 5(sensors[4]) will be detecting if the lines are going left or right. 
		if(sensors[1]<100 && sensors[2]<100 && sensors[3]<100){
			//no line 
			//its probably an dead end
		} else if(sensors[0]>200 || sensors[4]>200){
			//its an intersection
			return;
		}
		
	}
}