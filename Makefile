main: my-split

my-split:
	g++ --std=c++11 my_split_class.cc my-split.cc -o my-split

clean:
	rm -fr my-split

