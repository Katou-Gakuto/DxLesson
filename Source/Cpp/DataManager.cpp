#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <map>

#include "../Header/DataManager.h"

#include "../Header/DataManagerMacro.h"

#include "../Header/ItemRecoveryMedicine.h"


// コンストラクタ
DataManager::DataManager(std::string startFileName)
: mnPlayPlayerDataNumber(-1)
{
	mbFailureFlag = false;

	mstBaseData = OnePlayerAllData();
	mstBaseData.dataFlag = false;
	mstBaseData.playerData.dataFlag = false;
	mstBaseData.playerData.item.clear();
	mstBaseData.oneDatas.clear();

	mstInitPlayerDatas.clear();

	mstPlayPlayerData = OnePlayerAllData();
	mstPlayPlayerData.dataFlag = false;
	mstPlayPlayerData.playerData.dataFlag = false;
	mstPlayPlayerData.playerData.item.clear();
	mstPlayPlayerData.oneDatas.clear();

	mstPlayerDatas.clear();
	mstrPlayerDatasFileName.clear();

	mmGetFilePosNumbers.clear();

	msDeleteItemName.clear();

	Init(startFileName);
}

// デストラクタ
DataManager::~DataManager()
{
	mstPlayerDatas.clear();

	for (int i = 0; i < mstPlayPlayerData.playerData.item.size(); i++)
	{
		delete mstPlayPlayerData.playerData.item[i];
	}
}


// 初期化
void DataManager::Init(std::string startFileName)
{

	// ベースデータを取得する
	{
		OneData setData;
		setData.dataChangeFlag = false;
		setData.fileNameAndType.name = startFileName;
		setData.fileNameAndType.typeNumber = 0;
		mstBaseData.dataFlag = false;
		mstBaseData.oneDatas.clear();

		// ファイルを開ける
		std::ifstream baseNameDataFile;
		baseNameDataFile.open(startFileName, std::ios_base::in);

		if (baseNameDataFile.is_open())
		{
			// ファイル確認
			baseNameDataFile >> setData.fileNameAndType.typeNumber;
			if (setData.fileNameAndType.typeNumber == (int)DataType::FILE_NAME)
			{
				setData = GetOneFileData(setData.fileNameAndType, &baseNameDataFile);
			}
		}
		else {
			mbFailureFlag = true;
			return;
		}

		baseNameDataFile.close();
		mstBaseData.oneDatas.push_back(setData);
		setData.fileNameAndType.name.clear();
		setData.fileNameAndType.typeNumber = -1;

		// ファイル名に保存されているファイルをすべて取得する
		for (int i = 0; i < mstBaseData.oneDatas[0].datas.fileNameDatas.size(); i++)
		{
			setData.fileNameAndType.name = mstBaseData.oneDatas[0].datas.fileNameDatas[i].fileName;

			// ファイルを開ける
			std::ifstream baseDataFile;
			baseDataFile.open(setData.fileNameAndType.name, std::ios_base::in);

			if (baseDataFile.is_open())
			{
				baseDataFile >> setData.fileNameAndType.typeNumber;
				switch ((DataType)setData.fileNameAndType.typeNumber)
				{
				case DataType::PLAYER:
				{
					mstrPlayerDatasFileName = setData.fileNameAndType.name;
					int playerNumber;
					baseDataFile >> playerNumber;
					mstPlayerDatas.reserve(playerNumber);
					for (int i = 0; i < playerNumber; i++)
					{
						mstPlayerDatas.push_back(GetPlayerFileData(&baseDataFile));
					}
				}
						break;

				case DataType::INIT_PLAYER:
				{
					int playerNumber;
					baseDataFile >> playerNumber;
					mstInitPlayerDatas.reserve(playerNumber);
					for (int i = 0; i < playerNumber; i++)
					{
						mstInitPlayerDatas.push_back(GetPlayerFileData(&baseDataFile));
					}
				}
				break;

				default:
						setData = GetOneFileData(setData.fileNameAndType, &baseDataFile);
						mstBaseData.oneDatas.push_back(setData);
						break;
				}
			}
			else
			{
				mbFailureFlag = true;
				return;
			}

			baseDataFile.close();
			setData.fileNameAndType.name.clear();
			setData.fileNameAndType.typeNumber = -1;
		}

		mstBaseData.dataFlag = true;
	}
}

