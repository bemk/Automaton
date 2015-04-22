
CPP=g++
INCLUDE=include/

SOURCES=src/main.o src/Automaton.o


.PHONY: all clean
all: $(SOURCES)
	$(CPP) -o automaton $(SOURCES)

clean:
	rm -fv `find -name *.o` automaton
