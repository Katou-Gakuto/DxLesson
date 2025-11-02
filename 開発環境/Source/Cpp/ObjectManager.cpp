#include "Dxlib.h"
#include "../Header/ObjectManager.h"
#include "../Header/Object_Base.h"
#include "../Header/Object_Base_Attack.h"
#include "../Header/Object_Base_Character.h"
#include "../Header/Object_Base_Fixed.h"

ObjectManager::ObjectManager() 
: mpObject(nullptr)
, mpObjectL(nullptr)
, mpCharacterObject(nullptr)
, mpCharacterObjectL(nullptr)
, mpFixedObject(nullptr)
, mpFixedObjectL(nullptr)
{

}

ObjectManager::~ObjectManager()
{

}

void ObjectManager::Initilize()
{
    mpObject->Initilize();
    mpObjectL->Initilize();
}

void ObjectManager::Finalize()
{

}

void ObjectManager::Update()
{
    // 何も生成してないなら何もしない
    if (mpObject == nullptr)
    {
        return;
    }

    Object_Base *workObject = mpObject;
    do {
        workObject->Update();
        workObject = workObject->GetNextObject();
    } while (workObject != nullptr);

    /*
    if (mpObject == nullptr)
    {
        return;
    }

    Object_Base *workObject = mpObject;
    bool Last = false;
    /*
    do
    {
        workObject->Update();
        workObject = workObject->GetNextObject();
    } while (workObject != mpObjectL);
    *//*
    while (1)
    {

        if (workObject == mpObjectL)
        {
            Last = true;
        }

        /*//*////////////////////////
        if (workObject == nullptr)
        {
            break;
        }
        *//*////////////////////////

        workObject->Update();
        workObject = workObject->GetNextObject();

        if (Last)
        {
            break;
        }
    }
    */
}

void ObjectManager::Draw()
{

    // 何も生成してないなら何もしない
    if (mpObject == nullptr)
    {
        return;
    }

    Object_Base *workObject = mpObject;
    do {
        workObject->Draw();
        workObject = workObject->GetNextObject();
    } while (workObject != nullptr);
    /*
    if (mpObject == nullptr)
    {
        return;
    }

    Object_Base *workObject = mpObject;
    bool LastFinal = false;
    /*
    do
    {
        workObject->Draw();
        workObject = workObject->GetNextObject();
    } while (workObject != mpObjectL);
    *//*
    while (1)
    {
        if (workObject == mpObjectL)
        {
            LastFinal = true;
        }

        /*//*///////////////////////
        if (workObject == nullptr)
        {
            break;
        }
        *//*////////////////////////

        workObject->Draw();
        workObject = workObject->GetNextObject();

        if (LastFinal)
        {
            break;
        }
    }
*/
}

/*
* @fn Add
* @drief リストにオブジェクトを追加する関数
*/
void ObjectManager::Add(Object_Base *object)
{
    if (mpObject == nullptr)
    {
        mpObject = object;
        mpObjectL = object;
        return;
    }

    // 一番後ろの場所を探している。
    Object_Base *currentObject = mpObject;
    Object_Base *nextObject = mpObject->GetNextObject();
    while (nextObject != nullptr)
    {
        currentObject = nextObject;
        nextObject = currentObject->GetNextObject();
    }

    // 一番後ろのさらに後ろにオブジェクトを追加する。
    currentObject->SetNextObject(object);
    object->SetPrevObject(currentObject);
    mpObjectL = object;
}

/*
* @fn Delete
* @drief リストからオブジェクトを除外する関数
*/
void ObjectManager::Delete(Object_Base *object)
{
    // 最初のオブジェクトすらない場合は何もしない。
    if (mpObject == nullptr)
    {
        return;
    }

    // もし最初のオブジェクトだった場合は特別な処理をする。
    if (mpObject == object)
    {
        Object_Base *next = mpObject->GetNextObject();
        if (next != nullptr)
        {
            next->SetPrevObject(nullptr);
            mpObject = next;
        }
        else {
            mpObject = nullptr;
            mpObjectL = nullptr;
        }

        object->Finalize();
        delete object;
        return;
    }

    // 以下、最初のオブジェクトではなかった場合の処理

    // 削除対象のオブジェクトを探索する
    Object_Base *target = mpObject->GetNextObject();
    while (target != object)
    {
        if (target == mpObjectL)
        {
            return;             // 見つからなかった場合なので、苦肉の策でリターン。
        }
        target = target->GetNextObject();
    }

    // 削除対象のオブジェクトの前と後ろを繋げるために、一旦確保しておく
    Object_Base *prev = target->GetPrevObject();
    Object_Base *next = target->GetNextObject();

    // mpObjectLが削除対象だった場合、削除対象のひとつ前をmpObjectLにする必要がある。
    if (target == nullptr)//mpObjectL)
    {
        mpObjectL = prev;
    }

    // 削除対象のオブジェクトの前後を繋げ、削除対象を孤立させる
    prev->SetNextObject(next);
    if (next != nullptr)
    {
        next->SetPrevObject(prev);
    }
    /*
    else
    {
        next->SetPrevObject(nullptr);
    }
    */

    // target自体がポインタなので、targetを通じて実引数objectをdeleteする
    target->Finalize();
    delete target;
    target = nullptr;
}

