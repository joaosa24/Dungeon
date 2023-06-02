#include <dungeon.h>

Entidade *createPlayer(Posicao pos_inicial)
{
    Entidade *newPlayer = calloc(1, sizeof(Entidade));

    newPlayer->pos.y = pos_inicial.y;
    newPlayer->pos.x = pos_inicial.x;
    newPlayer->ch = '@';
    newPlayer->vida = 100;
    newPlayer->damage = 10;
    newPlayer->gold = 200;

    return newPlayer;
}

Inimigo *createInimigo(Posicao pos_inicial_i, int dungeon_level)
{
    Inimigo *newInimigo = calloc(1, sizeof(Inimigo));

    newInimigo->ent.pos.y = pos_inicial_i.y;
    newInimigo->ent.pos.x = pos_inicial_i.x;
    if (dungeon_level % 5 != 0)
    {
        newInimigo->ent.ch = 'b';
    }
    else
        newInimigo->ent.ch = 'B';

    newInimigo->ent.vida = vida_atual_inimigo;
    newInimigo->ent.damage = 5;

    return newInimigo;
}

void handleInput(Entidade *player, Inimigo *inimigo, int input, int MAP_HEIGHT, int MAP_WIDTH, Terreno **map)
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
    case '7':
        newPos.x--;
        newPos.y--;
        break;
    case '9':
        newPos.x++;
        newPos.y--;
        break;
    case '1':
        newPos.x--;
        newPos.y++;
        break;
    case '3':
        newPos.x++;
        newPos.y++;
        break;
    case '8':
        newPos.y--;
        break;
    case '2':
        newPos.y++;
        break;
    case '4':
        newPos.x--;
        break;
    case '6':
        newPos.x++;
        break;
    default:
        break;
    }

    movePlayer(newPos, player, inimigo, MAP_HEIGHT, MAP_WIDTH, map);
}

int enemy_pos(Posicao newPos, Inimigo *inimigo)
{
    if ((newPos.y == inimigo->ent.pos.y) && (newPos.x == inimigo->ent.pos.x) && (inimigo->ent.vida > 0))
        return 0;

    return 1;
}

void movePlayer(Posicao newPos, Entidade *player, Inimigo *inimigo, int MAP_HEIGHT, int MAP_WIDTH, Terreno **map)
{
    if (map[newPos.y][newPos.x].walkable && enemy_pos(newPos, inimigo))
    {
        player->pos.y = newPos.y;
        player->pos.x = newPos.x;
    }
    else if (!(enemy_pos(newPos, inimigo)))
    {
        inimigo->ent.vida -= player->damage;
    }
    else if (((newPos.y == MAP_HEIGHT - 2) || (newPos.y == 1) || (newPos.x == MAP_WIDTH - 2) || (newPos.x == 1)) && has_pickaxe > 0) // caso em que o jogador tenta minerar o bound do mapa 
    {
        trigger = 14;
    }
    else if (!(map[newPos.y][newPos.x].walkable) && enemy_pos(newPos, inimigo) && has_pickaxe != 0 && ((newPos.y != MAP_HEIGHT - 2) && (newPos.y != 1) && (newPos.x != MAP_WIDTH - 2) && (newPos.x != 1)))
    {
        map[newPos.y][newPos.x].walkable = true;
        map[newPos.y][newPos.x].ch = '.';
        has_pickaxe--;
    }
}

