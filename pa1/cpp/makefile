CC      = g++
CFLAGS  = --std=c++98 -O2
HANDY_P = ./lib/handy

nfa2dfa: obj/prog.o obj/nfa.o obj/handy.a
	@#$(CC) $(CFLAGS) -L./obj -Wl,-rpath=./obj -o $@ $^
	$(CC) $(CFLAGS) -o $@ $^

obj/handy.a: obj/handy_file.o obj/handy_stream.o
	ar rcs $@ $^
	@#rm $^

obj/handy_file.o: $(HANDY_P)/file.c
	$(CC) $(CFLAGS) -o $@ -c $^

obj/handy_stream.o: $(HANDY_P)/stream.c
	$(CC) $(CFLAGS) -o $@ -c $^

obj/prog.o: src/main.cpp
	$(CC) $(CFLAGS) -o $@ -c $^

obj/nfa.o: src/nfa.cpp
	$(CC) $(CFLAGS) -o $@ -c $^

clean:
	rm -f nfa2dfa obj/*.o obj/*.a obj/*.so
