#include <iostream>
#include <string>

#include "DxLib.h"
#include "../Header/CoordinateXY.h"
#include "../Header/DataManager.h"
#include "../Header/DataManagerMacro.h"
#include "../Header/Data_Structs.h"
#include "../Header/GameManager.h"
#include "../Header/GraphManager.h"
#include "../Header/MenuManager.h"
#include "../Header/Menu_Base.h"
//#include "../Header/ObjectManager.h"
//#include "../Header/ObjectTagMacro.h"
#include "../Header/Object_Base.h"
//#include "../Header/Object_Base_Character.h"
#include "../Header/Operation.h"
#include "../Header/SceneManager.h"
#include "../Header/TimeManager.h"

Menu_Base::Menu_Base(int maxMenuSelect, COORDINATE_X_Y upperLeft, COORDINATE_X_Y lowerRight, unsigned int color, int drawBoxType, int drawBoxNumber, bool notDecreaseFlag, bool playerDataDrawFlag, bool closeSoundFlag, bool decisionSoundFlag, bool selectChangeSoundFlag)
: Object_Base()
, mnMenuSelect(0)
, mnMaxMenuSelect(maxMenuSelect)
, mnChangeFrame(0)
, mnDecisionFrame(0)
, mnColor(color)
, mnMyMenuNumber(0)
, mbNotDecreaseFlag(notDecreaseFlag)
, mnDrawBoxBlendType(drawBoxType)
, mnDrawBoxBlendNumber(drawBoxNumber)
, mpDataManager(nullptr)
, mpSceneManager(nullptr)
, mnNotPlayerDataHandle(-1)
, mbDrawPlayerDataFlag(playerDataDrawFlag)
, mbCloseSoundFlag(closeSoundFlag)
, mbDecisionSoundFlag(decisionSoundFlag)
, mbSelectChangeSoundFlag(selectChangeSoundFlag)
{
	// 描画用座標セット
	msUpperLeft.x = 0.0f;
	msUpperLeft.y = 0.0f;
	msLowerRight.x = 0.0f;
	msLowerRight.y = 0.0f;

    if (lowerRight.x > upperLeft.x) {
        msLowerRight.x = lowerRight.x;
        msUpperLeft.x = upperLeft.x;
    }
    else {
        msLowerRight.x = upperLeft.x;
        msUpperLeft.x = lowerRight.x;
    }

    if (lowerRight.y > upperLeft.y) {
        msLowerRight.y = lowerRight.y;
        msUpperLeft.y = upperLeft.y;
    }
    else {
        msLowerRight.y = upperLeft.y;
        msUpperLeft.y = lowerRight.y;
    }

    for (int i = 0; i < PLAYER_DATA_NUMBER; i++) {
        mnDrawPlayerPictureHandle[i] = -1;
    }
}

Menu_Base::~Menu_Base()
{
}

void Menu_Base::Initilize()
{
    mnMyMenuNumber =  Master::mpGameManager->GetMenuManager()->IncreaseMenuNumber(this);

    ResetDecisionFlame();

    mpDataManager = Master::mpGameManager->GetDataManager();
    mpSceneManager = Master::mpGameManager->GetSceneManager();

    // 文字サイズ設定
    {
        mnNotPlayerDataHandle = CreateFontToHandle(NULL, 100, 15);
    }

    // プレイヤー画像描画ハンドル取得
    SetDrawPlayerHandle();

    MyInitilize();
}

void Menu_Base::Finalize()
{
    if (!mbNotDecreaseFlag) {
        Master::mpGameManager->GetMenuManager()->DecreaseMenuNumber();
        if (mbCloseSoundFlag) {
            SetCloseMenuSound();
        }
    }
    
    DeleteFontToHandle(mnNotPlayerDataHandle);

	MyFinalize();
}

