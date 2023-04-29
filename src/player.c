#include <dungeon.h>

Entidade *createPlayer(Posicao pos_inicial)
{
    Entidade *newPlayer = calloc(1, sizeof(Entidade));

    newPlayer->pos.y = pos_inicial.y;
    newPlayer->pos.x = pos_inicial.x;
    newPlayer->ch = '@';

    return newPlayer;
}

Inimigo *createInimigo(Posicao pos_inicial)
{
    Inimigo *newInimigo = calloc(1, sizeof(Inimigo));

    newInimigo->ent.pos.y = pos_inicial.y + 1;
    newInimigo->ent.pos.x = pos_inicial.x + 1;
    newInimigo->ent.ch = 'b';
    newInimigo->eJogador = false;

    return newInimigo;
}

void handleInput(int input)
{
    Posicao newPos = {player->pos.y, player->pos.x};
    switch (input)
    {
    case 'w': // cima
        newPos.y--;
        break;
    case 's': // baixo
        newPos.y++;
        break;
    case 'a': // esquerda
        newPos.x--;
        break;
    case 'd': // direita
        newPos.x++;
        break;
    default:
        break;
    }

    movePlayer(newPos);
}

void movePlayer(Posicao newPos)
{
    if (map[newPos.y][newPos.x].walkable)
    {
        player->pos.y = newPos.y;
        player->pos.x = newPos.x;
    }
}