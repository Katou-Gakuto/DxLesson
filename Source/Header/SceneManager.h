#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "../Header/CharacterType_Enum.h"
#include "../Header/Data_Structs.h"
#include "../Header/Scene_Enum.h"
#include "../Header/StageManagerObject.h"

class DataManager;

class SceneManager 
{
public:

    SceneManager();     // コンストラクタ
    ~SceneManager();    // デストラクタ

    SCENE GetNowScene() { return meNowScene; }              // 現在のシーン取得
    void SetNextScene(SCENE scene) { meNextScene = scene; } // 次のシーン設定

    int GetPlayerDataNumber() { return mnPlayerDataNumber; }                                    // いくつ目のプレイヤーデータか取得
    void SetPlayerDataNumber(int playerDataNumber) { mnPlayerDataNumber = playerDataNumber; }   // いくつ目のプレイヤーデータか設定

    CHARACTER_TYPE GetCharacterType(std::string characterType); // キャラクタータイプ変換

    void CheckScene();                                      // シーン変更するかどうかチェックして実行する

    void SetCharacter_StageManager(StageManagerObject *stageManager, SCENE nowScene, std::vector<DATA_NAME> playerFileNameData, std::vector<DATA_NAME> baseFileNameData);   // キャラクター生成データ入力
    void SetBattleCharacter_StageManager(StageManagerObject *stageManager, CHARACTER_TYPE characterType, VECTOR position_1, VECTOR position_2, VECTOR position_3);  // バトルの敵を生み出す

    bool GetAsyncFlag() { return mbAsyncFlag; } // 非同期フラグ取得

    void NewSceneProcess(); // 新しいシーン移行処理

    bool GetNowSceneType(std::string sceneType);    // 指定されたシーンタイプと現在のシーンタイプが同じならtrueを返す

    PLAYER_DATA GetOldPlayerData() { return msOldPlayerData; }  // 前のプレイヤーデータ

    float GetMapMaxSize() { return mfMapMaxSize; }

private:
    SCENE meNowScene;   // 現在のシーン
    SCENE meNextScene;  // 次のシーン

    int mnPlayerDataNumber;   // 初期値-1

    std::vector<MAP_DATA> msMapDatas;

    bool mbAsyncFlag;   // 非同期フラグ

    int mnLoadingHandle;    // ローディング動画ハンドル

    DataManager *mpDataManager;	// データマネージャー

    float mfMagnificationRate;      // マップ拡大率
    float mfMapMaxSize; // マップ最大サイズ

    PLAYER_DATA msOldPlayerData;    // 　保存用プレイヤーデータ

    void SetTowerObject(VECTOR plusPosition, int modelNumber, const char *filename, int xTowerNumber = 1, int zTowerNumber = 1);    //  タワー作成用関数
};