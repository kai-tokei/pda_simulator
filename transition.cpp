#pragma once
#include <string>

using namespace std;

// 状態遷移函数
struct Transition
{
    int from;     // 遷移元
    int to;       // 遷移先
    string r_str; // スタックで読み取る記号
    string p_str; // スタックに積む記号

    // 遷移可能か
    bool can_trans(string stack_front)
    {
        return r_str == stack_front;
    }

    bool operator<(const Transition &trans) const
    {
        return to > trans.to;
    }
};
