
CPP=g++
CC=gcc
CFLAGS:=
CPP_FLAGS:=$(CFLAGS)

CPP_FILES := $(wildcard src/*.cpp) 
CFILES := $(wildcard src/*.c)
OBJ_FILES := $(addprefix src/,$(notdir $(CPP_FILES:.cpp=.o)))
COBJ_FILES := $(addprefix src/,$(notdir $(CFILES:.c=.o)))

.PHONY: all clean
all: $(OBJ_FILES) $(COBJ_FILES)
	$(CPP) -o automaton $(OBJ_FILES) $(COBJ_FILES) $(CPP_FLAGS)

clean:
	rm -fv `find -name *.o` automaton
