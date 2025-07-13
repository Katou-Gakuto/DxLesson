#pragma once
#include <iostream>
#include <string>

#include "../Header/Object_Base.h"
#include "../Header/Status_Struct.h"

class Motion_Base;

class Object_Base_Character : public Object_Base
{
private:
    Object_Base_Character *mpPrevCharacterObject;                                                  // 前キャラクターオブジェクトへのポインタ
    Object_Base_Character *mpNextCharacterObject;                                                  // 次キャラクターオブジェクトへのポインタ

    int mnStasusDrawScreenHandle;   // ステータス描画範囲ハンドル
    int mnScreenSizeX;  // スクリーンの横幅

protected:
    //float mnHp;                 // 残りHP
    //float mnMaxHp;        // 最大HP
    //float mfAttackPower;        // 攻撃

    STATUS msStatus;    // ステータス

//    bool AttackHitPlayerFlag;   // 攻撃が有効フラグ

    VECTOR mvObjectPosition;    // オブジェクトの座標    移動する変数
    float mfAngle;  // 方向

    std::string mstrName;   // 名前
    std::string mstrDataFileName;   // データがあるファイル名

    Motion_Base *mpMotion;  // モーション

    bool mbMotionEndFlag;   // モーションエンドフラグ

    bool mbInvincibleFlag;          // 無敵フラグ
    bool mbHpMinusInvincibleFlag;   // HP減り無敵フラグが起動したかどうか
    int mnCheckHp;                  // HPチェック用
    int mnInvincibleTime;           // 無敵時間
    const int SET_INVINCIBLE_TIME = 2000;  // 無敵時間設定用

    void CheckHp_Invincible();  // HPが前回より減っているかどうか

    void SetMotionAttack(); // 攻撃モーションセット用

    void DrawBillboard_Name_Level();    // レベルと名前を表示
    void DrawBillboard_Name_Level_Hp(); // レベルと名前とHPを表示

    unsigned int GetHpColor() { return GetColor(255 * (1 - (static_cast<float>(msStatus.hp) / static_cast<float>(msStatus.maxHp))), 255 * (static_cast<float>(msStatus.hp) / static_cast<float>(msStatus.maxHp)), 0); }
    
public:

    Object_Base_Character(STATUS status, float angle, std::string name, std::string dataFileName);    // コンストラクタ
    ~Object_Base_Character();   // デストラクタ

    virtual void Initilize() override;  // 初期化
    virtual void Update() override;     // 更新
    virtual void Draw() override;       // 描画
    void Finalize() override final;     // キャラクターオブジェクト共通終了処理
    virtual void MyFinailize() = 0;     // 派生オブジェクト終了処理

    Object_Base_Character *GetPrevCharacterObject() { return mpPrevCharacterObject; }   // 前キャラクターオブジェクトへのポインタ取得
    Object_Base_Character *GetNextCharacterObject() { return mpNextCharacterObject; }   // 次キャラクターオブジェクトへのポインタ取得

    void SetPrevCharacterObject(Object_Base_Character *characterObject) { mpPrevCharacterObject = characterObject; }    // 前キャラクターオブジェクトのポインタを設定する関数
    void SetNextCharacterObject(Object_Base_Character *characterObject) { mpNextCharacterObject = characterObject; }    // 次キャラクターオブジェクトのポインタを設定する関数

    VECTOR GetObjectPosition() { return mvObjectPosition; }                     // ポジションゲット
    VECTOR *GetObjectPositionPointer() { return &mvObjectPosition; }                     // ポジション座標ゲット

    float GetObjectAngle() { return mfAngle; }  // 向いてる方向取得
    void SetObjectAngle(float angle) { mfAngle = angle; }   // 向いてる方向設定

    STATUS GetStatus() { return msStatus; } // ステータス取得

    void Damage(int damage, bool penetrationFlag = false);  // ダメージ
    virtual void HpZeroMove() = 0;  // HPが0以下時の処理

    void Recovery(int recovery);    // 回復

    void SetInvincibleFlag(bool flag);  // 無敵状態を設定する
    bool GetHpMinusInvincibleFlag() { return mbHpMinusInvincibleFlag; } // HPに減り無敵フラグが有効になったかどうか

    void SetAttackPower(float power) { msStatus.attackPower = power; } // 攻撃力セット

    std::string GetCharacterName() { return mstrName; } // キャラクターの名前
    std::string GetCharacterDataFileName() { return mstrDataFileName; } // データがあるファイル名取得
    //float GetTagAttackPower(int tag);                           // 指定の攻撃力取得

    //void SetAttackHitPlayerFlag(bool flag) { AttackHitPlayerFlag = flag; }    // 攻撃の有効設定
    //bool GetAttackHitPlayerFlag() { return AttackHitPlayerFlag; }  // 攻撃の有効フラグ取得

    //void StatusClear(int attackPower = 0, int hp = 0, int maxHp = 0, int defense = 0, int speed = 0);// ステータス初期化
};