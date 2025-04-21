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

struct AllocatorBase : std::enable_shared_from_this<AllocatorBase> {
protected:
    virtual void* allocate(size_t size, size_t alignment) = 0;

    virtual void deallocate(void* pointer, size_t alignment) = 0;

public:
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
        // forward might do a move, making `args` invalid for subsequent iterations.
        // I feel like this is mostly the user's problem?
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

    template<typename Type>
    struct Deleter {
        std::shared_ptr<AllocatorBase> allocator;

        void operator()(Type* pointer) {
            allocator->destruct(pointer);
            allocator->deallocate(pointer);
        }
    };

    template<typename Type, typename ...Args>
    std::unique_ptr<Type, Deleter<Type>> create(Args&& ...args) {
        auto* ptr = allocate<Type>(1);
        construct(ptr, std::forward<Args>(args)...);
        return {ptr, {shared_from_this()}};
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

struct PoolAllocator : AllocatorBase {
    struct MemoryPool {
        std::shared_ptr<unsigned char[]> memory;

        std::span<unsigned char> whole_block;
        std::span<unsigned char> remaining_block;
    };

    MemoryPool pool;

    PoolAllocator()
        : PoolAllocator(4096)
    {}

    PoolAllocator(const size_t block_size)
        : pool({
            std::shared_ptr<unsigned char[]>{new unsigned char[block_size]},
            {pool.memory.get(), block_size},
            {pool.whole_block}
        })
    {}

    PoolAllocator(const PoolAllocator&) = delete;
    void operator=(const PoolAllocator&) = delete;

    void* allocate(const size_t size, const size_t alignment) override {
        std::cout << "PoolAllocator allocating\n";
        const auto* rptr = pool.remaining_block.data();
        pool.remaining_block = pool.remaining_block.subspan(alignment - (reinterpret_cast<size_t>(rptr) % alignment));
        auto* pointer = pool.remaining_block.data();
        pool.remaining_block = pool.remaining_block.subspan(size);
        return pointer;
    }

    void deallocate(void* ptr, const size_t alignment) override {
        std::cout << "PoolAllocator deallocating\n";
    }
};

struct ContextFrame {
    std::shared_ptr<AllocatorBase> allocator;
    std::shared_ptr<LoggerBase> logger;
    // error handling
    // coroutine handling?
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
        std::cout << "pushing context " << stack.size() << std::endl;
        stack.push(frame);
    }

    void pop() {
        std::cout << "popping context " << stack.size() << std::endl;
        stack.pop();
    }

    const ContextFrame& context() const {
        return stack.top();
    }
};

thread_local inline ContextStack GlobalCtxStack{};

void push_context(ContextFrame frame) {
    GlobalCtxStack.push(frame);
}

void push_context(std::shared_ptr<AllocatorBase> allocator) {
    push_context(ContextFrame{
        .allocator = allocator,
        .logger = GlobalCtxStack.stack.top().logger,
    });
}

void push_context(std::shared_ptr<LoggerBase> logger) {
    push_context(ContextFrame{
        .allocator = GlobalCtxStack.stack.top().allocator,
        .logger = logger,
    });
}

void pop_context() {
    GlobalCtxStack.pop();
}

const ContextFrame& context() {
    return GlobalCtxStack.context();
}

auto allocator() {
    return context().allocator;
}

auto logger() {
    return context().logger;
}

struct ScopedContext {
    template<typename ...Args>
    ScopedContext(Args&& ...args) {
        push_context(std::forward<Args>(args)...);
    }
    ~ScopedContext() {
        pop_context();
    }
};

template<typename Type, typename ...Args>
auto create_scoped_context(Args&& ...args) {
    return ScopedContext(std::make_shared<Type>(std::forward<Args>(args)...));
}

struct S {
    int i;

    S() {
        std::cout << "\tConstructing S\n";
        std::cout << '\t' << this << std::endl;
    }
    ~S() {
        std::cout << "\tDestructing S\n";
        std::cout << '\t' << this << std::endl;
    }
};


struct UseAllocFoo {
    std::shared_ptr<AllocatorBase> allocator;

    std::shared_ptr<S> foo() {
        return allocator->create<S>();
    }
};

struct UseAllocBar {
    std::shared_ptr<AllocatorBase> allocator;

    std::shared_ptr<S> bar() {
        return allocator->create<S>();
    }
};

void run1() {
    ScopedContext _ (std::make_shared<STDAllocator>(1));

    std::cout << "start run1" << std:: endl;

    UseAllocFoo foo{allocator()};

    {
        ScopedContext _(std::make_shared<STDAllocator>(1138));

        UseAllocFoo bar{allocator()};

        foo.foo();
        bar.foo();

    }

    std::cout << "end run1" << std:: endl;
}

UseAllocBar get_bar() {
    return {allocator()};
}

void run2() {
    ScopedContext _ (std::make_shared<STDAllocator>(1));

    std::cout << "run2 start\n";

    auto bar1 = get_bar();

    auto bar2 = []{
        ScopedContext _ (std::make_shared<STDAllocator>(1138));

        return get_bar();
    }();

    auto bar3 = get_bar();

    auto s1 = bar1.bar();
    auto s2 = bar2.bar();
    auto s3 = bar3.bar();

    std::cout << "run2 end\n";
}

void run3() {
    std::cout << "run3 start\n";

    auto bar = get_bar();
    auto _ = create_scoped_context<PoolAllocator>();

    bar.bar();

    auto bar2 = get_bar();

    bar2.bar();

    std::cout << "run3 end\n";
}

int main() {
    // runs without additional context of its own

    std::cout << "context stack size " << GlobalCtxStack.stack.size() << std::endl;

    run1();

    std::cout << "context stack size " << GlobalCtxStack.stack.size() << std::endl;

    run2();

    std::cout << "context stack size " << GlobalCtxStack.stack.size() << std::endl;

    run3();

    std::cout << "context stack size " << GlobalCtxStack.stack.size() << std::endl;
}
