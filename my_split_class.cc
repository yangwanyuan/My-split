#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <inttypes.h>
#include <sys/ioctl.h>
#include <linux/fs.h>
#include <string.h>
#include <stdlib.h>

#include <iostream>
                   
#include "my_split_class.h"

using namespace std;

namespace ali_test {

MySplit::MySplit() {}

MySplit::~MySplit() {
    if (is_check) {
        delete[] data_buf_;
        close(source_file_fd_);
    }
}

MySplit::MySplit(string file_path, int split_size)
        : file_path_(file_path), split_size_(split_size),
        total_split_file_num_(-1), source_file_fd_(-1),
        capacity_(0), is_check(false){}

bool MySplit::CheckParameter() {
    source_file_fd_ = open(file_path_.c_str(), O_RDWR, 0666);
    if (source_file_fd_ < 0) {
        LogError("File not exist!");
        return false;
    }

    int ret = 0;
    struct stat stat_buf;
    ret = fstat(source_file_fd_, &stat_buf);
    if (ret < 0) {
        LogError("Can't get file stat!");
        return false;
    }

    capacity_ = stat_buf.st_size;

    if(split_size_ <= 0) {
        LogError("Invalid Split Size!");
        return false;
    }

    total_split_file_num_ = (capacity_ / split_size_) + 1;
    if (total_split_file_num_ > 1000) {
        LogWarn("Maybe split too many files!");
    }

    data_buf_ = new char[split_size_];

    is_check = true;
   
    return true;
}

bool MySplit::Split() {
    if (!is_check) {
        LogError("Forbid split, please check parameter first!");
        return false;
    }
    
    int ret = 0;
    for (int i = 0; i < total_split_file_num_; i++) {
        ret = WriteNewFile(i);
        if (!ret) {
            LogError("Split is not completed!");
            return false;
        }
    }
    return true;
}

bool MySplit::WriteNewFile(int file_id) {
    string split_filename = file_path_ + std::string(".") + std::to_string(file_id);

    int split_fd = open(split_filename.c_str(), O_RDWR | O_CREAT, 0666);
    if (split_fd < 0) {
        string msg = "Write" + split_filename + "Failed!";
        LogError(msg);
        return false;
    }

    ssize_t ret = 0;
    ssize_t data_size = 0;
    off_t read_offset = split_size_ * file_id;

    if (file_id == total_split_file_num_ - 1) {
        data_size = capacity_ - (split_size_ * file_id);
    } else {
        data_size = split_size_;
    }

    ret = pread(source_file_fd_, data_buf_, data_size, read_offset);
    if (ret != data_size) {
        string msg = "Read data from" + std::to_string(read_offset) + "Failed!";
        LogError(msg);
        return false;
    }

    ret = pwrite(split_fd, data_buf_, data_size, 0);
    if (ret != data_size) {
        string msg = "Write data to " + split_filename + "Failed!";
        LogError(msg);
        return false;
    }

    close(split_fd);
    return true;
}

void LogError(string msg) {
    cout<< "ERROR: " << msg << "\n";
}
void LogWarn(string msg) {
    cout<< "WARNING: " << msg << "\n";
}
void LogInfo(string msg) {
    cout<< "INFO: " << msg << "\n";
}

} // namespace ali_test
