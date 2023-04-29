#include <dungeon.h>

void cursesSetup(void)
{
    initscr();
    noecho();
    curs_set(0);
}

void gameLoop(void)
{
    int ch;

    drawAll();

    while (ch = getch())
    {
        if (ch == 'q')
        {
            break;
        }
        handleInput(ch);
        drawAll();
    }
}

void closeGame(void)
{
    endwin();
    free(player);
}
