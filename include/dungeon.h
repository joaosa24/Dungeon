#ifndef DUNGEON_H
#define DUNGEON_H

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
    int y;
    int x;
} Posicao;

typedef struct
{
    char ch;
    bool walkable;
} Terreno;

typedef struct
{
    int height;
    int width;
    Posicao pos;
    Posicao centro;
} Sala;

typedef struct
{
    Posicao pos;
    char ch;
} Entidade;

typedef struct {
    Entidade ent;
    bool eJogador;
    char classe[20];
} Inimigo;

// draw.c functions
void drawMapa(void);
void drawEntidade(Entidade *entidade);
void drawAll(void);

// engine.c functions
void cursesSetup(void);
void gameLoop(void);
void closeGame(void);

// map.c functions
Terreno **createMapa(void);
void freeMapa(void);
Posicao setupMap(void);

// player.c functions
Entidade *createPlayer(Posicao pos_inicial);
void handleInput(int input);
void movePlayer(Posicao newPos);
Inimigo *createInimigo(Posicao pos_inicial);

// room.c functions
Sala createSala(int y, int x, int height, int width);
void addSalaToMap(Sala sala);
void conectSalas(Posicao centro1, Posicao centro2);

// variaveis externas
extern const int MAP_HEIGHT;
extern const int MAP_WIDTH;
extern Entidade *player;
extern Terreno **map;
extern Inimigo *inimigo;

#endif
