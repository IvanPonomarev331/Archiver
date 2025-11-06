#include "Trie.h"

Node::Node() {
}

Node::Node(int val, int symbol) : val(val), symbol(symbol){};

bool Node::operator<(const Node &v) const {
    return std::make_pair(val, symbol) < std::make_pair(v.val, v.symbol);
}

bool Node::operator>(const Node &v) const {
    return std::make_pair(val, symbol) > std::make_pair(v.val, v.symbol);
}

void Dfs(Node *&v, int length, std::unordered_map<int, int> &code) {
    if (!v->l) {
        code[v->symbol] = length;
        return;
    }
    length++;
    Dfs(v->l, length, code);
    Dfs(v->r, length, code);
}

void Destruct(Node *&v) {
    if (v == nullptr) {
        return;
    }
    if (v->l != nullptr) {
        Destruct(v->l);
    }
    if (v->r != nullptr) {
        Destruct(v->r);
    }
    delete v;
}

void Add(Node *&root, const int symbol, std::string &code) {
    if (code.empty()) {
        root->symbol = symbol;
        return;
    }
    char bit = code.back();
    code.pop_back();
    if (bit == '0') {
        if (!root->l) {
            root->l = new Node();
        }
        Add(root->l, symbol, code);
    } else {
        if (!root->r) {
            root->r = new Node();
        }
        Add(root->r, symbol, code);
    }
}