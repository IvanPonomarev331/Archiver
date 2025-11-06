#pragma once

#include "include.h"

class Node {
public:
    int val;
    int symbol = -1;

    Node *l = nullptr;
    Node *r = nullptr;

    Node();

    Node(int val, int symbol);

    bool operator<(const Node &v) const;

    bool operator>(const Node &v) const;
};

void Dfs(Node *&v, int length, std::unordered_map<int, int> &code);

void Destruct(Node *&v);

void Add(Node *&root, const int symbol, std::string &code);