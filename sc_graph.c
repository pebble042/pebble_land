#include "mng_window.h"
#include "graph.h"

#define WIDTH_GRAPH 	724
#define HEIGHT_GRAPH 	700

extern DFBResult create_axis_graph( LiteBox *box , int axisSize);	
extern DFBResult create_axis_grid( LiteBox *box );

static DFBColor 	Silver 			= { a: 255, r: 192, g: 192, b: 192 };
static DFBColor 	graphBoxColor 	= 	{a:255 , r:250, g:250 , b:250 };

DFBRectangle		rect;
DFBResult			res;

LiteTextButton 		*txtBtnHome;
LiteTextButton 		*plotTxtBtn;
LiteTextLine		*txtline_m;
LiteTextLine		*txtline_b;


// static void func_plot_graph_press (LiteTextButton *button, void *ctx){
// {
// 	char *bString, *mString;

// 	lite_get_textline_text (	txtline_m, &mString );
// 	lite_get_textline_text (	txtline_b, &bString );
// }

static void to_home_page (LiteButton *button, void *ctx){

	changeToPage  	(SC1_HOME);
}

static void to_cal_page (LiteButton *button, void *ctx){

	changeToPage  	(SC3_CALCULATOR);
}

int sc_graph(LiteWindow *window)
{

	LiteBox 			*box 		= bx[SC2_GRAPH];
	LiteBox 			*graphBox ;
	//LiteBox 			*inputBox ;
    LiteImage     		*backgroundGraph;
    LiteButton 			*btnHome_graph;
    LiteButton 			*btnCalculator_graph;

	box->background 	= &Silver;

	rect.x = 0; rect.y = 0; rect.w = WIDTH; rect.h = HEIGHT; 
	lite_new_image(box , &rect , liteDefaultImageTheme , &backgroundGraph );
	lite_load_image(backgroundGraph , PATH_BACKGROUND "/pebbleGraph.png");

	lite_new_box					( &graphBox , box , WIDTH - WIDTH_GRAPH /* 1024-724 = 300 */ , 40 , WIDTH_GRAPH , HEIGHT_GRAPH );  
	graphBox ->background 			= &graphBoxColor;
	create_axis_graph				( graphBox , 600 );
	create_axis_grid				( graphBox );

	rect.x = 0;	rect.y = 200;	rect.w = 200;	rect.h = 45;
	lite_new_button 				( box , &rect, liteDefaultButtonTheme, &btnHome_graph);
	lite_set_button_image  			( btnHome_graph,	LITE_BS_PRESSED, 	"button/btn_home_press.png");
	lite_on_button_press  			( btnHome_graph,	to_home_page, 	(void *)(long)1);

	rect.x = 0;	rect.y = 290;	rect.w = 200;	rect.h = 45;
	lite_new_button 				( box , &rect, liteDefaultButtonTheme, &btnCalculator_graph);
	lite_set_button_image  			( btnCalculator_graph,	LITE_BS_PRESSED, 	"button/btn_cal_press.png");
	lite_on_button_press  			( btnCalculator_graph,	to_cal_page, 	(void *)(long)1);

	
	/*
	lite_new_box					( &inputBox , box , 200 , 0 , 100 , HEIGHT_GRAPH );  
	inputBox ->background 			= &graphBoxColor;

	rect.x = 30;	rect.y = 100;	rect.w = 70;	rect.h = 0;
	res  =	lite_new_textline		( 	inputBox , &rect , liteNoTextLineTheme , &txtline_m	);

	rect.x = 30;	rect.y = 200;
	res  =	lite_new_textline		( 	inputBox , &rect , liteNoTextLineTheme , &txtline_b	);
	
	rect.x = 30; rect.y = 300;	rect.w = 50;	rect.h = 30;
	lite_new_text_button			(	inputBox , &rect , "PLOT" , txtBtnTheme , &plotTxtBtn );
	//lite_on_text_button_press		(	plotTxtBtn , func_plot_graph_press , NULL );
	*/
	// -- set state visible --
	lite_set_box_visible(box, 0);
	return 0;
}
