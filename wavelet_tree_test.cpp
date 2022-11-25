#include <bits/stdc++.h>
#include "wavelet_tree.h"
using namespace std;

int main() {
	string s = "alabar a la alabarda";
	wt::wavelet_tree tree(s);

#ifdef DEBUG
	tree.traverse();
#endif

	// Access Test
	for (size_t i = 0; i < s.size(); ++i)
		cout << tree.access(i);
	cout << endl;

	return 0;
}
