#include <iostream>
#include <cstring>
#include <vector>

#include "DxLib.h"
#include "../Header/CoordinateXY.h"
#include "../Header/DataManager.h"
#include "../Header/DataManagerMacro.h"
#include "../Header/Data_Structs.h"
#include "../Header/GameManager.h"
#include "../Header/GraphManager.h"
#include "../Header/MenuCheck.h"
#include "../Header/MenuNewData.h"
#include "../Header/Menu_Base.h"
#include "../Header/Operation.h"
#include "../Header/TimeManager.h"

/*
* @fn コンストラクタ
*/
MenuNewData::MenuNewData()
: Menu_Base(3, XYGet(0, 0), IntXY_Change_FloatXY(GetScreenSize()), GetColor(70, 170, 255), DX_BLENDMODE_NOBLEND, 255, false, true)
, mnSelectManagerNumber(0)
, mbWordSize(false)
, mnMaxNameNumber(0)
, mnSelectHeight(0)
, mnSelectWidth(0)
, mnPlayerTypeNumber(0)
, mnAlphabetHandle(-1)
, mnNameHandle(-1)
, mnNotAlphabetHandle(-1)
, mbDrawUpKeyFlag(false)
, mbDrawDownKeyFlag(false)
{
    for (int i = 0; i < 1; i++) {
        mnPlayerTypeModelHandle[i] = -1;
        for (int j = 0; j < 4; j++) {
            mfPlayerTypeModelDrawPos[j][i] = 0;
        }
    }

    strncpy_s(mcPlayerNameSet[0][0], "0123456789", sizeof(mcPlayerNameSet[0][0]) - 1);
    strncpy_s(mcPlayerNameSet[0][1], "abcdefghij", sizeof(mcPlayerNameSet[0][1]) - 1);
    strncpy_s(mcPlayerNameSet[0][2], "klmnopqrst", sizeof(mcPlayerNameSet[0][2]) - 1);
    strncpy_s(mcPlayerNameSet[0][3], "uvwxyz()<>", sizeof(mcPlayerNameSet[0][3]) - 1);
    strncpy_s(mcPlayerNameSet[0][4], " %+-!$.:  ", sizeof(mcPlayerNameSet[0][4]) - 1);

    strncpy_s(mcPlayerNameSet[1][0], "0123456789", sizeof(mcPlayerNameSet[1][0]) - 1);
    strncpy_s(mcPlayerNameSet[1][1], "ABCDEFGHIJ", sizeof(mcPlayerNameSet[1][1]) - 1);
    strncpy_s(mcPlayerNameSet[1][2], "KLMNOPQRST", sizeof(mcPlayerNameSet[1][2]) - 1);
    strncpy_s(mcPlayerNameSet[1][3], "UVWXYZ{}[]", sizeof(mcPlayerNameSet[1][3]) - 1);
    strncpy_s(mcPlayerNameSet[1][4], " /*=?@,;  ", sizeof(mcPlayerNameSet[1][4]) - 1);
}

/*
* @fn デストラクタ
*/
MenuNewData::~MenuNewData()
{
}

/*
* @fn MyInitilize
* @drief 個別初期化処理
*/
void MenuNewData::MyInitilize()
{
    // 文字サイズ設定
    {
        mnNotAlphabetHandle = CreateFontToHandle(NULL, 12, 5);
        mnNameHandle = CreateFontToHandle(NULL, 25, 5);
        mnAlphabetHandle = CreateFontToHandle(NULL, 30, 7);
    }

    // プレイヤータイプ別画像取得
    mnPlayerTypeModelHandle[0] = Master::mpGameManager->GerGraphManager()->GetGraphHandle(GRAPH_TYPE::ROBOT_CHARACTER);
    mfPlayerTypeModelDrawPos[0][0] = (3 * (GetScreenSize().x / 5) * 0.45);
    mfPlayerTypeModelDrawPos[1][0] = ((0 + 0.1 + 4) * (GetScreenSize().y / 5) * 0.5);
    mfPlayerTypeModelDrawPos[2][0] = (8 * (GetScreenSize().x / 5) * 0.45);
    mfPlayerTypeModelDrawPos[3][0] = ((4 + 1.0 + 4) * (GetScreenSize().y / 5) * 0.5);
}

