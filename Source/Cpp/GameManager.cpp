#include "Dxlib.h"
#include "../Header/Camera.h"
#include "../Header/DataManager.h"
#include "../Header/GameManager.h"
#include "../Header/GraphManager.h"
#include "../Header/MenuManager.h"
#include "../Header/ModelManager.h"
#include "../Header/ObjectManager.h"
#include "../Header/SceneManager.h"
#include "../Header/SoundManager.h"
#include "../Header/Scene_Enum.h"
#include "../Header/TimeManager.h"

GameManager::GameManager() : mpDataManager(nullptr),  mpObjectManager(nullptr), mpSceneManager(nullptr), mpTimeManager(nullptr), mbEndFlag(false), mpMenuManager(nullptr), mpSoundManager(nullptr), mpGraphManager(nullptr), mpModelManager(nullptr)
{

}

GameManager::~GameManager()
{

}

void GameManager::Initilize()
{
    // データマネージャー初期化処理
    mpDataManager = new DataManager();
    mpDataManager->Initilize();
    //mpDataManager->SetTestFileData("GameData/Test_Data.txt");

    // グラフマネジャー初期化処理
    mpGraphManager = new GraphManager();
    mpGraphManager->Initilize();

    // メニューマネージャー初期化処理
    mpMenuManager = new MenuManager();

    // モデルマネージャー初期化処理
    mpModelManager = new ModelManager();
    mpModelManager->Initilize();

    // シーンマネージャー初期化処理
    mpSceneManager = new SceneManager();

    // オブジェクトマネージャー初期化処理
    mpObjectManager = new ObjectManager();
    
    // タイムマネージャー初期化処理
    mpTimeManager = new TimeManager();
    mpTimeManager->Initilize();

    // サウンドマネージャー初期化処理
    mpSoundManager = new SoundManager();
    mpSoundManager->Initilize();

    // シーンマネージャー
    mpSceneManager->SetNextScene(SCENE::TITLE);


    SetDrawScreen(DX_SCREEN_BACK);
}

void GameManager::Finalize()
{
    mpSoundManager->Finalize();
    mpModelManager->Finalize();
    mpGraphManager->Finalize();

    mpObjectManager->DeleteAll();
    delete mpSoundManager;
    delete mpTimeManager;
    delete mpObjectManager;
    delete mpSceneManager;
    delete mpModelManager;
    delete mpMenuManager;
    delete mpGraphManager;
    delete mpDataManager;
}

void GameManager::Update()
{
    // 時間更新
    mpTimeManager->Update();

    // サウンド更新
    mpSoundManager->Update();

    // オブジェクト更新
    mpObjectManager->Update();

    // カメラの更新
    Master::mpCamera->Updete();

    // 他マネージャーの終了フラグが有効になっていれば終了フラグを有効にする
    UpdateEndSetProcess();
}
#include "../Header/Operation.h"

void GameManager::Draw()
{


    ClearDrawScreen();

    mpObjectManager->Draw();
    
    //if (Operation::CheckYKey()) {
    //    // 画面サイズ取得
    //    int colorBit = 0;
    //    int setx, sety;
    //    GetScreenState(&setx, &sety, &colorBit);
    //    SaveDrawScreenToBMP(0, 0, setx, sety, "Resource/TEST/GameCamera.bmp");
    //}

    ScreenFlip();
}

/*
* @fn UpdateEndSetProcess
* @drief 更新時終了フラグ更新処理
*/
void GameManager::UpdateEndSetProcess()
{
    if (mpDataManager->GetFailureFlag()) {
        mbEndFlag = true;
    }
}