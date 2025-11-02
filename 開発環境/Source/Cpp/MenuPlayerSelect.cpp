#include "DxLib.h"
#include "../Header/CoordinateXY.h"
#include "../Header/DataManager.h"
#include "../Header/Data_Structs.h"
#include "../Header/GameManager.h"
#include "../Header/MenuCheck.h"
#include "../Header/MenuNewData.h"
#include "../Header/MenuPlayerDataReSet.h"
#include "../Header/Menu_Base.h"
#include "../Header/MenuPlayerSelect.h"
#include "../Header/Operation.h"
#include "../Header/SceneManager.h"
#include "../Header/Scene_Enum.h"
#include "../Header/TimeManager.h"

/*
* @fn コンストラクタ
*/
MenuPlayerSelect::MenuPlayerSelect()
: Menu_Base(Master::mpGameManager->GetDataManager()->GetPlayerData().size(), XYGet(0.0f, 0.0f), IntXY_Change_FloatXY(GetScreenSize()), GetColor(50, 150, 255), DX_BLENDMODE_NOBLEND, 255, false, true)
{
}

/*
* @fn デストラクタ
*/
MenuPlayerSelect::~MenuPlayerSelect()
{
}

/*
* @fn MyInitilize
* @drief 初期化処理
*/
void MenuPlayerSelect::MyInitilize()
{
}

/*
* @fn MyFinalize
* @drief 終了処理
*/
void MenuPlayerSelect::MyFinalize()
{
}

/*
* @fn Update
* @drief 更新処理
*/
void MenuPlayerSelect::MyUpdate()
{
    // デフォルトの選択変更
    DefaultMenuSelectUpdate();

    // データリセット
    if (Operation::CheckLKey() && CheckFrame(1)) {
        mnDecisionFrame = Master::mpGameManager->GetTimeManager()->GetFrame();
        MenuPlayerDataReSet *menuPlayerDataReSet = new MenuPlayerDataReSet();
        menuPlayerDataReSet->Initilize();
        SetSelectDecisionSound();
    }

    // 新データセット
    if (Operation::CheckRKey() && CheckFrame(1)) {
        mnDecisionFrame = Master::mpGameManager->GetTimeManager()->GetFrame();
        MenuNewData *menuNewData = new MenuNewData();
        menuNewData->Initilize();
        SetSelectDecisionSound();
    }

    // タイトル移動
    if (Operation::CheckBKey() && CheckFrame(1)) {
        mnDecisionFrame = Master::mpGameManager->GetTimeManager()->GetFrame();
        Master::mpGameManager->GetSceneManager()->SetNextScene(SCENE::TITLE);
        SetDecreaseMenuNumber();
        SetCloseMenuSound();
    }
}