void Menu_Base::Update()
{
    if (NowMyMenuFlag()) {
        int checkSelectNumber = mnMenuSelect;
        MyUpdate();
        if (mnMenuSelect != checkSelectNumber) {
            if (mbSelectChangeSoundFlag) {
                SetSelectChangeSound();
            }
        }
    }
}

void Menu_Base::Draw()
{

    SetDrawBlendMode((mnDrawBoxBlendType), mnDrawBoxBlendNumber);
	DrawBoxAA(msUpperLeft.x, msUpperLeft.y, msLowerRight.x, msLowerRight.y, mnColor, TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	MyDraw();
}

/*
* @fn ResetDecisionFlame
* @drief 決定判定用変数のフレーム数をリセットする
*/
void Menu_Base::ResetDecisionFlame()
{
    mnDecisionFrame = Master::mpGameManager->GetTimeManager()->GetFrame();
}

/*
* @fn DefaultMenuSelectUpdate
* @drief デフォルトの選択変更用処理
*/
void Menu_Base::DefaultMenuSelectUpdate()
{
    // 上キーを押したときの選択変更処理
    DefaultUpKeyProcess();

    // 下キーを押したときの選択変更処理
    DefaultDownKeyProcess();
    
    // 選択決定処理
    CheckDecision_AKeyAndFrame();
}

/*
* @fn DefaultUpKeyProcess
* @drief デフォルトのアップキーを押した時の処理
*/
void Menu_Base::DefaultUpKeyProcess()
{
    if (CheckUpKeyAndFrame()) {
        mnMenuSelect -= 1;
        if (mnMenuSelect < 0) {
            mnMenuSelect = 0;
        }
    }
}

/*
* @fn DefaultDownKeyProcess
* @drief デフォルトのダウンキーを押した時の処理
*/
void Menu_Base::DefaultDownKeyProcess()
{
    if (CheckDownKeyAndFrame()) {
        mnMenuSelect += 1;
        if (mnMenuSelect >= mnMaxMenuSelect) {
            mnMenuSelect = (mnMaxMenuSelect - 1);
        }
    }
}

/*
* @fn CheckBkey_CloseProcess
* @drief Bキーを押したらメニューを閉じる処理
*/
void Menu_Base::CheckBkey_CloseProcess()
{
    // 閉じる
    if (Operation::CheckBKey() && CheckFrame(1)) {
        SetDeleteFlag(true);
    }
}

/*
* @fn CheckRightKeyAndFrame
* @drief 右キーが押されていて前回押したフレームから指定フレーム経っていればtrueを返す
*/
bool Menu_Base::CheckRightKeyAndFrame()
{
    bool flag = false;

    if (CheckFrame(0))
    {
        if (Operation::CheckRightKey())
        {
            mnChangeFrame = Master::mpGameManager->GetTimeManager()->GetFrame();
            flag = true;
        }
    }

    return flag;
}

/*
* @fn CheckLeftKeyAndFrame
* @drief 左キーが押されていて前回押したフレームから指定フレーム経っていればtrueを返す
*/
bool Menu_Base::CheckLeftKeyAndFrame()
{
    bool flag = false;

    if (CheckFrame(0))
    {
        if (Operation::CheckLeftKey())
        {
            mnChangeFrame = Master::mpGameManager->GetTimeManager()->GetFrame();
            flag = true;
        }
    }

    return flag;
}

/*
* @fn CheckUpKeyAndFrame
* @drief アップキーが押されていて前回押したフレームから指定フレーム経っていればtrueを返す
*/
bool Menu_Base::CheckUpKeyAndFrame()
{
    bool flag = false;

    if (CheckFrame(0))
    {
        if (Operation::CheckUpKey())
        {
            mnChangeFrame = Master::mpGameManager->GetTimeManager()->GetFrame();
            flag = true;
        }
    }

    return flag;
}

/*
* @fn CheckDownKeyAndFrame
* @drief ダウンキーが押されていて前回押したフレームから指定フレーム経っていればtrueを返す
*/
bool Menu_Base::CheckDownKeyAndFrame()
{
    bool flag = false;

    if (CheckFrame(0))
    {
        if (Operation::CheckDownKey())
        {
            mnChangeFrame = Master::mpGameManager->GetTimeManager()->GetFrame();
            flag = true;
        }
    }

    return flag;
}

/*
* @fn 
* @drief Aキーが押されていて指定フレームぶん経っていれば[SelectDecision]を呼び出す
*/
bool Menu_Base::CheckDecision_AKeyAndFrame()
{
    bool flag = false;

    if (CheckFrame(1))
    {
        if (Operation::CheckAKey())
        {
            mnDecisionFrame = Master::mpGameManager->GetTimeManager()->GetFrame();
            SelectDecision();
            if (mbDecisionSoundFlag) {
                SetSelectDecisionSound();
            }
        }
    }

    return flag;
}

/*
* @fn GetScreenSize
* @drief スクリーンのサイズ取得
*/
COORDINATE_X_Y_INT Menu_Base::GetScreenSize()
{
    COORDINATE_X_Y_INT set = XYGet_Int(0, 0);

    // 画面サイズ取得
    int colorBit = 0;
    GetScreenState(&set.x, &set.y, &colorBit);

    return set;
}

/*
* @fn NowMyMenuFlag
* @drief 現在操作しているメニューはこのメニューか判定
*/
bool Menu_Base::NowMyMenuFlag()
{
    return (mnMyMenuNumber == Master::mpGameManager->GetMenuManager()->GetNowMenuNumber());
}

/*
* @fn 
* @drief フレームが一定時間経っているかどうか
*/
bool Menu_Base::CheckFrame(int frameNumber)
{
    switch (frameNumber)
    {
    case 0:
        return (mnChangeFrame + 9 < Master::mpGameManager->GetTimeManager()->GetFrame());

    case 1:
        return ((mnDecisionFrame + 20) < Master::mpGameManager->GetTimeManager()->GetFrame());
    }

    return false;
}

/*
* @fn DrawPlayerDatas
* @drief プレイヤー情報描画用
*/
void Menu_Base::DrawPlayerDatas()
{
    // プレイヤー
    for (int i = 0; i < 3; i++) {
        DrawBoxAA((msLowerRight.x / 6) * 0.95, (msLowerRight.y / 24) * (0.8 + (i * 8)), (msLowerRight.x / 6) * 5.05, (msLowerRight.y / 24) * (7.2 + (i * 8)), GetColor(255, 255, 255), TRUE);
        if (mnMenuSelect == i) {
            DrawBoxAA(msLowerRight.x / 6, (msLowerRight.y / 24) * (1 + (i * 8)), (msLowerRight.x / 6) * 5, (msLowerRight.y / 24) * (7 + (i * 8)), GetColor(0, 0, 255), TRUE);
        }
        else {
            DrawBoxAA(msLowerRight.x / 6, (msLowerRight.y / 24) * (1 + (i * 8)), (msLowerRight.x / 6) * 5, (msLowerRight.y / 24) * (7 + (i * 8)), GetColor(0, 0, 100), TRUE);
        }
        if (mpDataManager->GetPlayerData()[i].dataFlag) {
            DrawFormatString((msLowerRight.x / 6) * 1.05, (msLowerRight.y / 24) * (1.1 + (i * 8)), GetColor(255.0f, 255.0f, 255.0f), "SAVE DATA %d", i + 1);
            DrawFormatString((msLowerRight.x / 6) * 1.05, (msLowerRight.y / 24) * (2.1 + (i * 8)), GetColor(255.0f, 255.0f, 255.0f), "PLAYER NAME : %s", mpDataManager->GetPlayerData()[i].characterData.templateData.name.c_str());
            DrawFormatString((msLowerRight.x / 6) * 1.05, (msLowerRight.y / 24) * (3.1 + (i * 8)), GetColor(255.0f, 255.0f, 255.0f), "CHARACTER TYPE : %s", GetCharacterTypeName(mpDataManager->GetPlayerData()[i].characterData.templateData.typeNumber).c_str());
            DrawFormatString((msLowerRight.x / 6) * 1.05, (msLowerRight.y / 24) * (4.1 + (i * 8)), GetColor(255.0f, 255.0f, 255.0f), "MAP NAME : %s", GetMapName(mpDataManager->GetPlayerData()[i].characterData.mapType).c_str());
            DrawFormatString((msLowerRight.x / 6) * 1.05, (msLowerRight.y / 24) * (5.1 + (i * 8)), GetColor(255.0f, 255.0f, 255.0f), "LEVEL:%-4d EXP:%-5d HP:%d", mpDataManager->GetPlayerData()[i].characterData.status.level, mpDataManager->GetPlayerData()[i].characterData.status.exp, mpDataManager->GetPlayerData()[i].characterData.status.hp);
            DrawFormatString((msLowerRight.x / 6) * 1.05, (msLowerRight.y / 24) * (6.1 + (i * 8)), GetColor(255.0f, 255.0f, 255.0f), "ATTACK:%-4d DEFENSE:%-4d SPEED:%d", mpDataManager->GetPlayerData()[i].characterData.status.attackPower, mpDataManager->GetPlayerData()[i].characterData.status.defense, mpDataManager->GetPlayerData()[i].characterData.status.speed);

            if (mnDrawPlayerPictureHandle[i] != -1) {
                DrawExtendGraph((msLowerRight.x / 6) * 4.1, (msLowerRight.y / 24) * (1 + (i * 8)), (msLowerRight.x / 6) * 5, (msLowerRight.y / 24) * (5.8 + (i * 8)), mnDrawPlayerPictureHandle[i], FALSE);
            }
        }
        else {
            DrawStringToHandle(msLowerRight.x / 6, (msLowerRight.y / 24) * (1 + (i * 8)), "NO DATA", GetColor(255, 255, 255), mnNotPlayerDataHandle);
        }
 
        if (mnMenuSelect == i) {
            DrawString((msLowerRight.x / 6) * 3.9, (msLowerRight.y / 24) * (6 + (i * 8)), "\"A\" DECISION", GetColor(255, 255, 255));
        }
    }
}

/*
* @fn SetDrawPlayerHandle
* @drief プレイヤー描画用ハンドル初期化
*/
void Menu_Base::SetDrawPlayerHandle()
{
    if (mbDrawPlayerDataFlag) {
        for (int i = 0; i < PLAYER_DATA_NUMBER; i++) {
            CHARACTER_TYPE characterType = (CHARACTER_TYPE)mpDataManager->GetPlayerData()[i].characterData.templateData.typeNumber;
            if (characterType == CHARACTER_TYPE::ROBOT_PLAYER) {
                mnDrawPlayerPictureHandle[i] = Master::mpGameManager->GerGraphManager()->GetGraphHandle(GRAPH_TYPE::ROBOT_CHARACTER);
            }
            else {
                mnDrawPlayerPictureHandle[i] = -1;
            }
        }
    }
}

/*
* @fn SetDecreaseMenuNumber
* @drief 指定の処理だけメニューがあるシーンへの移動の場合使う
*/
void Menu_Base::SetDecreaseMenuNumber()
{
    Master::mpGameManager->GetMenuManager()->DecreaseMenuNumber();
    mbNotDecreaseFlag = true;
}

/*
* @fn GameEnd
* @drief チェックメニュー用関数(終了用)
*/
void Menu_Base::GameEnd()
{
    Master::mpGameManager->SetEndFlag(true);
}

/*
* @fn TitleGo
* @drief チェックメニュー用関数(タイトル移動用)
*/
void Menu_Base::TitleGo()
{
   // Master::mpGameManager->GetDataManager()->Initilize();
    mpSceneManager->SetNextScene(SCENE::TITLE);
    SetDecreaseMenuNumber();
}

/*
* @fn GetMapName
* @drief マップタイプ名取得
*/
std::string Menu_Base::GetMapName(SCENE mapType)
{
    switch (mapType)
    {
    case SCENE::SART:
        return "SART";

    case SCENE::TITLE:
        return "TITLE";

    case SCENE::SELECT_SAVE_DATA:
        return "SELECT_SAVE_DATA";

    case SCENE::DEFAULT_MAP_ONE:
        return "DEFAULT_MAP_ONE";

    case SCENE::MAP_ONE:
        return "MAP_ONE";
            
    case SCENE::MAP_TWO:
        return "MAP_TWO";
            
    case SCENE::MAP_THREE:
        return "MAP_THREE";
            
    case SCENE::MAP_FOUR:
        return "MAP_FOUR";
            
    case SCENE::MAP_FIVE:
        return "MAP_FIVE";
            
    case SCENE::MAP_SIX:
        return "MAP_SIX";
            
    case SCENE::MAP_SEVEN:
        return "MAP_SEVEN";
            
    case SCENE::MAP_EIGHT:
        return "MAP_EIGHT";
            
    case SCENE::MAP_NINE:
        return "MAP_NINE";
            
    case SCENE::MAP_TEN:
        return "MAP_TEN";
            
    case SCENE::MAP_ELEVEN:
        return "MAP_ELEVEN";
            
    case SCENE::MAP_TWELVE:
        return "MAP_TWELVE";
            
    case SCENE::MAP_THIRTEEN:
        return "MAP_THIRTEEN";
            
    case SCENE::MAP_FOURTEEN:
        return "MAP_FOURTEEN";
            
    case SCENE::MAP_FIFTEEN:
        return "MAP_FIFTEEN";
            
    case SCENE::MAP_SIXTEEN:
        return "MAP_SIXTEEN";
            
    case SCENE::MAP_SEVENTEEN:
        return "MAP_SEVENTEEN";
            
    case SCENE::MAP_EIGHTEEN:
        return "MAP_EIGHTEEN";
            
    case SCENE::MAP_NINETEEN:
        return "MAP_NINETEEN";
            
    case SCENE::MAP_TWENTY:
        return "MAP_TWENTY";
            
    case SCENE::MAP_TWENTY_ONE:
        return "MAP_TWENTY_ONE";
            
    case SCENE::MAP_TWENTY_TWO:
        return "MAP_TWENTY_TWO";
            
    case SCENE::MAP_TWENTY_THREE:
        return "MAP_TWENTY_THREE";
            
    case SCENE::MAP_TWENTY_FOUR:
        return "MAP_TWENTY_FOUR";
            //24個
                    // バトルゲーム1
    case SCENE::BATTLE_GAME_ONE:
        return "BATTLE_GAME_ONE";
               // ボスバトルゲーム1
    case SCENE::BOSS_BATTLE_GAME_ONE:
        return "BOSS_BATTLE_GAME_ONE";
                      // バトルリザルト
    case SCENE::BATTLE_RESULT:
        return "BATTLE_RESULT";
                          // ゲームオーバー
    case SCENE::GAME_OVER:
        return "GAME_OVER";
                         // ゲームクリア
    case SCENE::GAME_CLEAR:
        return "GAME_CLEAR";
                       // ゲーム無し
    case SCENE::GAME_NOTHING:
        return "GAME_NOTHING";
              // 例外
    case SCENE::EXCEPTION:
        return "EXCEPTION";

    case SCENE::SCENE_NULL:
        return "SCENE_NULL";
    }
    return "NULL";
}

/*
* @fn GetCharacterTypeName
* @drief キャラクタータイプ名取得
*/
std::string Menu_Base::GetCharacterTypeName(int characterType)
{
    switch ((CHARACTER_TYPE)characterType)
    {
    case CHARACTER_TYPE::ROBOT_PLAYER:
        return "ロボットプレイヤー";
    }

    return "NULL";
}