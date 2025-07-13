#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

#include "DxLib.h"
#include "../Header/DataManager.h"
#include "../Header/DataManagerMacro.h"
#include "../Header/Data_Structs.h"
#include "../Header/GameManager.h"
#include "../Header/ItemRecoveryMedicine.h"
#include "../Header/Item_Base.h"
#include "../Header/SceneManager.h"
#include "../Header/Scene_Enum.h"

/*
* @fn コンストラクタ
*/
DataManager::DataManager()
: mbFailureFlag(false)
{
    //std::string tet;
  //  const char* test =  "gg";
//    OneData set = GetFileData<OneData>(tet, test);
}

/*
* @fn デストラクタ
*/
DataManager::~DataManager()
{
}

/*
* @fn Initilize
* @drief 初期化
*/
void DataManager::Initilize()
{
    SetAllData("GameData/FileNames_Data.txt");
}

/*
* @fn AllSetData
* @drief 全データ設定
*/
void DataManager::SetAllData(const char* fileName)
{
    SetBaseAllData(fileName);
    // 上の関数内に入れる
    SetLevelData(GetFileName_FileType(LEVEL_FILE_NAME, GetBaseData_FileName()));
    
    SetPlayerData(GetFileName_FileType(PLAYER_FILE_NAME, msBaseDatas.oneDatas[CheckDataType(FILE_NAMES_FILE_NAME, msBaseDatas.oneDatas)[0]].fileNameDatas));
}

/*
* @fn GetNotPlayer_AllDatas
* @drief 指定されているファイルにあるデータを返す
*/
std::vector<OneData> DataManager::GetAllDatas(std::string dataNames)
{
    // ファイル名
    {

    }
    std::vector<OneData> getDatas;
    
    // for {
    // データ
    {

    }

    // プレイヤーデータ
    {
    }
    // }

    return getDatas;
}

template <typename dataTemplate>
dataTemplate DataManager::GetFileData(std::string typeName, const char* fileName)
{
    switch (dataTemplate)
    {
    case DATA_NAME:
        break;

    case CHARACTER_DATA:
        break;

    case MAP_DATA:
        break;

    case LEVEL_DATA:
        break;
    }
}

/*
* @fn GetNotPlayer_OneData
* @drief ファイルのタイプに合ったデータに入力を返す
*/
OneData DataManager::GetNotPlayer_OneData(std::string fileTypeName, std::string fileName, bool* playerDataFlag)
{
    OneData getOneData;
    

    if (fileTypeName == NOT_PLAYER_CHARACTER_FILE_NAME)
    {

    }
    else if (fileTypeName == MAP_FILE_NAME)
    {

    }
    else if (fileTypeName == FILE_NAMES_FILE_NAME)
    {

    }
    else if (fileTypeName == LEVEL_FILE_NAME)
    {

    }
    else
    {
        *playerDataFlag = true;
    }
//    PLAYER_INIT_DATA_FILE_NAME  別で現在プレイヤーデータも
    return getOneData;
}

/*
* @fn CheckDataType
* @drief 指定のタイプが何個目にあるかを返す
*/
std::vector<int> DataManager::CheckDataType(std::string checkTypeName, std::vector<OneData> detas)
{
    std::vector<int> numbers;

    for (int i = 0; i < detas.size(); i++)
    {
        if (detas[i].fileNameAndType.typeName == checkTypeName)
        {
            numbers.push_back(i);
        }
    }

    return numbers;
}

/*
* @fn GetFileNameInitializationData
* @drie 初期化されたファイル名データ
*/
DATA_NAME DataManager::GetFileNameInitializationData()
{
    DATA_NAME fileName;
    fileName.fileName = "NULL";
    fileName.fileTypeName = "NULL";
    fileName.sceneType = SCENE::SCENE_NULL;

    return fileName;
}

/*
* @fn Delete_OneFile
* @drief ファイル削除
*/
void DataManager::Delete_OneFile(const char *fileName, const char *fileTypeName)
{
    // ファイルを開ける
    std::ifstream fileData;
    fileData.open(fileName, std::ios_base::in);

    bool flag = false;

    if (fileData.is_open())
    {
        std::string check;
        fileData >> check;

        if (check == fileTypeName) {
            flag = true;
        }
    }
    // ファイル閉じる
    fileData.close();

    if (flag) {
        std::remove(fileName);
    }
}

/*
* @fn GetFileName_FileType
* @drief 指定されたファイルの中から指定のファイルタイプのファイル名を一つ返す
*/
std::string DataManager::GetFileName_FileType(const char *fileType, std::vector<DATA_NAME> fileNameData)
{
    for (int i = 0; i < fileNameData.size(); i++) {
        if (fileNameData[i].fileTypeName == fileType) {
            return fileNameData[i].fileName;
        }
    }

    return "NULL";
}

/*
* @fn GetFileNames_FileType
* @drief 指定されたファイルの中から指定のファイルタイプのファイル名を全て返す
*/
std::vector<std::string> DataManager::GetFileNames_FileType(const char *fileType, std::vector<DATA_NAME> fileNameData)
{
    std::vector<std::string> setFileNames;
    setFileNames.clear();

    for (int i = 0; i < fileNameData.size(); i++) {
        if (fileNameData[i].fileTypeName == fileType) {
            setFileNames.push_back(fileNameData[i].fileName);
        }
    }

    return setFileNames;
}

/*
* @fn GetFileName_SceneType
* @drief 指定されたシーンで生成されるファイルデータを一つ返す
*/
DATA_NAME DataManager::GetFileName_SceneType(SCENE scene)
{
    for (int i = 0; i < msBaseDatas.oneDatas[0].fileNameDatas.size(); i++) {
        if (msBaseDatas.oneDatas[0].fileNameDatas[i].sceneType == scene) {
            return msBaseDatas.oneDatas[0].fileNameDatas[i];
        }
    }

    return GetFileNameInitializationData();
}

/*
* @fn GetFileNames_SceneType
* @drief 指定されたシーンで生成されるファイルデータを全て返す
*/
std::vector<DATA_NAME> DataManager::GetFileNames_SceneType(SCENE scene)
{
    std::vector<DATA_NAME> setFileNames;
    setFileNames.clear();

    for (int i = 0; i < msBaseDatas.oneDatas[0].fileNameDatas.size(); i++) {
        if (msBaseDatas.oneDatas[0].fileNameDatas[i].sceneType == scene) {
            setFileNames.push_back(msBaseDatas.oneDatas[0].fileNameDatas[i]);
        }
    }

    return setFileNames;
}

/*
* @fn Init_PlayerFileName_And_Item
* @drief プレイヤー用ファイルの名前とアイテム情報取得
*/
void DataManager::Init_PlayerFileName_And_Item(int playerNumber)
{
    // プレイヤーファイル設定
    SetFile_PlayerFileNameDatas(GetPlayerFilePos("/FileNames_Data.txt", playerNumber));

    // アイテム生成
    SetItems(playerNumber);
}

