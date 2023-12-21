#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"

void copymap(MAP* destin, MAP* origin){
    destin->rows = origin->rows;
    destin->columns = origin->columns;

    allocmap(destin);
    for(int i = 0; i < origin->rows; i++){
        strcpy(destin->matrix[i], origin->matrix[i]);
    }
}

void walking(MAP* m, int xinit, int yinit, int xfinal, int yfinal){
    char character = m->matrix[xinit][yinit];
    m->matrix[xfinal][yfinal] = character;
    m->matrix[xinit][yinit] = EMPTY;
}

int iswall(MAP* m, int x, int y){
    return m->matrix[x][y] == VERTICAL_WALL ||
        m->matrix[x][y] == HORIZONTAL_WALL;

}

int ischaracter(MAP* m, char character, int x, int y){
    return m->matrix[x][y] == character;
}

int canwalk(MAP* m, char character, int x, int y){
    return isvalid(m, x, y) && !iswall(m, x, y) && !ischaracter(m, character, x, y);
}

int isvalid(MAP* m, int x, int y){
    if(x >= m->rows){
        return 0;
    }
    if(y >= m->columns){
        return 0;
    }

    return 1;
}

int isempty(MAP* m, int x, int y){
    return m->matrix[x][y] == EMPTY;
}

int findmap(MAP* m, POSITION* p, char c){
    for(int i = 0; i < m->rows; i++){
        for(int j = 0; j < m->columns; j++){
            // get player position
            if(m->matrix[i][j] == c){
                p->x = i;
                p->y = j;
                return 1;
            }
        }
    }

    return 0;
}

// dynamically allocating map's matrix
void allocmap(MAP* m){
    m->matrix = malloc(sizeof(char*) * m->rows);
    for(int i = 0; i < m->rows; i++){
        m->matrix[i] = malloc(sizeof(char) * (m->columns + 1)); // '+1' cause we're reading a file and it ends with \0
    }
}

//freeing allocated map memory
void freemap(MAP* m){
    for(int i = 0; i < m->rows; i++){
        free(m->matrix[i]);
    }
    free(m->matrix);
}

// open map's file and read it
void readmap(MAP* m){
    FILE* f;
    f = fopen("map.txt", "r");
    // check if cannot open file
    if(f == 0){
        printf("Erro na leitura do mapa");
        exit(1);
    }

    fscanf(f, "%d %d", &(m->rows), &(m->columns));

    allocmap(m);

    // read map row
    for(int i = 0; i < 5; i++){
        fscanf(f, "%s", m->matrix[i]);
    }

    fclose(f);
}
