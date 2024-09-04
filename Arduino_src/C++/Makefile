CXX = g++
CFLAGS = -g -Wall

BLD_DIR = build/

default: all

# Ensure the build directory exists
$(BLD_DIR):
	mkdir -p $(BLD_DIR)

all: $(BLD_DIR)main

$(BLD_DIR)main: $(BLD_DIR)main.o $(BLD_DIR)SerialHandler.o $(BLD_DIR)Packet.o
	$(CXX) $(CFLAGS) $^ -o $@

$(BLD_DIR)main.o: main.cpp SerialHandler.h Packet.h | $(BLD_DIR)
	$(CXX) $(CFLAGS) -c main.cpp -o $@

$(BLD_DIR)SerialHandler.o: SerialHandler.cpp SerialHandler.h Packet.h | $(BLD_DIR)
	$(CXX) $(CFLAGS) -c SerialHandler.cpp -o $@

$(BLD_DIR)Packet.o: Packet.cpp Packet.h | $(BLD_DIR)
	$(CXX) $(CFLAGS) -c Packet.cpp -o $@

.PHONY: run clean

run: $(BLD_DIR)main
	./$(BLD_DIR)main

clean:
	rm -rf $(BLD_DIR)
