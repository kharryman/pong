# Specify the compiler
CC=g++
LFLAGS =  -lX11 -lGLU -lGL -I/usr/X11R6/include -L/usr/X11R6/lib -pthread -lm

#This command will be called 
#when you run 'make'
all: pong

pong: game.o player.o
	$(CC) pong.cpp game.o player.o $(LFLAGS)  -o pong

#Each class will need its own 
#object file. For each class you create
#add it to the make file 
game.o: player.o game.h game.cpp
	$(CC) -c game.cpp player.o

player.o: player.h player.cpp
	$(CC) -c player.cpp

clean:
	rm -f pong
	rm -f *.o
