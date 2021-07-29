#ifndef WINDOW_MNG
#define WINDOW_MNG

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <lite/lite.h>
#include <lite/window.h>
#include <lite/theme.h>

#include <leck/textbutton.h>
#include <leck/button.h>
#include <leck/textline.h>
#include <leck/image.h>

#define HEIGHT		740
#define WIDTH 		1024

#define PATH_BACKGROUND		"/home/camtac/Documents/pebble_land/background"

typedef enum {
	SC1_HOME = 0,		// screen Home page
	SC2_GRAPH,			// screen Graph page
	SC3_CALCULATOR,		// screen Calculator page
	SC4_TEMP_GRAPH,		// screen Temperator graph page
	SC5_OTHER,			// screen Other page

	SC_MAX
} window_page;

/* Variable */
extern  LiteBox	 				*bx[];
extern  LiteTextButtonTheme		*txtBtnTheme;

int 	createWindow 	( int argc, char *argv[]);
int  	changeToPage  	( int page );




#endif