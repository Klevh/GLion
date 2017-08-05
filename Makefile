#!/bin/makefile

#change this variable to match the path from the current directory to where GLion is store (without the last '/')
GLIONPATH=GLion

#------------------------------------------------------------------------------
#in this part, nothing for you to be done, it is the inclusion of GLion's files and LDFLAGS
#GLion's files
GLion=$(GLionPATH)/GLion.o
#GLion's LDFLAGS
LDFLAGS=-lGL -lGLEW -lglfw
#added because .o files are made in your directory
OGLion=GLion.o 
#------------------------------------------------------------------------------

#add to this variables all the '.o' files for your program
OFILES=

#add the LDFLAGS you need (such as -g or -O)
LDFLAGS+=-g

#your compilation flags, do not put ansi or -std=c89
CFLAGS=-Wall -Wextra -pedantic

#your program's name
EXEC=

#your compiler
CC=gcc


all:$(EXEC)

$(EXEC):$(OFILES) $(GLion)
	$(CC) $(OFILES) $(OGLion) -o $(EXEC) $(LDFLAGS) $(DEBUG)

%.o:%.c
	$(CC) -c $< $(CFLAGS)

clear:
	rm *.o

clean: clear

cleaner:
	rm *.o $(EXEC)
