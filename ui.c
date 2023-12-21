#include <stdio.h>
#include <stdlib.h>
#include "ui.h"
#include "map.h"

char ghost_draw[4][7] = {
    {" .-.  " },
    {"| OO| " },
    {"|   | " },
    {"'^^^' " }
};

char wall_draw[4][7] = {
    {"......" },
    {"......" },
    {"......" },
    {"......" }
};

char player_draw[4][7] = {
    {" .--. "  },
    {"/ _.-'"  },
    {"\\  '-." },
    {" '--' "  }
};

char pill_draw[4][7] = {
    {"      "},
    {" .-.  "},
    {" '-'  "},
    {"      "}
};

char empty_draw[4][7] = {
    {"      "},
    {"      "},
    {"      "},
    {"      "}
};

void printpart(char draw[4][7], int part){
    printf("%s", draw[part]);
}

// print map
void printmap(MAP* m){
    for(int i = 0; i < m->rows; i++){

        for(int part = 0; part < 4; part++){
            for(int j = 0; j < m->columns; j++){

                switch(m->matrix[i][j]){
                    case GHOST:
                        printpart(ghost_draw, part);
                        break;

                    case PLAYER:
                        printpart(player_draw, part);
                        break;

                    case PILL:
                        printpart(pill_draw, part);
                        break;

                    case VERTICAL_WALL:
                    case HORIZONTAL_WALL:
                        printpart(wall_draw, part);
                        break;

                    case EMPTY:
                        printpart(empty_draw, part);
                        break;
                }

            }

            printf("\n");
        }

    }
}
