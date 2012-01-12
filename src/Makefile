OBJS = Object.o SpatialHash.o Bullet.o Entity.o Enemy.o Player.o Main.o 
CC = g++
#DEBUG = -g
DEBUG = 
CFLAGS = -Wall -c $(DEBUG) -L$(SFML_LIB_DIR) -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -I$(SFML_INC_DIR) -I../include
LFLAGS = -Wall $(DEBUG) -L$(SFML_LIB_DIR) -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -I$(SFML_INC_DIR) -I../include

SHELL = /bin/sh

.SUFFIXES: 
.SUFFIXES: .cpp .h .o

zombie.bin : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o zombie.bin

Object.o : Object.cpp 
	$(CC) $(CFLAGS) Object.cpp

SpatialHash.o : SpatialHash.cpp 
	$(CC) $(CFLAGS) SpatialHash.cpp

Bullet.o : Bullet.cpp 
	$(CC) $(CFLAGS) Bullet.cpp

Entity.o : Entity.cpp 
	$(CC) $(CFLAGS) Entity.cpp

Enemy.o : Enemy.cpp 
	$(CC) $(CFLAGS) Enemy.cpp

Player.o : Player.cpp 
	$(CC) $(CFLAGS) Player.cpp

Main.o : Main.cpp 
	$(CC) $(CFLAGS) Main.cpp

clean:
	rm -f *.o *.bin
