#include <dungeon.h>

void drawMapa(Entidade *player,int MAP_HEIGHT, int MAP_WIDTH,Terreno **map,int dungeon_level)
{
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            Posicao pos = {i, j};
            if (is_visible(player, pos))
            {
                if ((map[i][j].ch == '#'))
                {
                    if (dungeon_level % 5 != 0)
                    {
                        attron(COLOR_PAIR(4));
                        mvaddch(i, j, map[i][j].ch);
                        attroff(COLOR_PAIR(4));
                    }
                    else
                    {
                        attron(COLOR_PAIR(3));
                        mvaddch(i, j, map[i][j].ch);
                        attroff(COLOR_PAIR(3));
                    }
                }
                else if (map[i][j].ch == '.')
                {
                    mvaddch(i, j, map[i][j].ch);
                }
            }
            else
            {
                mvaddch(i, j, ' ');
            }
        }
    }
}

void drawHUD(Entidade *player,int MAP_HEIGHT, int MAP_WIDTH,int dungeon_level)
{
    attron(A_BOLD);
    mvprintw(MAP_HEIGHT, 1, "Health: ");
    attroff(A_BOLD);
    if (player->vida >= 70 && player->vida <= 100)
    {
        attron(COLOR_PAIR(1) | A_BOLD);
        mvprintw(MAP_HEIGHT, 9, "%d", player->vida);
        attroff(COLOR_PAIR(1) | A_BOLD);
    }
    else if (player->vida >= 35)
    {
        attron(COLOR_PAIR(2) | A_BOLD);
        mvprintw(MAP_HEIGHT, 9, "%d", player->vida);
        attroff(COLOR_PAIR(2) | A_BOLD);
    }
    else if (player->vida < 35)
    {
        attron(COLOR_PAIR(3) | A_BOLD);
        mvprintw(MAP_HEIGHT, 9, "%d", player->vida);
        attroff(COLOR_PAIR(3) | A_BOLD);
    }
    else if (player->vida > 100)
    {
        attron(COLOR_PAIR(7) | A_BOLD);
        mvprintw(MAP_HEIGHT, 9, "%d", player->vida);
        attroff(COLOR_PAIR(7) | A_BOLD);
    }

    attron(COLOR_PAIR(5) | A_BOLD);
    mvprintw(MAP_HEIGHT, 20, "Dungeon Level: %d", dungeon_level);
    attroff(COLOR_PAIR(5) | A_BOLD);
    attron(COLOR_PAIR(2) | A_BOLD);
    mvprintw(MAP_HEIGHT + 1, 20, "Damage Buff: %d%c", damage_buff, 'x');
    attroff(COLOR_PAIR(2) | A_BOLD);
    attron(COLOR_PAIR(2) | A_BOLD);
    mvprintw(MAP_HEIGHT + 2, 20, "Pickaxe uses: %d%c", has_pickaxe, 'x');
    attroff(COLOR_PAIR(2) | A_BOLD);
    attron(COLOR_PAIR(6));
    mvprintw(MAP_HEIGHT, MAP_WIDTH - 38, "Press 'e' to INTERACT with the mob    ");
    attroff(COLOR_PAIR(6));
    attron(COLOR_PAIR(6));
    mvprintw(MAP_HEIGHT + 1, MAP_WIDTH - 38, "Press 'h' to get a HINT (50 gold)     ");
    attroff(COLOR_PAIR(6));
    attron(COLOR_PAIR(6));
    mvprintw(MAP_HEIGHT + 2, MAP_WIDTH - 38, "Press 'p' to buy a PICKAXE (150 gold) ");
    attroff(COLOR_PAIR(6));
    // desenha o parametro "damage"
    attron(A_BOLD);
    mvprintw(MAP_HEIGHT + 1, 1, "Damage: ");
    attroff(A_BOLD);
    attron(COLOR_PAIR(3) | A_BOLD);
    mvprintw(MAP_HEIGHT + 1, 9, "%d", player->damage);
    attroff(COLOR_PAIR(3) | A_BOLD);
    // desenha o parametro "gold"
    attron(A_BOLD);
    mvprintw(MAP_HEIGHT + 2, 1, "Gold: ");
    attroff(A_BOLD);
    attron(COLOR_PAIR(7) | A_BOLD); // a corlor_pair(7) que deveria ser dourado está amarelo ??
    mvprintw(MAP_HEIGHT + 2, 9, "%d", player->gold);
    attroff(COLOR_PAIR(7) | A_BOLD);
}

