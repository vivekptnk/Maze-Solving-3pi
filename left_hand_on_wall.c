/*
 * left_hand_on_wall.c
 *
 * Created: 5/14/2020 6:27:52 PM
 *  Author: vivek
 */ 

char left_hand_on_wall(unsigned char left_detect, unsigned char right_detect, unsigned char straight_detect){
	//we will use left-hand-on-the-wall strategy as discussed in the solutions document
	if(left_detect)
		return 'L';
	else if(straight_detect)
		return 'S';
	else if(right_detect)
		return 'R';
	else
		return 'B';
}