CC=g++
STD=-std=c++11
CF=$(STD)
BUILD_DIR=build

all: $(BUILD_DIR) utrip.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) $(CF) -c utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) $(CF) -c utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) $(CF) -c utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/route.cpp -o $(BUILD_DIR)/route.o

$(BUILD_DIR)/handlers.o: app/handlers.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp app/Utrip.hpp
	$(CC) $(CF) -c app/handlers.cpp -o $(BUILD_DIR)/handlers.o

$(BUILD_DIR)/main.o: app/main.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp app/Utrip.hpp
	$(CC) $(CF) -c app/main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/Hotel.o: app/Hotel.cpp app/Hotel.hpp app/StructsAndDefines.hpp app/Room.hpp app/User.hpp 
	$(CC) $(CF) -c app/Hotel.cpp -o $(BUILD_DIR)/Hotel.o

$(BUILD_DIR)/User.o: app/User.cpp app/User.hpp app/Filter.hpp app/Hotel.hpp 
	$(CC) $(CF) -c app/User.cpp -o $(BUILD_DIR)/User.o

$(BUILD_DIR)/Utrip.o: app/Utrip.cpp app/Utrip.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp app/User.hpp app/Hotel.hpp app/CSVReader.hpp
	$(CC) $(CF) -c app/Utrip.cpp -o $(BUILD_DIR)/Utrip.o

$(BUILD_DIR)/Filter.o: app/Filter.cpp app/Filter.hpp app/Hotel.hpp 
	$(CC) $(CF) -c app/Filter.cpp -o $(BUILD_DIR)/Filter.o

$(BUILD_DIR)/Room.o: app/Room.cpp app/Room.hpp app/StructsAndDefines.hpp
	$(CC) $(CF) -c app/Room.cpp -o $(BUILD_DIR)/Room.o

$(BUILD_DIR)/CSVReader.o: app/CSVReader.cpp app/CSVReader.hpp app/Hotel.hpp 
	$(CC) $(CF) -c app/CSVReader.cpp -o $(BUILD_DIR)/CSVReader.o

utrip.out: $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/Utrip.o $(BUILD_DIR)/Hotel.o $(BUILD_DIR)/User.o $(BUILD_DIR)/Filter.o $(BUILD_DIR)/Room.o $(BUILD_DIR)/CSVReader.o 
	$(CC) $(CF) $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/Utrip.o $(BUILD_DIR)/Hotel.o $(BUILD_DIR)/User.o $(BUILD_DIR)/Filter.o $(BUILD_DIR)/Room.o  $(BUILD_DIR)/CSVReader.o -o utrip.out

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out &> /dev/null
