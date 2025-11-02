#include "DxLib.h"
#include "../Header/ModelManager.h"

/*
* @fn コンストラクタ
*/
ModelManager::ModelManager()
{
	mcModelFileNames[0] = (char *)"Resource/3D/Test/robotSphere.mv1"; // ロボットモデル
	// ロボット系アニメーション
	mcModelFileNames[1] = (char *)"Resource/3D/Test/Animation/robotSphere@anim_open.mv1";
	mcModelFileNames[2] = (char*)"Resource/3D/Test/Animation/robotSphere@anim_Idle_Loop_S.mv1";
	mcModelFileNames[3] = (char*)"Resource/3D/Test/Animation/robotSphere@anim_open_Idle_F1.mv1";
	mcModelFileNames[4] = (char*)"Resource/3D/Test/Animation/robotSphere@anim_open_Walk_Loop.mv1";
	mcModelFileNames[5] = (char*)"Resource/3D/Test/Animation/robotSphere@anim_open_GoToRoll.mv1";
	mcModelFileNames[6] = (char*)"Resource/3D/Test/Animation/robotSphere@anim_cloed_Roll_Loop.mv1";
	mcModelFileNames[7] = (char*)"Resource/3D/Test/Animation/robotSphere@anim_closed_StopRoll.mv1";
	mcModelFileNames[8] = (char*)"Resource/3D/Test/Animation/robotSphere@anim_close.mv1";

	mcModelFileNames[9] = (char *)"Resource/3D/Tower/Wall.mv1";// タワー
	mcModelFileNames[10] = (char *)"Resource/3D/Floor/Ceiling_Closed.mv1"; // 地面

	for (int i = 0; i < MODEL_TYPE::MAX_MODEL; i++)
	{
		mnModelHandles[i] = -1;
	}
}

/*
* @fn デストラタ
*/
ModelManager::~ModelManager()
{
}

/*
* @fn Initilize
* @drief 初期化
*/
void ModelManager::Initilize()
{
	for (int i = 0; i < MODEL_TYPE::MAX_MODEL; i++)
	{
		mnModelHandles[i] = MV1LoadModel(mcModelFileNames[i]);
	}
}

/*
* @fn Finalize
* @drief 終了
*/
void ModelManager::Finalize()
{
	for (int i = 0; i < MODEL_TYPE::MAX_MODEL; i++)
	{
		MV1DeleteModel(mnModelHandles[i]);
	}
}

/*
* @fn GetModelHandle
* @drief モデルハンドル取得
*/
int ModelManager::GetModelHandle(int modelNumber)
{
	return MV1DuplicateModel(mnModelHandles[modelNumber]);
}

/*
* @fn GetModelNumber
* @drief モデルファイルが何個目に格納されているかを返す
*/
int ModelManager::GetModelNumber(const char* modelFileName, bool getModelHandleFlag)
{
	for (int i = 0; i < MODEL_TYPE::MAX_MODEL; i++)
	{
		if (modelFileName == mcModelFileNames[i])
		{
			if (getModelHandleFlag)
			{
				return GetModelHandle(i);
			}
			return i;
		}
	}

	return -1;
}