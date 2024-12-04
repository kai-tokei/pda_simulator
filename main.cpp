#include <iostream>
#include "pda.cpp"
#include "utils.cpp"

using namespace std;

int main()
{
    // プッシュダウンオートマトンを読み込み
    vector<PDA> pdas;
    pdas.push_back(read_graph_from_file("./sub.txt"));

    cout << pdas[0].to_str();

    return 0;
}
