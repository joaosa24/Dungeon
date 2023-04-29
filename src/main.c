#include <stdio.h>
#include <dungeon.h>

const int MAP_HEIGHT = 25;
const int MAP_WIDTH = 100;

Entidade *player;
Inimigo *inimigo;
Terreno **map;

int main(void)
{
    Posicao pos_inicial;
    cursesSetup();
    srand(time(NULL));

    map = createMapa();
    pos_inicial = setupMap();
    player = createPlayer(pos_inicial);
    inimigo = createInimigo(pos_inicial);

    gameLoop();

    closeGame();
    return 0;
}