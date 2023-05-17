#include <dungeon.h>

void drawMapa(void) {
    for (int i = 0; i < MAP_HEIGHT ; i++) {
        for (int j = 0; j < MAP_WIDTH ; j++) {
            Posicao pos = {i,j};
            if (is_visible(player, pos)) {
                mvaddch(i, j, map[i][j].ch);
            } else {
                mvaddch(i, j, ' ');
            }
        }
    }
}

void drawHUD() {
    attron(A_BOLD);
    mvprintw(MAP_HEIGHT, 1, "Health : %d", player->vida);
    attroff(A_BOLD);
}

void drawEntidade(Entidade *entidade) {
    attron(A_BOLD);
    mvaddch(entidade->pos.y, entidade->pos.x, entidade->ch);
    attroff(A_BOLD);
}

void drawInimigo(Inimigo *inimigo) {
    for (int i = 0; i < MAP_HEIGHT ; i++) {
        for (int j = 0; j < MAP_WIDTH ; j++) {
            if (is_enemy_visible(player, inimigo)) {
                attron(A_BOLD);
                mvaddch(inimigo->ent.pos.y, inimigo->ent.pos.x, inimigo->ent.ch);
                attroff(A_BOLD);
            }
        }
    }
}

int drawMenuMorte() {

    WINDOW* win = NULL;
    clear();
    if(win != NULL) delwin(win);

    char opcoes [2] [40] = {"Play Again", "Exit"};
    int choice;
    int highlight = 0;
    int length1 = strlen(opcoes [0]);
    int length2 = strlen(opcoes [1]);

    WINDOW *menu_win_morte = newwin(4, 14, MAP_HEIGHT/2 - 2, MAP_WIDTH/2 - 10);

    initscr();
    noecho();
    cbreak();
    curs_set(0);

    box(menu_win_morte, 0, 0);
    refresh();
    wrefresh(menu_win_morte);
    keypad(menu_win_morte, true);

    while (1) {
        for (int i = 0; i < 2; i++) {
            if (i == highlight) {
                wattron (menu_win_morte, A_BOLD);
            }
            if(i==0){
                mvwprintw (menu_win_morte, i+1, length1/2-3, "%s", opcoes[i]);
                wattroff (menu_win_morte, A_BOLD);
            }
            if(i==1){
                mvwprintw (menu_win_morte, i+1, length2+1, "%s", opcoes[i]);
                wattroff (menu_win_morte, A_BOLD);
            }
        }
        choice = wgetch(menu_win_morte);

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
        return 1;
    } else if(highlight == 1 || choice == 'q') {
        return 2;
    }
    return 0;
}

void drawAll(void) {
    clear();
    refresh();
    drawMapa();
    drawHUD();
    drawEntidade(player);
    drawInimigo(inimigo);
}