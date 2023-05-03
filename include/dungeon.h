#ifndef DUNGEON_H
#define DUNGEON_H

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

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
    Posicao pos;
    char ch;
    int vida;
} Entidade;

typedef struct {
    Entidade ent;
    bool eJogador;
    char classe[20];
} Inimigo;

//vision.c functions
int is_visible(Entidade* player, Posicao pos);

// draw.c functions
void drawMapa(void);
void drawEntidade(Entidade *entidade);
void drawAll(void);

// engine.c functions
void cursesSetup(void);
void gameLoop(void);
void closeGame(void);

// map.c functions
Terreno **generate_map(void);
void FreeMapa(Terreno **map);
Posicao setupMap(Terreno **map);

// player.c functions
Entidade *createPlayer(Posicao pos_inicial);
void handleInput(int input);
void movePlayer(Posicao newPos);
Inimigo *createInimigo(Posicao pos_inicial);

// variaveis externas
extern const int MAP_HEIGHT;
extern const int MAP_WIDTH;
extern Entidade *player;
extern Terreno **map;
extern Inimigo *inimigo;
extern Posicao pos_inicial;

#endif
