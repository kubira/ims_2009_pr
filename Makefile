# Makefile for client/server example
# see 'man make' for more details
GEN          = generator
GEN_SOURCES  = generator.c

DEFINES         = 

CFLAGS         = -g

LIBRARIES       = -lm

CC              = gcc
GEN_OBJECTS  = $(GEN_SOURCES:.c=.o)
INCLUDES        = #-I.
LIBDIRS         = 
LDFLAGS         = $(LIBDIRS) $(LIBRARIES)

###########################################

.SUFFIXES: .c .o

.c.o:
		$(CC) $(CFLAGS) -c $<

###########################################

all:		$(GEN)

rebuild:	clean all

$(GEN):	$(GEN_OBJECTS)
		$(CC) $(GEN_OBJECTS) $(LDFLAGS) -o $@

###########################################

clean:
	rm -fr core* *~ $(GEN_OBJECTS) $(GEN) .make.state .sb

###########################################

run:
	./generator
