main: my-split test

my_split:
	g++ --std=c++11 my-split.cc -o my-split

test:
	g++ --std=c++11 my_split_class.cc test.cc -o test

clean:
	rm -fr my-split
	rm -fr test
