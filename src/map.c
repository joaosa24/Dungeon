#include <dungeon.h>

Terreno **createMapa(void)
{
    Terreno **tiles = calloc(MAP_HEIGHT, sizeof(Terreno *));

    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        tiles[y] = calloc(MAP_WIDTH, sizeof(Terreno));
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            tiles[y][x].ch = '#';
            tiles[y][x].walkable = false;
        }
    }
    return tiles;
}

Posicao setupMap(void)
{
    int y, x, height, width, n_salas;
    n_salas = (rand() % 11) + 5;
    Sala *salas = calloc(n_salas, sizeof(Sala));
    Posicao pos_inicial;

    for (int i = 0; i < n_salas; i++)
    {
        y = (rand() % (MAP_HEIGHT - 10)) + 1;
        x = (rand() % (MAP_WIDTH - 20)) + 1;
        height = (rand() % 7) + 3;
        width = (rand() % 15) + 5;
        salas[i] = createSala(y, x, height, width);
        addSalaToMap(salas[i]);

        if (i > 0)
        {
            conectSalas(salas[i - 1].centro, salas[i].centro);
        }
    }

    pos_inicial.y = salas[0].centro.y;
    pos_inicial.x = salas[0].centro.x;

    return pos_inicial;
}

void freeMapa(void)
{
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        free(map[y]);
    }
    free(map);
}
