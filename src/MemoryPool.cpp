#include <thread>
#include <atomic>
#include<queue>

using namespace std;

template<class ELEM_TYPE>
class MemoryPool {
public:
    MemoryPool();
    ~MemoryPool();

    ELEM_TYPE* alloc();
    void free(ELEM_TYPE* ptr);

    // Utility Methods
    uint32_t getCurrentUsage();
    uint32_t getAvailableSlots();

private:
    /**
     * The size of the ELEM_TYPE type
     */
    uint32_t sizeOfElement_;

    /**
     * The current memory usage in terms of bytes
     */
    atomic_size_t currentUsage_;

    /**
     * The mutex that ensures alloc and free methods are thread safe
     */
    mutex guard_;

    /**
     * Slots hold the free memory blocks of ELEM_TYPE type
     */
    queue<ELEM_TYPE *>slots_;
};

/**
 * The default constructor for the MemoryPool class
 * @tparam ELEM_TYPE the element type
 */
template<class ELEM_TYPE>
MemoryPool<ELEM_TYPE>::MemoryPool() {
    sizeOfElement_ = sizeof(ELEM_TYPE);
    currentUsage_ = 0;
}

/**
 * The default destructor for the MemoryPool class
 * @tparam ELEM_TYPE the element type
 */
template<class ELEM_TYPE>
MemoryPool<ELEM_TYPE>::~MemoryPool() {
    while (!slots_.empty()) {
        auto slot = slots_.front();
        slots_.pop();
        slot->~ELEM_TYPE();
    }
}

/**
 * Allocates memory for the element
 * If there are free slots available then we use them first before allocating new memory.
 * @tparam ELEM_TYPE the element type
 * @return the pointer to the allocated memory
 */
template<class ELEM_TYPE>
ELEM_TYPE* MemoryPool<ELEM_TYPE>::alloc() {
    ELEM_TYPE *ptr = nullptr;
    unique_lock<mutex> lock(guard_);
    if (slots_.empty()) {
        ptr = reinterpret_cast<ELEM_TYPE *> (operator new(sizeOfElement_));
        currentUsage_ += sizeOfElement_;
    } else {
        ptr = slots_.front();
        slots_.pop();
    }
    return ptr;
}

/**
 * Deallocates the memory of element and puts the available memory in the free slots
 * @tparam ELEM_TYPE the element type
 * @param ptr the pointer to the allocated memory
 */
template<class ELEM_TYPE>
void MemoryPool<ELEM_TYPE>::free(ELEM_TYPE *ptr) {
    if (!ptr) {
        return;
    }

    unique_lock<mutex> lock(guard_);
    slots_.push(ptr);
}

/**
 * Gets the current usage in terms of number bytes in the MemoryPool
 * @return the size in number of bytes
 */
template<class ELEM_TYPE>
uint32_t MemoryPool<ELEM_TYPE>::getCurrentUsage() {
    return currentUsage_.load();
}

/**
 * Returns the number of free slots in the MemoryPool at a given time
 * @return the number of free slots
 */
template <class ELEM_TYPE>
uint32_t MemoryPool<ELEM_TYPE>::getAvailableSlots() {
    return slots_.size();
}
