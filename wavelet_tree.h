#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <utility>
#include <iomanip>
#include <iostream>

#define PRECOMP

namespace wt {

template <class T>
class node {
public:
    std::vector<bool> bitmap;
    std::vector<size_t> rank_0, select_0, select_1;
    node *children[2];

#ifdef DEBUG
    std::vector<T> data;
#endif

    node() {
        children[0] = children[1] = nullptr;
    }

#ifdef DEBUG
    node(const std::vector<T> &v) : data(v) {
        children[0] = children[1] = nullptr;
    }

    void print_data() const {
        for (const T& t : data)
            std::cout << "'" << t << "', ";
        std::cout << std::endl;
    }
#endif
};

namespace bin_util {
    size_t rank(bool b, const std::vector<bool> &bitmap, size_t index) {
        if (b) return index - rank(0, bitmap, index) + 1;

        size_t count = 0;
        for (size_t i = 0; i <= index; ++i)
            count += (!bitmap[i]);
        return count;
    }

    size_t select(bool b, const std::vector<bool> &bitmap, size_t rank) {
        size_t index = 0, count = 0;
        while (count < rank) {
            if (bitmap[index++] == b) ++count;
        }
        return index - 1;
    }

    template <typename T>
    size_t precomp_rank(bool b, const node<T> *_node, size_t index) {
        if (b) return index - precomp_rank(0, _node, index) + 1;
        return _node->rank_0[index];
    }

    template <typename T>
    size_t precomp_select(bool b, const node<T> *_node, size_t rank) {
        if (b) return _node->select_1[rank];
        return _node->select_0[rank];
    }
}

template <class T=char>
class wavelet_tree {
    // a_map = short for alphabet map
    using a_map = std::unordered_map<T, size_t>;
    using range = std::pair<size_t, size_t>;

    node<T> *root;
    std::vector<T> alphabet;
    a_map alpha_map;

    template <typename I>
    void build_alphabet_map(I begin, I end) {
        std::set<T> st(begin, end);
        alphabet = std::vector<T>(st.begin(), st.end());

#ifdef DEBUG
        std::cout << "alphabet: '";
        for (const T& t: alphabet)
            std::cout << "'" << t << "', ";
        std::cout << std::endl;
#endif

        size_t count = 0;
        for (const T &t : alphabet)
            alpha_map[t] = ++count; // count goes from 1 to n
    }

    node<T>* build_node(const std::vector<T> &v, const range &_range) {
        if (_range.first == _range.second)
            return nullptr;

#ifdef DEBUG
        auto *_node = new node(v);
#else
        auto *_node = new node<T>;
#endif

        size_t v_len = v.size();
        std::vector<T> v0, v1;
        auto& bitmap = _node->bitmap;
        auto& rank_0 = _node->rank_0;
        auto& select_0 = _node->select_0;
        auto& select_1 = _node->select_1;
        bitmap.resize(v_len);
        rank_0.resize(v_len);
        size_t rank_0_so_far = 0;

        auto mid = (_range.first + _range.second) / 2;
        for (size_t i = 0; i < v_len; ++i) {
            const T &val = v[i];
            if (alpha_map[val] <= mid) {
                bitmap[i] = 0;
                rank_0_so_far++;
                select_0.push_back(i);
                v0.push_back(val);
            } else {
                bitmap[i] = 1;
                select_1.push_back(i);
                v1.push_back(val);
            }
            rank_0[i] = rank_0_so_far;
        }

        _node->children[0] = build_node(v0, {_range.first, mid});
        _node->children[1] = build_node(v1, {mid + 1, _range.second});

        return _node;
    }

    void destroy_node(const node<T> *_node) {
        if (_node == nullptr)
            return;

        destroy_node(_node->children[0]);
        destroy_node(_node->children[1]);

        delete _node;
    }



public:
    wavelet_tree(const std::string &s) {
        build_alphabet_map(s.begin(), s.end());
        root = build_node({s.begin(), s.end()}, {1, alphabet.size()});
    }

    wavelet_tree(const std::vector<T> &v) {
        build_alphabet_map(v.begin(), v.end());
        root = build_node(v, {1, alphabet.size()});
    }

