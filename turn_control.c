#include <pololu/3pi.h>

void turn_control(char direction){
	switch(direction)
	{
		case 'TL':
			//turn left
			set_motors(-80,80);
			delay_ms(200);
			break;
		
		case 'TR':
			//turn right 
			set_motors(80,-80);
			delay(200);
			break;
			
		case 'TB':
			//turn back 
			set_motors(80,-80);
			delay_ms(400);
			break;
		case 'GS': // go straight
			// no action
			break;
	}
}