// データを保存
void DataManager::Save()
{
	if (mnPlayPlayerDataNumber != -1)
	{
		if (mstPlayPlayerData.dataFlag)
		{
			mstPlayerDatas[mnPlayPlayerDataNumber] = mstPlayPlayerData.playerData;

			// プレイヤー全データをファイルに書き込み	
			// ファイルを開ける
			std::ofstream setPlayerFileData;
			setPlayerFileData.open(mstrPlayerDatasFileName, std::ios_base::out);

			if (setPlayerFileData.is_open())
			{
				// 書き込み
				setPlayerFileData <<  (int)DataType::PLAYER;
				setPlayerFileData << '\n';
				setPlayerFileData << mstPlayerDatas.size();
				for (int i = 0; i < mstPlayerDatas.size(); i++) {
					// 書き込み処理
					SetPlayerFileData(mstPlayerDatas[i], &setPlayerFileData);
				}
			}
			else
			{
				mbFailureFlag = true;
				return;
			}

			// ファイル閉じる
			setPlayerFileData.close();


			// 変更したデータをファイルに入れる
			for (OneData oneData : mstPlayPlayerData.oneDatas)
			{
				if (oneData.dataChangeFlag)
				{
					// ファイルを開ける
					std::ofstream setPlayerFileData;
					setPlayerFileData.open(oneData.fileNameAndType.name, std::ios_base::out);

					if (setPlayerFileData.is_open())
					{
							SetOneFileData(oneData, &setPlayerFileData);
					}
					else
					{
						mbFailureFlag = true;
						return;
					}

					setPlayerFileData.close();
				}
			}
		}
	}
}

// プレイヤーデータ設定
void DataManager::ChangePlayerData(PLAYER_DATA data, int playerNumber)
{
	if (mstPlayerDatas.size() > playerNumber)
	{
		mstPlayerDatas[playerNumber] = data;
	}
}

