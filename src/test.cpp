#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
// #include "headers/include.h"
// #include "headers/encoder.h"
// #include "headers/decoder.h"
// #include "headers/writer.h"
#include "reader.h"

int ToInt(std::bitset<SIZE> &b) {
    int result = 0;
    for (size_t i = 0; i < SIZE; ++i) {
        result += (1 << i) * b[i];
    }
    return result;
}

int main() {
    std::ifstream in("archive");
    char buffer = 0;
    in.get(buffer);
    std::cerr << (int)buffer << '\n';
    in.get(buffer);
    std::cerr << (int)buffer << '\n';
    in.get(buffer);
    std::cerr << (int)buffer << '\n';
    in.get(buffer);
    std::cerr << (int)buffer << '\n';
    in.get(buffer);
    std::cerr << (int)buffer << '\n';
    in.get(buffer);
    std::cerr << (int)buffer << '\n';
    in.get(buffer);
    std::cerr << (int)buffer << '\n';
}