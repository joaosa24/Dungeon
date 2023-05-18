#include <dungeon.h>

int WallCount(Terreno **map, int r, int col, int row)
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

Terreno **mapborder(Terreno **map)
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

Terreno **generate_map()
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
            if (rand() % 100 < 44)
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

    mapborder(map);

    int fst = 4, snd = 3;

    while (fst > 0)
    {

        for (i = 0; i < MAP_HEIGHT; i++)
        {
            for (j = 0; j < MAP_WIDTH; j++)
            {
                if (WallCount(map, 1, i, j) >= 5 || WallCount(map, 2, i, j) <= 2)
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
        fst--;
    }

    mapborder(map);

    while (snd > 0)
    {

        for (i = 0; i < MAP_HEIGHT; i++)
        {
            for (j = 0; j < MAP_WIDTH; j++)
            {
                if (WallCount(map, 1, i, j) >= 5)
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
        snd--;
    }

    mapborder(map);

    return map;
}

Posicao setupMap(Terreno **map)
{
    Posicao pos_inicial;
    int x, y;
    do
    {
        x = rand() % MAP_WIDTH;
        y = rand() % MAP_HEIGHT;
        pos_inicial.x = x;
        pos_inicial.y = y;
    } while (map[y][x].walkable == false || (WallCount(map, 3, y, x) != 0));
    return pos_inicial;
}

Posicao setupMapi(Terreno **map)
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

Posicao level_entry(Terreno **map)
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

int next_level(Entidade *player, int trigger)
{
    if (trigger == 'e' && ((player->pos.y == pos_lvl.y) && (player->pos.x == pos_lvl.x)))
    {
        vida_atual_inimigo += 10; // para aumentar 20 pois a função é chamada duas vezes no gameloop! 
        return 1;
    }
    else
        return 0;
}

void FreeMapa(Terreno **map)
{
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        free(map[i]);
    }
    free(map);
}