#include "encoder.h"

std::vector<std::pair<int, std::string> > Encode(std::istream &in, std::unordered_map<int, int> &cnt,
                                                 std::string &filename) {
    Heap<Node> prior_queue;
    for (auto &[symbol, val] : cnt) {
        prior_queue.Push(new Node(val, symbol));
    }
    while (prior_queue.Size() > 1) {
        Node *min1 = prior_queue.Get();
        Node *min2 = prior_queue.Get();
        Node *new_node = new Node(min1->val + min2->val, std::min(min1->symbol, min2->symbol));
        new_node->l = min1;
        new_node->r = min2;
        prior_queue.Push(new_node);
    }

    Node *root = prior_queue.Get();
    std::unordered_map<int, int> code;
    Dfs(root, 0, code);
    Destruct(root);

    std::vector<std::pair<int, int> > sizes;
    for (auto &p : code) {
        sizes.emplace_back(p.second, p.first);
    }
    std::sort(sizes.begin(), sizes.end());
    std::vector<std::pair<int, std::string> > norm_code;
    int cur_code = 0;
    for (size_t i = 0; i < sizes.size(); ++i) {
        std::string bin_code;
        int k = cur_code;
        while (k > 0) {
            bin_code += static_cast<char>('0' + (k & 1));
            k >>= 1;
        }
        std::reverse(bin_code.begin(), bin_code.end());
        while (bin_code.size() < sizes[i].first) {
            bin_code = '0' + bin_code;
        }
        norm_code.emplace_back(sizes[i].second, bin_code);
        if (i + 1 != sizes.size()) {
            cur_code = ((cur_code + 1) << (sizes[i + 1].first - sizes[i].first));
        }
    }
    return norm_code;
}