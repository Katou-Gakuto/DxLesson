#pragma once

enum class SCENE // シーン種類
{
    SART,                   // スタート
    TITLE,                  // タイトル
    SELECT_SAVE_DATA,       // セーブ選択
    DEFAULT_MAP_ONE,       // デフォルトマップ1
    //マップ
    MAP_ONE,
    MAP_TWO,
    MAP_THREE,
    MAP_FOUR,
    MAP_FIVE,
    MAP_SIX,
    MAP_SEVEN,
    MAP_EIGHT,
    MAP_NINE,
    MAP_TEN,
    MAP_ELEVEN,
    MAP_TWELVE,
    MAP_THIRTEEN,
    MAP_FOURTEEN,
    MAP_FIFTEEN,
    MAP_SIXTEEN,
    MAP_SEVENTEEN,
    MAP_EIGHTEEN,
    MAP_NINETEEN,
    MAP_TWENTY,
    MAP_TWENTY_ONE,
    MAP_TWENTY_TWO,
    MAP_TWENTY_THREE,
    MAP_TWENTY_FOUR,
    //24個
    BATTLE_GAME_ONE,        // バトルゲーム1
    BOSS_BATTLE_GAME_ONE,   // ボスバトルゲーム1
    BATTLE_RESULT,          // バトルリザルト
    GAME_OVER,              // ゲームオーバー
    GAME_CLEAR,             // ゲームクリア
    GAME_NOTHING,           // ゲーム無し
    EXCEPTION,  // 例外
    SCENE_NULL, // シーンに何も入ってないもしくは間違ったのが入ってる(データマネージャーで使うために作った)
};/*
        MAP_ONE

        MAP_TWO
        MAP_THREE
        MAP_FOUR
        MAP_FIVE
        MAP_SIX
        MAP_SEVEN
        MAP_EIGHT
        MAP_NINE
        MAP_TEN
        MAP_ELEVEN
        MAP_TWELVE
        MAP_THIRTEEN
        MAP_FOURTEEN
        MAP_FIFTEEN
        MAP_SIXTEEN
        MAP_SEVENTEEN
        MAP_EIGHTEEN
        MAP_NINETEEN
        MAP_TWENTY
        MAP_TWENTY_ONE
        MAP_TWENTY_TWO
        MAP_TWENTY_THREE
        MAP_TWENTY_FOUR
        */