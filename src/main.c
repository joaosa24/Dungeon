#include <stdio.h>
#include <dungeon.h>

const int MAP_HEIGHT = 57;
const int MAP_WIDTH = 238;

Entidade *player;
Inimigo *inimigo;
Terreno **map;

int main(void)
{
    Posicao pos_inicial;
    cursesSetup();
    srand(time(NULL));

    map = generate_map();
    pos_inicial = setupMap(map);
    player = createPlayer(pos_inicial);
    inimigo = createInimigo(pos_inicial);

    gameLoop();
    
    FreeMapa(map);

    closeGame();
    return 0;
}