#include "writer.h"

std::string ToBinary(int n) {
    std::string result;
    if (n < 0) {
        n += CHAR;
    }
    while (n > 0) {
        result += static_cast<char>('0' + (n & 1));
        n >>= 1;
    }
    while (result.size() < SIZE) {
        result += '0';
    }
    return result;
}

Writer::Writer(std::ostream &out) : out_(out) {
}

void Writer::WriteOneBit(int symbol) {
    symbol <<= cnt_;
    buffer_ |= symbol;
    ++cnt_;
    if (cnt_ == BUFFER_SIZE) {
        if (buffer_ >= HALF_CHAR) {
            buffer_ -= CHAR;
        }
        out_ << static_cast<char>(buffer_);
        buffer_ = 0;
        cnt_ = 0;
    }
}

void Writer::WriteNineBit(std::string s) {
    for (int i = 0; i < SIZE; ++i) {
        WriteOneBit(s[i] - '0');
    }
}

void Writer::WriteString(std::string s) {
    for (size_t i = 0; i < s.size(); ++i) {
        WriteOneBit(s[i] - '0');
    }
}

void Writer::ClearBuffer() {
    if (buffer_ >= HALF_CHAR) {
        buffer_ -= CHAR;
    }
    out_ << static_cast<char>(buffer_);
    buffer_ = 0;
    cnt_ = 0;
}

void WriteSymbol(std::ostream &out, char symbol) {
    out << symbol;
}

void WriteFile(Writer &writer, std::string &filename, std::vector<std::pair<int, std::string> > &code, bool last) {
    int symbols_count = static_cast<int>(code.size());
    writer.WriteNineBit(ToBinary(symbols_count));
    std::unordered_map<int, std::string> symbol_code;
    int max_size = 0;
    for (auto &[symbol, sc] : code) {
        symbol_code[symbol] = sc;
        max_size = std::max(max_size, static_cast<int>(sc.size()));
    }
    std::vector<int> cnt_of_length(max_size);
    for (auto &[symbol, sc] : code) {
        ++cnt_of_length[static_cast<int>(sc.size()) - 1];
    }
    for (int i = 0; i < symbols_count; ++i) {
        writer.WriteNineBit(ToBinary(code[i].first));
    }
    for (int i = 0; i < max_size; ++i) {
        writer.WriteNineBit(ToBinary(cnt_of_length[i]));
    }
    for (auto symbol : filename) {
        writer.WriteString(symbol_code[symbol]);
    }
    writer.WriteString(symbol_code[FILENAME_END]);
    std::string file = "" + filename;
    std::ifstream in(file.c_str());
    std::string s;
    while (Get(in, s, 1)) {
        writer.WriteString(symbol_code[s.front()]);
        s.pop_back();
    }
    if (last) {
        writer.WriteString(symbol_code[ARCHIVE_END]);
    } else {
        writer.WriteString(symbol_code[ONE_MORE_FILE]);
    }
}