/*
* @fn GetSceneType
* @drief 文字列をシーンタイプのenumに変換する
*/
SCENE DataManager::GetSceneType(std::string sceneType)
{
    if (sceneType == "SART") {
        return SCENE::SART;
    }
    if (sceneType == "TITLE") {
        return SCENE::TITLE;
    }
    if (sceneType == "SELECT_SAVE_DATA") {
        return SCENE::SELECT_SAVE_DATA;
    }
    if (sceneType == "DEFAULT_MAP_ONE") {
        return SCENE::DEFAULT_MAP_ONE;
    }

    if (sceneType == "MAP_ONE") {
        return SCENE::MAP_ONE;
    }
    if (sceneType == "MAP_TWO") {
        return SCENE::MAP_TWO;
    }
    if (sceneType == "MAP_THREE") {
        return SCENE::MAP_THREE;
    }
    if (sceneType == "MAP_FOUR") {
        return SCENE::MAP_FOUR;
    }
    if (sceneType == "MAP_FIVE") {
        return SCENE::MAP_FIVE;
    }
    if (sceneType == "MAP_SIX") {
        return SCENE::MAP_SIX;
    }
    if (sceneType == "MAP_SEVEN") {
        return SCENE::MAP_SEVEN;
    }
    if (sceneType == "MAP_EIGHT") {
        return SCENE::MAP_EIGHT;
    }
    if (sceneType == "MAP_NINE") {
        return SCENE::MAP_NINE;
    }
    if (sceneType == "MAP_TEN") {
        return SCENE::MAP_TEN;
    }
    if (sceneType == "MAP_ELEVEN") {
        return SCENE::MAP_ELEVEN;
    }
    if (sceneType == "MAP_TWELVE") {
        return SCENE::MAP_TWELVE;
    }
    if (sceneType == "MAP_THIRTEEN") {
        return SCENE::MAP_THIRTEEN;
    }
    if (sceneType == "MAP_FOURTEEN") {
        return SCENE::MAP_FOURTEEN;
    }
    if (sceneType == "MAP_FIFTEEN") {
        return SCENE::MAP_FIFTEEN;
    }
    if (sceneType == "MAP_SIXTEEN") {
        return SCENE::MAP_SIXTEEN;
    }
    if (sceneType == "MAP_SEVENTEEN") {
        return SCENE::MAP_SEVENTEEN;
    }
    if (sceneType == "MAP_EIGHTEEN") {
        return SCENE::MAP_EIGHTEEN;
    }
    if (sceneType == "MAP_NINETEEN") {
        return SCENE::MAP_NINETEEN;
    }
    if (sceneType == "MAP_TWENTY") {
        return SCENE::MAP_TWENTY;
    }
    if (sceneType == "MAP_TWENTY_ONE") {
        return SCENE::MAP_TWENTY_ONE;
    }
    if (sceneType == "MAP_TWENTY_TWO") {
        return SCENE::MAP_TWENTY_TWO;
    }
    if (sceneType == "MAP_TWENTY_THREE") {
        return SCENE::MAP_TWENTY_THREE;
    }
    if (sceneType == "MAP_TWENTY_FOUR") {
        return SCENE::MAP_TWENTY_FOUR;
    }

    if (sceneType == "BATTLE_GAME_ONE") {
        return SCENE::BATTLE_GAME_ONE;
    }
    if (sceneType == "BOSS_BATTLE_GAME_ONE") {
        return SCENE::BOSS_BATTLE_GAME_ONE;
    }
    if (sceneType == "BATTLE_RESULT") {
        return SCENE::BATTLE_RESULT;
    }
    if (sceneType == "GAME_OVER") {
        return SCENE::GAME_OVER;
    }
    if (sceneType == "GAME_CLEAR") {
        return SCENE::GAME_CLEAR;
    }
    if (sceneType == "GAME_NOTHING") {
        return SCENE::GAME_NOTHING;
    }
    if (sceneType == "EXCEPTION") {
        return SCENE::EXCEPTION;
    }

    return SCENE::SCENE_NULL;
}

/*
* @fn SetFile_FileNameData
* @drief ファイル名用　ファイル情報　書き込み処理
*/
void DataManager::SetFile_FileNameData(std::ofstream *file, DATA_NAME nameData)
{
    *file << '\n';
    *file << nameData.fileName;
    *file << '\n';
    *file << nameData.fileTypeName;
    *file << '\n';
    switch (nameData.sceneType)
    {
    case SCENE::SART:   // スタート
        *file << "SART";
        break;

    case SCENE::TITLE:
        *file << "TITLE";
        break;

    case SCENE::DEFAULT_MAP_ONE:
        *file << "DEFAULT_MAP_ONE";
        break;

    case SCENE::MAP_ONE:
        *file << "MAP_ONE";
        break;
    case SCENE::MAP_TWO:
        *file << "MAP_TWO";
        break;
    case SCENE::MAP_THREE:
        *file << "MAP_THREE";
        break;
    case SCENE::MAP_FOUR:
        *file << "MAP_FOUR";
        break;
    case SCENE::MAP_FIVE:
        *file << "MAP_FIVE";
        break;
    case SCENE::MAP_SIX:
        *file << "MAP_SIX";
        break;
    case SCENE::MAP_SEVEN:
        *file << "MAP_SEVEN";
        break;
    case SCENE::MAP_EIGHT:
        *file << "MAP_EIGHT";
        break;
    case SCENE::MAP_NINE:
        *file << "MAP_NINE";
        break;
    case SCENE::MAP_TEN:
        *file << "MAP_TEN";
        break;
    case SCENE::MAP_ELEVEN:
        *file << "MAP_ELEVEN";
        break;
    case SCENE::MAP_TWELVE:
        *file << "MAP_TWELVE";
        break;
    case SCENE::MAP_THIRTEEN:
        *file << "MAP_THIRTEEN";
        break;
    case SCENE::MAP_FOURTEEN:
        *file << "MAP_FOURTEEN";
        break;
    case SCENE::MAP_FIFTEEN:
        *file << "MAP_FIFTEEN";
        break;
    case SCENE::MAP_SIXTEEN:
        *file << "MAP_SIXTEEN";
        break;
    case SCENE::MAP_SEVENTEEN:
        *file << "MAP_SEVENTEEN";
        break;
    case SCENE::MAP_EIGHTEEN:
        *file << "MAP_EIGHTEEN";
        break;
    case SCENE::MAP_NINETEEN:
        *file << "MAP_NINETEEN";
        break;
    case SCENE::MAP_TWENTY:
        *file << "MAP_TWENTY";
        break;
    case SCENE::MAP_TWENTY_ONE:
        *file << "MAP_TWENTY_ONE";
        break;
    case SCENE::MAP_TWENTY_TWO:
        *file << "MAP_TWENTY_TWO";
        break;
    case SCENE::MAP_TWENTY_THREE:
        *file << "MAP_TWENTY_THREE";
        break;
    case SCENE::MAP_TWENTY_FOUR:
        *file << "MAP_TWENTY_FOUR";
        break;

    case SCENE::BATTLE_GAME_ONE:
        *file << "BATTLE_GAME_ONE";
        break;

    case SCENE::BOSS_BATTLE_GAME_ONE:
        *file << "BOSS_BATTLE_GAME_ONE";
        break;

    case SCENE::BATTLE_RESULT:
        *file << "BATTLE_RESULT";
        break;

    case SCENE::GAME_OVER:
        *file << "GAME_OVER";
        break;

    case SCENE::GAME_CLEAR:
        *file << "GAME_CLEAR";
        break;

    case SCENE::GAME_NOTHING:
        *file << "GAME_NOTHING";
        break;

    case SCENE::EXCEPTION:  // 例外
        *file << "EXCEPTION";
        break;
    }
}

