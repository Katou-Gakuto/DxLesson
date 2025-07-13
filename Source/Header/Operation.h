#pragma once

// 操作用クラス
class Operation
{
public:
    /// <summary>
    /// 上
    /// </summary>
    static bool CheckUpKey();
    /// <summary>
    /// 下
    /// </summary>
    static bool CheckDownKey();
    /// <summary>
    /// 右
    /// </summary>
    static bool CheckRightKey();
    /// <summary>
    /// 左
    /// </summary>
    static bool CheckLeftKey();

    /// <summary>
    /// L
    /// </summary>
    static bool CheckLKey();
    /// <summary>
    /// R
    /// </summary>
    static bool CheckRKey();

    /// <summary>
    /// A
    /// </summary>
    static bool CheckAKey();
    /// <summary>
    /// B
    /// </summary>
    static bool CheckBKey();
    /// <summary>
    /// X
    /// </summary>
    static bool CheckXKey();
    /// <summary>
    /// Y
    /// </summary>
    static bool CheckYKey();

};