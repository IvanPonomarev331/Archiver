#pragma once

#include "include.h"

class Reader {

public:
    explicit Reader(std::istream &in);

    bool ReadOneBit();

    std::bitset<SIZE> ReadNineBits();

private:
    std::istream &in_;
    char buffer_ = 0;
    int cnt_ = 0;
};

bool Get(std::istream &in, std::string &buffer, size_t cnt);

std::unordered_map<int, int> GetStatistics(std::istream &in, std::string &filename);