#include <bits/stdc++.h>
#include "wavelet_tree.h"
using namespace std;

int main() {
	string s = "alabar a la alabarda";
	wt::wavelet_tree tree(s);

#ifdef DEBUG
	tree.traverse();
#endif

	return 0;
}
