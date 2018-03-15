#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <sys/time.h>
#include <vector>
#include <algorithm>
#include <string.h>

#include <string>
using namespace std;

#define FILE_PATH "test.log"
#define DLIMT "."
#define SPLIT_BYTES 100

int main() {
    int fd = open(FILE_PATH, O_RDWR, 0666);

    struct stat stat_buf;
    fstat(fd, &stat_buf);
    
    uint64_t capacity = stat_buf.st_size;

    int file_num = (capacity / SPLIT_BYTES) + 1;

    off_t offset = 0;
    char *data_buff = new char[SPLIT_BYTES];
    for(int i = 0; i < file_num - 1; i++) {
        string split_filename = std::string(FILE_PATH) + std::string(DLIMT) + std::to_string(i);
        int split_fd = open(split_filename.c_str(), O_RDWR | O_CREAT, 0666);
        
        pread(fd, data_buff, SPLIT_BYTES, offset);
        pwrite(split_fd, data_buff, SPLIT_BYTES, 0);
        close(split_fd);
        offset += SPLIT_BYTES;
    }

    string split_filename = std::string(FILE_PATH) + std::string(DLIMT) + std::to_string(file_num-1);
    int split_fd = open(split_filename.c_str(), O_RDWR | O_CREAT, 0666);
    
    ssize_t last_size = capacity - SPLIT_BYTES * (file_num - 1);
    pread(fd, data_buff, last_size, offset);
    pwrite(split_fd, data_buff, last_size, 0);
    offset += SPLIT_BYTES;
    close(split_fd);

    close(fd);
    return 0;

}
