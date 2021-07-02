#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <signal.h>
#include <unistd.h>

#include "mng_window.h"

#define VERSION "1.0.0"

static void parse_opts(int argc, char *argv[]) {
	int opt;

	const struct option options[] = {
		{"version",		no_argument,		0,		'v'},
		{"debug",		no_argument ,		0,		'd'},
		{"no_hardware",	no_argument ,		0,		'n'},
		{"chattering",	required_argument ,	0,		'c'},
		{NULL,			0,					0,		 0}
	};

	while((opt = getopt_long(argc, argv, "vdnc:", options, NULL)) >= 0) {
		switch(opt) {
			case 'v':	fprintf(stdout, "VERSION %s\n", VERSION); break;
			case 'd':	break;
			case 'n':	break;
			case 'c':	break;
			default:	break;
		}
	}
}

void signalCtrl(int signal) {
	switch(signal){
		case SIGINT	 : 									// Term Interrupt from keyboard (Ex. CTRL+C)
		case SIGTERM :									// 
		case SIGHUP  :									// 
		case SIGKILL : 									// 
		default:
			break;
	}
}

// void exitFunc() {
// 	destroy  ();
// }

int main (int argc, char *argv[]) {

	//atexit(exitFunc);
	signal(SIGINT, 	signalCtrl);
	signal(SIGTERM, signalCtrl);
	signal(SIGHUP, 	signalCtrl);
	signal(SIGKILL, signalCtrl);

	/* EXE OPTION */
	parse_opts 		(argc, argv);									// read file setting
	
	// create window and box
	createWindow  	(argc, argv);
	return 0;
}