void drawPlayer(Entidade *player) // função que desenha o jogador
{
    if (player->vida >= 70) // se o jogador estiver com 70 ou mais de vida, o caracter '@' estará a verde
    {
        attron(COLOR_PAIR(1) | A_BOLD);
        mvaddch(player->pos.y, player->pos.x, player->ch);
        attroff(COLOR_PAIR(1) | A_BOLD);
    }
    else if (player->vida >= 35) // se o jogador estiver com 35 ou mais de vida, o caracter '@' estará a amarelo
    {
        attron(COLOR_PAIR(2) | A_BOLD);
        mvaddch(player->pos.y, player->pos.x, player->ch);
        attroff(COLOR_PAIR(2) | A_BOLD);
    }
    else // se o jogador estiver com menos de 35, o caracter '@' estará a vermelho
    {
        attron(COLOR_PAIR(3) | A_BOLD);
        mvaddch(player->pos.y, player->pos.x, player->ch);
        attroff(COLOR_PAIR(3) | A_BOLD);
    }
}

void drawInimigo(Entidade *player,Inimigo *inimigo,int MAP_HEIGHT, int MAP_WIDTH) // função que desenha o inimigo
{
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            if (is_enemy_visible(player, inimigo) && inimigo->ent.vida > 0)
            {
                attron(COLOR_PAIR(5) | A_BOLD);
                mvaddch(inimigo->ent.pos.y, inimigo->ent.pos.x, inimigo->ent.ch);
                attroff(COLOR_PAIR(5) | A_BOLD);
            }
            else
            {
                if (is_enemy_visible(player, inimigo)) // se a vida do inimigo for menor que 0 , i.e o inimigo está morto, a cor dele muda
                {
                    attron(COLOR_PAIR(3) | A_BOLD);
                    mvaddch(inimigo->ent.pos.y, inimigo->ent.pos.x, inimigo->ent.ch);
                    attroff(COLOR_PAIR(3) | A_BOLD);
                }
            }
        }
    }
}

void drawLvlEntry(Entidade *player,Posicao pos_lvl) // função que desenha a entrada para o proximo nivel
{
    char lvl = '>';
    if (is_visible(player, pos_lvl))
    {
        attron(COLOR_PAIR(2) | A_BOLD);
        mvaddch(pos_lvl.y, pos_lvl.x, lvl);
        attroff(COLOR_PAIR(2) | A_BOLD);
    }
}

void drawDica(Entidade *player,int MAP_HEIGHT,Posicao pos_lvl) // função que vai desenhar uma dica sobre a posição da entrada para o proximo nivel
{
    if (trigger == 1) 
    {
        if (distancia_portal(player, pos_lvl)) // a função distancia_portal (player.c) retorna 1 se o portal estiver à esquerda e 0 se estiver à direita
        {
            attron(COLOR_PAIR(7) | A_BOLD);
            mvprintw(MAP_HEIGHT + 1, 100, "THE GATE IS IN THE WEST");
            attroff(COLOR_PAIR(7) | A_BOLD);
        }
        else
        {
            attron(COLOR_PAIR(7) | A_BOLD);
            mvprintw(MAP_HEIGHT + 1, 100, "THE GATE IS IN THE EAST");
            attron(COLOR_PAIR(7) | A_BOLD);
        }
    }
}

