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
    if((newPos.y == inimigo->ent.pos.y) && (newPos.x == inimigo->ent.pos.x)) return 0;

    return 1;
}

void movePlayer(Posicao newPos, Inimigo* inimigo) {
    if (map[newPos.y][newPos.x].walkable && enemy_pos(newPos, inimigo)) {
        player->pos.y = newPos.y;
        player->pos.x = newPos.x;
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

void damage(Inimigo* inimigo, Entidade* player) {
    if(distance_inimigo(player, inimigo) == 1) {
        player->vida -= 5;
    }
}