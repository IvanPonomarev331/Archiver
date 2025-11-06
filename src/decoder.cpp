#include "decoder.h"

void CheckFlag(bool &flag) {
    if (!flag) {
        exit(EXIT_CODE);
    }
}

void CheckInt(int a, int b) {
    if (a > b) {
        exit(EXIT_CODE);
    }
}

int ToInt(std::bitset<SIZE> &b) {
    int result = 0;
    for (size_t i = 0; i < SIZE; ++i) {
        result += (1 << i) * b[i];
    }
    return result;
}

bool DecodeFile(Reader &reader) {
    std::bitset<SIZE> buffer;
    buffer = reader.ReadNineBits();
    // CheckFlag(flag);
    int symbols_count = ToInt(buffer);
    CheckInt(symbols_count, ALPH_SIZE);
    std::vector<int> alph;
    for (int i = 0; i < symbols_count; ++i) {
        buffer = reader.ReadNineBits();
        int symbol = ToInt(buffer);
        CheckInt(symbol, ARCHIVE_END);
        alph.push_back(symbol);
    }

    std::vector<int> length;
    int k = symbols_count;
    for (int i = 0; k > 0; ++i) {
        buffer = reader.ReadNineBits();
        int cnt = ToInt(buffer);
        CheckInt(cnt, k);
        k -= cnt;
        for (int j = 0; j < cnt; ++j) {
            length.push_back(i + 1);
        }
    }
    CheckInt(k, 0);

    std::vector<std::string> code;
    int cur_code = 0;
    for (size_t i = 0; i < symbols_count; ++i) {
        std::string bin_code;
        int num = cur_code;
        while (num > 0) {
            bin_code += static_cast<char>('0' + (num & 1));
            num >>= 1;
        }
        std::reverse(bin_code.begin(), bin_code.end());
        while (bin_code.size() < length[i]) {
            bin_code = '0' + bin_code;
        }
        std::reverse(bin_code.begin(), bin_code.end());
        code.push_back(bin_code);
        if (i + 1 != length.size()) {
            cur_code = ((cur_code + 1) << (length[i + 1] - length[i]));
        }
    }

    Node *root = new Node();
    for (int i = 0; i < symbols_count; i++) {
        Add(root, alph[i], code[i]);
    }

    Node *cur = root;
    std::string filename;
    while (true) {
        int bit = reader.ReadOneBit();
        if (bit == 0) {
            if (cur->l == nullptr) {
                exit(EXIT_CODE);
            }
            cur = cur->l;
        } else {
            if (cur->r == nullptr) {
                exit(EXIT_CODE);
            }
            cur = cur->r;
        }
        if (cur->symbol != -1) {
            if (cur->symbol == FILENAME_END) {
                break;
            }
            CheckInt(cur->symbol, FILENAME_END);
            filename += static_cast<char>(cur->symbol);
            cur = root;
        }
    }

    std::ofstream out(filename.c_str());
    cur = root;
    while (true) {
        int bit = reader.ReadOneBit();
        if (bit == 0) {
            if (cur->l == nullptr) {
                exit(EXIT_CODE);
            }
            cur = cur->l;
        } else {
            if (cur->r == nullptr) {
                exit(EXIT_CODE);
            }
            cur = cur->r;
        }
        if (cur->symbol != -1) {
            if (cur->symbol == ONE_MORE_FILE) {
                Destruct(root);
                return false;
            }
            if (cur->symbol == ARCHIVE_END) {
                Destruct(root);
                return true;
            }
            CheckInt(cur->symbol, MAX_SYMBOL);
            WriteSymbol(out, static_cast<char>(cur->symbol));
            cur = root;
        }
    }
    Destruct(root);
}

void Decode(std::istream &in) {
    Reader reader(in);
    while (true) {
        bool is_last = DecodeFile(reader);
        if (is_last) {
            break;
        }
    }
}