// プレイヤー設定
void DataManager::SetPlayPlayer(int playerNumber)
{
	if (mstPlayerDatas.size() > playerNumber)
	{
		if (mstPlayerDatas[playerNumber].characterData.survivalFlag)
		{
			// プレイヤーデータ初期化
			{
				for (int i = 0; i < mstPlayPlayerData.playerData.item.size(); i++)
				{
					delete mstPlayPlayerData.playerData.item[i];
				}

				mstPlayPlayerData.playerData.item.clear();

				mmGetFilePosNumbers.clear();

				mnPlayPlayerDataNumber = playerNumber;
				mstPlayPlayerData.dataFlag = false;
				mstPlayPlayerData.playerData = mstPlayerDatas[playerNumber];
				mstPlayPlayerData.oneDatas.clear();

				for (int i = 0; i < mstPlayPlayerData.playerData.itemNumber; i++) {

					Item_Base* itemBase;
					ITEM_DATA checkItemData = mstPlayPlayerData.playerData.itemData[i];

					switch ((ItemType)checkItemData.templateData.typeNumber)
					{
					case ItemType::RECOVERY_MEDICIN_SMALL:
						itemBase = new ItemRecoveryMedicine(checkItemData, 30);
						break;
						
					case ItemType::RECOVERY_MEDICIN_MEDIUM:
						itemBase = new ItemRecoveryMedicine(checkItemData, 100);
						break;
						
					case ItemType::RECOVERY_MEDICIN_LARGE:
						itemBase = new ItemRecoveryMedicine(checkItemData, 500);
						break;
					}

					mstPlayPlayerData.playerData.item.push_back(itemBase);
				}
			}

			// データ設定用初期化
			OneData setData;
			setData.dataChangeFlag = false;
			setData.fileNameAndType.name = mstPlayPlayerData.playerData.playerFolderName + "/FileNames_Data.txt";
			setData.fileNameAndType.typeNumber = -1;

			// ファイルを開ける
			std::ifstream nameDataFile;
			nameDataFile.open(setData.fileNameAndType.name, std::ios_base::in);

			// ファイルデータ取得
			if (nameDataFile.is_open())
			{
				// ファイル確認
				nameDataFile >> setData.fileNameAndType.typeNumber;
				if (setData.fileNameAndType.typeNumber == (int)DataType::FILE_NAME)
				{
					setData = GetOneFileData(setData.fileNameAndType, &nameDataFile);
				}
			}
			else
			{
				mbFailureFlag = true;
				return;
			}

			nameDataFile.close();
			mstPlayPlayerData.oneDatas.push_back(setData);
			setData.fileNameAndType.name.clear();
			setData.fileNameAndType.typeNumber = -1;


			// ファイル名に保存されているファイルをすべて取得する
			for (DATA_NAME fileNameData : mstPlayPlayerData.oneDatas[0].datas.fileNameDatas)
			{
				setData.fileNameAndType.name = fileNameData.fileName;

				// ファイルを開ける
				std::ifstream dataFile;
				dataFile.open(setData.fileNameAndType.name, std::ios_base::in);

				if (dataFile.is_open())
				{
					dataFile >> setData.fileNameAndType.typeNumber;
					if (setData.fileNameAndType.typeNumber == (int)DataType::PLAYER ||
						setData.fileNameAndType.typeNumber == (int)DataType::INIT_PLAYER)
					{
						return;
					}
					else
					{
						setData = GetOneFileData(setData.fileNameAndType, &dataFile);
						mstPlayPlayerData.oneDatas.push_back(setData);
					}
				}
				else
				{
					mbFailureFlag = true;
					return;
				}

				dataFile.close();
				setData.fileNameAndType.name.clear();
				setData.fileNameAndType.typeNumber = -1;
			}


		}

		mstPlayPlayerData.dataFlag = true;
	}
}

// プレイプレイヤーデータを取得
PLAYER_DATA DataManager::GetPlayPlayerData()
{
	return mstPlayPlayerData.playerData;
}

// プレイプレイヤーデータ設定
void DataManager::SetPlayPlayerData(PLAYER_DATA data)
{
	mstPlayPlayerData.playerData = data;
}

// プレイ中に設定されたデータを削除する
void DataManager::PlayDataDelete(int playerNumber)
{
	if (playerNumber >= mstPlayerDatas.size())
	{
		return;
	}
	SetPlayPlayer(playerNumber);

	/*
	* 【ファイル名データに載っているファイルを全削除】
	*/
	if (mstPlayPlayerData.oneDatas[0].fileNameAndType.typeNumber == (int)DataType::FILE_NAME)
	{
		for (int i = 0; i < mstPlayPlayerData.oneDatas[0].datas.fileNameDatas.size(); i++)
		{
			if (std::remove(mstPlayPlayerData.oneDatas[0].datas.fileNameDatas[i].fileName.c_str()) == 0)
			{

				for (int j = 0; j < mstPlayPlayerData.oneDatas.size(); j++)
				{
					if (mstPlayPlayerData.oneDatas[j].fileNameAndType.name == mstPlayPlayerData.oneDatas[0].datas.fileNameDatas[i].fileName)
					{
						// vectorから削除
						mstPlayPlayerData.oneDatas.erase(mstPlayPlayerData.oneDatas.begin() + j);
						break;
					}
				}
			}
		}
	}

	mstPlayPlayerData.playerData.dataFlag = false;

	/*
	* 【プレイヤーデータクリアした後にセーブする】
	*/
	Save();
}