/*
* @fn GetFile_fileNameData
* @drief ファイル名用　ファイル情報　読み取り処理
*/
DATA_NAME DataManager::GetFile_fileNameData(std::ifstream *file)
{
    std::string sceneType = const_cast<char *>("NULL");
    DATA_NAME dataName = GetFileNameInitializationData();
    *file >> dataName.fileName;
    *file >> dataName.fileTypeName;
    *file >> sceneType;
    dataName.sceneType = GetSceneType(sceneType);

    return dataName;
}

/*
* @fn SetFile_FileNameDatas
* @drief ファイル名データを取得
*/
void DataManager::SetBaseAllData(std::string fileName)
{
    // リセット
    msBaseDatas.oneDatas.clear();
    OneData setOneData;
    std::vector<DATA_NAME> setFileNameDatas;

    // ファイルを開ける
    std::ifstream fileNamesData;
    fileNamesData.open(fileName, std::ios_base::in);

    // ファイルオープン失敗フラグ有効化
    mbFailureFlag = true;

    if (fileNamesData.is_open()) 
    {
        // ファイル確認
        std::string fileNameCheck;
        fileNamesData >> fileNameCheck;
        if (fileNameCheck == FILE_NAMES_FILE_NAME) {
            int fileNumber = 0;
            fileNamesData >> fileNumber;
            for (int i = 0; i < fileNumber; i++)
            {
                DATA_NAME setFileNameData = GetFile_fileNameData(&fileNamesData);

                // 末尾に追加
                setFileNameDatas.push_back(setFileNameData);
            }
            setOneData.fileNameAndType.name = fileName;
            setOneData.fileNameAndType.typeName = FILE_NAMES_FILE_NAME;
            setOneData.fileNameDatas = setFileNameDatas;
            setOneData.dataChangeFlag = false;
            msBaseDatas.oneDatas.push_back(setOneData);
        }

        // ファイルオープン失敗フラグ無効化
        mbFailureFlag = false;
    }
    else {
        int TEST = 0;
    }
    

    // ファイルを閉じる
    fileNamesData.close();
}

/*
* @fn AddFile_FileNameData
* @drief ファイル名データを追加
*/
void DataManager::AddFile_FileNameData(std::string fileName, DATA_NAME dataName)
{

    //-- 書き込み前情報取得 --//
    // ファイルを開ける
    std::ifstream getFileNamesData;
    getFileNamesData.open(fileName, std::ios_base::in);

    // ファイル名用フォルダ一時保存用
    std::vector<DATA_NAME> setDataNames;
    setDataNames.clear();

    // ファイルがファイル名用ファイルかどうかのフラグ
    bool notFileNameFlag = false;

    // ファイルオープン失敗フラグ有効化
    mbFailureFlag = true;

    if (getFileNamesData.is_open())
    {
        // ファイル確認
        std::string fileNameCheck;
        getFileNamesData >> fileNameCheck;
        if (fileNameCheck == FILE_NAMES_FILE_NAME) {
            int fileNumber = 0;
            getFileNamesData >> fileNumber;
            for (int i = 0; i < fileNumber; i++)
            {
                DATA_NAME setFileNameData = GetFile_fileNameData(&getFileNamesData);
                
                setDataNames.push_back(setFileNameData);
            }
        }
        else {
            notFileNameFlag = true;
        }

        // ファイルオープン失敗フラグ無効化
        mbFailureFlag = false;
    }
    else {
        notFileNameFlag = true;
        int TEST = 0;
    }

    // ファイルを閉じる
    getFileNamesData.close();
    //--                    --//



    if (!notFileNameFlag) 
    {
        //-- 書き込み開始 --//
        // ファイルを開ける
        std::ofstream setFileNamesData;
        setFileNamesData.open(fileName, std::ios_base::out);

        // ファイルオープン失敗フラグ有効化
        mbFailureFlag = true;

        if (setFileNamesData.is_open()) 
        {
            setFileNamesData << FILE_NAMES_FILE_NAME;
            setFileNamesData << '\n';
            setFileNamesData << (setDataNames.size() + 1);

            for (int i = 0; i < setDataNames.size(); i++) {
                SetFile_FileNameData(&setFileNamesData, setDataNames[i]);
            }

            SetFile_FileNameData(&setFileNamesData, dataName);

            // ファイルオープン失敗フラグ無効化
            mbFailureFlag = false;

        }
        else {
            int TEST = 0;
        }


        // ファイルを閉じる
        setFileNamesData.close();
        //--              --//
    }
}

/*
* @fn DeleteFile_FileNameData
* @drief ファイル名データを削除
*/
void DataManager::DeleteFile_FileNameData(std::string fileName, std::string deleteFileName, const char *deleteFileTypeName)
{

    //-- 書き込み前情報取得 --//
    // ファイルを開ける
    std::ifstream getFileNamesData;
    getFileNamesData.open(fileName, std::ios_base::in);

    // ファイル名用フォルダ一時保存用
    std::vector<DATA_NAME> setDataNames;
    setDataNames.clear();

    // ファイルがファイル名用ファイルかどうかのフラグ
    bool notFileNameFlag = false;

    // ファイルオープン失敗フラグ有効化
    mbFailureFlag = true;

    if (getFileNamesData.is_open())
    {
        // ファイル確認
        std::string fileNameCheck;
        getFileNamesData >> fileNameCheck;
        if (fileNameCheck == FILE_NAMES_FILE_NAME) {
            int fileNumber = 0;
            getFileNamesData >> fileNumber;
            for (int i = 0; i < fileNumber; i++)
            {
                DATA_NAME setFileNameData = GetFile_fileNameData(&getFileNamesData);

                // 削除対象なら追加しない
                if (setFileNameData.fileName != deleteFileName || setFileNameData.fileTypeName != deleteFileTypeName)
                {
                    // 末尾に追加
                    setDataNames.push_back(setFileNameData);
                }
            }
        }
        else {
            notFileNameFlag = true;
        }

        // ファイルオープン失敗フラグ無効化
        mbFailureFlag = false;
    }
    else {
        notFileNameFlag = true;
        int TEST = 0;
    }

    // ファイルを閉じる
    getFileNamesData.close();
    //--                    --//



    if (!notFileNameFlag)
    {
        //-- 書き込み開始 --//
        // ファイルを開ける
        std::ofstream setFileNamesData;
        setFileNamesData.open(fileName, std::ios_base::out);

        // ファイルオープン失敗フラグ有効化
        mbFailureFlag = true;

        if (setFileNamesData.is_open())
        {
            setFileNamesData << FILE_NAMES_FILE_NAME;
            setFileNamesData << '\n';
            setFileNamesData << setDataNames.size();

            for (int i = 0; i < setDataNames.size(); i++) {
                SetFile_FileNameData(&setFileNamesData, setDataNames[i]);
            }

            // ファイルオープン失敗フラグ無効化
            mbFailureFlag = false;

        }
        else {
            int TEST = 0;
        }


        // ファイルを閉じる
        setFileNamesData.close();
        //--              --//
    }
}

