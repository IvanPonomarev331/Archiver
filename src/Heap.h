#pragma once

#include "include.h"

template <typename T>
class Heap {

public:
    Heap() {
        tree_.resize(1);
    }

    ~Heap() {
    }

    bool Empty() {
        return sz_ != 0;
    }

    T* Get() {
        T* result = tree_[1];
        std::swap(tree_[1], tree_[sz_]);
        tree_.resize(sz_);
        --sz_;
        size_t v = 1;
        while (v * 2 <= sz_) {
            if (v * 2 + 1 <= sz_) {
                if (*tree_[v * 2] < *tree_[v * 2 + 1] && *tree_[v * 2] < *tree_[v]) {
                    std::swap(tree_[v], tree_[v * 2]);
                    v = v * 2;
                } else if (*tree_[v * 2 + 1] < *tree_[v * 2] && *tree_[v * 2] < *tree_[v]) {
                    std::swap(tree_[v], tree_[v * 2 + 1]);
                    v = v * 2 + 1;
                } else {
                    break;
                }
            } else {
                if (*tree_[v * 2] < *tree_[v]) {
                    std::swap(tree_[v], tree_[v * 2]);
                    v = v * 2;
                } else {
                    break;
                }
            }
        }
        return result;
    }

    void Push(T* node) {
        if (sz_ + 1 >= tree_.size()) {
            tree_.push_back(node);
        } else {
            tree_[sz_ + 1] = node;
        }
        ++sz_;
        size_t v = sz_;
        while (v > 1) {
            if (*tree_[v] < *tree_[v / 2]) {
                std::swap(tree_[v], tree_[v / 2]);
                v /= 2;
            } else {
                break;
            }
        }
    }

    int Size() {
        return sz_;
    }

private:
    size_t sz_ = 0;
    std::vector<T*> tree_;
};