// 一種類分データを取得
OneData DataManager::GetOneData(std::string fileName, int fileType, bool baseFlag)
{
	if (baseFlag)
	{
		for (int i = 0; i < mstBaseData.oneDatas.size(); i++)
		{
			if ((mstBaseData.oneDatas[i].fileNameAndType.name == fileName) &&
				(mstBaseData.oneDatas[i].fileNameAndType.typeNumber == fileType))
			{
				return mstBaseData.oneDatas[i];
			}
		}
	}
	else
	{
		for (int i = 0; i < mstPlayPlayerData.oneDatas.size(); i++)
		{
			if ((mstPlayPlayerData.oneDatas[i].fileNameAndType.name == fileName) &&
				(mstPlayPlayerData.oneDatas[i].fileNameAndType.typeNumber == fileType))
			{
				return mstPlayPlayerData.oneDatas[i];
			}
		}
	}

	OneData nullData;
	nullData.dataChangeFlag = false;
	nullData.fileNameAndType.name.clear();
	nullData.fileNameAndType.typeNumber = -1;

	nullData.datas.levelData.characterType = -1;
	nullData.datas.levelData.levelNumber.clear();
	nullData.datas.levelData.levelUpExpNumber.clear();
	nullData.datas.levelData.maxLevelNumber = -1;

	return nullData;
}

// 指定のシーンに必要な全データを取得
std::vector<OneData> DataManager::GetSceneData(SCENE sceneName)
{
	// 以前見つけたファイルなら見つけたファイルをプレイ中のデータから取り出す
	if (mmGetFilePosNumbers.find(sceneName) != mmGetFilePosNumbers.end())
	{
		std::vector<OneData> resultData;
		resultData.clear();

		std::list<int> setData = mmGetFilePosNumbers[sceneName];

		resultData.reserve(setData.size() - 1);
		for (int checkNumber : setData)
		{
			resultData.push_back(mstPlayPlayerData.oneDatas[checkNumber]);
		}

		return resultData;
	}

	std::list <std::string> baseFileNames;

	// ベースファイルにいくつこのシーンの情報があるかを調べる
	for (int i = 0; i < mstBaseData.oneDatas.size(); i++)
	{
		if (mstBaseData.oneDatas[i].fileNameAndType.typeNumber == (int)DataType::FILE_NAME)
		{
			for (int j = 0; j < mstBaseData.oneDatas[i].datas.fileNameDatas.size(); j++)
			{
				if (mstBaseData.oneDatas[i].datas.fileNameDatas[j].sceneType == sceneName)
				{
					baseFileNames.push_back(mstBaseData.oneDatas[i].datas.fileNameDatas[j].fileName);
				}
			}
		}
	}

	// 必要なデータを返す
	{
		// 返すデータ
		std::vector<OneData> resultData;
		resultData.clear();
		resultData.reserve(baseFileNames.size() - 1);

		// デート場所記録用
		std::list<int> setGetFilePosNumbers;
		setGetFilePosNumbers.clear();

		// プレイ中データの何処にファイルネームデータあるかを取得する
		std::list<int> fileNameDataPos;
		fileNameDataPos.clear();
		for (int i = 0; i < mstPlayPlayerData.oneDatas.size(); i++)
		{
			if (mstPlayPlayerData.oneDatas[i].fileNameAndType.typeNumber == (int)DataType::FILE_NAME)
			{
				fileNameDataPos.push_back(i);
			}
		}

		for (std::string baseFileName : baseFileNames)
		{
			// プレイ中データにあるか探す
			bool checkFile = false;
			std::string checkName = baseFileName;
			for (int namePos : fileNameDataPos)
			{
				for (int i = 0; i < mstPlayPlayerData.oneDatas[namePos].datas.fileNameDatas.size(); i++)
				{
					if (mstPlayPlayerData.oneDatas[namePos].datas.fileNameDatas[i].fileName.substr(18) == baseFileName.substr(9))
					{
						checkFile = true;
						for (int j = 0; j < mstPlayPlayerData.oneDatas.size(); j++)
						{
							if (mstPlayPlayerData.oneDatas[j].fileNameAndType.name == mstPlayPlayerData.oneDatas[namePos].datas.fileNameDatas[i].fileName)
							{
								resultData.push_back(mstPlayPlayerData.oneDatas[j]);
								setGetFilePosNumbers.push_back(j);
								break;
							}
						}
						break;
					}
				}
				if (checkFile)
				{
					break;
				}
			}

			// プレイ中データにない場合ベースデータから取得する
			if (!checkFile)
			{
				for (int i = 0; i < mstBaseData.oneDatas.size(); i++)
				{
					if (mstBaseData.oneDatas[i].fileNameAndType.name == baseFileName)
					{
						// プレイヤーデータに情報を追加
						OneData setData = mstBaseData.oneDatas[i];
						setData.dataChangeFlag = true;
						setData.fileNameAndType.name = (mstPlayPlayerData.playerData.playerFolderName + "/" + setData.fileNameAndType.name.substr(9));
						mstPlayPlayerData.oneDatas.push_back(setData);
						setGetFilePosNumbers.push_back(mstPlayPlayerData.oneDatas.size() - 1);
						
						// リザルトに情報追加
						resultData.push_back(setData);
						

						// ファイル名データに情報追加
						DATA_NAME setFileName;
						setFileName.sceneType = sceneName;
						setFileName.fileName = setData.fileNameAndType.name;
						setFileName.fileTypeName = setData.fileNameAndType.typeNumber;
						mstPlayPlayerData.oneDatas[0].datas.fileNameDatas.push_back(setFileName);
						break;
					}
				}
			}
		}

		mmGetFilePosNumbers[sceneName] = setGetFilePosNumbers;
		return resultData;
	}
}

