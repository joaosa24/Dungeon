#include <dungeon.h>

void drawMapa(void)
{
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            mvaddch(y, x, map[y][x].ch);
        }
    }
}

void drawEntidade(Entidade *entidade)
{
    mvaddch(entidade->pos.y, entidade->pos.x, entidade->ch);
}

void drawAll(void)
{
    clear();
    drawMapa();
    drawEntidade(player);
}