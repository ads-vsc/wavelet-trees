#include <bits/stdc++.h>
#include "wavelet_tree.h"

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
		cout << "access(" << i << ") = " << tree.access(i) << endl;
	cout << endl;

	// Rank Test
	for (char c : set<char>(s.begin(), s.end()))
		cout << "rank(" << c << ", " << s.size()-1 << ") = " << tree.rank(c, s.size()-1) << endl;
	cout << endl;

	// Select Test
	for (char c : set<char>(s.begin(), s.end()))
		cout << "select(" << c << ", " << 1 << ") = " << tree.select(c, 1) << endl;
	cout << endl;

	return 0;
}
