#include <stdio.h>
#include <stdlib.h>

#include "calculate.h"

struct _Calculate
{
	float 		p_Y[2];
	float		p_X[2];
	float 		pxStart[2];
	float 		pxFinal[2];
};

	float 	mValue;	
	float   bValue;

Calculate find_point_coordinates (char *mString , char *bString )
{
	Calculate cal;

	cal.p_Y[0] = 10;
	cal.p_Y[1] = -10;

	mValue = atof(mString);
	bValue = atof(bString);

	cal.p_X[0] = (cal.p_Y[0] - bValue) / mValue;
	cal.p_X[1] = (cal.p_Y[1] - bValue) / mValue;

	 for(int i=0 ; i<2 ; i++)
	 {
	 	if (i == 0)
	 	{
	 		cal.pxStart[i] 		= 412 + ( 30 * cal.p_X[i]);
	 		cal.pxStart[i+1] 		= 350 - ( 30 * cal.p_Y[i]);
	 	}
	 	else
	 	{
	 		cal.pxFinal[i-1] 	= 412 + ( 30 * cal.p_X[i]);
	 		cal.pxFinal[i] 		= 350 - ( 30 * cal.p_Y[i]);
	 	}		
	 }

	return  cal;
}

// Calculate convert_to_pix( Calculate cal )
// {
// 	double 		mValue	, bValue ;

// }





