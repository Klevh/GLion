#!/bin/makefile

SRC=$(wildcard *.c)  
EXE=a.out

CFLAGS+=-Wall -Wextra -g
LDFLAGS=-lGL -lGLEW -lglfw

OBJ=$(addprefix build/,$(SRC:.c=.o))
DEP=$(addprefix build/,$(SRC:.c=.d))

all: $(OBJ)
  $(CXX) -o $(EXE) $^ $(LDFLAGS)

build/%.o: sources/%.c
  @mkdir -p build
  $(CXX) $(CFLAGS) -o $@ -c $<

clean:
  rm -rf build core *.gch

-include $(DEP)