/*
* @fn MyFinalize
* @drief 個別終了処理
*/
void MenuNewData::MyFinalize()
{
    DeleteFontToHandle(mnNotAlphabetHandle);
    DeleteFontToHandle(mnNameHandle);
    DeleteFontToHandle(mnAlphabetHandle);
}

/*
* @fn MyUpdate
* @drief 個別更新処理
*/
void MenuNewData::MyUpdate()
{
    switch (mnSelectManagerNumber)
    {
    case 0: // 新しく作るデータは何処にあるか取得する

        // 上キーを押したときの選択変更処理
        DefaultUpKeyProcess();

        // 下キーを押したときの選択変更処理
        DefaultDownKeyProcess();


        if (Operation::CheckBKey() && CheckFrame(1)) {
            mnDecisionFrame = Master::mpGameManager->GetTimeManager()->GetFrame();
            SetDeleteFlag(true);
        }
        if (Operation::CheckAKey() && CheckFrame(1)) {
            mnDecisionFrame = Master::mpGameManager->GetTimeManager()->GetFrame();
            mstrPlayerName.clear();
            mnSelectManagerNumber += 1;
            SetSelectDecisionSound();
        }
        break;

    case 1: // ネーム決定
        if (CheckLeftKeyAndFrame()) {
            mnSelectWidth -= 1;
            if (mnSelectWidth < 0) {
                mnSelectWidth = (10 - 1);
            }
            SetSelectChangeSound();
        }
        if (CheckRightKeyAndFrame()) {
            mnSelectWidth += 1;
            if (mnSelectWidth >= 10) {
                mnSelectWidth = 0;
            }
            SetSelectChangeSound();
        }

        if (CheckUpKeyAndFrame()) {
            mnSelectHeight -= 1;
            if (mnSelectHeight < 0) {
                mnSelectHeight = (5 - 1);
            }
            SetSelectChangeSound();
        }
        if (CheckDownKeyAndFrame()) {
            mnSelectHeight += 1;
            if (mnSelectHeight >= 5) {
                mnSelectHeight = 0;
            }
            SetSelectChangeSound();
        }

        if (Operation::CheckRKey() && CheckFrame(1)) {
            mnDecisionFrame = Master::mpGameManager->GetTimeManager()->GetFrame();
            mbWordSize = (mbWordSize ? false : true);
        }

        if (Operation::CheckBKey() && CheckFrame(1)) {
            mnDecisionFrame = Master::mpGameManager->GetTimeManager()->GetFrame();
            mnSelectManagerNumber -= 1;
            SetCloseMenuSound();
        }
        if (Operation::CheckAKey() && CheckFrame(1)) {
            mnDecisionFrame = Master::mpGameManager->GetTimeManager()->GetFrame();
            SetPlayerNameProcess();
        }
        break;

    case 2: // プレイヤータイプ決定

        if (CheckUpKeyAndFrame()) {
            mnPlayerTypeNumber -= 1;
            mbDrawUpKeyFlag = true;
            mbDrawDownKeyFlag = false;
            if (mnPlayerTypeNumber < 0) {
                mnPlayerTypeNumber = 0;
            }
            SetSelectChangeSound();
        }
        else if (CheckFrame(0)) {
            mbDrawUpKeyFlag = false;
        }

        if (CheckDownKeyAndFrame()) {
            mnPlayerTypeNumber += 1;
            mbDrawDownKeyFlag = true;
            mbDrawUpKeyFlag = false;
            if (mnPlayerTypeNumber >= mpDataManager->GetInitPlayerData().size()) {
                mnPlayerTypeNumber = (mpDataManager->GetInitPlayerData().size() - 1);
            }
            SetSelectChangeSound();
        }
        else if (CheckFrame(0)) {
            mbDrawDownKeyFlag = false;
        }

        if (Operation::CheckBKey() && CheckFrame(1)) {
            mnDecisionFrame = Master::mpGameManager->GetTimeManager()->GetFrame();
            mnSelectManagerNumber -= 1;
            SetCloseMenuSound();
        }

        // 選択決定処理
        CheckDecision_AKeyAndFrame();
        break;
    }

}

