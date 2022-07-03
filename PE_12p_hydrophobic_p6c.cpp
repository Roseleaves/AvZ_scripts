// 水无12炮
// dodecannoned hydrophobics
#include "avz.h"

using namespace AvZ;

void Script()
{
    OpenMultipleEffective();
    SetZombies({
        GIGA_GARGANTUAR,      // 红眼巨人
        GARGANTUAR,           // 巨人
        DANCING_ZOMBIE,       // MJ
        POLE_VAULTING_ZOMBIE, // 撑杆
        ZOMBONI,              // 冰车
        DIGGER_ZOMBIE,        // 矿工
        LADDER_ZOMBIE,        // 梯子
        DOLPHIN_RIDER_ZOMBIE, // 海豚
        POGO_ZOMBIE,          // 跳跳
        BUCKETHEAD_ZOMBIE,    // 铁桶
        BUNGEE_ZOMBIE,        // 小偷
    });

    SelectCards({
        ICE_SHROOM,
        CHERRY_BOMB,
        SQUASH,
        BLOVER,
        FLOWER_POT,
        SCAREDY_SHROOM,
        SUNFLOWER,
        SUN_SHROOM,
        PUFF_SHROOM,
        M_PUFF_SHROOM,
    });

    pao_operator.resetPaoList({
        {1, 1},
        {2, 1},
        {5, 1},
        {6, 1},
        {1, 5},
        {2, 5},
        {5, 5},
        {6, 5},
        {1, 7},
        {2, 7},
        {5, 7},
        {6, 7},
    });

    const int HURT_ALL_POLES = 359,
              PAO_ANIMATION = 373,
              ICE_ANIMATION = 100;

    // 荼蘼的14炮节奏的垫材使用较为复杂. 因此后面集中处置垫材。
    // PD / Pc
    for (auto wave : {1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 12, 13, 14, 15, 16, 17, 18, 19}) {
        SetTime(230 - PAO_ANIMATION, wave),
            pao_operator.pao(5, 9);
        SetTime(HURT_ALL_POLES - PAO_ANIMATION, wave),
            pao_operator.pao(2, 9);
        SetTime(190, wave),
            Card(8 + wave % 3, 1, 9), // 9,10,8,9,10,8...
            Card(7 - wave % 3, 2, 9); // 6, 5,7,6, 5,7...
        SetTime(210, wave),
            Shovel(1, 9),
            Shovel(2, 9);
        SetTime(535, wave),
            Card(8 + (wave - 1) % 3, 5, 9), // 8,9,10,8,9,10...
            Card(6 - (wave + 1) % 3, 6, 9); // 4,6, 5,4,6,5...
        SetTime(140, wave + 1),
            Shovel(5, 9),
            Shovel(6, 9);
    }

    // wave = 10
    SetTime(230 - PAO_ANIMATION + 40, 10),
        pao_operator.pao(5, 9),
        pao_operator.pao(2, 9),
        Card(BLOVER, 1, 9);
    SetTime(HURT_ALL_POLES - ICE_ANIMATION + 40, 10),
        Card(CHERRY_BOMB, 2, 9);
    // SetTime(HURT_ALL_POLES - PAO_ANIMATION + 40, 10),
    SetTime(486 - ICE_ANIMATION, 10),
        Card(ICE_SHROOM, 1, 9);

    // wave = 9
    SetTime(0, 9),
        pao_operator.recoverPao({{5, 9}, {2, 9}}),
        pao_operator.recoverPao({{5, 9}, {2, 9}}),
        pao_operator.recoverPao({{5, 9}, {2, 9}});

    // wave = 19
    SetTime(0, 19),
        pao_operator.recoverPao({{5, 9}, {2, 9}}),
        pao_operator.recoverPao({{5, 9}, {2, 9}}),
        pao_operator.recoverPao({{5, 9}, {2, 9}});

    // wave = 20
    SetTime(230 - PAO_ANIMATION + 40, 20),
        pao_operator.pao(1, 9),
        pao_operator.pao(6, 9);
    SetTime(HURT_ALL_POLES - PAO_ANIMATION + 40, 20),
        pao_operator.pao(2, 9),
        pao_operator.pao(5, 9);
    SetTime(486 - ICE_ANIMATION, 20),
        Card(ICE_SHROOM, 5, 9);

    pao_operator.recoverPao({{5, 9}, {2, 9}}),
        pao_operator.recoverPao({{5, 9}, {2, 9}}),
        pao_operator.recoverPao({{5, 9}, {2, 9}});

    // 垫材处理. 使用阻塞来回避读内存等复杂操作

    // int mat = 0, MAT_LEN = 3;
    // for (int wave = 1; wave <= 19; ++wave) {
    //     if (wave % 3 != 1)
    //         WaitUntil(195, wave),
    //             Card(10 - mat++ % MAT_LEN, 2, 9);

    //     WaitUntil(207, wave),
    //         Shovel(2, 9);

    //     WaitUntil(535, wave),
    //         Card(10 - mat++ % MAT_LEN, 4, 9);
    //     Delay(25),
    //         Shovel(4, 9);
    // }
}