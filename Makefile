# Specify the compiler
CC=g++
LL= -lGL -lglut

#This command will be called 
#when you run 'make'
all: pong

pong: game.o player.o
	$(CC) Pong.cpp game.o player.o  -framework OpenGL -framework GLUT -I/usr/local/include -lglfw3  -o pong 

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