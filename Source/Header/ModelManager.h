#pragma once

typedef enum
{
	/// <summary>ロボットモデル</summary>
	ROBOT_MODEL = 0,
	/// <summary>ロボット開きアニメーション</summary>
	ROBOT_OPEN_ANIMATION,
	/// <summary>ロボット通常アニメーション</summary>
	ROBOT_IDLE_ANIMATION,
	/// <summary>ロボット開き中通常アニメーション</summary>
	ROBOT_OPEN_IDLE_ANIMATION,
	/// <summary>ロボット歩きアニメーション</summary>
	ROBOT_OPEN_WALK_LOOP_ANIMATION,
	/// <summary>ロボット転がり初めアニメーション</summary>
	ROBOT_OPEN_GO_TO_ROLL_ANIMATION,
	/// <summary>ロボット転がり中アニメーション</summary>
	ROBOT_CLOSED_ROLL_LOOP_ANIMATION,
	/// <summary>ロボット転がり終了アニメーション</summary>
	ROBOT_CLOSED_STOP_ROLL_ANIMATION,
	/// <summary>ロボット閉じアニメーション</summary>
	ROBOT_CLOSE_ANIMATION,
	/// <summary>タワーモデル</summary>
	TOWER_MODEL,
	/// <summary>地面モデル</summary>
	FLOOR_MODEL,
	/// <summary>画像最大数</summary>
	MAX_MODEL
}MODEL_TYPE;

class ModelManager
{
private:
	int mnModelHandles[MODEL_TYPE::MAX_MODEL];
	char *mcModelFileNames[MODEL_TYPE::MAX_MODEL];

public:
	ModelManager();
	~ModelManager();

	void Initilize();	// 初期化
	void Finalize();	// 終了
	
	int GetModelHandle(int modelNumber);	// モデルハンドル取得

	int GetModelNumber(const char* modelFileName, bool getModelHandleFlag = false);	// モデルファイルが何個目に格納されているかを返す
};