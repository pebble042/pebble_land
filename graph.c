#include <stdio.h>
#include <stdlib.h>

#include <lite/lite.h>
#include <lite/window.h>

#include <directfb.h>

#include "graph.h"
#include "calculate.h"

#define FONT3		"whiterabbit"

Graph 					graph;
Calculate 				valueGraph;
static LiteFont			*font8;
static LiteFont			*font14;
static IDirectFBFont 	*font_scale_axis;
static IDirectFBFont 	*font_axis;

//static DFBColor 		graphBoxColor 	= 	{a:255 , r:255, g:100 , b:150 };

static DFBResult draw_axis_graph (LiteBox *box, const DFBRegion *region, DFBBoolean clear);

static DFBResult draw_grid_graph (LiteBox *box, const DFBRegion *region, DFBBoolean clear);
static DFBResult draw_plot_linear_graph(LiteBox *box , const DFBRegion *region , DFBBoolean clear);


/*====================================
=            Set Variable            =
====================================*/

static void func_setting(LiteBox *box , int axisSize)
{
	/* create font */
	lite_get_font_from_file			( 	FONT3 , 8 , DEFAULT_FONT_ATTRIBUTE , &font8);
	lite_font           			(	font8 , &font_scale_axis	);

	lite_get_font_from_file			( 	FONT3 , 14 , DEFAULT_FONT_ATTRIBUTE , &font14);
	lite_font           			(	font14 , &font_axis	);

	graph.axisLenght 	= 	axisSize;
	graph.width 		= 	box->rect.w;		/* 824 */
	graph.height 		= 	box->rect.h;		/* 700 */
	graph.ORIGIN_X		= 	graph.width / 2; 	/* 412 */
	graph.ORIGIN_Y		= 	graph.height / 2; 	/* 350 */
	
}

/*================================
=            Function            =
================================*/


DFBResult create_axis_graph(LiteBox *box , int axisSize)
{
	//LiteBox *axisGraphBox;
	LiteBox *axisGraphBox;


	func_setting		( box , axisSize);
	lite_new_box		( &axisGraphBox , box , 162 , 50 , 600+10 , 600+10 );
	
	axisGraphBox->Draw			= draw_axis_graph;
	
	//axisGraphBox->background 	= &graphBoxColor;

	return DFB_OK;
}

DFBResult create_grid_graph( LiteBox *box,int x , int y )
{
	LiteBox *gridGraphBox;
	lite_new_box					( &gridGraphBox , box , x/*62 + 100*/ , y /*50 */, 600 + 1 , 600 + 1);

	gridGraphBox->Draw = draw_grid_graph;
	//gridGraphBox->background = &graphBoxColor;

	return DFB_OK;
}

DFBResult plot_linear_graph(LiteBox *box , char *mString , char *bString )
{
	valueGraph = find_point_coordinates (mString , bString );
	printf("rect x : %d\n", box->rect.x);
	//box->rect.x += 50;

	box->Draw = draw_plot_linear_graph;


	//box->background = &graphBoxColor;
	lite_update_box( box , NULL);
	return DFB_OK;
}

/*=====  End of Function  ======*/

/*=====================================
=            Draw Function            =
=====================================*/

/*=============  Draw Axis ============= */

