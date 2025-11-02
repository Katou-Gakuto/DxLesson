#include "../Header/Camera.h"
#include "../Header/GameManager.h"
#include "../Header/Motion_Base.h"
#include "../Header/Object_Base_Character.h"
#include "../Header/ObjectManager.h"
#include "../Header/TimeManager.h"

/*
* @fn コンストラクタ
*/
Object_Base_Character::Object_Base_Character(STATUS status, float angle, std::string name, std::string dataFileName)
: Object_Base()
, mpNextCharacterObject(nullptr)
, mpPrevCharacterObject(nullptr)
, mvObjectPosition(VGet(0.0f, 0.0f, 0.0f))
, msStatus(status)
, mstrName(name)
, mstrDataFileName(dataFileName)
, mfAngle(angle)
, mpMotion(nullptr)
, mbMotionEndFlag(false)
, mbInvincibleFlag(false)
, mbHpMinusInvincibleFlag(false)
, mnInvincibleTime(0)
{
    mnCheckHp = msStatus.hp;
    //StatusClear();

    Master::mpGameManager->GetObjectManager()->AddCharacter(this);
    
    // ステータス描画用ハンドル設定
    {
        // 描画ハンドル
        mnScreenSizeX = name.size() * 10;
        if (mnScreenSizeX <= 70) {
            mnScreenSizeX = 70;
        }
        mnStasusDrawScreenHandle = MakeScreen(mnScreenSizeX, 40);
    }
}

/*
* @fn デストラクタ
*/
Object_Base_Character::~Object_Base_Character()
{
}

/*
* @fn Initilize
* @drief 初期化
*/
void Object_Base_Character::Initilize()
{
    // 無効
}

/*
* @fn Finalize
* @drief 終了処理
*/
void Object_Base_Character::Finalize()
{
    Master::mpGameManager->GetObjectManager()->CharacterDelete(this);

    if (mpMotion != nullptr) {
        mpMotion->Finalize();
        delete mpMotion;
    }
    DeleteGraph(mnStasusDrawScreenHandle);

    MyFinailize();
}

/*
* @fn Update
* @drief 更新
*/
void Object_Base_Character::Update()
{
}

/*
* @fn Draw
* @drief 描画
*/
void Object_Base_Character::Draw()
{
}

/*
* @fn Damage
* @drief ダメージ
*/
void Object_Base_Character::Damage(int damage, bool penetrationFlag)
{
    if (!mbInvincibleFlag || (penetrationFlag && (mnInvincibleTime == -1))) {
        int setDamage = (damage - msStatus.defense);
        if (setDamage > 0) {
            if (msStatus.hp > 0) {
                msStatus.hp -= setDamage;
            }
            if (msStatus.hp <= 0) {
                msStatus.hp = 0;
                HpZeroMove();
                mpMotion->HpZeroSound();
            }
            else {
                mpMotion->AttackHitSound();
            }
        }
    }
}

/*
* @fn Recovery
* @drief 回復
*/
void Object_Base_Character::Recovery(int recovery)
{
    msStatus.hp += recovery;
    if (msStatus.hp > msStatus.maxHp) {
        msStatus.hp = msStatus.maxHp;
    }
}

/*
* @fn CheckHp_Invincible
* @drief HPが前回より減っているかどうか
*/
void Object_Base_Character::CheckHp_Invincible()
{
    if (!mbInvincibleFlag) {
        if (mnCheckHp > msStatus.hp) {
            mbInvincibleFlag = true;
            mbHpMinusInvincibleFlag = true;
            mnCheckHp = msStatus.hp;
            mnInvincibleTime = (Master::mpGameManager->GetTimeManager()->GetGameTime() + SET_INVINCIBLE_TIME);
        }
    }
    else {
        if (mnInvincibleTime != -1) {
            if (mnInvincibleTime <= Master::mpGameManager->GetTimeManager()->GetGameTime()) {
                mbInvincibleFlag = false;
                mbHpMinusInvincibleFlag = false;
            }
        }
        else {
            mbHpMinusInvincibleFlag = false;
        }
    }
}

/*
* @fn SetInvincibleFlag
* @drief 無敵状態を設定する
*/
void Object_Base_Character::SetInvincibleFlag(bool flag)
{
    if (flag) {
        mnInvincibleTime = -1;
    }
    mbInvincibleFlag = flag;
}

/*
* @fn SetMotionAttack
* @drief 攻撃モーションセット用
*/
void Object_Base_Character::SetMotionAttack()
{
    // モーションの攻撃フラグを有効にする
    mpMotion->SetAttaclFlag(true);

    // モーションに設定された攻撃をする
    mpMotion->SetMotionAttackObject();
}

