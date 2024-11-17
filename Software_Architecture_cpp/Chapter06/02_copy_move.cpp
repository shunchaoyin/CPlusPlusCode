struct NonCopyable
{
    NonCopyable() = default;
    NonCopyable(const NonCopyable &) = delete;
    NonCopyable &operator=(const NonCopyable &) = delete;
};

class MyType :NonCopyable
{
};

struct MyType2 
{
    MyType2() = default;
    MyType2(const MyType2 &) = delete;
    MyType2 &operator=(const MyType2 &) = delete;
    MyType2(MyType2 &&) = delete;
    MyType2 &operator=(MyType2 &&) = delete; // becareful this having no const;
};


int main()
{
    auto myproject = MyType();
    auto my_better_project = MyType2();
    return 0;
}