#ifndef GRAPH
#define GRAPH

typedef struct _graph
{
	int 	width;
	int 	height;
	int 	axisLenght;
	int 	ORIGIN_X;
	int 	ORIGIN_Y;

}Graph;

DFBResult create_axis_graph(LiteBox *box , int axisSize);
DFBResult create_grid_graph( LiteBox *box,int x , int y );
DFBResult plot_linear_graph(LiteBox *box , char *mString , char *bString );

#endif