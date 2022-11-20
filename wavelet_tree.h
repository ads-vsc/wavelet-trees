#include <vector>
#include <string>

namespace wt {

class node {
    std::vector<bool> bitmap;
    node *children[2];
};

class wavelet_tree {
    node *root;

public:
    wavelet_tree(std::string &s) {

    }
};

}