#include <thread>
#include <deque>
#include <atomic>

template<class ELEM_TYPE>
class MemoryPool {
public:
    MemoryPool();
    ~MemoryPool();

    ELEM_TYPE* alloc();

    template <class... Args>
    ELEM_TYPE* alloc(Args&&... args);

    void free(ELEM_TYPE* ptr);

    std::uint32_t getCurrentUsage();
    std::uint32_t getAvailableSlots();
private:
    std::uint32_t sizeOfElement_;
    std::atomic_size_t currentUsage_;
    std::mutex guard_;
    std::deque<ELEM_TYPE *> slots_;
};

template<class ELEM_TYPE>
MemoryPool<ELEM_TYPE>::MemoryPool() {
    sizeOfElement_ = sizeof(ELEM_TYPE);
    currentUsage_ = 0;
}

template<class ELEM_TYPE>
MemoryPool<ELEM_TYPE>::~MemoryPool() {
    while (!slots_.empty()) {
        auto slot = slots_.front();
        slots_.pop_front();
        slot->~ELEM_TYPE();
    }
}

template<class ELEM_TYPE>
ELEM_TYPE* MemoryPool<ELEM_TYPE>::alloc() {
    ELEM_TYPE *ptr = nullptr;
    std::unique_lock<std::mutex> lock(guard_);
    if (slots_.empty()) {
        ptr = reinterpret_cast<ELEM_TYPE *> (operator new(sizeOfElement_));
        currentUsage_ += sizeOfElement_;
    } else {
        ptr = slots_.front();
        slots_.pop_front();
    }
    return ptr;
}

template<class ELEM_TYPE>
template<class... Args>
ELEM_TYPE* MemoryPool<ELEM_TYPE>::alloc(Args&&... args) {
    ELEM_TYPE *ptr = alloc();
    return new (ptr) ELEM_TYPE (std::forward<Args>(args)...);
}

template<class ELEM_TYPE>
void MemoryPool<ELEM_TYPE>::free(ELEM_TYPE *ptr) {
    if (!ptr) {
        return;
    }

    std::unique_lock<std::mutex> lock(guard_);
    slots_.push_front(ptr);
}

template<class ELEM_TYPE>
std::uint32_t MemoryPool<ELEM_TYPE>::getCurrentUsage() {
    return currentUsage_.load();
}

template <class ELEM_TYPE>
std::uint32_t MemoryPool<ELEM_TYPE>::getAvailableSlots() {
    return slots_.size();
}