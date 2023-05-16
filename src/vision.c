#include <dungeon.h>

int is_visible(Entidade* player, Posicao pos) {
    int dx = abs(pos.x - player->pos.x);
    int dy = abs(pos.y - player->pos.y);
    int distance = sqrt(pow(dx, 2) + pow(dy, 2));

    if (distance <= 100) {
        return 1;
    }
return 0;
}

int is_enemy_visible(Entidade* player, Inimigo * inimigo) {
    int dx = abs(inimigo->ent.pos.x - player->pos.x);
    int dy = abs(inimigo->ent.pos.y - player->pos.y);
    int distance = sqrt(pow(dx, 2) + pow(dy, 2));

    if (distance <= 100) {
        return 1;
    }
return 0;
}



