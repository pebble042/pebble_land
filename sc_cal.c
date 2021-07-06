#include "mng_window.h"

static DFBColor 	Silver 			= { a: 255, r: 192, g: 192, b: 192 };
//static DFBColor 	graphBoxColor 	= 	{a:255 , r:0, g:0 , b:0 };
extern int obj_cal(LiteBox *box);

static void to_home_page (LiteButton *button, void *ctx)
{
	
	changeToPage  	(SC1_HOME);
}

static void to_graph_page (LiteButton *button, void *ctx)
{
	
	changeToPage  	(SC2_GRAPH);
}

int sc_cal(LiteWindow *window)
{
	//LiteTextButton 		*txtBtnHome;
	DFBRectangle		 rect;
	LiteBox 			*box 		= bx[SC3_CALCULATOR]; // [address] bx[SC3_CALCULATOR]
	LiteBox 			*calculatorPageBox;
	LiteBox 			*calculatorObjectBox;
    LiteImage     		*backgroundCal;
    LiteButton			*btnHome_cal;
	LiteButton			*btnGraph_cal;


	box->background 				= &Silver;
	/*------- Menu --------*/
	rect.x = 0; rect.y = 0; rect.w = WIDTH; rect.h = HEIGHT; 
	lite_new_image(box , &rect , liteDefaultImageTheme , &backgroundCal );
	lite_load_image(backgroundCal , PATH_BACKGROUND "/pebbleCalculator.png");

	rect.x = 0;	rect.y = 200;	rect.w = 200;	rect.h = 45;
	lite_new_button 				( box , &rect, liteDefaultButtonTheme, &btnHome_cal);
	lite_set_button_image  			( btnHome_cal,	LITE_BS_PRESSED, 	"button/btn_home_press.png");
	lite_on_button_press  			( btnHome_cal,	to_home_page, 	(void *)(long)1);

	rect.x = 0;	rect.y = 245;	rect.w = 200;	rect.h = 45;
	lite_new_button 				( box , &rect, liteDefaultButtonTheme, &btnGraph_cal);
	lite_set_button_image  			( btnGraph_cal,	LITE_BS_PRESSED, 	"button/btn_graph_press.png");
	lite_on_button_press  			( btnGraph_cal,	to_graph_page, 	(void *)(long)1);
	/*------- End Menu --------*/
	



	// box for Calculator
	rect.x = 200;	rect.y = 40;	rect.w = 824;	rect.h = 700;
	lite_new_box					( &calculatorPageBox , box , rect.x , rect.y , rect.w , rect.h );  
	//calculatorBox ->background  = &graphBoxColor;

	rect.x = 224;	rect.y = 87;	rect.w = 375;	rect.h = 525;
	lite_new_box					( &calculatorObjectBox , calculatorPageBox , rect.x , rect.y , rect.w , rect.h );  
	//calculatorBox ->background  = &graphBoxColor;

	obj_cal(calculatorObjectBox);


	// -- set state visible --
	lite_set_box_visible(box, 0);
	return 0;
}
