#include "DxLib.h"
#include "../Header/CoordinateXY.h"
#include "../Header/GameManager.h"
#include "../Header/MenuSystem.h"
#include "../Header/Menu_Base.h"
#include "../Header/ObjectManager.h"
#include "../Header/ObjectTagMacro.h"
#include "../Header/Object_Base.h"
#include "../Header/Operation.h"
#include "../Header/StageManagerObject.h"
#include "../Header/SoundManager.h"
#include "../Header/TimeManager.h"

/*
* @fn コンストラクタ
*/
MenuSystem::MenuSystem()
:Menu_Base(4, XYGet((GetScreenSize().x / 10) * 0.7, (GetScreenSize().y / 10)), XYGet((GetScreenSize().x / 10) * 9.3, (GetScreenSize().y / 10) * 9), GetColor(0, 0, 0), DX_BLENDMODE_NOBLEND)
, mpStageManager(nullptr)
, mnSelectManagerNumber(0)
, mnSystemDrawHandle(-1)
, mbDrawRightKeyFlag(false)
, mbDrawLeftKeyFlag(false)
, mbDrawUpKeyFlag(false)
, mbDrawDownKeyFlag(false)
, mnManualDrawHandle(-1)
, mnSystemBackSoundDrawHandle(-1)
, mpSoundManager(nullptr)
, mbTestSoundFlag(false)
{
}

/*
* @fn デストラクタ
*/
MenuSystem::~MenuSystem()
{
}

/*
* @fn MyInitilize
* @drief 個別初期化処理
*/
void MenuSystem::MyInitilize()
{
    Object_Base *setObject = Master::mpGameManager->GetObjectManager()->FindByTag(STAGE_MANAGER_TAG);

    mpStageManager = dynamic_cast<StageManagerObject *>(setObject);
    
    mpSoundManager = Master::mpGameManager->GetSoundManager();

    // 文字サイズ設定
    {
        mnSystemBackSoundDrawHandle = CreateFontToHandle(NULL, 55, 10);
        mnSystemDrawHandle = CreateFontToHandle(NULL, 65, 10);
        mnManualDrawHandle = CreateFontToHandle(NULL, 50, 10);
    }
}

/*
* @fn MyFinalize
* @drief 個別終了処理
*/
void MenuSystem::MyFinalize()
{
    DeleteFontToHandle(mnSystemBackSoundDrawHandle);
    DeleteFontToHandle(mnSystemDrawHandle);
    DeleteFontToHandle(mnManualDrawHandle);
}

/*
* @fn MyUpdate
* @drief 個別更新処理
*/
void MenuSystem::MyUpdate()
{
    switch (mnSelectManagerNumber)
    {
    case 0:
        // 選択変更
        DefaultMenuSelectUpdate();

        // 閉じる
        CheckBkey_CloseProcess();
        break;
    case 1:

        mbDrawRightKeyFlag = Operation::CheckRightKey();
        mbDrawLeftKeyFlag = Operation::CheckLeftKey();
        mbDrawUpKeyFlag = Operation::CheckUpKey();
        mbDrawDownKeyFlag = Operation::CheckDownKey();
        switch (mnMenuSelect)
        {
        case 0:
            break;
        case 1:
            mpStageManager->MapMagnification();
            break;

        case 2:
            if (mbDrawRightKeyFlag) {
                mpSoundManager->UpBackSoundVolume(1);
            }
            if (mbDrawUpKeyFlag) {
                mpSoundManager->UpBackSoundVolume(5);
            }

            if (mbDrawLeftKeyFlag) {
                mpSoundManager->DownBackSoundVolume(1);
            }
            if (mbDrawDownKeyFlag) {
                mpSoundManager->DownBackSoundVolume(5);
            }

            // バックサウンドセット
            if (GetAllDrawFlag()) {
                mpSoundManager->SetBackSoundVolumeProcess();
            }
            break;
        case 3:
            if (mbDrawRightKeyFlag) {
                mpSoundManager->UpSoundVolume(1);
            }
            if (mbDrawUpKeyFlag) {
                mpSoundManager->UpSoundVolume(5);
            }

            if (mbDrawLeftKeyFlag) {
                mpSoundManager->DownSoundVolume(1);
            }
            if (mbDrawDownKeyFlag) {
                mpSoundManager->DownSoundVolume(5);
            }

            // 音を鳴らす
            if (Operation::CheckAKey()) {
                if (!mbTestSoundFlag && CheckFrame(1)) {
                    mnDecisionFrame = Master::mpGameManager->GetTimeManager()->GetFrame();

                    SetSelectDecisionSound();
                    mbTestSoundFlag = true;
                }
            }
            else {
                if (mbTestSoundFlag) {
                    mbTestSoundFlag = false;
                }
            }

            //// サウンドセット
            //if (GetAllDrawFlag()) {
            //    mpSoundManager->SetSoundVolumeProcess();
            //}
            break;
        }

        if (Operation::CheckBKey() && CheckFrame(1)) {
            mnDecisionFrame = Master::mpGameManager->GetTimeManager()->GetFrame();
            SelectDecision();
            SetCloseMenuSound();
        }
        break;

    }
}