/*
* @fn GetFile_fileNameDatas
* @drief ファイル名取得
*/
std::vector<DATA_NAME> DataManager::GetFile_fileNameDatas(std::string fileName)
{
    // ファイルを開ける
    std::ifstream fileNamesData;
    fileNamesData.open(fileName, std::ios_base::in);
    std::vector<DATA_NAME> file;
    file.clear();

    // ファイルオープン失敗フラグ有効化
    mbFailureFlag = true;

    if (fileNamesData.is_open())
    {
        // ファイル確認
        std::string fileNameCheck;
        fileNamesData >> fileNameCheck;
        if (fileNameCheck == FILE_NAMES_FILE_NAME) {
            int fileNumber = 0;
            fileNamesData >> fileNumber;
            for (int i = 0; i < fileNumber; i++)
            {
                DATA_NAME setFileNameData = GetFile_fileNameData(&fileNamesData);

                // 末尾に追加
                file.push_back(setFileNameData);
            }
        }

        // ファイルオープン失敗フラグ無効化
        mbFailureFlag = false;
    }
    else {
        int TEST = 0;
    }

    // ファイルを閉じる
    fileNamesData.close();

    return file;
}

/*
* @fn SetFile_PlayerFileData
* @driefr プレイヤー用　ファイル情報　書き込み処理
*/
void DataManager::SetFile_PlayerFileData(std::ofstream *file, PLAYER_DATA playerData)
{
    *file << '\n';
    *file << playerData.dataFlag;
    *file << '\n';
    *file << playerData.characterData.templateData.typeName;
    *file << '\n';
    *file << playerData.characterData.templateData.name;
    *file << '\n';
    *file << playerData.characterData.survivalFlag;
    *file << '\n';
    *file << playerData.characterData.status.level;
    *file << '\n';
    *file << playerData.characterData.status.exp;
    *file << '\n';
    *file << playerData.characterData.status.attackPower;
    *file << '\n';
    *file << playerData.characterData.status.maxHp;
    *file << '\n';
    *file << playerData.characterData.status.hp;
    *file << '\n';
    *file << playerData.characterData.status.defense;
    *file << '\n';
    *file << playerData.characterData.status.speed;
    *file << '\n';
    *file << playerData.characterData.status.size;
    *file << '\n';
    *file << playerData.characterData.mapName;
    *file << '\n';
    *file << playerData.characterData.position.x;
    *file << '\n';
    *file << playerData.characterData.position.y;
    *file << '\n';
    *file << playerData.characterData.position.z;
    *file << '\n';
    *file << playerData.characterData.angle;
    *file << '\n';
    *file << playerData.playerFolderName;
    *file << '\n';
    *file << playerData.itemNumber;
    for (int i = 0; i < playerData.itemNumber; i++) {
        *file << '\n';
        *file << playerData.itemData[i].templateData.name;
        *file << '\n';
        *file << playerData.itemData[i].templateData.typeName;
        *file << '\n';
        *file << playerData.itemData[i].possessionCount;
        *file << '\n';
        *file << playerData.itemData[i].itemPhotoFileName;
    }
}

/*
* @fn GetData_PlayerFileData
* @drief プレイヤー用　ファイル情報読み取り
*/
PLAYER_DATA DataManager::GetData_PlayerFileData(std::ifstream *file)
{
    PLAYER_DATA setPlayerData;

    *file >> setPlayerData.dataFlag;    // セーブされたデータがあるかどうか
    *file >> setPlayerData.characterData.templateData.typeName;    // キャラクタータイプ
    *file >> setPlayerData.characterData.templateData.name;    // キャラクターの名前
    *file >> setPlayerData.characterData.survivalFlag;    // キャラクターの生存フラグ
    *file >> setPlayerData.characterData.status.level;  // レベル
    *file >> setPlayerData.characterData.status.exp;    // 経験値
    *file >> setPlayerData.characterData.status.attackPower;  // 攻撃力
    *file >> setPlayerData.characterData.status.maxHp;    // 最大HP
    *file >> setPlayerData.characterData.status.hp;       // HP
    *file >> setPlayerData.characterData.status.defense;  // 防御力
    *file >> setPlayerData.characterData.status.speed;    // 速度
    *file >> setPlayerData.characterData.status.size; // 大きさ
    *file >> setPlayerData.characterData.mapName; // マップ名
    *file >> setPlayerData.characterData.position.x;  // 居る場所X軸
    *file >> setPlayerData.characterData.position.y;  // 居る場所Y軸
    *file >> setPlayerData.characterData.position.z;  // 居る場所Z軸
    *file >> setPlayerData.characterData.angle;  // 見ている方向
    *file >> setPlayerData.playerFolderName; // プレイヤー情報があるフォルダー名
    
    *file >> setPlayerData.itemNumber;   // アイテムの数
    for (int i = 0; i < setPlayerData.itemNumber; i++) {
        ItemData setItemData;
        *file >> setItemData.templateData.name;
        *file >> setItemData.templateData.typeName;
        *file >> setItemData.possessionCount;
        *file >> setItemData.itemPhotoFileName;

        setPlayerData.itemData.push_back(setItemData);
    }

    return setPlayerData;
}

/*
* @fn GetFile_PlayerFileDatas
* @drief ファイルからプレイヤーデータを複数取得
*/
std::vector<PLAYER_DATA> DataManager::GetFile_PlayerFileDatas(std::string fileName)
{
    std::vector<PLAYER_DATA> playerDatas;

    // ファイルを開ける
    std::ifstream playerDataFile;
    playerDataFile.open(fileName, std::ios_base::in);

    // ファイルオープン失敗フラグ有効化
    mbFailureFlag = true;

    if (playerDataFile.is_open())
    {
        // ファイル確認
        std::string getFileName;
        playerDataFile >> getFileName;
        if (getFileName == PLAYER_FILE_NAME || getFileName == PLAYER_INIT_DATA_FILE_NAME)
        {
            // プレイヤーファイル情報読み取り
            int dataNumber;
            playerDataFile >> dataNumber;
            for (int i = 0; i < dataNumber; i++) {
                PLAYER_DATA setPlayerData;

                setPlayerData = GetData_PlayerFileData(&playerDataFile);

                playerDatas.push_back(setPlayerData);
            }
        }

        // ファイルオープン失敗フラグ無効化
        mbFailureFlag = false;
    }
    else {
        int TEST = 0;
    }

    playerDataFile.close();

    return playerDatas;
}

