#include <dungeon.h>

int WallCount(Terreno **map, int r, int col, int row, int MAP_HEIGHT, int MAP_WIDTH) // manecas
{
    int x, y;
    int wall_count = 0;

    for (y = col - r; y <= col + r; y++)
    {
        for (x = row - r; x <= row + r; x++)
        {
            if ((y >= 1) && (y < MAP_HEIGHT - 1) && (x >= 1) && (x < MAP_WIDTH - 1))
            {
                if (map[y][x].ch == '#')
                {
                    wall_count++;
                }
            }
        }
    }
    return wall_count;
}

Terreno **mapborder(Terreno **map, int MAP_HEIGHT, int MAP_WIDTH) // manecas
{
    int x, y;

    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
        {
            if (y == 0 || y == MAP_HEIGHT - 1)
            {
                map[y][x].ch = '#';
                map[y][x].walkable = false;
            }
            if (y == 1 || y == MAP_HEIGHT - 2)
            {
                map[y][x].ch = '#';
                map[y][x].walkable = false;
            }
        }
    }
    for (x = 0; x < MAP_WIDTH; x++)
    {
        for (y = 0; y < MAP_HEIGHT; y++)
        {
            if (x == 0 || x == MAP_WIDTH - 1)
            {
                map[y][x].ch = '#';
                map[y][x].walkable = false;
            }
            if (x == 1 || x == MAP_WIDTH - 2)
            {
                map[y][x].ch = '#';
                map[y][x].walkable = false;
            }
        }
    }
    return map;
}

Terreno **generate_map(int MAP_HEIGHT, int MAP_WIDTH)
{
    int i, j;
    Terreno **map = calloc(MAP_HEIGHT, sizeof(Terreno *));

    if (map == NULL)
        printf("Error no memory allocated");

    for (i = 0; i < MAP_HEIGHT; i++)
    {
        map[i] = calloc(MAP_WIDTH, sizeof(Terreno));
        if (map[i] == NULL)
            printf("Error no memory allocated");
    }

    for (i = 2; i < MAP_HEIGHT - 2; i++)
    {
        for (j = 2; j < MAP_WIDTH - 2; j++)
        {
            if (rand() % 100 < 45)
            {
                map[i][j].ch = '#';
                map[i][j].walkable = false;
            }
            else
            {
                map[i][j].ch = '.';
                map[i][j].walkable = true;
            }
        }
    }

    mapborder(map, MAP_HEIGHT, MAP_WIDTH);

    int fst = 4, snd = 3;

    for (int k = 0; k < fst; k++)
    {
        for (i = 0; i < MAP_HEIGHT; i++)
        {
            for (j = 0; j < MAP_WIDTH; j++)
            {
                if (WallCount(map, 1, i, j, MAP_HEIGHT, MAP_WIDTH) >= 5 || WallCount(map, 2, i, j, MAP_HEIGHT, MAP_WIDTH) <= 2)
                {
                    map[i][j].ch = '#';
                    map[i][j].walkable = false;
                }
                else
                {
                    map[i][j].ch = '.';
                    map[i][j].walkable = true;
                }
            }
        }
    }

    mapborder(map, MAP_HEIGHT, MAP_WIDTH);

    for (int k = 0; k < snd; k++)
    {

        for (i = 0; i < MAP_HEIGHT; i++)
        {
            for (j = 0; j < MAP_WIDTH; j++)
            {
                if (WallCount(map, 1, i, j, MAP_HEIGHT, MAP_WIDTH) >= 5)
                {
                    map[i][j].ch = '#';
                    map[i][j].walkable = false;
                }
                else
                {
                    map[i][j].ch = '.';
                    map[i][j].walkable = true;
                }
            }
        }
    }

    mapborder(map, MAP_HEIGHT, MAP_WIDTH);

    return map;
}

Posicao setupMap(Terreno **map, int MAP_HEIGHT, int MAP_WIDTH) // manecas
{
    Posicao pos_inicial;
    int x, y;
    do
    {
        x = rand() % MAP_WIDTH;
        y = rand() % MAP_HEIGHT;
        pos_inicial.x = x;
        pos_inicial.y = y;
    } while (map[y][x].walkable == false || (WallCount(map, 3, y, x, MAP_HEIGHT, MAP_WIDTH) != 0));
    return pos_inicial;
}

Posicao setupMapi(Terreno **map, int MAP_HEIGHT, int MAP_WIDTH, Posicao pos_inicial) // manecas
{
    Posicao pos_inicial_i;
    int x, y;
    do
    {
        x = rand() % MAP_WIDTH;
        y = rand() % MAP_HEIGHT;
        pos_inicial_i.y = y;
        pos_inicial_i.x = x;

    } while (map[y][x].walkable == false || (x == pos_inicial.x && y == pos_inicial.y));
    return pos_inicial_i;
}