// 全データを取得
std::vector<OneData> DataManager::GetAllData(bool baseFlag)
{
	return (baseFlag ? mstBaseData.oneDatas : mstPlayPlayerData.oneDatas);
}

// 一種類分データを変更
void DataManager::ChangeOneData(OneData data, std::string fileName, int fileType)
{
	if (mstPlayPlayerData.dataFlag)
	{
		for (int i = 0; i < mstPlayPlayerData.oneDatas.size(); i++)
		{
			if ((mstPlayPlayerData.oneDatas[i].fileNameAndType.name == fileName) &&
				(mstPlayPlayerData.oneDatas[i].fileNameAndType.typeNumber == fileType))
			{
				mstPlayPlayerData.oneDatas[i].dataChangeFlag = data.dataChangeFlag;

				switch ((DataType)fileType)
				{
				case DataType::FILE_NAME:
					mstPlayPlayerData.oneDatas[i].datas.fileNameDatas = data.datas.fileNameDatas;
					break;
					
				case DataType::CHARACTER:
					mstPlayPlayerData.oneDatas[i].datas.characterDatas = data.datas.characterDatas;
					break;
					
				case DataType::LEVEL:
					mstPlayPlayerData.oneDatas[i].datas.levelData = data.datas.levelData;
					break;
				}
			}
		}
	}
}

// 全データを変更
void DataManager::ChangeAllData(std::vector<OneData> data)
{
	if (mstPlayPlayerData.dataFlag)
	{
		mstPlayPlayerData.oneDatas = data;
	}
}

// アイテム再設定
void DataManager::ReSetItem()
{
	for (int i = 0; i < mstPlayPlayerData.playerData.item.size(); i++)
	{
		delete mstPlayPlayerData.playerData.item[i];
	}

	mstPlayPlayerData.playerData.item.clear();

	for (int i = 0; i < mstPlayPlayerData.playerData.itemNumber; i++) {

		Item_Base* itemBase;
		ITEM_DATA checkItemData = mstPlayPlayerData.playerData.itemData[i];

		switch ((ItemType)checkItemData.templateData.typeNumber)
		{
		case ItemType::RECOVERY_MEDICIN_SMALL:
			itemBase = new ItemRecoveryMedicine(checkItemData, 30);
			break;

		case ItemType::RECOVERY_MEDICIN_MEDIUM:
			itemBase = new ItemRecoveryMedicine(checkItemData, 100);
			break;

		case ItemType::RECOVERY_MEDICIN_LARGE:
			itemBase = new ItemRecoveryMedicine(checkItemData, 500);
			break;
		}

		mstPlayPlayerData.playerData.item.push_back(itemBase);
	}
}

