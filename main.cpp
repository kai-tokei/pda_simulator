#include <iostream>
#include <fstream>
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

    // 記録用ファイルの作成
    ofstream file("log.csv");
    file << "Q,sigma,delta,ganma," << endl;

    // 入力列を読み込み
    string input = argv[2];

    // オートマトンを実行
    for (const char &v : input)
    {
        vector<PDA> next_pdas;
        for (int i = 0; i < pdas.size(); i++)
        {
            for (const Transition &t : pdas[i].delta[string{v}])
            {
                // 遷移する
                if (pdas[i].can_trans(t))
                {
                    PDA p = pdas[i];
                    p.trans(string{v}, t);
                    next_pdas.push_back(p);
                }
            }
            if (pdas[i].delta.count("ε"))
            {
                for (const Transition &t : pdas[i].delta["ε"])
                {
                    // 遷移する
                    if (pdas[i].can_trans(t))
                    {
                        PDA p = pdas[i];
                        p.trans(string{v}, t);
                        next_pdas.push_back(p);
                    }
                }
            }
        }

        // 現在の状況を出力
        for (const PDA &p : next_pdas)
        {
            cout << p.log.back() << endl;
            file << p.log.back() << endl;
        }
        cout << endl;
        file << endl;

        pdas = next_pdas;
    }

    return 0;
}
