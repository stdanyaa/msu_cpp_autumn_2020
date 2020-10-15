#include <cstddef>

class Allocator{
    char* memory_pointer_;
    size_t size_;
    size_t offset_;

public:
    void makeAllocator(size_t maxSize){
        size_ = maxSize;
        offset_ = 0;
        memory_pointer_ = new char[size_];
    };
    char* alloc(size_t size){
        if (offset_ + size > size_){
            return nullptr;
        }
        if (size <= 0){
            return nullptr;
        }
        char *ret = memory_pointer_ + offset_;
        offset_ += size;
        return ret;
    };
    void reset(){
        offset_ = 0;
    };
    ~Allocator(){
        if(memory_pointer_ != nullptr){
            delete []memory_pointer_;
        }
    }
};