/*
* @fn FindByTag
* @drief タグからオブジェクトを取得
* @detail 見つからなかったらnullを返すので、呼び出し側でnullチェック
*/
Object_Base *ObjectManager::FindByTag(int tag, bool flag)
{
    // 何も生成してないなら何もしない
    if (mpObject == nullptr)
    {
        return mpObject;
    }

    Object_Base *workObject = mpObject;
    do {
        if ((!(workObject->IsDeleteFlag())) || flag) {
            if (tag == workObject->GetTag())
            {
                return workObject;
            }
        }
        workObject = workObject->GetNextObject();
    } while (workObject != nullptr);
    return workObject;
}



/*
* @fn FindsByTag
* @drief タグからオブジェクトを複数、取得
* @detail 見つからなかったらnullを返すので、呼び出し側でnullチェック
*/
std::vector<Object_Base *> ObjectManager::FindsByTag(int tag, bool flag)
{
    std::vector<Object_Base *> result;

    // 最初のオブジェクトがないなら何もしない
    if (mpObject == nullptr)
    {
        return result;
    }

    Object_Base *target = mpObject;
    do {

        Object_Base *next = target->GetNextObject();
        if ((!(target->IsDeleteFlag())) || flag) {
            if (tag == target->GetTag())
            {
                result.push_back(target);
            }
        }
        target = next;
    
    } while (target != nullptr);

    // 見つけた物を返す
    return result;
}

/*
* @fn AddAttack
* @drief リストに攻撃オブジェクトを追加
*/
void ObjectManager::AddAttack(Object_Base_Attack *attackObject)
{
    if (mpAttackObject == nullptr)
    {
        mpAttackObject = attackObject;
        mpAttackObjectL = attackObject;
        return;
    }

    // 一番後ろの場所を探している。
    Object_Base_Attack *currentAttackObject = mpAttackObject;
    Object_Base_Attack *nextAttackObject = mpAttackObject->GetNextAttackObject();
    while (nextAttackObject != nullptr)
    {
        currentAttackObject = nextAttackObject;
        nextAttackObject = currentAttackObject->GetNextAttackObject();
    }

    // 一番後ろのさらに後ろにオブジェクトを追加する。
    currentAttackObject->SetNextAttackObject(attackObject);
    attackObject->SetPrevAttackObject(currentAttackObject);
    mpAttackObjectL = attackObject;
}

/*
* @fn AttackDelete
* @drief リストから攻撃オブジェクトを除外
*/
void ObjectManager::AttackDelete(Object_Base_Attack *attackObject)
{
    // 最初のオブジェクトすらない場合は何もしない。
    if (mpAttackObject == nullptr)
    {
        return;
    }

    // もし最初のオブジェクトだった場合は特別な処理をする。
    if (mpAttackObject == attackObject)
    {
        Object_Base_Attack *next = mpAttackObject->GetNextAttackObject();
        if (next != nullptr)
        {
            next->SetPrevAttackObject(nullptr);
            mpAttackObject = next;
        }
        else {
            mpAttackObject = nullptr;
            mpAttackObjectL = nullptr;
        }
        return;
    }

    // 以下、最初のオブジェクトではなかった場合の処理

    // 削除対象のオブジェクトを探索する
    Object_Base_Attack *target = mpAttackObject->GetNextAttackObject();
    while (target != attackObject)
    {
        if (target == mpAttackObjectL)
        {
            return;             // 見つからなかった場合なので、苦肉の策でリターン。
        }
        target = target->GetNextAttackObject();
    }

    // 削除対象のオブジェクトの前と後ろを繋げるために、一旦確保しておく
    Object_Base_Attack *prev = target->GetPrevAttackObject();
    Object_Base_Attack *next = target->GetNextAttackObject();

    // mpAttackObjectLが削除対象だった場合、削除対象のひとつ前をmpAttackObjectLにする必要がある。
    if (target == nullptr)//mpAttackObjectL)
    {
        mpAttackObjectL = prev;
    }

    // 削除対象のオブジェクトの前後を繋げ、削除対象を孤立させる
    prev->SetNextAttackObject(next);
    if (next != nullptr)
    {
        next->SetPrevAttackObject(prev);
    }
}

