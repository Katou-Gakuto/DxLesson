#pragma once

enum class CHARACTER_TYPE   // キャラクタータイプ
{
    MAP_PLAYER, // マッププレイヤー

    ROBOT_PLAYER,    // ロボットプレイヤー

    MAP_CHARACTER_1,    // マップキャラクター1

    MAP_WEAK_ENEMY_1,   // マップ雑魚エネミー1

    MAP_BOSS_ENEMY_1,   // マップボスエネミー1

    BATTLE_WEAK_ENEMY_1,   // バトル雑魚エネミー1

    BATTLE_BOSS_ENEMY_1,    // バトルボスエネミー1

    TYPE_NULL,  // ヌルキャラ
};