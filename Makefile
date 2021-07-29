app			=		main_program
mng			=		mng_window
sc_home 	=		sc_home
sc_graph 	=		sc_graph
sc_cal 		=		sc_cal
sc_tmpgr 	=		sc_tempGraph
sc_other	= 		sc_other
mng_graph	=		graph
cal			=		calculate
obj_cal		=		obj_cal



LIBS	=	-ldirect -ldirectfb -llite -lleck -lpthread -lm

INCLUDES = -I /usr/local/include/directfb/

STATIC = -static
CFLAGS = -Wall

.PHONY: default

default:
	gcc $(CFLAGS) $(app).c $(mng).c $(mng_graph).c $(sc_home).c $(sc_graph).c $(sc_cal).c $(sc_tmpgr).c $(sc_other).c   $(obj_cal).c $(cal).c -o $(app) $(INCLUDES) $(LIBS)

clean:
	@rm -f *.o
	@rm -f *.a
	@rm -f $(app)