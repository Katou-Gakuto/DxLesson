#include <string.h>

#include "DxLib.h"
#include "../Header/GraphManager.h"

/*
* @fn コンストラクタ
*/
GraphManager::GraphManager()
{
	mcGraphFileNames[0] = (char*)"Resource/2D/RobotSphere.png";
	mcGraphFileNames[1] = (char*)"Resource/2D/Controller.jpg";
	mcGraphFileNames[2] = (char*)"Resource/2D/HowToPlay_1.jpg";
	mcGraphFileNames[3] = (char*)"Resource/2D/HowToPlay_2.jpg";
	mcGraphFileNames[4] = (char*)"Resource/2D/RecoveryMedicine(Small).png";
	mcGraphFileNames[5] = (char*)"Resource/2D/RecoveryMedicine(Medium).png";
	mcGraphFileNames[6] = (char*)"Resource/2D/RecoveryMedicine(Large).png";

	for (int i = 0; i < GRAPH_TYPE::MAX_GRAPH; i++)
	{
		mnGraphHandles[i] = -1;
	}
}

/*
* @f デストラクタ
*/
GraphManager::~GraphManager()
{
}

/*
* @fn Initilize
* @drief 初期化
*/
void GraphManager::Initilize()
{

	for (int i = 0; i < GRAPH_TYPE::MAX_GRAPH; i++)
	{
		mnGraphHandles[i] = LoadGraph(mcGraphFileNames[i]);
	}
}

/*
* @fn Finalize
* @drief 終了
*/
void GraphManager::Finalize()
{
	for (int i = 0; i < GRAPH_TYPE::MAX_GRAPH; i++)
	{
		DeleteGraph(mnGraphHandles[i]);
	}
}

/*
* @fn GetGraphHandle
* @drief 画像ハンドル取得
*/
int GraphManager::GetGraphHandle(int graphNumber)
{
	return mnGraphHandles[graphNumber];
}

/*
* @fn GetGraphNumber
* @drief 画像ファイルが何個目に格納されているかを返す
*/
int GraphManager::GetGraphNumber(const char* graphFileName, bool getGraphHandleFlag)
{
	for (int i = 0; i < GRAPH_TYPE::MAX_GRAPH; i++)
	{
		if (strcmp(graphFileName, mcGraphFileNames[i]) == 0)
		{
			if (getGraphHandleFlag)
			{
				return GetGraphHandle(i);
			}
			return i;
		}
	}

	return -1;
}