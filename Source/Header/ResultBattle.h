#pragma once
#include <iostream>
#include <vector>

#include "../Header/DataManager.h"
#include "../Header/Data_Structs.h"
#include "../Header/Menu_Base.h"
#include "../Header/SceneManager.h"

class ResultBattle : public Menu_Base
{
private:

    enum {
        MAP = 0,    // マップ
//        RESULT_IN_DETAIL = 1,   // リザルト詳細
        MAX = 1,    // enumの最大個数
    };

    // リザルト用構造体作る取得

    int mnResultHandle; // リザルト文字ハンドル
    int mnSelectHandle; // 選択文字ハンドル
    int mnPlayerHandle; // プレイヤー情報描画用ハンドル

    //-- 画面サイズ保存用変数 --//
    int mnWidth;    // 横幅
    int mnHeight;   // 高さ
    //--                      --//

    std::vector<ITEM_DATA> msPlusItem;    // 追加するアイテム
    std::vector<int> mnItemHandle;  // アイテム画像用ハンドル

public:

    ResultBattle();   // コンストラクタ
    ~ResultBattle();  // デストラクタ


    void MyInitilize()    override;   // 初期化
    void MyUpdate()       override;   // 更新
    void MyDraw()         override;   // 描画
    void MyFinalize()     override;   // 終了処理

    void SelectDecision() override;  // 選択決定時処理

    PLAYER_DATA GetPlayer_PlusNewItem(PLAYER_DATA playerData);  // アイテムを追加したプレイヤーデータを取得
};