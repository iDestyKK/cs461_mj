# Compiles all tools made for PA1
CC     = g++
CFLAGS = --std=c++98 -O2

all: nfa_gen

nfa_gen: obj/nfa_gen.o
	$(CC) $(CFLAGS) -o $@ $^

obj/nfa_gen.o: src/nfa_gen.cpp
	$(CC) $(CFLAGS) -o $@ -c $^

clean:
	rm nfa_gen obj/*.o
