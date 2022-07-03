// 水无12炮
// dodecannoned hydrophobics
#include "avz.h"

using namespace AvZ;

void Script()
{
    // OpenMultipleEffective('Q');
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
        COFFEE_BEAN,
        CHERRY_BOMB,
        SQUASH,
        WALL_NUT,
        GARLIC,
        FLOWER_POT,
        SCAREDY_SHROOM,
        SUN_SHROOM,
        PUFF_SHROOM,
        // M_PUFF_SHROOM,
    });

    pao_operator.resetPaoList({{1, 1}, {2, 1}, {3, 1}, {4, 1},
        {3, 3}, {4, 3},
        {1, 5}, {2, 5}, {3, 5}, {4, 5},
        {1, 7}, {2, 7}, {3, 7}, {4, 7}});

    const int POLES_ALL_HURT = 359,
              IMP_THROWING = 115,
              PAO_ANIMATION = 373,
              ASH_ANIMATION = 100,
              COFFEE_ANIMATION = 299;

    SetTime(0, 3),
        Card(WALL_NUT, 5, 1),
        Card(GARLIC, 6, 1);
    SetTime(0, 13),
        Card(WALL_NUT, 5, 1),
        Card(GARLIC, 6, 1);

    // 上半场 Pc, 下半场P
    // PD / Pc
    int ACTIVATION = 230,
        POLE_CRUSH = 535,
        TAILING_TIME = 280;
    float TAILING_COLUMN = 2.5;
    // TAILING_TIME:
    // at 2.5 column, at min: <300, >230, <280, <275, <250, >240
    // at 4.5 column, at min: <240, <230, <235, <232, >227, >228, >229 result: 230
    // at 2.5 column, at max: >280, >290, >300, >310, <320(hypno-shroom), <310, <300,
    // <290(hpyno imp), <280, >270, >280, <285(hypno-shroom), >283, <284 result:284
    for (auto wave : {1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 12, 13, 14, 15, 16, 17, 18, 19}) {
        SetTime(ACTIVATION - PAO_ANIMATION, wave),
            pao_operator.pao(2, 9),
            pao_operator.pao(5, 9);
        SetTime(POLE_CRUSH, wave),
            Card(7 + wave % 2, 1, 9),
            Card(9 + wave % 2, 2, 9);
        SetTime(POLE_CRUSH + 50, wave),
            Shovel(1, 9),
            Shovel(2, 9);
    }

    for (auto wave : {3, 6, 9, 13, 16, 19}) {
        SetTime(ACTIVATION + TAILING_TIME - PAO_ANIMATION, wave),
            pao_operator.pao(5, TAILING_COLUMN);
    }

    // wave = 10
    SetTime(ACTIVATION - PAO_ANIMATION + 40, 10),
        pao_operator.pao(5, 9),
        pao_operator.pao(2, 9);
    SetTime(ACTIVATION - ASH_ANIMATION + 40, 10),
        Card(CHERRY_BOMB, 5, 9);
    SetTime(ACTIVATION + IMP_THROWING - PAO_ANIMATION + 40, 10),
        pao_operator.pao(5, 9);
    SetTime(486 - COFFEE_ANIMATION, 10),
        Card(ICE_SHROOM, 5, 5),
        Card(COFFEE_BEAN, 5, 5);

    // wave = 9
    SetTime(600, 9),
        pao_operator.recoverPao({{5, 9}, {2, 9}}),
        pao_operator.recoverPao({{5, 9}, {2, 9}}),
        pao_operator.recoverPao(2, 9);

    // wave = 19
    SetTime(600, 19),
        pao_operator.recoverPao({{5, 9}, {2, 9}}),
        pao_operator.recoverPao({{5, 9}, {2, 9}}),
        pao_operator.recoverPao(2, 9);

    // wave = 20
    SetTime(-150, 20),
        pao_operator.pao(4, 7);
    SetTime(ACTIVATION - PAO_ANIMATION + 40, 20),
        pao_operator.pao(2, 9),
        pao_operator.pao(6, 9);
    SetTime(ACTIVATION + IMP_THROWING - PAO_ANIMATION + 40, 20),
        pao_operator.pao(1, 9),
        pao_operator.pao(5, 9);
    SetTime(ACTIVATION + 2 * IMP_THROWING - PAO_ANIMATION + 40, 20),
        pao_operator.pao(1, 9),
        pao_operator.pao(5, 9);
    SetTime(ACTIVATION + 3 * IMP_THROWING - PAO_ANIMATION + 40, 20),
        pao_operator.pao(1, 9),
        pao_operator.pao(5, 9);
    SetTime(486 - PAO_ANIMATION, 20),
        pao_operator.pao(2, 1),
        pao_operator.pao(1, 6);
    // SetTime(486 - COFFEE_ANIMATION, 20),
    //     Card(ICE_SHROOM, 5, 5),
    //     Card(COFFEE_BEAN, 5, 5);

    // pao_operator.recoverPao({{5, 9}, {2, 9}}),
    //     pao_operator.recoverPao({{5, 9}, {2, 9}}),
    //     pao_operator.recoverPao({{5, 9}, {2, 9}});

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