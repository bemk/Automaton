
CPP=g++
CC=gcc
CFLAGS:=-g
CXXFLAGS:=$(CFLAGS)

CXXFILES := $(wildcard src/*.cpp) 
CFILES := $(wildcard src/*.c)
OBJ_FILES := $(addprefix src/,$(notdir $(CXXFILES:.cpp=.o)))
COBJ_FILES := $(addprefix src/,$(notdir $(CFILES:.c=.o)))

.PHONY: all clean test

all: $(OBJ_FILES) $(COBJ_FILES)
	$(CPP) -o automaton $(OBJ_FILES) $(COBJ_FILES) $(CXXFLAGS)

clean:
	rm -fv `find -name *.o` automaton
	rm -fv *.dot
	rm -fv *.png

png: all
	./automaton -d 2 -r "ca+a(bb|((c.c|ff)*|ee))d?d" -v -g dot.dot
	dot -Tpng dot.dot -o dot.png
