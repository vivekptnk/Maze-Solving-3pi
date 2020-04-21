#include <pololu/3pi.h>
#include "turn_control.h"
#include "intersection_handling.h"

//variable to store the path taken that is "TR TL TB GS"
char path_tracker = "";
unsigned char path_length = 0;

char turn_detection(unsigned char left_detect, unsigned char right_detect, unsigned char straight_detect){
	//we will use left-hand-on-the-wall strategy
	if(left_detect)
		return "TL";
	else if(straight_detect)
		return "GS";
	else if(right_detect)
		return "TR";
	else
		return "TB";
}


//maze solver
void maze_solver(){
	while(1){
		PID_handling();
		
		//calibrating the surface by moving ahead slowly
		set_motors(50,50);
		delay_ms(50);
		
		//variables to keep track of the intersections
		unsigned char left_detect = 0;
		unsigned char straight_detect = 0;
		unsigned char right_detect = 0;
		
		//read line sensors
		unsigned sensors[5];
		read_line(sensors, IR_EMITTERS_ON);
		
		//check for left or right by checking sensors[0] and sensors[4]
		if(sensors[0]>100){
			left_detect = 1;
		}
		
		if(sensors[4]>100){
			right_detect = 1;
		}
		
		set_motors(40,40);
		delay_ms(200);
		
		
		//check if straight exists
		if(sensors[1]>200 || sensors[2]>200 || sensors[3]>200){
			straight_detect = 1;
		}
		
		if(sensors[1] > 600 && sensors[2] > 600 && sensors[3] > 600){
			break;
		}
		
		//intersection identified
		unsigned char direction = turn_detection(left_detect, right_detect, straight_detect);
		
		//use the turn_control function to make the right turn
		turn_control(direction);
		
		// use solve_path function to make the path more efficient 
		solve_path();
		
	}
	
	//
}