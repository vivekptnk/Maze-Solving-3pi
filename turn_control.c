#include <pololu/3pi.h>

void turn_control(char direction){
	switch(direction)
	{
		case 'L':
			//turn left
			set_motors(-80,80);
			delay_ms(200);
			break;
		
		case 'R':
			//turn right 
			set_motors(80,-80);
			delay(200);
			break;
			
		case 'B':
			//turn back 
			set_motors(80,-80);
			delay_ms(400);
			break;
			
		case 'S': // go straight
			// no action
			break;
	}
}

