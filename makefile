CXX = g++
FLAGS = -g -c -std=c++14
#CFLAGS=-I
DEPS = fileReading.hpp hashTable.hpp point.hpp manhattanDistance.hpp
OBJ = fileReading.o hashTable.o point.o manhattanDistance.o bruteForce.o
OUT = mainCube mainLSH

all: $(OUT)

mainCube: mainCube.o
	$(CXX) -g mainCube.o -std=c++14 -o mainCube

mainLSH: mainLSH.o LSH.o $(OBJ)
	$(CXX) -g mainLSH.o LSH.o $(OBJ) -std=c++14 -o mainLSH

mainCube.o: mainCube.cpp
	$(CXX) $(FLAGS) mainCube.cpp -o mainCube.o

mainLSH.o: mainLSH.cpp $(DEPS)
	$(CXX) $(FLAGS) mainLSH.cpp -o mainLSH.o

LSH.o: LSH.cpp LSH.hpp hashTable.hpp point.hpp
	$(CXX) $(FLAGS) LSH.cpp -o LSH.o

bruteForce.o: bruteForce.cpp
	$(CXX) $(FLAGS) bruteForce.cpp -o bruteForce.o

fileReading.o: fileReading.cpp fileReading.hpp point.hpp
	$(CXX) $(FLAGS) fileReading.cpp -o fileReading.o

hashTable.o: hashTable.cpp hashTable.hpp point.hpp
	$(CXX) $(FLAGS) hashTable.cpp -o hashTable.o

manhattanDistance.o: manhattanDistance.cpp manhattanDistance.hpp point.hpp
	$(CXX) $(FLAGS) manhattanDistance.cpp -o manhattanDistance.o

point.o: point.cpp point.hpp
	$(CXX) $(FLAGS) point.cpp -o point.o

clean:
	rm *.o $(OUT)