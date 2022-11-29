#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <utility>
#include <iomanip>
#include <iostream>

namespace wt {

class node {
public:
    std::vector<bool> bitmap;
    std::vector<size_t> rank_0;
    node *children[2];

#ifdef DEBUG
    std::string str;
#endif

    node() {
        children[0] = children[1] = nullptr;
    }

#ifdef DEBUG
    node(const std::string &s) : str(s) {
        children[0] = children[1] = nullptr;
    }
#endif
};

class bin_util {
public:
    static size_t rank(bool b, const std::vector<bool> &bitmap, size_t index) {
        if (b) return index - rank(0, bitmap, index) + 1;

        size_t count = 0;
        for (size_t i = 0; i <= index; ++i)
            count += (!bitmap[i]);
        return count;
    }

    static size_t select(bool b, const std::vector<bool> &bitmap, size_t rank) {
        size_t index = 0, count = 0;
        while (count < rank) {
            if (bitmap[index++] == b) ++count;
        }
        return index - 1;
    }
};

class wavelet_tree {
    // a_map = short for alphabet map
    using a_map = std::unordered_map<char, uint8_t>;
    using range = std::pair<size_t, size_t>;

    node *root;
    std::string alphabet;
    a_map alpha_map;

    void build_alphabet_map(const std::string &s) {
        std::set<char> st(s.begin(), s.end());
        alphabet = std::string(st.begin(), st.end());

        uint8_t count = 0;
        for (const char c : alphabet)
            alpha_map[c] = ++count; // count goes from 1 to n
    }

    node* build_node(const std::string &s, const range &_range) {
        if (_range.first == _range.second)
            return nullptr;

#ifdef DEBUG
        node *_node = new node(s);
#else
        node *_node = new node;
#endif

        size_t s_len = s.length();
        std::string s0, s1;
        auto& bitmap = _node->bitmap;
        auto& rank_0 = _node->rank_0;
        bitmap.resize(s_len);
        rank_0.resize(s_len);
        size_t rank_0_so_far = 0;

        uint8_t mid = (_range.first + _range.second) / 2;
        for (size_t i = 0; i < s_len; ++i) {
            char c = s[i];
            if (alpha_map[c] <= mid) {
                bitmap[i] = 0;
                rank_0_so_far++;
                s0.push_back(c);
            } else {
                bitmap[i] = 1;
                s1.push_back(c);
            }
            rank_0[i] = rank_0_so_far;
        }

        _node->children[0] = build_node(s0, {_range.first, mid});
        _node->children[1] = build_node(s1, {mid + 1, _range.second});

        return _node;
    }

    void destroy_node(const node *_node) {
        if (_node == nullptr)
            return;

        destroy_node(_node->children[0]);
        destroy_node(_node->children[1]);

        delete _node;
    }


public:
    wavelet_tree(const std::string &s) {
        build_alphabet_map(s);

#ifdef DEBUG
        std::cout << "alphabet: '" << alphabet << '\'' << std::endl << std::endl;
#endif
        root = build_node(s, {1, alphabet.size()});
        
    }

    ~wavelet_tree() {
        destroy_node(root);
    }

    size_t rank(char c, size_t index) const {
        node *_node = root;
        range _range = {1, alphabet.size()};
        // TODO: handle c not in map => if (!alpha_map.count(c))
        uint8_t symbol_num = alpha_map.at(c);
        size_t r;

        while (_node) {
            uint8_t mid = (_range.first + _range.second) / 2;
            bool b = symbol_num > mid;
            // bin_util::rank returns count; so subtract 1 to use as index in bitmap
            r = index = bin_util::rank(b, _node->bitmap, index) - 1;
            _node = _node->children[b];

            // update range
            b ? _range.first = mid + 1 : _range.second = mid;
        }

        assert(_range.first == _range.second);
        // Add 1 back to rank as it should be a count
        return r + 1;
    }

    size_t _select(const node *_node, range &_range, char c, size_t rank) const {
        if (!_node) {
            assert(_range.first == _range.second);
            return rank;
        }

        uint8_t mid = (_range.first + _range.second) / 2;
        // TODO: handle c not in map => if (!alpha_map.count(c))
        bool b = alpha_map.at(c) > mid;
        // update range
        b ? _range.first = mid + 1 : _range.second = mid;
        rank = _select(_node->children[b], _range, c, rank);
        // Value returned by _select is an index. Add 1 to get rank.
        return bin_util::select(b, _node->bitmap, rank + 1);
    }

    size_t select(char c, size_t rank) const {
        range _range = {1, alphabet.size()};
        // Treat rank as index instead of count to simplify select operation
        return _select(root, _range, c, rank - 1);
    }

    char access(size_t index) const {
        node *_node = root;
        range _range = {1, alphabet.size()};
        
        while (_node) {
            bool b = _node->bitmap[index];
            // bin_util::rank returns count; so subtract 1 to use as index in bitmap
            index = bin_util::rank(b, _node->bitmap, index) - 1;
            _node = _node->children[b];
            
            // update range
            uint8_t mid = (_range.first + _range.second) / 2;
            b ? _range.first = mid + 1 : _range.second = mid;
        }

        assert(_range.first == _range.second);
        return alphabet[_range.first - 1];
    }

#ifdef DEBUG
    void _traverse(const node *_node, int level) {
        if (_node == nullptr)
            return;

        std::cout << "level: " << level << std::endl;
        std::cout << _node->str << std::endl;
        for (bool b : _node->bitmap)
            std::cout << b;
        std::cout << std::endl;
        std::cout << "bitmap: ";
        for (bool b : _node->bitmap)
            std::cout << std::setw(2) << b << ' ';
        std::cout << std::endl;
        std::cout << "rank_0: ";
        for (size_t r : _node->rank_0)
            std::cout << std::setw(2) << r << ' ';
        std::cout << std::endl << std::endl;

        _traverse(_node->children[0], level + 1);
        _traverse(_node->children[1], level + 1);
    }

    void traverse() {
		std::cout << "traverse()" << std::endl;
        _traverse(root, 0);
    }
#endif
};

}