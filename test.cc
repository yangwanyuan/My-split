
#include <string>
#include "my_split_class.h" 

using namespace std;
int main() {
    string file_name = "test.log";
    int split_size = 100;
    
    ali_test::MySplit split(file_name, split_size);
    split.CheckParameter();
    split.Split();
}
