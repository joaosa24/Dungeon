#include <dungeon.h>

Entidade *createPlayer(Posicao pos_inicial) {
    Entidade *newPlayer = calloc(1, sizeof(Entidade));

    newPlayer->pos.y = pos_inicial.y;
    newPlayer->pos.x = pos_inicial.x;
    newPlayer->ch = '@';
    newPlayer->vida = 100;

    return newPlayer;
}

Inimigo *createInimigo(Posicao pos_inicial_i) {
    Inimigo *newInimigo = calloc(1, sizeof(Inimigo));

    newInimigo->ent.pos.y = pos_inicial_i.y ;
    newInimigo->ent.pos.x = pos_inicial_i.x ;
    newInimigo->ent.ch = 'b';
    newInimigo->ent.vida = 50;    
    newInimigo->walkable = false;

    return newInimigo;
}

void handleInput(int input) {
    Posicao newPos = {player->pos.y, player->pos.x};
    switch (input) {
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

    movePlayer(newPos, inimigo);
}

int enemy_pos(Posicao newPos, Inimigo* inimigo) {
    if((newPos.y == inimigo->ent.pos.y) && (newPos.x == inimigo->ent.pos.x) && (inimigo->ent.vida > 0)) return 0;

    return 1;
}

void movePlayer(Posicao newPos, Inimigo* inimigo) {
    if (map[newPos.y][newPos.x].walkable && enemy_pos(newPos, inimigo)) {
        player->pos.y = newPos.y;
        player->pos.x = newPos.x;
    } else    
    {
        inimigo->ent.vida -= 10;
    }
}

int distance_inimigo(Entidade *player, Inimigo *inimigo) {
    int x = player->pos.x;
    int y = player->pos.y;
    int ini_x = inimigo->ent.pos.x;
    int ini_y = inimigo->ent.pos.y;
    int distancia = sqrt(pow((x - ini_x), 2) + pow((y - ini_y), 2));

    return distancia;
}

void moveInimigo(Inimigo *inimigo, Entidade *player, Terreno **map)
{
    int difx = player->pos.x - inimigo->ent.pos.x;
    int dify = player->pos.y - inimigo->ent.pos.y;

    if (inimigo->ent.vida <= 0)
    {
        map[inimigo->ent.pos.y][inimigo->ent.pos.x].walkable = true;
        map[inimigo->ent.pos.y][inimigo->ent.pos.x].ch = '.';
        return;
    }
    if (distance_inimigo(player, inimigo) < 10)
    {
        int next_x = inimigo->ent.pos.x;
        int next_y = inimigo->ent.pos.y;

        if (abs(difx) > abs(dify))
        {
            if (difx > 0 && map[next_y][next_x + 1].walkable && next_x + 1 != player->pos.x)
            {
                next_x++;
            }
            else if (difx < 0 && map[next_y][next_x - 1].walkable && next_x - 1 != player->pos.x)
            {
                next_x--;
            }
        }
        else
        {
            if (dify > 0 && map[next_y + 1][next_x].walkable && next_y + 1 != player->pos.y)
            {
                next_y++;
            }
            else if (dify < 0 && map[next_y - 1][next_x].walkable && next_y - 1 != player->pos.y)
            {
                next_y--;
            }
        }

        inimigo->ent.pos.x = next_x;
        inimigo->ent.pos.y = next_y;
    }
}

void damage(Inimigo* inimigo, Entidade* player) {
    if((inimigo->ent.vida > 0) && (distance_inimigo(player, inimigo) == 1)) {
        player->vida -= 5;
    }
}