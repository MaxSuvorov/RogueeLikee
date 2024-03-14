#include "imports.h"
#include "Game.h"
#include "Trap.h"
#include "Map.h"
#include "Monster.h"
#include "Item.h"
#include "intro.h"

Game::loop(int c, int rows, int cols)
{
    int new_lvl;

    Map Map;
    Monster Monsters;
    Trap Trap;
    Item Items;


    srand(time(NULL));

    Map.generate(rows, cols);

    this->respawn(rows, cols);


    if(c !=0)
    {
        new_lvl = this->action(c, rows, cols);
    }

    Monsters.turn(rows, cols);
    Trap.damage(rows, cols);
    Items.get(rows, cols);

    Map.draw(rows, cols);

    attron(A_BOLD);
    mvaddch(Singleton::getInstance() -> y,Singleton::getInstance() -> x, '@');
    attroff(A_BOLD);

    if (new_lvl)
    {
        clear();
        mvprintw(15, 37, "Welcome to level: %d. Press Any Key to Continue", Singleton::getInstance() -> dlvl++);
        getch();
        clear();
        if (Singleton::getInstance() -> dlvl  > 2)
        {
            Singleton::getInstance() -> gold += 1000*Singleton::getInstance() -> dlvl;
            mvprintw(16, 37, "You received %d for moving to a new lvl", 1000*Singleton::getInstance() -> dlvl);
            getch();
            clear();
        }


    }
    if(Singleton::getInstance() -> hp <= 1 && Singleton::getInstance() -> AE_count > 0)
    {
        Singleton::getInstance() -> hp += 30 + Singleton::getInstance() -> dlvl;
        Singleton::getInstance() -> AE_count--;
    }
    if(Singleton::getInstance() -> hp < 1 && Singleton::getInstance() -> AE_count == 0)
    {
        clear();
        mvprintw(15, 50, "YOU DIED");
        mvprintw(16, 47, "You had %d Singleton::getInstance() -> gold", Singleton::getInstance() -> gold);
        mvprintw(17, 42, "You've been living %d moves", Singleton::getInstance() -> turn);
        printw("\n\n\t\t\t\t\ Try again!");
    }


    c = getch();

    return c;
}

int Game::battle(int rows, int cols, int dir_y, int dir_x)
{
    int gold_per_monster = 0;

    for(int m = 0; m < 15; m++)
    {
        if(dir_y == Singleton::getInstance() -> monster[m].y && dir_x == Singleton::getInstance() -> monster[m].x)
        {
            if (Singleton::getInstance() -> monster[m].lvl <= 0)
            {
                Singleton::getInstance() -> map[dir_y][dir_x] = ' ';
                gold_per_monster = rand()% 3 * Singleton::getInstance() -> monster[m].type * Singleton::getInstance() -> dlvl;
                Singleton::getInstance() -> gold += gold_per_monster;
            }
            else
                Singleton::getInstance() -> monster[m].lvl -=Singleton::getInstance() -> atc;
            break;
        }
    }
    return 0;
}

