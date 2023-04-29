#include <dungeon.h>

Sala createSala(int y, int x, int height, int width)
{
    Sala new;

    new.pos.y = y;
    new.pos.x = x;
    new.height = height;
    new.width = width;
    new.centro.y = y + (int)(height / 2);
    new.centro.x = x + (int)(width / 2);

    return new;
}

void conectSalas(Posicao centro1, Posicao centro2)
{
    Posicao temp;
    temp.x = centro1.x;
    temp.y = centro1.y;

    while (1)
    {
        if (abs((temp.x - 1) - centro2.x) < abs(temp.x) - centro2.x)
        {
            temp.x--;
        }
        else if (abs((temp.x + 1) - centro2.x) < abs(temp.x - centro2.x))
        {
            temp.x++;
        }
        else if (abs((temp.y + 1) - centro2.y) < abs(temp.y - centro2.y))
        {
            temp.y++;
        }
        else if (abs((temp.y - 1) - centro2.y) < abs(temp.y - centro2.y))
        {
            temp.y--;
        }
        else
            break;

        map[temp.y][temp.x].ch = '.';
        map[temp.y][temp.x].walkable = true;
    }
}

void addSalaToMap(Sala sala)
{
    for (int y = sala.pos.y; y < (sala.pos.y + sala.height); y++)
    {
        for (int x = sala.pos.x; x < (sala.pos.x + sala.width); x++)
        {
            map[y][x].ch = '.';
            map[y][x].walkable = true;
        }
    }
}