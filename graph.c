#include <stdio.h>
#include <stdlib.h>

#include <lite/lite.h>
#include <lite/window.h>

#include <directfb.h>

#include "graph.h"

#define FONT3		"whiterabbit"

Graph 					graph;

static LiteFont			*font8;
static LiteFont			*font14;
static IDirectFBFont 	*font_scale_axis;
static IDirectFBFont 	*font_axis;

//static DFBColor 		graphBoxColor 	= 	{a:255 , r:250, g:250 , b:250 };

static DFBResult draw_axis_graph (LiteBox *box, const DFBRegion *region, DFBBoolean clear);
static DFBResult draw_axis_grid (LiteBox *box, const DFBRegion *region, DFBBoolean clear);

static void func_setting(LiteBox *box , int axisSize)
{
	/* create font */
	lite_get_font_from_file			( 	FONT3 , 8 , DEFAULT_FONT_ATTRIBUTE , &font8);
	lite_font           			(	font8 , &font_scale_axis	);

	lite_get_font_from_file			( 	FONT3 , 14 , DEFAULT_FONT_ATTRIBUTE , &font14);
	lite_font           			(	font14 , &font_axis	);

	graph.axisLenght 	= 	axisSize;
	graph.width 		= 	box->rect.w;
	graph.height 		= 	box->rect.h;
	graph.ORIGIN_X		= 	graph.width / 2;
	graph.ORIGIN_Y		= 	graph.height / 2;

}

DFBResult create_axis_graph(LiteBox *box , int axisSize)
{
	LiteBox *bx = box;
	LiteBox *axisGraphBox;

	func_setting		( bx , axisSize);
	lite_new_box		( &axisGraphBox , bx , bx->rect.x , bx->rect.y , graph.width , graph.height );
	
	//bx->background 		= &graphBoxColor; // Test color box
	bx->Draw			= draw_axis_graph;


	return DFB_OK;
}

DFBResult create_axis_grid(LiteBox *box )
{
	LiteBox *gridGraphBox;
	lite_new_box					( &gridGraphBox , box , 62 , 50 , 601 , 601 );

	gridGraphBox->Draw = draw_axis_grid;

	return DFB_OK;
}


static DFBResult draw_axis_grid (LiteBox *box, const DFBRegion *region, DFBBoolean clear)
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

static DFBResult draw_axis_graph (LiteBox *box, const DFBRegion *region, DFBBoolean clear)
{

	IDirectFBSurface *surface = box->surface;
	if(clear) { lite_clear_box(box, region); }

	surface->SetFont(surface, font_scale_axis);

	/* x-axis */
	int Xpoint_x1 = (graph.width - graph.axisLenght) / 2	/* 62 */		,	Xpoint_y1 = graph.height/2; 	/* 350 */
	int Xpoint_x2 = graph.width - Xpoint_x1					/* 662 */ 		,	Xpoint_y2 = graph.height/2;	/* 350 */

	/* Scale line X*/
	int topOfAxis_x[2] 		= 	{ 	Xpoint_x1 ,	Xpoint_y1 - 2 	},	
		 bottomOfAxis_x[2] 	= 	{ 	Xpoint_x1 , Xpoint_y1 + 2 	};

	/* ---------------------- create x-axis ---------------------- */
	surface->SetColor				(surface, 0, 0, 0, 100);
	surface->DrawLine 				(surface, Xpoint_x1, Xpoint_y1, Xpoint_x2, Xpoint_y2 );
	/* ---------------------- End create x-axis ---------------------- */

	/* ---------------------- |X-axis| Create Scale line and Scale number ---------------------- */

	int addValue	=	10;
	char numChar[4] = {'\0'};

	while(topOfAxis_x[0] <= Xpoint_x2 && bottomOfAxis_x[0] <= Xpoint_x2)
	{

		surface->DrawLine 				(	surface, topOfAxis_x[0], topOfAxis_x[1], bottomOfAxis_x[0], bottomOfAxis_x[1] );
		
		/* ----- Create Scale number ----- */
		if((topOfAxis_x[0] < graph.ORIGIN_X) && (bottomOfAxis_x[0] < graph.ORIGIN_X) )
		{
			
			snprintf(numChar,4,"-%d", addValue);
			surface->DrawString				(surface, numChar, -1, bottomOfAxis_x[0] - 3 , bottomOfAxis_x[1] + 10, DSTF_BOTTOM);
			addValue -=1;
			
		}
		else if((topOfAxis_x[0] >= graph.ORIGIN_X) && (bottomOfAxis_x[0] >= graph.ORIGIN_X))
		{
			
			snprintf(numChar,3,"%d", addValue);
			surface->DrawString				(surface, numChar, -1, bottomOfAxis_x[0] , bottomOfAxis_x[1] + 10, DSTF_BOTTOM);
			addValue +=1;
		}

		/* ----- End Create Scale number ----- */
		topOfAxis_x[0] 		+= (Xpoint_x2 - Xpoint_x1) / 20; 			// 20 is the number of lines on the axis. 
		bottomOfAxis_x[0] 	+= (Xpoint_x2 - Xpoint_x1) / 20; 			// 20 is the number of lines on the axis.
	} 

	/* ---------------------- |X-axis| End create Scale line and Scale number ---------------------- */
	
	/* ---------------------- |Y-axis| Create Scale line and Scale number ---------------------- */
	/* y-axis */
	int Ypoint_x1 = graph.width/2	/*  */			,	Ypoint_y1 = (graph.height - graph.axisLenght) /2;
	int Ypoint_x2 = graph.width/2 	/*  */			,	Ypoint_y2 = graph.height - Ypoint_y1; /*  */
	
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
		
		if(	(leftOfAxis_y[1] < graph.ORIGIN_Y) && (rightOfAxis_y[1] < graph.ORIGIN_Y) )
		{
			snprintf				(numChar,3,"%d", addValue);
			surface->DrawString		(surface, numChar, -1, rightOfAxis_y[0] + 5 , rightOfAxis_y[1] + 5, DSTF_BOTTOM);
			addValue -=1;
		}
		else if( (leftOfAxis_y[1] > graph.ORIGIN_Y) && (rightOfAxis_y[1] > graph.ORIGIN_Y) )
		{
			addValue +=1;
			snprintf				(numChar,4,"-%d", addValue);
			surface->DrawString		(surface, numChar, -1, rightOfAxis_y[0] + 5 , rightOfAxis_y[1] + 5, DSTF_BOTTOM);
			
		}
		leftOfAxis_y[1] += (Ypoint_y2 - Ypoint_y1) / 20;
		rightOfAxis_y[1] += (Ypoint_y2 - Ypoint_y1) / 20;

	}
	/* ---------------------- |Y-axis| End create "Scale line" and "Scale number" ---------------------- */
	
	surface->SetFont			(surface, font_axis);	
	surface->SetColor			(surface, 255, 0, 0, 255);
	surface->DrawString			(surface, "Y", -1 , graph.width/2 + 5 , 40 , DSTF_RIGHT);
	surface->DrawString			(surface, "X", -1 , Xpoint_x2 + 20 , Xpoint_y2 + 10 , DSTF_RIGHT);

	return DFB_OK;
} 

