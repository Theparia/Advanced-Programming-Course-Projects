CC :=g++ -std=c++11
OBJECTS = main.o Channel.o Echo.o Fred.o Librarian.o Logger.o Observer.o Robot.o functions.o DuplicateName.o Nonexistence.o SameSrcAndDst.o


all=2.out

2.out: $(OBJECTS)
	$(CC) -o 2.out $(OBJECTS)

DuplicateName.o: DuplicateName.cpp 
	$(CC) -c DuplicateName.cpp

Nonexistence.o:Nonexistence.cpp
	$(CC) -c Nonexistence.cpp

SameSrcAndDst.o:SameSrcAndDst.cpp
	$(CC) -c SameSrcAndDst.cpp

main.o: main.cpp Observer.hpp functions.hpp
	$(CC) -c main.cpp

functions.o: functions.cpp Observer.hpp SameSrcAndDst.hpp DuplicateName.hpp
	$(CC) -c functions.cpp 

Channel.o: Channel.cpp Robot.hpp
	$(CC) -c Channel.cpp

Echo.o: Echo.cpp Robot.hpp Channel.hpp
	$(CC) -c Echo.cpp

Fred.o: Fred.cpp Robot.hpp Channel.hpp
	$(CC) -c Fred.cpp

Librarian.o: Librarian.cpp Channel.hpp Robot.hpp
	$(CC) -c Librarian.cpp

Logger.o: Logger.cpp Channel.hpp Robot.hpp
	$(CC) -c Logger.cpp

Observer.o: Observer.cpp Robot.hpp Channel.hpp Echo.hpp Logger.hpp Fred.hpp Librarian.hpp Nonexistence.hpp DuplicateName.hpp SameSrcAndDst.hpp
	$(CC) -c Observer.cpp

Robot.o: Robot.cpp 
	$(CC) -c Robot.cpp

clean:
	rm 2.out
	rm -r *.o