/*
* @fn FindByTag_AttackObject
* @drief タグから攻撃オブジェクトを取得
*/
Object_Base_Attack *ObjectManager::FindByTag_AttackObject(int tag, bool flag)
{
    // 何も生成してないなら何もしない
    if (mpAttackObject == nullptr)
    {
        return mpAttackObject;
    }

    Object_Base_Attack *workObject = mpAttackObject;
    do {
        if ((!(workObject->IsDeleteFlag())) || flag) {
            if (tag == workObject->GetTag())
            {
                return workObject;
            }
        }
        workObject = workObject->GetNextAttackObject();
    } while (workObject != nullptr);
    return workObject;
}

/*
* @fn FindsByTag_AttackObject
* @drief タグから複数攻撃オブジェクトを取得
*/
std::vector<Object_Base_Attack *>ObjectManager::FindsByTag_AttackObject(int tag, bool flag)
{
    std::vector<Object_Base_Attack *> result;

    // 最初のオブジェクトがないなら何もしない
    if (mpAttackObject == nullptr)
    {
        return result;
    }

    Object_Base_Attack *target = mpAttackObject;
    do {

        Object_Base_Attack *next = target->GetNextAttackObject();
        if ((!(target->IsDeleteFlag())) || flag) {
            if (tag == target->GetTag())
            {
                result.push_back(target);
            }
        }
        target = next;

    } while (target != nullptr);

    // 見つけた物を返す
    return result;
}

/*
* @fn AttackObjectHitCheck
* @drief 攻撃オブジェクトの攻撃判定　当たていればダメージを負う
*/
bool ObjectManager::AllAttackObjectHitCheck(Object_Base_Character *characterObject)
{
    bool flag = false;

    if (mpAttackObject == nullptr) {
        return flag;
    }
    
    Object_Base_Attack *checkObject = mpAttackObject;
    do {
        Object_Base_Attack *next = checkObject->GetNextAttackObject();

        flag |= checkObject->CheckCharacter(characterObject);

        checkObject = next;

    } while (checkObject != nullptr);

    return flag;
}

/*
* @fn AddCharacter
* @drief リストにキャラクターオブジェクトを追加
*/
void ObjectManager::AddCharacter(Object_Base_Character *characterObject)
{
    if (mpCharacterObject == nullptr)
    {
        mpCharacterObject = characterObject;
        mpCharacterObjectL = characterObject;
        return;
    }

    // 一番後ろの場所を探している。
    Object_Base_Character *currentCharacterObject = mpCharacterObject;
    Object_Base_Character *nextCharacterObject = mpCharacterObject->GetNextCharacterObject();
    while (nextCharacterObject != nullptr)
    {
        currentCharacterObject = nextCharacterObject;
        nextCharacterObject = currentCharacterObject->GetNextCharacterObject();
    }

    // 一番後ろのさらに後ろにオブジェクトを追加する。
    currentCharacterObject->SetNextCharacterObject(characterObject);
    characterObject->SetPrevCharacterObject(currentCharacterObject);
    mpCharacterObjectL = characterObject;
}

