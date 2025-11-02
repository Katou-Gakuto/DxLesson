#pragma once
#include "../Header/CoordinateXY.h"
#include "../Header/Menu_Base.h"

class DataManager;

class MenuPlayerSelect : public Menu_Base
{
private:

public:
    MenuPlayerSelect();
    ~MenuPlayerSelect();

    void MyInitilize() override;    // 初期化処理
    void MyFinalize() override;     // 終了処理
    void MyUpdate() override;		    // 更新処理
    void MyDraw() override;         // 描画処理

    void SelectDecision() override; // 選択決定時処理

    void SetOverride_CheckMenuProcess() override;   // チェックメニュー用関数(ゲーム移行)
};