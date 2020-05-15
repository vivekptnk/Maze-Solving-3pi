/* Maze_solving - an application for the Pololu 3pi Robot
 *
 * Created: 4/17/2020 2:25:58 AM
 *  Author: vivek
 */

#include <pololu/3pi.h>
#include <avr/pgmspace.h>
#include "maze_solving_algorithm.h"

const char project_name1[] PROGMEM = "3pi Maze"; 
const char project_name2[] PROGMEM = "Solving";

const char project_author1[] PROGMEM = "Project by:";
const char project_author2[] PROGMEM = "Vivek P.";

const char videogame_tune[] PROGMEM = "v12 L16 o5 eererce8g8r8<g8r8"
"c8.<gr8<e8.<a8<b8<b-<a8<g.e.g.a8fgre8cd<b8."
"c8.<gr8<e8.<a8<b8<b-<a8<g.e.g.a8fgre8cd<b8."
"r8gf#fd#8er<g#<acr<acd"
"r8gf#fd#8er>c8>c>c4"
"r8gf#fd#8er<g#<acr<acd"
"r8e-8rd8.c4 v12 L16 o5 eererce8g8r8<g8r8"
"c8.<gr8<e8.<a8<b8<b-<a8<g.e.g.a8fgre8cd<b8."
"c8.<gr8<e8.<a8<b8<b-<a8<g.e.g.a8fgre8cd<b8."
"r8gf#fd#8er<g#<acr<acd"
"r8gf#fd#8er>c8>c>c4"
"r8gf#fd#8er<g#<acr<acd"
"r8e-8rd8.c4 v12 L16 o5 eererce8g8r8<g8r8"
"c8.<gr8<e8.<a8<b8<b-<a8<g.e.g.a8fgre8cd<b8."
"c8.<gr8<e8.<a8<b8<b-<a8<g.e.g.a8fgre8cd<b8."
"r8gf#fd#8er<g#<acr<acd"
"r8gf#fd#8er>c8>c>c4"
"r8gf#fd#8er<g#<acr<acd"
"r8e-8rd8.c4 v12 L16 o5 eererce8g8r8<g8r8"
"c8.<gr8<e8.<a8<b8<b-<a8<g.e.g.a8fgre8cd<b8."
"c8.<gr8<e8.<a8<b8<b-<a8<g.e.g.a8fgre8cd<b8."
"r8gf#fd#8er<g#<acr<acd"
"r8gf#fd#8er>c8>c>c4"
"r8gf#fd#8er<g#<acr<acd"
"r8e-8rd8.c4 v12 L16 o5 eererce8g8r8<g8r8"
"c8.<gr8<e8.<a8<b8<b-<a8<g.e.g.a8fgre8cd<b8."
"c8.<gr8<e8.<a8<b8<b-<a8<g.e.g.a8fgre8cd<b8."
"r8gf#fd#8er<g#<acr<acd"
"r8gf#fd#8er>c8>c>c4"
"r8gf#fd#8er<g#<acr<acd"
"r8e-8rd8.c4 v12 L16 o5 eererce8g8r8<g8r8"
"c8.<gr8<e8.<a8<b8<b-<a8<g.e.g.a8fgre8cd<b8."
"c8.<gr8<e8.<a8<b8<b-<a8<g.e.g.a8fgre8cd<b8."
"r8gf#fd#8er<g#<acr<acd"
"r8gf#fd#8er>c8>c>c4"
"r8gf#fd#8er<g#<acr<acd"
"r8e-8rd8.c4";

void init(){
	unsigned int calibration_counter;
	
	pololu_3pi_init(2000);
	
	//display project name
	print_from_program_space(project_name1);
	lcd_goto_xy(0,1);
	print_from_program_space(project_name2);
	delay(2000);
	
	clear();
	//display project author name
	print_from_program_space(project_author1);
	lcd_goto_xy(0,1);
	print_from_program_space(project_author2);
	play_from_program_space(videogame_tune);
	delay_ms(2000);
	
	while(!button_is_pressed(BUTTON_B))
	{
		clear();
		print("Press B");
		delay_ms(100);
	}
	
	wait_for_button_release(BUTTON_B);
	delay_ms(1000);
	
	
	// Following segment is for auto calibration of the 3pi
	for(calibration_counter=0; calibration_counter<80; calibration_counter++){
		if(calibration_counter < 20 || calibration_counter >= 60){
			set_motors(40,-40);
		} else {
			set_motors(-40,40);
		}
		
		calibrate_line_sensors(IR_EMITTERS_ON);
		delay_ms(20);
	}
	set_motors(0,0);
	
	wait_for_button_release(BUTTON_B);
	clear();
	
}


int main()
{
	init();
	
	maze_solving_algorithm();
	
	while(1);
}