// 削除アイテム設定
void DataManager::SetDeleteItem(std::string name)
{
	for (int i = 0; i < mstPlayPlayerData.playerData.itemData.size(); i++)
	{
		if (name == mstPlayPlayerData.playerData.itemData[i].templateData.name)
		{
			mstPlayPlayerData.playerData.itemData.erase(mstPlayPlayerData.playerData.itemData.begin() + i);
		}
	}

	msDeleteItemName.push_back(name);
}

// 削除する必要があるアイテムを削除する
void DataManager::DeleteItemIfNeeded()
{
	for (auto it = msDeleteItemName.begin(); it != msDeleteItemName.end(); ++it)
	{
		for (int i = 0; i < mstPlayPlayerData.playerData.item.size(); i++)
		{
			if ((*it) == mstPlayPlayerData.playerData.item[i]->GetItemName())
			{
				delete mstPlayPlayerData.playerData.item[i];
				mstPlayPlayerData.playerData.item.erase(mstPlayPlayerData.playerData.item.begin() + i);
				break;
			}
		}
	}

	msDeleteItemName.clear();
}

// 渡されたデータから指定のキャラクタータイプのレベルデータを取得する
LEVEL_DATA DataManager::GetLevelData(std::vector<OneData> data, int characterType)
{
	for (OneData oneData : data)
	{
		if (oneData.fileNameAndType.typeNumber == (int)DataType::LEVEL)
		{
			if (oneData.datas.levelData.characterType == characterType)
			{
				return oneData.datas.levelData;
			}
		}
	}

	LEVEL_DATA nullData;
	nullData.characterType = -1;
	nullData.levelNumber.clear();
	nullData.levelUpExpNumber.clear();
	nullData.maxLevelNumber = -1;
	return nullData;
}

