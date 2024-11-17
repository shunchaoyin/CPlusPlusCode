#include <algorithm>
#include <iostream>
#include <string_view>

struct NullPrintPolicy
{
    template <typename... Arg>
    void operator()(Arg...) {}
};

struct CountPringPolicy
{
    void operator()(std::string_view text)
    {
        std::cout << text << std::endl;
    }
};

template <typename T, typename DebugPrintPolicy = NullPrintPolicy>
class Array
{
private:
    T *array_;
    int size_;
    /* data */
public:
    Array(T *array, int size) : array_{array}, size_{size}
    {
        DebugPrintPolicy{}("constructor");
    }
    ~Array()
    {
        DebugPrintPolicy{}("deconstructor");
        delete[] array_;
    }
    Array(const Array &other) : array_{new T[other.size_]}, size_(other.size_)
    {
        DebugPrintPolicy{}("copy constructor");
        std::copy_n(other.array_, other.size_, array_);
    }
    Array &operator=(Array other) noexcept
    {
        DebugPrintPolicy{}("assignment constructor");
        swap(*this, other);
        return *this;
    }
    Array(Array &&other) noexcept : array_{std::exchange(other.array_, nullptr)},
                                    size_{std::exchange(other.size_, 0)}
    {
        DebugPrintPolicy{}("move constructor");
    }

    friend void swap(Array &left, Array &right) noexcept
    {
        DebugPrintPolicy{}("swap");
        using std::swap;
        swap(left.array_, right.array_);
        swap(left.size_, right.size_);
    }
    T &operator[](int index) { return array_[index]; }
    int size() { return size_; }
};

template <typename T>
Array<T> make_array(int size)
{
    return Array(new T[size], size);
}

template <typename T>
Array<T, CountPringPolicy> make_verbose_array(int size)
{
    return Array<T, CountPringPolicy>(new T[size], size);
}

int main()
{
    auto my_array = make_array<int>(7);
    auto my_array_copy = my_array;
    my_array = my_array_copy;

    auto my_verbose_array = make_verbose_array<int>(7);
    auto my_verbose_copy_array = my_verbose_array;
    my_verbose_array = my_verbose_copy_array;
    return 0;
}