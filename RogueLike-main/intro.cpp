#include "intro.h"
#include "imports.h"

int Intro::ui()
{
    int c = 0;

    printw("\n");
    attron(A_BOLD);
    printw("\t\t\t\t Roguelike");
    attroff(A_BOLD);

    printw("\n\n\n\tHow to play::\n\n"
           "\tYou can use arrows(key_up....) and wasd(also WASD) to move and attack\n"
           "\tAt the levels you can find heals and buffs\n"
           "\tTo get to the next level find the stairs and press shift and >\n"
           "\tPress 'n' to start a new game.\n"
           "\tPress 'ESC' to quit the game\n\n"
           "\tLegend:\n\n"
           "\t1)ABCDE.... - mobs. Depending on the letter it has different HP and attack\n"
           "\t2)H - Heal\n"
           "\t3)S - Sword. It gives you an attack buff for the rest of the run.\n"
           "\t4)^ - Traps. If you step on them you or the mobs will take damage\n"
           "\t5)0 - Aegis of the Immortal. Gives you extra life");


    c = getch();

}
