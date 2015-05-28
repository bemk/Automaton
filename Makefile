
CPP=g++
CC=gcc
CFLAGS:=-g
CXXFLAGS:=$(CFLAGS)

CXXFILES := $(wildcard src/*.cpp)
CFILES := $(wildcard src/*.c)

OBJ_FILES := $(addprefix src/,$(notdir $(CXXFILES:.cpp=.o)))
COBJ_FILES := $(addprefix src/,$(notdir $(CFILES:.c=.o)))

LEXERFILES := $(wildcard src/lexer/*.cpp)
LEXER_OBJ_FILES := $(addprefix src/lexer/,$(notdir $(LEXERFILES:.cpp=.o)))

.PHONY: all clean test

all: $(OBJ_FILES) $(COBJ_FILES) $(LEXER_OBJ_FILES)
	$(CPP) -o automaton $(OBJ_FILES) $(COBJ_FILES) $(LEXER_OBJ_FILES) \
	$(CXXFLAGS)

clean:
	rm -fv `find -name *.o` automaton
	rm -fv *.dot
	rm -fv *.png

png: all
	./automaton -d 2 -r "ca+a(bb|((cc|f.f)*|ee))d?d" -g dot.dot $(AUTOFLAGS)
	dot -Tpng dot.dot -o dot.png
