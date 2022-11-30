#include <bits/stdc++.h>
#include "wavelet_tree.h"

using namespace std;

void int_test() {
	vector<int> v = {7, 4, 1, 6, 8, 3, 5, 2};
	wt::wavelet_tree tree(v);

#ifdef DEBUG
	tree.traverse();
#endif

	for (size_t i = 0; i < v.size(); ++i)
		cout << "access(" << i << ") = " << tree.access(i) << endl;
	cout << endl;

	// Rank Test
	for (int c : set<int>(v.begin(), v.end()))
		cout << "rank(" << c << ", " << v.size()-1 << ") = " << tree.rank(c, v.size()-1) << endl;
	cout << endl;

	// Select Test
	for (int c : set<int>(v.begin(), v.end()))
		cout << "select(" << c << ", " << 1 << ") = " << tree.select(c, 1) << endl;
	cout << endl;	
}

void string_test() {
	vector<string> v = {"to", "be", "or", "not", "to", "be"};
	wt::wavelet_tree tree(v);

#ifdef DEBUG
	tree.traverse();
#endif

	for (size_t i = 0; i < v.size(); ++i)
		cout << "access(" << i << ") = " << tree.access(i) << endl;
	cout << endl;

	// Rank Test
	for (string c : set<string>(v.begin(), v.end()))
		cout << "rank(" << c << ", " << v.size()-1 << ") = " << tree.rank(c, v.size()-1) << endl;
	cout << endl;

	// Select Test
	for (string c : set<string>(v.begin(), v.end()))
		cout << "select(" << c << ", " << 1 << ") = " << tree.select(c, 1) << endl;
}

int main() {
	string s = "alabar a la alabarda";
	// string s = "mississippi";
	wt::wavelet_tree<char> tree(s);

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

	int_test();
	string_test();
	return 0;
}
