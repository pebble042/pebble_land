#include "mng_window.h"

//static DFBColor white 			= { a: 255, r:   250, g:   250, b: 250 };

static void to_graph_page(LiteButton *button,void *ctx)
{
	changeToPage  	(SC2_GRAPH);

}


static void to_calculator_page (LiteButton *button, void *ctx)
{
	
	changeToPage  	(SC3_CALCULATOR);
}

static void to_temp_graph_page (LiteButton *button, void *ctx)
{
	
	changeToPage  	(SC4_TEMP_GRAPH);
}

static void to_other_page (LiteButton *button, void *ctx)
{
	
	changeToPage  	(SC5_OTHER);
}


int home_mng(LiteWindow *window)
{
    LiteImage     		*backgroundHome;
	LiteButton			*btnGraph_home;
	LiteButton			*btnCalculator_home;
	LiteButton			*btnTempGraph_home;
	LiteButton			*btnOther_home;


	DFBRectangle		rect;
	LiteBox 			*box 		= bx[SC1_HOME];

	rect.x = 0; rect.y = 0; rect.w = WIDTH; rect.h = HEIGHT; 
	lite_new_image(box , &rect , liteDefaultImageTheme , &backgroundHome );
	lite_load_image(backgroundHome , PATH_BACKGROUND "/pebbleHome.png");
	//box->background 				= &white;

	rect.x = 0;	rect.y = 245;	rect.w = 200;	rect.h = 45;
	lite_new_button 				( box , &rect, liteDefaultButtonTheme, &btnGraph_home);
	lite_set_button_image  			( btnGraph_home,	LITE_BS_PRESSED, 	"button/btn_graph_press.png");
	lite_on_button_press  			( btnGraph_home,	to_graph_page, 	(void *)(long)1);

	rect.x = 0;	rect.y = 290;	rect.w = 200;	rect.h = 45;
	lite_new_button 				( box , &rect, liteDefaultButtonTheme, &btnCalculator_home);
	lite_set_button_image  			( btnCalculator_home,	LITE_BS_PRESSED, 	"button/btn_cal_press.png");
	lite_on_button_press  			( btnCalculator_home,	to_calculator_page, 	(void *)(long)1);
	
	rect.x = 0;	rect.y = 335;	rect.w = 200;	rect.h = 45;
	lite_new_button 				( box , &rect, liteDefaultButtonTheme, &btnTempGraph_home);
	lite_set_button_image  			( btnTempGraph_home,	LITE_BS_PRESSED, 	"button/btn_temp_graph_press.png");
	lite_on_button_press  			( btnTempGraph_home,	to_temp_graph_page, 	(void *)(long)1);

	rect.x = 0;	rect.y = 380;	rect.w = 200;	rect.h = 45;
	lite_new_button 				( box , &rect, liteDefaultButtonTheme, &btnOther_home);
	lite_set_button_image  			( btnOther_home,	LITE_BS_PRESSED, 	"button/btn_other_press.png");
	lite_on_button_press  			( btnOther_home,	to_other_page, 	(void *)(long)1);
	// -- set state visible --
	lite_set_box_visible(box, 0);
	return 0;

}