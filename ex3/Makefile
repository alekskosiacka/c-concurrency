#################################################
# Makefile for 370ct                            #
#################################################

CC = gcc
CFLAGS = -Wall 
LLIBS =  -lm -lpthread
EXE = baseprog

OBJS = $(patsubst %.c,%.o,$(wildcard *.c))

#----------
dining: $(OBJS)
	$(CC) $(LLIBS) $(OBJS)  -o $(EXE)
	rm -f *.o *~

#----------

$(OBJS): %.o : %.c
	$(CC) $(CFLAGS) -c $<

#----------

clean:
	rm -f *.o *.*~ *~  $(EXE)

#----------


