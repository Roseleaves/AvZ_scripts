// PE三路放空20炮
//
#include "avz.h"

using namespace AvZ;

void Script()
{
    OpenMultipleEffective('Q', AvZ::MAIN_UI_OR_FIGHT_UI);
    SetZombies({
        GIGA_GARGANTUAR,      // 红眼巨人
        GARGANTUAR,           // 巨人
        DANCING_ZOMBIE,       // MJ
        POLE_VAULTING_ZOMBIE, // 撑杆
        ZOMBONI,              // 冰车
        DIGGER_ZOMBIE,        // 矿工
        SNORKEL_ZOMBIE,       // 潜水
        DOLPHIN_RIDER_ZOMBIE, // 海豚
        POGO_ZOMBIE,          // 跳跳
        BUCKETHEAD_ZOMBIE,    // 铁桶
        BUNGEE_ZOMBIE,        // 小偷
        // JACK_IN_THE_BOX_ZOMBIE, // 小丑
    });

    SelectCards({
        M_ICE_SHROOM,
        ICE_SHROOM,
        CHERRY_BOMB,
        JALAPENO,
        COFFEE_BEAN,
        LILY_PAD,
        FLOWER_POT,
        SCAREDY_SHROOM,
        SUN_SHROOM,
        PUFF_SHROOM,
    });

    pao_operator.resetPaoList({
        {1, 1},
        {2, 1},
        {4, 1},
        {5, 1},
        {6, 1},
        {1, 3},
        {2, 3},
        {4, 3},
        {5, 3},
        {6, 3},
        {1, 5},
        {2, 5},
        {4, 5},
        {5, 5},
        {6, 5},
        {1, 7},
        {2, 7},
        {4, 7},
        {5, 7},
        {6, 7},
    });

    const int HURT_ALL_POLES = 359,
              HURT_ALL_GARGANTUARS = 230,
              PAO_ANIMATION = 373,
              ICE_ANIMATION = 100,
              COFFEE_ICE = 299,
              ICE_TIME = 5,
              Ch6_Wavelength = 1230,
              IMP_INTERCEPT_TIME = 116,
              SEPARATION_TIME = 500;
    const float IMP_INTERCEPT_ROW = 8 + 1.0 / 8,
                SEPARATION_ROW = 7.5;

    Card(LILY_PAD, 3, 1);

    ice_filler.start({{4, 9}, {3, 1}, {3, 7}});

    SetTime(10, 4),
        Shovel(3, 1);
    SetTime(3500, 9),
        Card(LILY_PAD, 3, 7);
    SetTime(10, 15),
        Shovel(3, 7);
    // /*
    // IS-PS, PDc
    // PDc
    for (auto wave : {1, 3, 5, 7, 12, 14, 16, 18}) {
        SetTime(HURT_ALL_GARGANTUARS - PAO_ANIMATION, wave),
            pao_operator.pao({{5, 9}, {wave == 1 ? 2 : 1, 9}});
        Delay(IMP_INTERCEPT_TIME),
            pao_operator.pao(5, IMP_INTERCEPT_ROW),
            pao_operator.pao(1, IMP_INTERCEPT_ROW);
        SetTime(ICE_TIME - 180, wave + 1),
            Card(10, 1, 9),
            Card(9, 2, 9),
            Card(8, 5, 9),
            Card(7, 6, 9);
        SetTime(ICE_TIME, wave + 1),
            Shovel({{1, 9}, {2, 9}, {5, 9}, {6, 9}});
    }
    // IS-PS
    for (auto wave : {1, 3, 5, 7, 9, 11, 13, 15, 17, 19}) {
        SetTime(600 + ICE_TIME - COFFEE_ICE, wave - 1),
            ice_filler.coffee();
        SetTime(SEPARATION_TIME - PAO_ANIMATION, wave),
            pao_operator.pao(2, SEPARATION_ROW),
            pao_operator.pao(5, SEPARATION_ROW);
        SetTime(Ch6_Wavelength - 200 - PAO_ANIMATION, wave),
            pao_operator.pao({{2, 9.2}, {5, 9.2}});
        Delay(215),
            pao_operator.pao({{1, 8.5}, {5, 8.5}});
        // SetTime(HURT_ALL_POLES - PAO_ANIMATION, wave),
    }
    // */
    // wave = 10

    SetTime(HURT_ALL_GARGANTUARS - PAO_ANIMATION + 40, 10),
        pao_operator.pao({{5, 9}, {2, 9}});
    Delay(IMP_INTERCEPT_TIME),
        pao_operator.pao(5, 8),
        pao_operator.pao(1, 9);
    SetTime(HURT_ALL_GARGANTUARS - ICE_ANIMATION + 40, 10),
        Delay(IMP_INTERCEPT_TIME * 2),
        Card(CHERRY_BOMB, 1, 9);
    SetTime(-180, 11),
        Card(10, 5, 9),
        Card(9, 6, 9);
    SetTime(0, 11),
        Shovel({{5, 9}, {6, 9}});

    // wave = 9

    Delay(IMP_INTERCEPT_TIME),
        pao_operator.pao(5, IMP_INTERCEPT_ROW),
        pao_operator.pao(3, IMP_INTERCEPT_ROW);
    SetTime(HURT_ALL_GARGANTUARS - PAO_ANIMATION + 2, 9),
        pao_operator.pao({{5, 9}, {1, 9}});
    Delay(PAO_ANIMATION - COFFEE_ICE + 6),
        ice_filler.coffee();
    SetTime(HURT_ALL_GARGANTUARS - PAO_ANIMATION + 1 + 607, 9),
        pao_operator.pao({{5, 9}, {2, 8.7}});
    Delay(215),
        pao_operator.pao({{5, 9}, {1, 9}});
    Delay(PAO_ANIMATION + 5),
        Card(10, 1, 9);

    SetTime(1350, 9);
    InsertOperation([=]() {
        bool flag = true;
        auto zombie = GetMainObject()->zombieArray(); // 再取出僵尸的内存块
        for (int index = 0; index < GetMainObject()->zombieTotal() && flag; ++index) {
            // 如果在 1 路有红眼僵尸
            if (zombie[index].isExist()
                && zombie[index].type() == GIGA_GARGANTUAR
                && !zombie[index].isDead()
                && zombie[index].row() == 0) {
                // 炮轰 2 路红眼，留下 1 路红眼
                flag = false;
            }
        }
        if (flag) {
            // AvZ::ShowError("垫2路!");
            SetTime(1350, 9),
                AvZ::MaidCheats::dancing();
        } else {
            // AvZ::ShowError("垫1路!");
            SetTime(1800, 9),
                pao_operator.pao(3, 9);
        }
    });

    SetTime(1800, 9),
        pao_operator.pao(5, 9);
    SetTime(3000, 9),
        AvZ::MaidCheats::dancing();
    SetTime(-750, 10),
        pao_operator.pao({{5, 9}, {2, 9}}),
        AvZ::MaidCheats::stop();

    // wave = 19
    SetTime(HURT_ALL_GARGANTUARS - PAO_ANIMATION + Ch6_Wavelength, 19),
        pao_operator.pao({{5, 9}, {1, 9}});
    // SetTime(0, 19),
    SetTime(2000, 19),
        pao_operator.pao({{5, 9}, {2, 9}});
    // SetTime(3000, 19)

    // wave = 20
    SetTime(-150, 20),
        pao_operator.pao(4, 7);
    SetTime(HURT_ALL_GARGANTUARS - PAO_ANIMATION + 40, 20),
        pao_operator.pao({{2, 9}, {5, 9}});
    Delay(29), pao_operator.pao(1, 9);
    Delay(29), pao_operator.pao(5, 9);
    Delay(29), pao_operator.pao(1, 9);
    Delay(29), pao_operator.pao(5, 9);
    Delay(29), pao_operator.pao(1, 9);
    Delay(29), pao_operator.pao(5, 9);
}