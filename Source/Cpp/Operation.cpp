#include "DxLib.h"
#include "../Header/Operation.h"

/*
* @drief 上ボタン状態取得
*/
bool Operation::CheckUpKey()
{
    bool flag = false;

    flag |= (CheckHitKey(KEY_INPUT_UP) == 1);
    flag |= (CheckHitKey(KEY_INPUT_W) == 1);

    flag |= ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP) != 0);

    return flag;
}
/*
* @drief 下ボタン状態取得
*/
bool Operation::CheckDownKey()
{
    bool flag = false;

    flag |= (CheckHitKey(KEY_INPUT_DOWN) == 1);
    flag |= (CheckHitKey(KEY_INPUT_S) == 1);

    flag |= ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN) != 0);

    return flag;
}
/*
* @drief 右ボタン状態取得
*/
bool Operation::CheckRightKey()
{
    bool flag = false;

    flag |= (CheckHitKey(KEY_INPUT_RIGHT) == 1);
    flag |= (CheckHitKey(KEY_INPUT_D) == 1);

    flag |= ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT) != 0);

    return flag;
}
/*
* @drief 左ボタン状態取得
*/
bool Operation::CheckLeftKey()
{
    bool flag = false;

    flag |= (CheckHitKey(KEY_INPUT_LEFT) == 1);
    flag |= (CheckHitKey(KEY_INPUT_A) == 1);

    flag |= ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT) != 0);

    return flag;
}

/*
* @drief Lボタン状態取得
*/
bool Operation::CheckLKey()
{
    bool flag = false;

    flag |= (CheckHitKey(KEY_INPUT_Q) == 1);

    flag |= ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_5) != 0);

    return flag;
}
/*
* @drief Rボタン状態取得
*/
bool Operation::CheckRKey()
{
    bool flag = false;

    flag |= (CheckHitKey(KEY_INPUT_E) == 1);

    flag |= ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_6) != 0);

    return flag;
}

/*
* @drief Aボタン状態取得
*/
bool Operation::CheckAKey()
{
    bool flag = false;

    flag |= (CheckHitKey(KEY_INPUT_L) == 1);
    flag |= (CheckHitKey(KEY_INPUT_RETURN) == 1);

    flag |= ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_2) != 0);

    return flag;
}
/*
* @drief Bボタン状態取得
*/
bool Operation::CheckBKey()
{
    bool flag = false;

    flag |= (CheckHitKey(KEY_INPUT_BACK) == 1);

    flag |= ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0);

    return flag;
}
/*
* @drief Xボタン状態取得
*/
bool Operation::CheckXKey()
{
    bool flag = false;

    flag |= (CheckHitKey(KEY_INPUT_X) == 1);

    flag |= ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_4) != 0);

    return flag;
}
/*
* @drief Yボタン状態取得
*/
bool Operation::CheckYKey()
{
    bool flag = false;

    flag |= (CheckHitKey(KEY_INPUT_Y) == 1);

    flag |= ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_3) != 0);

    return flag;
}