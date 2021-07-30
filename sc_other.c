#include "mng_window.h"

static void change_page (LiteButton *button, void *ctx)
{
	int id_page = (int)(long)ctx;
	changeToPage  	(id_page);
			
}


int sc_other(LiteWindow *window)
{
	DFBRectangle		rect;
	LiteBox 			*box 	= bx[SC5_OTHER];
	LiteImage     		*backgroundOther;
	
	LiteButton			*btnHome_other;
	LiteButton			*btnGraph_other;
	LiteButton			*btnCalculator_other;
	LiteButton			*btnTempGraph_other;

	rect.x = 0; rect.y = 0; rect.w = WIDTH; rect.h = HEIGHT; 
	lite_new_image(box , &rect , liteDefaultImageTheme , &backgroundOther );
	lite_load_image(backgroundOther , PATH_BACKGROUND "/pebbleOther.png");
	
	rect.x = 0;	rect.y = 200;	rect.w = 200;	rect.h = 45;
	lite_new_button 				( box , &rect, liteDefaultButtonTheme, &btnHome_other);
	lite_set_button_image  			( btnHome_other,	LITE_BS_PRESSED, 	"button/btn_home_press.png");
	lite_on_button_press  			( btnHome_other,	change_page, 	(void *)(long)SC1_HOME);

	rect.x = 0;	rect.y = 245;	rect.w = 200;	rect.h = 45;
	lite_new_button 				( box , &rect, liteDefaultButtonTheme, &btnGraph_other);
	lite_set_button_image  			( btnGraph_other,	LITE_BS_PRESSED, 	"button/btn_graph_press.png");
	lite_on_button_press  			( btnGraph_other,	change_page, 	(void *)(long)SC2_GRAPH);
	
	rect.x = 0;	rect.y = 290;	rect.w = 200;	rect.h = 45;
	lite_new_button 				( box , &rect, liteDefaultButtonTheme, &btnCalculator_other);
	lite_set_button_image  			( btnCalculator_other,	LITE_BS_PRESSED, 	"button/btn_cal_press.png");
	lite_on_button_press  			( btnCalculator_other,	change_page, 	(void *)(long)SC3_CALCULATOR);

	rect.x = 0;	rect.y = 335;	rect.w = 200;	rect.h = 45;
	lite_new_button 				( box , &rect, liteDefaultButtonTheme, &btnTempGraph_other);
	lite_set_button_image  			( btnTempGraph_other,	LITE_BS_PRESSED, 	"button/btn_temp_graph_press.png");
	lite_on_button_press  			( btnTempGraph_other,	change_page, 	(void *)(long)SC4_TEMP_GRAPH);

	

	return 0;
}