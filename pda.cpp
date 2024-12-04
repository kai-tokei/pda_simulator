#pragma once
#include <string>
#include <vector>
#include <set>
#include <map>

#include "transition.cpp"

using namespace std;

// グラフデータの入力フォーマット
/*
N (グラフの頂点の数)
q0 (初期状態)
z0 (初期スタック記号)
0,0:a:Z/ZA
(input):(from):(to):(stackのbackの記号)/(pushする記号)  <- pushの場合
(input):(from):(to):(stackのbackの記号)/(e)  <- popの場合
*/

/*
プッシュダウンオートマトンの性質上
Vertex構造体を作るよりも
Navigation構造体を使い
現在の遷移状態をポインタとして保持した方が、柔軟性が高いのではないか？
ポインタを持つ主体としてのPDAが、進行に伴い分裂していく？
*/

struct PDA
{
    // 状態集合Qは、idとしてのみ保持する
    string q;                              // 現在の状態
    vector<string> ganma;                  // スタック記号集合
    map<string, vector<Transition>> delta; // 状態遷移函数の集合(入力記号:それに関する状態遷移函数)
    string q0;                             // 初期状態
    string z0;                             // 最初のスタックに記録されるスタック記号

    PDA(int _q0, string _z0)
    {
        q0 = _q0;
        z0 = _z0;
        q = q0;
    }

    // 遷移先を追加する
    void add_transition(string key, Transition transition)
    {
        delta[key].push_back(transition);
    }

    // シリアライズ
    string to_str()
    {
        string out;
        for (const auto d : delta)
        {
            for (const Transition &t : d.second)
            {
                out += d.first + ":" + t.from + ":" + t.to + ":" + t.r_str + "/" + t.p_str + "\n";
            }
        }
        return out;
    }
};