// ファイルデータ読み込み用(OneData)
OneData DataManager::GetOneFileData(DATA_STRUCT fileName, std::ifstream* file)
{
	OneData resultData = OneData();
	resultData.fileNameAndType = fileName;

	switch ((DataType)resultData.fileNameAndType.typeNumber)
	{
	case DataType::LEVEL:
	{
		LEVEL_DATA levelData;
		*file >> levelData.characterType;
		*file >> levelData.maxLevelNumber;

		levelData.levelNumber.reserve(levelData.maxLevelNumber);
		levelData.levelUpExpNumber.reserve(levelData.maxLevelNumber);

		for (int i = 0; i < levelData.maxLevelNumber; i++)
		{
			int setLevelNumber = 0;
			int setExpNumber = 0;
			*file >> setLevelNumber;
			*file >> setExpNumber;

			levelData.levelNumber.push_back(setLevelNumber);
			levelData.levelUpExpNumber.push_back(setExpNumber);
		}

		resultData.datas.levelData = levelData;
	}
		break;

	case DataType::CHARACTER:
	{
		int dataNumber;
		*file >> dataNumber;

		std::vector<CHARACTER_DATA> characterData;
		characterData.clear();
		characterData.reserve(dataNumber);

		for (int i = 0; i < dataNumber; i++)
		{
			CHARACTER_DATA setCharacterData;

			*file >> setCharacterData.templateData.typeNumber;    // キャラクタータイプ
			*file >> setCharacterData.templateData.name;    // キャラクターの名前
			*file >> setCharacterData.survivalFlag;    // キャラクターの生存フラグ
			*file >> setCharacterData.status.level;    // レベル
			*file >> setCharacterData.status.exp;  // 経験値
			*file >> setCharacterData.status.attackPower;  // 攻撃力
			*file >> setCharacterData.status.maxHp;    // 最大HP
			*file >> setCharacterData.status.hp;       // HP
			*file >> setCharacterData.status.defense;  // 防御力
			*file >> setCharacterData.status.speed;    // 速度
			*file >> setCharacterData.status.size; // 大きさ
			*file >> (int&)setCharacterData.mapType; // マップ名
			*file >> setCharacterData.position.x;  // 居る場所X軸
			*file >> setCharacterData.position.y;  // 居る場所Y軸
			*file >> setCharacterData.position.z;  // 居る場所Z軸
			*file >> setCharacterData.angle;   // 向いている方向

			characterData.push_back(setCharacterData);
		}
		resultData.datas.characterDatas = characterData;
	}
		break;

	case DataType::FILE_NAME:
	{
		// ファイル名情報読み取り
		int dataNumber;
		*file >> dataNumber;

		std::vector<DATA_NAME> fileNameData;
		fileNameData.clear();
		fileNameData.reserve(dataNumber);

		for (int i = 0; i < dataNumber; i++) {
			DATA_NAME setFileNameData;

			*file >> setFileNameData.fileName;
			*file >> setFileNameData.fileTypeName;

			//【必要シーンを取得】
			int sceneType;
			*file >> sceneType;
			setFileNameData.sceneType = (SCENE)sceneType;

			fileNameData.push_back(setFileNameData);
		}
		resultData.datas.fileNameDatas = fileNameData;
	}
		break;
	}

	return resultData;
}

// ファイルデータ書き込み用(OneData)
void DataManager::SetOneFileData(OneData setData, std::ofstream* file)
{
	switch ((DataType)setData.fileNameAndType.typeNumber)
	{
	case DataType::LEVEL:
		*file << setData.fileNameAndType.typeNumber;
		*file << "\n";
		*file << setData.datas.levelData.characterType;
		*file << "\n";
		*file << setData.datas.levelData.maxLevelNumber;
		*file << "\n";
		for (int  i = 0; i < setData.datas.levelData.maxLevelNumber; i++)
		{
			*file << setData.datas.levelData.levelNumber[i];
			*file << "\n";
			*file << setData.datas.levelData.levelUpExpNumber[i];
			*file << "\n";
		}
		break;

	case DataType::CHARACTER:
		*file << setData.fileNameAndType.typeNumber;
		*file << "\n";
		*file << setData.datas.characterDatas.size();
		for (CHARACTER_DATA setCharacterData : setData.datas.characterDatas)
		{
			*file << '\n';
			*file << setCharacterData.templateData.typeNumber;    // キャラクタータイプ
			*file << '\n';
			*file << setCharacterData.templateData.name;    // キャラクターの名前
			*file << '\n';
			*file << setCharacterData.survivalFlag;    // キャラクター生存フラグ
			*file << '\n';
			*file << setCharacterData.status.level;    // レベル
			*file << '\n';
			*file << setCharacterData.status.exp;  // 経験値
			*file << '\n';
			*file << setCharacterData.status.attackPower;  // 攻撃力
			*file << '\n';
			*file << setCharacterData.status.maxHp;    // 最大HP
			*file << '\n';
			*file << setCharacterData.status.hp;       // HP
			*file << '\n';
			*file << setCharacterData.status.defense;  // 防御力
			*file << '\n';
			*file << setCharacterData.status.speed;    // 速度
			*file << '\n';
			*file << setCharacterData.status.size; // 大きさ
			*file << '\n';
			*file << (int)setCharacterData.mapType; // マップ名
			*file << '\n';
			*file << setCharacterData.position.x;  // 居る場所X軸
			*file << '\n';
			*file << setCharacterData.position.y;  // 居る場所Y軸
			*file << '\n';
			*file << setCharacterData.position.z;  // 居る場所Z軸
			*file << '\n';
			*file << setCharacterData.angle;   // 見ている方向
		}
		break;

	case DataType::FILE_NAME:
		*file << setData.fileNameAndType.typeNumber;
		*file << "\n";
		*file << setData.datas.fileNameDatas.size();
		*file << "\n";
		for (int i = 0; i < setData.datas.fileNameDatas.size(); i++)
		{
			*file << setData.datas.fileNameDatas[i].fileName;
			*file << "\n";
			*file << setData.datas.fileNameDatas[i].fileTypeName;
			*file << "\n";
			/*
			* 【必要シーンを設定】
			*/
			*file << "シーン";// 仮
		}
		break;
	}
}

