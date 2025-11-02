#include "../Header/GameManager.h"
#include "../Header/MenuManager.h"
#include "../Header/TimeManager.h"

/*
* @fn コンストラクタ
*/
MenuManager::MenuManager()
: mnNowMenuNumber(0)
{
}

/*
* @fn デストラクタ
*/
MenuManager::~MenuManager()
{
}

/*
* @fn Initilize
* @drief 初期化
*//*
void MenuManager::Initilize()
{
}*/

/*
* @fn Update
* @drief 更新
*//*
void MenuManager::Update()
{
}*/

/*
* @fn IncreaseMenuNumber
* @drief メニューナンバー増加
*/
int MenuManager::IncreaseMenuNumber(Menu_Base *menuBase)
{
    // 一番後ろに追加
    mpMenu_Bases.push_back(menuBase);
    
    mnNowMenuNumber += 1;
    if (mnNowMenuNumber == 1) {
        // 時間を止める
        Master::mpGameManager->GetTimeManager()->SetStopFlag(true);
    }
    return mnNowMenuNumber;
}

/*
* @fn DecreaseMenuNumber
* @drief メニューナンバー減少
*/
void MenuManager::DecreaseMenuNumber()
{
    // 一番後ろを削除
    mpMenu_Bases.pop_back();

    mnNowMenuNumber -= 1;
    if (mnNowMenuNumber <= 0) {
        mnNowMenuNumber = 0;

        // 時間を動かす
        Master::mpGameManager->GetTimeManager()->SetStopFlag(false);
    }
    else {
        mpMenu_Bases[mnNowMenuNumber - 1]->ResetDecisionFlame();
        if (!(Master::mpGameManager->GetEndFlag())) {
            if ((mpMenu_Bases[mnNowMenuNumber - 1]->GetPlayerDataDrawFlag())) {
                mpMenu_Bases[mnNowMenuNumber - 1]->SetDrawPlayerHandle();   // 描画用のハンドル設定
            }
        }
    }
}