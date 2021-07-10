#ifndef CALCULATE
#define CALCULATE

typedef struct _Calculate
{
	double 		p_Y[2];
	double		p_X[2];
	double 		pxStart[2];
	double 		pxFinal[2];
}Calculate;

Calculate find_point_coordinates (char mString[] , char bString[] );

#endif