void drawBossHealth(Inimigo *inimigo,int MAP_HEIGHT,int dungeon_level) // função que desenha, ao lado das stats, a vida do boss e o nome (respetivamente)
{
    if (dungeon_level % 5 == 0 && inimigo->ent.vida > 0) 
    {
        if (dungeon_level == 5)
        {
            attron(COLOR_PAIR(3) | A_BOLD);
            mvprintw(MAP_HEIGHT + 1, 50, "Brutalus Health: %d", inimigo->ent.vida);
            attroff(COLOR_PAIR(3) | A_BOLD);
        }
        else if (dungeon_level == 10)
        {
            attron(COLOR_PAIR(3) | A_BOLD);
            mvprintw(MAP_HEIGHT + 1, 50, "Blackheart Health: %d", inimigo->ent.vida);
            attroff(COLOR_PAIR(3) | A_BOLD);
        }
        else if (dungeon_level == 15)
        {
            attron(COLOR_PAIR(3) | A_BOLD);
            mvprintw(MAP_HEIGHT + 1, 50, "Betrayer Health: %d", inimigo->ent.vida);
            attroff(COLOR_PAIR(3) | A_BOLD);
        }
    }
}
void drawDicaBoss(Inimigo *inimigo,int MAP_HEIGHT,int dungeon_level) // apos o boss morrer, é spawnado um bau 
{
    if ((dungeon_level % 5 == 0) && inimigo->ent.vida <= 0 && pos_treasure.x < 600) // pos_treasure.x < 600 pois quando apanhamos o loot, para remover o bau do mapa, atribuimos a coordenada x = 600
    {
        attron(COLOR_PAIR(7) | A_BOLD);
        mvprintw(MAP_HEIGHT + 1, 50, "AS THE BOSS DROPS DEAD, A CHEST STARTS TO GLOW");
        mvprintw(MAP_HEIGHT + 2, 65, "Location: %d, %d", pos_treasure.x, pos_treasure.y);
        attron(COLOR_PAIR(7) | A_BOLD);
    }
}

void drawObjDamage(Entidade *player,Posicao *pos_damage) // função que desenha os objetos responsáveis por adicionar damage
{
    char obj = '+';

    for (int i = 0; i < 5; i++) // desenha 5 "espadas"
    {
        if (is_visible(player, pos_damage[i]))
        {
            attron(COLOR_PAIR(2) | A_BOLD);
            mvaddch(pos_damage[i].y, pos_damage[i].x, obj);
            attroff(COLOR_PAIR(2) | A_BOLD);
        }
    }
}

void drawtraps(Entidade *player,Posicao *pos_traps,int dungeon_level) // função que desenha traps
{
    char trap = '^'; 
    if (dungeon_level % 5 == 0)
    {
        flag_boss = 50; // no andar do boss existem mais traps (+20)
    }
    else
        flag_boss = 30;

    for (int i = 0; i < flag_boss; i++)
    {
        if (is_visible(player, pos_traps[i]))
        {
            attron(COLOR_PAIR(3) | A_BOLD);
            mvaddch(pos_traps[i].y, pos_traps[i].x, trap);
            attroff(COLOR_PAIR(3) | A_BOLD);
        }
    }
}
void drawTreasure(Entidade *player,Inimigo *inimigo,int dungeon_level) // função que desenha o tesouro 
{
    char treasure = '$';
    if (dungeon_level % 5 == 0 && inimigo->ent.vida <= 0) // apenas desenha no nível dos bosses e quando o boss morre 
    {
        if (is_visible(player, pos_treasure))
        {
            attron(COLOR_PAIR(2) | A_BOLD);
            mvaddch(pos_treasure.y, pos_treasure.x, treasure);
            attroff(COLOR_PAIR(2) | A_BOLD);
        }
    }
}

void drawMysteryBox(Entidade *player,int dungeon_level) // função que desenha uma caixa mistério
{
    char mystery = '?';
    if (dungeon_level % 5 != 0) // apenas desenha nos níveis aonde existe boss
    {
        if (is_visible(player, pos_mystery))
        {
            attron(COLOR_PAIR(2) | A_BOLD);
            mvaddch(pos_mystery.y, pos_mystery.x, mystery);
            attroff(COLOR_PAIR(2) | A_BOLD);
        }
    }
}

void drawHealFruit(Entidade *player,Posicao *pos_fruit) // função que desenha frutas responsáveis por dar vida ao jogador
{
    char fruit = 'f';

    for (int i = 0; i < 3; i++) // desenha apenas 3 
    {
        if (is_visible(player, pos_fruit[i]))
        {
            attron(COLOR_PAIR(1) | A_BOLD);
            mvaddch(pos_fruit[i].y, pos_fruit[i].x, fruit);
            attroff(COLOR_PAIR(1) | A_BOLD);
        }
    }
}

