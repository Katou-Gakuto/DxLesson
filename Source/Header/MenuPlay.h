#pragma once

#include "../Header/Menu_Base.h"
#include "../Header/Object_Base_Character.h"

class MenuPlay : public Menu_Base
{
private:

    int mnMenuHandle;   // メニュー文字ハンドル
    int mnSelectHandle; // 選択文字ハンドル
    int mnPlayerDataHandle; // プレイヤー情報表示用ハンドル

    int mnSelectManager;    // 選択管理用

    Object_Base_Character *mpPlayer;    // プレイヤー

    void SetOverride_CheckMenuProcess() override;    // チェック用関数(セーブ用)

public:
    MenuPlay(Object_Base_Character *player);
    ~MenuPlay();

    void MyInitilize() override;    // 個別初期化処理
    void MyFinalize() override; // 個別終了処理
    void MyUpdate() override;   // 個別更新処理
    void MyDraw() override; // 個別描画化処理
    
    void SelectDecision() override; // 選択決定時処理
};