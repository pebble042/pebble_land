#include "mng_window.h"

	DFBRectangle		rect;
	
	LiteImage     		*calculatorTem;
	LiteTextLine		*txtlineInputCal;
	LiteButton 			*btnCal[4][4];

int 		num[4][4] = {	// 48 - 57 = 0 - 9
							{55,56,57,67}, 	//67 = C
							{52,53,54,42}, 	//42 = X
							{49,50,51,45}, 	//45 = -
							{48,61,47,43} 	//61 = '=' ,47 = '/' , 43 = '+'
	 					};

char *textTextline;
char strShow[] = "";

static void button_cal_press (LiteButton *button, void *ctx)
{
	int idx = (int)(long)ctx;
	int	lenStrShow = (int)strlen(strShow);
	

	if(idx == 67) // 67 is C
	{
		memset( strShow , 0 , lenStrShow );
		lite_set_textline_text(txtlineInputCal,strShow);
	}
	else if(idx == 61) // 61 is =
	{
		lite_get_textline_text ( txtlineInputCal , &textTextline);
		strcpy(strShow , textTextline);
		// printf("strShow : %s\n", strShow);
		// printf("lenght strShow : %d\n", (int)strlen(strShow));

		// printf(textTextline);
		// printf("\nSolution Cal\n");
	}
	else
	{	
		char charValue = idx;
		strShow[lenStrShow] = charValue;
		lite_set_textline_text(txtlineInputCal,strShow);
	}

	//printf("strShow : %s\n", strShow);


}
	
int obj_cal(LiteBox *box)
{
	LiteBox 			*bx = box;

	/* template calculatoy */
	rect.x = 0; rect.y = 0; rect.w = 375; rect.h = 525; 
	lite_new_image(bx , &rect , liteDefaultImageTheme , &calculatorTem );
	lite_load_image(calculatorTem , PATH_BACKGROUND "/calculator_template.png");

	/* box for receive Input*/
	rect.x = 42;	rect.y = 38;	rect.w = 290;	rect.h = 62;
	lite_new_textline			( 	bx , &rect , liteNoTextLineTheme , &txtlineInputCal  );
	
	/* Button cal*/
	rect.x = 37; rect.y = 175; rect.w = 60; rect.h = 60;
	for(int i = 0; i<4 ;i++)
	{
		for(int j = 0 ; j<4;j++)
		{
			lite_new_button 		( bx, &rect , liteDefaultButtonTheme , &btnCal[i][j]	);
			lite_set_button_image  	( btnCal[i][j],	LITE_BS_PRESSED, 	"button/btn_test_press.png");

			lite_on_button_press 	(btnCal[i][j],button_cal_press,(void*)(long)num[i][j]);
			rect.x += 80;
		}
		rect.x = 37;
		rect.y += 80;
	}
	return 0;

}