void drawEventMessage(int MAP_HEIGHT) // função que desenha mensagens por cada evento
{
    attron(COLOR_PAIR(6) | A_BOLD);
    mvprintw(MAP_HEIGHT, 100, "RECENT EVENTS:");
    attron(COLOR_PAIR(6) | A_BOLD);
    if (trigger == 3)
    {
        attron(COLOR_PAIR(7) | A_BOLD);
        mvprintw(MAP_HEIGHT + 1, 100, "YOU PICKED UP A RUSTY SWORD (+10 Damage)");
        attroff(COLOR_PAIR(7) | A_BOLD);
    }
    else if (trigger == 4)
    {
        attron(COLOR_PAIR(3) | A_BOLD);
        mvprintw(MAP_HEIGHT + 1, 100, "SOMETHING STUNG YOU (-10 Health)");
        attroff(COLOR_PAIR(3) | A_BOLD);
    }
    else if (trigger == 5)
    {
        attron(COLOR_PAIR(5) | A_BOLD);
        mvprintw(MAP_HEIGHT + 1, 100, "YOU ADVENTURED DEEP INTO THE DUNGEON");
        attroff(COLOR_PAIR(5) | A_BOLD);
    }
    else if (trigger == 6)
    {
        attron(COLOR_PAIR(1) | A_BOLD);
        mvprintw(MAP_HEIGHT + 1, 100, "THE PLAYER'S VITALITY IS RENEWED AS THE MYSTERIOUS FRUIT IS CONSUMED (+10 Health)");
        attroff(COLOR_PAIR(1) | A_BOLD);
    }
    else if (trigger == 7)
    {
        attron(COLOR_PAIR(7) | A_BOLD);
        mvprintw(MAP_HEIGHT + 1, 100, "YOU DECIDED TO OPEN THE MOLDY CHEST THAT WAS GLOWING (+250 Gold / +20 Damage)");
        attroff(COLOR_PAIR(7) | A_BOLD);
    }
    else if (trigger == 8)
    {
        attron(COLOR_PAIR(7) | A_BOLD);
        mvprintw(MAP_HEIGHT + 1, 100, "THERE'S A STRANGE BOX LYING IN THE FLOOR, DO YOU WANT TO OPEN IT? (press 'e' to open)");
        attroff(COLOR_PAIR(7) | A_BOLD);
    }
    else if (trigger == 9)
    {
        attron(COLOR_PAIR(8) | A_BOLD);
        mvprintw(MAP_HEIGHT + 1, 100, "YOU PICKED UP A HOLY SWORD AND SOME ANCIENT COINS (+150 Gold / +20 Damage)");
        attroff(COLOR_PAIR(8) | A_BOLD);
    }
    else if (trigger == 10)
    {
        attron(COLOR_PAIR(3) | A_BOLD);
        mvprintw(MAP_HEIGHT + 1, 100, "A BUNCH OF SPIDERS STUNG YOU AND STOLE SOME OF YOUR GOLD (-40 Gold / -20 Health)");
        attroff(COLOR_PAIR(3) | A_BOLD);
    }
    else if (trigger == 11)
    {
        attron(COLOR_PAIR(7) | A_BOLD);
        mvprintw(MAP_HEIGHT + 1, 100, "YOU PICKED UP AN IRON PICKAXE");
        attroff(COLOR_PAIR(7) | A_BOLD);
    }
    else if (trigger == 12)
    {
        attron(COLOR_PAIR(1) | A_BOLD);
        mvprintw(MAP_HEIGHT + 1, 100, "YOU FOUND A ROTTEN AND SMELLY SHOE (NOW YOU STINK)");
        attroff(COLOR_PAIR(1) | A_BOLD);
    }
    else if (trigger == 13)
    {
        attron(COLOR_PAIR(1) | A_BOLD);
        mvprintw(MAP_HEIGHT + 1, 100, "YOU SEARCH THE CORPSE AND FIND SOME POTIONS AND SOME COINS (+10 Health / +20 Gold)");
        attroff(COLOR_PAIR(1) | A_BOLD);
    }
    else if (trigger == 14)
    {
        attron(COLOR_PAIR(4) | A_BOLD);
        mvprintw(MAP_HEIGHT+1,100,"THE DUNGEON IS PROTECTED BY SOME WEIRD RUNES YOU CAN'T BREAK");
        attroff(COLOR_PAIR(4) | A_BOLD);
    }
    
}

