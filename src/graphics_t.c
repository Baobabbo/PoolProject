//--------------------------------------------------------
//  GRAPHICS_T_H - draw the movement of the balls
//--------------------------------------------------------

#include "init_t.h"

void graphics_task(void) {
	// Screen refresh at each execution
	
	while(1){
		blit(bground, buf, 0, 0, RESX / 2 - bground->w / 2, RESY - bground->h,
			RESX, RESY);
		
		ptask_wait_for_period();
	}
}