/*
* @fn SetPlayerData
* @drief メンバプレイヤーデータに保存
*/
void DataManager::SetPlayerData(std::string fileName)
{
    std::vector<PLAYER_DATA>setPlayerData = GetFile_PlayerFileDatas(fileName);

    for (int i = 0; i < PLAYER_DATA_NUMBER; i++) {
        msPlayerData[i].playerData = setPlayerData[i];
    }
}

/*
* @fn SetFile_PlayerFileNameDatas
* @drief プレイヤー用ファイルネームデータを設定
*/
void DataManager::SetFile_PlayerFileNameDatas(std::string fileName)
{
    msPlayerFileNameData.clear();

    // ファイルを開ける
    std::ifstream fileNamesData;
    fileNamesData.open(fileName, std::ios_base::in);

    // ファイルオープン失敗フラグ有効化
    mbFailureFlag = true;

    if (fileNamesData.is_open())
    {
        // ファイル確認
        std::string fileNameCheck;
        fileNamesData >> fileNameCheck;
        if (fileNameCheck == FILE_NAMES_FILE_NAME) {
            int fileNumber = 0;
            fileNamesData >> fileNumber;
            for (int i = 0; i < fileNumber; i++)
            {
                DATA_NAME setFileNameData = GetFile_fileNameData(&fileNamesData);

                // 末尾に追加
                msPlayerFileNameData.push_back(setFileNameData);
            }
        }

        // ファイルオープン失敗フラグ無効化
        mbFailureFlag = false;
    }
    else {
        int TEST = 0;
    }


    // ファイルを閉じる
    fileNamesData.close();
}

/*
* @fn ChangeFile_PlayerFileData
* @drief プレイヤーデータ変更
*/
void DataManager::ChangeFile_PlayerFileData(std::string fileName, std::string playerName, PLAYER_DATA playerData)
{
    // 必要情報
    std::vector<PLAYER_DATA> allFileData;
    allFileData.clear();
    std::string fileTypeName;
    int dataNumber = 0;
    bool notPlayerFlag = false;
    int playerCharacterNumber = -1;

    //-- 書き込み前情報取得 --//
    // ファイルを開ける
    std::ifstream getFileData;
    getFileData.open(fileName, std::ios_base::in);

    // ファイルオープン失敗フラグ有効化
    mbFailureFlag = true;

    if (getFileData.is_open())
    {
        // ファイル確認
        getFileData >> fileTypeName;
        if (fileTypeName == PLAYER_FILE_NAME)
        {
            // ファイル情報読み取り
            getFileData >> dataNumber;
            for (int i = 0; i < dataNumber; i++)
            {
                // 一時保存用
                PLAYER_DATA setData;

                // 読み取り処理
                setData = GetData_PlayerFileData(&getFileData);

                // 指定されたキャラクターなら何処に居たか記録する
                if (setData.characterData.templateData.name == playerName) {
                    playerCharacterNumber = i;
                }

                // 取得したデータを保存する
                allFileData.push_back(setData);
            }
        }
        else {
            notPlayerFlag = true;
        }

        // ファイルオープン失敗フラグ無効化
        mbFailureFlag = false;
    }
    else {
        int TEST = 0;
    }

    // ファイル閉じる
    getFileData.close();
    //--                    --//


    //-- 書き込み開始 --//
    if (!notPlayerFlag)
    {
        // ファイルを開ける
        std::ofstream setFileData;
        setFileData.open(fileName, std::ios_base::out);

        // ファイルオープン失敗フラグ有効化
        mbFailureFlag = true;

        if (setFileData.is_open())
        {
            // 書き込み
            setFileData << fileTypeName;
            setFileData << '\n';
            setFileData << dataNumber;
            for (int i = 0; i < dataNumber; i++) {
                // 書き込み処理
                if (playerCharacterNumber != i)
                {
                    SetFile_PlayerFileData(&setFileData, allFileData[i]);
                }
                else {
                    // 指定された場所に新しいキャラクター情報を入れる
                    SetFile_PlayerFileData(&setFileData, playerData);
                }
            }

            // ファイルオープン失敗フラグ無効化
            mbFailureFlag = false;
        }
        else {
            int TEST = 0;
        }

        // ファイル閉じる
        setFileData.close();
    }
    //--              --//
}

/*
* @fn SetItems
* @drief アイテムセット
*/
void DataManager::SetItems(int playerNumber)
{
    mpItem.clear();

    for (int i = 0; i < msPlayerData[playerNumber].playerData.itemNumber; i++) {

        Item_Base *itemBase;
        ITEM_DATA checkItemData = msPlayerData[playerNumber].playerData.itemData[i];

        if (checkItemData.templateData.typeName == "RecoveryMedicine(Small)") {
            itemBase = new ItemRecoveryMedicine(checkItemData, 30);
        }
        else if (checkItemData.templateData.typeName == "RecoveryMedicine(Medium)") {
            itemBase = new ItemRecoveryMedicine(checkItemData, 100);
        }
        else if (checkItemData.templateData.typeName == "RecoveryMedicine(Large)") {
            itemBase = new ItemRecoveryMedicine(checkItemData, 500);
        }

        mpItem.push_back(itemBase);
    }
}

/*
* @fn DeleteItem
* @drief アイテム削除
*/
void DataManager::DeleteItem(std::string itemName)
{
    int setNumber = Master::mpGameManager->GetSceneManager()->GetPlayerDataNumber();

    for (int i = 0; i < msPlayerData[setNumber].playerData.itemNumber; i++) {
        if (msPlayerData[setNumber].playerData.itemData[i].templateData.name == itemName) {
            msPlayerData[setNumber].playerData.itemNumber -= 1;
            msPlayerData[setNumber].playerData.itemData.erase(msPlayerData[setNumber].playerData.itemData.begin() + i);

            SetItems(Master::mpGameManager->GetSceneManager()->GetPlayerDataNumber());
            return;
        }
    }
}

