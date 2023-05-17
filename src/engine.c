#include <dungeon.h>

void cursesSetup(void) {
    initscr();
    noecho();
    cbreak();
    curs_set(0);

    WINDOW *win;
    win = newwin(MAP_HEIGHT, MAP_WIDTH, 5 ,5);
    box(win, 0, 0);
    refresh();
    wrefresh(win);
    keypad(win, true);

}

void gameLoop(void) {
    int ch;
    int menu;

    drawAll();

    while (player->vida > 0 && (ch = getch())) {
        if (ch == 'q') {
            break;
        }
        handleInput(ch);
        moveInimigo(inimigo, player, map);
        damage(inimigo, player);
        drawAll();
    }

    if(player->vida <= 0) {

        menu = drawMenuMorte();

    } else menu = 0;

    if(menu == 1) {

        srand(time(NULL));

        map = generate_map();
        pos_inicial = setupMap(map);
        pos_inicial_i = setupMapi(map);
        player = createPlayer(pos_inicial);
        inimigo = createInimigo(pos_inicial_i);

        gameLoop();
    }
}

void closeGame(void) {
    endwin();
    free(player);
    FreeMapa(map);
}