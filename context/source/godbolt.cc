// This file was originally developed on godbolt to expand on the idea
//
#include <cstddef>
#include <iostream>
#include <memory>
#include <span>
#include <stack>

template<typename Type>
struct RC {
    Type value;
};

template<typename Type>
struct SharedPointer {
    struct ControlBlock {
        Type* pointer = nullptr;
        size_t ref_count{};
        void (deleter)(Type*);
    };

    ControlBlock* control_block = nullptr;

    SharedPointer(Type* ptr)
        : control_block(new ControlBlock{ptr, 1, &default_deleter})
    {}

    template<typename Deleter>
    SharedPointer(Type* ptr, Deleter deleter) {
    }

    template<typename Deleter>
    SharedPointer(Type value, Deleter deleter) {
    }

    SharedPointer() = default;

    SharedPointer(const SharedPointer& other)
        : control_block(other.control_block) {
        increment();
    }

    SharedPointer(SharedPointer&& other)
        : control_block(other.control_block) {
        other.control_block = nullptr;
    }

    SharedPointer& operator=(const SharedPointer& other) {
        if (control_block != nullptr) {
            decrement();
        }

        control_block = other.control_block;
        increment();

        return *this;
    }

    SharedPointer& operator=(SharedPointer&& other) {
        control_block = other.control_block;
        other.control_block = nullptr;
        return *this;
    }

    ~SharedPointer() {
        decrement();
    }

    explicit operator bool() const {
        return control_block != nullptr;
    }

    Type& operator*() {
        return *control_block->pointer;
    }

private:
    static void default_deleter(Type* pointer) {
        delete pointer;
    }

    void decrement() {
        --control_block->ref_count;
        if (control_block->ref_count ==0) {
            delete control_block;
        }
    }

    void increment() {
        ++control_block->ref_count;
    }
};

struct MemoryPool {
    std::shared_ptr<unsigned char[]> memory;
    std::span<unsigned char> block;
    std::span<unsigned char> remaining_block;

    MemoryPool(const size_t block_size)
        : memory(new unsigned char[block_size])
        , block(memory.get(), block_size)
    {}

    //MemoryPool(init with a memory block)

    template<typename Type, typename ...Args>
    SharedPointer<Type> create(Args&& ...args) {
        // find next alignment
        //remaining_block = remaining_block.subspan(get_alignment(alignof(Type)));
        new (remaining_block.data()) Type(std::forward<Args>(args)...);
        return {
            remaining_block.data()
        };
    }
};

struct LoggerBase {
    enum class Noise {
    };

    enum class Severity {
        trace,
        info,
        warn,
        error,
    };

    virtual void log(Severity, Noise) = 0;
};

struct AllocatorBase {
    virtual void* allocate(size_t, size_t) = 0;

    virtual void deallocate(void* pointer, size_t alignment) = 0;

    template<typename Type>
    Type* allocate(const size_t count){
        return static_cast<Type*>(allocate(count * sizeof(Type), alignof(Type)));
    }
    template<typename Type>
    void deallocate(Type* pointer) {
        deallocate(pointer, alignof(Type));
    }

    template<typename Type, typename ...Args>
    void construct(Type* pointer, Args&& ...args) {
        new (pointer) Type(std::forward<Args>(args)...);
    }
    template<typename Type, typename ...Args>
    void construct_n(Type* pointer, const size_t count, Args&& ...args) {
        for (auto* ptr = pointer; ptr != pointer + count; ++ptr) {
            construct(ptr, std::forward<Args>(args)...);
        }
    }

    template<typename Type>
    void destruct(Type* pointer) {
        pointer->~Type();
    }
    template<typename Type>
    void destruct_n(Type* pointer, const size_t count) {
        for(auto* ptr = pointer; ptr != pointer + count; ++ptr) {
            destruct(ptr);
        }
    }
};

struct STDLogger : LoggerBase {
    void log(Severity, Noise) override {
    }
};

struct STDAllocator : AllocatorBase {
    size_t id{};
    STDAllocator(const size_t ID)
        : id(ID)
    {}
    STDAllocator(const STDAllocator&) = delete;
    void operator=(const STDAllocator&) = delete;

    void* allocate(const size_t size, const size_t alignment) override {
        std::cout << "STDAllocator " << id << " allocating\n";
        return operator new(size, static_cast<std::align_val_t>(alignment));
    }

    void deallocate(void* ptr, const size_t alignment) override {
        std::cout << "STDAllocator " << id << " deallocating\n";
        operator delete(ptr, static_cast<std::align_val_t>(alignment));
    }
};

struct ContextFrame {
    std::shared_ptr<AllocatorBase> allocator;
    std::shared_ptr<LoggerBase> logger;
};

struct ContextStack {
    std::stack<ContextFrame> stack;

    ContextStack() {
        stack.push({
            std::make_shared<STDAllocator>(42),
            std::make_shared<STDLogger>(),
        });
    }

    void push(ContextFrame frame) {
        stack.push(frame);
    }

    void pop() {
        stack.pop();
    }

    const ContextFrame& context() const {
        return stack.top();
    }
};

thread_local inline ContextStack GlobalContext{};

void push_context(ContextFrame frame) {
    GlobalContext.push(frame);
}

void push_context(std::shared_ptr<AllocatorBase> allocator) {
    push_context(ContextFrame{
        .allocator = allocator,
        .logger = GlobalContext.stack.top().logger,
    });
}

void push_context(std::shared_ptr<LoggerBase> logger) {
    push_context(ContextFrame{
        .allocator = GlobalContext.stack.top().allocator,
        .logger = logger,
    });
}

void pop_context() {
    GlobalContext.pop();
}

const ContextFrame& context() {
    return GlobalContext.context();
}

AllocatorBase& allocator() {
    return *context().allocator;
}

LoggerBase& logger() {
    return *context().logger;
}

using ScopedContext = std::shared_ptr<ContextFrame>;

struct S {
    int i;

    S() {
        std::cout << "Constructing S\n";
        std::cout << this << std::endl;
    }
    ~S() {
        std::cout << "Destructing S\n";
        std::cout << this << std::endl;
    }
};

void foo() {
    auto& palloc = allocator();

    auto* p = palloc.allocate<S>(1);
    palloc.construct(p);
    palloc.destruct(p);
    palloc.deallocate(p);
}

int main() {
    auto& palloc = allocator();
    auto* p = palloc.allocate<S>(2);
    palloc.construct_n(p, 2);

    push_context(std::make_shared<STDAllocator>(1138));
    foo();

    palloc.destruct_n(p, 2);
    palloc.deallocate(p);
}