int drawMenuMorte(int choice,int MAP_HEIGHT, int MAP_WIDTH)
{

    WINDOW *win = NULL;
    clear();
    if (win != NULL)
        delwin(win);

    char opcoes[2][40] = {"Play Again", "Exit"};
    int highlight = 0;
    int length1 = strlen(opcoes[0]);
    int length2 = strlen(opcoes[1]);

    WINDOW *menu_win_morte = newwin(40, 72, MAP_HEIGHT / 2 - 20, MAP_WIDTH / 2 - 36);

    initscr();
    noecho();
    cbreak();
    curs_set(0);

    refresh();
    wrefresh(menu_win_morte);
    keypad(menu_win_morte, true);

    while (1)
    {
        wattron(menu_win_morte, COLOR_PAIR(3) | A_BOLD);
        mvwprintw(menu_win_morte, 10, 0, "    ##     ##  ########  ##    ##      #######    ##  ########  #######");
        mvwprintw(menu_win_morte, 11, 0, "     ##  ##   ##    ##  ##    ##      ##    ##   ##  ##        ##    ##");
        mvwprintw(menu_win_morte, 12, 0, "       ##    ##    ##  ##    ##      ##     ##  ##  #######   ##     ##");
        mvwprintw(menu_win_morte, 13, 0, "     ##     ##    ##  ##    ##      ##    ##   ##  ##        ##    ##");
        mvwprintw(menu_win_morte, 14, 0, "   ##      ########  ########      #######    ##  ########  #######");
        wattroff(menu_win_morte, COLOR_PAIR(3) | A_BOLD);

        for (int i = 0; i < 2; i++)
        {
            if (i == highlight)
            {
                wattron(menu_win_morte, A_BOLD);
            }
            if (i == 0)
            {
                mvwprintw(menu_win_morte, i + 20, 34 - length1 / 2, "%s", opcoes[i]);
                wattroff(menu_win_morte, A_BOLD);
            }
            if (i == 1)
            {
                mvwprintw(menu_win_morte, i + 20, 34 - length2 / 2, "%s", opcoes[i]);
                wattroff(menu_win_morte, A_BOLD);
            }
        }
        choice = wgetch(menu_win_morte);

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
        return 1;
    }
    else if (highlight == 1 || choice == 'q')
    {
        return 2;
    }
    return 0;
}

void drawAll(Entidade *player,Inimigo *inimigo,int MAP_HEIGHT, int MAP_WIDTH,Terreno **map,Posicao pos_lvl,Posicao *pos_damage,Posicao *pos_traps,Posicao *pos_fruit,int dungeon_level) // função responsável por desenhar todos os componentes
{
    clear();
    refresh();
    drawMapa(player,MAP_HEIGHT,MAP_WIDTH,map,dungeon_level);
    drawHUD(player,MAP_HEIGHT,MAP_WIDTH,dungeon_level);
    drawDica(player,MAP_HEIGHT,pos_lvl);
    drawBossHealth(inimigo,MAP_HEIGHT,dungeon_level);
    drawDicaBoss(inimigo,MAP_HEIGHT,dungeon_level);
    drawtraps(player,pos_traps,dungeon_level);
    drawObjDamage(player,pos_damage);
    drawHealFruit(player,pos_fruit);
    drawTreasure(player,inimigo,dungeon_level);
    drawMysteryBox(player,dungeon_level);
    drawEventMessage(MAP_HEIGHT);
    drawLvlEntry(player,pos_lvl);
    drawInimigo(player,inimigo,MAP_HEIGHT,MAP_WIDTH);
    drawPlayer(player);
}