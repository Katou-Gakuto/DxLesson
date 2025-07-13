#include "DxLib.h"
#include "../Header/CoordinateXY.h"
#include "../Header/GameManager.h"
#include "../Header/MenuCheck.h"
#include "../Header/MenuHowToPlay.h"
#include "../Header/MenuManager.h"
#include "../Header/Menu_Base.h"
#include "../Header/Operation.h"
#include "../Header/Scene_Enum.h"
#include "../Header/SceneManager.h"
#include "../Header/TimeManager.h"
#include "../Header/Title.h"

const float LINE_AERA_SIZE = 10000.0f;
const int LINE_NUM = 50;

/*
* @fn コンストラクタ
*/
Title::Title()
: Menu_Base(Title::MAX, XYGet(0, 0), XYGet(0, 0), GetColor(0, 0, 0), DX_BLENDMODE_NOBLEND, 255, true)
, mnSelectHandle(-1)
, mnTitleHandle(-1)
, mnOperationHandle(-1)
, mnWidth(-1)
, mnHeight(-1)
{
}

/*
* @fn デストラクタ
*/
Title::~Title()
{
}

/*
* @fn Initilize
* @drief 初期化処理
*/
void Title::MyInitilize()
{
    // 画面サイズ取得
    int colorBit = 0;
    GetScreenState(&mnWidth, &mnHeight, &colorBit);

    { // 文字サイズハンドル設定
        mnTitleHandle = CreateFontToHandle(NULL, 90, 9, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
        mnSelectHandle = CreateFontToHandle(NULL, 30, 5);
        mnOperationHandle = CreateFontToHandle(NULL, 15, 1);
    }
}

/*
* @fn Updete
* @drief 更新処理
*/
void Title::MyUpdate()
{
    DefaultMenuSelectUpdate();
}

/*
* @fn Draw
* @drief 描画処理
*/
void Title::MyDraw()
{
    DrawBox((mnWidth / 3) - 25, (mnHeight / 2) - 5, ((mnWidth / 3) * 2) - 5, (mnHeight / 2) + 155, GetColor(255, 255, 255), true);
    DrawBox((mnWidth / 3) - 20, mnHeight / 2, ((mnWidth / 3) * 2) - 10, (mnHeight / 2) + 150, GetColor(100, 100, 100), true);

    // タイトル
    DrawStringToHandle((mnWidth / 10.0f) * 0.6f, (mnHeight / 6), "ROBOT BATTLE", GetColor(255, 255, 255), mnTitleHandle);

    //-- 選択肢用文字 --//
    DrawStringToHandle((mnWidth / 3), (mnHeight / 2) + 20, "GAME START", mnMenuSelect == Title::START ? GetColor(255, 0, 0) : GetColor(255, 255, 255), mnSelectHandle);
    DrawStringToHandle((mnWidth / 3), (mnHeight / 2) + 60, "GAME SETTING", mnMenuSelect == Title::SETTING ? GetColor(255, 0, 0) : GetColor(255, 255, 255), mnSelectHandle);
    DrawStringToHandle((mnWidth / 3), (mnHeight / 2) + 100, "END", mnMenuSelect == Title::END ? GetColor(255, 0, 0) : GetColor(255, 255, 255), mnSelectHandle);
    //--            --//

    // 簡易操作説明
    DrawStringToHandle((mnWidth / 3), (mnHeight / 10) * 9, "↑↓... Select Change", GetColor(255, 255, 255), mnOperationHandle);
    DrawStringToHandle((mnWidth / 3), ((mnHeight / 10) * 9) + 15, " A...        Decision", GetColor(255, 255, 255), mnOperationHandle);

    VECTOR pos1;
    VECTOR pos2;

    SetUseZBufferFlag(true);

    pos1 = VGet(-LINE_AERA_SIZE / 2.0f, 0.0f, -LINE_AERA_SIZE / 2.0f);
    pos2 = VGet(-LINE_AERA_SIZE / 2.0f, 0.0f, LINE_AERA_SIZE / 2.0f);
    for (int i = 0; i < LINE_NUM; i++)
    {
        DrawLine3D(pos1, pos2, GetColor(0, 255, 0));
        pos1.x += LINE_AERA_SIZE / LINE_NUM;
        pos2.x += LINE_AERA_SIZE / LINE_NUM;
    }

    pos1 = VGet(-LINE_AERA_SIZE / 2.0f, 0.0f, -LINE_AERA_SIZE / 2.0f);
    pos2 = VGet(LINE_AERA_SIZE / 2.0f, 0.0f, -LINE_AERA_SIZE / 2.0f);
    for (int i = 0; i < LINE_NUM; i++)
    {
        DrawLine3D(pos1, pos2, GetColor(255, 0, 0));
        pos1.z += LINE_AERA_SIZE / LINE_NUM;
        pos2.z += LINE_AERA_SIZE / LINE_NUM;
    }
}

/*
* @fn Finalize
* @drief 終了処理
*/
void Title::MyFinalize()
{
    DeleteFontToHandle(mnTitleHandle);
    DeleteFontToHandle(mnSelectHandle);
    DeleteFontToHandle(mnOperationHandle);
}

/*
* @fn SelectDecision
* @drief 選択決定時処理
*/
void Title::SelectDecision()
{
    switch (mnMenuSelect)
    {
    case Title::START:
        Master::mpGameManager->GetSceneManager()->SetNextScene(SCENE::SELECT_SAVE_DATA);
        //Master::mpGameManager->GetSceneManeger()->SetNextScene(SCENE::BATTLE_RESULT);
        //Master::mpGameManager->GetSceneManeger()->SetNextScene(SCENE::GAME_NOTHING);
        Master::mpGameManager->GetMenuManager()->DecreaseMenuNumber();
        break;

    case Title::SETTING:
        MenuHowToPlay* menuHowToPlay;
        menuHowToPlay = new MenuHowToPlay();
        menuHowToPlay->Initilize();
        break;

    case Title::END:
        MenuCheck *check;
        check = new MenuCheck(*this, &Title::GameEnd, this);
        check->Initilize();
        break; 
    }
}