int distance_inimigo(Entidade *player, Inimigo *inimigo)
{
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
    int next_x = inimigo->ent.pos.x;
    int next_y = inimigo->ent.pos.y;

    if (inimigo->ent.vida <= 0)
    {
        map[inimigo->ent.pos.y][inimigo->ent.pos.x].walkable = true;
        return;
    }

    if (distance_inimigo(player, inimigo) < 350 && distance_inimigo(player, inimigo) >= 5)
    {

        if (abs(difx) > abs(dify))
        {
            if (difx > 0)
            {
                if (next_x + 1 != player->pos.x && map[next_y][next_x + 1].walkable)
                {
                    next_x++;
                }
                else if (dify > 0 && next_y + 1 != player->pos.y && map[next_y + 1][next_x].walkable)
                {
                    next_y++;
                }
                else if (dify < 0 && next_y - 1 != player->pos.y && map[next_y - 1][next_x].walkable)
                {
                    next_y--;
                }
            }
            else
            {
                if (next_x - 1 != player->pos.x && map[next_y][next_x - 1].walkable)
                {
                    next_x--;
                }
                else if (dify > 0 && next_y + 1 != player->pos.y && map[next_y + 1][next_x].walkable)
                {
                    next_y++;
                }
                else if (dify < 0 && next_y - 1 != player->pos.y && map[next_y - 1][next_x].walkable)
                {
                    next_y--;
                }
            }
        }
        else
        {
            if (dify > 0)
            {
                if (next_y + 1 != player->pos.y && map[next_y + 1][next_x].walkable)
                {
                    next_y++;
                }
                else if (difx > 0 && next_x + 1 != player->pos.x && map[next_y][next_x + 1].walkable)
                {
                    next_x++;
                }
                else if (difx < 0 && next_x - 1 != player->pos.x && map[next_y][next_x - 1].walkable)
                {
                    next_x--;
                }
            }
            else
            {
                if (next_y - 1 != player->pos.y && map[next_y - 1][next_x].walkable)
                {
                    next_y--;
                }
                else if (difx > 0 && next_x + 1 != player->pos.x && map[next_y][next_x + 1].walkable)
                {
                    next_x++;
                }
                else if (difx < 0 && next_x - 1 != player->pos.x && map[next_y][next_x - 1].walkable)
                {
                    next_x--;
                }
            }
        }

        inimigo->ent.pos.x = next_x;
        inimigo->ent.pos.y = next_y;
    }
    else if (distance_inimigo(player, inimigo) <= 5)
    {

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

void damage(Inimigo *inimigo, Entidade *player)
{
    if ((inimigo->ent.vida > 0) && (distance_inimigo(player, inimigo) == 1))
    {
        player->vida -= inimigo->ent.damage;
    }
}

void heal(Inimigo *inimigo, Entidade *player, int input, int dungeon_level)
{
    if ((inimigo->ent.vida <= 0) && (inimigo->ent.vida % 2 == 0) && (distance_inimigo(player, inimigo) == 0) && input == 'e')
    {
        if (dungeon_level % 5 == 0)
        {
            if (player->vida + 40 > 150)
            {
                player->vida = 150;
                player->gold += 80;
                inimigo->ent.vida--;
            }
            else
            {
                player->vida += 40;
                player->gold += 80;
                inimigo->ent.vida--;
            }
        }
        else if (player->vida + 25 > 150) // Repetimos o caso em cima para funcionar tanto nos bosses como nos minions (rewards sao piores)
        {
            player->vida = 150;
            player->gold += 20;
            inimigo->ent.vida--;
        }
        else
        {
            player->vida += 25;
            player->gold += 20;
            inimigo->ent.vida--;
        }
        trigger = 13;
    }
}

void respawn(Entidade *player, Inimigo *inimigo, int MAP_HEIGHT, int MAP_WIDTH, Terreno **map)
{
    if (((inimigo->ent.vida <= 0) && distance_inimigo(player, inimigo) > 8))
    {
        do
        {
            inimigo->ent.vida = vida_atual_inimigo;
            inimigo->ent.pos.x = rand() % MAP_WIDTH;
            inimigo->ent.pos.y = rand() % MAP_HEIGHT;
        } while (map[inimigo->ent.pos.y][inimigo->ent.pos.x].walkable == false || (distance_inimigo(player, inimigo) < 8));
    }
}

int dica(Entidade *player, int input)
{
    if (player->gold >= 50)
    {
        if (input == 'h')
        {
            if (player->gold == 50)
            {
                player->gold = 0;
            }
            else
                player->gold -= 50;
            return 1;
        }
    }
    // Retorno padrão caso nenhuma das condições seja atendida
    return 0;
}

int pickaxe(Entidade *player, int input)
{
    if (player->gold >= 150)
    {
        if (input == 'p')
        {
            has_pickaxe += 5;
            if (player->gold == 150)
            {
                player->gold = 0;
            }
            else
                player->gold -= 150;
            return 1;
        }
    }
    // Retorno padrão caso nenhuma das condições seja atendida
    return 0;
}

int distancia_portal(Entidade *player, Posicao entrada)
{
    int dx = player->pos.x - entrada.x;
    if (dx > 0) // porta está à esquerda
    {
        return 1;
    }
    else
        return 0; // portal está à direita
}

void plus_damage(Entidade *player, int input, int MAP_HEIGHT, Posicao *pos_damage)
{
    int i;

    for (i = 0; i < 5; i++)
    {

        if ((player->pos.x == pos_damage[i].x && player->pos.y == pos_damage[i].y) && input == 'e')
        {
            player->damage += 10;
            pos_damage[i].x = 400;
            pos_damage[i].y = MAP_HEIGHT;
            damage_buff++;
            trigger = 3;
        }
    }
}

void fruits_heal(Entidade *player, int input, int MAP_HEIGHT, Posicao *pos_fruit)
{
    int i;

    for (i = 0; i < 3; i++)
    {

        if ((player->pos.x == pos_fruit[i].x && player->pos.y == pos_fruit[i].y) && input == 'e')
        {
            if (player->vida + 10 > 150)
            {
                player->vida = 150;
                pos_fruit[i].x = 500;
                pos_fruit[i].y = MAP_HEIGHT;
                trigger = 6;
            }
            else
            {
                player->vida += 10;
                pos_fruit[i].x = 500;
                pos_fruit[i].y = MAP_HEIGHT;
                trigger = 6;
            }
        }
    }
}

void traps_damage(Entidade *player, Posicao *pos_traps)
{
    int i;

    for (i = 0; i < flag_boss; i++)
    {

        if ((player->pos.x == pos_traps[i].x && player->pos.y == pos_traps[i].y))
        {
            player->vida -= 10;
            trigger = 4;
        }
    }
}

void treasure_loot(Entidade *player, int input, int MAP_HEIGHT)
{
    if ((player->pos.x == pos_treasure.x && player->pos.y == pos_treasure.y) && input == 'e')
    {
        player->gold += 250;
        player->damage += 20;
        pos_treasure.x = 600;
        pos_treasure.y = MAP_HEIGHT;
        trigger = 7;
    }
}

void mystery_loot(Entidade *player, int input, int MAP_HEIGHT)
{
    srand(time(NULL));
    static int flag = 0; // uso a static int pois assim quando a função for chamada da proxima vez o valor vai ser mantido
    int random = rand();
    if (player->pos.x == pos_mystery.x && player->pos.y == pos_mystery.y)
    {
        if (input == 'e')
            flag++;

        if (flag == 1)
        {
            trigger = 8;
        }
        else if (flag == 2)
        {
            if (random % 4 == 0)
            {
                player->gold += 150;
                player->damage += 20;
                trigger = 9;
            }
            else if (random % 4 == 1)
            {
                player->vida -= 20;
                if (player->gold - 40 <= 0)
                {
                    player->gold = 0;
                }
                else
                    player->gold -= 40;
                trigger = 10;
            }
            else if (random % 4 == 2)
            {
                has_pickaxe += 5;
                trigger = 11;
            }
            else
            {
                trigger = 12;
            }
            pos_mystery.x = 601;
            pos_mystery.y = MAP_HEIGHT;
            flag = 0;
        }
    }
}