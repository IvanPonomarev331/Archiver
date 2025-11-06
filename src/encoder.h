#include "include.h"
#include "Trie.h"
#include "Heap.h"
#include "reader.h"

std::vector<std::pair<int, std::string> > Encode(std::istream &in, std::unordered_map<int, int> &cnt,
                                                 std::string &filename);