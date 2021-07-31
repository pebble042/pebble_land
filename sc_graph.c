#include "mng_window.h"
#include "graph.h"
#include "calculate.h"

#define WIDTH_GRAPH_BOX 	824
#define HEIGHT_GRAPH_BOX 	700

extern DFBResult create_axis_graph	( LiteBox *box , int axisSize );	
extern DFBResult create_grid_graph	( LiteBox *box  , int x , int y );
extern DFBResult plot_linear_graph(LiteBox *box , char *mString , char *bString);


//static DFBColor 	Silver 			= 	{ a: 255, r: 192, g: 192, b: 192 };
static DFBColor 	graphBoxColor 	= 	{ a:255 , r:250, g:250 , b:250 };

DFBRectangle		rect;
DFBResult			res;

LiteTextButton 		*txtBtnHome;
LiteTextButton 		*plotTxtBtn;
LiteTextLine		*txtline_m;
LiteTextLine		*txtline_b;
LiteBox 			*graphBox ;
LiteBox 			*plotGraphBox ;



static void change_page (LiteButton *button, void *ctx)
{
	int id_page = (int)(long)ctx;
	changeToPage  	(id_page);
			
}

static void func_plot_graph_press (LiteTextButton *button, void *ctx)
{
	char *bString, *mString;

	lite_get_textline_text 		( txtline_m, &mString );
	lite_get_textline_text 		( txtline_b, &bString );

	plot_linear_graph			( plotGraphBox , mString , bString);

}

int sc_graph(LiteWindow *window)
{

	LiteBox 			*box 		= bx[SC2_GRAPH];
    LiteImage     		*backgroundGraph;
    LiteButton 			*btnHome_graph;
    LiteButton 			*btnCalculator_graph;
    LiteButton			*btnTempGraph_graph;
	LiteButton			*btnOther_graph;

	//box->background 	= &Silver;

	rect.x = 0; rect.y = 0; rect.w = WIDTH; rect.h = HEIGHT; 
	lite_new_image				( box , &rect , liteDefaultImageTheme , &backgroundGraph );
	lite_load_image				( backgroundGraph , PATH_BACKGROUND "/pebbleGraph.png" );

	rect.x = 0;	rect.y = 200;	rect.w = 200;	rect.h = 45;
	lite_new_button 			( box , &rect , liteDefaultButtonTheme , &btnHome_graph);
	lite_set_button_image  		( btnHome_graph ,	LITE_BS_PRESSED , "button/btn_home_press.png" );
	lite_on_button_press  		( btnHome_graph ,	change_page, 	(void *)(long)SC1_HOME);

	rect.x = 0;	rect.y = 290;	rect.w = 200;	rect.h = 45;
	lite_new_button 			( box , &rect , liteDefaultButtonTheme , &btnCalculator_graph );
	lite_set_button_image  		( btnCalculator_graph ,	LITE_BS_PRESSED , "button/btn_cal_press.png" );
	lite_on_button_press  		( btnCalculator_graph ,	change_page , 	(void *)(long)SC3_CALCULATOR);

	rect.x = 0;	rect.y = 335;	rect.w = 200;	rect.h = 45;
	lite_new_button 			( box , &rect , liteDefaultButtonTheme , &btnTempGraph_graph);
	lite_set_button_image  		( btnTempGraph_graph ,	LITE_BS_PRESSED , "button/btn_temp_graph_press.png" );
	lite_on_button_press  		( btnTempGraph_graph ,	change_page, 	(void *)(long)SC4_TEMP_GRAPH);

	rect.x = 0;	rect.y = 380;	rect.w = 200;	rect.h = 45;
	lite_new_button 			( box , &rect , liteDefaultButtonTheme , &btnOther_graph );
	lite_set_button_image  		( btnOther_graph ,	LITE_BS_PRESSED , "button/btn_other_press.png" );
	lite_on_button_press  		( btnOther_graph ,	change_page , 	(void *)(long)SC5_OTHER );

	/* ------------ graphBox Main Box ------------ */
	lite_new_box				( &graphBox , box , WIDTH - WIDTH_GRAPH_BOX /* 1024-824 = 200 */ , 40 , WIDTH_GRAPH_BOX , HEIGHT_GRAPH_BOX );  
	//graphBox ->background 			= &graphBoxColor;
	// position of graphBox (x,y) = (200,40) 40 is size of titlebar
	// WIDTH is size of window and 

	/* ------------ Box for plot linear line ------------ */
	
	lite_new_box				( &plotGraphBox , graphBox , 162 , 50 , 600 , 600 );  
	graphBox ->background 		= &graphBoxColor;

	create_axis_graph			( graphBox , 600 );
	create_grid_graph			( graphBox , 162 ,50 );

	/* ------------ Textline m and b ------------ */
	rect.x = 50;	rect.y = 100;	rect.w = 50;	rect.h = 35;
	res  =	lite_new_textline	( graphBox , &rect , liteNoTextLineTheme , &txtline_m );

	rect.y = 200;
	res  =	lite_new_textline	( graphBox , &rect , liteNoTextLineTheme , &txtline_b );
	
	/* ------------ Button ~Plot~ ------------ */
	rect.y = 300;	rect.w = 50;	rect.h = 30;
	lite_new_text_button		( graphBox , &rect , "PLOT" , txtBtnTheme , &plotTxtBtn );
	lite_on_text_button_press	( plotTxtBtn , func_plot_graph_press , NULL );


	// -- set state visible --
	lite_set_box_visible(box, 0);
	return 0;
}
