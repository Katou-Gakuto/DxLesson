#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "DxLib.h"
#include "../Header/Scene_Enum.h"
#include "../Header/Status_Struct.h"

typedef struct Data_Name
{
    std::string fileName; // ファイル名
    std::string fileTypeName; // ファイルタイプ名
    SCENE sceneType;  // 生成マップタイプ スタートは初めに入力　例外は必要と思われる場所で
}DATA_NAME;

typedef struct Data_Struct
{
    std::string name;   // 名前

    std::string typeName;   // タイプ名

}DATA_STRUCT;

typedef struct Character_Data
{
    bool survivalFlag;  // 生存フラグ

    DATA_STRUCT templateData;   // 基本データ

    STATUS status;  // ステータス

    std::string mapName;    // 居るマップの名前
    VECTOR position;    // ポジション
    float angle;    // 見てる方向

}CHARACTER_DATA;

typedef struct ItemData
{
    DATA_STRUCT templateData;   // 基本データ

    int possessionCount;    // 所持数

    std::string itemPhotoFileName;  // アイテム画像のファイルネーム

}ITEM_DATA;

typedef struct Player_Data
{
    bool dataFlag;  // データが存在するかどうか

    CHARACTER_DATA characterData;   // キャラクターデータ

    int itemNumber; // アイテム数

    std::string playerFolderName;   // プレイヤー情報があるフォルダー名
    /*
    アイテムと装備情報
    */
    std::vector<ITEM_DATA> itemData;

}PLAYER_DATA;

typedef struct MapData
{
    DATA_STRUCT templateData;   // 基本データ

    int typeNameTypeNumber; // 種類数

    std::vector<std::string> typeName;   // タイプ名
    std::vector<int> typeNumber;    // タイプ必要数
}MAP_DATA;

typedef struct LevelData
{
    int maxLevelNumber; // 最大レベル
    std::vector<int> levelNumber;   // レベル
    std::vector<int> levelUpExpNumber;  // 次のレベルまで必要な経験値
}LEVEL_DATA;


typedef struct OneData
{
    bool dataChangeFlag = false;    // 変更フラグ

    DATA_STRUCT fileNameAndType; // ファイル名とタイプ名

    /*---*  データを全種類持つ  *---*/
    std::vector<DATA_NAME> fileNameDatas;       // ファイルネームデータズ
    std::vector<CHARACTER_DATA> characterDatas; // キャラクターデータズ
    std::vector<MAP_DATA> mapDatas;             // マップデータズ
    LEVEL_DATA levelData;                       // レベルデータ
    /*---*                      *---*/
};

typedef struct OnePlayerAllData
{
    bool dataFlag = false; // データ存在フラグ

    PLAYER_DATA playerData; // プレイヤーデータ

    std::vector<OneData> oneDatas;  // データ一つ分を全部
};