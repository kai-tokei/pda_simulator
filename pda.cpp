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
    int q;                                 // 現在の状態
    vector<string> ganma;                  // スタック記号集合
    map<string, vector<Transition>> delta; // 状態遷移函数の集合(入力記号:それに関する状態遷移函数)
    set<int> acceptance;                   // 受理するオートマトン
    vector<string> log;                    // 遷移の記録

    PDA(int _q0, string _z0, set<int> _acceptance)
    {
        q = _q0;
        ganma.push_back(_z0);
    }

    // 遷移可能かどうか
    bool can_trans(Transition transition)
    {
        return (q == transition.from) && (transition.r_str == ganma.back());
    }

    // 遷移先の選択は上位層に行ってもらう
    void trans(string key, Transition transition)
    {
        // 状態を更新し、stack
        q = transition.to;

        // スタック制御
        if (transition.p_str != "")
        {
            if (transition.p_str == "ε")
            {
                ganma.pop_back();
            }
            else
            {
                ganma.push_back(transition.p_str);
            }
        }

        // 記録をとる
        string record = "";
        record += to_string(q) + "," + key + "," + to_string(transition.to) + ",";
        for (const string &v : ganma)
        {
            record += v + ":";
        }
        log.push_back(record);
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
        out += q + "\n";
        out += ganma.back() + "\n";
        for (const auto d : delta)
        {
            for (const Transition &t : d.second)
            {
                out += d.first + ":" + to_string(t.from) + ":" + to_string(t.to) + ":" + t.r_str + "/" + t.p_str + "\n";
            }
        }
        return out;
    }
};
