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

	return 0;
}
