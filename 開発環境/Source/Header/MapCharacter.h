#pragma once
#include <iostream>
#include <string>

#include "../Header/CharacterType_Enum.h"
#include "../Header/Object_Base_Character.h"
#include "../Header/Scene_Enum.h"
#include "../Header/Status_Struct.h"

class MapCharacter : public Object_Base_Character
{
private:
    Object_Base_Character* mpPlayer;

    CHARACTER_TYPE meCharacterType;

    SCENE meGoScene;

    bool mbPopUpFlag;

    int mnPopUpScreenHandle;    // ポップアップ表示用ハンドル
    int mnDrawPopUpStringHabdle;    // ポップアップ表示用文字サイズハンドル

    int mnDrawLevelNumber;  // レベルの桁数

    int mnNextAKeyTime; // 次のAキーが有効になる時間

    bool mbDeleteCharacterDataFlag; // キャラクターデータ削除フラグ

public:
    MapCharacter(STATUS status, VECTOR position, float angle, std::string name, CHARACTER_TYPE characterType, SCENE goScene, std::string characterFileName, bool deleteCharacterDataFlag = true); // コンストラクタ
    ~MapCharacter();    // デストラクタ

    void Initilize()    override;   // 初期化
    void Update()       override;   // 更新
    void Draw()         override;   // 描画
    void MyFinailize()     override;   // 終了処理

    void HpZeroMove() override; // HPが0以下時の処理

    bool PlayerCheck(); // プレイヤーが近くに居るか

    void PopUpProcess();    // ポップアップ表示中の処理
    void DrawPopUpText();   // ポップアップを表示する

    SCENE GetGoScene() { return meGoScene; }    // 移動するシーンを取得

    std::string GetGoSceneName();   // 移動するシーンを文字列で取得

    bool GetDeleteDataFlag() { return mbDeleteCharacterDataFlag; }  // キャラクターデータ削除フラグ取得
};