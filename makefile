CC = gcc
CFLAGS = -lncurses -Wall -Wextra -pedantic -O2 -lm -I./include/
SOURCES = ./src/*.c 

all: dungeon run clean 

dungeon: 
			$(CC) $(SOURCES) $(CFLAGS) -o dungeon

run:
		./dungeon

clean:
		rm dungeon
