#include <dungeon.h>

void cursesSetup(void)
{
    initscr();
    noecho();
    cbreak();
    curs_set(0);

    WINDOW *win;
    win = newwin(57, 238, 5 ,5);
    box(win, 0, 0);
    refresh();

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
