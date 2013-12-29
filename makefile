###############################################################################
#	SPECIAL MACROS
#
#	CC	-	command name of the compiler
#	CFLAGS	-	flags to be passed to the compiler
#	$@	-	full name of the current target (allows for recursion)
#	$?	-	list of dependency files that are out of date
#	$<	-	name of the current dependency
###############################################################################

#select compiler
CC=g++
#compile flags
CFLAGS=-Wall -std=c++11
#additional libraries
LIBS=-lsfml-system -lsfml-graphics -lsfml-window 
#executable name
EX=tacticalCommand
#sources
SOURCES=main.cpp Game.cpp Board.cpp Player.cpp
#source objects
OBJECTS=$(SOURCES:.cpp=.o)


#build all
all: $(SOURCES) $(EX) $(HEADERS)

#build for debugging
debug: CFLAGS += -g
debug: $(SOURCES) $(EX)

#build the executable
$(EX): $(OBJECTS)
	$(CC) -o $(EX) $(OBJECTS) $(CFLAGS) $(LIBS)

#recursively build all sources
.cpp.o:
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -rf *.o $(EX)
