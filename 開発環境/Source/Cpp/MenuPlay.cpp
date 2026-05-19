#include "DxLib.h"
#include "../Header/CoordinateXY.h"
#include "../Header/DataManager.h"
#include "../Header/GameManager.h"
#include "../Header/MenuCheck.h"
#include "../Header/MenuItem.h"
#include "../Header/MenuPlay.h"
#include "../Header/MenuSystem.h"
#include "../Header/Menu_Base.h"
#include "../Header/ObjectManager.h"
#include "../Header/ObjectTagMacro.h"
#include "../Header/Object_Base_Character.h"
#include "../Header/Operation.h"
#include "../Header/SceneManager.h"
#include "../Header/TimeManager.h"

/*
* @fn コンストラクタ
*/
MenuPlay::MenuPlay(Object_Base_Character *player)
: Menu_Base(6, XYGet((GetScreenSize().x / 10) * 0.7, (GetScreenSize(). y/ 10)), XYGet((GetScreenSize().x / 10) * 9.3, (GetScreenSize().y / 10) * 9), GetColor(200, 200, 200), DX_BLENDMODE_ALPHA, 230)
, mnMenuHandle(-1)
, mnSelectHandle(-1)
, mnSelectManager(0)
, mpPlayer(player)
, mnPlayerDataHandle(-1)
{
}

/*
* @fn デストラクタ
*/
MenuPlay::~MenuPlay()
{
}

/*
* @fn MyInitilize
* @drief 個別初期化処理
*/
void MenuPlay::MyInitilize()
{
    { // 文字サイズハンドル設定
        mnMenuHandle = CreateFontToHandle(NULL, 40, 9);
        mnSelectHandle = CreateFontToHandle(NULL, 30, 5);
        mnPlayerDataHandle = CreateFontToHandle(NULL, 30, 5);
    }
    SetOpenMenuSound();
}

/*
* @fn MyFinalize
* @drief 個別終了処理
*/
void MenuPlay::MyFinalize()
{
    DeleteFontToHandle(mnMenuHandle);
    DeleteFontToHandle(mnSelectHandle);
    DeleteFontToHandle(mnPlayerDataHandle);
}

/*
* @fn MyUpdate
* @drief 個別更新処理
*/
void MenuPlay::MyUpdate()
{
    switch (mnSelectManager)
    {
    case 0:
        //--選択変更関連処理--//
    
        // 左列に移動
        if (Operation::CheckLeftKey() && CheckFrame(0)) {
            if (mnMenuSelect >= 3) {
                // 時間設定
                mnChangeFrame = Master::mpGameManager->GetTimeManager()->GetFrame();

                // 選択を左にずらす
                mnMenuSelect -= 3;
            }
        }

        // 右列に移動
        if (Operation::CheckRightKey() && CheckFrame(0)) {
            if (mnMenuSelect < 3) {
                // 時間設定
                mnChangeFrame = Master::mpGameManager->GetTimeManager()->GetFrame();

                // 選択肢を右にずらす
                mnMenuSelect += 3;
            }
        }
        // 閉じる
        CheckBkey_CloseProcess();

        // デフォルトの選択変更、決定処理
        DefaultMenuSelectUpdate();
        //--------------------//
        break;

    case 1:
        if (Operation::CheckBKey() && CheckFrame(1)) {
            mnDecisionFrame = Master::mpGameManager->GetTimeManager()->GetFrame();
            mnSelectManager -= 1;
            SetCloseMenuSound();
        }
        break;
    }
}

