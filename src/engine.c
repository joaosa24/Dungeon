#include <dungeon.h>

void cursesSetup(void)
{
    initscr();
    noecho();
    cbreak();
    curs_set(0);

    WINDOW *win;
    win = newwin(50, 230, 5 ,5);
    box(win, 0, 0);
    refresh();
    wrefresh(win);
    keypad(win, true);

}

void gameLoop(void)
{
    int ch;
    
    drawAll();

    while (player->vida > 0 && (ch = getch()))
    {
        if (ch == 'q')
        {
            break;
        }
        handleInput(ch);
        damage(inimigo, player);
        drawAll();
    }
}


void closeGame(void)
{
    endwin();
    free(player);
}