/*
* @fn MyDraw
* @drief 個別描画化処理
*/
void MenuSystem::MyDraw()
{
    switch (mnSelectManagerNumber)
    {
    case 0:
            for (int i = 0; i < 4; i++) {
                DrawBox((GetScreenSize().x / 10) * 0.8, (GetScreenSize().y / 10) * (1.1 + ((7.8 / 4) * i)), 
                        (GetScreenSize().x / 10) * 9.2, (GetScreenSize().y / 10) * (1.1 + ((7.8 / 4) * (i + 1))), 
                    ((i == mnMenuSelect) ? GetColor(100, 100, 100) : GetColor(200, 200, 200)), TRUE);
            }
            
            DrawStringToHandle((GetScreenSize().x / 10) * 3.4, (GetScreenSize().y / 10) * (1.4 + ((7.8 / 4) * 0)), "MANUAL", GetColor(0, 0, 0), mnSystemDrawHandle);
            DrawStringToHandle((GetScreenSize().x / 10) * 1.0, (GetScreenSize().y / 10) * (1.4 + ((7.8 / 4) * 1)), "MAP SIZE CHANGE", GetColor(0, 0, 0), mnSystemDrawHandle);
            DrawStringToHandle((GetScreenSize().x / 10) * 1.15, (GetScreenSize().y / 10) * (1.4 + ((7.8 / 4) * 2)), "BACK SOUND VOLUME", GetColor(0, 0, 0), mnSystemBackSoundDrawHandle);
            DrawStringToHandle((GetScreenSize().x / 10) * 1.7, (GetScreenSize().y / 10) * (1.4 + ((7.8 / 4) * 3)), "SOUND VOLUME", GetColor(0, 0, 0), mnSystemDrawHandle);
        break;
    case 1:
        DrawBox((GetScreenSize().x / 10) * 0.8, (GetScreenSize().y / 10) * 1.1, (GetScreenSize().x / 10) * 9.2, (GetScreenSize().y / 10) * 8.9, GetColor(200, 200, 200), TRUE);
        switch (mnMenuSelect)
        {
        case 0:
            DrawBox((GetScreenSize().x / 10) * 0.8, (GetScreenSize().y / 10) * 1.1, (GetScreenSize().x / 10) * 4.2, (GetScreenSize().y / 10) * 2.7, GetColor(0, 0, 0), TRUE);
            DrawBox((GetScreenSize().x / 10) * 0.8, (GetScreenSize().y / 10) * 1.1, (GetScreenSize().x / 10) * 4.1, (GetScreenSize().y / 10) * 2.6, GetColor(100, 100, 100), TRUE);
            DrawStringToHandle((GetScreenSize().x / 10) * 0.9, (GetScreenSize().y / 10) * 1.2, "MANUAL", GetColor(255, 255, 255), mnSystemDrawHandle);

            DrawBox((GetScreenSize().x / 10) * 0.8, (GetScreenSize().y / 10) * 2.6, (GetScreenSize().x / 10) * 9.2, (GetScreenSize().y / 10) * 8.3, GetColor(0, 0, 0), TRUE);
            DrawBox((GetScreenSize().x / 10) * 0.8, (GetScreenSize().y / 10) * 2.7, (GetScreenSize().x / 10) * 9.2, (GetScreenSize().y / 10) * 8.2, GetColor(100, 100, 100), TRUE);
            DrawStringToHandle((GetScreenSize().x / 10) * 0.9, (GetScreenSize().y / 10) * 2.8, "↑→←↓...MOVE\nRL...CAMERA_MOVE\nA...ATTACK, DECISION\nX...MENU\nB...CANCE", GetColor(255, 255, 255), mnManualDrawHandle);
            break;
        case 1:
            
            // マップの描画
            mpStageManager->MapDraw();
            mpStageManager->DrawMapRate((GetScreenSize().x / 3) * 2, (GetScreenSize().y / 3), (GetScreenSize().x / 3), (GetScreenSize().y / 3), (GetScreenSize().y / 10) * 0.1, GetColor(255, 255, 255));

            DrawBox((GetScreenSize().x / 10) * 1.3, (GetScreenSize().y / 10) * 4, (GetScreenSize().x / 10) * 3.1, (GetScreenSize().y / 10) * 5.3, GetColor(255, 255, 255), TRUE);
            DrawStringToHandle((GetScreenSize().x / 10) * 1.4, (GetScreenSize().y / 3) * 1.2, "MIN", GetColor(0, 0, 0), mnSystemDrawHandle);

            DrawBox((GetScreenSize().x / 10) * 6.9, (GetScreenSize().y / 10) * 4, (GetScreenSize().x / 10) * 8.7, (GetScreenSize().y / 10) * 5.3, GetColor(255, 255, 255), TRUE);
            DrawStringToHandle((GetScreenSize().x / 10) * 7, (GetScreenSize().y / 3) * 1.2, "MAX", GetColor(0, 0, 0), mnSystemDrawHandle);

            // 左
            DrawTriangleAA((GetScreenSize().x / 6) * 2.9, (GetScreenSize().y / 10) * 4,
                           (GetScreenSize().x / 6) * 2.9, (GetScreenSize().y / 10) * 8,
                           (GetScreenSize().x / 10) * 3.1, (GetScreenSize().y / 10) * 6, 
                (mbDrawLeftKeyFlag ? GetColor(100, 100, 100) : GetColor(255, 255, 255)), TRUE);
            // 右
            DrawTriangleAA((GetScreenSize().x / 6) * 3.1, (GetScreenSize().y / 10) * 4,
                           (GetScreenSize().x / 6) * 3.1, (GetScreenSize().y / 10) * 8,
                           (GetScreenSize().x / 10) * 6.9, (GetScreenSize().y / 10) * 6,
                (mbDrawRightKeyFlag ? GetColor(100, 100, 100) : GetColor(255, 255, 255)), TRUE);

            break;
        case 2:
            // バックサウンドボリューム割合描画
            mpSoundManager->DrawBackSoundVolumeRate((GetScreenSize().x / 3) * 2, (GetScreenSize().y / 3), (GetScreenSize().x / 3), (GetScreenSize().y / 3), (GetScreenSize().y / 10) * 0.1, GetColor(255, 255, 255));

            DrawBox((GetScreenSize().x / 10) * 1.3, (GetScreenSize().y / 10) * 1.3, (GetScreenSize().x / 10) * 3.1, (GetScreenSize().y / 10) * 2.6, GetColor(255, 255, 255), TRUE);
            DrawStringToHandle((GetScreenSize().x / 10) * 1.4, (GetScreenSize().y / 10) * 1.3, "MIN", GetColor(0, 0, 0), mnSystemDrawHandle);

            DrawBox((GetScreenSize().x / 10) * 6.9, (GetScreenSize().y / 10) * 1.3, (GetScreenSize().x / 10) * 8.7, (GetScreenSize().y / 10) * 2.6, GetColor(255, 255, 255), TRUE);
            DrawStringToHandle((GetScreenSize().x / 10) * 7, (GetScreenSize().y / 10) * 1.3, "MAX", GetColor(0, 0, 0), mnSystemDrawHandle);
            
            DrawFormatStringToHandle((GetScreenSize().x / 10) * 4.2, (GetScreenSize().y / 10) * 1.3, GetColor(255, 255, 255), mnSystemDrawHandle, "%d", mpSoundManager->GetBackSoundVolume());
            
            // 左
            DrawTriangleAA((GetScreenSize().x / 10) * 4.1, (GetScreenSize().y / 10) * 4.85,
                           (GetScreenSize().x / 10) * 4.1, (GetScreenSize().y / 10) * 7.15,
                           (GetScreenSize().x / 10) * 3.2, (GetScreenSize().y / 10) * 6,
                (mbDrawLeftKeyFlag ? GetColor(100, 100, 100) : GetColor(255, 255, 255)), TRUE);
            // 右
            DrawTriangleAA((GetScreenSize().x / 10) * 5.9, (GetScreenSize().y / 10) * 4.85,
                           (GetScreenSize().x / 10) * 5.9, (GetScreenSize().y / 10) * 7.15,
                           (GetScreenSize().x / 10) * 6.8, (GetScreenSize().y / 10) * 6,
                (mbDrawRightKeyFlag ? GetColor(100, 100, 100) : GetColor(255, 255, 255)), TRUE);
            // 上
            DrawTriangleAA((GetScreenSize().x / 10) * 4.1, (GetScreenSize().y / 10) * 4.85,
                           (GetScreenSize().x / 10) * 5.9, (GetScreenSize().y / 10) * 4.85,
                           (GetScreenSize().x / 10) * 5, (GetScreenSize().y / 10) * 3.5,
                (mbDrawUpKeyFlag ? GetColor(100, 100, 100) : GetColor(255, 255, 255)), TRUE);
            // 下
            DrawTriangleAA((GetScreenSize().x / 10) * 4.1, (GetScreenSize().y / 10) * 7.15,
                           (GetScreenSize().x / 10) * 5.9, (GetScreenSize().y / 10) * 7.15,
                           (GetScreenSize().x / 10) * 5, (GetScreenSize().y / 10) * 8.5,
                (mbDrawDownKeyFlag ? GetColor(100, 100, 100) : GetColor(255, 255, 255)), TRUE);
            break;
        case 3:
            // サウンドボリューム割合描画
            mpSoundManager->DrawSoundVolumeRate((GetScreenSize().x / 3) * 2, (GetScreenSize().y / 3), (GetScreenSize().x / 3), (GetScreenSize().y / 3), (GetScreenSize().y / 10) * 0.1, GetColor(255, 255, 255));

            DrawBox((GetScreenSize().x / 10) * 1.3, (GetScreenSize().y / 10) * 1.3, (GetScreenSize().x / 10) * 3.1, (GetScreenSize().y / 10) * 2.6, GetColor(255, 255, 255), TRUE);
            DrawStringToHandle((GetScreenSize().x / 10) * 1.4, (GetScreenSize().y / 10) * 1.3, "MIN", GetColor(0, 0, 0), mnSystemDrawHandle);

            DrawBox((GetScreenSize().x / 10) * 6.9, (GetScreenSize().y / 10) * 1.3, (GetScreenSize().x / 10) * 8.7, (GetScreenSize().y / 10) * 2.6, GetColor(255, 255, 255), TRUE);
            DrawStringToHandle((GetScreenSize().x / 10) * 7, (GetScreenSize().y / 10) * 1.3, "MAX", GetColor(0, 0, 0), mnSystemDrawHandle);

            DrawFormatStringToHandle((GetScreenSize().x / 10) * 4.2, (GetScreenSize().y / 10) * 1.3, GetColor(255, 255, 255), mnSystemDrawHandle, "%d", mpSoundManager->GetSoundVolume());

            // 左
            DrawTriangleAA((GetScreenSize().x / 10) * 4.1, (GetScreenSize().y / 10) * 4.85,
                           (GetScreenSize().x / 10) * 4.1, (GetScreenSize().y / 10) * 7.15,
                           (GetScreenSize().x / 10) * 3.2, (GetScreenSize().y / 10) * 6,
                (mbDrawLeftKeyFlag ? GetColor(100, 100, 100) : GetColor(255, 255, 255)), TRUE);
            // 右
            DrawTriangleAA((GetScreenSize().x / 10) * 5.9, (GetScreenSize().y / 10) * 4.85,
                           (GetScreenSize().x / 10) * 5.9, (GetScreenSize().y / 10) * 7.15,
                           (GetScreenSize().x / 10) * 6.8, (GetScreenSize().y / 10) * 6,
                (mbDrawRightKeyFlag ? GetColor(100, 100, 100) : GetColor(255, 255, 255)), TRUE);
            // 上
            DrawTriangleAA((GetScreenSize().x / 10) * 4.1, (GetScreenSize().y / 10) * 4.85,
                           (GetScreenSize().x / 10) * 5.9, (GetScreenSize().y / 10) * 4.85,
                           (GetScreenSize().x / 10) * 5, (GetScreenSize().y / 10) * 3.5,
                (mbDrawUpKeyFlag ? GetColor(100, 100, 100) : GetColor(255, 255, 255)), TRUE);
            // 下
            DrawTriangleAA((GetScreenSize().x / 10) * 4.1, (GetScreenSize().y / 10) * 7.15,
                           (GetScreenSize().x / 10) * 5.9, (GetScreenSize().y / 10) * 7.15,
                           (GetScreenSize().x / 10) * 5, (GetScreenSize().y / 10) * 8.5,
                (mbDrawDownKeyFlag ? GetColor(100, 100, 100) : GetColor(255, 255, 255)), TRUE);

            DrawCircle((GetScreenSize().x / 10) * 5, (GetScreenSize().y / 10) * 6, (((GetScreenSize().x / 10) + (GetScreenSize().y / 10)) * 0.5) * 0.9, mbTestSoundFlag ? GetColor(255, 0, 0) : GetColor(255, 255, 255));
            DrawStringToHandle((GetScreenSize().x / 10) * 4.75, (GetScreenSize().y / 10) * 5.3, "A", GetColor(0, 0, 0), mnSystemDrawHandle);
            break;
        }
        break;
    }

    // 戻る操作文字描画
    DrawBoxAA((GetScreenSize().x / 10) * 0.7, (GetScreenSize().y / 10) * 9.0, (GetScreenSize().x / 10) * 2, (GetScreenSize().y / 10) * 9.6, GetColor(0, 0, 0), TRUE);
    DrawBoxAA((GetScreenSize().x / 10) * 0.8, (GetScreenSize().y / 10) * 9.0, (GetScreenSize().x / 10) * 1.9, (GetScreenSize().y / 10) * 9.5, GetColor(255, 255, 255), TRUE);
    DrawString((GetScreenSize().x / 10) * 0.8, (GetScreenSize().y / 10) * 9.1, "\"B\"BACK", GetColor(0, 0, 0));
}

/*
* @fn SelectDecision
* @drief 選択決定時処理
*/
void MenuSystem::SelectDecision()
{
    switch (mnSelectManagerNumber)
    {
    case 0:
        mnSelectManagerNumber += 1;
        break;
    case 1:
        mnSelectManagerNumber -= 1;
        /*switch (mnMenuSelect)
        {
        case 2:
        case 3:
            break;
        }
        break;*/
    }
}

/*
* @fn GetAllDrawFlag
* @drief 描画用フラグのどれかが有効かどうか返す
*/
bool MenuSystem::GetAllDrawFlag()
{
    bool flag = false;

    flag |= mbDrawLeftKeyFlag;
    flag |= mbDrawRightKeyFlag;
    flag |= mbDrawUpKeyFlag;
    flag |= mbDrawDownKeyFlag;

    return flag;
}