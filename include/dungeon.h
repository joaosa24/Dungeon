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
    char classe[20];
    bool walkable;
} Inimigo;

//vision.c functions
int is_visible(Entidade* player, Posicao pos);
int is_enemy_visible(Entidade* player, Inimigo * inimigo);

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
Posicao setupMapi(Terreno **map);

// player.c functions
Entidade *createPlayer(Posicao pos_inicial);
void handleInput(int input);
void movePlayer(Posicao newPos, Inimigo* inimigo);
Inimigo *createInimigo(Posicao pos_inicial);
int distance_inimigo(Entidade *player, Inimigo *inimigo);
void damage(Inimigo* inimigo, Entidade* player);

// variaveis externas
extern const int MAP_HEIGHT;
extern const int MAP_WIDTH;
extern Entidade *player;
extern Terreno **map;
extern Inimigo *inimigo;
extern Posicao pos_inicial;
extern Posicao pos_inicial_i;

#endif
