#pragma once
#include "../Header/CoordinateXY.h"
#include "../Header/DataManagerMacro.h"
#include "../Header/GameManager.h"
#include "../Header/Object_Base.h"
#include "../Header/SoundManager.h"

class DataManager;
class SceneManager;

class Menu_Base : public Object_Base
{
private:
	unsigned int mnColor;	// 基本の色

	int mnMyMenuNumber;	// 自分のメニューナンバー

	bool NowMyMenuFlag();	// 現在操作しているメニューはこのメニューか判定

	bool mbNotDecreaseFlag;	// 自動で減らさないフラグ

	int mnDrawBoxBlendType;	// 四角描画ブレンドタイプ指定用
	int mnDrawBoxBlendNumber;	// 四角描画ブレンドのパラメーター

	int mnNotPlayerDataHandle;  // プレイヤーがない時の文字描画ハンドル

	bool mbDrawPlayerDataFlag;	// プレイヤーデータを描画するかどうか

	bool mbSelectChangeSoundFlag;	// 選択変更時サウンド実行フラグ
	bool mbDecisionSoundFlag;	// 選択決定時サウンド実行フラグ
	bool mbCloseSoundFlag;	// メニュー終了時サウンド実行フラグ

protected:
	DataManager *mpDataManager;	// データマネージャー
	SceneManager *mpSceneManager;	// シーンマネージャー

	int mnMenuSelect;		// メニュー画面選択用変数
	int mnMaxMenuSelect;	// 最大メニュー画面選択数

	int mnChangeFrame;  // 選択変更したフレーム数
	int mnDecisionFrame;	// 決定するまでのフレーム

	COORDINATE_X_Y msUpperLeft;	// 左上座標
	
	COORDINATE_X_Y msLowerRight;	// 右下座標

	int mnDrawPlayerPictureHandle[PLAYER_DATA_NUMBER]; // プレイヤー画像描画ハンドル

	void DefaultMenuSelectUpdate();	// デフォルトの選択変更用処理
	void DefaultUpKeyProcess();		// デフォルトのアップキーを押した時の処理
	void DefaultDownKeyProcess();	// デフォルトのダウンキーを押した時の処理
	
	void CheckBkey_CloseProcess();	// Bキーを押したらメニューを閉じる処理

	bool CheckRightKeyAndFrame();	// 右キーが押されていて前回押したフレームから指定フレーム経っていればtrueを返す
	bool CheckLeftKeyAndFrame();	// 左キーが押されていて前回押したフレームから指定フレーム経っていればtrueを返す
	bool CheckUpKeyAndFrame();		// アップキーが押されていて前回押したフレームから指定フレーム経っていればtrueを返す
	bool CheckDownKeyAndFrame();	// ダウンキーが押されていて前回押したフレームから指定フレーム経っていればtrueを返す
	bool CheckDecision_AKeyAndFrame();	// Aキーが押されていて指定フレームぶん経っていれば[SelectDecision]を呼び出す
	
	COORDINATE_X_Y_INT GetScreenSize();	// スクリーンのサイズ取得

	bool CheckFrame(int frameNumber);	// フレームが一定時間経っているかどうか

	void DrawPlayerDatas();	// プレイヤー情報描画用

	void SetDecreaseMenuNumber();	// 指定の処理だけメニューがあるシーンへの移動の場合使う

	void GameEnd();	// チェックメニュー用関数(終了用)
	void TitleGo();	// チェックメニュー用関数(タイトル移動用)

	void SetCheckMenu_0() { SetOverride_CheckMenuProcess(); }	// チェック用メニュー関数(0番)
	virtual void SetOverride_CheckMenuProcess() {}	// チェックメニュー用関数(個別)

	void SetSelectChangeSound() { Master::mpGameManager->GetSoundManager()->SetSound(SOUND::SELECT_CHANGE); }	// 選択変更時サウンド
	void SetSelectDecisionSound() { Master::mpGameManager->GetSoundManager()->SetSound(SOUND::DECISION); }	// 選択決定時サウンド
	void SetCloseMenuSound() { Master::mpGameManager->GetSoundManager()->SetSound(SOUND::CLOSE); }	// メニュー閉じる時のサウンド
	void SetOpenMenuSound() { Master::mpGameManager->GetSoundManager()->SetSound(SOUND::OPEN); }	// メニュー開く時のサウンド
	void SetBeepSound() { Master::mpGameManager->GetSoundManager()->SetSound(SOUND::BEEP); }	// ビープサウンド

	void SetDecisionSoundFlag(bool flag) { mbDecisionSoundFlag = flag; }	// 決定時のサウンドフラグ設定
	void SetCloseSoundFlag(bool flag) { mbCloseSoundFlag = flag; }	// 閉じる時のサウンドフラグ設定
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="maxMenuSelect">最大選択数</param>
	/// <param name="upperLeft">左上</param>
	/// <param name="lowerRight">右下</param>
	/// <param name="color">色</param>
	/// <param name="drawBoxType">描画時描画タイプ</param>
	/// <param name="drawBoxNumber">描画時ナンバー</param>
	/// <param name="notDecreaseFlag">終了時メニューナンバーを減らさないフラグ</param>
	/// <param name="playerDataDrawFlag">プレイヤーデータを使用するフラグ</param>
	/// <param name="closeSoundFlag">メニューを閉じる時のサウンドフラグ</param>
	/// <param name="decisionSoundFlag">選択決定時のサウンドフラグ</param>
	/// <param name="selectChangeSoundFlag">選択変更時のサウンドフラグ</param>
	Menu_Base(int maxMenuSelect, COORDINATE_X_Y upperLeft, COORDINATE_X_Y lowerRight, unsigned int color, int drawBoxType, int drawBoxNumber = 255, bool notDecreaseFlag = false, bool playerDataDrawFlag = false, bool closeSoundFlag = true, bool decisionSoundFlag = true, bool selectChangeSoundFlag = true);
	~Menu_Base();	// デストラクタ

	void Initilize() override final;	// 共通初期化処理
	virtual void MyInitilize() = 0;		// 個別初期化処理
	void Finalize() override final;		// 共通終了処理
	virtual void MyFinalize() = 0;		// 個別終了処理
	void Update() override final;		// 共通更新処理
	virtual void MyUpdate() = 0;		// 個別更新処理
	void Draw() override final;			// 共通描画処理
	virtual void MyDraw() = 0;			// 個別描画化処理

	virtual void SelectDecision() = 0;  // 選択決定時処理

	void ResetDecisionFlame();	// 決定判定用変数のフレーム数をリセットする

	bool GetPlayerDataDrawFlag() { return mbDrawPlayerDataFlag; }
	void SetDrawPlayerHandle();	// プレイヤー描画用ハンドル初期化
};