CXXFLAGS = -Wall -std=c++17 -O3 -D_GLIBCXX_DEBUG

all: clean Serveis.exe run_test convert
setup.exe: src/setup.cc
	$(CXX) $^ -o $@

run_test:
	./Serveis.exe d

clean:
	rm -f Serveis.exe ./src/*.o ./lib/*.o result.md Serveis.html

Serveis.exe: src/main.o lib/header.o
	$(CXX) $^ -o $@

reset: clean Serveis.exe
convert: result.md
	pandoc result.md -o Serveis.html

main.o: src/main.cpp lib/header.hh
lib/header.o: lib/header.cpp lib/header.hh