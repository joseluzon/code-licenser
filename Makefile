CXX		  := g++-8
CXX_FLAGS := -Wall -Wextra -std=c++17

BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib

LIBRARIES	:= -lstdc++fs
EXECUTABLE	:= code-licenser
EXECUTABLE_DBG	:= code-licenser.dbg
ARGS		:= /path-to-code license-header.txt "//" "c|cpp|h|hpp"


all: $(BIN)/$(EXECUTABLE)

debug: $(BIN)/$(EXECUTABLE_DBG)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE) $(ARGS)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

$(BIN)/$(EXECUTABLE_DBG): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -ggdb -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/*
