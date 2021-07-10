#include "mng_window.h"

LiteWindow				*window;
LiteTextButtonTheme		*txtBtnTheme;

DFBColor 				black 			= { a: 255, r: 0, g: 0, b: 0};

LiteBox				*bx[3];
int 				currPage 	= 	-1;

extern int home_mng(LiteWindow *window);
extern int sc_graph(LiteWindow *window);
extern int sc_cal(LiteWindow *window);


static
void createCmp()
{
	/* create theme */
	lite_new_text_button_theme ("./button/btn_img.png", &txtBtnTheme);

	/* create box */
	for(int i = 0; i < 3; i++) {
		if(bx[i]) lite_destroy_box(bx[i]); // check if bx is not empty , destroy the bx first
		
			lite_new_box  		(&bx[i], LITE_BOX(window), 0, 0, WIDTH, HEIGHT);
			lite_set_box_visible(bx[i], 0);
	}

	home_mng(window);
	sc_cal(window);
	sc_graph(window);


	// set first screen
	currPage = SC1_HOME; // SC_BX1 = 0
	changeToPage 		(currPage);
}

int createWindow ( int argc,char *argv[])
{
	int argcx			= 1;
	char *argvxData[]	= {	"self"};
	char **argvx		= argvxData;

	if (lite_open(&argcx,&argvx)) return -1;

	DFBRectangle rect;
	rect.x 		=		LITE_CENTER_HORIZONTALLY;
	rect.y 		=		LITE_CENTER_VERTICALLY;
	rect.w 		= 		WIDTH;
	rect.h 		= 		HEIGHT;

	lite_new_window		(	NULL , &rect , DWCAPS_ALPHACHANNEL , liteNoWindowTheme , NULL , &window  );
	lite_set_window_background  (window, &black);					/* Set Background Window */
	lite_set_window_opacity  	(window, liteFullWindowOpacity);  	/* show the window */

	createCmp 					(); 								/* create box (mng_window.c)*/

	lite_window_event_loop  	(window, 0);						/* show the window */
	return 0;

}

int changeToPage(int page) {

	if(page < 0) return -1; // error page

	printf("page : %d\n", page);
	printf("currPage : %d\n", page);
	lite_set_box_visible(bx[currPage], 0);
	currPage = page;
	lite_set_box_visible(bx[currPage], 1);

	return 0;
}
