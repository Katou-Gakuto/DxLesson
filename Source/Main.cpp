#include "DxLib.h"
#include "Header/Camera.h"
#include "Header/GameManager.h"
#include "Header/ObjectManager.h"
#include "Header/SceneManager.h"
#include "Header/TimeManager.h"

/*タグ
* ステージマネージャー(312)
* プレイヤー(7578)
* エネミー(2966)
* 中立キャラクター(798)
* 壁(3973)
* 攻撃(1916)
*/


/*
* 基本構造
  
* DxLib設定
  ↓
* 初期化
  ↓

* //--- ループ
* 更新
  ↓
* シーンチェック
  ↓
* 削除チェック
  ↓
* 描画
* //--- ループ終了チェック

  ↓
* 終了処理
  ↓
* ゲームマネージャー削除
  ↓
* DxLib終了処理
  ↓
* 終了

*/

/*
* メモ
* ・小文字英字横幅 9
*/

/**
* @file 
* @author 
* @date 
*
* @details 
* @note リファレンス https://dxlib.xsrv.jp/dxfunc.html
*/

// 静的メンバ変数定義
GameManager *Master::mpGameManager = new GameManager();
Camera *Master::mpCamera = new Camera();




/**
* @fn WinMain
* @brief Main関数
* @param[in] HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow
* @return int 0 正常終了／-1 エラー
* @details Main関数
*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	// ウインドウモードで起動
	ChangeWindowMode(true);

	// DXライブラリ初期化処理
	if(DxLib_Init() == -1)
	{
		return -1;		// エラーが起きたら直ちに終了
	}

	// 描画先画面を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);

	// ゲームマネージャーの初期化
	Master::mpGameManager->Initilize();

	// ループ
	while (ProcessMessage() == 0 && !Master::mpGameManager->GetEndFlag())
	{
		// エスケープキーを押していれば終了する
		if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) {
			Master::mpGameManager->SetEndFlag(true);
		}

		// ゲームマネージャーのオブジェクトマネージャーによる更新。
		Master::mpGameManager->Update();

		// シーン変更の必要があればシーンを変更する
		Master::mpGameManager->GetSceneManager()->CheckScene();

		// 必要であればオブジェクトを削除
		Master::mpGameManager->GetObjectManager()->DeleteAllIfNeeded();

		// ゲームマネージャーのオブジェクトマネージャーによる描画。
		Master::mpGameManager->Draw();

		// １７ミリ秒(約秒間６０フレームだった時の１フレームあたりの経過時間)
		// 経過するまでここで待つ
		while (GetNowCount() - Master::mpGameManager->GetTimeManager()->GetPreviousTime() < Master::mpGameManager->GetTimeManager()->GetOneFrame())
		{
		}
	}

	// ゲームマネージャーの終了処理
	Master::mpGameManager->Finalize();

	// ゲームマネージャーの消去
	delete Master::mpGameManager;

	// DXライブラリ使用の終了処理
	DxLib_End();

	// ソフトの終了
	return 0;
}
