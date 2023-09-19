CC := g++ -std=c++11
CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer
OBJECTS = main.o rsdl.o Bullet.o coordinates.o Enemy.o Event.o Game.o Gatling.o InputFunctions.o Missile.o Player.o Runner.o Scrambler.o StubbornRunner.o SuperTrooper.o Tesla.o Tower.o Glue.o

all: FieldRunners.out

FieldRunners.out: $(OBJECTS)
	$(CC) $(OBJECTS) $(CCFLAGS) -o FieldRunners.out

main.o: main.cpp rsdl.hpp Player.hpp InputFunctions.hpp Game.hpp
	$(CC) -c main.cpp

rsdl.o: rsdl.cpp
	$(CC) -c rsdl.cpp

Bullet.o: Bullet.cpp rsdl.hpp coordinates.hpp Enemy.hpp
	$(CC) -c Bullet.cpp

coordinates.o: coordinates.cpp rsdl.hpp 
	$(CC) -c coordinates.cpp

Enemy.o: Enemy.cpp coordinates.hpp 
	$(CC) -c Enemy.cpp

Event.o: Event.cpp rsdl.hpp Enemy.hpp Player.hpp
	$(CC) -c Event.cpp

Game.o: Game.cpp Enemy.hpp Player.hpp Event.hpp Runner.hpp Scrambler.hpp SuperTrooper.hpp StubbornRunner.hpp
	$(CC) -c Game.cpp

Gatling.o: Gatling.cpp Tower.hpp Enemy.hpp
	$(CC) -c Gatling.cpp

Glue.o: Glue.cpp Tower.hpp Enemy.hpp
	$(CC) -c Glue.cpp

InputFunctions.o: InputFunctions.cpp coordinates.hpp 
	$(CC) -c InputFunctions.cpp

Missile.o: Missile.cpp Tower.hpp Enemy.hpp
	$(CC) -c Missile.cpp

Player.o: Player.cpp Enemy.hpp Gatling.hpp Missile.hpp Tesla.hpp Glue.hpp
	$(CC) -c Player.cpp

Runner.o: Runner.cpp rsdl.hpp coordinates.hpp Enemy.hpp
	$(CC) -c Runner.cpp

Scrambler.o: Scrambler.cpp rsdl.hpp coordinates.hpp Enemy.hpp
	$(CC) -c Scrambler.cpp

StubbornRunner.o: StubbornRunner.cpp rsdl.hpp coordinates.hpp Enemy.hpp
	$(CC) -c StubbornRunner.cpp

SuperTrooper.o: SuperTrooper.cpp rsdl.hpp coordinates.hpp Enemy.hpp
	$(CC) -c SuperTrooper.cpp

Tesla.o: Tesla.cpp Tower.hpp Enemy.hpp
	$(CC) -c Tesla.cpp

Tower.o: Tower.cpp rsdl.hpp coordinates.hpp Bullet.hpp Enemy.hpp
	$(CC) -c Tower.cpp

.PHONY: clean
clean:
	rm -r *.o