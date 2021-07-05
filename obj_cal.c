#include "mng_window.h"

int obj_cal(LiteBox *box)
{
	DFBRectangle		rect;
	LiteBox 			*bx = box;

	LiteImage     		*calculatorTem;
	LiteTextLine		*txtlineInputCal;


	rect.x = 0; rect.y = 0; rect.w = 375; rect.h = 525; 
	lite_new_image(bx , &rect , liteDefaultImageTheme , &calculatorTem );
	lite_load_image(calculatorTem , PATH_BACKGROUND "/calculator_template.png");

	rect.x = 42;	rect.y = 38;	rect.w = 290;	rect.h = 62;
	lite_new_textline			( 	bx , &rect , liteNoTextLineTheme , &txtlineInputCal  );
	return 0;
}