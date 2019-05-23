CXXFLAGS = -Wall -std=c++11 -O2

all: serveis.exe

clean:
	rm -f serveis.exe *.o

serveis.exe: main.o commonlib.o
	$(CXX) $^ -o $@

main.o: main.cpp commonlib.h
commonlib.o: commonlib.cpp commonlib.h

