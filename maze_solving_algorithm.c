#include <pololu/3pi.h>
#include "turn_control.h"
#include "PID_handling.h"

//variable to store the path taken that is "TR TL TB GS"
char path_tracker[200] = "";
unsigned char path_length = 0;

char turn_detection(unsigned char left_detect, unsigned char right_detect, unsigned char straight_detect){
	//we will use left-hand-on-the-wall strategy
	if(left_detect)
		return 'L';
	else if(straight_detect)
		return 'S';
	else if(right_detect)
		return 'R';
	else
		return 'B';
}



//we can optimize the path by eliminating dead ends (making U turns can be avoided)
void optimize_path(){
	
	if(path_length<3 || path_tracker[path_length-2] != 'B'){
		return;
	}
	
	int angle = 0;
	int i;
	
	for(i=0; i<=3; i++){
		switch(path_tracker[path_length-i]){
			case 'R':
			angle = angle + 90;
			break;
			case 'L':
			angle = angle + 270;
			break;
			case 'B':
			angle = angle + 180;
			break;
		}
	}
	
	// angle should remain between 0 to 360
	angle = angle % 360;
	
	//optimizing the turns with a single turn
	switch(angle){
		case 0:
		path_tracker[path_length-3] = 'S';
		break;
		case 90:
		path_tracker[path_length-3] = 'R';
		break;
		case 180:
		path_tracker[path_length-3] = 'B';
		break;
		case 270:
		path_tracker[path_length-3] = 'L';
		break;
	}
	
	//since path is now shorter by 2 steps
	path_length = path_length -2 ;
}


//maze solver
void maze_solving_algorithm(){
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
		
		// use optimize_path() function to make the path more efficient 
		optimize_path();	
		
	}
	
	//loop to run maze infinite times
	while(1){
		
		
		//wait for button to be pressed
		while(button_is_pressed(BUTTON_B)){
			if(get_ms() % 2000 < 1000){
				clear();
				print("solved");
				lcd_goto_xy(0,1);
				print("Press B");
			}
			
			delay_ms(30);
		}
		
		while(button_is_pressed(BUTTON_B));
		
		delay_ms(1000);
		
		
		int i;
		for(i=0; i<path_length; i++){
			PID_handling();
			
			//going straight slowly 
			set_motors(50,50);
			delay_ms(50);
			set_motors(40,40);
			delay_ms(200);
			
			turn_control(path_tracker[i]);
			
		}
		
		PID_handling();
	}
}
