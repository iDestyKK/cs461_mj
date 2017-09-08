CC      = g++
CFLAGS  = --std=c++98 -g
HANDY_P = ./lib/handy

all: nfa2dfa

nfa2dfa:
	$(CC) $(CFLAGS) -o nfa2dfa main.cpp nfa.cpp $(HANDY_P)/file.c $(HANDY_P)/stream.c

#all: handy prog nfa nfa2dfa

#handy:
#	$(CC) $(CFLAGS) -shared -o obj/handy.o $(HANDY_P)/file.c $(HANDY_P)/stream.c
#	ar ruv obj/handy.a obj/handy.o
#
#prog:
#	$(CC) $(CFLAGS) -o obj/prog.o -c main.cpp
#
#nfa:
#	$(CC) $(CFLAGS) -o obj/nfa.o -c nfa.cpp
#
#nfa2dfa:
#	$(CC) $(CFLAGS) -o nfa2dfa -I./obj/ obj/prog.o obj/nfa.o obj/handy.a obj/handy.o
#
clean:
	rm nfa2dfa obj/*.o obj/*.a
