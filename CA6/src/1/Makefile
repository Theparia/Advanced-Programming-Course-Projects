CC :=g++ -std=c++11

all=1.out

1.out:JsonBuilder.o main.o Array.o Data.o NumericData.o Object.o StringData.o InvalidId.o UndefinedType.o DuplicateKey.o
	$(CC) -o 1.out JsonBuilder.o main.o Array.o Data.o NumericData.o Object.o StringData.o InvalidId.o UndefinedType.o DuplicateKey.o

JsonBuilder.o: JsonBuilder.cpp Object.hpp Array.hpp InvalidId.hpp UndefinedType.hpp DuplicateKey.hpp
	$(CC) -c JsonBuilder.cpp

main.o: main.cpp JsonBuilder.hpp
	$(CC) -c main.cpp

Array.o: Array.cpp Data.hpp StringData.hpp NumericData.hpp
	$(CC) -c Array.cpp

Data.o: Data.cpp 
	$(CC) -c Data.cpp

NumericData.o: NumericData.cpp Data.hpp
	$(CC) -c NumericData.cpp

Object.o: Object.cpp Data.hpp StringData.hpp NumericData.hpp 
	$(CC) -c Object.cpp

StringData.o: StringData.cpp Data.hpp
	$(CC) -c StringData.cpp

InvalidId.o: InvalidId.cpp
	$(CC) -c InvalidId.cpp

UndefinedType.o: UndefinedType.cpp
	$(CC) -c UndefinedType.cpp

DuplicateKey.o: DuplicateKey.cpp
	$(CC) -c DuplicateKey.cpp

clean:
	rm 1.out
	rm -r *.o