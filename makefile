#carpeta de la llibreria amb les llibreries
LIB=lib/

#subcarpeta de LIB on hi ha tot el relacionat amb edos
_EDOS=edos/
EDOS=$(LIB)$(_EDOS)

#subcarpeta de LIB on hi ha tot el relacionat amb àlgebra lineal
_LINALG=linalg/
LINALG=$(LIB)$(_LINALG)

#subcarpeta de LIB on hi ha els camps diversos
_FIELDS=fields/
FIELDS=$(LIB)$(_FIELDS)

#executables a la carpeta principal
EXECS=rf_pendol flux_pendol



# ! ---------- Codis relacionats amb el managment de tot plegat ----------- !

#build de tot

all: $(EXECS)

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


# ! ---------- Programes Finals -------------- !

#construeix el programa que et dona òrbites del pèndol
rf_pendol: $(FIELDS)pendol.o $(EDOS)rk78.o
	gcc -Wall -o rf_pendol rf_pendol.c $(FIELDS)pendol.o $(EDOS)rk78.o -lm

#construeix el programa que et dona el flux del pèndol
flux_pendol: $(FIELDS)pendol.o $(EDOS)flux.o 
	gcc -Wall -o flux_pendol flux_pendol.c $(FIELDS)pendol.o $(EDOS)flux.o $(EDOS)rk78.o -lm

# ! ---------- Programes relacionats amb els camps ------------ !

#codi del pendol
$(FIELDS)pendol.o: $(FIELDS)pendol.c
	gcc -c -Wall -o $(FIELDS)pendol.o $(FIELDS)pendol.c -lm

# ! ---------- Programes relacionats amb el calcul d'EDOS ------------ !

#construeix la llibreria del flux

$(EDOS)flux.o: $(EDOS)flux.c  $(EDOS)rk78.o
	gcc -c -Wall -o $(EDOS)flux.o $(EDOS)flux.c -lm

#codi objecte del rk78
$(EDOS)rk78.o: $(EDOS)rk78.c
	gcc -c -Wall -o $(EDOS)rk78.o $(EDOS)rk78.c -lm

# ! ---------- Programes relacionats amb COSES LINEALS ------------ !

#codi objecte del qrres
$(LINALG)qrres.o: $(LINALG)qrres.c
	gcc -c -Wall -o $(LINALG)qrres.o $(LINALG)qrres.c -lm
