#include "Monster.h"
#include "imports.h"

int Monster::turn(int rows, int cols)
{
    int dist_y;
    int dist_x;

    for(int m = 0; m < 15; m++)
    {
        if(Singleton::getInstance() -> monster[m].lvl < 1)
            continue;

        dist_y = abs(Singleton::getInstance() -> monster[m].y - Singleton::getInstance() -> y);
        dist_x = abs(Singleton::getInstance() -> monster[m].x - Singleton::getInstance() -> x);

        if(dist_y < 5 && dist_x < 5)
            Singleton::getInstance() -> monster[m].awake = 1;

        if(Singleton::getInstance() -> monster[m].awake == 0)
            continue;

        int dir_y = Singleton::getInstance() -> monster[m].y;
        int dir_x = Singleton::getInstance() -> monster[m].x;

        //’одьба монстров

        if(dist_y > dist_x)
        {
            //ѕр€олинейно
            if(dir_y < Singleton::getInstance() -> y)
                dir_y++;

            else
                dir_y--;
        }
        else
        {
            if(dir_x < Singleton::getInstance() -> x)
                dir_x++;

            else
                dir_x--;
        }
        if(Singleton::getInstance() -> map[dir_y][dir_x] == '#' || Singleton::getInstance() -> map[dir_y][dir_x] == '%')
        {
            //ƒиагональ
            dir_y = Singleton::getInstance() -> monster[m].y;
            dir_x = Singleton::getInstance() -> monster[m].x;

            if(dir_y < Singleton::getInstance() -> y)
                dir_y++;

            else
                dir_y--;

            if(dir_x < Singleton::getInstance() -> x)
                dir_x++;

            else
                dir_x--;
        }
        if(Singleton::getInstance() -> map[dir_y][dir_x] == '#' || Singleton::getInstance() -> map[dir_y][dir_x] == '%')
        {
            dir_y = Singleton::getInstance() -> monster[m].y;
            dir_x = Singleton::getInstance() -> monster[m].x;
            //ѕр€олинейно
            if(dist_y > dist_x)
                if(dir_y > Singleton::getInstance() -> y)
                    dir_y++;

                else
                    dir_y--;

            else

            if(dir_x > Singleton::getInstance() -> y)
                dir_x++;

            else
                dir_x--;
        }

        if(dist_y < 2 && dist_x < 2)
        {
            Singleton::getInstance() -> hp -= (rand() % 2) + Singleton::getInstance() -> monster[m].type - 64;
        }
        else if(Singleton::getInstance() -> map[dir_y][dir_x] == ' ')
        {
            Singleton::getInstance() -> map[Singleton::getInstance() -> monster[m].y][Singleton::getInstance() -> monster[m].x] = ' ';
            Singleton::getInstance() -> monster[m].y = dir_y;
            Singleton::getInstance() -> monster[m].x = dir_x;
            Singleton::getInstance() -> map[Singleton::getInstance() -> monster[m].y][Singleton::getInstance() -> monster[m].x] = 'G';
        }
        else if(Singleton::getInstance() -> map[dir_y][dir_x] == '^')
        {
            Singleton::getInstance() -> monster[m].lvl -=30;
            if(Singleton::getInstance() -> monster[m].lvl < 0)
                Singleton::getInstance() -> map[Singleton::getInstance() -> monster[m].y][Singleton::getInstance() -> monster[m].x] = ' ';
        }
    }
}
