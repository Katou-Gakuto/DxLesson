#include <iostream>
#include <string>

#include "../Header/Calculation.h"
#include "../Header/Camera.h"
#include "../Header/DataManager.h"
#include "../Header/Data_Structs.h"
#include "../Header/GameManager.h"
#include "../Header/MapCharacter.h"
#include "../Header/MenuCheck.h"
#include "../Header/MotionRobotSphere.h"
#include "../Header/ObjectManager.h"
#include "../Header/ObjectTagMacro.h"
#include "../Header/Object_Base.h"
#include "../Header/Object_Base_Character.h"
#include "../Header/Operation.h"
#include "../Header/SceneManager.h"
#include "../Header/Scene_Enum.h"
#include "../Header/Status_Struct.h"
#include "../Header/TimeManager.h"

/*
* @fn コンストラクタ
*/
MapCharacter::MapCharacter(STATUS status, VECTOR position, float angle, std::string name, CHARACTER_TYPE characterType, SCENE goScene, std::string characterFileName, bool deleteCharacterDataFlag)
: Object_Base_Character(status, angle, name, characterFileName)
, meCharacterType(characterType)
, mpPlayer(nullptr)
, mbPopUpFlag(false)
, meGoScene(goScene)
, mnNextAKeyTime(0)
, mnPopUpScreenHandle(-1)
, mnDrawPopUpStringHabdle(-1)
, mnDrawLevelNumber(0)
, mbDeleteCharacterDataFlag(deleteCharacterDataFlag)
{
    mvObjectPosition = position;

}

/*
* @fn デストラクタ
*/
MapCharacter::~MapCharacter()
{
}

/*
* @fn Initilize
* @drief 初期化
*/
void MapCharacter::Initilize()
{
    mpPlayer = Master::mpGameManager->GetObjectManager()->FindByTag_CharacterObject(PLAYER_TAG);

    switch (meCharacterType)
    {    
    case CHARACTER_TYPE::MAP_CHARACTER_1:
        mpMotion = new MotionRobotSphere(this, 2000 + GetRand(4000));
        mpMotion->Initilize();
        break;

    }

    mnDrawLevelNumber = 0;
    if (msStatus.level > 0) {
        mnDrawLevelNumber += 1;
        if (msStatus.level > 9) {
            mnDrawLevelNumber += 1;
            if (msStatus.level > 99) {
                mnDrawLevelNumber += 1;
                if (msStatus.level > 999) {
                    mnDrawLevelNumber += 1;
                }
            }
        }
    }

    mnPopUpScreenHandle = MakeScreen(190 + (GetGoSceneName().size() * 20) + (mnDrawLevelNumber * 20), 40);
    mnDrawPopUpStringHabdle = CreateFontToHandle(NULL, 35, 5);

    SetTag(NEUTRAL_CHARACTER);
}

/*
* @fnUpdate
* @drief 更新
*/
void MapCharacter::Update()
{
    // 時間停止フラグが有効なら更新しない
    if (Master::mpGameManager->GetTimeManager()->GetStopFlag()) {
        return;
    }

    if (PlayerCheck()) {
        PopUpProcess();
        mbPopUpFlag = true;
    }
    else {
        mbPopUpFlag = false;
    }

    // モーションフラグを初期化
    mpMotion->ReSetFlag();

    // 移動
    if (!mpMotion->GetStopMoveMotionFlag()) {
    }
    else {
        mpMotion->StopMoveProcess();
    }
    // 攻撃現在の時間
    if (!mpMotion->GetStopAttackFlag()) {
    }
    else {
        // 攻撃の処理の代わりの処理
        mpMotion->StopAttackProcess();
    }

    // モーション更新
    mpMotion->Update();
}

/*
* @fn Draw
* @drief 描画
*/
void MapCharacter::Draw()
{
    if (mbPopUpFlag || (msStatus.level >= 300)) {
        DrawPopUpText();
    }
    mpMotion->Draw();
}

/*
* @fn MyFinailize
* @drief 終了処理
*/
void MapCharacter::MyFinailize()
{
    DeleteGraph(mnPopUpScreenHandle);
    DeleteFontToHandle(mnDrawPopUpStringHabdle);
}

/*
* @fn HpZeroMove
* @drief HPが0以下時の処理
*/
void MapCharacter::HpZeroMove()
{
    mpMotion->SetMotionEnd(&mbMotionEndFlag);
}

/*
* @fn PlayerCheck
* @drief プレイヤーが近くに居るか
*/
bool MapCharacter::PlayerCheck()
{
    bool flag = false;
    if (mpPlayer != nullptr) {
        flag |= Calculation::Check_Circle_And_Pos(mvObjectPosition, (msStatus.size * 1.5) + (mpPlayer->GetStatus().size * 1.5), mpPlayer->GetObjectPosition());

    }
    
    return flag;
}

void MenuCheckDedicated_GoScene(Object_Base *object)
{
    MapCharacter *mapCharacter = dynamic_cast<MapCharacter *>(object);

    Master::mpGameManager->GetSceneManager()->SetNextScene(mapCharacter->GetGoScene());

    DataManager* dataManager = Master::mpGameManager->GetDataManager();

    PLAYER_DATA playerData = dataManager->GetPlayPlayerData();
    playerData.characterData.position = VGet(0.0f, 0.0f, 0.0f);
    playerData.characterData.angle = 0.0f;
    playerData.characterData.mapName = mapCharacter->GetGoSceneName();

    dataManager->SetPlayPlayerData(playerData);

    if (mapCharacter->GetDeleteDataFlag()) {
        OneData characterdata = dataManager->GetOneData(mapCharacter->GetCharacterDataFileName(), (int)DataType::CHARACTER);

        for (int i = 0; i < characterdata.datas.characterDatas.size(); i++)
        {
            if (characterdata.datas.characterDatas[i].templateData.name == mapCharacter->GetCharacterName())
            {
                characterdata.datas.characterDatas.erase(characterdata.datas.characterDatas.begin() + i);
                break;
            }
        }

        dataManager->ChangeOneData(characterdata, characterdata.fileNameAndType.name, (int)DataType::CHARACTER);
    }
}

