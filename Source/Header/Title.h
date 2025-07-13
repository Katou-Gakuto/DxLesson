#pragma once
#include "../Header/Menu_Base.h"

class Title : public Menu_Base
{
public:

    Title();    // コンストラクタ
    ~Title();   // デストラクタ

    void MyInitilize()    override; // 初期化
    void MyUpdate()       override; // 更新
    void MyDraw()         override; // 描画

    void SelectDecision() override; // 選択決定時処理
    void MyFinalize()     override; // 終了

private:

    enum SELECT_TITLE
    {
        START,// スタート
        SETTING,// 設定
        END,// 終了
        MAX,// 最大
    };

    //int mnSelect;   // 選択用変数

    //int mnChangeFrame;  // 選択変更したフレーム数

    int mnTitleHandle;      // タイトル文字ハンドル
    int mnSelectHandle;     // 選択文字ハンドル
    int mnOperationHandle;  // 簡易操作説明文字ハンドル

    //-- 画面サイズ保存用変数 --//
    int mnWidth;    // 横幅
    int mnHeight;   // 高さ
    //int mnColorBit; // カラービット深度
    //--                      --//

};