/*
* @fn CharacterDelete
* @drief リストからキャラクターオブジェクトを除外
*/
void ObjectManager::CharacterDelete(Object_Base_Character *characterObject)
{
    // 最初のオブジェクトすらない場合は何もしない。
    if (mpCharacterObject == nullptr)
    {
        return;
    }

    // もし最初のオブジェクトだった場合は特別な処理をする。
    if (mpCharacterObject == characterObject)
    {
        Object_Base_Character *next = mpCharacterObject->GetNextCharacterObject();
        if (next != nullptr)
        {
            next->SetPrevCharacterObject(nullptr);
            mpCharacterObject = next;
        }
        else {
            mpCharacterObject = nullptr;
            mpCharacterObjectL = nullptr;
        }
        return;
    }

    // 以下、最初のオブジェクトではなかった場合の処理

    // 削除対象のオブジェクトを探索する
    Object_Base_Character *target = mpCharacterObject->GetNextCharacterObject();
    while (target != characterObject)
    {
        if (target == mpCharacterObjectL)
        {
            return;             // 見つからなかった場合なので、苦肉の策でリターン。
        }
        target = target->GetNextCharacterObject();
    }

    // 削除対象のオブジェクトの前と後ろを繋げるために、一旦確保しておく
    Object_Base_Character *prev = target->GetPrevCharacterObject();
    Object_Base_Character *next = target->GetNextCharacterObject();

    // mpCharacterObjectLが削除対象だった場合、削除対象のひとつ前をmpCharacterObjectLにする必要がある。
    if (target == nullptr)//mpCharacterObjectL)
    {
        mpCharacterObjectL = prev;
    }

    // 削除対象のオブジェクトの前後を繋げ、削除対象を孤立させる
    prev->SetNextCharacterObject(next);
    if (next != nullptr)
    {
        next->SetPrevCharacterObject(prev);
    }
}

/*
* @fn FindByTag_CharacterObject
* @drief タグからキャラクターオブジェクトを取得
*/
Object_Base_Character *ObjectManager::FindByTag_CharacterObject(int tag, bool flag)
{
    // 何も生成してないなら何もしない
    if (mpCharacterObject == nullptr)
    {
        return mpCharacterObject;
    }

    Object_Base_Character *workObject = mpCharacterObject;
    do {
        if ((!(workObject->IsDeleteFlag())) || flag) {
            if (tag == workObject->GetTag())
            {
                return workObject;
            }
        }
        workObject = workObject->GetNextCharacterObject();
    } while (workObject != nullptr);
    return workObject;
}

/*
* @fn FindsByTag_CharacterObject
* @drief タグから複数キャラクターオブジェクトを取得
*/
std::vector<Object_Base_Character *>ObjectManager::FindsByTag_CharacterObject(int tag, bool flag)
{
    std::vector<Object_Base_Character *> result;

    // 最初のオブジェクトがないなら何もしない
    if (mpCharacterObject == nullptr)
    {
        return result;
    }

    Object_Base_Character *target = mpCharacterObject;
    do {

        Object_Base_Character *next = target->GetNextCharacterObject();
        if ((!(target->IsDeleteFlag())) || flag) {
            if (tag == target->GetTag())
            {
                result.push_back(target);
            }
        }
        target = next;

    } while (target != nullptr);

    // 見つけた物を返す
    return result;
}

/*
* @fn AddFixed
* @drief リストに固定オブジェクトを追加
*/
void ObjectManager::AddFixed(Object_Base_Fixed *fixedObject)
{
    if (mpFixedObject == nullptr)
    {
        mpFixedObject = fixedObject;
        mpFixedObjectL = fixedObject;
        return;
    }

    // 一番後ろの場所を探している。
    Object_Base_Fixed *currentFixedObject = mpFixedObject;
    Object_Base_Fixed *nextFixedObject = mpFixedObject->GetNextFixedObject();
    while (nextFixedObject != nullptr)
    {
        currentFixedObject = nextFixedObject;
        nextFixedObject = currentFixedObject->GetNextFixedObject();
    }

    // 一番後ろのさらに後ろにオブジェクトを追加する。
    currentFixedObject->SetNextFixedObject(fixedObject);
    fixedObject->SetPrevFixedObject(currentFixedObject);
    mpFixedObjectL = fixedObject;
}

