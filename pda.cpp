#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;

// グラフデータの入力フォーマット
/*
N (グラフの頂点の数)
0,0:a:Z/ZA
(input):(from):(to):(stackのbackの記号)/(pushする記号)  <- pushの場合
(input):(from):(to):(stackのbackの記号)/(e)  <- popの場合
*/

/*
プッシュダウンオートマトンの性質上
Vertex構造体を作るよりも
Navigation構造体を使い
現在の遷移状態をポインタとして保持した方が、柔軟性が高いのではないか？
ポインタを持つ主体としてのPDAが世界線に合わせて分裂していく？
*/

// 状態遷移函数
struct Transition
{
    string input; // 入力
    string str;   // スタック記号
    string to;    // 遷移先
};

struct PDA
{
    // 状態集合Qは、idとしてのみ保持する
    string sigma;                       // 入力記号集合
    vector<string> ganma;               // スタック記号集合
    map<string, set<Transition>> delta; // 状態遷移函数の集合
    string q0;                          // 初期状態
    string z0;                          // 最初のスタックに記録されるスタック記号
};
