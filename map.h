#ifndef _MAP_H_
#define _MAP_H_

#define PLAYER '@'
#define GHOST 'G'
#define EMPTY '.'
#define VERTICAL_WALL '|'
#define HORIZONTAL_WALL '-'
#define PILL 'P'

typedef struct map MAP;
typedef struct position POSITION;

int ischaracter(MAP* m, char character, int x, int y);
int iswall(MAP* m, int x, int y);
int findmap(MAP* m, POSITION* p, char c);
int canwalk(MAP* m, char character, int x, int y);
void copymap(MAP* destin, MAP* origin);
void walking(MAP* m, int xinit, int yinit, int xfinal, int yfinal);
void freemap(MAP* m);
void readmap(MAP* m);
void allocmap(MAP* m);
int isvalid(MAP* m, int x, int y);
int isempty(MAP* m, int x, int y);

struct map{
    char** matrix;
    int rows;
    int columns;
};

struct position{
    int x;
    int y;
};

#endif
