#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include "pda.cpp"

using namespace std;

// slashで分割されたデータを分解する
pair<string, string> get_slash_divided_data(string input)
{
    string l = "", r = "";
    bool slash = false;
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i] == '/')
        {
            slash = true;
        }
        else
        {
            if (slash)
            {
                r += input[i];
            }
            else
            {
                l += input[i];
            }
        }
    }

    return pair<string, string>{l, r};
}

// keyを元に文字列を分割する
vector<string> divide_string(string line, char divider)
{
    stringstream ss(line);
    vector<string> vals;
    string s;

    // コロンで入力文字列を分割する
    while (getline(ss, s, ':'))
    {
        vals.push_back(s);
    }

    return vals;
}

// ファイルからグラフデータを取得する
PDA read_graph_from_file(string file_path)
{
    ifstream file(file_path); // グラフデータのファイル
    string line;              // 入力行

    int N;               // 状態集合の数
    int q0;              // 初期状態のid
    string z0;           // 初期スタック記号
    set<int> acceptance; // 受理する頂点の番号

    // 状態集合の数を取得する
    getline(file, line);
    N = stoi(line);

    // 初期状態を取得
    getline(file, line);
    q0 = stoi(line);

    // 初期スタック記号を取得
    getline(file, line);
    z0 = line;

    // 受理する頂点の番号を取得
    getline(file, line);
    vector<string> node_number = divide_string(line, ',');
    for (const auto &v : node_number)
    {
        acceptance.insert(stoi(v));
    }

    PDA pda(q0, z0); // プッシュダウンオートマトンのインスタンス

    while (getline(file, line))
    {
        // コロンで文字列を分割
        vector<string> vals = divide_string(line, ':');

        string input = vals[0]; // 入力記号
        string from = vals[1];  // 遷移元
        string to = vals[2];    // 遷移先

        pair<string, string> slashed = get_slash_divided_data(vals[3]);

        // スタックに関する記号
        string r_str = slashed.first, p_str = slashed.second;

        // スタックしない遷移の設定
        if (r_str == p_str)
        {
            p_str = "";
        }

        // 遷移先を追加
        pda.add_transition(input, Transition{from, to, r_str, p_str});
    }

    return pda;
}
