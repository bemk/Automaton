
CPP=g++
CC=gcc
ECFLAGS:=-g
CFLAGS:=$(ECFLAGS)
CXXFLAGS:=$(ECFLAGS)

CXXFILES := $(wildcard src/*.cpp)
CFILES := $(wildcard src/*.c)

OBJ_FILES := $(addprefix src/,$(notdir $(CXXFILES:.cpp=.o)))
COBJ_FILES := $(addprefix src/,$(notdir $(CFILES:.c=.o)))

LEXER_FILES := $(wildcard src/lexer/*.cpp)
LEXER_OBJ_FILES := $(addprefix src/lexer/,$(notdir $(LEXER_FILES:.cpp=.o)))

NFA_FILES := $(wildcard src/NFA/*.cpp)
NFA_OBJ_FILES := $(addprefix src/NFA/,$(notdir $(NFA_FILES:.cpp=.o)))

DFA_FILES := $(wildcard src/DFA/*.cpp)
DFA_OBJ_FILES := $(addprefix src/DFA/,$(notdir $(DFA_FILES:.cpp=.o)))

TARGETS := $(OBJ_FILES) $(COBJ_FILES) $(LEXER_OBJ_FILES) $(NFA_OBJ_FILES) $(DFA_OBJ_FILES) 

.PHONY: all clean test

all: $(TARGETS)
	$(CXX) -o automaton $(TARGETS) $(CXXFLAGS)

clean:
	rm -fv $(TARGETS) automaton
	rm -fv *.dot
	rm -fv *.png
	rm -fv *.svg
	rm -rfv doc/*

png: all
	./automaton -d 8 -r "ca+a(bb|((cc|f.f)*|ee))d?d" -g parsetree.dot -n nfa.dot -o dfa.dot $(AUTOFLAGS)
	dot -Tpng parsetree.dot -o parsetree.png
	dot -Tpng nfa.dot -o nfa.png
	dot -Tpng dfa.dot -o dfa.png
	eog *.png

svg: all
	./automaton -d 8 -r "ca+a(bb|((cc|f.f)*|ee))d?d" -g parsetree.dot -n nfa.dot -o dfa.dot $(AUTOFLAGS)
	dot -Tsvg parsetree.dot -o parsetree.svg
	dot -Tsvg nfa.dot -o nfa.svg
	dot -Tsvg dfa.dot -o dfa.svg
	eog *.svg


doxygen:
	mkdir -p doc/
	doxygen

