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
#subcarpeta de LIB on hi ha els camps diversos
_NEWTON=newton/
NEWTON=$(LIB)$(_NEWTON)
#subcarpeta de LIB on hi ha els camps diversos
_PERIOD=period/
PERIOD=$(LIB)$(_PERIOD)
#carpeta on hi ha les parts
PARTS=exercicis/


#executables a la carpeta principal
EXECS = $(PARTS)1/rf_pendol\
		$(PARTS)1/flux_pendol\
		$(PARTS)1/harmonic_errors\
		$(PARTS)1/1.4.a_errors\
		$(PARTS)1/lorentz\
		\
		$(PARTS)2/differential\
		\
		period_pendol\
		period_halo\
		continue_halo


# Coses que fan falta en general per a fer  tot lo numèric
NUMERIC = $(EDOS)flux.o \
		  $(EDOS)rk78.o \
		  $(LINALG)qrres.o \
		  $(PERIOD)troba_periodiques.o 
# camps amb els que podem treballar 
FIELDLIST = $(FIELDS)pendol.o \
		    $(FIELDS)var_pendol.o \
		    $(FIELDS)rtbp.o \
		    $(FIELDS)ex_1.4.o \
		    $(FIELDS)lorentz.o \
		    $(FIELDS)ex_2.o 

LIBRARY = $(NUMERIC) \
		  $(FIELDS)
          
# ! ---------- Codis relacionats amb el management de tot plegat ----------- !

#build de tot

all: $(EXECS) 

libraries: $(LIBRARY)


#neteja tots els object code de la carpeta principal
clean: clean_lib clean_parts
	rm -f *.o

#neteja tots els objectes de la llibreria
clean_lib:
	rm -f $(LIB)*/*.o

#neteja tots els objectes de les parts
clean_parts:
	rm -f $(PARTS)*/*.o

#neteja tot el que no sigui codi
realclean: clean
	rm -f $(EXECS)

#neteja tot el que no sigui codi i recompila-ho tot
remake: realclean all libraries




# ! ---------- Programes Finals -------------- !


#construeix el programa que et continua el halo
continue_halo: continue_halo.c \
			   $(NUMERIC) \
			   $(FIELDS)rtbp.o 

	gcc -Wall -o continue_halo continue_halo.c \
			   $(NUMERIC) \
			   $(FIELDS)rtbp.o \
	           -lm

#construeix el programa que et dona òrbites halo
period_halo:   period_halo.c \
			   $(NUMERIC) \
			   $(FIELDS)rtbp.o 

	gcc -Wall -o period_halo period_halo.c \
			   $(NUMERIC) \
			   $(FIELDS)rtbp.o \
	           -lm



#construeix el programa que et dona òrbites del pèndol
period_pendol: period_pendol.c \
			   $(NUMERIC) \
			   $(FIELDS)var_pendol.o 

	gcc -Wall -o period_pendol period_pendol.c \
			   $(NUMERIC) \
			   $(FIELDS)var_pendol.o \
	           -lm

#construeix el programa que et dona òrbites del pèndol
$(PARTS)1/rf_pendol: $(PARTS)1/rf_pendol.c \
			   $(FIELDS)pendol.o \
			   $(EDOS)rk78.o 

	gcc -Wall -o $(PARTS)1/rf_pendol $(PARTS)1/rf_pendol.c \
			   $(FIELDS)pendol.o  \
			   $(EDOS)rk78.o \
			   -lm

#construeix el programa que et dona el flux del pèndol
$(PARTS)1/flux_pendol: $(PARTS)1/flux_pendol.c \
					   $(FIELDS)var_pendol.o \
					   $(EDOS)flux.o 

	gcc -Wall -o $(PARTS)1/flux_pendol $(PARTS)1/flux_pendol.c \
					   $(FIELDS)var_pendol.o \
					   $(EDOS)flux.o \
					   $(EDOS)rk78.o -lm

