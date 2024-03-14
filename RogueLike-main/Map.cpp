#include "Map.h"
#include "imports.h"

int Map::generate(int rows, int cols){
    if (!Singleton::getInstance() -> r_placed)
    {
        int ry, rx; // room coords
        int r_size_y, r_size_x; // room size
        int r_center_y, r_center_x;
        int r_old_center_y, r_old_center_x;
        int room_num = rand() % 8    + 5;

        bool collisian;
        //ќтрисовка карты и ее границ
        for (int wall = 0; wall <= rows; wall++)
        {
            for (int floor = 0; floor <= cols; floor++)
            {
                //границы
                if (wall == 0 || wall == rows - 1 || wall == 1 ||
                    floor == 0 || floor == cols)
                    Singleton::getInstance() -> map[wall][floor] = '%';
                    // стены
                else
                    Singleton::getInstance() -> map[wall][floor] = '#';
            }
        }
        while(Singleton::getInstance() -> r_placed < room_num)
        {
            int try_counter = 0;

            do
            {
                collisian = 0;

                ry = rand() % (rows - 3) + 1;
                rx = rand() % (cols - 3) + 1;

                r_size_y = rand() % 7 + 6;
                r_size_x = rand() % 7    + 6;

                try_counter++;

                if(try_counter > 100)
                {
                    ry = 3;
                    rx = 3;
                    r_size_y = 3;
                    r_size_x = 3;
                    break;
                }

                for(int wall = ry; wall <= ry + r_size_y; wall++)
                {

                    for(int floor = rx; floor <= rx + r_size_x; floor++)
                    {
                        if (Singleton::getInstance() -> map[wall][floor] == '%' || Singleton::getInstance() -> map[wall][floor] == ' ' ||
                            Singleton::getInstance() -> map[wall-2][floor] == ' ' || Singleton::getInstance() -> map[wall][floor-2] == ' ' ||
                            Singleton::getInstance() -> map[wall+2][floor] == ' ' || Singleton::getInstance() -> map[wall][floor+2] == ' ')
                        {
                            collisian = 1;
                            wall = ry + r_size_y + 1;
                            break;
                        }
                    }
                }
            }
            while (collisian == 1);

            for(int wall = ry; wall <= ry + r_size_y; wall++)
            {
                for(int floor = rx; floor <= rx + r_size_x; floor++)
                {
                    if (Singleton::getInstance() -> map[wall][floor] == '%')
                    {
                        wall = ry + r_size_y + 1;
                        break;
                    }
                    else
                        Singleton::getInstance() -> map[wall][floor] = ' ';
                }
            }
            Singleton::getInstance() -> r_placed++;

            if(Singleton::getInstance() -> r_placed > 1)
            {
                r_old_center_y = r_center_y;
                r_old_center_x = r_center_x;
            }

            r_center_y = ry + (r_size_y / 2);
            r_center_x = rx + (r_size_x / 2);

            if(Singleton::getInstance() -> r_placed > 1)
            {
                int path_y;

                for (path_y = r_old_center_y; path_y != r_center_y; )
                {
                    if(Singleton::getInstance() -> map[path_y][r_old_center_x != '%'])
                        Singleton::getInstance() -> map[path_y][r_old_center_x] = ' ';

                    if(r_old_center_y < r_center_y)
                        path_y++;
                    else if(r_old_center_y > r_center_y)
                        path_y--;
                }
                for (int path_x = r_old_center_x; path_x != r_center_x; )
                {
                    if (Singleton::getInstance() -> map[path_y][path_x] != '%')
                        Singleton::getInstance() -> map[path_y][path_x] = ' ';

                    if (r_old_center_x < r_center_x)
                        path_x++;
                    else if (r_old_center_x > r_center_x)
                        path_x--;

                }
            }
        }
        int Sy, Sx;
        do
        {
            Sy = rand() % (rows - 3) + 1;
            Sx = rand() % (cols - 3) + 1;
        }
        while(Singleton::getInstance() -> map[Sy][Sx] != ' ');
        Singleton::getInstance() -> map[Sy][Sx] = '>';

    }
    return 0;
}

