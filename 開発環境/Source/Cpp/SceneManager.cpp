#include <future>
#include <iostream>
#include <string>
#include <vector>

#include "DxLib.h"
#include "../Header/Camera.h"
#include "../Header/CharacterType_Enum.h"
#include "../Header/DataManager.h"
#include "../Header/DataManagerMacro.h"
#include "../Header/Data_Structs.h"
#include "../Header/FixedTower.h"
#include "../Header/GameManager.h"
#include "../Header/GenerateInformation_Struct.h"
#include "../Header/MapType_Enum.h"
#include "../Header/MenuPlayerSelect.h"
#include "../Header/ObjectManager.h"
#include "../Header/ObjectTagMacro.h"
#include "../Header/Object_Base_Character.h"
#include "../Header/ResultBattle.h"
#include "../Header/ResultGameEnd.h"
#include "../Header/Scene_Enum.h"
#include "../Header/SceneManager.h"
#include "../Header/SoundManager.h"
#include "../Header/StageManagerObject.h"
#include "../Header/Status_Struct.h"
#include "../Header/TimeManager.h"
#include "../Header/Title.h"


/*
* @fn コンストラクタ
*/
SceneManager::SceneManager()
: meNowScene(SCENE::SART)
, meNextScene(SCENE::SART)
, mnPlayerDataNumber(-1)
{
    mpDataManager = Master::mpGameManager->GetDataManager();

    //msMapDatas = mpDataManager->GetData_MapFile(mpDataManager->GetFileName_FileType(MAP_FILE_NAME, mpDataManager->GetBaseData_FileName()));
    
    mfMapMaxSize = 10000.0f;//3000.0f;//

    mfMagnificationRate = ((mfMapMaxSize/*plusPosition.x*/ + mfMapMaxSize/*plusPosition.z*/) / 2) / 5;   // 拡大率
}

/*
* @fn デストラクタ
*/
SceneManager::~SceneManager()
{
}

/*
* @fn GetCharacterType
* @drief キャラクタータイプ変換
*/
CHARACTER_TYPE SceneManager::GetCharacterType(std::string characterType)
{
    if (characterType == "RobotPlayer") {
        return CHARACTER_TYPE::ROBOT_PLAYER;
    }
    if (characterType == "MapCharacter1") {
        return CHARACTER_TYPE::MAP_CHARACTER_1;
    }
    if (characterType == "MapWeakEnemy1") {
        return CHARACTER_TYPE::MAP_WEAK_ENEMY_1;
    }
    if (characterType == "MapBossEnemy1") {
        return CHARACTER_TYPE::MAP_BOSS_ENEMY_1;
    }
    if (characterType == "BattleWeakEnemy1") {
        return CHARACTER_TYPE::BATTLE_WEAK_ENEMY_1;
    }
    if (characterType == "BattleBossEnemy1") {
        return CHARACTER_TYPE::BATTLE_BOSS_ENEMY_1;
    }

    return CHARACTER_TYPE::TYPE_NULL;
}

/*
* @fn SetAsyncFunction
* @drief 非同期用関数
*/
void SetAsyncFunction()
{
    Master::mpGameManager->GetSceneManager()->NewSceneProcess();
}

/*
* @fn CheckScene
* @drief シーン変更するかどうかチェックして実行する
*/
void SceneManager::CheckScene()
{
    if (meNowScene == meNextScene) {
        return;
    }

    Master::mpGameManager->GetTimeManager()->SetNewSceneTimeFlag(true);

    // 新しいシーンに移行
    NewSceneProcess();
}

