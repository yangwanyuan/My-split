#include <string>
#include <iostream>

#include "my_split_class.h" 

using namespace std;

void Usage() {
    cout << "Usage: ./my-split file_path split_size" << endl;
}

int ParseOption(int argc, char** argv, std::string &file_path, int &split_size) {
    if (argc != 3) {
        cout << "Input parameters are invalid!" << endl;
        return -1;
    }
    file_path = argv[1];
    split_size = atoi(argv[2]);
    return 0;
}

int main(int argc, char** argv) {
    std::string file_path;
    int split_size = 0;

    if(ParseOption(argc, argv, file_path, split_size) < 0) {
        Usage();
        return -1;
    }
    
    ali_test::MySplit split(file_path, split_size);
    split.CheckParameter();
    split.Split();

    return 0;
}