/*
* @fn MyDraw
* @drief 個別描画化処理
*/
void MenuPlay::MyDraw()
{
    switch (mnSelectManager)
    {
    case 0:
        // 基礎描画
        DrawBoxAA((GetScreenSize().x / 10) * 4, (GetScreenSize().y / 10) * 1.5, (GetScreenSize().x / 10) * 6, (GetScreenSize().y / 10) * 2.5, GetColor(50, 50, 50), TRUE);

        DrawBoxAA((GetScreenSize().x / 10), (GetScreenSize().y / 10) * 3, (GetScreenSize().x / 10) * 4, (GetScreenSize().y / 10) * 4, ((mnMenuSelect == 0) ? GetColor(0, 0, 0) : GetColor(50, 50, 50)), TRUE);
        DrawBoxAA((GetScreenSize().x / 10), (GetScreenSize().y / 10) * 5, (GetScreenSize().x / 10) * 4, (GetScreenSize().y / 10) * 6, ((mnMenuSelect == 1) ? GetColor(0, 0, 0) : GetColor(50, 50, 50)), TRUE);
        DrawBoxAA((GetScreenSize().x / 10), (GetScreenSize().y / 10) * 7, (GetScreenSize().x / 10) * 4, (GetScreenSize().y / 10) * 8, ((mnMenuSelect == 2) ? GetColor(0, 0, 0) : GetColor(50, 50, 50)), TRUE);
        DrawBoxAA((GetScreenSize().x / 10) * 6, (GetScreenSize().y / 10) * 3, (GetScreenSize().x / 10) * 9, (GetScreenSize().y / 10) * 4, ((mnMenuSelect == 3) ? GetColor(0, 0, 0) : GetColor(50, 50, 50)), TRUE);
        DrawBoxAA((GetScreenSize().x / 10) * 6, (GetScreenSize().y / 10) * 5, (GetScreenSize().x / 10) * 9, (GetScreenSize().y / 10) * 6, ((mnMenuSelect == 4) ? GetColor(0, 0, 0) : GetColor(50, 50, 50)), TRUE);
        DrawBoxAA((GetScreenSize().x / 10) * 6, (GetScreenSize().y / 10) * 7, (GetScreenSize().x / 10) * 9, (GetScreenSize().y / 10) * 8, ((mnMenuSelect == 5) ? GetColor(0, 0, 0) : GetColor(50, 50, 50)), TRUE);
        //

        // Menu文字
        DrawStringToHandle((GetScreenSize().x / 10) * 4.34, (GetScreenSize().y / 10) * 1.6, "MENU", GetColor(255, 255, 255), mnMenuHandle);

        // 選択文字
        DrawStringToHandle((GetScreenSize().x / 10) * 1.2, (GetScreenSize().y / 10) * 3.2, "PLAYER DATA", ((mnMenuSelect == 0) ? GetColor(200, 200, 200) : GetColor(255, 255, 255)), mnSelectHandle);
        if (mpSceneManager->GetNowSceneType("MAP"))
        {
            DrawStringToHandle((GetScreenSize().x / 10) * 2, (GetScreenSize().y / 10) * 5.2, "SAVE", ((mnMenuSelect == 1) ? GetColor(200, 200, 200) : GetColor(255, 255, 255)), mnSelectHandle);
        }
        else
        {
            DrawStringToHandle((GetScreenSize().x / 10) * 2, (GetScreenSize().y / 10) * 5.2, "SAVE", GetColor(100, 100, 100), mnSelectHandle);
        }
        DrawStringToHandle((GetScreenSize().x / 10) * 1.9, (GetScreenSize().y / 10) * 7.2, "CLOSE", ((mnMenuSelect == 2) ? GetColor(200, 200, 200) : GetColor(255, 255, 255)), mnSelectHandle);
        DrawStringToHandle((GetScreenSize().x / 10) * 7, (GetScreenSize().y / 10) * 3.2, "ITEM", ((mnMenuSelect == 3) ? GetColor(200, 200, 200) : GetColor(255, 255, 255)), mnSelectHandle);
        DrawStringToHandle((GetScreenSize().x / 10) * 6.8, (GetScreenSize().y / 10) * 5.2, "SYSTEM", ((mnMenuSelect == 4) ? GetColor(200, 200, 200) : GetColor(255, 255, 255)), mnSelectHandle);
        DrawStringToHandle((GetScreenSize().x / 10) * 6.6, (GetScreenSize().y / 10) * 7.2, "GO TITLE", ((mnMenuSelect == 5) ? GetColor(200, 200, 200) : GetColor(255, 255, 255)), mnSelectHandle);
        //
        break;

    case 1:
        DrawBox((GetScreenSize().x / 10) * 0.7, (GetScreenSize().y / 10),       (GetScreenSize().x / 10) * 9.3, (GetScreenSize().y / 10) * 9, GetColor(255, 255, 255), TRUE);
        DrawBox((GetScreenSize().x / 10) * 0.8, (GetScreenSize().y / 10) * 1.1, (GetScreenSize().x / 10) * 9.2, (GetScreenSize().y / 10) * 8.9, GetColor(200, 200, 200), TRUE);
        DrawStringToHandle((GetScreenSize().x / 10) * 6.5, (GetScreenSize().y / 10) * 8.1, "\"B\"CLOSE", GetColor(0, 0, 0), mnMenuHandle);

        DrawFormatStringToHandle((GetScreenSize().x / 10) * 0.9, (GetScreenSize().y / 10) * 1.2,  GetColor(0, 0, 0), mnPlayerDataHandle, "PLAYER NAME : %s", mpDataManager->GetPlayPlayerData().characterData.templateData.name.c_str());
        DrawFormatStringToHandle((GetScreenSize().x / 10) * 0.9, (GetScreenSize().y / 10) * 1.97, GetColor(0, 0, 0), mnPlayerDataHandle, "PLAYER TYPE : %s", GetCharacterTypeName(mpDataManager->GetPlayPlayerData().characterData.templateData.typeNumber).c_str());
        DrawFormatStringToHandle((GetScreenSize().x / 10) * 0.9, (GetScreenSize().y / 10) * 2.74, GetColor(0, 0, 0), mnPlayerDataHandle, "LEVEL       : %d", mpPlayer->GetStatus().level);
        DrawFormatStringToHandle((GetScreenSize().x / 10) * 0.9, (GetScreenSize().y / 10) * 3.51, GetColor(0, 0, 0), mnPlayerDataHandle, "EXP         : %d", mpPlayer->GetStatus().exp);
        DrawFormatStringToHandle((GetScreenSize().x / 10) * 0.9, (GetScreenSize().y / 10) * 4.28, GetColor(0, 0, 0), mnPlayerDataHandle, "ATTACK      : %d", mpPlayer->GetStatus().attackPower);
        DrawFormatStringToHandle((GetScreenSize().x / 10) * 0.9, (GetScreenSize().y / 10) * 5.05, GetColor(0, 0, 0), mnPlayerDataHandle, "MAX HP      : %d", mpPlayer->GetStatus().maxHp);
        DrawFormatStringToHandle((GetScreenSize().x / 10) * 0.9, (GetScreenSize().y / 10) * 5.82, GetColor(0, 0, 0), mnPlayerDataHandle, "HP          : %d", mpPlayer->GetStatus().hp);
        DrawFormatStringToHandle((GetScreenSize().x / 10) * 0.9, (GetScreenSize().y / 10) * 6.59, GetColor(0, 0, 0), mnPlayerDataHandle, "DEFENSE     : %d", mpPlayer->GetStatus().defense);
        DrawFormatStringToHandle((GetScreenSize().x / 10) * 0.9, (GetScreenSize().y / 10) * 7.36, GetColor(0, 0, 0), mnPlayerDataHandle, "SPEED       : %d", mpPlayer->GetStatus().speed);
        DrawFormatStringToHandle((GetScreenSize().x / 10) * 0.9, (GetScreenSize().y / 10) * 8.13, GetColor(0, 0, 0), mnPlayerDataHandle, "SIZE        : %d", mpPlayer->GetStatus().size);

        break;
    }
}