/*
* @fn MyDraw
* @drief 描画処理
*/
void MenuPlayerSelect::MyDraw()
{
    // プレイヤー
    DrawPlayerDatas();
    //for (int i = 0; i < 3; i++) {
    //    if (mnMenuSelect == i) {
    //        DrawBoxAA(msLowerRight.x / 6, (msLowerRight.y / 24) * (1 + (i * 8)), (msLowerRight.x / 6) * 5, (msLowerRight.y / 24) * (7 + (i * 8)), GetColor(0, 0, 255), TRUE);
    //    }
    //    else {
    //        DrawBoxAA(msLowerRight.x / 6, (msLowerRight.y / 24) * (1 + (i * 8)), (msLowerRight.x / 6) * 5, (msLowerRight.y / 24) * (7 + (i * 8)), GetColor(0, 0, 100), TRUE);
    //    }
    //    if (mpDataManager->GetPlayerData(i).dataFlag) {
    //        DrawFormatString(msLowerRight.x / 6, (msLowerRight.y / 24) * (1 + (i * 8)), GetColor(255.0f, 255.0f, 255.0f), "SAVE DATA %d", i);
    //        DrawFormatString(msLowerRight.x / 6, (msLowerRight.y / 24) * (2 + (i * 8)), GetColor(255.0f, 255.0f, 255.0f), "PLAYER NAME : %s", mpDataManager->GetPlayerData(i).characterData.templateData.name.c_str());
    //        DrawFormatString(msLowerRight.x / 6, (msLowerRight.y / 24) * (3 + (i * 8)), GetColor(255.0f, 255.0f, 255.0f), "CHARACTER TYPE : %s", mpDataManager->GetPlayerData(i).characterData.templateData.typeName.c_str());
    //        DrawFormatString(msLowerRight.x / 6, (msLowerRight.y / 24) * (4 + (i * 8)), GetColor(255.0f, 255.0f, 255.0f), "MAP NAME : %s", mpDataManager->GetPlayerData(i).characterData.mapName.c_str());
    //        DrawFormatString(msLowerRight.x / 6, (msLowerRight.y / 24) * (5 + (i * 8)), GetColor(255.0f, 255.0f, 255.0f), "HP:%-5d      DEFENSE:%d", mpDataManager->GetPlayerData(i).characterData.status.hp, mpDataManager->GetPlayerData(0).characterData.status.defense);
    //        DrawFormatString(msLowerRight.x / 6, (msLowerRight.y / 24) * (6 + (i * 8)), GetColor(255.0f, 255.0f, 255.0f), "ATTACK:%-4d   SPEED:%d", mpDataManager->GetPlayerData(i).characterData.status.attackPower, mpDataManager->GetPlayerData(0).characterData.status.speed);

    //        if (mnMenuSelect == i) {
    //            DrawString((msLowerRight.x / 6) * 3.9, (msLowerRight.y / 24) * (6 + (i * 8)), "\"A\" DECISION", GetColor(255, 255, 255));
    //        }
    //    }
    //    else {
    //       // DrawStringToHandle(msLowerRight.x / 6, (msLowerRight.y / 24) * (1 + (i * 8)), "NO DATA", GetColor(255, 255, 255), mnNotPlayerDataHandle);
    //    }
    //}

    // データ削除操作描画
    DrawBoxAA(0, (GetScreenSize().y / 10) * 9.5, (GetScreenSize().x / 10) * 1.5, GetScreenSize().y, GetColor(255, 255, 255), TRUE);
    DrawString((GetScreenSize().x / 10) * 0.1, (GetScreenSize().y / 10) * 9.6, "\"L\"DELETE", GetColor(0, 0, 0));

    // ニューデータ操作描画
    DrawBoxAA((GetScreenSize().x / 10) * 8.5, (GetScreenSize().y / 10) * 9.5, GetScreenSize().x, GetScreenSize().y, GetColor(255, 255, 255), TRUE);
    DrawString((GetScreenSize().x / 10) * 8.8, (GetScreenSize().y / 10) * 9.6, "\"R\"NEW", GetColor(0, 0, 0));

    // セーブ選択文字描画
    DrawBoxAA(0, 0, (GetScreenSize().x / 10) * 1.1, (GetScreenSize().y / 10) * 0.9, GetColor(255, 255, 255), TRUE);
    DrawString((GetScreenSize().x / 10) * 0.1, (GetScreenSize().y / 10) * 0.1, "DATA\nSELECT", GetColor(0, 0, 0));
}

/*
* @fn SelectDecision
* @drief 選択決定時処理
*/
void MenuPlayerSelect::SelectDecision()
{
    /*
    * ここでプレイヤーデータ関連設定
    */
    if (mpDataManager->GetPlayerData()[mnMenuSelect].dataFlag) {
        MenuCheck* menuCheck = new MenuCheck(*this, &MenuPlayerSelect::SetCheckMenu_0, this);
        menuCheck->Initilize();
    }
}

/*
* @fn SetOverride_CheckMenuProcess
* @drief チェックメニュー用関数(ゲーム移行)
*/
void MenuPlayerSelect::SetOverride_CheckMenuProcess()
{
    // プレイヤーナンバー設定
    mpSceneManager->SetPlayerDataNumber(mnMenuSelect);
    // データを設定
    mpDataManager->SetPlayPlayer(mnMenuSelect);
    // シーン移動
    mpSceneManager->SetNextScene(mpDataManager->GetPlayPlayerData().characterData.mapType);

}