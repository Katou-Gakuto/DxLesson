#pragma once

typedef enum
{
	/// <summary>ロボットキャラクター画像</summary>
	ROBOT_CHARACTER = 0,
	/// <summary>コントローラー説明</summary>
	CONTROLLER_EXPLAIN,
	/// <summary>遊び方説明1</summary>
	HOW_TO_PLAY_ONE,
	/// <summary>遊び方説明2</summary>
	HOW_TO_PLAY_TWO,
	/// <summary>回復薬(小)</summary>
	RECOVERY_MEDICINE_SMALL,
	/// <summary>回復薬(中)</summary>
	RECOVERY_MEDICINE_MEDIUUM,
	/// <summary>回復薬(大)</summary>
	RECOVERY_MEDICINE_LARGE,

	/// <summary>画像最大数</summary>
	MAX_GRAPH
}GRAPH_TYPE;


class GraphManager
{
private:
	int mnGraphHandles[GRAPH_TYPE::MAX_GRAPH];		// 画像ハンドル
	char* mcGraphFileNames[GRAPH_TYPE::MAX_GRAPH];	// 画像ファイル

public:
	GraphManager();
	~GraphManager();

	void Initilize();	// 初期化
	void Finalize();	// 終了

	int GetGraphHandle(int graphNumber);	// 画像ハンドル取得

	int GetGraphNumber(const char* graphFileName, bool getGraphHandleFlag = false);	// 画像ファイルが何個目に格納されているかを返す
};