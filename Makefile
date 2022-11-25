build:
	g++ -std=c++11 wavelet_tree_test.cpp -o wavelet_tree.out

debug:
	g++ -std=c++11 -D DEBUG wavelet_tree_test.cpp -o wavelet_tree.out

run:
	./wavelet_tree.out