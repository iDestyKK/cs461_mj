CC      = gcc
CFLAGS  = --std=gnu89 -g
HANDY_P = ./lib/handy

all: nfa2dfa

nfa2dfa:
	$(CC) $(CFLAGS) -o nfa2dfa nfa2dfa.c $(HANDY_P)/file.c $(HANDY_P)/stream.c $(HANDY_P)/memory.c $(HANDY_P)/cnds/cn_vec.c $(HANDY_P)/cnds/cn_map.c $(HANDY_P)/cnds/cn_comp.c $(HANDY_P)/cnds/cn_list.c $(HANDY_P)/cnds/cn_string.c

clean:
	rm nfa2dfa
