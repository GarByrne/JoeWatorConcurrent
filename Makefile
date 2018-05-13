
CC=g++
CFLAGS= -std=c++11 -pthread
HFILES= Animal.h
CPPFILES= Animal.cpp Finale.cpp

#This rule says that each .o file depends on a .cpp file of the same name
%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUGFLAGS)

ALL: $(HFILES) $(CPPFILES)
	$(CC) -o Wator $(CFLAGS) $(CPPFILES) $(DEBUGFLAGS)

DEBUG: DEBUGFLAGS = -DDEBUG
DEBUG: ALL

#this is customary and just deletes all .o files
CLEAN:
	rm *.o
