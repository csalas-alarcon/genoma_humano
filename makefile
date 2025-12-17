
COMP=g++
OPT=-Wall -std=c++11 -g

main: Ejemplo.o CadenaADN.o ListaCadenasADN.o
	$(COMP) $(OPT) -o main Ejemplo.o CadenaADN.o ListaCadenasADN.o

Ejemplo.o: Ejemplo.cc CadenaADN.h
	$(COMP) $(OPT) -c  Ejemplo.cc

CadenaADN.o: CadenaADN.cc CadenaADN.h
	$(COMP) $(OPT) -c CadenaADN.cc

ListaCadenasADN.o: ListaCadenasADN.cc ListaCadenasADN.h CadenaADN.h
	$(COMP) $(OPT) -c ListaCadenasADN.cc


clean:
	rm *.o main
