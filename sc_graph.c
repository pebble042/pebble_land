#include "mng_window.h"
#include "graph.h"
#include "calculate.h"

//extern Position position_graph(char *mString , char *bString );


#define WIDTH_GRAPH_BOX 	824
#define HEIGHT_GRAPH_BOX 	700

extern DFBResult create_axis_graph	( LiteBox *box , int axisSize );	
extern DFBResult create_grid_graph	( LiteBox *box  , int x , int y );

static DFBColor 	Silver 			= 	{ a: 255, r: 192, g: 192, b: 192 };
static DFBColor 	graphBoxColor 	= 	{ a:255 , r:250, g:250 , b:250 };

DFBRectangle		rect;
DFBResult			res;

LiteTextButton 		*txtBtnHome;
LiteTextButton 		*plotTxtBtn;
LiteTextLine		*txtline_m;
LiteTextLine		*txtline_b;

static void to_home_page (LiteButton *button, void *ctx){

	changeToPage  	(SC1_HOME);
}

static void to_cal_page (LiteButton *button, void *ctx){

	changeToPage  	(SC3_CALCULATOR);
}

static void func_plot_graph_press (LiteTextButton *button, void *ctx)
{
	char *bString, *mString;
	//position pos ;

	lite_get_textline_text (	txtline_m, &mString );
	lite_get_textline_text (	txtline_b, &bString );

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

	lite_new_box					( &graphBox , box , WIDTH - WIDTH_GRAPH_BOX /* 1024-824 = 200 */ , 40 , WIDTH_GRAPH_BOX , HEIGHT_GRAPH_BOX );  
	graphBox ->background 			= &graphBoxColor;
	// position of graphBox (x,y) = (200,40) 40 is size of titlebar
	// WIDTH is size of window and 

	create_axis_graph				( graphBox , 600 );
	create_grid_graph				( graphBox , 162 ,50 );

	rect.x = 0;	rect.y = 200;	rect.w = 200;	rect.h = 45;
	lite_new_button 				( box , &rect, liteDefaultButtonTheme, &btnHome_graph);
	lite_set_button_image  			( btnHome_graph,	LITE_BS_PRESSED, 	"button/btn_home_press.png");
	lite_on_button_press  			( btnHome_graph,	to_home_page, 	(void *)(long)1);

	rect.x = 0;	rect.y = 290;	rect.w = 200;	rect.h = 45;
	lite_new_button 				( box , &rect, liteDefaultButtonTheme, &btnCalculator_graph);
	lite_set_button_image  			( btnCalculator_graph,	LITE_BS_PRESSED, 	"button/btn_cal_press.png");
	lite_on_button_press  			( btnCalculator_graph,	to_cal_page, 	(void *)(long)1);

	/* ------------ Textline m and b ------------ */
	rect.x = 20;	rect.y = 100;	rect.w = 100;	rect.h = 35;
	res  =	lite_new_textline		( 	graphBox , &rect , liteNoTextLineTheme , &txtline_m	);

	rect.x = 20;	rect.y = 200;
	res  =	lite_new_textline		( 	graphBox , &rect , liteNoTextLineTheme , &txtline_b	);
	
	/* ------------ Button ~Plot~ ------------ */
	rect.x = 20; rect.y = 300;	rect.w = 50;	rect.h = 30;
	lite_new_text_button			(	graphBox , &rect , "PLOT" , txtBtnTheme , &plotTxtBtn );
	lite_on_text_button_press		(	plotTxtBtn , func_plot_graph_press , NULL );

	

	// -- set state visible --
	lite_set_box_visible(box, 0);
	return 0;
}
