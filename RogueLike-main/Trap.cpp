#include "Trap.h"
#include "imports.h"

int Trap::damage(int rows, int cols) {
    if (Singleton::getInstance() -> map[Singleton::getInstance() -> y][Singleton::getInstance() -> x] == '^')
        Singleton::getInstance() -> hp -= rand() % Singleton::getInstance() -> dlvl + 2;
    return 0;
}
