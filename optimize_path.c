#include <pololu/3pi.h>
#include "maze_solving_algorithm.h"

//variable to store the path taken that is "R(right) L B S"
unsigned char path_length = 0;
char path_tracker[200] = "";


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
