#include "DxLib.h"
#include "../Header/Camera.h"
#include "../Header/CoordinateXY.h"
#include "../Header/DataManager.h"
#include "../Header/GameManager.h"
#include "../Header/Item_Base.h"
#include "../Header/MenuItem.h"
#include "../Header/Menu_Base.h"
#include "../Header/ObjectManager.h"
#include "../Header/ObjectTagMacro.h"
#include "../Header/Operation.h"
#include "../Header/TimeManager.h"

/*
* @fn コンストラクタ
*/
MenuItem::MenuItem()
: Menu_Base(Master::mpGameManager->GetDataManager()->GetPlayPlayerData().item.size(), XYGet((GetScreenSize().x / 10) * 0.6, (GetScreenSize().y / 10) * 0.9), XYGet((GetScreenSize().x / 10) * 9.4, (GetScreenSize().y / 10) * 9.1), GetColor(50, 50, 50), DX_BLENDMODE_NOBLEND, 255)
, mpItems(Master::mpGameManager->GetDataManager()->GetPlayPlayerData().item)
{
    mnXMax = ((GetScreenSize().x / 10) * 9.3) - ((GetScreenSize().x / 10) * 0.7);
    mnYMax = ((GetScreenSize().y / 10) * 9) - (GetScreenSize().y / 10);
    mnItemDrawHandle = MakeScreen(mnXMax, mnYMax, TRUE);
}

/*
* @fn デストラクタ
*/
MenuItem::~MenuItem()
{
}

/*
* @fn MyInitilize
* @drief 個別初期化処理
*/
void MenuItem::MyInitilize()
{
}

/*
* @fn MyFinalize
* @drief 個別終了処理
*/
void MenuItem::MyFinalize()
{
    DeleteGraph(mnItemDrawHandle);
}

/*
* @fn MyUpdate
* @drief 個別更新処理
*/
void MenuItem::MyUpdate()
{
    //選択変更関連処理
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
        // 上列に移動
        if ((mnMenuSelect - 6) >= 0) {
            if (CheckUpKeyAndFrame()) {
                mnMenuSelect -= 6;
            }
        }
        // 下列に移動
        if ((mnMenuSelect + 6) < mnMaxMenuSelect) {
            if (CheckDownKeyAndFrame()) {
                mnMenuSelect += 6;
            }
        }


        // 選択決定処理
        CheckDecision_AKeyAndFrame();
    }

    // 閉じる
    if (Operation::CheckBKey() && CheckFrame(1)) {
        SetDeleteFlag(true);
    }
}

/*
* @fn MyDraw
* @drief 個別描画化処理
*/
void MenuItem::MyDraw()
{
    DrawBoxAA((GetScreenSize().x / 10) * 0.7, (GetScreenSize().y / 10), (GetScreenSize().x / 10) * 9.3, (GetScreenSize().y / 10) * 9, GetColor(150, 150, 150), TRUE);

    // 描画先を変更
    SetDrawScreen(mnItemDrawHandle);
    ClearDrawScreen();

    float maxX = ((GetScreenSize().x / 10) * 9.3) - ((GetScreenSize().x / 10) * 0.7);
    float maxY = ((GetScreenSize().y / 10) * 9) - (GetScreenSize().y / 10);

    DrawBoxAA(0, (maxY / 4) * 3.75, (maxX / 10) * 1.3, maxY, GetColor(0, 0, 0), TRUE);
    DrawString(0, (maxY / 4) * 3.8, "\"B\"BACK", GetColor(230, 230, 230));

    // 枠描画
    {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 6; j++) {
                DrawBox(((j + 0.3) * (mnYMax / 5) * 1.15), ((i + 0.3) * (mnYMax / 5) * 1.15),
                        ((j + 1.0) * (mnYMax / 5) * 1.15), ((i + 1.0) * (mnYMax / 5) * 1.15),
                        ((mnMenuSelect == ((j) + (i * 6))) ? GetColor(200, 200, 200) : GetColor(255, 255, 255)), TRUE);
                // 外枠
                DrawBox(((j + 0.3) * (mnYMax / 5) * 1.15), ((i + 0.3) * (mnYMax / 5) * 1.15),
                        ((j + 1.0) * (mnYMax / 5) * 1.15), ((i + 1.0) * (mnYMax / 5) * 1.15),
                        GetColor(0, 0, 0), FALSE);
            }
        }
    }

    for (int i = 0; i < 4; i++) {
        if ((i * 6) >= mpItems.size()) {
            break;
        }

        for (int j = 0; j < 6; j++) {
            if ((j + 1) + (i * 6) > mpItems.size()) {
                break;
            }

            mpItems[j + (i * 6)]->Draw(((j + 0.3) * (mnYMax / 5) * 1.15), ((i + 0.3) * (mnYMax / 5) * 1.15),
                                       ((0.7) *     (mnYMax / 5) * 1.15), ((0.7) *     (mnYMax / 5) * 1.15));

            DrawFormatString(((j + 0.3) * (mnYMax / 5) * 1.15), ((i + 0.14) * (mnYMax / 5) * 1.15), GetColor(0, 0, 0), "%d", mpItems[j + (i * 6)]->GetItemNumber());
        }
    }

    // 表示画面再設定
    SetDrawScreen(DX_SCREEN_BACK);
    // 3Dカメラ設定
    Master::mpCamera->Initialize3DCameraTemplate();
    DrawGraph((GetScreenSize().x / 10) * 0.7, GetScreenSize().y / 10, mnItemDrawHandle, TRUE);
}

/*
* @fn SelectDecision
* @drief 選択決定時処理
*/
void MenuItem::SelectDecision()
{
    if (mnMenuSelect < mpItems.size()) {
        mpItems[mnMenuSelect]->ItemEffect(Master::mpGameManager->GetObjectManager()->FindByTag_CharacterObject(PLAYER_TAG));

        if (mpItems[mnMenuSelect]->GetItemNumber() <= 0) {
            mpItems.clear();
            mpItems = mpDataManager->GetPlayPlayerData().item;
            mnMaxMenuSelect -= 1;
            if (mnMenuSelect >= mnMaxMenuSelect) {
                if (mnMaxMenuSelect == 0) {
                    mnMenuSelect = 0;
                    mnMaxMenuSelect = 1;
                }
                else {
                    mnMenuSelect = (mnMaxMenuSelect - 1);
                }
            }
        }
    }
}