/*
* @fn 
* @drief 選択決定時処理
*/
void MenuPlay::SelectDecision()
{
    switch (mnMenuSelect)
    {
    case 0: // プレイヤーデータ確認
        mnSelectManager += 1;
        break;
    case 1: // セーブ
        if (mpSceneManager->GetNowSceneType("MAP"))
        {
            MenuCheck* saveCheck;
            saveCheck = new MenuCheck(*this, &MenuPlay::SetCheckMenu_0, this);
            saveCheck->Initilize();
        }
        break;
    case 2: // メニュー終了
        SetDeleteFlag(true);
        SetDecisionSoundFlag(false);
        break;
    case 3: // アイテム
        MenuItem * menuItem;
        menuItem = new MenuItem();
        menuItem->Initilize();
        break;
    case 4: // システム(ミニマップや操作説明など)
        MenuSystem * menuSystem;
        menuSystem = new MenuSystem();
        menuSystem->Initilize();
        break;
    case 5: // ゲーム終了(確認)
        MenuCheck * endCheck;
        endCheck = new MenuCheck(*this, &MenuPlay::TitleGo, this);
        endCheck->Initilize();
        break;
    }
}

/*
* @fn SetOverride_CheckMenuProcess
* @drief チェック用関数(セーブ用)
*/
void MenuPlay::SetOverride_CheckMenuProcess()
{
    // プレイヤーデータセーブ
    {
        // プレイヤー取得
        Object_Base_Character* player = Master::mpGameManager->GetObjectManager()->FindByTag_CharacterObject(PLAYER_TAG);

        // プレイヤー情報入力
        PLAYER_DATA playerData = mpDataManager->GetPlayPlayerData();


        playerData.characterData.status = player->GetStatus();

        // マップ情報を入力
        playerData.characterData.position = player->GetObjectPosition();
        playerData.characterData.angle = player->GetObjectAngle();
        playerData.characterData.mapType = mpSceneManager->GetNowScene();

        mpDataManager->SetPlayPlayerData(playerData);
        mpDataManager->Save();

        //// プレイヤーデータ変更
        //mpDataManager->ChangeFile_PlayerFileData(mpDataManager->GetFileName_FileType(PLAYER_FILE_NAME, mpDataManager->GetBaseData_FileName()),
        //    mpDataManager->GetPlayerData(mpSceneManager->GetPlayerDataNumber()).characterData.templateData.name,
        //    playerData);

        //// ゲーム内に反映
        //mpDataManager->Initilize();
    }
}