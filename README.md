# Wavelet Trees

# CSCI 7000: Advanced Data Structures (Fall 2022)
## Team Members
1. Varad Raut
2. Sagar Pathare
3. Chinmay Agrawal

## Date: December 1, 2022

## [Slides](https://github.com/ads-vsc/wavelet-trees/blob/main/ADS-%20Wavelet%20Trees-%20Varad%2C%20Sagar%2C%20Chinmay.pdf)

## Reference- [Navarro, G. (2014). Wavelet trees for all. Journal of Discrete Algorithms, 25, 2-20.](https://doi.org/10.1016/j.jda.2013.07.004)

<br/>Example usage:
```cpp
// Note: To use template type deduction, compile with c++17 or above
// The example below will work with c++11
#include "wavelet_tree.h"
using namespace std;

int main() {
    // Works with strings
    wt::wavelet_tree<char> tree("alabar a la alabarda");
    assert(tree.rank('a', tree.select('a', 3)) == 3);

    // vector of strings too
    wt::wavelet_tree<string> str_tree({"to", "be", "or", "not", "to", "be"});
    assert(str_tree.access(3) == "not");
    return 0;
}
```