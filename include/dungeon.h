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
    int damage;
} Entidade;

typedef struct
{
    Entidade ent;
} Inimigo;

// vision.c functions
int is_visible(Entidade *player, Posicao pos);
int is_enemy_visible(Entidade *player, Inimigo *inimigo);

// draw.c functions
void drawMapa(void);
void drawEntidade(Entidade *entidade);
void drawAll(void);
int drawMenuMorte(int choice);

// engine.c functions
void cursesSetup(void);
void gameLoop(void);
void closeGame(void);

// map.c functions
Terreno **generate_map(void);
void FreeMapa(Terreno **map);
Posicao setupMap(Terreno **map);
Posicao setupMapi(Terreno **map);
Posicao level_entry(Terreno **map);
int next_level(Entidade *player, int trigger);

// player.c functions
Entidade *createPlayer(Posicao pos_inicial);
void handleInput(int input);
void movePlayer(Posicao newPos, Inimigo *inimigo);
Inimigo *createInimigo(Posicao pos_inicial);
int distance_inimigo(Entidade *player, Inimigo *inimigo);
void damage(Inimigo *inimigo, Entidade *player);
int enemy_pos(Posicao newPos, Inimigo *inimigo);
void moveInimigo(Inimigo *inimigo, Entidade *player, Terreno **map);
void heal(Inimigo *inimigo, Entidade *player, int trigger);
void respawn(Inimigo *inimigo);

// variaveis externas
extern int MAP_HEIGHT;
extern int MAP_WIDTH;
extern Entidade *player;
extern Terreno **map;
extern Inimigo *inimigo;
extern Posicao pos_inicial;
extern Posicao pos_inicial_i;
extern Posicao pos_lvl;
extern int dungeon_level;
extern int vida_atual_inimigo;
extern WINDOW *win;

#endif