#include <stdio.h>
#include <dungeon.h>

const int MAP_HEIGHT = 56;
const int MAP_WIDTH = 238;

Entidade *player;
Inimigo *inimigo;
Terreno **map;
Posicao pos_inicial;
Posicao pos_inicial_i;
WINDOW *win;

int main(void)
{
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    start_color();

    WINDOW *menuwin;
    menuwin = newwin(4,14 , 26 ,108);
    box(menuwin, 0, 0);
    refresh();
    wrefresh(menuwin);
    keypad(menuwin, true);

    char opcoes [2] [40] = {"Start Game", "Exit"};
    int choice;
    int highlight = 0;
    int length1 = strlen(opcoes [0]);
    int length2 = strlen(opcoes [1]);

    while (1) {
        for (int i = 0; i < 2; i++) {
            if (i == highlight) {
                wattron (menuwin, A_BOLD);
            }
            if(i==0){
            mvwprintw (menuwin, i+1, length1/2-3, "%s", opcoes[i]);
            wattroff (menuwin, A_BOLD);
        }
            if(i==1){
            mvwprintw (menuwin, i+1, length2+1, "%s", opcoes[i]);
            wattroff (menuwin, A_BOLD);
        }
    }
        choice = wgetch(menuwin);

        switch (choice){
            case KEY_UP:
                if (highlight > 0) {
                    highlight--;
                } else {
                    highlight = 1;
                }
                break;
            case KEY_DOWN:
                if (highlight < 1) {
                    highlight++;
                } else {
                    highlight = 0;
                }
                break;
            default:
                break;
        }
        if ((choice == 10) || (choice == 'q')){
            break;
        }
    }

    if(highlight == 0 && choice == 10) {

        clear();
        delwin(menuwin);

        cursesSetup();

        srand(time(NULL));

        map = generate_map();
        pos_inicial = setupMap(map);
        pos_inicial_i = setupMapi(map);
        player = createPlayer(pos_inicial);
        inimigo = createInimigo(pos_inicial_i);
        damage(inimigo, player);

        gameLoop();
    
        FreeMapa(map);

        closeGame();

    }else if(highlight == 1 || choice == 'q') {
        endwin();
    }
    return 0;
}