#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#ifdef  DEBUG
#define DEBUG_TEST 1
#else
#define DEBUG_TEST 0
#endif

#define debug_print(fmt)\
        do{if(DEBUG_TEST) fprintf(stderr, "%s:%d:%s() " fmt, __FILE__,\
                          __LINE__,__func__);} while(0)

namespace Jing{

template<class T>//, class Alloc = allocator<T> >
class list{
private:
    bool inited;
    int data;
    list *next;
    list *last;
    size_t size;
    size_t max_size;

    void init();

public:
    list();

    list(T val);

    explicit list(size_t n);

    list(const list& x);

    list(const list&& x);

    ~list();

    list& operator=(const list& x);

    list& operator=(list&& x);

    bool empty() const noexcept;
    
    size_t size() const noexcept;

    void assign(size_t n, const T& val);

    void push_front(const T& val);

    void push_front(T&& val);

    void pop_front();

    void push_back(const T& val);

    void push_front(T&& val);

    void pop_back();

    list& insert(size_t n, const T& val);

    list& insert(size_t n, size_t i, T& val);

    list& insert(size_t n, T&& val);

    list& erase(size_t n);

    list& erase(size_t first, size_t last);

    void swap(list& x);

    void swap(size_t a, size_t b);

    void clear() noexcept;

    void splice(size_t n, list& x);

    void splice(size_t n, list&& x);

    void splice(size_t n, list& x, size_t i);

    void splice(size_t n, list&& x, size_t i);

    void splice(size_t n, list& x, size_t i, size_t first, size_t last);

    void splice(size_t n, list&& x, size_t i, size_t first, size_t last);

    void remove(const T& val);

    void unique();

    void sort();

    void reverse() noexcept;

};

}

#endif

