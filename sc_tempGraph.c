#include "mng_window.h"

static void to_home_page (LiteButton *button, void *ctx)
{
	
	changeToPage  	(SC1_HOME);
}

static void to_graph_page(LiteButton *button,void *ctx)
{
	changeToPage  	(SC2_GRAPH);

}


static void to_calculator_page (LiteButton *button, void *ctx)
{
	
	changeToPage  	(SC3_CALCULATOR);
}

static void to_other_page (LiteButton *button, void *ctx)
{
	
	changeToPage  	(SC5_OTHER);
}

int sc_tempGraph(LiteWindow *window)
{
	DFBRectangle		rect;
	LiteBox 			*box 	= bx[SC4_TEMP_GRAPH];
	LiteImage     		*backgroundTempGraph;
	
	LiteButton			*btnHome_tmpGraph;
	LiteButton			*btnGraph_tmpGraph;
	LiteButton			*btnCalculator_tmpGraph;
	LiteButton			*btnOther_tmpGraph;

	rect.x = 0; rect.y = 0; rect.w = WIDTH; rect.h = HEIGHT; 
	lite_new_image(box , &rect , liteDefaultImageTheme , &backgroundTempGraph );
	lite_load_image(backgroundTempGraph , PATH_BACKGROUND "/pebbleTempGraph.png");
	
	// -- Button menu --

	rect.x = 0;	rect.y = 200;	rect.w = 200;	rect.h = 45;
	lite_new_button 				( box , &rect, liteDefaultButtonTheme, &btnHome_tmpGraph);
	lite_set_button_image  			( btnHome_tmpGraph,	LITE_BS_PRESSED, 	"button/btn_home_press.png");
	lite_on_button_press  			( btnHome_tmpGraph,	to_home_page, 	(void *)(long)1);

	rect.x = 0;	rect.y = 245;	rect.w = 200;	rect.h = 45;
	lite_new_button 				( box , &rect, liteDefaultButtonTheme, &btnGraph_tmpGraph);
	lite_set_button_image  			( btnGraph_tmpGraph,	LITE_BS_PRESSED, 	"button/btn_graph_press.png");
	lite_on_button_press  			( btnGraph_tmpGraph,	to_graph_page, 	(void *)(long)1);
	
	rect.x = 0;	rect.y = 290;	rect.w = 200;	rect.h = 45;
	lite_new_button 				( box , &rect, liteDefaultButtonTheme, &btnCalculator_tmpGraph);
	lite_set_button_image  			( btnCalculator_tmpGraph,	LITE_BS_PRESSED, 	"button/btn_cal_press.png");
	lite_on_button_press  			( btnCalculator_tmpGraph,	to_calculator_page, 	(void *)(long)1);

	rect.x = 0;	rect.y = 380;	rect.w = 200;	rect.h = 45;
	lite_new_button 				( box , &rect, liteDefaultButtonTheme, &btnOther_tmpGraph);
	lite_set_button_image  			( btnOther_tmpGraph,	LITE_BS_PRESSED, 	"button/btn_other_press.png");
	lite_on_button_press  			( btnOther_tmpGraph,	to_other_page, 	(void *)(long)1);




	return 0;
}