/*
* @fn SetCharacter_StageManager
* @drief キャラクター生成データ入力
*/
void SceneManager::SetCharacter_StageManager(StageManagerObject *stageManager, SCENE nowScene, std::vector<DATA_NAME> playerFileNameData, std::vector<DATA_NAME> baseFileNameData)
{
    GENERATE_INFORATION generateInforation;

    std::vector<OneData> characterDatas = mpDataManager->GetSceneData(nowScene);

    for (OneData& oneCharacterData : characterDatas)
    {
        if (oneCharacterData.fileNameAndType.typeNumber == (int)DataType::CHARACTER)
        {
            for (CHARACTER_DATA& oneCharacter : oneCharacterData.datas.characterDatas)
            {
                generateInforation.survivalFlag = oneCharacter.survivalFlag;
                generateInforation.characterType = (CHARACTER_TYPE)oneCharacter.templateData.typeNumber;
                generateInforation.GeneratePosition = oneCharacter.position/*VGet(-900.0f + (i * 600.0f), 0.0f, 600.0f)*/;
                generateInforation.angle = oneCharacter.angle;
                generateInforation.status = oneCharacter.status;
                generateInforation.name = oneCharacter.templateData.name;
                generateInforation.scene = oneCharacter.mapType;
                generateInforation.dataFileName = oneCharacterData.fileNameAndType.name;

                // ステージマネージャーにエネミー情報を入力
                stageManager->AddGenerateInforation(generateInforation);
            }
        }
    }
    /*
    int baseCount = 0;

    std::vector<DATA_NAME> setPlayData;

    // ベースファイルに生成する種類のファイル数を取得
    for (DATA_NAME& oneBaseFileName : baseFileNameData)
    {
        if ((oneBaseFileName.sceneType == nowScene) && (oneBaseFileName.fileTypeName == NOT_PLAYER_CHARACTER_FILE_NAME))
        {
            ++baseCount;
        }
    }

    setPlayData.clear();
    setPlayData.reserve(baseCount);

    // プレイヤーファイルに生成する種類のファイル数を取得
    for (DATA_NAME& onePlayerFileName : playerFileNameData)
    {
        if ((onePlayerFileName.sceneType == nowScene) && (onePlayerFileName.fileTypeName == NOT_PLAYER_CHARACTER_FILE_NAME))
        {
            setPlayData.push_back(onePlayerFileName);
        }
    }

    // エネミー情報を設定する
    if (baseCount > 0)
    {
        std::vector<CHARACTER_DATA> characterData;
        if (baseCount > setPlayData.size())
        {
            for (DATA_NAME& oneBaseFileName : baseFileNameData)
            {
                if ((oneBaseFileName.sceneType == nowScene) && (oneBaseFileName.fileTypeName == NOT_PLAYER_CHARACTER_FILE_NAME))
                {
                    bool setDataFlag = false;

                    std::string playerFilePath;
                    playerFilePath = mpDataManager->GetPlayPlayerData().playerFolderName;

                    for (DATA_NAME& oneData : setPlayData)
                    {
                        if ((playerFilePath + oneBaseFileName.fileName.substr(9)) == oneData.fileName)
                        {
                            setDataFlag = true;
                        }
                    }
                    
                    if (!setDataFlag)
                    {
                    }

                    --baseCount;
                    if (baseCount == 0)
                    {
                        break;
                    }
                }
            }
        }
        else
        {
            // プレイヤーデータにある生成する種類のキャラクター情報を設定する
            for (DATA_NAME& onePlayerFileName : playerFileNameData)
            {
                if ((onePlayerFileName.sceneType == nowScene) && (onePlayerFileName.fileTypeName == NOT_PLAYER_CHARACTER_FILE_NAME))
                {
                    for (OneData& onePlayFileData : Master::mpGameManager->GetDataManager()->GetAllData())
                    {
                        if (onePlayFileData.fileNameAndType.name == onePlayerFileName.fileName)
                        {
                            characterData = onePlayFileData.datas.characterDatas;

                            for (int j = 0; j < characterData.size(); j++) {
                                generateInforation.survivalFlag = characterData[j].survivalFlag;
                                generateInforation.characterType = (CHARACTER_TYPE)characterData[j].templateData.typeNumber;
                                generateInforation.GeneratePosition = characterData[j].position/*VGet(-900.0f + (i * 600.0f), 0.0f, 600.0f)*//*;
                                generateInforation.angle = characterData[j].angle;
                                generateInforation.status = characterData[j].status;
                                generateInforation.name = characterData[j].templateData.name;
                                generateInforation.scene = characterData[j].mapType;
                                generateInforation.dataFileName = onePlayerFileName.fileName;

                                // ステージマネージャーにエネミー情報を入力
                                stageManager->AddGenerateInforation(generateInforation);
                            }
                        }
                    }
                }
            }
        }
    }

    // 生成するマップデータを取得
    for (int i = 0; i < msMapDatas.size(); i++) {
        if (mpDataManager->GetSceneType(msMapDatas[i].templateData.typeName) == nowScene) {
            mapData = msMapDatas[i];
            break;
        }
    }

    // 生成する種類の情報取得
    for (int i = 0; i < mapData.typeName.size(); i++) {
        if (mapData.typeName[i] == NOT_PLAYER_CHARACTER_FILE_NAME) {
            number = i;
            break;
        }
    }

    // 生成するデータの個数取得
    for (int i = 0; i < playerFileNameData.size(); i++) {
        if (playerFileNameData[i].sceneType == nowScene) {
            if (playerFileNameData[i].fileTypeName == NOT_PLAYER_CHARACTER_FILE_NAME) {
                count += 1;
            }
        }
    }

    // エネミー
    if (number != -1)
    {
        std::vector<CHARACTER_DATA> characterData;
        if (count >= mapData.typeNumber[number])
        {
            // エネミー生成情報入力
            for (int i = 0; i < playerFileNameData.size(); i++)
            {
                if (playerFileNameData[i].sceneType == nowScene) {
                    characterData = mpDataManager->GetData_CharacterFileDatas(playerFileNameData[i].fileName);

                    for (int j = 0; j < characterData.size(); j++) {
                        generateInforation.survivalFlag = characterData[j].survivalFlag;
                        generateInforation.characterType = GetCharacterType(characterData[j].templateData.typeName);
                        generateInforation.GeneratePosition = characterData[j].position/*VGet(-900.0f + (i * 600.0f), 0.0f, 600.0f)*//*;
                        generateInforation.angle = characterData[j].angle;
                        generateInforation.status = characterData[j].status;
                        generateInforation.name = characterData[j].templateData.name;
                        generateInforation.scene = mpDataManager->GetSceneType(characterData[j].mapName);
                        generateInforation.dataFileName = playerFileNameData[i].fileName;

                        // ステージマネージャーにエネミー情報を入力
                        stageManager->AddGenerateInforation(generateInforation);
                    }
                }
            }
        }
        else {
            DATA_NAME fileNameData;
            std::vector<CHARACTER_DATA> plusFileData;
            std::string playerFilePath;
            playerFilePath = mpDataManager->GetPlayerFilePos("/", mnPlayerDataNumber);

            for (int i = 0; i < baseFileNameData.size(); i++) {
                if (baseFileNameData[i].sceneType == nowScene) {
                    if (baseFileNameData[i].fileTypeName == NOT_PLAYER_CHARACTER_FILE_NAME)
                    {
                        plusFileData.clear();
                        characterData = mpDataManager->GetData_CharacterFileDatas(baseFileNameData[i].fileName);

                        for (int j = 0; j < characterData.size(); j++)
                        {
                            generateInforation.survivalFlag = characterData[j].survivalFlag;
                            generateInforation.characterType = GetCharacterType(characterData[j].templateData.typeName);
                            generateInforation.GeneratePosition = characterData[j].position/*VGet(-900.0f + (i * 600.0f), 0.0f, 600.0f)*//*;
                            generateInforation.angle = characterData[j].angle;
                            generateInforation.status = characterData[j].status;
                            generateInforation.name = characterData[j].templateData.name;
                            generateInforation.scene = mpDataManager->GetSceneType(characterData[j].mapName);
                            generateInforation.dataFileName = playerFilePath + baseFileNameData[i].fileName.substr(9);

                            // ステージマネージャーにエネミー情報を入力
                            stageManager->AddGenerateInforation(generateInforation);


                            plusFileData.push_back(characterData[j]);
                        }

                        // データ入力
                        {
                            // ファイル名追加
                            fileNameData.fileName = playerFilePath + baseFileNameData[i].fileName.substr(9);
                            fileNameData.sceneType = nowScene;
                            fileNameData.fileTypeName = NOT_PLAYER_CHARACTER_FILE_NAME;
                            mpDataManager->AddFile_FileNameData(playerFilePath + "FileNames_Data.txt", fileNameData);

                            // ファイル作成
                            mpDataManager->AddCharacterFile(fileNameData.fileName, plusFileData[0]);
                            for (int j = 1; j < plusFileData.size(); j++) {
                                mpDataManager->AddFile_CharacterFileData(fileNameData.fileName, plusFileData[j]);
                            }
                        }

                    }
                }
            }

            Master::mpGameManager->GetDataManager()->Init_PlayerFileName_And_Item(Master::mpGameManager->GetSceneManager()->GetPlayerDataNumber());
        }
    }*/
}

