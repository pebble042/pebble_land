#include "mng_window.h"

int sc_other(LiteWindow *window)
{
	DFBRectangle		rect;
	LiteBox 			*box 	= bx[SC5_OTHER];
	LiteImage     		*backgroundOther;
	
	LiteButton			*btnHome_tmpGraph;
	LiteButton			*btnGraph_tmpGraph;
	LiteButton			*btnCalculator_tmpGraph;
	LiteButton			*btnOther_tmpGraph;

	rect.x = 0; rect.y = 0; rect.w = WIDTH; rect.h = HEIGHT; 
	lite_new_image(box , &rect , liteDefaultImageTheme , &backgroundOther );
	lite_load_image(backgroundOther , PATH_BACKGROUND "/pebbleOther.png");
	

	return 0;
}