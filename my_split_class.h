#ifndef _ALI_TEST_MY_SPLIT_H_
#define _ALI_TEST_MY_SPLIT_H_

#include <string>

namespace ali_test {

class MySplit {
public:
    MySplit();
    virtual ~MySplit();
    MySplit(std::string file_path, int split_size);
    
    bool CheckParameter();
    bool Split();
    
private:
    std::string file_path_;
    int split_size_;

    int total_split_file_num_;

    int source_file_fd_;
    uint64_t capacity_;

    bool is_check;

    char* data_buf_;

private:
    bool WriteNewFile(int file_id);

};

void LogError(std::string msg);
void LogWarn(std::string msg);
void LogInfo(std::string msg);

} // namespace ali_test
#endif // #ifndef _ALI_TOOLS_MY_SPLIT_H_
