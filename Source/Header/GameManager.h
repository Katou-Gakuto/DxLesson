#pragma once

//  class Object;

class Camera;
class DataManager;
class GraphManager;
class MenuManager;
class ModelManager;
class ObjectManager;
class SceneManager;
class SoundManager;
class TimeManager;

class GameManager
{
private:
    bool mbEndFlag; // 終了フラグ

    //int intger;
    DataManager *mpDataManager; // データマネージャー

    GraphManager *mpGraphManager;   // グラフマネジャー

    MenuManager *mpMenuManager; // メニューマネージャー

    ModelManager* mpModelManager; // モデルマネージャー

    ObjectManager *mpObjectManager; // オブジェクトマネージャー

    SceneManager *mpSceneManager;   // シーンマネージャー

    SoundManager *mpSoundManager;   // サウンドマネージャー

    TimeManager *mpTimeManager; // タイムマネージャー

//    Object *m_pObject;


public:
    GameManager();                                                              // コンストラクタ
    ~GameManager();                                                             // デストラクタ

    void Initilize();                                                           // 初期化処理
    void Finalize();                                                            // 終了処理
    void Update();                                                              // 更新処理
    void Draw();                                                                // 描画処理

    void UpdateEndSetProcess(); // 更新時終了フラグ更新処理

    void SetEndFlag(bool setEndFlag) { mbEndFlag = setEndFlag; }        // 終了フラグ設定
    bool GetEndFlag() { return mbEndFlag; }                             // 終了フラグ取得

    DataManager *GetDataManager() { return mpDataManager; }

    GraphManager* GerGraphManager() { return mpGraphManager ; }

    MenuManager *GetMenuManager() { return mpMenuManager; }

    ModelManager *GetModelManager() { return mpModelManager; }

    ObjectManager *GetObjectManager() { return mpObjectManager; }

    SceneManager *GetSceneManager() { return mpSceneManager; }

    SoundManager* GetSoundManager() { return mpSoundManager; }

    TimeManager *GetTimeManager() { return mpTimeManager; }
};



class Master
{
private:
    int Nnmber;

public:
    static GameManager *mpGameManager;
    static Camera *mpCamera;
};