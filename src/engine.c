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
    int highlight;

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

    if(player->vida <= 0){

        highlight = drawMenuMorte();

    }else highlight = 1;

    if(highlight == 0){

        srand(time(NULL));

        map = generate_map();
        pos_inicial = setupMap(map);
        pos_inicial_i = setupMapi(map);
        player = createPlayer(pos_inicial);
        inimigo = createInimigo(pos_inicial_i);

        gameLoop();
    }

}

void closeGame(void)
{
    endwin();
    free(player);
    FreeMapa(map);
}