/*
* @fn SetBattleCharacter_StageManager
* @drief バトルの敵を生み出す
*/
void SceneManager::SetBattleCharacter_StageManager(StageManagerObject *stageManager, CHARACTER_TYPE characterType, VECTOR position_1, VECTOR position_2, VECTOR position_3)
{
    GENERATE_INFORATION generateInforation;
    Object_Base_Character *mapEnemy = Master::mpGameManager->GetObjectManager()->FindByTag_CharacterObject(ENEMY_TAG);
    int levelNumber = mapEnemy->GetStatus().level;

    // エネミー生成情報入力
    generateInforation.survivalFlag = true;
    generateInforation.characterType = characterType;
    generateInforation.GeneratePosition = position_1;
    generateInforation.angle = 180.0f;
    generateInforation.name = mapEnemy->GetCharacterName();
    generateInforation.status = mapEnemy->GetStatus();

    // ステージマネージャーにエネミー情報を入力
    stageManager->AddGenerateInforation(generateInforation);

    STATUS setStatus;
    setStatus.attackPower = (levelNumber * 1.5);
    setStatus.defense = levelNumber;
    setStatus.exp = 0;
    setStatus.level = levelNumber;
    setStatus.maxHp = (levelNumber * 5);
    setStatus.hp = (levelNumber * 5);
    setStatus.size = 80;
    setStatus.speed = 1 + (levelNumber * 0.25);

    generateInforation.survivalFlag = true;
    generateInforation.characterType = CHARACTER_TYPE::BATTLE_WEAK_ENEMY_1;
    generateInforation.GeneratePosition = position_2;
    generateInforation.angle = 180.0f;
    generateInforation.name = "ENEMY(A)";
    generateInforation.status = setStatus;
    // ステージマネージャーにエネミー情報を入力
    stageManager->AddGenerateInforation(generateInforation);

    generateInforation.GeneratePosition = position_3;
    generateInforation.name = "ENEMY(B)";
    // ステージマネージャーにエネミー情報を入力
    stageManager->AddGenerateInforation(generateInforation);
}

