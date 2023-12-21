#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pacman.h"
#include "map.h"
#include "ui.h"

MAP m;
POSITION player;
int haspill = 0;


int ghostdirection(int currentx, int currenty, int* xdestin, int* ydestin){
    int options[4][2] = {
        {currentx, currenty + 1},
        {currentx + 1, currenty},
        {currentx, currenty - 1},
        {currentx - 1, currenty}
    };

    srand(time(0));
    for(int i = 0; i < 10; i++){
        int pos = rand() % 4;

        if(canwalk(&m, GHOST, options[pos][0], options[pos][1])){
            *xdestin = options[pos][0];
            *ydestin = options[pos][1];

            return 1;
        }
    }

    return 0;
}

void ghosts(){
    MAP copy;
    copymap(&copy, &m);

    for(int i = 0; i < m.rows; i++){
        for(int j = 0; j < m.columns; j++){

            if(copy.matrix[i][j] == GHOST){

                int xdestin;
                int ydestin;

                int found = ghostdirection(i, j, &xdestin, &ydestin);

                if(found){
                    walking(&m, i, j, xdestin, ydestin);
                }
            }
        }
    }

    freemap(&copy);
}

int endgame(){
    POSITION pos;
    int playerinmap = findmap(&m, &pos, PLAYER);
    return !playerinmap;
}

int isdir(char dir){
    return dir == LEFT ||
    dir == UP ||
    dir == DOWN ||
    dir == RIGHT;
}

void move(char dir){

    if(!isdir(dir)){
        return;
       }

    int nextx = player.x;
    int nexty = player.y;

    // change pacman pos
    switch(dir){
        case LEFT:
            nexty--;
            break;
        case UP:
            nextx--;
            break;
        case DOWN:
            nextx++;
            break;
        case RIGHT:
            nexty++;
            break;
    }

    // Check walls and limits
    if(!canwalk(&m, PLAYER, nextx, nexty)){
        return;
    }

    //  Pill
    if(ischaracter(&m, PILL, nextx, nexty)){
        haspill = 1;
    }

    // walking and clear 'old pacman' otherwise, it'd have two pacmans
    walking(&m, player.x, player.y, nextx, nexty);
    player.x = nextx;
    player.y = nexty;

}

void explodepilldir(){

    if(!haspill) return;

    explodepill(player.x, player.y, 0, 1, 3); //RIGHT
    explodepill(player.x, player.y, 0, -1, 3); //LEFT
    explodepill(player.x, player.y, 1, 0, 3); //UP
    explodepill(player.x, player.y, -1, 0, 3); //DOWN

    haspill = 0;
}

void explodepill(int x, int y, int sumx, int sumy, int qtd){

    if(qtd == 0) return;

    int newx = x + sumx;
    int newy = y + sumy;

    if(!isvalid(&m, newx, newy)) return;
    if(iswall(&m, newx, newy)) return;

    m.matrix[newx][newy] = EMPTY;
    explodepill(newx, newy, sumx, sumy, qtd - 1);
}

int main()
{

    readmap(&m);
    findmap(&m, &player, PLAYER);

    do{

        printf("Tem pilula: %s\n", (haspill ? "SIM" : "NAO"));
        printmap(&m);

        char key;
        scanf(" %c", &key);
        move(key);
        if(key == BOMB) explodepilldir(player.x, player.y, 3);

        ghosts();

    }while(!endgame());

    freemap(&m);

    return 0;
}