/*
* @fn MyDraw
* @drief 個別描画化処理
*/
void MenuNewData::MyDraw()
{
        // 戻る操作文字描画
        DrawBoxAA(0, (GetScreenSize().y / 10) * 9.5, (GetScreenSize().x / 10) * 1.5, GetScreenSize().y, GetColor(255, 255, 255), TRUE);
        DrawString((GetScreenSize().x / 10) * 0.1, (GetScreenSize().y / 10) * 9.6, "\"B\"BACK", GetColor(0, 0, 0));

    switch (mnSelectManagerNumber)
    {
    case 0:
        // プレイヤー
        DrawPlayerDatas();

        // 新データ文字描画
        DrawBoxAA(0, 0, (GetScreenSize().x / 10) * 0.8, (GetScreenSize().y / 10) * 0.9, GetColor(255, 255, 255), TRUE);
        DrawString((GetScreenSize().x / 10) * 0.1, (GetScreenSize().y / 10) * 0.1, "NEW\nDATA", GetColor(0, 0, 0));

        break;

    case 1:
        // 名前入力中　文字描画
        DrawBoxAA(0, 0, (GetScreenSize().x / 10) * 0.9, (GetScreenSize().y / 10) * 0.9, GetColor(255, 255, 255), TRUE);
        DrawString((GetScreenSize().x / 10) * 0.1, (GetScreenSize().y / 10) * 0.1, "NAME\nINPUT", GetColor(0, 0, 0));

        // 全角/半角操作描画
        DrawBoxAA((GetScreenSize().x / 10) * 7.9, (GetScreenSize().y / 10) * 9.5, GetScreenSize().x, GetScreenSize().y, GetColor(255, 255, 255), TRUE);
        DrawString((GetScreenSize().x / 10) * 8, (GetScreenSize().y / 10) * 9.6, (mbWordSize ? "\"R\"half-width" : "\"R\"full-width"), GetColor(0, 0, 0));

        // 入力中の名前を描画
        DrawBox((GetScreenSize().x / 5) * 1, (GetScreenSize().y / 5) * 0.5,
            (GetScreenSize().x / 5) * 4, (GetScreenSize().y / 5) * 1, GetColor(255, 255, 255), TRUE);
        DrawFormatStringToHandle((GetScreenSize().x / 5) * 1.4, (GetScreenSize().y / 5) * 0.6, GetColor(0, 0, 0), mnNameHandle, "%s", mstrPlayerName.c_str());
        // 現在の名前が使用可能か描画
        bool outDataNameFlag;
        outDataNameFlag = false;
        for (int i = 0; i < 3; i++) {
            if (mpDataManager->GetPlayerData()[i].dataFlag) {
                if ((mpDataManager->GetPlayerData()[i].characterData.templateData.name == mstrPlayerName) && (mnMenuSelect != i)) {
                    DrawStringToHandle((GetScreenSize().x / 5) * 1, (GetScreenSize().y / 5) * 0.6, "×", GetColor(255, 0, 0), mnAlphabetHandle);
                    outDataNameFlag = true;
                    break;
                }
            }
        }

        // 入力用文字全描画
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 10; j++) {
                if ((i == 4) && (j == 9)) {
                    DrawBox(((j + 0.1 + 0.5) * (GetScreenSize().x / 5) * 0.45), ((i + 0.1 + 4) * (GetScreenSize().y / 5) * 0.5),
                        ((j + 1.0 + 0.5) * (GetScreenSize().x / 5) * 0.45), ((i + 1.0 + 4) * (GetScreenSize().y / 5) * 0.5),
                        ((mstrPlayerName.size() > 0) && !outDataNameFlag) ? (((i == mnSelectHeight) && (j == mnSelectWidth)) ? GetColor(200, 200, 200) : GetColor(255, 255, 255)) : (((i == mnSelectHeight) && (j == mnSelectWidth)) ? GetColor(50, 50, 50) : GetColor(100, 100, 100)), TRUE);
                }
                else if ((i == 4) && ((j == 8) || (j == 0))) {
                    DrawBox(((j + 0.1 + 0.5) * (GetScreenSize().x / 5) * 0.45), ((i + 0.1 + 4) * (GetScreenSize().y / 5) * 0.5),
                        ((j + 1.0 + 0.5) * (GetScreenSize().x / 5) * 0.45), ((i + 1.0 + 4) * (GetScreenSize().y / 5) * 0.5),
                        (mstrPlayerName.size() > 0) ? (((i == mnSelectHeight) && (j == mnSelectWidth)) ? GetColor(200, 200, 200) : GetColor(255, 255, 255)) : (((i == mnSelectHeight) && (j == mnSelectWidth)) ? GetColor(50, 50, 50) : GetColor(100, 100, 100)), TRUE);
                }
                else {
                    DrawBox(((j + 0.1 + 0.5) * (GetScreenSize().x / 5) * 0.45), ((i + 0.1 + 4) * (GetScreenSize().y / 5) * 0.5),
                        ((j + 1.0 + 0.5) * (GetScreenSize().x / 5) * 0.45), ((i + 1.0 + 4) * (GetScreenSize().y / 5) * 0.5),
                        (mstrPlayerName.size() <= 20) ? (((i == mnSelectHeight) && (j == mnSelectWidth)) ? GetColor(200, 200, 200) : GetColor(255, 255, 255)) : (((i == mnSelectHeight) && (j == mnSelectWidth)) ? GetColor(50, 50, 50) : GetColor(100, 100, 100)), TRUE);
                }

                if ((i == 4) && ((j == 0) || (j == 8) || (j == 9))) {
                    switch (j) {
                    case 0:
                        DrawStringToHandle(((j + 0.3 + 0.5) * (GetScreenSize().x / 5) * 0.45), ((i + 0.4 + 4) * (GetScreenSize().y / 5) * 0.5), "Clear", GetColor(0, 0, 0), mnNotAlphabetHandle);
                        break;
                    case 8:
                        DrawStringToHandle(((j + 0.2 + 0.5) * (GetScreenSize().x / 5) * 0.45), ((i + 0.4 + 4) * (GetScreenSize().y / 5) * 0.5), "Delete", GetColor(0, 0, 0), mnNotAlphabetHandle);
                        break;
                    case 9:
                        DrawStringToHandle(((j + 0.14 + 0.5) * (GetScreenSize().x / 5) * 0.45), ((i + 0.4 + 4) * (GetScreenSize().y / 5) * 0.5), "Decision", GetColor(0, 0, 0), mnNotAlphabetHandle);
                        break;
                    }
                }
                else {
                    DrawFormatStringToHandle(((j + 0.4 + 0.5) * (GetScreenSize().x / 5) * 0.45), ((i + 0.3 + 4) * (GetScreenSize().y / 5) * 0.5), GetColor(0, 0, 0), mnAlphabetHandle,
                        "%c", mcPlayerNameSet[mbWordSize ? 1 : 0][i][j]);
                }
            }
        }
        break;

    case 2:
        // プレイヤータイプ選択　文字描画
        DrawBoxAA(0, 0, (GetScreenSize().x / 10) * 1.1, (GetScreenSize().y / 10) * 0.9, GetColor(255, 255, 255), TRUE);
        DrawString((GetScreenSize().x / 10) * 0.1, (GetScreenSize().y / 10) * 0.1, "TYPE\nSELECT", GetColor(0, 0, 0));

        // 入力中タイプ描画
        DrawBox((GetScreenSize().x / 5) * 1, (GetScreenSize().y / 5) * 0.5,
            (GetScreenSize().x / 5) * 4, (GetScreenSize().y / 5) * 1, GetColor(255, 255, 255), TRUE);
        DrawFormatStringToHandle((GetScreenSize().x / 5) * 1.2, (GetScreenSize().y / 5) * 0.6, GetColor(0, 0, 0), mnAlphabetHandle, "%s", mpDataManager->GetInitPlayerData()[mnPlayerTypeNumber].characterData.templateData.name.c_str());
        
        // 上下図形描画
        // 上
        DrawTriangleAA((GetScreenSize().x / 5) * 1, (GetScreenSize().y / 5) * 0.4,
                       (GetScreenSize().x / 5) * 4, (GetScreenSize().y / 5) * 0.4,
                       (GetScreenSize().x / 5) * 2.5, (GetScreenSize().y / 5) * 0.1,
            (mbDrawUpKeyFlag ? GetColor(200, 200, 200) : GetColor(255, 255, 255)), TRUE);
        // 下
        DrawTriangleAA((GetScreenSize().x / 5) * 1, (GetScreenSize().y / 5) * 1.1,
                       (GetScreenSize().x / 5) * 4, (GetScreenSize().y / 5) * 1.1,
                       (GetScreenSize().x / 5) * 2.5, (GetScreenSize().y / 5) * 1.4,
            (mbDrawDownKeyFlag ? GetColor(200, 200, 200) : GetColor(255, 255, 255)), TRUE);

        DrawExtendGraph(mfPlayerTypeModelDrawPos[0][mnPlayerTypeNumber], mfPlayerTypeModelDrawPos[1][mnPlayerTypeNumber], mfPlayerTypeModelDrawPos[2][mnPlayerTypeNumber], mfPlayerTypeModelDrawPos[3][mnPlayerTypeNumber], 
            mnPlayerTypeModelHandle[mnPlayerTypeNumber], FALSE);
        break;
    }
}

