#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "calculate.h"

double 	mValue;	
double   bValue;

/* ---------------- Graph ---------------- */

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

		
	 for(int i=0 ; i<2 ; i++)
	 {
	 	if (i == 0)
	 	{
	 		cal.pxStart[i] 			= 300 + ( 30 * cal.p_X[i]);		// 412 is Origin X
	 		cal.pxStart[i+1] 		= 300 - ( 30 * cal.p_Y[i]);		// 350 is Origin Y
	 	}
	 	else
	 	{
	 		cal.pxFinal[i-1] 		= 300  + ( 30 * cal.p_X[i]);		// 412 is Origin X
	 		cal.pxFinal[i] 			= 300 - ( 30 * cal.p_Y[i]);		// 350 is Origin Y
	 	}		
	 }

	return  cal;
}

/* ---------------- Calculator ---------------- */

static char **malloc2d(int rows, int columns)
{
	char **result = (char **) malloc(rows * sizeof(char *));
	for (int row = 0; row < rows; ++row)
	{
		result[row] = (char *) malloc(columns * sizeof(char *));
	}

	return result;
}


static void free2d(char **array , int rows , int columns)
{
	for (int row = 0; row < rows; ++row)
	{
		free(array[row]);
	}

	free(array);
}


static char **split_string( char strNum[20] )
{
	char **newString = malloc2d( 3 , 4 );
	int j , ctr;

	j = 0;
	ctr = 0;
	for (int i = 0; i <=(strlen(strNum)); ++i)
	 {
	 	if (strNum =='\0')
		{
			newString[ctr][j] = '\0';

		}
		else if (strNum[i] == '+' || strNum[i] == '-' || strNum[i] == '*' || strNum[i] == '/')
		{
			newString[ctr][j] = '\0';
			ctr++;
			j = 0;
			newString[ctr][j] = strNum[i];
			j++;
			newString[ctr][j] = '\0';
			ctr++;
			j = 0;
			
		}
		else
		{
			newString[ctr][j] = strNum[i];
			j++;
		}
	 } 

	 return newString;
}


float calculator_function(char strNum[10])
{
	//printf("strNum In func : %s\n", strNum);
	char **strNew = split_string(strNum);
	float result;

	for (int i = 0; i < 3; ++i)
	{
		printf("strNew : %s\n", *(strNew+i));
		if (strcmp( *(strNew+i) , "+") == 0)
		{
			result =  atof(*(strNew + (i-1))) + atof(*(strNew + (i+1)));
		}
		else if (strcmp( *(strNew+i) , "-") == 0)
		{
			result =  atof(*(strNew + (i-1))) - atof(*(strNew + (i+1)));
		}
		else if (strcmp( *(strNew+i) , "*") == 0)
		{
			result =  atof(*(strNew + (i-1))) * atof(*(strNew + (i+1)));
		}
		else if (strcmp( *(strNew+i) , "/") == 0)
		{
			result =  atof(*(strNew + (i-1))) / atof(*(strNew + (i+1)));
		}
	}

	free2d(strNew , 3 , 4);


	return result;
}











