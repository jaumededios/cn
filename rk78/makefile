EXECS=rf_pendol flux

all: $(EXECS)

flux: flux.o rk78.o
	gcc -Wall -o flux flux.c rk78.o pendol.o -lm

flux.o: flux.c
	gcc -c -Wall -o flux.o flux.c -lm

rf_pendol: pendol.o rk78.o
	gcc -Wall -o rf_pendol rf_pendol.c pendol.o rk78.o -lm

pendol.o: pendol.c
	gcc -c -Wall -o pendol.o pendol.c -lm

rk78.o: rk78.c
	gcc -c -Wall -o rk78.o rk78.c -lm

clean:
	rm -f *.o

realclean: clean
	rm -f $(EXECS)

remake: realclean all
