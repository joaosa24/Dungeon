CC = gcc
CFLAGS = -lncurses -I./include/
SOURCES = ./src/*.c 

all: dungeon run clean 

dungeon: 
			$(CC) $(SOURCES) $(CFLAGS) -o dungeon

run:
		./dungeon

clean:
		rm dungeon