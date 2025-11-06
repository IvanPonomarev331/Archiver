#pragma once

#include "reader.h"

const int HALF_CHAR = 128;
const int CHAR = 256;

std::string ToBinary(int n);

class Writer {

public:
    explicit Writer(std::ostream &out);

    void WriteOneBit(int symbol);

    void WriteNineBit(std::string s);

    void WriteString(std::string s);

    void ClearBuffer();

private:
    std::ostream &out_;
    int buffer_ = 0;
    int cnt_ = 0;
};

void WriteSymbol(std::ostream &out, char symbol);

void WriteFile(Writer &writer, std::string &filename, std::vector<std::pair<int, std::string> > &code, bool last);