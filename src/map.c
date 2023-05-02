#include <dungeon.h>

int WallCount(Terreno **map, int r, int col, int row) {
    int x, y;
    int wall_count = 0;

            for (y = col - r; y <= col + r; y++) {
                for (x = row - r; x <= row + r; x++) {
                    if ((y >= 1) && (y < MAP_HEIGHT-1) && (x >= 1) && (x < MAP_WIDTH - 1)) {
                        if (map[y][x].ch == '#') {
                            wall_count++;
                     }
                 }
            }
        } 
return wall_count;
}



Terreno** mapborder(Terreno **map) {
    int x ,y;

    for(y = 0; y < MAP_HEIGHT; y++){
        for(x = 0; x < MAP_WIDTH; x++){
            if(y == 0 || y == MAP_HEIGHT - 1) {
                map[y][x].ch = '#';
                map[y][x].walkable =false;               
            }
            if(y == 1 || y == MAP_HEIGHT -2){
                map[y][x].ch = '#';
                map[y][x].walkable =false;
            }
        }
    }
    for(x = 0; x < MAP_WIDTH; x++){
        for(y = 0; y < MAP_HEIGHT; y++){
            if(x == 0 || x == MAP_WIDTH - 1) {
                map[y][x].ch = '#';
                map[y][x].walkable =false;               
            }
            if(x == 1 || x == MAP_WIDTH -2){
                map[y][x].ch = '#';
                map[y][x].walkable =false;
            }
        }
    }
return map;
}

Terreno **generate_map() {
    int i, j;
    Terreno **map = calloc(MAP_HEIGHT, sizeof(Terreno *));

    if(map == NULL) printf("Error no memory allocated");

    for (i = 0; i < MAP_HEIGHT; i++) {
        map[i] = calloc(MAP_WIDTH, sizeof(Terreno));
        if(map[i] == NULL) printf("Error no memory allocated"); 
    }

    for (i = 2; i < MAP_HEIGHT-2; i++) {
        for (j = 2; j < MAP_WIDTH-2; j++) {
            if (rand() % 100 < 45) {
                map[i][j].ch = '#';
                map[i][j].walkable = false;
            } else {
                map[i][j].ch = '.';
                map[i][j].walkable = true;
            }
        }
    }

mapborder(map);

int fst = 2, snd = 3;

while(fst > 0) {

for (i = 0; i < MAP_HEIGHT; i++) {
    for (j = 0; j < MAP_WIDTH; j++) {
        if(WallCount(map, 1, i, j) >= 5 || WallCount(map, 2, i, j) <= 2){
            map[i][j].ch = '#';
            map[i][j].walkable = false;
        }else {
            map[i][j].ch = '.';
            map[i][j].walkable = true;
        }        
      }
    }
fst--;    
  }

mapborder(map);

while(snd > 0) {

for (i = 0; i < MAP_HEIGHT; i++) {
    for (j = 0; j < MAP_WIDTH; j++) {
        if(WallCount(map, 1, i, j) >= 5) {
            map[i][j].ch = '#';
            map[i][j].walkable = false;
        }else {
            map[i][j].ch = '.';
            map[i][j].walkable = true;
        }
      }
    } 
snd--;    
}

mapborder(map);

return map;
}


Posicao setupMap(Terreno **map)
{
    Posicao pos_inicial;
    int i, j;
    
    for (int i = 0; i < MAP_HEIGHT - 1; i++) {
        for (int j = 0 ; j < MAP_WIDTH - 1; j++) {
            if(WallCount(map, 2, i, j) == 0 && map[i][j].ch == '.'){
                pos_inicial.y = i;
                pos_inicial.x = j;
                break;
            } 
        }
    }
    return pos_inicial;
}

void FreeMapa(Terreno **map) {
        for(int i = 0; i < MAP_HEIGHT; i++) {
        free(map[i]);
    }
    free(map);
}

