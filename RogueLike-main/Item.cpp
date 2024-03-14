#include "Item.h"
#include "imports.h"

int Item::get(int rows, int cols)
{
    if(Singleton::getInstance() -> map[Singleton::getInstance() -> y][Singleton::getInstance() -> x] == 'H')
    {
        Singleton::getInstance() -> hp += 1000*Singleton::getInstance() -> dlvl;
        Singleton::getInstance() -> map[Singleton::getInstance() -> y][Singleton::getInstance() -> x] = ' ';
        Singleton::getInstance() -> H_placed = 0;
    }
    if(Singleton::getInstance() -> map[Singleton::getInstance() -> y][Singleton::getInstance() -> x] == 'S')
    {
        Singleton::getInstance() -> atc *=1.5;
        Singleton::getInstance() -> map[Singleton::getInstance() -> y][Singleton::getInstance() -> x] = ' ';
        Singleton::getInstance() -> Sword_placed = 1;
    }
    if(Singleton::getInstance() -> map[Singleton::getInstance() -> y][Singleton::getInstance() -> x] == '0')
    {
        Singleton::getInstance() -> map[Singleton::getInstance() -> y][Singleton::getInstance() -> x] = ' ';
        Singleton::getInstance() -> AE_count++;
        Singleton::getInstance() -> AE_placed = 1;
    }

}
