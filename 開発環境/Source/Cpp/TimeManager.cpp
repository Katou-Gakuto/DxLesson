#include "DxLib.h"
#include "../Header/TimeManager.h"

/*
* @fn コンストラクタ
*/
TimeManager::TimeManager()
: mnFrameCount(0)
, mnStartTime(0)
, mnPreviousTime(0)
, mnStopTime(0)
, mbStopFlag(false)
, mnOneFrame(0)
, mbNewSceneTimeFlag(false)
{
}

/*
* @fn デストラクタ
*/
TimeManager::~TimeManager()
{
}

/*
* @fn Initilize
* @drief 初期化
*/
void TimeManager::Initilize()
{
    mnStartTime = GetNowCount();
    mnOneFrame = 17;
}

/*
* @fn Update
* @drief 更新
*/
void TimeManager::Update()
{
    mnFrameCount += 1;

    if (mbStopFlag) {
        mnStopTime += (GetNowCount() - mnPreviousTime);
        if (mbNewSceneTimeFlag) {
            mbNewSceneTimeFlag = false;
        }
    }
    else if (mbNewSceneTimeFlag) {
        mnStopTime += ((GetNowCount() - mnPreviousTime) - GetOneFrame());
        mbNewSceneTimeFlag = false;
    }

    mnPreviousTime = GetNowCount();
}