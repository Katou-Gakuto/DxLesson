#pragma once
#include <vector>

#include "DxLib.h"
#include "../Header/GameManager.h"
#include "../Header/Object_Base_Character.h"
#include "../Header/SoundManager.h"

class TimeManager;

class Motion_Base
{
private:


    int mnAnimNumber2;  // 一つ前のアニメーションナンバー
    int mnAnimNumber1;  // 現在のアニメーションナンバー
    float mfAnimCount2; // 一つ前のアニメーションカウント
    float mfAnimCount1; // 現在のアニメーションカウント
    float mfAnimBlendRate;  // ブレンド率
    int mnAnimation2;  // 一つ前のアタッチされているアニメーション
    int mnAnimation1;  // 現在のアタッチされているアニメーション

    bool mbNotOneAnimFlag; // 複数のアニメーションを使うフラグ
    
    const float CHARA_ANIM_BLEND_SPEED = 0.1f;  // ブレンド率
    const float CHARA_PLAY_ANIM_SPEED = 0.5f;   // アニメーション再生速度

protected:
    TimeManager *mpTimeManager; // タイムマネージャー

    int mnModelHandle;  // モデルハンドル
    char *mcModelFileName;  // モデルファイル名

    std::vector<int> mnAnimHandle;  // アニメーションモデル
    std::vector<char *> mcAnimFileName; // アニメーションファイル名

    bool mbMoveFlag;  // 行動フラグ

    bool mbLoopFlag2;    // 一つ前のループフラグ
    bool mbLoopFlag1;    // 現在のループフラグ

    float mfAngle;  // アングル
    VECTOR mvAnglePostion;  // アングル用ポジション

    Object_Base_Character *mpCharacter; // このモーションをするキャラクター

    bool mbAttackFlag;  // 攻撃フラグ

    bool *mpCharacterEndFlag;  // キャラクター終了フラグ
    bool mbEndFlag; // 終了モーションフラグ
    int mnEndTime;  // 終了モーション時間

    bool mbEndObjectFlag;

    int mnNextFixedHitSoundTime;   // 固定物が当たった時のサウンド一定時間経つまで鳴らさない
//    int mnNextAttackHitSoundTime;

    float GetAnimCount() { return mfAnimCount1; }   // アニメーションカウント取得

    bool GetNotOneAnimFlag() { return mbNotOneAnimFlag; }   // 複数のアニメーションを使うフラグ取得

    const float GetPrayAnimSpeed() { return CHARA_PLAY_ANIM_SPEED; }    // アニメーション再生速度取得

    void Set3DSound(SOUND_3D sound3D) { Master::mpGameManager->GetSoundManager()->Set3DSound(sound3D, mpCharacter->GetObjectPosition()); }

public:

    Motion_Base(Object_Base_Character *character, const char* fileName, bool notOneAnimFlaga, bool endObjectFlag);
    ~Motion_Base();
    
    // 初期化
    void Initilize();
    virtual void MyInitilize() = 0;
    // 更新
    void Update();
    virtual void MyUpdata() = 0;
    // 描画
    void Draw();
    virtual void MyDraw() = 0;
    // 終了処理
    void Finalize();
    virtual void MyFinalize() = 0;

    void AddAnim(const char *fileName);   // アニメーション追加

    void SetMoveFlag(bool flag) { mbMoveFlag = flag; }  // 移動フラグ

    void ReSetFlag();   // フラグをリセットする
    virtual void ReSetPlusFlag() = 0;   // 子クラスで追加されたフラグをリセットする
    void SetDataSort(); // データを整理する
    virtual void SetPlusDataSort() = 0; // 追加されたデータを整理する
    bool GetAllFlag();  // 全フラグがfalseかどうか返す(一つでもtrueがあればtrueを返す)
    virtual bool GetPlusAllFlag() = 0;// 子クラスで追加されたフラグがfalseかどうか返す(一つでもtrueがあればtrueを返す)

    void SetAllFlag(bool flag); // 全フラグ設定
    virtual void SetPlusAllFlag(bool flag) = 0; // 子クラスで追加した全フラグ設定

    virtual int GetIndexNumber(const char *AnimName) = 0; // インデックスナンバーを行動名で取得
    int GetIndexNumberTemplate(const char *AnimName);   // インデックスナンバーを行動名で取得する関数のテンプレート
    virtual int GetIndexNumberLookFlag() = 0;   // インデックスナンバーをフラグで取得
    void ChangeAnimation(int index);  // アニメーション切り替え処理
    void PlayAnimation();   // アニメーション処理
    virtual bool LoopCheck(int index) = 0;   // ループチェック用

    void SetPosition(VECTOR position) { MV1SetPosition(mnModelHandle, position); }  // モデルの座標設定

    void SetAnglePosition(VECTOR position) { mvAnglePostion = VNorm(position); } // アングルポジション取得
    void SetAngleProcess(); // モデルアングル設定処理

    virtual void SetMultiAnimFrame() = 0;   // アニメーションフレーム固定用 複数
    virtual void SetOneAnimFrame() = 0; // アニメーションフレーム固定用 一つ

    void SetAttaclFlag(bool flag) { mbAttackFlag = flag; }  // 攻撃フラグ設定
    bool GetAttackFlag() { return mbAttackFlag; }   // 攻撃フラグ取得

    virtual void SetMotionAttackObject() = 0;   // モーションに設定されている攻撃をする

    int GetAnimationTimeFrame(int number);  // アニメーションの再生時間を取得する

    virtual void SetMotionEnd(bool *endFlag) = 0;   // モーション終了モーションスタート(無ければすぐ終了)

    bool GetStopMoveMotionFlag();   // キャラクターの移動処理をストップするフラグならtrueを返す
    virtual bool GetPlusStopMoveMotionFlag() = 0;   // キャラクターの移動処理をストップする子クラスで追加されたフラグならtrueを返す
    virtual VECTOR StopMoveProcess() = 0; // キャラクターの移動処理の代わりの処理をする

    bool GetStopAttackFlag();   // キャラクターの攻撃処理をストップするフラグが有効であればtrueを返す
    virtual bool GetPlusStopAttackFlag() = 0;   // キャラクターの攻撃処理をストップする子クラスで追加されたフラグが有効ならtrueを返す
    virtual void StopAttackProcess() = 0;   // キャラクターの攻撃処理の代わりの処理をする

    virtual int GetAttackTime() = 0;   // 攻撃時間を求める

    virtual void AttackHitSound() = 0;  // 攻撃が当たった時のサウンド
    virtual void FixedHitSound() = 0;   // 固定物に当たった時のサウンド
    virtual void HpZeroSound() = 0; // HPが0の時のサウンド

    virtual void CangeAttackFlag(int number) {} // 攻撃フラグを変更する
};