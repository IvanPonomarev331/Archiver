#include "reader.h"

Reader::Reader(std::istream &in) : in_(in) {
}

bool Reader::ReadOneBit() {
    if (cnt_ == 0) {
        char buffer1 = 0;
        in_.get(buffer1);
        buffer_ = buffer1;
    }
    bool result = (buffer_ & 1);
    buffer_ >>= 1;
    cnt_ = (cnt_ + 1) % BUFFER_SIZE;
    return result;
}

std::bitset<SIZE> Reader::ReadNineBits() {
    std::bitset<SIZE> result;
    for (int i = 0; i < SIZE; ++i) {
        result[i] = ReadOneBit();
    }
    return result;
}

bool Get(std::istream &in, std::string &buffer, size_t cnt) {
    buffer.clear();
    char symbol = 0;
    while (cnt > 0 && in.get(symbol)) {
        buffer += symbol;
        --cnt;
    }
    return cnt == 0;
}

std::unordered_map<int, int> GetStatistics(std::istream &in, std::string &filename) {
    std::unordered_map<int, int> res;
    std::string buffer;
    while (Get(in, buffer, 1)) {
        ++res[buffer[0]];
    }
    for (auto symbol : filename) {
        ++res[symbol];
    }
    res[FILENAME_END] = res[ONE_MORE_FILE] = res[ARCHIVE_END] = 1;
    return res;
}