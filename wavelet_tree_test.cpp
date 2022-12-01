#include <bits/stdc++.h>
#include "wavelet_tree.h"

using namespace std;

void char_test() {
	string s = "alabar a la alabarda";
	char invalid_c = 'z';
	// string s = "mississippi";
	wt::wavelet_tree tree(s);

#ifdef DEBUG
	tree.traverse();
#endif

	// access test
	// for (size_t i = 0; i < s.size(); ++i)
	// 	cout << "access(" << i << ") = " << tree.access(i) << endl;
	cout << "access(" << 10 << ") = " << tree.access(10) << endl;
	cout << "access(" << 15 << ") = " << tree.access(15) << endl;

	// access test- invalid input
	try {
		cout << "access(" << -3 << ") = " << tree.access(-3) << endl;
	} catch(const std::out_of_range& e) {
		std::cout << e.what() << endl;
	}
	try {
		cout << "access(" << 50 << ") = " << tree.access(50) << endl;
	} catch(const std::out_of_range& e) {
		std::cout << e.what() << endl;
	}
	cout << endl;
	
	// rank test
	// for (char c : set<char>(s.begin(), s.end()))
	// 	cout << "rank(" << c << ", " << s.size()-1 << ") = " << tree.rank(c, s.size()-1) << endl;
	cout << "rank(" << 'l' << ", " << 11 << ") = " << tree.rank('l', 11) << endl;
	cout << "rank(" << 'b' << ", " << 16 << ") = " << tree.rank('b', 16) << endl;

	// rank test- invalid input
	try {
		cout << "rank(" << invalid_c << ", 3" << ") = " << tree.rank(invalid_c, 3) << endl;
	} catch(const std::out_of_range& e) {
		cout << e.what() << endl;
	}
	cout << endl;

	// select test
	// for (char c : set<char>(s.begin(), s.end()))
	// 	cout << "select(" << c << ", " << 1 << ") = " << tree.select(c, 1) << endl;
	// cout << endl;
	char c;
	cout << "select(" << (c = 'b') << ", " << 2 << ") = " << tree.select(c, 2) << endl;
	cout << "select(" << (c = 'a') << ", " << 6 << ") = " << tree.select(c, 6) << endl;

	// select invalid input test
	try {
		cout << "select(" << invalid_c << ", 3" << ") = " << tree.rank(invalid_c, 3) << endl;
	} catch(const std::out_of_range& e) {
		cout << e.what() << endl;
	}
	cout << endl;
}

void int_test() {
	vector<int> v = {7, 4, 1, 6, 8, 3, 5, 2};
	wt::wavelet_tree tree(v);

#ifdef DEBUG
	tree.traverse();
#endif

	// access test
	for (size_t i = 0; i < v.size(); ++i)
		cout << "access(" << i << ") = " << tree.access(i) << endl;
	cout << endl;

	// rank test
	for (int c : set<int>(v.begin(), v.end()))
		cout << "rank(" << c << ", " << v.size()-1 << ") = " << tree.rank(c, v.size()-1) << endl;
	cout << endl;

	// select test
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

	// access test
	// for (size_t i = 0; i < v.size(); ++i)
	// 	cout << "access(" << i << ") = " << tree.access(i) << endl;
	cout << "access(" << 2 << ") = " << tree.access(2) << endl;
	cout << "access(" << 4 << ") = " << tree.access(4) << endl;
	cout << endl;

	// rank test
	// for (string c : set<string>(v.begin(), v.end()))
	// 	cout << "rank(" << c << ", " << v.size()-1 << ") = " << tree.rank(c, v.size()-1) << endl;
	cout << "rank(" << "to" << ", " << 2 << ") = " << tree.rank("to", 2) << endl;
	cout << "rank(" << "be" << ", " << 6 << ") = " << tree.rank("be", 6) << endl;
	cout << endl;

	// select test
	// for (string c : set<string>(v.begin(), v.end()))
	// 	cout << "select(" << c << ", " << 1 << ") = " << tree.select(c, 1) << endl;
	string c;
	cout << "select(" << (c = "be") << ", " << 1 << ") = " << tree.select(c, 1) << endl;
	cout << "select(" << (c = "to") << ", " << 2 << ") = " << tree.select(c, 2) << endl;
	cout << endl;
}

void range_quantile_query_test() {
	vector<int> v({8, 1, 11, 3, 15, 8, 6, 1});
	wt::wavelet_tree tree(v);

	// range quantile query test
	// for (int k = 1; k <= v.size(); k++)
	// 	cout << "range_quantile_query(" << 0 << ", " << v.size()-1 << ", " << k << ") = " << tree.range_quantile_query(0, v.size()-1, k) << endl;
	cout << "range_quantile_query(" << 1 << ", " << 4 << ", " << 2 << ") = " << tree.range_quantile_query(1, 4, 2) << endl;
	cout << "range_quantile_query(" << 2 << ", " << 6 << ", " << 3 << ") = " << tree.range_quantile_query(2, 6, 3) << endl;
	cout << endl;
}

int main() {
	char_test();
	// int_test();
	string_test();
	range_quantile_query_test();
	return 0;
}
