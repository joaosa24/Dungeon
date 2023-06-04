#ifndef DUNGEON_H
#define DUNGEON_H

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <unistd.h>


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
    int gold;
} Entidade;

typedef struct
{
    Entidade ent;
} Inimigo;

// vision.c functions
int is_visible(Entidade *player, Posicao pos);
int is_enemy_visible(Entidade *player, Inimigo *inimigo);
int vision_range(Entidade *player);

// draw.c functions
void drawMapa(Entidade *player,int MAP_HEIGHT, int MAP_WIDTH,Terreno **map,int dungeon_level);
void drawPlayer(Entidade *player);
void drawDicaBoss(Inimigo *inimigo,int MAP_HEIGHT,int dungeon_level);
void drawDica(Entidade *player,int MAP_HEIGHT,Posicao pos_lvl);
void drawHUD(Entidade *player,int MAP_HEIGHT, int MAP_WIDTH,int dungeon_level);
void drawInimigo(Entidade *player, Inimigo *inimigo);
void drawLvlEntry(Entidade *player, Posicao pos_lvl);
int drawMenuMorte(int choice,int MAP_HEIGHT, int MAP_WIDTH);
void drawObjDamage(Entidade *player, Posicao *pos_damage);
void drawtraps(Entidade *player, Posicao *pos_traps);
void drawHealFruit(Entidade *player, Posicao *pos_fruit);
void drawTreasure(Entidade *player, Inimigo *inimigo,int dungeon_level);
void drawMysteryBox(Entidade *player,int dungeon_level);
void drawBossHealth(Inimigo *inimigo,int MAP_HEIGHT,int dungeon_level);
void drawAll(Entidade *player, Inimigo *inimigo,int MAP_HEIGHT, int MAP_WIDTH,Terreno **map,Posicao pos_lvl,Posicao *pos_damage,Posicao *pos_traps,Posicao *pos_fruit,int dungeon_level);

// engine.c functions
void cursesSetup(int MAP_HEIGHT, int MAP_WIDTH);
void gameLoop(Entidade *player, Inimigo *inimigo,int MAP_HEIGHT, int MAP_WIDTH,Terreno **map,Posicao pos_inicial,Posicao pos_inicial_i,Posicao pos_lvl,Posicao *pos_damage,Posicao *pos_traps,Posicao *pos_fruit,int dungeon_level);
void closeGame(Entidade *player, Inimigo *inimigo,int MAP_HEIGHT,Terreno **map,Posicao *pos_damage,Posicao *pos_traps,Posicao *pos_fruit);

// map.c functions
Terreno **generate_map(int MAP_HEIGHT, int MAP_WIDTH);
void FreeMapa(Terreno **map,int MAP_HEIGHT);
Posicao setupMap(Terreno **map,int MAP_HEIGHT, int MAP_WIDTH);
Posicao setupMapi(Terreno **map,int MAP_HEIGHT, int MAP_WIDTH,Posicao pos_inicial);
Posicao level_entry(Terreno **map,int MAP_HEIGHT,int MAP_WIDTH,Posicao pos_inicial,Posicao pos_inicial_i);
int next_level(Entidade *player, int input,Posicao pos_lvl);
Posicao *plus_damage_obj(Terreno **map,int MAP_HEIGHT,int MAP_WIDTH,Posicao pos_inicial,Posicao pos_inicial_i,Posicao pos_lvl);
Posicao *traps(Terreno **map,int MAP_HEIGHT,int MAP_WIDTH,Posicao pos_inicial,Posicao pos_inicial_i,Posicao pos_lvl, int dungeon_level);
Posicao *fruits(Terreno **map,int MAP_HEIGHT,int MAP_WIDTH,Posicao pos_inicial,Posicao pos_inicial_i,Posicao pos_lvl);
Posicao treasure(Terreno **map,int MAP_HEIGHT,int MAP_WIDTH,Posicao pos_inicial,Posicao pos_inicial_i,Posicao pos_lvl);
Posicao mystery(Terreno **map,int MAP_HEIGHT,int MAP_WIDTH,Posicao pos_inicial,Posicao pos_inicial_i,Posicao pos_lvl);
int distance(Posicao pos1, Posicao pos2);

// player.c functions
Entidade *createPlayer(Posicao pos_inicial);
void handleInput(Entidade *player, Inimigo *inimigo, int input,int MAP_HEIGHT,int MAP_WIDTH,Terreno **map);
void movePlayer(Posicao newPos, Entidade *player, Inimigo *inimigo,int MAP_HEIGHT,int MAP_WIDTH,Terreno **map);
Inimigo *createInimigo(Posicao pos_inicial,int dungeon_level);
int distance_inimigo(Entidade *player, Inimigo *inimigo);
void damage(Inimigo *inimigo, Entidade *player);
int enemy_pos(Posicao newPos, Inimigo *inimigo);
void moveInimigo(Inimigo *inimigo, Entidade *player, Terreno **map);
void heal(Inimigo *inimigo, Entidade *player, int input,int dungeon_level);
void respawn(Entidade *player,Inimigo *inimigo,int MAP_HEIGHT,int MAP_WIDTH,Terreno **map);
void plus_damage(Entidade *player, int input,int MAP_HEIGHT,Posicao *pos_damage);
int dica(Entidade *player, int input);
int distancia_portal(Entidade *player, Posicao entrada);
int pickaxe(Entidade *player, int input);
void traps_damage(Entidade *player,Posicao *pos_traps);
void fruits_heal(Entidade *player, int input,int MAP_HEIGHT,Posicao *pos_fruit);
void treasure_loot(Entidade *player, int input);
void mystery_loot(Entidade *player, int input,int MAP_HEIGHT);

// variaveis externas
extern Posicao pos_mystery;
extern Posicao pos_treasure; // ao remover de variavel global, não apagava pois não estava a receber um pointer!
extern int damage_buff;
extern int trigger; // nao consigo tirar trigger de variavel global pois tenho um warning quando apenas faço trigger = 5 na função
extern int vida_atual_inimigo;
extern int has_pickaxe;
extern int flag_boss;
extern WINDOW *win;

#endif