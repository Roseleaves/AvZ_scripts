#include "avz.h"

using namespace AvZ;

void Script()
{
    SelectCards({
        ICE_SHROOM,   // 寒冰菇
        M_ICE_SHROOM, // 模仿寒冰菇
        COFFEE_BEAN,  // 咖啡豆
        DOOM_SHROOM,  // 毁灭菇
        LILY_PAD,     // 荷叶
        SQUASH,       // 倭瓜
        CHERRY_BOMB,  // 樱桃炸弹
        BLOVER,       // 三叶草
        PUMPKIN,      // 南瓜头
        PUFF_SHROOM,  // 小喷菇
    });

    // SetZombies({
    //     POLE_VAULTING_ZOMBIE,   // 撑杆
    //     BUCKETHEAD_ZOMBIE,      // 铁桶
    //     ZOMBONI,                // 冰车
    //     JACK_IN_THE_BOX_ZOMBIE, // 小丑
    //     BALLOON_ZOMBIE,         // 气球
    //     LADDER_ZOMBIE,          // 梯子
    //     CATAPULT_ZOMBIE,        // 投篮
    //     GARGANTUAR,             // 巨人
    //     GIGA_GARGANTUAR,        // 红眼巨人
    //     POGO_ZOMBIE,            // 跳跳
    // });

    pao_operator.resetPaoList({
        {3, 3},
        {4, 5},
        {3, 1},
        {1, 1}, // {4, 7},
        {4, 1},
        {2, 1}, // {3, 7},
        {4, 3},
        {3, 5},
        {2, 5},
        {5, 5},
        {1, 5},
        {6, 5},
    });

    // 6s 一对炮
    for (int wave = 1; wave <= 20; ++wave) {
        if (wave == 20 || wave == 10) {
            SetTime(-55, wave);
            pao_operator.pao({{2, 9}, {5, 9}});
            if (wave == 20) {
                SetTime(-150, 20);
                pao_operator.pao(4, 7);
            }
            if (wave == 10) {
                SetTime(-55 + 373 - 100, 10);
                Card(CHERRY_BOMB, 2, 9);
            }
            continue;
        }

        // -95cs 发炮, 强调处理第 1 波
        SetTime(-95, wave);
        // 把炮发到 2 路 9 列和 5 路 9 列
        pao_operator.pao({{2, 9}, {5, 9}});
        if (wave == 19 || wave == 9) {
            pao_operator.recoverPao({{2, 9}, {5, 9}});
            pao_operator.recoverPao({{2, 9}, {5, 9}});
        }
    }

    // wave 20 的附加操作
    // 咆哮珊瑚
    // 解决僵尸出生点靠右的问题
}