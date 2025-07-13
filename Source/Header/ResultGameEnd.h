#pragma once
#include "../Header/Data_Structs.h"
#include "../Header/Menu_Base.h"

class ResultGameEnd : public Menu_Base
{
private:

    enum class GAME_OVER    // ゲームオーバー用イーナム
    {
        RE_START = 0,
        END = 1,
        MAX = 2
    };

    enum class GAME_CLEAR   // ゲームクリア用イーナム
    {
        RE_START = 0,
        END = 1,
        MAX = 2
    };

    enum class GAME_NOTHING // ゲーム無し用イーナム
    {
        RE_START = 0,
        END = 1,
        MAX = 2
    };

    int mnResultHandle; // リザルト文字ハンドル
    int mnSelectHandle; // 選択文字ハンドル
    int mnPlayerHandle; // プレイヤー情報描画用ハンドル

    //-- 画面サイズ保存用変数 --//
    int mnWidth;    // 横幅
    int mnHeight;   // 高さ
    //--                      --//

    std::vector<ITEM_DATA> msPlusItem;    // 追加するアイテム
    std::vector<int> mnItemHandle;  // アイテム画像用ハンドル

    PLAYER_DATA GetPlayer_ItemPlus(PLAYER_DATA playerData);   // アイテムを取得したデータを返す
    
    void DrawClear();   // クリア画面描画用

public:
    ResultGameEnd();
    ~ResultGameEnd();

    void MyInitilize()    override;   // 初期化
    void MyUpdate()       override;   // 更新
    void MyDraw()         override;   // 描画
    void MyFinalize()     override;   // 終了処理

    void SelectDecision() override;  // 選択決定時処理
};