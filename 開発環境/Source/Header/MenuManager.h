#pragma once
#include <vector>

#include "../Header/Menu_Base.h"

class MenuManager
{
private:
    int mnNowMenuNumber;    // メニューナンバー
    std::vector<Menu_Base *> mpMenu_Bases;  // メニューベースズ

public:
    MenuManager();  // コンストラクタ
    ~MenuManager(); // デストラクタ

    //void Initilize();   // 初期化
    //void Update();      // 更新

    int IncreaseMenuNumber(Menu_Base *menuBase);  // メニューナンバー増加
    void DecreaseMenuNumber();  // メニューナンバー減少
    int GetNowMenuNumber() { return mnNowMenuNumber; }  // メニューナンバー取得
};