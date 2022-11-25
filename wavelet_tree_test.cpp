#include <bits/stdc++.h>
#include "wavelet_tree.h"
#include <algorithm>

using namespace std;

int main() {
	string s = "alabar a la alabarda";
	// string s = "mississippi";
	wt::wavelet_tree tree(s);

#ifdef DEBUG
	tree.traverse();
#endif

	// Access Test
	for (size_t i = 0; i < s.size(); ++i)
		cout << tree.access(i);
	cout << endl;

	// Rank Test
	for (char c : unordered_set<char>(s.begin(), s.end()))
		cout << "Rank(" << c << ", " << s.size()-1 << "): " << tree.rank(c, s.size()-1) << endl;

	return 0;
}
