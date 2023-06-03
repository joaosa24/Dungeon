#include <dungeon.h>

void cursesSetup(int MAP_HEIGHT, int MAP_WIDTH) // inicializa a biblioteca ncurses
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

void gameLoop(Entidade *player, Inimigo *inimigo, int MAP_HEIGHT, int MAP_WIDTH, Terreno **map, Posicao pos_inicial, Posicao pos_inicial_i, Posicao pos_lvl, Posicao *pos_damage, Posicao *pos_traps, Posicao *pos_fruit, int dungeon_level) // (manecas e sá)
{
    int ch = -1; // inicializamos o inteiro com -1 (valor default) para não aparecer um warning "uninitialized" na chamada da função next_level;
    int menu;

    drawAll(player, inimigo, MAP_HEIGHT, MAP_WIDTH, map, pos_lvl, pos_damage, pos_traps, pos_fruit, dungeon_level);

    while (player->vida > 0 && (ch = getch()) && next_level(player, ch, pos_lvl) != 1)
    {
        if (ch == 'q')
        {
            break;
        }
        trigger = dica(player, ch);
        handleInput(player, inimigo, ch, MAP_HEIGHT, MAP_WIDTH, map);
        moveInimigo(inimigo, player, map);
        damage(inimigo, player);
        heal(inimigo, player, ch, dungeon_level);
        if (dungeon_level % 5 != 0)
        {
            respawn(player, inimigo, MAP_HEIGHT, MAP_WIDTH, map);
        }
        treasure_loot(player, ch);
        plus_damage(player, ch, MAP_HEIGHT, pos_damage);
        fruits_heal(player, ch, MAP_HEIGHT, pos_fruit);
        mystery_loot(player, ch, MAP_HEIGHT);
        traps_damage(player, pos_traps);
        pickaxe(player, ch);
        drawAll(player, inimigo, MAP_HEIGHT, MAP_WIDTH, map, pos_lvl, pos_damage, pos_traps, pos_fruit, dungeon_level);
    }
    
    if (player->vida <= 0)
    {

        menu = drawMenuMorte(ch, MAP_HEIGHT, MAP_WIDTH);
    }
    else
        menu = 0;

    if (menu == 1)
    {

        srand(time(NULL));

        map = generate_map(MAP_HEIGHT, MAP_WIDTH);
        pos_inicial = setupMap(map, MAP_HEIGHT, MAP_WIDTH);
        pos_inicial_i = setupMapi(map, MAP_HEIGHT, MAP_WIDTH, pos_inicial);
        player = createPlayer(pos_inicial);
        vida_atual_inimigo = 40;
        inimigo = createInimigo(pos_inicial_i, dungeon_level);
        pos_lvl = level_entry(map, MAP_HEIGHT, MAP_WIDTH, pos_inicial, pos_inicial_i);
        dungeon_level = 1;
        pos_damage = plus_damage_obj(map, MAP_HEIGHT, MAP_WIDTH, pos_inicial, pos_inicial_i, pos_lvl);
        pos_traps = traps(map, MAP_HEIGHT, MAP_WIDTH, pos_inicial, pos_inicial_i, pos_lvl);
        pos_fruit = fruits(map, MAP_HEIGHT, MAP_WIDTH, pos_inicial, pos_inicial_i, pos_lvl);
        pos_treasure = treasure(map, MAP_HEIGHT, MAP_WIDTH, pos_inicial, pos_inicial_i, pos_lvl);
        pos_mystery = mystery(map, MAP_HEIGHT, MAP_WIDTH, pos_inicial, pos_inicial_i, pos_lvl);
        inimigo->ent.ch = 'b';

        gameLoop(player, inimigo, MAP_HEIGHT, MAP_WIDTH, map, pos_inicial, pos_inicial_i, pos_lvl, pos_damage, pos_traps, pos_fruit, dungeon_level);
    }
    if (next_level(player, ch, pos_lvl) == 1)
    {
        int vida_atual = player->vida;
        int gold_atual = player->gold;
        int damage_atual = player->damage;
        vida_atual_inimigo += 40;
        srand(time(NULL));

        map = generate_map(MAP_HEIGHT, MAP_WIDTH);
        pos_inicial = setupMap(map, MAP_HEIGHT, MAP_WIDTH);
        pos_inicial_i = setupMapi(map, MAP_HEIGHT, MAP_WIDTH, pos_inicial);
        player = createPlayer(pos_inicial);
        dungeon_level++;
        if (dungeon_level % 5 == 0)
        {
            inimigo = createInimigo(pos_inicial_i, dungeon_level);
            inimigo->ent.vida = vida_atual_inimigo + 180;
            inimigo->ent.damage += dungeon_level;
        }
        else
            inimigo = createInimigo(pos_inicial_i, dungeon_level);

        pos_lvl = level_entry(map, MAP_HEIGHT, MAP_WIDTH, pos_inicial, pos_inicial_i);
        pos_damage = plus_damage_obj(map, MAP_HEIGHT, MAP_WIDTH, pos_inicial, pos_inicial_i, pos_lvl);
        pos_traps = traps(map, MAP_HEIGHT, MAP_WIDTH, pos_inicial, pos_inicial_i, pos_lvl);
        pos_fruit = fruits(map, MAP_HEIGHT, MAP_WIDTH, pos_inicial, pos_inicial_i, pos_lvl);
        pos_treasure = treasure(map, MAP_HEIGHT, MAP_WIDTH, pos_inicial, pos_inicial_i, pos_lvl);
        pos_mystery = mystery(map, MAP_HEIGHT, MAP_WIDTH, pos_inicial, pos_inicial_i, pos_lvl);
        player->vida = vida_atual;
        player->damage = damage_atual;
        player->gold = gold_atual;
        gameLoop(player, inimigo, MAP_HEIGHT, MAP_WIDTH, map, pos_inicial, pos_inicial_i, pos_lvl, pos_damage, pos_traps, pos_fruit, dungeon_level);
    }
}

void closeGame(Entidade *player, Inimigo *inimigo, int MAP_HEIGHT, Terreno **map, Posicao *pos_damage, Posicao *pos_traps, Posicao *pos_fruit) // manecas
{
    endwin();
    free(player);
    free(inimigo);
    free(pos_damage);
    free(pos_fruit);
    free(pos_traps);
    FreeMapa(map, MAP_HEIGHT);
}