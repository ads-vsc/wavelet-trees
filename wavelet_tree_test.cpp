#include <bits/stdc++.h>
#include "wavelet_tree.h"
#include <algorithm>

using namespace std;

int main() {
	// string s = "alabar a la alabarda";
	string s = "mississippi";
	wt::wavelet_tree tree(s);

	// int r = tree.rank(6, 'i');
	// cout << "Rank: " << r << endl;


#ifdef DEBUG
	tree.traverse();
#endif

	// Access Test
	for (size_t i = 0; i < s.size(); ++i)
		cout << tree.access(i);
	cout << endl;

	return 0;
}
