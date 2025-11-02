#pragma once
#include "DxLib.h"
#include "../Header/Object_Base_Character.h"
#include "../Header/Status_Struct.h"

class Camera;

class Player_Base : public Object_Base_Character
{
private:
    int mnDrawPlayerStatusSizeHandle;   // プレイヤー情報描画用ハンドル

protected:
    Camera *mpCanera;   // カメラ

    VECTOR mvMoveVec;   // 総移動量
    VECTOR mvFrontVec;  // 前方向
    VECTOR mvRightVec;  // 右方向

    VECTOR mvSetMoveVec;    // 保存用移動量

    bool mbFrontMoveFlag;
    bool mbBackMoveFlag;
    bool mbRightMoveFlag;
    bool mbLeftMoveFlag;

    int mnAttackTime;  // 攻撃した時間
    int mnAttackInterval;   // 攻撃の間

    void SetVec();  // 移動方向ベクトル設定
    void GoMove();  // 移動処理
    void GetKey_SetMoveFlag(); // キー状況によって移動フラグを設定する
    void MoveProcess(); // 移動全処理をひとまとめにした物

    void AttackProcess();   // 攻撃処理
    virtual void GenerationAttackObject() = 0;  // 攻撃オブジェクト生成
    //void SetMotionAttack(); // 攻撃モーションセット用

    void EndProcess();  // 終了処理

public:

    Player_Base(Camera *camera, STATUS status, VECTOR position, float angle, std::string name, std::string dataFileName, int attackInterval);   // コンストラクタ
    ~Player_Base();  // デストラクタ

    // 初期化
    void Initilize() override final;
    virtual void MyInitilize() = 0;
    // 更新
    void Update() override final;
    virtual void MyUpdate() = 0;
    // 描画
    void Draw() override final;
    virtual void MyDraw() = 0;
    // 終了処理
    virtual void MyFinailize() override;
    

    void HpZeroMove() override; // HPが0以下時の処理

    void SetCamera();   // カメラをこのオブジェクトを見るようにする
};