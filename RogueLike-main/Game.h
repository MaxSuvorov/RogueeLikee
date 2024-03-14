#ifndef CGAME_GAME_H
#define CGAME_GAME_H

class Game {
public:
    int action(int c, int rows, int cols);

    int loop(int c, int rows, int cols);

    int battle(int rows, int cols, int dir_y, int dir_x);

    int respawn(int rows, int cols);
};


#endif //CGAME_GAME_H