static DFBResult draw_axis_graph (LiteBox *box, const DFBRegion *region, DFBBoolean clear)
{
	double	width 	= box->rect.w - 10; /* 610 - 10 = 600 */
	double	height 	= box->rect.h - 10; /* 610 - 10 = 600 */

	double	ORIGIN_X = width / 2; // 600 / 2 = 300
	double	ORIGIN_Y = height / 2; // 600 / 2 = 300

	int Xpoint_x1 = 0 		/* 0 */		,	Xpoint_y1 = height/2; 	/* 300 */
	int Xpoint_x2 = width	/* 600 */ 	,	Xpoint_y2 = height/2;	/* 300 */

	/* -------- Scale line -------- */

	int 	topOfAxis_x[2] 		= 	{ 	
										Xpoint_x1 ,		
										Xpoint_y1 - 2 	
						  			},	
	   		bottomOfAxis_x[2] 	= 	{ 	
	   									Xpoint_x1 , 	
	   									Xpoint_y1 + 2 	
	   					  			};

	IDirectFBSurface *surface = box->surface;

	if(clear) { lite_clear_box(box, region); }

	surface->SetFont(surface, font_scale_axis);
	surface->SetClip					(surface, NULL);
	surface->SetDrawingFlags			(surface, DSDRAW_SRC_PREMULTIPLY);

	//Graph axis
	/* ---------------------- create x-axis ---------------------- */

	surface->SetColor				(surface, 0, 0, 0, 100);
	surface->DrawLine 				(surface, Xpoint_x1, Xpoint_y1, Xpoint_x2, Xpoint_y2 );

	/* ---------------------- End create x-axis ---------------------- */	

	/* ---------------------- |X-axis| Create Scale line and Scale number ---------------------- */

	int addValue	=	-10;
	char numChar[4] = {'\0'};
	//surface->DrawString				(surface, "10", -1, 590 , 300 + 10, DSTF_BOTTOM);

	while(topOfAxis_x[0] <= Xpoint_x2 && bottomOfAxis_x[0] <= Xpoint_x2)
	{
		surface->DrawLine 				(	surface, topOfAxis_x[0], topOfAxis_x[1], bottomOfAxis_x[0], bottomOfAxis_x[1] );
		
		/* ----- Create Scale number ----- */
		if((topOfAxis_x[0] < ORIGIN_X) && (bottomOfAxis_x[0] < ORIGIN_X) )
		{
			snprintf(numChar,4,"%d", addValue);
			surface->DrawString				(surface, numChar, -1, bottomOfAxis_x[0] , bottomOfAxis_x[1] + 10, DSTF_BOTTOM);
			addValue +=1;
			
		}
		else if((topOfAxis_x[0] >= ORIGIN_X) && (bottomOfAxis_x[0] >= ORIGIN_X))
		{
			
			snprintf(numChar,3,"%d", addValue);
			surface->DrawString				(surface, numChar, -1, bottomOfAxis_x[0] , bottomOfAxis_x[1] + 10, DSTF_BOTTOM);
			addValue +=1;
		}

		topOfAxis_x[0] 		+= (Xpoint_x2 - Xpoint_x1) / 20; // 600 / 20 = 30			// 20 is the number of lines on the axis. 
		bottomOfAxis_x[0] 	+= (Xpoint_x2 - Xpoint_x1) / 20; // 20 is the number of lines on the axis.

		/* ----- End Create Scale number ----- */
	}

	/* ---------------------- |Y-axis| Create Scale line and Scale number ---------------------- */
	/* y-axis */
	int 	Ypoint_x1 = width/2		/* 600/2 = 300  */		,	Ypoint_y1 = 0;
	int 	Ypoint_x2 = height /2 	/* 600/2 = 300 */		,	Ypoint_y2 = width; /* 600 */
	
	printf("X1 : %d , Y1 : %d\n", Ypoint_x1 , Ypoint_y1 );
	printf("X2 : %d , Y2 : %d\n", Ypoint_x2 , Ypoint_y2 );

	// Y
	int 	leftOfAxis_y[2] 	= 	{ 	Ypoint_x1 - 2 ,	Ypoint_y1	},	
	   		rightOfAxis_y[2] 	= 	{ 	Ypoint_x1 + 2 , Ypoint_y1	};

	/* ---------------------- create x-axis ---------------------- */
	surface->DrawLine 			(	surface , Ypoint_x1 , Ypoint_y1 , Ypoint_x2 , Ypoint_y2 );
	/* ---------------------- End create x-axis ---------------------- */
	
	surface->SetColor			(surface, 0, 0, 0, 100);
	addValue	=	10;

	while( (leftOfAxis_y[1] <= Ypoint_y2) && (rightOfAxis_y[1] <= Ypoint_y2) ) 
	{
		surface->DrawLine 			(	surface, leftOfAxis_y[0], leftOfAxis_y[1],	rightOfAxis_y[0], rightOfAxis_y[1]	); //line scale
		
		if(	(leftOfAxis_y[1] < ORIGIN_Y) && (rightOfAxis_y[1] < ORIGIN_Y) )
		{
			snprintf				(numChar,3,"%d", addValue);
			surface->DrawString		(surface, numChar, -1, rightOfAxis_y[0] + 5 , rightOfAxis_y[1] + 10, DSTF_BOTTOM);
			addValue -=1;
		}
		else if( (leftOfAxis_y[1] > ORIGIN_Y) && (rightOfAxis_y[1] > ORIGIN_Y) )
		{
			addValue +=1;
			snprintf				(numChar,4,"-%d", addValue);
			surface->DrawString		(surface, numChar, -1, rightOfAxis_y[0] + 5 , rightOfAxis_y[1] + 10, DSTF_BOTTOM);
			
		}

		leftOfAxis_y[1] 	+= (Ypoint_y2 - Ypoint_y1) / 20;
		rightOfAxis_y[1] 	+= (Ypoint_y2 - Ypoint_y1) / 20;

	}

/* ---------------------- |Y-axis| End create "Scale line" and "Scale number" ---------------------- */


	return DFB_OK;

}

	
/*=============  Draw Grid  ============= */
static DFBResult draw_grid_graph (LiteBox *box, const DFBRegion *region, DFBBoolean clear)
{

	IDirectFBSurface *surface = box->surface;
	if(clear)
		lite_clear_box(box, region);

	surface->SetDrawingFlags 		(surface, DSDRAW_BLEND);
	for(int i = 0 ; i <= box->rect.h && i <= box->rect.w ; i += 30)
	{
		surface->SetColor			(surface, 0, 0, 0, 40);
		surface->DrawLine 			(surface, 0, i, 600,  i);
		surface->DrawLine 			(surface, i, 0, i, 600 );
	}

	return DFB_OK;
}

/*=============  Draw Linear Graph  ============= */

static DFBResult draw_plot_linear_graph(LiteBox *box , const DFBRegion *region , DFBBoolean clear)
{
	IDirectFBSurface *surface = box->surface;
	if(clear)
		lite_clear_box(box, region);

	surface->SetClip				(surface, NULL);
	surface->SetDrawingFlags 		(surface, DSDRAW_BLEND);

	surface->SetColor				(surface, 0, 0, 200, 255);
	/* 50 is ??? */
	surface->DrawLine 				(surface, valueGraph.pxStart[0],valueGraph.pxStart[1], valueGraph.pxFinal[0], valueGraph.pxFinal[1] );
	surface->DrawLine 				(surface, valueGraph.pxStart[0]-1,valueGraph.pxStart[1], valueGraph.pxFinal[0]-1, valueGraph.pxFinal[1] );

	printf("pxStart[0] : %f\n", valueGraph.pxStart[0]);
	printf("pxStart[1] : %f\n", valueGraph.pxStart[1]);
	printf("pxFinal[0] : %f\n", valueGraph.pxFinal[0]);
	printf("pxFinal[1] : %f\n", valueGraph.pxFinal[1]);
	return DFB_OK;
}