/*
* @fn DrawBillboard_Name_Level
* @drief レベルと名前を表示
*/
void Object_Base_Character::DrawBillboard_Name_Level()
{

    // 描画必要データ取得
    VECTOR setCharacterPos = VAdd(mvObjectPosition, VGet(0, msStatus.size * 2.7, 0));

    // 描画先を変更
    SetDrawScreen(mnStasusDrawScreenHandle);
    ClearDrawScreen();

    // 土台
    DrawBoxAA(0, 0, mnScreenSizeX, 40, GetColor(255, 255, 255), TRUE);
    DrawBoxAA(2, 2, mnScreenSizeX - 2, 40 - 2, GetColor(0, 0, 0), TRUE);

    // 名前
    //DrawExtendGraph(0, 0, 100, 50, mnNameHandle, TRUE);
    DrawFormatString(5, 21, GetColor(255, 255, 255), "%s", mstrName.c_str());

    // レベル
    DrawBox(1, 1, 65, 20, GetColor(255, 255, 255), TRUE);
    DrawBox(3, 3, 63, 18, GetColor(0, 0, 0), TRUE);
    DrawFormatString(5, 3, GetColor(255, 255, 255), "Lv.%d", msStatus.level);

    SetDrawScreen(DX_SCREEN_BACK);
    // 3Dカメラ設定
    Master::mpCamera->Initialize3DCameraTemplate();
    DrawBillboard3D(setCharacterPos, 0.5f, 0.5f, 200.0f, 0.0f, mnStasusDrawScreenHandle, TRUE);

}

/*
* @fn DrawBillboard_Name_Level_Hp
* @drief レベルと名前とHPを表示
*/
void Object_Base_Character::DrawBillboard_Name_Level_Hp()
{

    // 描画必要データ取得
    VECTOR setCharacterPos = VAdd(mvObjectPosition, VGet(0, msStatus.size * 2.7, 0));

    // 描画先を変更
    SetDrawScreen(mnStasusDrawScreenHandle);
    ClearDrawScreen();

    // 土台
    DrawBoxAA(0, 0, mnScreenSizeX, 40, GetColor(255, 255, 255), TRUE);
    DrawBoxAA(2, 2, mnScreenSizeX - 2, 40 - 2, GetColor(0, 0, 0), TRUE);

    // 名前
    //DrawExtendGraph(0, 0, 100, 50, mnNameHandle, TRUE);
    DrawFormatString(5, 21, GetColor(255, 255, 255), "%s", mstrName.c_str());

    // レベル
    DrawBox(1, 1, 65, 20, GetColor(255, 255, 255), TRUE);
    DrawBox(3, 3, 63, 18, GetColor(0, 0, 0), TRUE);
    DrawFormatString(5, 3, GetColor(255, 255, 255), "Lv.%d", msStatus.level);

    SetDrawScreen(DX_SCREEN_BACK);
    // 3Dカメラ設定
    Master::mpCamera->Initialize3DCameraTemplate();
    DrawBillboard3D(VAdd(setCharacterPos, VGet(0, 100.0f, 0)), 0.5f, 0.5f, 200.0f, 0.0f, mnStasusDrawScreenHandle, TRUE);



    // 描画先を変更
    SetDrawScreen(mnStasusDrawScreenHandle);
    ClearDrawScreen();

    // 土台
    DrawBoxAA(0, 0, mnScreenSizeX, 40, GetColor(255, 255, 255), TRUE);
    DrawBoxAA(2, 2, mnScreenSizeX - 2, 40 - 2, GetColor(0, 0, 0), TRUE);

    // HP文字
    DrawFormatString(5, 3, GetColor(255, 255, 255), "HP:%d", msStatus.hp);

    // HPバー
    DrawBox(5, 20, mnScreenSizeX - 5, 35, GetColor(255, 255, 255), TRUE);
    DrawBox(8, 23, mnScreenSizeX - 8, 32, GetColor(0, 0, 0), TRUE);
    DrawBox(8, 23, ((mnScreenSizeX - 16) * (static_cast<float>(msStatus.hp) / static_cast<float>(msStatus.maxHp))) + 8, 32, GetHpColor(), TRUE);

    SetDrawScreen(DX_SCREEN_BACK);
    // 3Dカメラ設定
    Master::mpCamera->Initialize3DCameraTemplate();
    DrawBillboard3D(setCharacterPos, 0.5f, 0.5f, 200.0f, 0.0f, mnStasusDrawScreenHandle, TRUE);

}

///*
//* @fn GetTagAttackPower
//* @drief 指定の攻撃力取得
//*/
//float Object_Base_Character::GetTagAttackPower(int tag)
//{
//    Object_Base *obj = Master::mpGameManager->GetObjectManager()->FindByTag(tag);
//    if (obj != nullptr)
//    {
//        return obj->GetAttackPower();
//    }
//}

/*
* @fn StatusClear
* @drief ステータス初期化
*//*
void Object_Base_Character::StatusClear(int attackPower, int hp, int maxHp, int defense, int speed)
{
    msStatus.attackPower = attackPower;
    msStatus.hp = hp;
    msStatus.maxHp = maxHp;
    msStatus.defense = defense;
    msStatus.speed = speed;
}*/