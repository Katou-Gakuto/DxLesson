#pragma once

typedef struct Status   // ステータス
{
    int level;  // レベル
    int exp;    // 経験値
    int attackPower;    // 攻撃力
    int maxHp;          // 最大ヒットポイント
    int hp;             // ヒットポイント
    int defense;        // 防御力
    int speed;          // 速度
    int size;           // 大きさ　(円なら半径、四角ならx軸)
}STATUS;