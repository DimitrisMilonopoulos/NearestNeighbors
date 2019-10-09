CXX = g++
#CFLAGS=-I
DEPS = fileReading.hpp hashTable.hpp
OBJ = fileReading.o hashTable.o

all: mainCube mainLSH

mainCube: mainCube.o $(OBJ)
	$(CXX) mainCube.o $(OBJ) -o mainCube

mainLSH: mainLSH.o $(OBJ)
	$(CXX) mainLSH.o $(OBJ) -o mainLSH

mainCube.o: mainCube.cpp fileReading.hpp
	$(CXX) -c mainCube.cpp -o mainCube.o

mainLSH.o: mainLSH.cpp fileReading.hpp
	$(CXX) -c mainLSH.cpp -o mainLSH.o

fileReading.o: fileReading.cpp fileReading.hpp
	$(CXX) -c fileReading.cpp -o fileReading.o

clean:
	rm –f *.o mainCube mainLSH