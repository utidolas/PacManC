#ifndef PACMAN_H_
#define PACMAN_H_

#define UP 'w'
#define DOWN 's'
#define RIGHT 'd'
#define LEFT 'a'
#define BOMB 'b'

int ghostdirection(int currentx, int currenty, int* xdestin, int* ydestin);
void explodepill(int x, int y, int sumx, int sumy, int qtd);
void explodepilldir();
void ghosts();
int endgame();
void move(char dir);
void move(char dir);

#endif