/*
* @fn PopUpProcess
* @drief ポップアップ表示中の処理
*/
void MapCharacter::PopUpProcess()
{
    if (!mbPopUpFlag) {
        Master::mpGameManager->GetSoundManager()->SetSound(SOUND::POP_UP);
    }

    if (Operation::CheckAKey() && (mnNextAKeyTime <= Master::mpGameManager->GetTimeManager()->GetGameTime())) {
        MenuCheck *menuCheck = new MenuCheck(MenuCheckDedicated_GoScene, this);
        menuCheck->Initilize();

        mnNextAKeyTime = (Master::mpGameManager->GetTimeManager()->GetGameTime() + 340);
    }
}

/*
* @fn DrawPopUpText
* @drief ポップアップを表示する
*/
void MapCharacter::DrawPopUpText()
{

    // 描画必要データ取得
    VECTOR setCharacterPos = VAdd(mvObjectPosition, VGet(0, msStatus.size * 2.7, 0));

    // 描画先を変更
    SetDrawScreen(mnPopUpScreenHandle);
    ClearDrawScreen();

    // 土台
    DrawBoxAA(0, 0, 190 + (GetGoSceneName().size() * 20) + (mnDrawLevelNumber * 20), 40, GetColor(255, 255, 255), TRUE);
    DrawBoxAA(2, 2, 190 + (GetGoSceneName().size() * 20) + (mnDrawLevelNumber * 20) - 2, 40 - 2, GetColor(0, 0, 0), TRUE);

    // 移動するマップとレベルを表記
    DrawFormatStringToHandle(5, 3, GetColor(255, 255, 255), mnDrawPopUpStringHabdle, "\"A\"GO %s(Lv.%d)", GetGoSceneName().c_str(), msStatus.level);

    SetDrawScreen(DX_SCREEN_BACK);
    // 3Dカメラ設定
    Master::mpCamera->Initialize3DCameraTemplate();
    DrawBillboard3D(setCharacterPos, 0.5f, 0.5f, 200.0f, 0.0f, mnPopUpScreenHandle, TRUE);
}

/*
* @fn GetGoSceneName
* @drief 移動するシーンを文字列で取得
*/
std::string MapCharacter::GetGoSceneName()
{
    if (meGoScene == SCENE::MAP_ONE) {
        return "MAP_ONE";
    }
    if (meGoScene == SCENE::MAP_TWO) {
        return "MAP_TWO";
    }
    if (meGoScene == SCENE::MAP_THREE) {
        return "MAP_THREE";
    }
    if (meGoScene == SCENE::MAP_FOUR) {
        return "MAP_FOUR";
    }
    if (meGoScene == SCENE::MAP_FIVE) {
        return "MAP_FIVE";
    }
    if (meGoScene == SCENE::MAP_SIX) {
        return "MAP_SIX";
    }
    if (meGoScene == SCENE::MAP_SEVEN) {
        return "MAP_SEVEN";
    }
    if (meGoScene == SCENE::MAP_EIGHT) {
        return "MAP_EIGHT";
    }
    if (meGoScene == SCENE::MAP_NINE) {
        return "MAP_NINE";
    }
    if (meGoScene == SCENE::MAP_TEN) {
        return "MAP_TEN";
    }
    if (meGoScene == SCENE::MAP_ELEVEN) {
        return "MAP_ELEVEN";
    }
    if (meGoScene == SCENE::MAP_TWELVE) {
        return "MAP_TWELVE";
    }
    if (meGoScene == SCENE::MAP_THIRTEEN) {
        return "MAP_THIRTEEN";
    }
    if (meGoScene == SCENE::MAP_FOURTEEN) {
        return "MAP_FOURTEEN";
    }
    if (meGoScene == SCENE::MAP_FIFTEEN) {
        return "MAP_FIFTEEN";
    }
    if (meGoScene == SCENE::MAP_SIXTEEN) {
        return "MAP_SIXTEEN";
    }
    if (meGoScene == SCENE::MAP_SEVENTEEN) {
        return "MAP_SEVENTEEN";
    }
    if (meGoScene == SCENE::MAP_EIGHTEEN) {
        return "MAP_EIGHTEEN";
    }
    if (meGoScene == SCENE::MAP_NINETEEN) {
        return "MAP_NINETEEN";
    }
    if (meGoScene == SCENE::MAP_TWENTY) {
        return "MAP_TWENTY";
    }
    if (meGoScene == SCENE::MAP_TWENTY_ONE) {
        return "MAP_TWENTY_ONE";
    }
    if (meGoScene == SCENE::MAP_TWENTY_TWO) {
        return "MAP_TWENTY_TWO";
    }
    if (meGoScene == SCENE::MAP_TWENTY_THREE) {
        return "MAP_TWENTY_THREE";
    }
    if (meGoScene == SCENE::MAP_TWENTY_FOUR) {
        return "MAP_TWENTY_FOUR";
    }
    return "NULL";
}