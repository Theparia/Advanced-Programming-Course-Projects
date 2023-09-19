CC :=g++ -std=c++11

all: utrip.out

utrip.out: main.o Utrip.o Hotel.o User.o ManagementInterface.o Exception.o Filter.o StructsAndDefines.o Room.o Reservation.o CSVReader.o Rating.o
	$(CC) -o utrip.out main.o Utrip.o Hotel.o User.o ManagementInterface.o Exception.o Filter.o StructsAndDefines.o Room.o Reservation.o CSVReader.o Rating.o

main.o: main.cpp Utrip.hpp ManagementInterface.hpp Exception.hpp
	$(CC) -c main.cpp

Hotel.o: Hotel.cpp Exception.hpp StructsAndDefines.hpp Room.hpp User.hpp Rating.hpp
	$(CC) -c Hotel.cpp

User.o: User.cpp Exception.hpp Filter.hpp Hotel.hpp Reservation.hpp
	$(CC) -c User.cpp

Utrip.o: Utrip.cpp User.hpp Hotel.hpp Exception.hpp CSVReader.hpp
	$(CC) -c Utrip.cpp

ManagementInterface.o:ManagementInterface.cpp Utrip.hpp Exception.hpp StructsAndDefines.hpp
	$(CC) -c ManagementInterface.cpp

Exception.o: Exception.cpp StructsAndDefines.hpp
	$(CC) -c Exception.cpp

Filter.o: Filter.cpp Hotel.hpp Reservation.hpp
	$(CC) -c Filter.cpp

StructsAndDefines.o: StructsAndDefines.cpp
	$(CC) -c StructsAndDefines.cpp

Room.o: Room.cpp StructsAndDefines.hpp
	$(CC) -c Room.cpp

Reservation.o: Reservation.cpp Hotel.hpp
	$(CC) -c Reservation.cpp

CSVReader.o: CSVReader.cpp Hotel.hpp Rating.hpp
	$(CC) -c CSVReader.cpp

Rating.o: Rating.cpp
	$(CC) -c Rating.cpp

clean:
	rm utrip.out
	rm -r *.o