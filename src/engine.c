#include <dungeon.h>

void cursesSetup(void)
{
    initscr();
    noecho();
    cbreak();
    curs_set(0);

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
        if (dungeon_level % 5 != 0)
        {
            respawn(inimigo);
        }
        trigger = dica(player, ch);
        treasure_loot(player, ch);
        plus_damage(player, ch);
        fruits_heal(player, ch);
        traps_damage(player);
        pickaxe(player, ch);
        mystery_loot(player, ch);
        drawAll();
    }
    if (next_level(player, ch) == 1)
    {
        int vida_atual = player->vida;
        int gold_atual = player->gold;
        int damage_atual = player->damage;
        vida_atual_inimigo += 20;
        srand(time(NULL));

        map = generate_map();
        pos_inicial = setupMap(map);
        pos_inicial_i = setupMapi(map);
        player = createPlayer(pos_inicial);
        dungeon_level++;
        if (dungeon_level % 5 == 0)
        {
            inimigo = createInimigo(pos_inicial_i);
            inimigo->ent.vida = vida_atual_inimigo + 100;
            inimigo->ent.damage += dungeon_level;
        }
        else
            inimigo = createInimigo(pos_inicial_i);

        pos_lvl = level_entry(map);
        pos_damage = plus_damage_obj(map);
        pos_traps = traps(map);
        pos_fruit = fruits(map);
        pos_treasure = treasure(map);
        pos_mystery = mystery(map);
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
        dungeon_level = 1;
        pos_damage = plus_damage_obj(map);
        pos_traps = traps(map);
        pos_fruit = fruits(map);
        pos_treasure = treasure(map);
        pos_mystery=mystery(map);
        inimigo->ent.ch= 'b';

        gameLoop();
    }
}

void closeGame(void)
{
    endwin();
    free(player);
    free(inimigo);
    free(pos_damage);
    free(pos_fruit);
    free(pos_traps);
    FreeMapa(map);
}