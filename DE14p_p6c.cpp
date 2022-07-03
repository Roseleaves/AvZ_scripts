#include "avz.h"

using namespace AvZ;

void Script()
{
    SetZombies({
        GIGA_GARGANTUAR,        // 红眼巨人
        GARGANTUAR,             // 巨人
        DANCING_ZOMBIE,         // MJ
        POLE_VAULTING_ZOMBIE,   // 撑杆
        ZOMBONI,                // 冰车
        DIGGER_ZOMBIE,          // 矿工
        LADDER_ZOMBIE,          // 梯子
        JACK_IN_THE_BOX_ZOMBIE, // 小丑
        POGO_ZOMBIE,            // 跳跳
        BUCKETHEAD_ZOMBIE,      // 铁桶
        BUNGEE_ZOMBIE,          // 小偷
    });

    SelectCards({
        ICE_SHROOM,
        CHERRY_BOMB,
        SQUASH,
        GRAVE_BUSTER,
        SUNFLOWER,
        SCAREDY_SHROOM,
        FLOWER_POT,
        SUN_SHROOM,
        PUFF_SHROOM,
        M_PUFF_SHROOM,
    });

    pao_operator.resetPaoList({
        {1, 1},
        {2, 1},
        {3, 1},
        {4, 1},
        {5, 1},
        {1, 5},
        {2, 5},
        {3, 5},
        {4, 5},
        {5, 6},
        {1, 7},
        {2, 7},
        {3, 7},
        {4, 7},
    });

    const int HURT_ALL_POLE_VAULTING_ZOMBIE = 359,
              PAO_ANIMATION = 373,
              ICE_ANIMATION = 100;

    // 荼蘼的14炮节奏的垫材使用较为复杂. 因此后面集中处置垫材。
    // PD / Pc
    for (auto wave : {1, 4, 7, 13, 16, 19}) {
        SetTime(230 - PAO_ANIMATION, wave),
            pao_operator.pao(1, 9),
            pao_operator.pao(4, 9);
        SetTime(HURT_ALL_POLE_VAULTING_ZOMBIE - PAO_ANIMATION, wave),
            pao_operator.pao(2, 9);
    }

    // wave = 10
    SetTime(230 - PAO_ANIMATION + 40, 10),
        pao_operator.pao(1, 9),
        pao_operator.pao(4, 9);
    SetTime(HURT_ALL_POLE_VAULTING_ZOMBIE - PAO_ANIMATION + 40, 10),
        pao_operator.pao(2, 9);
    SetTime(486 - ICE_ANIMATION, 10),
        Card(ICE_SHROOM, 5, 8);

    // cP / Pc
    for (auto wave : {2, 3, 5, 6, 8, 9, 11, 12, 14, 15, 17, 18}) {
        SetTime(230 - PAO_ANIMATION, wave),
            pao_operator.pao(4, 9);
        SetTime(HURT_ALL_POLE_VAULTING_ZOMBIE - PAO_ANIMATION, wave),
            pao_operator.pao(2, 9);
    }

    // wave = 9
    SetTime(0, 9),
        pao_operator.recoverPao({{2, 9}, {4, 9}}),
        pao_operator.recoverPao({{2, 9}, {4, 9}});

    // wave = 19
    SetTime(0, 19),
        pao_operator.recoverPao({{2, 9}, {4, 9}}),
        pao_operator.recoverPao({{2, 9}, {4, 9}});

    SetTime(230 - PAO_ANIMATION + 40, 20),
        pao_operator.pao(1, 9),
        pao_operator.pao(4, 9);
    SetTime(HURT_ALL_POLE_VAULTING_ZOMBIE - PAO_ANIMATION + 40, 20),
        pao_operator.pao(2, 9),
        pao_operator.pao(4, 9);
    SetTime(486 - ICE_ANIMATION, 20),
        Card(ICE_SHROOM, 5, 8);

    // 垫材处理. 使用阻塞来回避读内存等复杂操作

    int mat = 0, MAT_LEN = 3;
    for (int wave = 1; wave <= 19; ++wave) {
        if (wave % 3 != 1)
            WaitUntil(195, wave),
                Card(10 - mat++ % MAT_LEN, 2, 9);

        WaitUntil(207, wave),
            Shovel(2, 9);

        WaitUntil(535, wave),
            Card(10 - mat++ % MAT_LEN, 4, 9);
        Delay(25),
            Shovel(4, 9);
    }
}