#include <dungeon.h>

void drawMapa(void)
{
    for (int i = 0; i < MAP_HEIGHT ; i++)
    {
        for (int j = 0; j < MAP_WIDTH ; j++)
        {
        Posicao pos = {i,j};
        if (is_visible(player, pos)) {

            mvaddch(i, j, map[i][j].ch);

        } else {

            mvaddch(i, j, ' ');
            }
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
    refresh();
    drawMapa();
    drawEntidade(player);
}