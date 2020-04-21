/*
 * Created: 4/19/2020 1:29:45 AM
 *  Author: vivek
 */ 

void follow_segment(){
	int last_proportional = 0;
	long integral = 0;
	
	while(){
		unsigned int sensors[5];
		unsigned int position  = read_line(sensors, IR_EMITTERS_ON);
		
		int proportional = ((int)position) - 2000;
		
		
	}
}