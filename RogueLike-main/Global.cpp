class Global
{
public:

    char map[30][120];

    int y;
    int x;

    int atc = 1;
    int hp = 320;
    int turn = 0;

    bool G_placed;
    bool P_placed;
    bool T_placed;
    bool H_placed;
    bool AE_placed;
    bool Sword_placed;

    int r_placed;

    int gold = 0;
    int dlvl = 1;
    int AE_count = 0;

    struct monsters
    {

    int y;
    int x;
    int lvl;
    int type;
    bool awake;

    };


    struct monsters monster[10];
};