/*
* @fn FixedDelete
* @drief リストから固定オブジェクトを除外
*/
void ObjectManager::FixedDelete(Object_Base_Fixed *fixedObject)
{
    // 最初のオブジェクトすらない場合は何もしない。
    if (mpFixedObject == nullptr)
    {
        return;
    }

    // もし最初のオブジェクトだった場合は特別な処理をする。
    if (mpFixedObject == fixedObject)
    {
        Object_Base_Fixed *next = mpFixedObject->GetNextFixedObject();
        if (next != nullptr)
        {
            next->SetPrevFixedObject(nullptr);
            mpFixedObject = next;
        }
        else {
            mpFixedObject = nullptr;
            mpFixedObjectL = nullptr;
        }
        return;
    }

    // 以下、最初のオブジェクトではなかった場合の処理

    // 削除対象のオブジェクトを探索する
    Object_Base_Fixed *target = mpFixedObject->GetNextFixedObject();
    while (target != fixedObject)
    {
        if (target == mpFixedObjectL)
        {
            return;             // 見つからなかった場合なので、苦肉の策でリターン。
        }
        target = target->GetNextFixedObject();
    }

    // 削除対象のオブジェクトの前と後ろを繋げるために、一旦確保しておく
    Object_Base_Fixed *prev = target->GetPrevFixedObject();
    Object_Base_Fixed *next = target->GetNextFixedObject();

    // mpFixedObjectLが削除対象だった場合、削除対象のひとつ前をmpFixedObjectLにする必要がある。
    if (target == nullptr)//mpFixedObjectL)
    {
        mpFixedObjectL = prev;
    }

    // 削除対象のオブジェクトの前後を繋げ、削除対象を孤立させる
    prev->SetNextFixedObject(next);
    if (next != nullptr)
    {
        next->SetPrevFixedObject(prev);
    }
    /*
    else
    {
        next->SetPrevObject(nullptr);
    }
    */
}

/*
* @fn FindByTag_FixedObject
* @drief タグから固定オブジェクトを取得
*/
Object_Base_Fixed *ObjectManager::FindByTag_FixedObject(int tag, bool flag)
{
    // 何も生成してないなら何もしない
    if (mpFixedObject == nullptr)
    {
        return mpFixedObject;
    }

    Object_Base_Fixed *workObject = mpFixedObject;
    do {
        if ((!(workObject->IsDeleteFlag())) || flag) {
            if (tag == workObject->GetTag())
            {
                return workObject;
            }
        }
        workObject = workObject->GetNextFixedObject();
    } while (workObject != nullptr);
    return workObject;
}

/*
* @fn FindsByTag_FixedObject
* @drief タグから複数固定オブジェクトを取得
*/
std::vector<Object_Base_Fixed *>ObjectManager::FindsByTag_FixedObject(int tag, bool flag)
{
    std::vector<Object_Base_Fixed *> result;

    // 最初のオブジェクトがないなら何もしない
    if (mpFixedObject == nullptr)
    {
        return result;
    }

    Object_Base_Fixed *target = mpFixedObject;
    do {

        Object_Base_Fixed *next = target->GetNextFixedObject();
        if ((!(target->IsDeleteFlag())) || flag) {
            if (tag == target->GetTag())
            {
                result.push_back(target);
            }
        }
        target = next;

    } while (target != nullptr);

    // 見つけた物を返す
    return result;
}

/*
* @fn FixedObjectHitCheck
* @drief 固定オブジェクトに当たっているかチェック
* @detail キャラクターなど移動した時に固定物に当たらない場所までの移動量を返す
*/
VECTOR ObjectManager::FixedObjectHitCheck(VECTOR checkPosition, VECTOR noePosition, VECTOR moveVec, float size)
{
    VECTOR move = VGet(0.0f, 0.0f, 0.0f);

    if (mpFixedObject == nullptr) {
        return move;
    }

    // 当たらない移動量を取得
    Object_Base_Fixed *checkObject = mpFixedObject;
    do {

        Object_Base_Fixed *next = checkObject->GetNextFixedObject();
        
        move = VAdd(checkObject->CheckHit_ReturnAmountMoved(VAdd(checkPosition, move), noePosition, moveVec, size), move);


        checkObject = next;

    } while (checkObject != nullptr);

    return move;
}


/*
* @fn DeleteSceneObject
* @drief 指定したシーンで生成されたオブジェクトの削除フラグ有効にする
*/
void ObjectManager::SetDeleteSceneObject(SCENE targetScene)
{
    // 最初のオブジェクトがないなら何もしない
    if (mpObject == nullptr)
    {
        return;
    }


    Object_Base *target = mpObject;
    do {

        Object_Base *next = target->GetNextObject();
        if (targetScene == target->GetObjectScene())
        {
            target->SetDeleteFlag(true);
        }
        target = next;

    } while (target != nullptr);

}

/*
* @f DeleteAll
* @drief オブジェクト全削除を行う
* @detail シーンが終了される時など、全削除が必要な場合はこちらを呼び出す
*/
void ObjectManager::DeleteAll()
{
    // 最初のオブジェクトがないなら何もしない
    if (mpObject == nullptr)
    {
        return;
    }

    // オブジェクトの全削除
    Object_Base *target = mpObject;
    do
    {
        Object_Base *next = target->GetNextObject();
        Delete(target);
        target = next;
    } while (target != nullptr);
}