/*
* @fn SelectDecision
* @drief 選択決定時処理
*/
void MenuNewData::SelectDecision()
{
    MenuCheck *menuCheck = new MenuCheck(*this, &MenuNewData::SetCheckMenu_0, this);
    menuCheck->Initilize();

}

/*
* @fn SetPlayerNameProcess
* @drief プレイヤー名設定処理
*/
void MenuNewData::SetPlayerNameProcess()
{
    if ((mnSelectHeight == 4) && ((mnSelectWidth == 0) || (mnSelectWidth == 8) || (mnSelectWidth == 9))) {
        switch (mnSelectWidth)
        {
        case 0:
            if (mstrPlayerName.size() > 0) {
                mstrPlayerName.clear();
                SetSelectDecisionSound();
            }
            else {
                SetBeepSound();
            }
            break;
        case 8: // 一文字消す
            if (mstrPlayerName.size() > 0) {
                mstrPlayerName.pop_back();
                SetSelectDecisionSound();
            }
            else {
                SetBeepSound();
            }
            break;
        case 9: // 決定
            for (int i = 0; i < 3; i++) {
                if ((mpDataManager->GetPlayerData()[i].characterData.templateData.name == mstrPlayerName) && (mnMenuSelect != i)) {
                    SetBeepSound();
                    return;
                }
            }
            if (mstrPlayerName.size() > 0) {
                mnSelectManagerNumber += 1;
                SetSelectDecisionSound();
            }
            else {
                SetBeepSound();
            }
            break;
        }
    }
    else {
        if (mstrPlayerName.size() <= 20) {
            mstrPlayerName.append(1, mcPlayerNameSet[mbWordSize ? 1 : 0][mnSelectHeight][mnSelectWidth]);
            SetSelectDecisionSound();
        }
        else {
            SetBeepSound();
        }
    }
}

/*
* @fn SetOverride_CheckMenuProcess
* @drief チェック用関数(新データ作成用)
*/
void MenuNewData::SetOverride_CheckMenuProcess()
{
    std::string playerNumber;
    switch (mnMenuSelect)
    {
    case 0:
        playerNumber = "0";
        break;
    case 1:
        playerNumber = "1";
        break;
    case 2:
        playerNumber = "2";
        break;
    }

    PLAYER_DATA playerData = mpDataManager->GetInitPlayerData()[mnPlayerTypeNumber];

    // 設定した情報を入力
    playerData.characterData.templateData.name = mstrPlayerName;
    playerData.playerFolderName = (playerData.playerFolderName + playerNumber);
    playerData.dataFlag = true;

    // プレイヤーファイルデータ削除
    mpDataManager->PlayDataDelete(mnMenuSelect);

    // プレイヤーデータ変更
    mpDataManager->SetPlayPlayerData(playerData);

    // データ初期化
    mpDataManager->Save();

    SetDrawPlayerHandle();

    SetDeleteFlag(true);
}