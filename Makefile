CXX=g++
CXXFLAGS=-g -Wall 

OBJS=main.o minesweeper.o solver.o

all: sweep

sweep: $(OBJS)
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ $(OBJS)

main.o: minesweeper.o solver.o
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c main.cpp
minesweeper.o: minesweeper.cpp minesweeper.h 
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c minesweeper.cpp
solver.o: solver.cpp solver.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c solver.cpp

clean:
	rm -f *.o sweep