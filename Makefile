
CPP=g++
CC=gcc
ECFLAGS:=-g
CFLAGS:=$(ECFLAGS)
CXXFLAGS:=$(ECFLAGS)

CXXFILES := $(wildcard src/*.cpp)
CFILES := $(wildcard src/*.c)

OBJ_FILES := $(addprefix src/,$(notdir $(CXXFILES:.cpp=.o)))
COBJ_FILES := $(addprefix src/,$(notdir $(CFILES:.c=.o)))

LEXERFILES := $(wildcard src/lexer/*.cpp)
LEXER_OBJ_FILES := $(addprefix src/lexer/,$(notdir $(LEXERFILES:.cpp=.o)))

NFA_FILES := $(wildcard src/NFA/*.cpp)
NFA_OBJ_FILES := $(addprefix src/NFA/,$(notdir $(NFA_FILES:.cpp=.o)))

TARGETS := $(OBJ_FILES) $(COBJ_FILES) $(LEXER_OBJ_FILES) $(NFA_OBJ_FILES)

.PHONY: all clean test

all: $(TARGETS)
	$(CPP) -o automaton $(TARGETS) $(CXXFLAGS)

clean:
	rm -fv $(TARGETS) automaton
	rm -fv *.dot
	rm -fv *.png

png: all
	./automaton -d 2 -r "ca+a(bb|((cc|f.f)*|ee))d?d" -g dot.dot $(AUTOFLAGS)
	dot -Tpng dot.dot -o dot.png
