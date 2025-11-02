#include "DxLib.h"
#include "../Header/CoordinateXY.h"
#include "../Header/GameManager.h"
#include "../Header/MenuCheck.h"
#include "../Header/MenuManager.h"
#include "../Header/Menu_Base.h"
#include "../Header/Operation.h"
#include "../Header/TimeManager.h"

/*
* @fn コンストラクタ
*/
MenuCheck::MenuCheck(Menu_Base &menuClass, void(Menu_Base:: *decisionProcess)(), Menu_Base *menu)
: Menu_Base(2, XYGet((GetScreenSize().x / 10) * 2.8, (GetScreenSize().y / 10) * 3.8), 
               XYGet((GetScreenSize().x / 10) * 6.2, (GetScreenSize().y / 10) * 7.2), GetColor(255, 255, 255), DX_BLENDMODE_NOBLEND, 255, true)
, mnCheckHandle(-1)
, mnSelectHandle(-1)
, mpMenuClass(menuClass)
, mfnDecisionProcess(decisionProcess)
, mpMenu(menu)
, mfnNotMenuDecisionProcess(nullptr)
, mbMenuFlag(true)
, mpObject(nullptr)
{
}

/*
* @fn コンストラクタ
*/
MenuCheck::MenuCheck(void(*decisionProcess)(Object_Base *object), Object_Base *object)
: Menu_Base(2, XYGet((GetScreenSize().x / 10) * 2.8, (GetScreenSize().y / 10) * 3.8),
               XYGet((GetScreenSize().x / 10) * 6.2, (GetScreenSize().y / 10) * 7.2), GetColor(255, 255, 255), DX_BLENDMODE_NOBLEND, 255, true)
, mnCheckHandle(-1)
, mnSelectHandle(-1)
, mfnNotMenuDecisionProcess(decisionProcess)
, mpObject(object)
, mpMenuClass(*this)
, mfnDecisionProcess(nullptr)
, mpMenu(nullptr)
, mbMenuFlag(false)
{
}

/*
* @fn デストラクタ
*/
MenuCheck::~MenuCheck()
{
}

/*
* @fn SetFunction
* @drief 関数ポインタ設定
*//*
void MenuCheck::SetFunction()
{
}*/

/*
* @fn MyInitilize
* @drief 個別初期化処理
*/
void MenuCheck::MyInitilize()
{
    { // 文字サイズハンドル設定
        mnCheckHandle = CreateFontToHandle(NULL, 40, 5);
        mnSelectHandle = CreateFontToHandle(NULL, 30, 5);
    }
    mnMenuSelect = 1;
}

/*
* @fn MyFinalize
* @drief 個別終了処理
*/
void MenuCheck::MyFinalize()
{
    DeleteFontToHandle(mnCheckHandle);
    DeleteFontToHandle(mnSelectHandle);
}

/*`
* @fn MyUpdate
* @drief 個別更新処理
*/
void MenuCheck::MyUpdate()
{

    // 左列に移動
    if (Operation::CheckLeftKey() && CheckFrame(0)) {
        if (mnMenuSelect > 0) {

            // 時間設定
            mnChangeFrame = Master::mpGameManager->GetTimeManager()->GetFrame();

            // 選択を左にずらす
            mnMenuSelect -= 1;
        }
    }
    // 右列に移動
    if (Operation::CheckRightKey() && CheckFrame(0)) {
        if (mnMenuSelect < (mnMaxMenuSelect - 1)) {

            // 時間設定
            mnChangeFrame = Master::mpGameManager->GetTimeManager()->GetFrame();

            // 選択を右にずらす
            mnMenuSelect += 1;
        }
    }

    // 選択決定処理
    CheckDecision_AKeyAndFrame();

    // 閉じる
    if (Operation::CheckBKey() && CheckFrame(1)) {
        Master::mpGameManager->GetMenuManager()->DecreaseMenuNumber();
        SetDeleteFlag(true);
        if (mbMenuFlag) {
            mpMenu->ResetDecisionFlame();
        }
        SetCloseMenuSound();
    }
}

/*
* @fn MyDraw
* @drief 個別描画化処理
*/
void MenuCheck::MyDraw()
{
    DrawBoxAA((GetScreenSize().x / 10) * 2.9, (GetScreenSize().y / 10) * 3.9,
              (GetScreenSize().x / 10) * 6.1, (GetScreenSize().y / 10) * 7.1, GetColor(100, 100, 100), TRUE);

    // YES
    DrawBoxAA((GetScreenSize().x / 10) * 2.95, (GetScreenSize().y / 10) * 5.4, (GetScreenSize().x / 10) * 4.15, (GetScreenSize().y / 10) * 6.4, GetColor(0, 0, 0), TRUE);
    DrawBoxAA((GetScreenSize().x / 10) * 3.05, (GetScreenSize().y / 10) * 5.5, (GetScreenSize().x / 10) * 4.05, (GetScreenSize().y / 10) * 6.3, ((mnMenuSelect == 1) ? GetColor(200, 200, 200) : GetColor(255, 255, 255)), TRUE);

    // NO
    DrawBoxAA((GetScreenSize().x / 10) * 4.85, (GetScreenSize().y / 10) * 5.4, (GetScreenSize().x / 10) * 6.05, (GetScreenSize().y / 10) * 6.4, GetColor(0, 0, 0), TRUE);
    DrawBoxAA((GetScreenSize().x / 10) * 4.95, (GetScreenSize().y / 10) * 5.5, (GetScreenSize().x / 10) * 5.95, (GetScreenSize().y / 10) * 6.3, ((mnMenuSelect == 0) ? GetColor(200, 200, 200) : GetColor(255, 255, 255)), TRUE);

    // Check文字
    DrawStringToHandle((GetScreenSize().x / 10) * 3.1, (GetScreenSize().y / 10) * 4.5, "EXECUTION", GetColor(0, 0, 0), mnCheckHandle);

    // 選択文字
    DrawStringToHandle((GetScreenSize().x / 10) * 3.2, (GetScreenSize().y / 10) * 5.6, "YES", GetColor(0, 0, 0), mnSelectHandle);
    DrawStringToHandle((GetScreenSize().x / 10) * 5.225, (GetScreenSize().y / 10) * 5.6, "NO", GetColor(0, 0, 0), mnSelectHandle);
}

/*
* @fn SelectDecision
* @drief 選択決定時処理
*/
void MenuCheck::SelectDecision()
{
    // 閉じる
    Master::mpGameManager->GetMenuManager()->DecreaseMenuNumber();
    SetDeleteFlag(true);
    
    if (mbMenuFlag) {
        mpMenu->ResetDecisionFlame();
    }

    if (mnMenuSelect == 0) {
        if (mbMenuFlag) {
            (mpMenuClass.*mfnDecisionProcess)(/*(mnMenuSelect == 0) ? false : true*/);
        }
        else {
            (mfnNotMenuDecisionProcess)(mpObject);
        }
    }
}