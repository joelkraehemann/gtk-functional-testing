CFLAGS = `pkg-config --cflags gtk+-2.0`
LDFLAGS = `pkg-config --libs gtk+-2.0`

OBJECTS = tictactoe.o ttt_functional_test_util.o ttt_functional_test.o

ttt_functional_test: ttt_functional_test.o ttt_functional_test_util.o tictactoe.o
	gcc -o $@ ${OBJECTS} ${CFLAGS} ${LDFLAGS}

tictactoe.o: tictactoe.[ch]
	gcc -c $^ ${CFLAGS} ${LDFLAGS}

ttt_functional_test_util.o: ttt_functional_test_util.[ch]
	gcc -c $^ ${CFLAGS} ${LDFLAGS}

ttt_functional_test.o: ttt_functional_test.c
	gcc -c $^ ${CFLAGS} ${LDFLAGS}

clean:
	rm ttt_functional_test ${OBJECTS}
	rm *.gch