/*
* @f DeleteAllIfNeeded
* @drief 必要であればオブジェクト削除を行う
* @detail 全オブジェクトのUpdate後に呼び出す
*         そうすることで、他のオブジェクトへの干渉が少なくなり、より安全な処理が行える
*/
void ObjectManager::DeleteAllIfNeeded()
{
    // 最初のオブジェクトがないなら何もしない
    if (mpObject == nullptr)
    {
        return;
    }

    // 削除フラグが立っているオブジェクトを順番に削除
    Object_Base *target = mpObject;
    do
    {
        Object_Base *next = target->GetNextObject();
        if (target->IsDeleteFlag())
        {
            Delete(target);
        }
        target = next;
    } while (target != nullptr);
}





/*
    オブジェクト管理クラス

    基本的には1つのシーンに1つのオブジェクト管理クラスを用意する。
*/

/**
* @fn コンストラクタ
*//*
ObjectManager::ObjectManager() : mpObject(nullptr)
{
}

/**
* @fn デストラクタ
*//*
ObjectManager::~ObjectManager()
{
}

/**
* @fn Initialize
* @drief 初期化処理
*//*
void ObjectManager::Initilize()
{

}

/**
* @fn Update
* @drief 更新処理
*//*
void ObjectManager::Update()
{
    // 何も生成してないなら何もしない
    if (mpObject == nullptr)
    {
        return;
    }

    Object_Base *workObject = mpObject;
    do {
        workObject->Update();
        workObject = workObject->GetNextObject();
    } while (workObject != nullptr);
}

/**
* @fn Draw
* @drief 描画処理
*//*
void ObjectManager::Draw()
{
    // 何も生成してないなら何もしない
    if (mpObject == nullptr)
    {
        return;
    }

    Object_Base *workObject = mpObject;
    do {
        workObject->Draw();
        workObject = workObject->GetNextObject();
    } while (workObject != nullptr);
}

/**
* @fn Finalize
* @drief 終了処理
*//*
void ObjectManager::Finalize()
{

}

/*
* @fn Add
* @drief オブジェクト追加
*//*
void ObjectManager::Add(Object_Base *object)
{
    // もし最初のオブジェクトがないならそのまま入れる
    if (mpObject == nullptr)
    {
        mpObject = object;
        return;
    }

    // NextObject が null になっているものを探索
    Object_Base *currentObject = mpObject;
    Object_Base *nextObject = mpObject->GetNextObject();
    while (nextObject != nullptr)
    {
        currentObject = nextObject;
        nextObject = currentObject->GetNextObject();
    }

    // 見つけたらオブジェクトをセット
    currentObject->SetNextObject(object);
    object->SetPrevObject(currentObject);
}

/*
* @fn Add
* @drief オブジェクトの削除
* @detail オブジェクトを直接削除したいときはこれを呼ぶ。
*         が、基本手的には削除フラグを立たせておいて、全てのオブジェクトのUpdateの後にまとめて削除
*//*
void ObjectManager::Delete(Object_Base *object)
{
    // 最初のオブジェクトがないなら何もしない
    if (mpObject == nullptr)
    {
        return;
    }

    // もし最初のオブジェクトが削除対象であれば専用処理をい行う
    if (mpObject == object)
    {
        Object_Base *next = mpObject->GetNextObject();
        if (next != nullptr)
        {
            next->SetNextObject(nullptr);
            mpObject = next;
        }

        object->Finalize();
        delete object;
        return;
    }

    // 削除対象のオブジェクトを探索
    Object_Base *target = mpObject->GetNextObject();
    while (target != object)
    {
        // 次のオブジェクトがnullの場合は探索が終わる (削除処理もしないのでreturnしておく)
        if (target == nullptr)
        {
            return;
        }
        target = target->GetNextObject();
    }

    // 削除対象を見つけたら、その手前と次のオブジェクトを取得しておく
    Object_Base *prev = target->GetNextObject();
    Object_Base *next = target->GetNextObject();

    // 前後のつながりを設定
    prev->SetNextObject(next);
    if (next != nullptr)
    {
        next->SetNextObject(prev);
    }

    // 整合性が取れたところで削除対象を削除
    target->Finalize();
    delete target;
    target = nullptr;
}*/