#pragma once
class DataController
{
private:
	// プレイヤーセーブデータ

	// プレイヤーナウデータ

	// ベースデータ

	bool mbFailureFlag;

public:
	DataController();
	~DataController();

	void DataGet();

	void GetBaseData();

	void GetPlayerData();

	void SetNowData();

	void SetSaveData();
private:
	void GetDats();

	void SetData();
};