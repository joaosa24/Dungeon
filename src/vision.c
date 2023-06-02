#include <dungeon.h>

int vision_range(Entidade * player) // função responsável por determinar o "range" da visão do jogador, consoante a vida do mesmo
{
    if (player->vida >= 70)
    {
        return 8;
    }
    else if (player->vida >= 35)
    {
        return 6;
    }
    else if (player->vida >= 20)
    {
        return 4;
    }
    else return 2;
    
}

int is_visible(Entidade *player, Posicao pos) // função que serve de parâmetro para desenho do mapa
{
    int range = vision_range(player);
    int dx = abs(pos.x - player->pos.x);
    int dy = abs(pos.y - player->pos.y);
    int distance = sqrt(pow(dx, 2) + pow(dy, 2));

    if (distance <= 200)
    {
        return 1;
    }
    return 0;
}

int is_enemy_visible(Entidade *player, Inimigo *inimigo) // função que serve de parâmetro para desenho do inimigo
{
    int range = vision_range(player);
    int dx = abs(inimigo->ent.pos.x - player->pos.x);
    int dy = abs(inimigo->ent.pos.y - player->pos.y);
    int distance = sqrt(pow(dx, 2) + pow(dy, 2));

    if (distance <= 200)
    {
        return 1;
    }
    return 0;
}