/*
* @fn SetFile_CharacterFileData
* @drief キャラクター用 ファイル情報 書き込み処理
*/
void DataManager::SetFile_CharacterFileData(std::ofstream *file, CHARACTER_DATA characterData)
{
    *file << '\n';
    *file << characterData.templateData.typeName;    // キャラクタータイプ
    *file << '\n';
    *file << characterData.templateData.name;    // キャラクターの名前
    *file << '\n';
    *file << characterData.survivalFlag;    // キャラクター生存フラグ
    *file << '\n';
    *file << characterData.status.level;    // レベル
    *file << '\n';
    *file << characterData.status.exp;  // 経験値
    *file << '\n';
    *file << characterData.status.attackPower;  // 攻撃力
    *file << '\n';
    *file << characterData.status.maxHp;    // 最大HP
    *file << '\n';
    *file << characterData.status.hp;       // HP
    *file << '\n';
    *file << characterData.status.defense;  // 防御力
    *file << '\n';
    *file << characterData.status.speed;    // 速度
    *file << '\n';
    *file << characterData.status.size; // 大きさ
    *file << '\n';
    *file << characterData.mapName; // マップ名
    *file << '\n';
    *file << characterData.position.x;  // 居る場所X軸
    *file << '\n';
    *file << characterData.position.y;  // 居る場所Y軸
    *file << '\n';
    *file << characterData.position.z;  // 居る場所Z軸
    *file << '\n';
    *file << characterData.angle;   // 見ている方向
}

/*
* @fn GetCharacterFileData
* @drief キャラクター用 ファイル情報 読み込み処理
*/
CHARACTER_DATA DataManager::GetFile_CharacterFileData(std::ifstream *file)
{
    CHARACTER_DATA characterData;

    *file >> characterData.templateData.typeName;    // キャラクタータイプ
    *file >> characterData.templateData.name;    // キャラクターの名前
    *file >> characterData.survivalFlag;    // キャラクターの生存フラグ
    *file >> characterData.status.level;    // レベル
    *file >> characterData.status.exp;  // 経験値
    *file >> characterData.status.attackPower;  // 攻撃力
    *file >> characterData.status.maxHp;    // 最大HP
    *file >> characterData.status.hp;       // HP
    *file >> characterData.status.defense;  // 防御力
    *file >> characterData.status.speed;    // 速度
    *file >> characterData.status.size; // 大きさ
    *file >> characterData.mapName; // マップ名
    *file >> characterData.position.x;  // 居る場所X軸
    *file >> characterData.position.y;  // 居る場所Y軸
    *file >> characterData.position.z;  // 居る場所Z軸
    *file >> characterData.angle;   // 向いている方向

    return characterData;
}

/*
* @fn GetCharacterInitializationData
* @drief 初期化されたキャラクターデータ
*/
CHARACTER_DATA DataManager::GetCharacterInitializationData()
{
    CHARACTER_DATA set;
    set.survivalFlag = false;
    set.mapName = "NULL";
    set.position = VGet(0.0f, 0.0f, 0.0f);
    set.angle = 0;
    set.status.level = 1;
    set.status.exp = 0;
    set.status.attackPower = 0;
    set.status.maxHp = 0;
    set.status.hp = 0;
    set.status.defense = 0;
    set.status.speed = 0;
    set.status.size = 0;
    set.templateData.name = "NULL";
    set.templateData.typeName = "NULL";

    return set;
}

/*
* @fn GetData_CharacterFileDatas
* @drief キャラクター用　ファイル内全キャラクター情報　取得
*/
std::vector<CHARACTER_DATA> DataManager::GetData_CharacterFileDatas(std::string fileName)
{
    std::vector<CHARACTER_DATA> characterDatas;
    characterDatas.clear();

    // ファイルを開ける
    std::ifstream getFileData;
    getFileData.open(fileName, std::ios_base::in);

    // ファイルオープン失敗フラグ有効化
    mbFailureFlag = true;

    if (getFileData.is_open())
    {
        // ファイル確認
        std::string fileTypeName;
        getFileData >> fileTypeName;
        if (fileTypeName == NOT_PLAYER_CHARACTER_FILE_NAME)
        {
            // ファイル情報読み取り
            int dataNumber = 0;
            getFileData >> dataNumber;
            for (int i = 0; i < dataNumber; i++)
            {
                // 一時保存用
                CHARACTER_DATA setData;

                // 読み取り処理
                setData = GetFile_CharacterFileData(&getFileData);

                // 取得したデータを保存する
                characterDatas.push_back(setData);
            }
        }

        // ファイルオープン失敗フラグ無効化
        mbFailureFlag = false;
    }
    else {
        int TEST = 0;
    }

    // ファイル閉じる
    getFileData.close();


    return characterDatas;
}

/*
* @fn AddCharacterFile
* @drief キャラクター用ファイル追加
*/
void DataManager::AddCharacterFile(std::string fileName, CHARACTER_DATA characterData)
{
    // 必要情報
    bool fileFlag = false;

    //-- 書き込み前情報取得 --//
    // ファイルを開ける
    std::ifstream getFileData;
    getFileData.open(fileName, std::ios_base::in);

    if (getFileData.is_open())
    {
        fileFlag = true;
    }

    // ファイル閉じる
    getFileData.close();
    //--                    --//
    

    //-- 書き込み開始 --//
    if (!fileFlag)
    {
        std::ofstream setFileData;
        setFileData.open(fileName, std::ios_base::out);

        // ファイルオープン失敗フラグ有効化
        mbFailureFlag = true;

        if (setFileData.is_open())
        {
            // 書き込み
            setFileData << NOT_PLAYER_CHARACTER_FILE_NAME;
            setFileData << '\n';
            setFileData << 1;
            
            // 書き込み処理
            SetFile_CharacterFileData(&setFileData, characterData);
            

            // ファイルオープン失敗フラグ無効化
            mbFailureFlag = false;
        }
        else {
            int TEST = 0;
        }

        // ファイル閉じる
        setFileData.close();
    }
    //--              --//
}

/*
* @fn AddCharacterFileData
* @drief キャラクター用ファイル情報追加
*/
void DataManager::AddFile_CharacterFileData(std::string fileName, CHARACTER_DATA characterData)
{
    // 必要情報
    std::vector<CHARACTER_DATA> allFileData;
    allFileData.clear();
    std::string fileTypeName;
    int dataNumber = 0;
    bool notCharacterFlag = false;

    //-- 書き込み前情報取得 --//
    // ファイルを開ける
    std::ifstream getFileData;
    getFileData.open(fileName, std::ios_base::in);

    // ファイルオープン失敗フラグ有効化
    mbFailureFlag = true;

    if (getFileData.is_open())
    {
        // ファイル確認
        getFileData >> fileTypeName;
        if (fileTypeName == NOT_PLAYER_CHARACTER_FILE_NAME)
        {
            // ファイル情報読み取り
            getFileData >> dataNumber;
            for (int i = 0; i < dataNumber; i++)
            {
                // 一時保存用
                CHARACTER_DATA setData;

                // 読み取り処理
                setData = GetFile_CharacterFileData(&getFileData);

                // 取得したデータを保存する
                allFileData.push_back(setData);
            }
        }
        else {
            notCharacterFlag = true;
        }

        // ファイルオープン失敗フラグ無効化
        mbFailureFlag = false;
    }
    else {
        int TEST = 0;
    }

    // ファイル閉じる
    getFileData.close();
    //--                    --//


    //-- 書き込み開始 --//
    if (!notCharacterFlag)
    {
        // ファイルを開ける
        std::ofstream setFileData;
        setFileData.open(fileName, std::ios_base::out);

        // ファイルオープン失敗フラグ有効化
        mbFailureFlag = true;

        if (setFileData.is_open())
        {
            // 書き込み
            setFileData << fileTypeName;
            setFileData << '\n';
            setFileData << (dataNumber + 1);
            for (int i = 0; i < dataNumber; i++) {
                // 書き込み処理
                SetFile_CharacterFileData(&setFileData, allFileData[i]);
            }

            // 追加キャラクター
            SetFile_CharacterFileData(&setFileData, characterData);

            // ファイルオープン失敗フラグ無効化
            mbFailureFlag = false;
        }
        else {
            int TEST = 0;
        }

        // ファイル閉じる
        setFileData.close();
    }
    //--              --//
}