int Game::respawn(int rows, int cols)
{
    if(!Singleton::getInstance() -> G_placed)
    {
        int Gy;
        int Gx;

        for(int m = 0; m < 10; m++)
        {
            do
            {
                Gy = rand() % rows;
                Gx = rand() % cols;

            }
            while(Singleton::getInstance() -> map[Gy][Gx] != ' ');

            Singleton::getInstance() -> monster[m].y = Gy;
            Singleton::getInstance() -> monster[m].x = Gx;
            Singleton::getInstance() -> monster[m].lvl = rand() % Singleton::getInstance() -> dlvl + 2;

            if (Singleton::getInstance() -> map[Singleton::getInstance() -> monster[m].y][Singleton::getInstance() -> monster[m].x] == '^')
                Singleton::getInstance() -> monster[m].lvl -=10;
            if (Singleton::getInstance() -> dlvl == 1 && !(rand() % 4))
                Singleton::getInstance() -> monster[m].lvl = 1;
            if (rand() % 3)
                Singleton::getInstance() -> monster[m].lvl = Singleton::getInstance() -> dlvl + 2;
            Singleton::getInstance() -> monster[m].type = rand() % Singleton::getInstance() -> dlvl +65;

            Singleton::getInstance() -> monster[m].awake = 0;
            Singleton::getInstance() -> map[Singleton::getInstance() -> monster[m].y][Singleton::getInstance() -> monster[m].x] = 'G';
        }
        Singleton::getInstance() -> G_placed = 1;
    }

    if(!Singleton::getInstance() -> T_placed)
    {
        int Ty;
        int Tx;

        if(Singleton::getInstance() -> turn % 10 == 0 && Singleton::getInstance() -> turn != 0 && Singleton::getInstance() -> map[Singleton::getInstance() -> y][Singleton::getInstance() -> x+1] != '#' &&
           Singleton::getInstance() -> map[Singleton::getInstance() -> y][Singleton::getInstance() -> x-1] != '#' && Singleton::getInstance() -> map[Singleton::getInstance() -> y-1][Singleton::getInstance() -> x] != '#' &&
           Singleton::getInstance() -> map[Singleton::getInstance() -> y+1][Singleton::getInstance() -> x] != '#')
        {
            for(int m = 0; m < 2; m++)
            {
                do
                {
                    Ty = rand() % rows;
                    Tx = rand() % cols;

                }
                while(Singleton::getInstance() -> map[Ty][Tx] != ' ');
                Singleton::getInstance() -> map[Ty][Tx] = '^';
            }
        }
    }

    if (!Singleton::getInstance() -> P_placed)
    {
        do
        {
            Singleton::getInstance() -> y = rand() % rows;
            Singleton::getInstance() -> x= rand() % cols;

        }
        while(Singleton::getInstance() -> map[Singleton::getInstance() -> y][Singleton::getInstance() -> x] == '#' || Singleton::getInstance() -> map[Singleton::getInstance() -> y][Singleton::getInstance() -> x] == '%');
        Singleton::getInstance() -> P_placed = 1;
    }
    if (!Singleton::getInstance() -> AE_placed)
    {
        int AEy;
        int AEx;
        do
        {
            AEy = rand() % rows;
            AEx = rand() % cols;

        }
        while(Singleton::getInstance() -> map[AEy][AEx] == '#' || Singleton::getInstance() -> map[AEy][AEx] == '%');
        Singleton::getInstance() -> map[AEy][AEx] = '0';
        if(rand() % 1000)
            Singleton::getInstance() -> AE_placed = 1;
    }
    if(!Singleton::getInstance() -> H_placed)
    {
        int Hy, Hx;

        do
        {
            Hy = rand() % rows;
            Hx = rand() % cols;

        }
        while(Singleton::getInstance() -> map[Hy][Hx] == '#' || Singleton::getInstance() -> map[Hy][Hx] == '%');
        Singleton::getInstance() -> map[Hy][Hx] = 'H';
        Singleton::getInstance() -> H_placed = 1;

    }

    if(!Singleton::getInstance() -> Sword_placed)
    {
        int Sy, Sx;

        do
        {
            Sy = rand() % rows;
            Sx = rand() % cols;

        }
        while(Singleton::getInstance() -> map[Sy][Sx] == '#' || Singleton::getInstance() -> map[Sy][Sx] == '%');
        Singleton::getInstance() -> map[Sy][Sx] = 'S';
        Singleton::getInstance() -> Sword_placed = 1;
    }
    return 0;
}

int Game::action(int c, int rows, int cols)
{
    int dir_y = Singleton::getInstance() -> y;
    int dir_x = Singleton::getInstance() -> x;

    if(c == KEY_UP || c == 'w' || c == 'W')
    {
        dir_y--;
        if(Singleton::getInstance() -> map[dir_y][dir_x] != '#' || Singleton::getInstance() -> map[dir_y][dir_x] != '%')
            Singleton::getInstance() -> turn++;
    }
    else if (c == KEY_DOWN || c == 's' || c == 'S')
    {
        dir_y++;
        if(Singleton::getInstance() -> map[dir_y+1][dir_x] != '#' || Singleton::getInstance() -> map[dir_y][dir_x] != '%')
            Singleton::getInstance() -> turn++;
    }
    else if (c == KEY_LEFT || c == 'a' || c == 'A')
    {
        dir_x--;
        if(Singleton::getInstance() -> map[dir_y][dir_x] != '#' || Singleton::getInstance() -> map[dir_y][dir_x] != '%')
            Singleton::getInstance() -> turn++;
    }
    else if (c == KEY_RIGHT || c == 'd'  || c == 'D')
    {
        dir_x++;
        if(Singleton::getInstance() -> map[dir_y][dir_x] != '#' || Singleton::getInstance() -> map[dir_y][dir_x] != '%')
            Singleton::getInstance() -> turn++;
    }
    else if (c == '>' && Singleton::getInstance() -> map[Singleton::getInstance() -> y][Singleton::getInstance() -> x] == '>')
    {
        Singleton::getInstance() -> G_placed = 0;
        Singleton::getInstance() -> P_placed = 0;
        Singleton::getInstance() -> r_placed = 0;
        Singleton::getInstance() -> H_placed = 0;
        Singleton::getInstance() -> AE_placed = 0;
        Singleton::getInstance() -> Sword_placed = 0;
        Singleton::getInstance() -> atc += rand() % 3 + 1;
        Singleton::getInstance() -> hp += rand() % 10 + 10;
        return 1;
    }

    if(Singleton::getInstance() -> map[dir_y][dir_x] == ' ' || Singleton::getInstance() -> map[dir_y][dir_x] == '>' || Singleton::getInstance() -> map[dir_y][dir_x] == '^' ||
       Singleton::getInstance() -> map[dir_y][dir_x] == 'H' || Singleton::getInstance() -> map[dir_y][dir_x] == 'S' || Singleton::getInstance() -> map[dir_y][dir_x] == '0')
    {
        Singleton::getInstance() -> y = dir_y;
        Singleton::getInstance() -> x = dir_x;
    }

    else if(Singleton::getInstance() -> map[dir_y][dir_x] == 'G')
        this->battle(rows, cols, dir_y, dir_x);

    return 0;
}
