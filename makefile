#
CC := gcc
CXX := g++

BUILD_PATH := build
OUTPUT := makeproj
O_ARGS :=
CCFLAGS :=
SRC := cr_make.cpp main.cpp
OBJ := $(SRC:%=$(BUILD_PATH)/%.o)

default: $(BUILD_PATH) $(OBJ)
	$(CXX) -o $(OUTPUT) $(OBJ) $(CCFLAGS)

$(BUILD_PATH):
	mkdir $(BUILD_PATH)

$(BUILD_PATH)/%.cpp.o: %.cpp
	$(CXX) -o $@ -c $< $(CCFLAGS)

clean: $(BUILD_PATH)
	-rm -r $(BUILD_PATH)/*
	-rm $(OUTPUT)

run: default
	./$(OUTPUT) $(args)

debug: $(BUILD_PATH) $(OBJ)
	$(CXX) -o $(OUTPUT) $(OBJ) $(CCFLAGS) -g

release: default
	sudo cp $(OUTPUT) /usr/bin/$(OUTPUT)