int Map::draw(int rows, int cols)
{


    for (int wall = 0; wall <= rows; wall++)
    {
        for (int floor = 0; floor <= cols; floor++)
        {
            if (wall == 0 || wall == rows)
                mvaddch(wall, floor,' ');
            else if (Singleton::getInstance() -> map[wall][floor] == 'H' && ((wall > Singleton::getInstance() -> y - 5 && floor > Singleton::getInstance() -> x - 5) &&
                                                 (wall < Singleton::getInstance() -> y + 5 && floor < Singleton::getInstance() -> x + 5)))
            {
                attron(A_BOLD | COLOR_PAIR(GREEN));
                mvaddch(wall, floor, 'H');
                attroff(A_BOLD | COLOR_PAIR(GREEN));
            }
            else if (Singleton::getInstance() -> map[wall][floor] == 'S'&& ((wall > Singleton::getInstance() -> y - 5 && floor > Singleton::getInstance() -> x - 5) &&
                                                (wall < Singleton::getInstance() -> y + 5 && floor < Singleton::getInstance() -> x + 5)))
            {
                attron(A_BOLD | COLOR_PAIR(GREEN));
                mvaddch(wall, floor, 'S');
                attroff(A_BOLD | COLOR_PAIR(GREEN));
            }
            else if (Singleton::getInstance() -> map[wall][floor] == '>' && ((wall > Singleton::getInstance() -> y - 5 && floor > Singleton::getInstance() -> x - 5) &&
                                                 (wall < Singleton::getInstance() -> y + 5 && floor < Singleton::getInstance() -> x + 5)))
            {
                attron(A_BOLD);
                mvaddch(wall, floor, '>');
                attroff(A_BOLD);
            }
            else if (Singleton::getInstance() -> map[wall][floor] == '^' && ((wall > Singleton::getInstance() -> y - 5 && floor > Singleton::getInstance() -> x - 5) &&
                                                 (wall < Singleton::getInstance() -> y + 5 && floor < Singleton::getInstance() -> x + 5)))
            {
                attron(A_BOLD | COLOR_PAIR(YELLOW));
                mvaddch(wall, floor, '^');
                attroff(A_BOLD | COLOR_PAIR(YELLOW));
            }
            else if (Singleton::getInstance() -> map[wall][floor] == '0' && ((wall > Singleton::getInstance() -> y - 5 && floor > Singleton::getInstance() -> x - 5) &&
                                                 (wall < Singleton::getInstance() -> y + 5 && floor < Singleton::getInstance() -> x + 5)))
            {
                attron(A_BOLD | COLOR_PAIR(BLUE));
                mvaddch(wall, floor, '0');
                attroff(A_BOLD | COLOR_PAIR(BLUE));
            }
            else if (Singleton::getInstance() -> map[wall][floor] == '%')
            {
                attroff(A_BOLD | COLOR_PAIR(YELLOW));
                mvaddch(wall, floor,'%');
                attroff(A_BOLD | COLOR_PAIR(YELLOW));
            }
            else if (Singleton::getInstance() -> map[wall][floor] == ' ')

                mvaddch(wall, floor,' ');
            else if (Singleton::getInstance() -> map[wall][floor] == '#' && ((wall > Singleton::getInstance() -> y - 5 && floor > Singleton::getInstance() -> x - 5) &&
                                                 (wall < Singleton::getInstance() -> y + 5 && floor < Singleton::getInstance() -> x + 5)))
                mvaddch(wall, floor, '#');
            else if (Singleton::getInstance() -> map[wall][floor] == 'G' && ((wall > Singleton::getInstance() -> y - 5 && floor > Singleton::getInstance() -> x - 5) &&
                                                 (wall < Singleton::getInstance() -> y + 5 && floor < Singleton::getInstance() -> x + 5) && (wall != '#' & floor != '#')))
            {
                for(int m = 0; m < 10; m++)
                {
                    if(Singleton::getInstance() -> monster[m].y == wall && Singleton::getInstance() -> monster[m].x == floor)
                    {
                        if(Singleton::getInstance() -> monster[m].lvl < Singleton::getInstance() -> dlvl / 2 + 2)
                        {
                            attron(COLOR_PAIR(RED));
                            mvaddch(wall, floor, Singleton::getInstance() -> monster[m].type);
                        }
                        else if(Singleton::getInstance() -> monster[m].lvl < Singleton::getInstance() -> dlvl + 2)
                        {
                            attron(COLOR_PAIR(YELLOW));
                            mvaddch(wall, floor, Singleton::getInstance() -> monster[m].type);
                        }
                        else
                            mvaddch(wall, floor, Singleton::getInstance() -> monster[m].type);
                    }
                    standend();
                }
            }
        }
    }
    mvprintw(0 , 0, "Turn Number: %d \t\t\t\t\t\ RogueLike!", Singleton::getInstance() -> turn);
    mvprintw(29, 0, "Gold: %d \t HP: %d  \t Att: %d \t lvl: %d \t Aegis: %d", Singleton::getInstance() -> gold, Singleton::getInstance() -> hp, Singleton::getInstance() -> atc, Singleton::getInstance() -> dlvl, Singleton::getInstance() -> AE_count);

    return 0;
}
