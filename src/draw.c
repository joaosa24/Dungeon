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

void drawHUD() {
    attron(A_BOLD);
    mvprintw(56, 1, "Health : %d", player->vida);
    attroff(A_BOLD);
    refresh();
}

void drawEntidade(Entidade *entidade)
{
    mvaddch(entidade->pos.y, entidade->pos.x, entidade->ch);
}

void drawInimigo(Inimigo *inimigo)
{
        for (int i = 0; i < MAP_HEIGHT ; i++)
    {
        for (int j = 0; j < MAP_WIDTH ; j++)
        {
        if (is_enemy_visible(player, inimigo)) {
            attron(A_BOLD);
            mvaddch(inimigo->ent.pos.y, inimigo->ent.pos.x, inimigo->ent.ch);
            attroff(A_BOLD);
        }
    }
}
}
void drawAll(void)
{
    clear();
    refresh();
    drawMapa();
    drawHUD();
    drawEntidade(player);
    drawInimigo(inimigo);
}