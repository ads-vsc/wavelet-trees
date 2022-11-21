#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include <iostream>

namespace wt {

class node {
public:
    std::vector<bool> bitmap;
    node *children[2];

    // Only for debugging. Remove if never used.
    std::string str;

    node() {
        children[0] = children[1] = nullptr;
    }

#ifdef DEBUG
    node(const std::string &s) : str(s) {
        children[0] = children[1] = nullptr;
    }
#endif
};

class wavelet_tree {
    // a_map = short for alphabet map
    using a_map = std::unordered_map<char, uint8_t>;
    using range = std::pair<size_t, size_t>;

    node *root;

    std::string get_alphabet(const std::string &s) const {
        std::unordered_set<char> st(s.begin(), s.end());
        return std::string(st.begin(), st.end());
    }

    a_map get_alphabet_map(const std::string &alphabet) const {
        a_map map;
        uint8_t count = 0;
        for (const char c : alphabet)
            map[c] = ++count; // count goes from 1 to n
        
        return map;
    }

    node* build_node(const std::string &s, const range &_range, const a_map &map) {
        if (_range.first == _range.second)
            return nullptr;

#ifdef DEBUG
        node *_node = new node(s);
#else
        node *_node = new node;
#endif

        std::string s0, s1;
        uint8_t mid = (_range.first + _range.second) / 2;
        for (char c : s) {
            if (map.find(c)->second <= mid) {
                _node->bitmap.push_back(0);
                s0.push_back(c);
            } else {
                _node->bitmap.push_back(1);
                s1.push_back(c);
            }
        }

        _node->children[0] = build_node(s0, {_range.first, mid}, map);
        _node->children[1] = build_node(s1, {mid + 1, _range.second}, map);

        return _node;
    }

public:
    wavelet_tree(const std::string &s) {
        // ephemeral alphabet for tree-building
        // If get_alphabet is not needed separately, then consider merging
        // get_alphabet & get_alphabet_map
        std::string alphabet = get_alphabet(s);
        a_map alpha_map = get_alphabet_map(alphabet);

        //debug
        // std::cout << "alphabet: " << alphabet << std::endl;

        root = build_node(s, {1, alphabet.size()}, alpha_map);
    }

#ifdef DEBUG
    void _traverse(node *_node) {
        if (_node == nullptr)
            return;

        std::cout << _node->str << std::endl;
        for (bool b : _node->bitmap)
            std::cout << b;
        std::cout << std::endl << std::endl;

        _traverse(_node->children[0]);
        _traverse(_node->children[1]);
    }

    void traverse() {
        _traverse(root);
    }
#endif
};

}