/*
* @fn NewSceneProcess
* @drief 新しいシーン移行処理
*/
void SceneManager::NewSceneProcess()
{
    // 現在のシーンのオブジェクト破棄
    Master::mpGameManager->GetObjectManager()->SetDeleteSceneObject(meNowScene);
    

    // 次のシーンのオブジェクト生成
    meNowScene = meNextScene;

    // 生成情報
    GENERATE_INFORATION generateInforation;
    
    PLAYER_DATA playerData;
    std::vector<CHARACTER_DATA> characterData;
    Object_Base_Character *mapEnemy;

    StageManagerObject *stageManager;

    switch (meNowScene)
    {
    case SCENE::TITLE:
        // タイトルセット
        Title *title;
        title = new Title();
        title->Initilize();

        // カメラセット
        Master::mpCamera->InitializeModeLook(VGet(180.0f, 180.0f, 180.0f), VGet(0.0f, 180.0f, 0.0f));

        // バックサウンド設定
        Master::mpGameManager->GetSoundManager()->SetBackSound(BACK_SOUND::NORMAL_SOUND);

        /*MenuNewData * test;
        test = new MenuNewData();
        test->Initilize();*/
        break;

    case SCENE::SELECT_SAVE_DATA:
        MenuPlayerSelect *playerSelectMenu;
        playerSelectMenu = new MenuPlayerSelect();
        playerSelectMenu->Initilize();

        // バックサウンド設定
        Master::mpGameManager->GetSoundManager()->SetBackSound(BACK_SOUND::SELECT_DATA_SOUND);
        break;

    case SCENE::DEFAULT_MAP_ONE:
        stageManager = new StageManagerObject("Resource/3D/Floor/Ceiling_Closed.mv1", MAP_TYPE::MAP, VGet(mfMapMaxSize, 000.0f, mfMapMaxSize), VGet(-mfMapMaxSize, 0.0f, -mfMapMaxSize), true, &mfMagnificationRate);
        stageManager->Initilize();

        // プレイヤー
        {
            // プレイヤー生成情報入力
            /*playerData = */SetPlayer(&generateInforation, mpDataManager->GetPlayPlayerData(), CHARACTER_TYPE::MAP_PLAYER);
            //generateInforation.survivalFlag = playerData.characterData.survivalFlag;
            //generateInforation.characterType = CHARACTER_TYPE::MAP_PLAYER; //GetCharacterType(playerData.characterData.templateData.typeName); // ここもいじるキャラモデルの変更など
            //generateInforation.GeneratePosition = playerData.characterData.position;
            //generateInforation.angle = playerData.characterData.angle;
            //generateInforation.status = playerData.characterData.status;
            //generateInforation.name = playerData.characterData.templateData.name;
            //generateInforation.scene = playerData.characterData.mapType;
            //for (DATA_NAME fileNameData : mpDataManager->GetAllData(true)[0].datas.fileNameDatas)
            //{
            //    if (fileNameData.fileTypeName == PLAYER_FILE_NAME)
            //    {
            //        generateInforation.dataFileName = fileNameData.fileName;
            //    }
            //}

            // ステージマネージャーにプレイヤー情報を入力
            stageManager->AddGenerateInforation(generateInforation);
        }

        // キャラクター入力
        {
            // キャラクタ生成情報入力
            SetCharacter_StageManager(stageManager, meNowScene, mpDataManager->GetAllData()[0].datas.fileNameDatas, mpDataManager->GetAllData(true)[0].datas.fileNameDatas);
        }

        // ステージ生成
        stageManager->CharacterGenerate();

        // タワー生成
        SetTowerObject(VGet(10000.0f, 0.0f, 8000.0f), 2, "Resource/3D/Tower/Wall.mv1", 10, 15);
        SetTowerObject(VGet(-4000.0f, 0.0f, 8000.0f), 2, "Resource/3D/Tower/Wall.mv1", 10, 15);
        SetTowerObject(VGet(3000.0f, 0.0f, -4000.0f), 2, "Resource/3D/Tower/Wall.mv1", 10, 10);


        Master::mpCamera->InitializeModeTargetLRMove(Master::mpGameManager->GetObjectManager()->FindByTag_CharacterObject(PLAYER_TAG));

        // バックサウンド設定
        Master::mpGameManager->GetSoundManager()->SetBackSound(BACK_SOUND::NORMAL_SOUND);
        break;
        
    case SCENE::MAP_ONE:
    case SCENE::MAP_TWO:
    case SCENE::MAP_THREE:
    case SCENE::MAP_FOUR:
    case SCENE::MAP_FIVE:
    case SCENE::MAP_SIX:
    case SCENE::MAP_SEVEN:
    case SCENE::MAP_EIGHT:
    case SCENE::MAP_NINE:
    case SCENE::MAP_TEN:
    case SCENE::MAP_ELEVEN:
    case SCENE::MAP_TWELVE:
    case SCENE::MAP_THIRTEEN:
    case SCENE::MAP_FOURTEEN:
    case SCENE::MAP_FIFTEEN:
    case SCENE::MAP_SIXTEEN:
    case SCENE::MAP_SEVENTEEN:
    case SCENE::MAP_EIGHTEEN:
    case SCENE::MAP_NINETEEN:
    case SCENE::MAP_TWENTY:
    case SCENE::MAP_TWENTY_ONE:
    case SCENE::MAP_TWENTY_TWO:
    case SCENE::MAP_TWENTY_THREE:
    case SCENE::MAP_TWENTY_FOUR:
        // ステージマネージャー生成
        //StageManagerObject *stageManager;
        stageManager = new StageManagerObject("Resource/3D/Floor/Ceiling_Closed.mv1", MAP_TYPE::MAP, VGet(mfMapMaxSize, 000.0f, mfMapMaxSize), VGet(-mfMapMaxSize, 0.0f, -mfMapMaxSize), true, &mfMagnificationRate);
        stageManager->Initilize();

        // プレイヤー
        {
            // プレイヤー生成情報入力
            /*playerData = */SetPlayer(&generateInforation, mpDataManager->GetPlayPlayerData(), CHARACTER_TYPE::MAP_PLAYER);
            //generateInforation.survivalFlag = playerData.characterData.survivalFlag;
            //generateInforation.characterType = CHARACTER_TYPE::MAP_PLAYER; //GetCharacterType(playerData.characterData.templateData.typeName); // ここもいじるキャラモデルの変更など
            //generateInforation.GeneratePosition = playerData.characterData.position;
            //generateInforation.angle = playerData.characterData.angle;
            //generateInforation.status = playerData.characterData.status;
            //generateInforation.name = playerData.characterData.templateData.name;
            //generateInforation.scene = mpDataManager->GetSceneType(playerData.characterData.mapName);
            //generateInforation.dataFileName = mpDataManager->GetFileName_FileType(PLAYER_FILE_NAME, mpDataManager->GetBaseData_FileName());
            

            // ステージマネージャーにプレイヤー情報を入力
            stageManager->AddGenerateInforation(generateInforation);
        }

        // キャラクタ生成情報入力
        SetCharacter_StageManager(stageManager, meNowScene, mpDataManager->GetAllData()[0].datas.fileNameDatas, mpDataManager->GetAllData(true)[0].datas.fileNameDatas);

        // ステージ生成
        stageManager->CharacterGenerate();

        switch (meNowScene) {
        case SCENE::MAP_ONE:
        case SCENE::MAP_TWO:
        case SCENE::MAP_THREE:
            SetTowerObject(VGet(8400.0f, 0.0f, 8400.0f), 2, "Resource/3D/Tower/Wall.mv1", 10, 10);
            SetTowerObject(VGet(-2400.0f, 0.0f, 8400.0f), 2, "Resource/3D/Tower/Wall.mv1", 10, 10);
            SetTowerObject(VGet(8400.0f, 0.0f, -2400.0f), 2, "Resource/3D/Tower/Wall.mv1", 10, 10);
            SetTowerObject(VGet(-2400.0f, 0.0f, -2400.0f), 2, "Resource/3D/Tower/Wall.mv1", 10, 10);
            break;
        case SCENE::MAP_FOUR:
        case SCENE::MAP_FIVE:
        case SCENE::MAP_SIX:
        case SCENE::MAP_SEVEN:
        case SCENE::MAP_EIGHT:
        case SCENE::MAP_NINE:
        case SCENE::MAP_TEN:
        case SCENE::MAP_ELEVEN:
            SetTowerObject(VGet(-1400.0f, 0.0f, 8000.0f), 2, "Resource/3D/Tower/Wall.mv1", 3, 3);
            SetTowerObject(VGet(-4400.0f, 0.0f, 4600.0f), 2, "Resource/3D/Tower/Wall.mv1", 3, 3);
            SetTowerObject(VGet(-6000.0f, 0.0f, 900.0f), 2, "Resource/3D/Tower/Wall.mv1", 3, 3);
            SetTowerObject(VGet(-4400.0f, 0.0f, -2800.0f), 2, "Resource/3D/Tower/Wall.mv1", 3, 3);
            SetTowerObject(VGet(-1400.0f, 0.0f, -6200.0f), 2, "Resource/3D/Tower/Wall.mv1", 3, 3);
            SetTowerObject(VGet(3200.0f, 0.0f, 8000.0f), 2, "Resource/3D/Tower/Wall.mv1", 3, 3);
            SetTowerObject(VGet(6200.0f, 0.0f, 4600.0f), 2, "Resource/3D/Tower/Wall.mv1", 3, 3);
            SetTowerObject(VGet(7800.0f, 0.0f, 900.0f), 2, "Resource/3D/Tower/Wall.mv1", 3, 3);
            SetTowerObject(VGet(6200.0f, 0.0f, -2800.0f), 2, "Resource/3D/Tower/Wall.mv1", 3, 3);
            SetTowerObject(VGet(3200.0f, 0.0f, -6200.0f), 2, "Resource/3D/Tower/Wall.mv1", 3, 3);
            break;
        case SCENE::MAP_TWELVE:
        case SCENE::MAP_THIRTEEN:
        case SCENE::MAP_FOURTEEN:
        case SCENE::MAP_FIFTEEN:
        case SCENE::MAP_SIXTEEN:
        case SCENE::MAP_SEVENTEEN:
        case SCENE::MAP_EIGHTEEN:
        case SCENE::MAP_NINETEEN:
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 3; j++) {
                    SetTowerObject(VGet(8400.0f + (-14400.0f * i), 0.0f, 8000.0f + (-6800.0f * j)), 2, "Resource/3D/Tower/Wall.mv1", 4, 4);
                }
                SetTowerObject(VGet(4400.0f + (-6400.0f * i), 0.0f, 1200.0f), 2, "Resource/3D/Tower/Wall.mv1", 4, 4);

                SetTowerObject(VGet(1200.0f, 0.0f, -3000.0f + (-5000.0f * i)), 2, "Resource/3D/Tower/Wall.mv1", 4, 4);
            }
            {   // 右側
                SetTowerObject(VGet(1050.0f, 0.0f, 7700.0f), 2, "Resource/3D/Tower/Wall.mv1", 1, 3);
                SetTowerObject(VGet(1650.0f, 0.0f, 6500.0f), 2, "Resource/3D/Tower/Wall.mv1");
                SetTowerObject(VGet(3150.0f, 0.0f, 7900.0f), 2, "Resource/3D/Tower/Wall.mv1", 2);
                SetTowerObject(VGet(3150.0f, 0.0f, 7300.0f), 2, "Resource/3D/Tower/Wall.mv1");
                SetTowerObject(VGet(4200.0f, 0.0f, 9500.0f), 2, "Resource/3D/Tower/Wall.mv1", 3);
                SetTowerObject(VGet(4200.0f, 0.0f, 8900.0f), 2, "Resource/3D/Tower/Wall.mv1");
            }
            {   // 左側
                SetTowerObject(VGet(-450.0f, 0.0f, 7700.0f), 2, "Resource/3D/Tower/Wall.mv1", 1, 3);
                SetTowerObject(VGet(-1050.0f, 0.0f, 6500.0f), 2, "Resource/3D/Tower/Wall.mv1");
                SetTowerObject(VGet(-1950.0f, 0.0f, 7900.0f), 2, "Resource/3D/Tower/Wall.mv1", 2);
                SetTowerObject(VGet(-2550.0f, 0.0f, 7300.0f), 2, "Resource/3D/Tower/Wall.mv1");
                SetTowerObject(VGet(-2400.0f, 0.0f, 9500.0f), 2, "Resource/3D/Tower/Wall.mv1", 3);
                SetTowerObject(VGet(-3600.0f, 0.0f, 8900.0f), 2, "Resource/3D/Tower/Wall.mv1");
            }
            break;
        case SCENE::MAP_TWENTY:
        case SCENE::MAP_TWENTY_ONE:
        case SCENE::MAP_TWENTY_TWO:
        case SCENE::MAP_TWENTY_THREE:
            SetTowerObject(VGet(1200.0f, 0.0f, 1600.0f), 2, "Resource/3D/Tower/Wall.mv1", 1, 4);
            SetTowerObject(VGet(600.0f, 0.0f, 1500.0f), 2, "Resource/3D/Tower/Wall.mv1", 3, 1);
            SetTowerObject(VGet(-700.0f, 0.0f, 900.0f), 2, "Resource/3D/Tower/Wall.mv1", 1, 3);
            SetTowerObject(VGet(1200.0f, 0.0f, -1000.0f), 2, "Resource/3D/Tower/Wall.mv1", 4, 1);
            break;
        case SCENE::MAP_TWENTY_FOUR:
            // タワー生成
            for (int i = 0; i < 20; i++) {
                for (int j = 1; j <= 2; j++) {
                    SetTowerObject(VGet(3000.0f * j, 0.0f, 10000.0f + (-1000.0f * i)), 2, "Resource/3D/Tower/Wall.mv1");
                }

                for (int j = 1; j <= 2; j++) {
                    SetTowerObject(VGet(-3000.0f * j, 0.0f, 10000.0f + (-1000.0f * i)), 2, "Resource/3D/Tower/Wall.mv1");
                }
            }
            break;
        }

        Master::mpCamera->InitializeModeTargetLRMove(Master::mpGameManager->GetObjectManager()->FindByTag_CharacterObject(PLAYER_TAG));
        //Master::mpCamera->InitializeModeTarget(Master::mpGameManager->GetObjectManager()->FindByTag_CharacterObject(PLAYER_TAG));
        //Master::mpCamera->InitializeModeLook(VGet(0.0f, 1500.0f, 600.0f), VGet(0.0f, 0.0f, 600.0f));
        // 
        // バックサウンド設定
        Master::mpGameManager->GetSoundManager()->SetBackSound(BACK_SOUND::MAP_SOUND);
        break;

    case SCENE::BATTLE_GAME_ONE:

        // ステージマネージャー生成
        //StageManagerObject *stageManager;
        stageManager = new StageManagerObject("Resource/3D/Floor/Ceiling_Closed.mv1", MAP_TYPE::BATTLE, VGet(mfMapMaxSize, 000.0f, mfMapMaxSize), VGet(-mfMapMaxSize, 0.0f, -mfMapMaxSize), true, &mfMagnificationRate);
        stageManager->Initilize();

        // 生成情報
        //GENERATE_INFORATION generateInforation;

        // プレイヤー
        {
            // プレイヤー生成情報入力
            playerData = SetPlayer(&generateInforation, mpDataManager->GetPlayPlayerData(), (CHARACTER_TYPE)mpDataManager->GetPlayPlayerData().characterData.templateData.typeNumber);
            /*generateInforation.survivalFlag = playerData.characterData.survivalFlag;
            generateInforation.characterType = GetCharacterType(playerData.characterData.templateData.typeName);
            generateInforation.GeneratePosition = VGet(0.0f, 0.0f, 0.0f);
            generateInforation.angle = 0.0f;
            generateInforation.status = playerData.characterData.status;
            generateInforation.name = playerData.characterData.templateData.name;
            generateInforation.dataFileName = mpDataManager->GetFileName_FileType(PLAYER_FILE_NAME, mpDataManager->GetBaseData_FileName());*/

            // ステージマネージャーにプレイヤー情報を入力
            stageManager->AddGenerateInforation(generateInforation);

            // プレイヤーデータ保存
            msOldPlayerData = playerData;
        }

        // エネミー
        {
            SetBattleCharacter_StageManager(stageManager, CHARACTER_TYPE::BATTLE_WEAK_ENEMY_1, VGet(0.0f, 0.0f, 3000.0f), VGet(2000.0f, 0.0f, 2000.0f), VGet(-2000.0f, 0.0f, 2000.0f));
            //mapEnemy = Master::mpGameManager->GetObjectManager()->FindByTag_CharacterObject(ENEMY_TAG);

            //// エネミー生成情報入力
            //generateInforation.survivalFlag = true;
            //generateInforation.characterType = CHARACTER_TYPE::BATTLE_WEAK_ENEMY_1;
            //generateInforation.GeneratePosition = VGet(0.0f, 0.0f, 3000.0f);
            //generateInforation.angle = 180.0f;
            //generateInforation.name = mapEnemy->GetCharacterName();
            //generateInforation.status = mapEnemy->GetStatus();

            //// ステージマネージャーにエネミー情報を入力
            //stageManager->AddGenerateInforation(generateInforation);
        }

        // ステージ生成
        stageManager->CharacterGenerate();

        // タワー生成
        SetTowerObject(VGet(10000.0f, 0.0f, 8000.0f), 2, "Resource/3D/Tower/Wall.mv1", 10, 15);
        SetTowerObject(VGet(-4000.0f, 0.0f, 8000.0f), 2, "Resource/3D/Tower/Wall.mv1", 10, 15);

        Master::mpCamera->InitializeModeTargetLRMove(Master::mpGameManager->GetObjectManager()->FindByTag_CharacterObject(PLAYER_TAG));
        //Master::mpCamera->InitializeModeTarget(player);

        // バックサウンド設定
        Master::mpGameManager->GetSoundManager()->SetBackSound(BACK_SOUND::BATTLE_1_SOUND);
        // サウンド設定
        Master::mpGameManager->GetSoundManager()->SetSound(SOUND::BATTLE_START);
        break;

    case SCENE::BOSS_BATTLE_GAME_ONE:

        // ステージマネージャー生成
        //StageManagerObject *stageManager;
        stageManager = new StageManagerObject("Resource/3D/Floor/Ceiling_Closed.mv1", MAP_TYPE::BATTLE, VGet(mfMapMaxSize, 000.0f, mfMapMaxSize), VGet(-mfMapMaxSize, 0.0f, -mfMapMaxSize), true, &mfMagnificationRate);
        stageManager->Initilize();

        // 生成情報
        //GENERATE_INFORATION generateInforation;

        // プレイヤー
        {
            // プレイヤー生成情報入力
            playerData = SetPlayer(&generateInforation, mpDataManager->GetPlayPlayerData(), (CHARACTER_TYPE)mpDataManager->GetPlayPlayerData().characterData.templateData.typeNumber);
            /*generateInforation.survivalFlag = playerData.characterData.survivalFlag;
            generateInforation.characterType = GetCharacterType(playerData.characterData.templateData.typeName);;
            generateInforation.GeneratePosition = VGet(0.0f, 0.0f, 0.0f);
            generateInforation.angle = 0.0f;
            generateInforation.status = playerData.characterData.status;
            generateInforation.name = playerData.characterData.templateData.name;
            generateInforation.dataFileName = mpDataManager->GetFileName_FileType(PLAYER_FILE_NAME, mpDataManager->GetBaseData_FileName());*/

            // ステージマネージャーにプレイヤー情報を入力
            stageManager->AddGenerateInforation(generateInforation);

            // プレイヤーデータ保存
            msOldPlayerData = playerData;
        }

        // ボスエネミー
        {
            SetBattleCharacter_StageManager(stageManager, CHARACTER_TYPE::BATTLE_BOSS_ENEMY_1, VGet(0.0f, 0.0f, 3000.0f), VGet(2000.0f, 0.0f, -2000.0f), VGet(-2000.0f, 0.0f, -2000.0f));
            //// ボスエネミー生成情報入力
            //generateInforation.survivalFlag = true;
            //generateInforation.characterType = CHARACTER_TYPE::BATTLE_BOSS_ENEMY_1;
            //generateInforation.GeneratePosition = VGet(0.0f, 0.0f, 3000.0f);
            //generateInforation.angle = 0.0f;
            //generateInforation.name = "BOSS";

            //// ステージマネージャーにボスエネミー情報を入力
            //stageManager->AddGenerateInforation(generateInforation);
        }

        // ステージ生成
        stageManager->CharacterGenerate();

        // タワー生成
        for (int i = 0; i < 20; i++) {
            for (int j = 1; j <= 2; j++) {
                SetTowerObject(VGet(4000.0f * j, 0.0f, 10000.0f + (-1000.0f * i)), 2, "Resource/3D/Tower/Wall.mv1");
            }

            for (int j = 1; j <= 2; j++) {
                SetTowerObject(VGet(-4000.0f * j, 0.0f, 10000.0f + (-1000.0f * i)), 2, "Resource/3D/Tower/Wall.mv1");
            }
        }

        Master::mpCamera->InitializeModeTargetLRMove(Master::mpGameManager->GetObjectManager()->FindByTag_CharacterObject(PLAYER_TAG));

        // バックサウンド設定
        Master::mpGameManager->GetSoundManager()->SetBackSound(BACK_SOUND::BATTLE_BOSS_1_SOUND);
        // サウンド設定
        Master::mpGameManager->GetSoundManager()->SetSound(SOUND::BATTLE_START);
        break;

    case SCENE::BATTLE_RESULT:
        ResultBattle *resultBattle;
        resultBattle = new ResultBattle();
        resultBattle->Initilize();

        // サウンド設定
        Master::mpGameManager->GetSoundManager()->SetSound(SOUND::SCORE);
        break;

    case SCENE::GAME_OVER:
    case SCENE::GAME_CLEAR:
    case SCENE::GAME_NOTHING:
        ResultGameEnd *resultGameEnd;
        resultGameEnd = new ResultGameEnd();
        resultGameEnd->Initilize();

        // サウンド設定
        Master::mpGameManager->GetSoundManager()->SetSound(SOUND::SCORE);
        break;
    }
}


