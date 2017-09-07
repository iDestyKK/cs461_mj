CC      = g++
CFLAGS  = --std=c++98 -g
HANDY_P = ./lib/handy

all: nfa2dfa

nfa2dfa:
		$(CC) $(CFLAGS) -o nfa2dfa main.cpp nfa.cpp $(HANDY_P)/file.c $(HANDY_P)/stream.c

clean:
		rm nfa2dfa
