#include "mng_window.h"

static DFBColor 	Silver 			= { a: 255, r: 192, g: 192, b: 192 };
static DFBColor 	graphBoxColor 	= 	{a:255 , r:0, g:0 , b:0 };


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
	DFBRectangle		rect;
	LiteBox 			*box 		= bx[SC3_CALCULATOR];
	LiteBox 			*calculatorBox;
    LiteImage     		*backgroundCal;
    LiteImage     		*calculatorTem;
    LiteButton			*btnHome_cal;
	LiteButton			*btnGraph_cal;
	LiteButton 			*num7Btn;
	LiteTextLine		*txtlineInputCal;

	LiteTextButton 		*txtBtnTest;
	LiteTextButtonTheme	*txtBtnTheme;



	box->background 				= &Silver;

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
	

	// box for Calculator
	rect.x = 200;	rect.y = 40;	rect.w = 824;	rect.h = 700;
	lite_new_box					( &calculatorBox , box , rect.x , rect.y , rect.w , rect.h );  
	//calculatorBox ->background  = &graphBoxColor;

	rect.x = 224; rect.y = 87; rect.w = 375; rect.h = 525; 
	lite_new_image(calculatorBox , &rect , liteDefaultImageTheme , &calculatorTem );
	lite_load_image(calculatorTem , PATH_BACKGROUND "/calculator_tem2.png");

	rect.x = 266;	rect.y = 125;	rect.w = 290;	rect.h = 62;
	lite_new_textline			( 	calculatorBox , &rect , liteNoTextLineTheme , &txtlineInputCal  );

	// rect.x = 261;	rect.y = 262;	rect.w = 60;	rect.h = 60;
	// lite_new_button 				( calculatorBox , &rect, liteDefaultButtonTheme, &num7Btn);
	// lite_set_button_image  			( num7Btn,	LITE_BS_PRESSED, 	"button/btn_num_cal_press.png");
	// //lite_set_button_image  			( num7Btn,	LITE_BS_PRESSED, 	"button/btn_num_cal_press.png");

	lite_new_text_button_theme 		("button/btn_num_cal_press2.png", 	&txtBtnTheme);

	rect.x = 600;	rect.y = 262;	rect.w = 60;	rect.h = 60;
	lite_new_text_button			(	calculatorBox , &rect, "7" , txtBtnTheme ,	&txtBtnTest );
	
	// -- set state visible --
	lite_set_box_visible(box, 0);
	return 0;
}
