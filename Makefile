clean:
	rm out/* -f

build: clean
	@mkdir -p out
	g++ -std=c++17 wavelet_tree_test.cpp -o out/wavelet_tree.out

debug: clean
	@mkdir -p out
	g++ -g -std=c++17 -D DEBUG wavelet_tree_test.cpp -o out/wavelet_tree.out

run:
	out/wavelet_tree.out