#construeix el programa que et dona el flux de l'harmonic
$(PARTS)1/harmonic_errors: $(PARTS)1/harmonic_errors.c \
					   $(FIELDS)ex_1.4.o \
					   $(EDOS)flux.o 

	gcc -Wall -o $(PARTS)1/harmonic_errors $(PARTS)1/harmonic_errors.c \
					   $(FIELDS)ex_1.4.o \
					   $(EDOS)flux.o \
					   $(EDOS)rk78.o -lm

#construeix el programa que et dona el flux del 1.4.a
$(PARTS)1/1.4.a_errors: $(PARTS)1/1.4.a_errors.c \
					   $(FIELDS)ex_1.4.o \
					   $(EDOS)flux.o 

	gcc -Wall -o $(PARTS)1/1.4.a_errors $(PARTS)1/1.4.a_errors.c \
					   $(FIELDS)ex_1.4.o \
					   $(EDOS)flux.o \
					   $(EDOS)rk78.o -lm

#construeix el programa que et representa Lorentz
$(PARTS)1/lorentz: $(PARTS)1/lorentz.c \
					   $(FIELDS)lorentz.o \
					   $(EDOS)rk78.o 

	gcc -Wall -o $(PARTS)1/lorentz $(PARTS)1/lorentz.c \
					   $(FIELDS)lorentz.o \
					   $(EDOS)flux.o \
					   $(EDOS)rk78.o -lm

#construeix el programa que et representa Lorentz
$(PARTS)2/differential: $(PARTS)2/differential.c \
					   $(FIELDS)ex_2.o \
					   $(EDOS)flux.o 

	gcc -Wall -o $(PARTS)2/differential $(PARTS)2/differential.c \
					   $(FIELDS)ex_2.o \
					   $(EDOS)flux.o \
					   $(EDOS)rk78.o -lm



# ! ---------- Programes relacionats amb els camps ------------ !



#codi de l'atractor de lorentz
$(FIELDS)lorentz.o: $(FIELDS)lorentz.c
	gcc -c -Wall -o $(FIELDS)lorentz.o $(FIELDS)lorentz.c -lm

#codi dels camps del problema 1.4
$(FIELDS)ex_1.4.o: $(FIELDS)ex_1.4.c
	gcc -c -Wall -o $(FIELDS)ex_1.4.o $(FIELDS)ex_1.4.c -lm

#codi dels camps del problema 2
$(FIELDS)ex_2.o: $(FIELDS)ex_2.c
	gcc -c -Wall -o $(FIELDS)ex_2.o $(FIELDS)ex_2.c -lm


#codi del pendol
$(FIELDS)pendol.o: $(FIELDS)pendol.c
	gcc -c -Wall -o $(FIELDS)pendol.o $(FIELDS)pendol.c -lm

#codi del pendol amb variacionals
$(FIELDS)var_pendol.o: $(FIELDS)var_pendol.c
	gcc -c -Wall -o $(FIELDS)var_pendol.o $(FIELDS)var_pendol.c -lm

#codi del problema de 3 cossos
$(FIELDS)rtbp.o: $(FIELDS)rtbp.c
	gcc -c -Wall -o $(FIELDS)rtbp.o $(FIELDS)rtbp.c -lm



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








# ! ---------- Programes relacionats amb MÈTODE DE NEWTON ------------ !

#codi objecte del newton #al final no l'utilitzem per que no es nxn!!!
$(NEWTON)newton.o: $(NEWTON)newton.c $(LINALG)qrres.o
	gcc -c -Wall -o $(NEWTON)newton.o $(NEWTON)newton.c -lm







# ! -------- Programa per a trobar es òrbites periòdiques

$(PERIOD)troba_periodiques.o: $(PERIOD)troba_periodiques.c $(LINALG)qrres.o $(EDOS)flux.o
	gcc -c -Wall -o $(PERIOD)troba_periodiques.o $(PERIOD)troba_periodiques.c -lm
