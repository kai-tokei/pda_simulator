#include <iostream>
#include "pda.cpp"
#include "utils.cpp"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        cerr << "Error: Not enough arguments" << endl;
        return 0;
    }

    // プッシュダウンオートマトンを読み込み
    vector<PDA> pdas;
    pdas.push_back(read_graph_from_file(argv[1]));

    // 入力列を読み込み
    string input = argv[2];

    // オートマトンを実行

    return 0;
}
