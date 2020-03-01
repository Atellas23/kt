CXXFLAGS = -Wall -std=c++17 -O3 -D_GLIBCXX_DEBUG

all: main.exe

run_test: reset
	./main.exe test2.csv serveis.dat
	@make clean_bin

clean_bin:
	rm -f main.exe *.o ./lib/*.o

clean: clean_bin
	rm -f *.md

main.exe: main.o lib/header.o
	$(CXX) $^ -o $@

reset: clean main.exe

main.o: main.cpp lib/header.hh
lib/header.o: lib/header.cpp lib/header.hh