CXX = g++
FLAGS = -g -c -std=c++14
#CFLAGS=-I
DEPS = fileReading.hpp hashTable.hpp dataStructs.hpp manhattanDistance.hpp dynamicTimeWarping.hpp bruteForce.hpp
OBJ = fileReading.o hashTable.o dataStructs.o manhattanDistance.o dynamicTimeWarping.o bruteForce.o
OUT = cube lsh curve

all: $(OUT)

curve: mainCurve.o gridCurve.o LSH.o cube.o $(OBJ)
	$(CXX) -g mainCurve.o gridCurve.o LSH.o cube.o $(OBJ) -std=c++14 -o curve

cube: mainCube.o cube.o $(OBJ)
	$(CXX) -g mainCube.o cube.o $(OBJ) -std=c++14 -o cube

lsh: mainLSH.o LSH.o $(OBJ)
	$(CXX) -g mainLSH.o LSH.o $(OBJ) -std=c++14 -o lsh

mainCube.o: mainCube.cpp cube.hpp $(DEPS)
	$(CXX) $(FLAGS) mainCube.cpp -o mainCube.o

mainLSH.o: mainLSH.cpp LSH.hpp $(DEPS)
	$(CXX) $(FLAGS) mainLSH.cpp -o mainLSH.o

mainCurve.o: mainCurve.cpp gridCurve.hpp LSH.hpp cube.hpp $(DEPS)
	$(CXX) $(FLAGS) mainCurve.cpp -o mainCurve.o

gridCurve.o: gridCurve.cpp gridCurve.hpp LSH.hpp cube.hpp dataStructs.hpp
	$(CXX) $(FLAGS) gridCurve.cpp -o gridCurve.o

LSH.o: LSH.cpp LSH.hpp hashTable.hpp dataStructs.hpp
	$(CXX) $(FLAGS) LSH.cpp -o LSH.o

cube.o: cube.cpp cube.hpp hashTable.hpp dataStructs.hpp
	$(CXX) $(FLAGS) cube.cpp -o cube.o

bruteForce.o: bruteForce.cpp bruteForce.hpp manhattanDistance.hpp dataStructs.hpp
	$(CXX) $(FLAGS) bruteForce.cpp -o bruteForce.o

fileReading.o: fileReading.cpp fileReading.hpp dataStructs.hpp
	$(CXX) $(FLAGS) fileReading.cpp -o fileReading.o

hashTable.o: hashTable.cpp hashTable.hpp dataStructs.hpp
	$(CXX) $(FLAGS) hashTable.cpp -o hashTable.o

manhattanDistance.o: manhattanDistance.cpp manhattanDistance.hpp dataStructs.hpp
	$(CXX) $(FLAGS) manhattanDistance.cpp -o manhattanDistance.o

dynamicTimeWarping.o: dynamicTimeWarping.cpp dynamicTimeWarping.hpp manhattanDistance.hpp dataStructs.hpp
	$(CXX) $(FLAGS) dynamicTimeWarping.cpp -o dynamicTimeWarping.o

dataStructs.o: dataStructs.cpp dataStructs.hpp
	$(CXX) $(FLAGS) dataStructs.cpp -o dataStructs.o

clean:
	rm *.o $(OUT)