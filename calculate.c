#include <stdio.h>
#include <stdlib.h>

#include "calculate.h"

double 	mValue;	
double   bValue;

Calculate find_point_coordinates (char mString[] , char bString[] )
{
	Calculate cal;

	cal.p_Y[0] = 10;
	cal.p_Y[1] = -10;

	mValue = atof(mString);
	bValue = atof(bString);

	if ( mValue == 0)
	{
		cal.p_X[0] =  10;
	 	cal.p_Y[0] =  bValue;
	 	cal.p_X[1] = -10;
	 	cal.p_Y[1] =  bValue;
	}
	else {

		cal.p_X[0] = (cal.p_Y[0] - bValue) / mValue;
		cal.p_X[1] = (cal.p_Y[1] - bValue) / mValue;
	}

	

	printf("p_X[0] : %f\n", cal.p_X[0]);
	printf("p_Y[0] : %f\n", cal.p_Y[0]);
	printf("p_X[1] : %f\n", cal.p_X[1]);
	printf("p_Y[1] : %f\n", cal.p_Y[1]);

		
	 for(int i=0 ; i<2 ; i++)
	 {
	 	if (i == 0)
	 	{
	 		cal.pxStart[i] 			= (412 + 50) + ( 30 * cal.p_X[i]);		// 412 is Origin X
	 		cal.pxStart[i+1] 		= 350 - ( 30 * cal.p_Y[i]);		// 350 is Origin Y
	 	}
	 	else
	 	{
	 		cal.pxFinal[i-1] 		= (412 + 50) + ( 30 * cal.p_X[i]);		// 412 is Origin X
	 		cal.pxFinal[i] 			= 350 - ( 30 * cal.p_Y[i]);		// 350 is Origin Y
	 	}		
	 }

	return  cal;
}

// Calculate convert_to_pix( Calculate cal )
// {
// 	double 		mValue	, bValue ;

// }





