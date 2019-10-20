CXX = g++
FLAGS = -g -c -std=c++14
#CFLAGS=-I
DEPS = fileReading.hpp hashTable.hpp point.hpp manhattanDistance.hpp dynamicTimeWarping.hpp bruteForce.hpp
OBJ = fileReading.o hashTable.o point.o manhattanDistance.o dynamicTimeWarping.o bruteForce.o
OUT = cube lsh curve

all: $(OUT)

curve: mainCurve.o LSH.o cube.o $(OBJ)
	$(CXX) -g mainCurve.o LSH.o cube.o $(OBJ) -std=c++14 -o curve

cube: mainCube.o cube.o $(OBJ)
	$(CXX) -g mainCube.o cube.o $(OBJ) -std=c++14 -o cube

lsh: mainLSH.o LSH.o $(OBJ)
	$(CXX) -g mainLSH.o LSH.o $(OBJ) -std=c++14 -o lsh

mainCube.o: mainCube.cpp cube.hpp $(DEPS)
	$(CXX) $(FLAGS) mainCube.cpp -o mainCube.o

mainLSH.o: mainLSH.cpp LSH.hpp $(DEPS)
	$(CXX) $(FLAGS) mainLSH.cpp -o mainLSH.o

mainCurve.o: mainCurve.cpp LSH.hpp $(DEPS)
	$(CXX) $(FLAGS) mainCurve.cpp -o mainCurve.o

LSH.o: LSH.cpp LSH.hpp hashTable.hpp point.hpp
	$(CXX) $(FLAGS) LSH.cpp -o LSH.o

cube.o: cube.cpp cube.hpp hashTable.hpp point.hpp
	$(CXX) $(FLAGS) cube.cpp -o cube.o

bruteForce.o: bruteForce.cpp bruteForce.hpp manhattanDistance.hpp point.hpp
	$(CXX) $(FLAGS) bruteForce.cpp -o bruteForce.o

fileReading.o: fileReading.cpp fileReading.hpp point.hpp
	$(CXX) $(FLAGS) fileReading.cpp -o fileReading.o

hashTable.o: hashTable.cpp hashTable.hpp point.hpp
	$(CXX) $(FLAGS) hashTable.cpp -o hashTable.o

manhattanDistance.o: manhattanDistance.cpp manhattanDistance.hpp point.hpp
	$(CXX) $(FLAGS) manhattanDistance.cpp -o manhattanDistance.o

dynamicTimeWarping.o: dynamicTimeWarping.cpp dynamicTimeWarping.hpp manhattanDistance.hpp point.hpp
	$(CXX) $(FLAGS) dynamicTimeWarping.cpp -o dynamicTimeWarping.o

point.o: point.cpp point.hpp
	$(CXX) $(FLAGS) point.cpp -o point.o

clean:
	rm *.o $(OUT)