#include <stdio.h>
#include <dungeon.h>

int vida_atual_inimigo = 40;
int trigger = 0;
int has_pickaxe = 0;
int flag_boss = 0;
int damage_buff = 1;

Posicao pos_mystery;
Posicao pos_treasure;
WINDOW *win;

int main(void)
{
    int MAP_HEIGHT;
    int MAP_WIDTH;
    Terreno **map;
    Entidade *player;
    Inimigo *inimigo;
    Posicao pos_inicial;
    Posicao pos_inicial_i;
    Posicao pos_lvl;
    Posicao *pos_damage;
    Posicao *pos_traps;
    Posicao *pos_fruit;
    int dungeon_level = 1;

    initscr();
    getmaxyx(stdscr, MAP_HEIGHT, MAP_WIDTH); // usamos a função getmaxyx para obter as dimensões para cada terminal
    MAP_HEIGHT -= 3; // subtraimos 3 para ter espaço para desenhar stats do player no fundo da tela
    noecho();
    cbreak();
    curs_set(0);

    start_color(); // usamos a função start_color para iniciar as cores que serão chamadas futuramente.
    init_color(COLOR_CYAN, 1000, 600, 0); // iniciamos a cor ciano para um rgb correspondente a laranja para a cor do inimigo.
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    init_pair(6, COLOR_BLACK, COLOR_WHITE);
    init_color(COLOR_MAGENTA, 700, 600, 0); // iniciamos a cor magenta com um rgb correspondente a dourado para a cor do gold.
    init_pair(7, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(8, COLOR_WHITE, COLOR_BLACK);

    WINDOW *menuwin;
    menuwin = newwin(40, 84, MAP_HEIGHT / 2 - 20, MAP_WIDTH / 2 - 46);
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
        wattron(menuwin, COLOR_PAIR(4) | A_BOLD);
        mvwprintw(menuwin, 10, 0, "    #######    ##    ##   ##        ##  ########   ########  ########  ##        ##");
        mvwprintw(menuwin, 11, 0, "   ##    ##   ##    ##   ## ##     ##  ##         ##        ##    ##  ## ##     ##");
        mvwprintw(menuwin, 12, 0, "  ##     ##  ##    ##   ##   ##   ##  ##   ####  #######   ##    ##  ##   ##   ##");
        mvwprintw(menuwin, 13, 0, " ##    ##   ##    ##   ##     ## ##  ##     ##  ##        ##    ##  ##     ## ##");
        mvwprintw(menuwin, 14, 0, "#######    ########   ##        ##  #########  ########  ########  ##        ##");
        wattroff(menuwin, COLOR_PAIR(4) | A_BOLD);
        for (int i = 0; i < 2; i++)
        {
            if (i == highlight)
            {
                wattron(menuwin, A_BOLD);
            }
            if (i == 0)
            {
                mvwprintw(menuwin, i + 20, 40 - length1 / 2 - 1, "%s", opcoes[i]);
                wattroff(menuwin, A_BOLD);
            }
            if (i == 1)
            {
                mvwprintw(menuwin, i + 20, 40 - length2 / 2 - 1, "%s", opcoes[i]);
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

        cursesSetup(MAP_HEIGHT, MAP_WIDTH);

        srand(time(NULL));

        map = generate_map(MAP_HEIGHT, MAP_WIDTH);
        pos_inicial = setupMap(map, MAP_HEIGHT, MAP_WIDTH);
        pos_inicial_i = setupMapi(map, MAP_HEIGHT, MAP_WIDTH, pos_inicial);
        player = createPlayer(pos_inicial);
        inimigo = createInimigo(pos_inicial_i, dungeon_level);
        pos_lvl = level_entry(map, MAP_HEIGHT, MAP_WIDTH, pos_inicial, pos_inicial_i);
        pos_damage = plus_damage_obj(map, MAP_HEIGHT, MAP_WIDTH, pos_inicial, pos_inicial_i, pos_lvl);
        pos_traps = traps(map, MAP_HEIGHT, MAP_WIDTH, pos_inicial, pos_inicial_i, pos_lvl, dungeon_level);
        pos_fruit = fruits(map, MAP_HEIGHT, MAP_WIDTH, pos_inicial, pos_inicial_i, pos_lvl);
        pos_treasure = treasure(map, MAP_HEIGHT, MAP_WIDTH, pos_inicial, pos_inicial_i, pos_lvl);
        pos_mystery = mystery(map, MAP_HEIGHT, MAP_WIDTH, pos_inicial, pos_inicial_i, pos_lvl);

        gameLoop(player, inimigo, MAP_HEIGHT, MAP_WIDTH, map, pos_inicial, pos_inicial_i, pos_lvl, pos_damage, pos_traps, pos_fruit, dungeon_level);
        closeGame(player, inimigo, MAP_HEIGHT, map, pos_damage, pos_traps, pos_fruit);
    }
    else if (highlight == 1 || choice == 'q')
    {
        endwin();
    }
    return 0;
}