    ~wavelet_tree() {
        destroy_node(root);
    }

    size_t rank(const T& val, size_t index) const {
        auto *_node = root;
        range _range = {1, alphabet.size()};

        if (alpha_map.count(val) == 0) {
            throw std::out_of_range("invalid input");
        }
        
        auto symbol_num = alpha_map.at(val);
        size_t r;

        while (_node) {
            auto mid = (_range.first + _range.second) / 2;
            bool b = symbol_num > mid;
            // rank returns count; so subtract 1 to use as index in bitmap
#ifdef PRECOMP
            r = index = bin_util::precomp_rank(b, _node, index) - 1;
#else
            r = index = bin_util::rank(b, _node->bitmap, index) - 1;
#endif
            _node = _node->children[b];

            // update range
            b ? _range.first = mid + 1 : _range.second = mid;
        }

        assert(_range.first == _range.second);
        // Add 1 back to rank as it should be a count
        return r + 1;
    }

    size_t _select(const node<T> *_node, range &_range, const T& val, size_t rank) const {
        if (!_node) {
            assert(_range.first == _range.second);
            return rank;
        }

        auto mid = (_range.first + _range.second) / 2;
        
        bool b = alpha_map.at(val) > mid;
        // update range
        b ? _range.first = mid + 1 : _range.second = mid;
        rank = _select(_node->children[b], _range, val, rank);

        // Value returned by _select is an index. Add 1 to get rank.
        // size_t sel1 = bin_util::select(b, _node->bitmap, rank + 1);

        // Don't add 1 because it uses 0-based indexing
        // size_t sel2 = precomp_select(b, _node, rank);

        // assert(sel1 == sel2);
        // std::cout << '(' << sel1 << ", " << sel2 << "), ";

#ifdef PRECOMP
        return bin_util::precomp_select(b, _node, rank);
#else
        return bin_util::select(b, _node->bitmap, rank + 1);
#endif
    }

    size_t select(T& val, size_t rank) const {

        if (alpha_map.count(val) == 0) {
            throw std::out_of_range("invalid input");
        }
        
        range _range = {1, alphabet.size()};
        // Treat rank as index instead of count to simplify select operation
        return _select(root, _range, val, rank - 1);
    }

    T access(size_t index) const {

        if (index < 0 || index >= root->bitmap.size()) {
            throw (std::out_of_range("index out of range"));
        }
        
        auto *_node = root;
        range _range = {1, alphabet.size()};
        
        while (_node) {
            bool b = _node->bitmap[index];
            // rank returns count; so subtract 1 to use as index in bitmap
            // size_t index1 = bin_util::rank(b, _node->bitmap, index) - 1;
            // size_t index2 = precomp_rank(b, _node, index) - 1;
            // assert(index1 == index2);
            // std::cout << '(' << index1 << ", " << index2 << "), ";
#ifdef PRECOMP
            index = bin_util::precomp_rank(b, _node, index) - 1;
#else
            index = bin_util::rank(b, _node->bitmap, index) - 1;
#endif
            _node = _node->children[b];
            
            // update range
            auto mid = (_range.first + _range.second) / 2;
            b ? _range.first = mid + 1 : _range.second = mid;
        }

        assert(_range.first == _range.second);
        return alphabet[_range.first - 1];
    }

#ifdef DEBUG
    void _traverse(const node<T> *_node, int level) {
        if (_node == nullptr)
            return;

        std::cout << "level: " << level << std::endl;
        _node->print_data();
        std::cout << "bitmap: ";
        for (bool b : _node->bitmap)
            std::cout << std::setw(2) << b << ' ';
        std::cout << std::endl;
        std::cout << "rank_0: ";
        for (size_t r : _node->rank_0)
            std::cout << std::setw(2) << r << ' ';
        std::cout << std::endl;
        std::cout << "select_0: ";
        for (size_t s : _node->select_0)
            std::cout << std::setw(2) << s << ' ';
        std::cout << std::endl;
        std::cout << "select_1: ";
        for (size_t s : _node->select_1)
            std::cout << std::setw(2) << s << ' ';
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