/*
* @fn DeleteCharacterFileData
* @drief キャラクター用ファイル情報削除
*/
void DataManager::DeleteFile_CharacterFileData(std::string fileName, std::string characterName)
{
    // 必要情報
    std::vector<CHARACTER_DATA> allFileData;
    allFileData.clear();
    std::string fileTypeName;
    int dataNumber = 0;
    bool notCharacterFlag = false;
    int deleteCharacterNumber = -1;

    //-- 書き込み前情報取得 --//
    // ファイルを開ける
    std::ifstream getFileData;
    getFileData.open(fileName, std::ios_base::in);

    // ファイルオープン失敗フラグ有効化
    mbFailureFlag = true;

    if (getFileData.is_open())
    {
        // ファイル確認
        getFileData >> fileTypeName;
        if (fileTypeName == NOT_PLAYER_CHARACTER_FILE_NAME)
        {
            // ファイル情報読み取り
            getFileData >> dataNumber;
            for (int i = 0; i < dataNumber; i++)
            {
                // 一時保存用
                CHARACTER_DATA setData;

                // 読み取り処理
                setData = GetFile_CharacterFileData(&getFileData);

                // 指定されたキャラクターなら何処に居たか記録する
                if (setData.templateData.name == characterName) {
                    deleteCharacterNumber = i;
                }

                // 取得したデータを保存する
                allFileData.push_back(setData);
            }
        }
        else {
            notCharacterFlag = true;
        }

        // ファイルオープン失敗フラグ無効化
        mbFailureFlag = false;
    }
    else {
        int TEST = 0;
    }

    // ファイル閉じる
    getFileData.close();
    //--                    --//


    //-- 書き込み開始 --//
    // ファイルを開ける
    if (!notCharacterFlag && deleteCharacterNumber != -1)
    {
        std::ofstream setFileData;
        setFileData.open(fileName, std::ios_base::out);

        // ファイルオープン失敗フラグ有効化
        mbFailureFlag = true;

        if (setFileData.is_open())
        {
            // 書き込み
            setFileData << fileTypeName;
            setFileData << '\n';
            setFileData << (dataNumber - 1);
            for (int i = 0; i < dataNumber; i++) {
                // 書き込み処理
                if (deleteCharacterNumber != i) {
                    SetFile_CharacterFileData(&setFileData, allFileData[i]);
                }
            }

            // ファイルオープン失敗フラグ無効化
            mbFailureFlag = false;
        }
        else {
            int TEST = 0;
        }

        // ファイル閉じる
        setFileData.close();
    }
    //--              --//
}

/*
* @fn ChangeCharacterFileData
* @drief キャラクター用ファイル内容一部変更
*/
void DataManager::ChangeFile_CharacterFileData(std::string fileName, std::string characterName, CHARACTER_DATA characterData)
{
    // 必要情報
    std::vector<CHARACTER_DATA> allFileData;
    allFileData.clear();
    std::string fileTypeName;
    int dataNumber = 0;
    bool notCharacterFlag = false;
    int changeCharacterNumber = -1;

    //-- 書き込み前情報取得 --//
    // ファイルを開ける
    std::ifstream getFileData;
    getFileData.open(fileName, std::ios_base::in);

    // ファイルオープン失敗フラグ有効化
    mbFailureFlag = true;

    if (getFileData.is_open())
    {
        // ファイル確認
        getFileData >> fileTypeName;
        if (fileTypeName == NOT_PLAYER_CHARACTER_FILE_NAME)
        {
            // ファイル情報読み取り
            getFileData >> dataNumber;
            for (int i = 0; i < dataNumber; i++)
            {
                // 一時保存用
                CHARACTER_DATA setData;

                // 読み取り処理
                setData = GetFile_CharacterFileData(&getFileData);

                // 指定されたキャラクターなら何処に居たか記録する
                if (setData.templateData.name == characterName) {
                    changeCharacterNumber = i;
                }

                // 取得したデータを保存する
                allFileData.push_back(setData);
            }
        }
        else {
            notCharacterFlag = true;
        }

        // ファイルオープン失敗フラグ無効化
        mbFailureFlag = false;
    }
    else {
        int TEST = 0;
    }

    // ファイル閉じる
    getFileData.close();
    //--                    --//


    //-- 書き込み開始 --//
    if (!notCharacterFlag)
    {
        // ファイルを開ける
        std::ofstream setFileData;
        setFileData.open(fileName, std::ios_base::out);

        // ファイルオープン失敗フラグ有効化
        mbFailureFlag = true;

        if (setFileData.is_open())
        {
            // 書き込み
            setFileData << fileTypeName;
            setFileData << '\n';
            setFileData << dataNumber;
            for (int i = 0; i < dataNumber; i++) {
                // 書き込み処理
                if (changeCharacterNumber != i) {
                    SetFile_CharacterFileData(&setFileData, allFileData[i]);
                }
                else {
                    // 指定された場所に新しいキャラクター情報を入れる
                    SetFile_CharacterFileData(&setFileData, characterData);
                }
            }

            // ファイルオープン失敗フラグ無効化
            mbFailureFlag = false;
        }
        else {
            int TEST = 0;
        }

        // ファイル閉じる
        setFileData.close();
    }
    //--              --//
}

/*
* @fn GetCharacterNameStr
* @drief キャラクタータイプ文字列変換
*/
std::string DataManager::GetCharacterNameStr(CHARACTER_TYPE characterType)
{
    switch (characterType)
    {
    case CHARACTER_TYPE::ROBOT_PLAYER:
        return "RobotPlayer";

    case CHARACTER_TYPE::MAP_CHARACTER_1:
        return "MapCharacter1";

    case CHARACTER_TYPE::MAP_WEAK_ENEMY_1:
        return "MapWeakEnemy1";
    
    case CHARACTER_TYPE::MAP_BOSS_ENEMY_1:
        return "MapBossEnemy1";
    
    case CHARACTER_TYPE::BATTLE_WEAK_ENEMY_1:
        return "BattleWeakEnemy1";
    
    case CHARACTER_TYPE::BATTLE_BOSS_ENEMY_1:
        return "BattleBossEnemy1";

    case CHARACTER_TYPE::TYPE_NULL:
        return "TYPE_NULL";
    }


    return "NULL";
}

