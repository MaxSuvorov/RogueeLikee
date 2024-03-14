#ifndef CGAME_SINGLETON_H
#define CGAME_SINGLETON_H

struct MonstersST{
    int y;
    int x;
    int lvl;
    int type;
    bool awake;
};

class Singleton
{
private:
    static Singleton * p_instance;
    // Конструкторы и оператор присваивания недоступны клиентам
    Singleton() {}
    Singleton( const Singleton& );
    Singleton& operator=( Singleton& );
public:
    static Singleton * getInstance() {
        if(!p_instance)
            p_instance = new Singleton();
        return p_instance;
    }


    char map[30][120];

    int y;
    int x;

    int atc = 1;
    int hp = 40;
    int max_hp = 40;
    int turn = 0;

    bool G_placed;
    bool P_placed;
    bool T_placed;
    bool  H_placed;
    bool AE_placed;
    bool Sword_placed;

    int r_placed;

    int gold = 0;
    int dlvl = 1;
    int AE_count = 0;

    struct MonstersST monster[10];
};


#endif //CGAME_SINGLETON_H
