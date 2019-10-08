CXX = g++
#CFLAGS=-I
DEPS = fileReading.hpp
OBJ = fileReading.o

fileReading.o: fileReading.cpp fileReading.hpp
	$(CXX) -c fileReading.cpp -o fileReading.o

mainCube.o: mainCube.cpp
	$(CXX) -c mainCube.cpp -o mainCube.o

mainLSH.o: mainLSH.cpp
	$(CXX) -c mainLSH.cpp -o mainLSH.o

mainCube: mainCube.o
	$(CXX) –o mainCube# $(CFLAGS)

mainLSH: mainLSH.o $(OBJ)
	$(CXX) –o mainLSH#$(CFLAGS)

clean:
	rm –f *.o mainCube mainLSH