/*
* @fn GetCharacterNameEnumClass
* @drief キャラクタータイプenum変換
*/
CHARACTER_TYPE DataManager::GetCharacterNameEnumClass(std::string characterType)
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
* @fn GetData_MapFile
* @drief マップファイルを取得
*/
std::vector<MAP_DATA> DataManager::GetData_MapFile(std::string fileName)
{
    std::vector<MAP_DATA> mapData;
    std::string fileTypeName;
    int dataNumber = 0;

    // ファイルを開ける
    std::ifstream getFileData;
    getFileData.open(fileName, std::ios_base::in);

    // ファイルオープン失敗フラグ有効化
    mbFailureFlag = true;

    if (getFileData.is_open())
    {
        // ファイル確認
        getFileData >> fileTypeName;
        if (fileTypeName == MAP_FILE_NAME) {
            getFileData >> dataNumber;
            for (int i = 0; i < dataNumber; i++) {
                MAP_DATA setData;
                getFileData >> setData.templateData.typeName;
                getFileData >> setData.templateData.name;
                getFileData >> setData.typeNameTypeNumber;
                for (int j = 0; j < setData.typeNameTypeNumber; j++) {
                    std::string setTypeName;
                    int typeNumber;
                    getFileData >> setTypeName;
                    getFileData >> typeNumber;

                    setData.typeName.push_back(setTypeName);
                    setData.typeNumber.push_back(typeNumber);
                }

                mapData.push_back(setData);
            }
        }

        // ファイルオープン失敗フラグ無効化
        mbFailureFlag = false;
    }
    else {
        int TEST = 0;
    }

    // ファイル閉じる
    getFileData.close();


    return mapData;
}

/*
* @fn SetLevelDataSSS
* @drief レベル情報取得
*/
void DataManager::SetLevelData(std::string fileName)
{
    std::string fileTypeName;

    // ファイルを開ける
    std::ifstream getFileData;
    getFileData.open(fileName, std::ios_base::in);

    // ファイルオープン失敗フラグ有効化
    mbFailureFlag = true;

    if (getFileData.is_open())
    {
        // ファイル確認
        getFileData >> fileTypeName;
        if (fileTypeName == LEVEL_FILE_NAME) {
            getFileData >> mslevelData.maxLevelNumber;
            for (int i = 0; i < mslevelData.maxLevelNumber; i++) {

                int setLevelNumber = 0;
                int setExpNumber = 0;
                getFileData >> setLevelNumber;
                getFileData >> setExpNumber;

                mslevelData.levelNumber.push_back(setLevelNumber);
                mslevelData.levelUpExpNumber.push_back(setExpNumber);
            }
        }

        // ファイルオープン失敗フラグ無効化
        mbFailureFlag = false;
    }
    else {
        int TEST = 0;
    }

    // ファイル閉じる
    getFileData.close();
}

/*
* @fn GetCharacterNameMaxNumber
* @drief キャラクタータイプ最大数
*/
int DataManager::GetCharacterNameMaxNumber()
{
    int number = 0;

    // テスト
    number += 1;

    return number;
}

/*
* @fn GetCharacterName_Number
* @drief キャラクタータイプ名取得
*/
std::string DataManager::GetCharacterName_Number(int number)
{
    switch (number)
    {
    case 0:
        return "RobotPlayer";
        break;
    }

    return "NULL";
}

/*
* @fn SetFileData
* @drief データ設定
*/
void DataManager::SetTestFileData(const char *fileName)
{
    // 必要情報
    std::vector<CHARACTER_DATA> allFileData;
    allFileData.clear();
    std::string fileTypeName;
    int dataNumber = 0;
    bool notCharacterFlag = false;

    //-- 書き込み前情報取得 --//
    // ファイルを開ける
    std::ifstream getFileData;
    getFileData.open(fileName, std::ios_base::in);

    // ファイルオープン失敗フラグ有効化
    mbFailureFlag = true;

    if (getFileData.is_open()) 
    {
        // ファイル確認
        getFileData >> fileTypeName;
        if (fileTypeName == NOT_PLAYER_CHARACTER_FILE_NAME)
        {
            // ファイル情報読み取り
            getFileData >> dataNumber;
            for (int i = 0; i < dataNumber; i++) 
            {
                // 一時保存用
                CHARACTER_DATA setData;

                // 読み取り処理
                setData = GetFile_CharacterFileData(&getFileData);

                // 取得したデータを保存する
                allFileData.push_back(setData);
            }
        }
        else {
            notCharacterFlag = true;
        }

        // ファイルオープン失敗フラグ無効化
        mbFailureFlag = false;
    }
    else {
        int TEST = 0;
    }

    // ファイル閉じる
    getFileData.close();
    //--                    --//


    //-- 書き込み開始 --//
    if (!notCharacterFlag)
    {
        // ファイルを開ける
        std::ofstream setFileData;
        setFileData.open(fileName, std::ios_base::out);

        // ファイルオープン失敗フラグ有効化
        mbFailureFlag = true;

        if (setFileData.is_open())
        {
            // 書き込み
            setFileData << fileTypeName;
            setFileData << '\n';
            setFileData << dataNumber;
            for (int i = 0; i < dataNumber; i++) {
                // 書き込み処理
                SetFile_CharacterFileData(&setFileData, allFileData[i]);
            }

            // ファイルオープン失敗フラグ無効化
            mbFailureFlag = false;
        }
        else {
            int TEST = 0;
        }

        // ファイル閉じる
        setFileData.close();
    }
    //--              --//
}
/*
    std::ifstream playerData;
    playerData.open("GameData/Player_Data.txt");

    if (playerData.is_open())
    {
        std::string data;
        float datain;
        std::string test1;
        playerData >> data;
        //playerData.seekg(3, std::ios::beg);
        playerData >> datain;
        playerData.clear();
        //playerData.seekg(2, std::ios::beg);
        playerData >> test1;
        //if (test1 == "Player") {
            std::cout << data << "\n" << datain << "\n" << test1 << "\n" << playerData.tellg() << playerData.eof();
        //}
    }

    playerData.close();
    *//*
    std::ofstream Enemy;

    Enemy.open("GameData/Enemy_Data.txt");

    if (Enemy.is_open()) {
        Enemy << "Enemy_Data\n213";
        Enemy << 12 << '\n';
        int neko = 3;
        float tamesi = 10.01f;
        std::string yahho = "iiiie";

        //Enemy << neko << tamesi << yahho;

        std::cout << "●";
    }

    Enemy.close();
    */