/*
bool GetNowSceneType(std::string scenetype);    // * @fn
* @drief 指定されたシーンタイプと現在のシーンタイプが同じならtrueを返す
*/
bool SceneManager::GetNowSceneType(std::string sceneType)
{
    switch (meNowScene)
    {
    case SCENE::SART:
        return (sceneType == "SART");
    case SCENE::TITLE:
        return (sceneType == "TITLE");
    case SCENE::SELECT_SAVE_DATA:
        return (sceneType == "SELECT_SAVE_DATA");
    case SCENE::DEFAULT_MAP_ONE:
    case SCENE::MAP_ONE:
    case SCENE::MAP_TWO:
    case SCENE::MAP_THREE:
    case SCENE::MAP_FOUR:
    case SCENE::MAP_FIVE:
    case SCENE::MAP_SIX:
    case SCENE::MAP_SEVEN:
    case SCENE::MAP_EIGHT:
    case SCENE::MAP_NINE:
    case SCENE::MAP_TEN:
    case SCENE::MAP_ELEVEN:
    case SCENE::MAP_TWELVE:
    case SCENE::MAP_THIRTEEN:
    case SCENE::MAP_FOURTEEN:
    case SCENE::MAP_FIFTEEN:
    case SCENE::MAP_SIXTEEN:
    case SCENE::MAP_SEVENTEEN:
    case SCENE::MAP_EIGHTEEN:
    case SCENE::MAP_NINETEEN:
    case SCENE::MAP_TWENTY:
    case SCENE::MAP_TWENTY_ONE:
    case SCENE::MAP_TWENTY_TWO:
    case SCENE::MAP_TWENTY_THREE:
    case SCENE::MAP_TWENTY_FOUR:
        return (sceneType == "MAP");
    case SCENE::BATTLE_GAME_ONE:
        return (sceneType == "BATTLE");
    case SCENE::BOSS_BATTLE_GAME_ONE:
        return (sceneType == "BOSS_BATTLE");
    case SCENE::GAME_OVER:
    case SCENE::GAME_NOTHING:
    case SCENE::GAME_CLEAR:
    case SCENE::BATTLE_RESULT:
        return (sceneType == "RESULT");
    case SCENE::EXCEPTION:
        return (sceneType == "EXCEPTION");
    case SCENE::SCENE_NULL:
        return (sceneType == "NULL");
    }
}