// ファイルデータ読み込み用(プレイヤー)
PLAYER_DATA DataManager::GetPlayerFileData(std::ifstream* file)
{
	PLAYER_DATA setPlayerData;

	*file >> setPlayerData.dataFlag;    // セーブされたデータがあるかどうか
	*file >> setPlayerData.characterData.templateData.typeNumber;    // キャラクタータイプ
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
	*file >> (int&)setPlayerData.characterData.mapType; // マップ名
	*file >> setPlayerData.characterData.position.x;  // 居る場所X軸
	*file >> setPlayerData.characterData.position.y;  // 居る場所Y軸
	*file >> setPlayerData.characterData.position.z;  // 居る場所Z軸
	*file >> setPlayerData.characterData.angle;  // 見ている方向
	*file >> setPlayerData.playerFolderName; // プレイヤー情報があるフォルダー名

	*file >> setPlayerData.itemNumber;   // アイテムの数
	
	setPlayerData.itemData.reserve(setPlayerData.itemNumber);

	for (int i = 0; i < setPlayerData.itemNumber; i++) {
		ItemData setItemData;
		*file >> setItemData.templateData.name;
		*file >> setItemData.templateData.typeNumber;
		*file >> setItemData.possessionCount;
		*file >> setItemData.itemPhotoFileName;

		setPlayerData.itemData.push_back(setItemData);
	}

	return setPlayerData;
}

// ファイルデータ書き込み用(プレイヤーデータ)
void DataManager::SetPlayerFileData(PLAYER_DATA setData, std::ofstream* file)
{
	*file << '\n';
	*file << setData.dataFlag;
	*file << '\n';
	*file << setData.characterData.templateData.typeNumber;
	*file << '\n';
	*file << setData.characterData.templateData.name;
	*file << '\n';
	*file << setData.characterData.survivalFlag;
	*file << '\n';
	*file << setData.characterData.status.level;
	*file << '\n';
	*file << setData.characterData.status.exp;
	*file << '\n';
	*file << setData.characterData.status.attackPower;
	*file << '\n';
	*file << setData.characterData.status.maxHp;
	*file << '\n';
	*file << setData.characterData.status.hp;
	*file << '\n';
	*file << setData.characterData.status.defense;
	*file << '\n';
	*file << setData.characterData.status.speed;
	*file << '\n';
	*file << setData.characterData.status.size;
	*file << '\n';
	*file << (int)setData.characterData.mapType;
	*file << '\n';
	*file << setData.characterData.position.x;
	*file << '\n';
	*file << setData.characterData.position.y;
	*file << '\n';
	*file << setData.characterData.position.z;
	*file << '\n';
	*file << setData.characterData.angle;
	*file << '\n';
	*file << setData.playerFolderName;
	*file << '\n';
	*file << setData.itemNumber;
	for (int i = 0; i < setData.itemNumber; i++) {
		*file << '\n';
		*file << setData.itemData[i].templateData.name;
		*file << '\n';
		*file << setData.itemData[i].templateData.typeNumber;
		*file << '\n';
		*file << setData.itemData[i].possessionCount;
		*file << '\n';
		*file << setData.itemData[i].itemPhotoFileName;
	}
}