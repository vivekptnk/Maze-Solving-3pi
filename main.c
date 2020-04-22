/* Maze_solving - an application for the Pololu 3pi Robot
 *
 * Created: 4/17/2020 2:25:58 AM
 *  Author: vivek
 */

#include <pololu/3pi.h>
#include "maze_solving_algorithm.h"

void init(){
	unsigned int counter;
	//unsigned int sensors[5];
	
	pololu_3pi_init(2000);
	
	wait_for_button_release(BUTTON_B);
	delay_ms(1000);
	
	for(counter=0; counter<80; counter++){
		if(counter < 20 || counter >= 60){
			set_motors(40,-40);
		} else {
			set_motors(-40,40);
		}
		
		calibrate_line_sensors(IR_EMITTERS_ON);
		delay_ms(20);
	}
	set_motors(0,0);
}


int main()
{
	init();
	
	maze_solving_algorithm();
	
	while(1);
}