/*
* @fn SetTowerObject
* @drief タワー作成用関数
*/
void SceneManager::SetTowerObject(VECTOR plusPosition, int modelNumber, const char *filename, int xTowerNumber, int zTowerNumber)
{
    FixedTower *fixedTower = new FixedTower(plusPosition, modelNumber, filename, xTowerNumber, zTowerNumber);
    fixedTower->Initilize();
}

/*
* @fn SetPlayer
* @drief プレイヤー情報設定
*/
PLAYER_DATA SceneManager::SetPlayer(GENERATE_INFORATION* generateInforation, PLAYER_DATA playerData, CHARACTER_TYPE characterType)
{
    generateInforation->survivalFlag = playerData.characterData.survivalFlag;
    generateInforation->characterType = characterType; //GetCharacterType(playerData.characterData.templateData.typeName); // ここもいじるキャラモデルの変更など
    generateInforation->GeneratePosition = playerData.nextScenePos;
    generateInforation->angle = playerData.nextSceneAngle;
    generateInforation->status = playerData.characterData.status;
    generateInforation->name = playerData.characterData.templateData.name;
    generateInforation->scene = playerData.characterData.mapType;
    for (DATA_NAME fileNameData : mpDataManager->GetAllData(true)[0].datas.fileNameDatas)
    {
        if (fileNameData.fileTypeName == PLAYER_FILE_NAME)
        {
            generateInforation->dataFileName = fileNameData.fileName;
        }
    }

    return playerData;
}