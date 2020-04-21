#include <pololu/3pi.h>
#include "turn_control.h"
#include "intersection_handling.h"

//variable to store the path taken that is "TR TL TB GS"
char path_tracker = "";
unsigned char path_length = 0;

char turn_detect(unsigned char left_detect, unsigned char right_detect, unsigned char straight_detect){
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