#include "autumn_security.h"

void start_game(Password* pass){
	size_t level = 0;
	size_t failed = 0;
	while(level != pass->len){
		// read_but
		// if but == ok
		// yellow
		// level++
		//else
		{
			level = 0;
			failed++;
			if(failed == 3){
				//failed_animation();
				failed = 0;
			}
		}

	}
}
