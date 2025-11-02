#include "DxLib.h"
#include "../Header/CoordinateXY.h"
#include "../Header/GameManager.h"
#include "../Header/GraphManager.h"
#include "../Header/MenuHowToPlay.h""
#include "../Header/Menu_Base.h"
#include "../Header/Operation.h"
#include "../Header/SoundManager.h"

/*
* @fn コンストラクタ
*/
MenuHowToPlay::MenuHowToPlay()
: Menu_Base(5, XYGet(0, 0), IntXY_Change_FloatXY(GetScreenSize()), GetColor(100, 100, 100), DX_BLENDMODE_NOBLEND)
, mbUpKyeFlag(false)
, mbDownKeyFlag(false)
, mpSoundManager(nullptr)
, mbDrawLeftKeyFlag(false)
, mbDrawRightKeyFlag(false)
{
	for (int i = 0; i < 2; i++) {
		mnDrawPictureHandle[i] = -1;
	}
}

/*
* @fn デストラクタ
*/
MenuHowToPlay::~MenuHowToPlay()
{
}

/*
* @fn MyInitilize
* @drief 個別初期化処理
*/
void MenuHowToPlay::MyInitilize()
{
	mpSoundManager = Master::mpGameManager->GetSoundManager();

	mnDrawPictureHandle[0] = Master::mpGameManager->GerGraphManager()->GetGraphHandle(GRAPH_TYPE::CONTROLLER_EXPLAIN);
	mnDrawPictureHandle[1] = Master::mpGameManager->GerGraphManager()->GetGraphHandle(GRAPH_TYPE::HOW_TO_PLAY_ONE);
	mnDrawPictureHandle[2] = Master::mpGameManager->GerGraphManager()->GetGraphHandle(GRAPH_TYPE::HOW_TO_PLAY_TWO);

	{
		mnDrawMaxMinStringHandle = CreateFontToHandle(NULL, 65, 10);
		mnDrawSoundVolumeStringHandle = CreateFontToHandle(NULL, 45, 10);
	}
}

/*
* @fn MyFinalize
* @drief 個別終了処理
*/
void MenuHowToPlay::MyFinalize()
{
	DeleteFontToHandle(mnDrawMaxMinStringHandle);
	DeleteFontToHandle(mnDrawSoundVolumeStringHandle);
}

/*
* @fn MyUpdate
* @drief 個別更新処理
*/
void MenuHowToPlay::MyUpdate()
{
	switch (mnMenuSelect)
	{
	case 0:
	case 1:
	case 2:
		break;

	case 3:
		if (Operation::CheckLeftKey()) {
			mpSoundManager->DownBackSoundVolume(1);
			mbDrawLeftKeyFlag = true;
		}
		else {
			mbDrawLeftKeyFlag = false;
		}
		if (Operation::CheckRightKey()) {
			mpSoundManager->UpBackSoundVolume(1);
			mbDrawRightKeyFlag = true;
		}
		else {
			mbDrawRightKeyFlag = false;
		}
		if (mbDrawLeftKeyFlag ^ mbDrawRightKeyFlag) {
			mpSoundManager->SetBackSoundVolumeProcess();
		}
		break;

	case 4:
		if (Operation::CheckLeftKey()) {
			mpSoundManager->DownSoundVolume(1);
			mbDrawLeftKeyFlag = true;
		}
		else {
			mbDrawLeftKeyFlag = false;
		}
		if (Operation::CheckRightKey()) {
			mpSoundManager->UpSoundVolume(1);
			mbDrawRightKeyFlag = true;
		}
		else {
			mbDrawRightKeyFlag = false;
		}
		break;
	}


	if (Operation::CheckUpKey()) {
		mbUpKyeFlag = true;
	}
	else {
		mbUpKyeFlag = false;
	}

	if (Operation::CheckDownKey()) {
		mbDownKeyFlag = true;
	}
	else {
		mbDownKeyFlag = false;
	}

	DefaultUpKeyProcess();
	DefaultDownKeyProcess();
	CheckBkey_CloseProcess();
}

