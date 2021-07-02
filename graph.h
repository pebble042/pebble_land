#ifndef WINDOW_MNG
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
DFBResult create_axis_grid(LiteBox *box );


#endif