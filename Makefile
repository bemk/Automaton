
CPP=g++
CPP_FLAGS:=

CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix src/,$(notdir $(CPP_FILES:.cpp=.o)))

.PHONY: all clean
all: $(OBJ_FILES)
	$(CPP) -o automaton $(OBJ_FILES)

clean:
	rm -fv `find -name *.o` automaton
