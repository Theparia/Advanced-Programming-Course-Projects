CC=g++
VERSION=-std=c++11
CFLAGS=-c
OBJECTS=main.o Author.o Book.o functions.o Goodreads.o Review.o User.o
EXECUTABLE=Goodreads.out

all: ${EXECUTABLE}

${EXECUTABLE}: ${OBJECTS}
	${CC} ${VERSION} -o ${EXECUTABLE} ${OBJECTS}

main.o: main.cpp functions.hpp Goodreads.hpp
	${CC} ${VERSION} ${CFLAGS} main.cpp

Author.o: Author.cpp 
	${CC} ${VERSION} ${CFLAGS} Author.cpp

Book.o: Book.cpp Author.hpp Review.hpp
	${CC} ${VERSION} ${CFLAGS} Book.cpp

functions.o: functions.cpp Goodreads.hpp Book.hpp User.hpp
	${CC} ${VERSION} ${CFLAGS} functions.cpp

Goodreads.o: Goodreads.cpp Book.hpp Author.hpp User.hpp Review.hpp functions.hpp
	${CC} ${VERSION} ${CFLAGS} Goodreads.cpp

Review.o: Review.cpp 
	${CC} ${VERSION} ${CFLAGS} Review.cpp

User.o: User.cpp Book.hpp Author.hpp Review.hpp
	${CC} ${VERSION} ${CFLAGS} User.cpp



clean:
		rm -rf ${OBJECTS} 
		rm ${EXECUTABLE}

