CXXFLAGS = -Wall -std=c++11 -O2

all: serveis.exe

clean:
	rm -f serveis.exe *.o

serveis.exe: main.o Criatura.o Biblioteca.o Muni.o
	$(CXX) $^ -o $@

main.o: main.cc Criatura.h Muni.h
Biblioteca.o: Biblioteca.cc Biblioteca.h
Muni.o: Muni.cc Muni.h Biblioteca.h
Criatura.o: Criatura.cc Criatura.h Biblioteca.h
