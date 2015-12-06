#executables a la carpeta principal
EXECS=rf_pendol flux_pendol

#carpeta de la llibreria amb les llibreries
LIB=lib/

#subcarpeta de LIB on hi ha tot el relacionat amb edos
EDOS=edos/

#subcarpeta de LIB on hi ha tot el relacionat amb àlgebra lineal
LINALG=linalg/

#build de tot
all: $(EXECS)

#construeix la llibreria del flux
flux.o: $(LIB)/S(EDOS)/flux.c
	gcc -c -Wall -o $(LIB)$(EDOS)flux.o $(LIB)$(EDOS)flux.c -lm

#construeix el rpograma que et dona òrbites del pèndol
rf_pendol: pendol.o $(LIB)$(EDOS)rk78.o
	gcc -Wall -o rf_pendol rf_pendol.c pendol.o rk78.o -lm

#codi objecte de l'anterior
pendol.o: pendol.c
	gcc -c -Wall -o pendol.o pendol.c -lm

#codi objecte del rk78
rk78.o: $(LIB)/S(EDOS)/rk78.c
	gcc -c -Wall -o $(LIB)$(EDOS)rk78.o rk78.c -lm

#neteja tots els object code de la carpeta principal
clean: clean_lib
	rm -f *.o

#neteja tots els objectes de la llibreria
clean_lib:
	rm -f $(LIB)/*/*.o

#neteja tot el que no sigui codi
realclean: clean
	rm -f $(EXECS)

#neteja tot el que no sigui codi i recompila-ho tot
remake: realclean all
