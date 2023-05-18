#include <dungeon.h>

void cursesSetup(void)
{
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    start_color();
    init_color(COLOR_CYAN, 1000, 600, 0); // iniciamos a cor ciano para um rgb correspondente a laranja para a cor do inimigo.
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    init_pair(6, COLOR_BLACK, COLOR_WHITE);
    init_color(COLOR_MAGENTA, 700, 600, 0); // iniciamos a cor magenta com um rgb correspondente a dourado para a cor do gold.
    init_pair(7, COLOR_MAGENTA, COLOR_BLACK);

    WINDOW *win;
    win = newwin(MAP_HEIGHT, MAP_WIDTH, 5, 5);
    box(win, 0, 0);
    refresh();
    wrefresh(win);
    keypad(win, true);
}

void gameLoop(void)
{
    int ch = -1; // inicializamos o inteiro com -1 (valor default) para não aparecer um warning "uninitialized" na chamada da função next_level;
    int menu;

    drawAll();

    while (player->vida > 0 && (ch = getch()) && next_level(player, ch) != 1)
    {
        if (ch == 'q')
        {
            break;
        }
        handleInput(ch);
        moveInimigo(inimigo, player, map);
        damage(inimigo, player);
        heal(inimigo, player, ch);
        respawn(inimigo);
        trigger = dica(player, ch);
        plus_damage(player, ch);
        drawAll();
    }
    if (next_level(player, ch) == 1)
    {
        int vida_atual = player->vida;
        int gold_atual = player->gold;
        int damage_atual = player->damage;
        srand(time(NULL));

        map = generate_map();
        pos_inicial = setupMap(map);
        pos_inicial_i = setupMapi(map);
        player = createPlayer(pos_inicial);
        inimigo = createInimigo(pos_inicial_i);
        pos_lvl = level_entry(map);
        pos_damage = plus_damage_obj(map);
        dungeon_level++;
        player->vida = vida_atual;
        player->damage = damage_atual;
        player->gold = gold_atual;
        gameLoop();
    }

    if (player->vida <= 0)
    {

        menu = drawMenuMorte(ch);
    }
    else
        menu = 0;

    if (menu == 1)
    {

        srand(time(NULL));

        map = generate_map();
        pos_inicial = setupMap(map);
        pos_inicial_i = setupMapi(map);
        player = createPlayer(pos_inicial);
        inimigo = createInimigo(pos_inicial_i);
        pos_lvl = level_entry(map);
        pos_damage = plus_damage_obj(map);

        gameLoop();
    }
}

void closeGame(void)
{
    endwin();
    free(player);
    free(inimigo);
    free(pos_damage);
    FreeMapa(map);
}