Posicao level_entry(Terreno **map, int MAP_HEIGHT, int MAP_WIDTH, Posicao pos_inicial, Posicao pos_inicial_i) //Sá
{
    Posicao pos_lvl;
    int x, y;
    do
    {
        x = rand() % MAP_WIDTH;
        y = rand() % MAP_HEIGHT;
        pos_lvl.y = y;
        pos_lvl.x = x;

    } while (map[y][x].walkable == false || (x == pos_inicial.x && y == pos_inicial.y) || (x == pos_inicial_i.x && y == pos_inicial_i.y));
    return pos_lvl;
}

int next_level(Entidade *player, int input, Posicao pos_lvl) // manecas
{
    if (input == 'e' && ((player->pos.y == pos_lvl.y) && (player->pos.x == pos_lvl.x)))
    {
        trigger = 5;
        return 1;
    }
    else
        return 0;
}

Posicao *plus_damage_obj(Terreno **map, int MAP_HEIGHT, int MAP_WIDTH, Posicao pos_inicial, Posicao pos_inicial_i, Posicao pos_lvl) // manecas
{

    Posicao *pos_damage = calloc(5, sizeof(Posicao));
    int x, y;

    for (int i = 0; i < 5; i++)
    {

        do
        {
            x = rand() % MAP_WIDTH;
            y = rand() % MAP_HEIGHT;
            pos_damage[i].y = y;
            pos_damage[i].x = x;

        } while (map[y][x].walkable == false || (x == pos_inicial.x && y == pos_inicial.y) || (x == pos_inicial_i.x && y == pos_inicial_i.y) || (x == pos_lvl.x && y == pos_lvl.y));
    }
    return pos_damage;
}

Posicao *traps(Terreno **map, int MAP_HEIGHT, int MAP_WIDTH, Posicao pos_inicial, Posicao pos_inicial_i, Posicao pos_lvl) // Sá
{

    Posicao *pos_traps = calloc(30, sizeof(Posicao));
    int x, y;

    for (int i = 0; i < 30; i++)
    {

        do
        {
            x = rand() % MAP_WIDTH;
            y = rand() % MAP_HEIGHT;
            pos_traps[i].y = y;
            pos_traps[i].x = x;

        } while (map[y][x].walkable == false || !(distance(pos_traps[i], pos_inicial)) || !(distance(pos_traps[i], pos_inicial_i)) || !(distance(pos_traps[i], pos_lvl)) || ((x == (pos_traps->x + 1) && (x == pos_traps->x - 1) && (y == pos_traps->y + 1) && (y == pos_traps->y - 1))));
    }
    return pos_traps;
}

Posicao *fruits(Terreno **map, int MAP_HEIGHT, int MAP_WIDTH, Posicao pos_inicial, Posicao pos_inicial_i, Posicao pos_lvl) // Sá
{

    Posicao *pos_fruit = calloc(3, sizeof(Posicao));
    int x, y;

    for (int i = 0; i < 3; i++)
    {

        do
        {
            x = rand() % MAP_WIDTH;
            y = rand() % MAP_HEIGHT;
            pos_fruit[i].y = y;
            pos_fruit[i].x = x;

        } while (map[y][x].walkable == false || !(distance(pos_fruit[i], pos_inicial)) || !(distance(pos_fruit[i], pos_inicial_i)) || !(distance(pos_fruit[i], pos_lvl)) || ((x > (pos_fruit->x + 20) && (x > pos_fruit->x - 20) && (y > pos_fruit->y + 20) && (y > pos_fruit->y - 20))));
    }
    return pos_fruit;
}

Posicao treasure(Terreno **map, int MAP_HEIGHT, int MAP_WIDTH, Posicao pos_inicial, Posicao pos_inicial_i, Posicao pos_lvl) // Sá
{
    Posicao pos_treasure;
    int x, y;
    do
    {
        x = rand() % MAP_WIDTH;
        y = rand() % MAP_HEIGHT;
        pos_treasure.y = y;
        pos_treasure.x = x;

    } while (map[y][x].walkable == false || !(distance(pos_treasure, pos_inicial)) || !(distance(pos_treasure, pos_inicial_i)) || !(distance(pos_treasure, pos_lvl)));
    return pos_treasure;
}

Posicao mystery(Terreno **map, int MAP_HEIGHT, int MAP_WIDTH, Posicao pos_inicial, Posicao pos_inicial_i, Posicao pos_lvl) // Sá
{
    Posicao pos_mystery;
    int x, y;
    do
    {
        x = rand() % MAP_WIDTH;
        y = rand() % MAP_HEIGHT;
        pos_mystery.y = y;
        pos_mystery.x = x;

    } while (map[y][x].walkable == false || !(distance(pos_mystery, pos_inicial)) || !(distance(pos_mystery, pos_inicial_i)) || !(distance(pos_mystery, pos_lvl)) || !(distance(pos_mystery, pos_treasure)));
    return pos_mystery;
}

int distance(Posicao pos1, Posicao pos2)
{
    int dx = pos1.x - pos2.x;
    int dy = pos1.y - pos2.y;
    int distancia = sqrt(pow(dx, 2) + pow(dy, 2));
    return distancia;
}

void FreeMapa(Terreno **map, int MAP_HEIGHT) // manecas
{
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        free(map[i]);
    }
    free(map);
}