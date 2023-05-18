#include <stdio.h>
#include <dungeon.h>

int MAP_HEIGHT;
int MAP_WIDTH;
int dungeon_level = 1;
int vida_atual_inimigo = 40;
int trigger = 0;

Entidade *player;
Inimigo *inimigo;
Terreno **map;
Posicao pos_inicial;
Posicao pos_inicial_i;
Posicao pos_lvl;
Posicao *pos_damage;
WINDOW *win;

int main(void)
{
    initscr();
    getmaxyx(stdscr, MAP_HEIGHT, MAP_WIDTH);
    MAP_HEIGHT -= 3;
    noecho();
    cbreak();
    curs_set(0);

    WINDOW *menuwin;
    menuwin = newwin(4, 14, MAP_HEIGHT / 2 - 2, MAP_WIDTH / 2 - 10);
    box(menuwin, 0, 0);
    refresh();
    wrefresh(menuwin);
    keypad(menuwin, true);

    char opcoes[2][40] = {"Start Game", "Exit"};
    int choice;
    int highlight = 0;
    int length1 = strlen(opcoes[0]);
    int length2 = strlen(opcoes[1]);

    while (1)
    {
        for (int i = 0; i < 2; i++)
        {
            if (i == highlight)
            {
                wattron(menuwin, A_BOLD);
            }
            if (i == 0)
            {
                mvwprintw(menuwin, i + 1, length1 / 2 - 3, "%s", opcoes[i]);
                wattroff(menuwin, A_BOLD);
            }
            if (i == 1)
            {
                mvwprintw(menuwin, i + 1, length2 + 1, "%s", opcoes[i]);
                wattroff(menuwin, A_BOLD);
            }
        }
        choice = wgetch(menuwin);

        switch (choice)
        {
        case KEY_UP:
            if (highlight > 0)
            {
                highlight--;
            }
            else
            {
                highlight = 1;
            }
            break;
        case KEY_DOWN:
            if (highlight < 1)
            {
                highlight++;
            }
            else
            {
                highlight = 0;
            }
            break;
        default:
            break;
        }
        if ((choice == 10) || (choice == 'q'))
        {
            break;
        }
    }

    if (highlight == 0 && choice == 10)
    {

        clear();
        delwin(menuwin);

        cursesSetup();

        srand(time(NULL));

        map = generate_map();
        pos_inicial = setupMap(map);
        pos_inicial_i = setupMapi(map);
        player = createPlayer(pos_inicial);
        inimigo = createInimigo(pos_inicial_i);
        pos_lvl = level_entry(map);
        pos_damage = plus_damage_obj(map);

        gameLoop();
        closeGame();
    }
    else if (highlight == 1 || choice == 'q')
    {
        endwin();
    }
    return 0;
}