/*
* @fn MyDraw
* @drief 個別描画化処理
*/
void MenuHowToPlay::MyDraw()
{
	// 枠
	DrawBox((GetScreenSize().x / 10) * 0.3, (GetScreenSize().y / 10) * 0.3,
			(GetScreenSize().x / 10) * 9.7, (GetScreenSize().y / 10) * 9.7,
		GetColor(255, 255, 255), TRUE);
	DrawBox((GetScreenSize().x / 10) * 0.4, (GetScreenSize().y / 10) * 0.4,
			(GetScreenSize().x / 10) * 9.6, (GetScreenSize().y / 10) * 9.6,
		GetColor(0, 0, 0), TRUE);

	// 戻る操作描画
	DrawBox((GetScreenSize().x / 10) * 0.5, (GetScreenSize().y / 10) * 9.0,
			(GetScreenSize().x / 10) * 1.6, (GetScreenSize().y / 10) * 9.5,
		GetColor(255, 255, 255), TRUE);
	DrawString((GetScreenSize().x / 10) * 0.55, (GetScreenSize().y / 10) * 9.1, "\"B\"BACK", GetColor(0, 0, 0));

	// HowToPlay文字描画
	DrawBox((GetScreenSize().x / 10) * 0.5, (GetScreenSize().y / 10) * 0.5,
			(GetScreenSize().x / 10) * 2.2, (GetScreenSize().y / 10) * 1,
		GetColor(255, 255, 255), TRUE);
	DrawString((GetScreenSize().x / 10) * 0.55, (GetScreenSize().y / 10) * 0.6, "HOW TO PLAY", GetColor(0, 0, 0));

	// 上下押し状態視覚化
	DrawTriangle((GetScreenSize().x / 10) * 5,   (GetScreenSize().y / 10) * 0.5,
				 (GetScreenSize().x / 10) * 3.0, (GetScreenSize().y / 10) * 1,
				 (GetScreenSize().x / 10) * 7.0, (GetScreenSize().y / 10) * 1,
		((mbUpKyeFlag) ? GetColor(150, 150, 150) : GetColor(255, 255, 255)), TRUE);
	DrawTriangle((GetScreenSize().x / 10) * 5,   (GetScreenSize().y / 10) * 9.5,
				 (GetScreenSize().x / 10) * 3.0, (GetScreenSize().y / 10) * 9,
				 (GetScreenSize().x / 10) * 7.0, (GetScreenSize().y / 10) * 9,
		((mbDownKeyFlag) ? GetColor(150, 150, 150) : GetColor(255, 255, 255)), TRUE);

	// 土台
	DrawBox((GetScreenSize().x / 10) * 0.5, (GetScreenSize().y / 10) * 1.1,
			(GetScreenSize().x / 10) * 9.5, (GetScreenSize().y / 10) * 8.9,
		GetColor(255, 255, 255), TRUE);

	switch (mnMenuSelect)
	{
	case 0:
	case 1:
	case 2:
		DrawExtendGraph((GetScreenSize().x / 10) * 0.5, (GetScreenSize().y / 10) * 1.1,
			(GetScreenSize().x / 10) * 9.5, (GetScreenSize().y / 10) * 8.9, mnDrawPictureHandle[mnMenuSelect], FALSE);
		break;

	case 3:
		DrawBox((GetScreenSize().x / 10) * 0.55, (GetScreenSize().y / 10) * 1.15,
				(GetScreenSize().x / 10) * 7.1, (GetScreenSize().y / 10) * 2.25,
			GetColor(0, 0, 0), TRUE);
		DrawBox((GetScreenSize().x / 10) * 0.65, (GetScreenSize().y / 10) * 1.25,
				(GetScreenSize().x / 10) * 7.0, (GetScreenSize().y / 10) * 2.15,
			GetColor(255, 255, 255), TRUE);
		DrawStringToHandle((GetScreenSize().x / 10) * 0.65, (GetScreenSize().y / 10) * 1.25, "BACK SOUND VOLUME", GetColor(0, 0, 0), mnDrawSoundVolumeStringHandle);

		// バックサウンドボリューム割合描画
		mpSoundManager->DrawBackSoundVolumeRate((GetScreenSize().x / 3) * 2, (GetScreenSize().y / 3), (GetScreenSize().x / 3), (GetScreenSize().y / 3), (GetScreenSize().y / 10) * 0.1, GetColor(200, 200, 200));


		DrawBox((GetScreenSize().x / 10) * 1.3, (GetScreenSize().y / 10) * 4, (GetScreenSize().x / 10) * 3.1, (GetScreenSize().y / 10) * 5.3, GetColor(0, 0, 0), TRUE);
		DrawStringToHandle((GetScreenSize().x / 10) * 1.4, (GetScreenSize().y / 3) * 1.2, "MIN", GetColor(255, 255, 255), mnDrawMaxMinStringHandle);

		DrawBox((GetScreenSize().x / 10) * 6.9, (GetScreenSize().y / 10) * 4, (GetScreenSize().x / 10) * 8.7, (GetScreenSize().y / 10) * 5.3, GetColor(0, 0, 0), TRUE);
		DrawStringToHandle((GetScreenSize().x / 10) * 7, (GetScreenSize().y / 3) * 1.2, "MAX", GetColor(255, 255, 255), mnDrawMaxMinStringHandle);

		// 左
		DrawTriangleAA((GetScreenSize().x / 6) * 2.9, (GetScreenSize().y / 10) * 4,
			(GetScreenSize().x / 6) * 2.9, (GetScreenSize().y / 10) * 8,
			(GetScreenSize().x / 10) * 3.1, (GetScreenSize().y / 10) * 6,
			(mbDrawLeftKeyFlag ? GetColor(100, 100, 100) : GetColor(200, 200, 200)), TRUE);
		// 右
		DrawTriangleAA((GetScreenSize().x / 6) * 3.1, (GetScreenSize().y / 10) * 4,
			(GetScreenSize().x / 6) * 3.1, (GetScreenSize().y / 10) * 8,
			(GetScreenSize().x / 10) * 6.9, (GetScreenSize().y / 10) * 6,
			(mbDrawRightKeyFlag ? GetColor(100, 100, 100) : GetColor(200, 200, 200)), TRUE);
		break;

	case 4:
		DrawBox((GetScreenSize().x / 10) * 0.55, (GetScreenSize().y / 10) * 1.15,
			(GetScreenSize().x / 10) * 5.25, (GetScreenSize().y / 10) * 2.25,
			GetColor(0, 0, 0), TRUE);
		DrawBox((GetScreenSize().x / 10) * 0.65, (GetScreenSize().y / 10) * 1.25,
			(GetScreenSize().x / 10) * 5.15, (GetScreenSize().y / 10) * 2.15,
			GetColor(255, 255, 255), TRUE);
		DrawStringToHandle((GetScreenSize().x / 10) * 0.65, (GetScreenSize().y / 10) * 1.25, "SOUND VOLUME", GetColor(0, 0, 0), mnDrawSoundVolumeStringHandle);

		// バックサウンドボリューム割合描画
		mpSoundManager->DrawSoundVolumeRate((GetScreenSize().x / 3) * 2, (GetScreenSize().y / 3), (GetScreenSize().x / 3), (GetScreenSize().y / 3), (GetScreenSize().y / 10) * 0.1, GetColor(200, 200, 200));


		DrawBox((GetScreenSize().x / 10) * 1.3, (GetScreenSize().y / 10) * 4, (GetScreenSize().x / 10) * 3.1, (GetScreenSize().y / 10) * 5.3, GetColor(0, 0, 0), TRUE);
		DrawStringToHandle((GetScreenSize().x / 10) * 1.4, (GetScreenSize().y / 3) * 1.2, "MIN", GetColor(255, 255, 255), mnDrawMaxMinStringHandle);

		DrawBox((GetScreenSize().x / 10) * 6.9, (GetScreenSize().y / 10) * 4, (GetScreenSize().x / 10) * 8.7, (GetScreenSize().y / 10) * 5.3, GetColor(0, 0, 0), TRUE);
		DrawStringToHandle((GetScreenSize().x / 10) * 7, (GetScreenSize().y / 3) * 1.2, "MAX", GetColor(255, 255, 255), mnDrawMaxMinStringHandle);

		// 左
		DrawTriangleAA((GetScreenSize().x / 6) * 2.9, (GetScreenSize().y / 10) * 4,
			(GetScreenSize().x / 6) * 2.9, (GetScreenSize().y / 10) * 8,
			(GetScreenSize().x / 10) * 3.1, (GetScreenSize().y / 10) * 6,
			(mbDrawLeftKeyFlag ? GetColor(100, 100, 100) : GetColor(200, 200, 200)), TRUE);
		// 右
		DrawTriangleAA((GetScreenSize().x / 6) * 3.1, (GetScreenSize().y / 10) * 4,
			(GetScreenSize().x / 6) * 3.1, (GetScreenSize().y / 10) * 8,
			(GetScreenSize().x / 10) * 6.9, (GetScreenSize().y / 10) * 6,
			(mbDrawRightKeyFlag ? GetColor(100, 100, 100) : GetColor(200, 200, 200)), TRUE);
		break;
	}
}

/*
* @fn SelectDecision
* @drief 選択決定時処理
*/
void MenuHowToPlay::SelectDecision()
{
}