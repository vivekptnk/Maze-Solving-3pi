#include <pololu/3pi.h>
#include "line_follow.h"
#include "turn_control.h"
#include "left_hand_on_wall.h"

//variable to store the path taken that is "R(right) L B S"
unsigned char path_length = 0;
char path_tracker[200] = "";

//we can optimize the path by eliminating dead ends (making U turns can be avoided)
void optimize_path() {
	if(path_length < 3 || path_tracker[path_length-2] != 'B'){
		return;
	}

	int angle = 0;
	int i;
	
	for(i=1; i<=3; i++)
	{
		switch(path_tracker[path_length-i])
		{
			case 'R':
				angle += 90;
				break;
			case 'L':
				angle += 270;
				break;
			case 'B':
				angle += 180;
				break;
		}
	}

	// angle should remain between 0 to 360.
	angle = angle % 360;

	//optimizing the turns with a single turn
	switch(angle)
	{
		case 0:
			path_tracker[path_length - 3] = 'S';
			break;
		case 90:
			path_tracker[path_length - 3] = 'R';
			break;
		case 180:
			path_tracker[path_length - 3] = 'B';
			break;
		case 270:
			path_tracker[path_length - 3] = 'L';
			break;
	}
	
	//since path is now shorter by 2 steps
	path_length -= 2;
}

//maze solver.
void maze_solving_algorithm()
{
	while(1)
	{
		line_follow();

		//calibrating the surface by moving ahead slowly
		set_motors(50,50);
		delay_ms(50);

		//variables to keep track of the intersections
		unsigned char left_detect1 = 0;
		unsigned char straight_detect1 = 0;
		unsigned char right_detect1 = 0;
		
		//read line sensors
		unsigned sensors[5];
		read_line(sensors, IR_EMITTERS_ON);

		//check for left or right by checking sensors[0] and sensors[4]
		if(sensors[0]>100){
			left_detect1 = 1;
		}
		if(sensors[4]>100){
			right_detect1 = 1;
		}

		// Lining up the wheels at intersection
		set_motors(40,40);
		delay_ms(200);

		// Check for a straight exit.
		read_line(sensors,IR_EMITTERS_ON);
		if(sensors[1] > 200 || sensors[2] > 200 || sensors[3] > 200)
		straight_detect1 = 1;

		//check for maze end --> all three middle sensors are on black then stop
		if(sensors[1] > 600 && sensors[2] > 600 && sensors[3] > 600)
		break;
		
		// intersection detection is done
		// we need to learn the solution if the maze isnt solved yet
		//intersection identified
		unsigned char direction = left_hand_on_wall(left_detect1, right_detect1, straight_detect1);

		// make the turn
		turn_control(direction);

		path_tracker[path_length] = direction;
		path_length ++;

		// use optimize_path() function to make the path more efficient
		optimize_path();
	}

	//loop to run maze infinite times
	while(1)
	{
		set_motors(0,0);
		
		//wait for button to be pressed
		while(!button_is_pressed(BUTTON_B))
		{
			if(get_ms() % 2000 < 1000)
			{
				clear();
				print("Solved!");
				lcd_goto_xy(0,1);
				print("Press B");
			}
			else

			delay_ms(30);
		}
		while(button_is_pressed(BUTTON_B));
		
		delay_ms(1000);
		
		int i;
		for(i=0;i<path_length;i++)
		{
			line_follow();

			//going straight before slowdown
			set_motors(50,50);
			delay_ms(50);
			set_motors(40,40);
			delay_ms(200);

			// Make a turn according to the instruction stored in
			// path[i].
			turn_control(path_tracker[i]);
		}

		line_follow();

		
	}
}

