# 本书介绍
代码仓库
https://github.com/PacktPublishing/Software-Architecture-with-Cpp
## Chapter 1: Importance of Software Architecture and Principles of Great Design
### 架构的层次
1. 企业级架构：公司所有系统是如何相互协作的。
2. 解决方案架构：特定系统与周围环境的交互方式。设计一个完整的软件系统或修改现有的软件系统。
3. 软件架构：特定项目、所用的技术以及如何与其它项目交互。
4. 基础设施架构：软件使用的基础设施。部署环境和策略、程序扩展方式、可靠性等细节。
### 敏捷宣言
1. 个体和互动 高于 流程和工具
2. 工作的软件 高于 详尽的文档
3. 客户合作 高于 合同谈判
4. 响应变化 高于 遵循计划
### C++哲学思想
1. C++底层不依赖基于任何其它语言（汇编除外）
2. 只为使用的东西付费（不需要为没有使用的语言特性付费）
3. 低成本提供高抽象（更高的目标是零成本提供高级抽象）
### SOLID原则
1. single responsibility priciple
   与之接近的是principle of least knowledge
2. open-closed principle
   拓展开放，修改关闭
3. liskov substitution priciple
   可以使用派生类指针或引用替换基类对象的指针或引用
4. interface segregation priciple
   不应该强迫客户依赖它不适用的接口或方法
5. dependecy inversion priciple
   依赖接口(多态和模板)
```cpp
#include <iostream>
#include <vector>
#include <variant>

class FrontDeveloper
{
public:
    void develope()
    {
        std::cout << "this front developer is working." << std::endl;
    }
};

class EndDeveloper
{
public:
    void develope()
    {
        std::cout << "this end developer is working." << std::endl;
    }
};


template<typename... Devs>
class Project
{
public:
    using Developers = std::vector<std::variant<Devs...>>;
    explicit Project(Developers developers) :m_developers(std::move(developers)) {}

    void deliver()
    {
        for (auto& developer : m_developers)
        {
            std::visit([](auto& dev) { dev.develope();}, developer);
        }
    }
private:
    Developers m_developers;
};

using MyProject = Project<FrontDeveloper, EndDeveloper>;

int main()
{
    auto alice = FrontDeveloper{};
    auto jack = EndDeveloper{};
    auto mypro = MyProject({ alice, jack });
    mypro.deliver();
}
```
### 参考资料
1. How Non-member Functions Improve Encapsulation(https://www.drdobbs.com/cpp/how-non-member-functions-improve-encapsu/184401197)
2. Domain-Driven Design: Tackling Complexity in the Heart of software

## Chapter 2: Architectural Styles
本章使用了conan(包管理器)
### 有状态风格和无状态风格
区分，是否存在状态。类似函数范式编程时无状态风格，线程安全，
### 单体风格
缺乏模块化，作者举例linux内核，但是不懂。
### 服务和微服务
将解决方案分成多个相互通信的服务，分配给不同的团队。
面向服务的架构(sevice-oriented architecture,soa),业务功能被模块化，每个团队可以使用适合自己的技术。例如C# 和C++。
微服务：不理解！！！
### 基于事件的架构
### 分层架构
### 基于模块的架构

### Reference
1. Flygare, R., and Holmqvist, A. (2017). Performance characteristics between monolithic and microservice-based systems (Dissertation).
2. Engelen, Robert. (2008). A framework for service-oriented computing with C and C++ web service components. ACM Trans. Internet Techn. 8. 10.1145/1361186.1361188
3. Fowler, Martin. Microservices – A definition of this new architectural term. Retrieved from https://martinfowler.com/articles/microservices.html#MicroservicesAndSoa
4. Getting Started – C++ Micro Services documentation. Retrieved from http://docs.cppmicroservices.org/en/stable/doc/src/getting_started.html

## Chapter 3: Functional and Nonfunctional Requirements
### 代码生成文档
需要安装CMake,Doxygen,Sphinx,m2r2,Breathe,ReadTheDocs;
### 需求的类型
功能性需求和非功能性需求（运行速度，代码质量）。
### 重要需求的管理
### 文档化需求

### Reference
1. Evaluate the Software Architecture using ATAM, JC Olamendy, blog post: https://johnolamendy.wordpress.com/2011/08/12/evaluate-the-software-architecture-using-atam/
2. EARS: The Easy Approach to Requirements Syntax, John Terzakis, Intel Corporation, conference talk from the ICCGI conference: https://www.iaria.org/conferences2013/filesICCGI13/ICCGI_2013_Tutorial_Terzakis.pdf
3. Eoin Woods and Nick Rozanski, Software Systems Architecture: Working With Stakeholders Using Viewpoints and Perspectives


## Chapter 4: Architectural and System Design Patterns
此章暂时未看懂。

## Chapter 5: Leveraging C++ Language Features
### RAII
```cpp
#include<memory>
struct Resource;
//C API
Resource* acquire();
void releaseResource(Resource* resource);

//C++ API
using ResourceRaii = std::unique_ptr < Resource, decltype(&releaseResource)>;
ResourceRaii acquireResourceRaii();

```
### 在接口中使用指针
```cpp
void A(Resource*);
void B(Resource&);
void C(std::unique_ptr<Resource>);
void D(std::unique_ptr<Resource>&)
void E(std::shared_ptr<Resource>)
void F(std::shared_ptr<Resource>&)
```
A和B，简单的参数传递，如果不对所有权做任何处理，不应该使用。
C-F,如果想操作指针本身，那么在进行参数传递时应该只使用智能指针，例如转移所有权。

### optional
```cpp
void calculate(int param);  //if param equals -1 means "no value"
void calculate(int param = -1)
//enhanced
void calculate(std::optional<int>param);

```
可选函数返回值
```cpp

int try_parse(std::string_view maybe_number);
bool try_parse(std::string_view maybe_number,int &parsed_number);
int* try_parse(std::string_view maybe_number);
//enhanced
std::optional<int> try_parser(std::string_view maybe_number);
//如果1函数出错，会抛出异常，还是魔法数？
//第二个，如果有错误，会返回false。但是容易忘记检查返回值。
//第三个函数，可以返回一个nullptr,没有错误返回整数，但是是否应该释放返回的int？
```


可选类成员
```cpp
struct UserProfile
{
    std::string name;
    std::optional<std::string>full_name;
    std::optional<std::string>address;
    std::optional<PhoneNumber>phone;
};
//如果类中某些成员可能不需要可以命名为optional
```
### 声明式代码


## Chapter 6: Design Patterns and C++
### 01 RAII
异常抛出（throw std::runtime_error{"unexpected fault!"};）在 C++ 中确实会增加一些显著的时间消耗。这是因为异常的处理机制在背后涉及了较多的系统操作和资源管理，使得它比普通的函数调用或控制流跳转要复杂得多。让我们详细分析一下为什么异常的抛出和捕获会增加如此多的执行时间。

异常处理机制复杂
异常的抛出与捕获并不仅仅是一个简单的函数调用或跳转，而是一个相对复杂的流程。C++ 中的异常处理涉及到许多底层的系统机制，具体包括以下几点：

1. 栈展开：当异常被抛出时，程序会开始栈展开，也就是从异常发生的地方逐步向上（沿调用链）查找可以处理该异常的 catch 语句。在这个过程中，所有在栈上分配的对象都需要被正确析构。栈展开涉及到：
    反复执行栈帧的销毁。
    调用每个作用域内局部对象的析构函数。
2. 保存和恢复上下文：在异常发生时，程序必须保存当前的执行上下文，以便在异常处理的 catch 块中恢复正常的执行。这些操作需要调用底层的系统函数，通常涉及操作系统提供的栈管理机制。

3. 动态类型信息（RTTI）：异常处理中有类型匹配的过程，它会查找哪个 catch 处理器能够处理这种类型的异常。这涉及到使用运行时类型识别（RTTI），增加了额外的开销。
### 03 Rules of 5 and rule of 0

Rule of Five 适用于你需要管理资源（例如动态分配内存、文件句柄、网络连接等）的类，确保资源在复制和移动过程中不被泄漏或出错。你需要明确的控制资源的生存期和所有权。

Rule of Zero 适用于尽量避免显式资源管理的场景，借助 C++ 标准库中的工具来简化管理。这样代码更具可读性，并且更安全，因为错误的资源管理是 C++ 中常见的 bug 来源之一。

### 04 隐藏的友元
隐藏的友元是指那些被声明为类的友元的非成员函数，它们在类的内部定义。通常来说，普通的友元函数会在类的外部定义，但隐藏友元则直接在类的定义中出现。由于这些函数位于类的作用域中，它们只能通过**参数依赖查找（Argument Dependent Lookup, ADL）**的方式被调用。

ADL 是一种查找方式，当调用一个函数时，编译器会根据函数参数的类型来查找可能的匹配，通常在参数类型的命名空间或类作用域中查找。因此，隐藏友元函数只能在与相关类型一起被使用时才会被找到和调用，避免了污染全局命名空间的可能性。

### 隐藏友元的优势
1. 减少重载数量：由于隐藏友元只能通过 ADL 被找到，这意味着编译器在函数查找时会考虑的重载数量大大减少，从而加快了编译速度。
2. 更简洁的错误消息：隐藏友元的设计使得编译器给出的错误消息比普通友元或其他候选方案更短、更易读。
3. 防止隐式转换：隐藏友元的一个特性是它们无法被调用，如果首先需要发生隐式转换。这意味着这些函数不会无意中被触发那些有可能进行隐式类型转换的调用，这帮助避免了一些难以发现的隐式转换错误。

ADL 机制：在 ADL 查找的过程中，编译器会只在参数的相关命名空间内查找对应的函数。这意味着，如果你要调用一个隐藏的友元函数，编译器要求该函数的参数已经是目标类型，而不是需要通过某种隐式转换来成为目标类型。

防止隐式转换：在调用隐藏友元函数时，如果函数参数需要进行隐式转换，编译器可能不会找到这个隐藏友元，因为它的查找机制是基于实际参数类型的，而不是转换后的类型。因此，如果参数不能直接匹配，隐藏友元就不会被选择为一个有效的候选函数。这有效地阻止了一些可能会引入问题的隐式转换调用。
```cpp
#include <algorithm>
#include <cassert>
#include <utility>

template <typename T>
class Array {
 public:
  Array(T *array, int size) : array_{array}, size_{size} {}

  Array(const Array &other) : array_{new T[other.size_]}, size_{other.size_} {
    std::copy_n(other.array_, size_, array_);
  }

  Array(Array &&other) noexcept
      : array_{std::exchange(other.array_, nullptr)},
        size_{std::exchange(other.size_, 0)} {}

  Array &operator=(Array other) noexcept {
    swap(*this, other);
    return *this;
  }

  ~Array() { delete[] array_; }

  // swap functions should never throw
  friend void swap(Array &left, Array &right) noexcept {
    using std::swap;
    swap(left.array_, right.array_);
    swap(left.size_, right.size_);
  }

  T &operator[](int index) { return array_[index]; }
  int size() const { return size_; }

 private:
  T *array_;
  int size_;
};

template <typename T>
Array<T> make_array(int size) {
  return Array(new T[size], size);
}

int main() {
  auto my_array = make_array<int>(7);
  auto my_move_constructed_array = std::move(my_array);
  my_array = std::move(my_move_constructed_array);  // move back
  auto my_copy_constructed_array = my_array;
  my_array = my_copy_constructed_array;  // copy back
  assert(my_array.size() == 7);
}
```
注意：此处没有单独实现移动赋值运算符

Array &operator=(Array other) noexcept 这行代码实现了赋值运算符，其中通过按值传递 Array 参数 other 来实现。在这过程中，以下几个步骤确保了它能够同时支持复制赋值和移动赋值：

按值传递参数：

当传递 Array other 作为参数时，会根据提供的 other 对象是否是左值或右值，调用合适的构造函数。
1. 如果 other 是左值，则调用复制构造函数，为 other 创建一个副本。
2. 如果 other 是右值，则调用移动构造函数，将资源从原来的对象转移到 other。
在赋值操作中使用 swap：

赋值运算符的实现是通过调用 swap(*this, other) 来实现的。swap 函数是一个友元函数，用于交换当前对象与参数 other 的内部资源。
通过交换，当前对象的资源被交给 other，而 other 原本的资源被赋给当前对象。
other 是按值传递的，离开作用域时会被销毁，从而自动释放原来当前对象所持有的旧资源。

### 异常安全级别：
1. 无保证：这是最基本的级别。在抛出异常后，不能保证对象的状态。
2. 基本的异常安全：可能有副作用，但对象不会泄漏任何资源，并将处于有效的状态，且包含有效的数据（不一定与操作前相同）。你的类型至少应该总是提供这个级别的安全。
3. 强异常安全：不会产生任何副作用。对象的状态将与操作之前相同。
4. 保证无异常抛出：操作将永远成功。如果在操作期间抛出异常，将在内部捕获和处理异常，以便操作不会在外部抛出异常。这些操作可以标记为noexcept。

### 05 niebloids
Niebler在2014年首先提出的。其目的是禁用不需要的ADL，使编译器不考虑从其他命名空间中进行重载。
此处不理解。。。。。。

### 07奇异递归模板模式(Curiously Recurring Template Pattern，CRTP)
提到多态性时，很多人会想到动态多态性，即在运行时收集执行函数调用所需的信息。与此相反，静态多态性是在编译时确定调用的。前者的一个优点是，你可以在运行时修改类型列表，从而允许通过插件和库来扩展类层次结构。第二种方法的最大优点是，如果你预先知道类型，则可以获得更好的性能。当然，在第一种情况下，有时你可以期望编译器去虚化(devirtualize)调用，但你不能总指望它这样做。但是，在第二种情况下，编译时间会更长。

鱼与熊掌不可兼得。尽管如此，为类型选择正确的多态性类型还是会有很大的帮助。如果性能是最重要的考虑因素，建议你考虑静态多态性。CRTP是一个可以用来实现它的习语。

### 参考资料
- [tag_invoke: A general pattern for supporting customisable functions](https://wg21.link/p1895) - Lewis Baker, Eric Niebler, Kirk Shoop, ISO C++ proposal
- [tag_invoke :: niebloids evolved](https://www.youtube.com/watch?v=Q26YL0J6DU) - Gašper Ažman for the Core C++ Conference, YouTube video
- [Inheritance Is The Base Class of Evil](https://channel9.msdn.com/Events/GoingNative/2013/Inheritance-Is-The-Base-Class-of-Evil) - Sean Parent, GoingNative 2013 Conference, Channel9 video
- [Modern C++ Design](https://www.amazon.com/Modern-C-Design-Generic-Programming/dp/0201704315) - Andrei Alexandrescu, Addison-Wesley, 2001
- [How Non-Member Functions Improve Encapsulation](https://www.drdobbs.com/cpp/how-non-member-functions-improve-encapsu/184401197) - Scott Meyers, Dr. Dobbs article
- [Returning a Status or a Value](https://abseil.io/docs/cpp/guides/status#returning-a-status-or-a-value) - Status User Guide, Abseil documentation
- [function_ref](https://github.com/TartanLlama/function_ref) - GitHub repository
- [How To Use std::visit With Multiple Variants](https://www.bfilipek.com/2018/09/visit-variants.html) - Bartłomiej Filipek, Bartek's coding blog
- [CppCon 2018: Effective replacement of dynamic polymorphism with std::variant](https://www.youtube.com/watch?v=gKbORJtnVu8) - Mateusz Pusz, YouTube video

## Chapter 7: Building and Packaging

### 典型的CMake目录
cmake：存放cmake脚本
include：存放公共头文件，通常包含用项目命名的子文件夹
src： 存放源文件和私有头文件
test：用于测试

### 目录变量
PROJECT_SOURCE_DIR： 最近一次运行的project命令的目录
CMAKE_SOURCE_DIR： 最上层目录
CMAKE_CURRENT_SOURCE_DIR： 当前的CMakeLists.txt的目录
CMAKE_CURRENT_LSIT_DIR:　CMAKE_CURRENT_LSIT_FILE的目录。如果当前CMAKE脚本被包含在另一个源代码目录中，他可能与当前源代码目录不同（对于被包含的CMAKE模块而言，很常见）

```cmake
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()
```
通过这种方式，CMake在构建项目时会使用ccache来缓存编译结果，从而加速后续的编译过程。这对于大型项目尤其有用，因为它可以显著减少重复编译相同代码所需的时间，提高开发效率。
```cmake
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}")
```

${CMAKE_CURRENT_LIST_DIR}/cmake添加到CMAKE_MODULE_PATH中，CMake会在当前目录下的cmake子目录中查找模块文件。这对于项目中包含自定义的CMake模块文件非常有用，可以确保CMake能够找到并使用这些模块文件。

接下来，list(APPEND CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}")这行代码将${CMAKE_BINARY_DIR}目录添加到CMAKE_PREFIX_PATH列表中。CMAKE_PREFIX_PATH是一个CMake变量，用于指定CMake在查找库文件、头文件和其他依赖项时应该搜索的目录列表。

```cmake

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
```
CMAKE_RUNTIME_OUTPUT_DIRECTORY是一个CMake变量，用于指定生成的可执行文件（如.exe或.out文件）应该放置的目录。
CMAKE_ARCHIVE_OUTPUT_DIRECTORY是一个CMake变量，用于指定生成的静态库文件（如.a或.lib文件）应该放置的目录
CMAKE_LIBRARY_OUTPUT_DIRECTORY是一个CMake变量，用于指定生成的共享库文件（如.so、.dylib或.dll文件）应该放置的目录。
```cmake
find_package(cpprestsdk CONFIG REQUIRED)
```
用于查找并配置cpprestsdk库。cpprestsdk（C++ REST SDK）是一个用于构建跨平台的RESTful应用程序的C++库，提供了丰富的功能来处理HTTP请求、JSON解析等。
cpprestsdk是要查找的库的名称，CONFIG表示使用配置模式查找库，这通常意味着CMake会查找一个名为cpprestsdkConfig.cmake的配置文件，该文件包含了cpprestsdk库的详细信息。REQUIRED关键字表示这个库是必需的，如果找不到cpprestsdk库，CMake将会停止配置过程并报错。
```cmake
include(CommonCompileFlags)
```
包含一个名为CommonCompileFlags.cmake的CMake模块文件。通过包含这个模块文件，可以将其中定义的编译标志和设置应用到当前的CMake项目中。
通过使用include(CommonCompileFlags)，可以将这些通用的编译设置集中管理，并在需要的地方重复使用。这种做法不仅提高了代码的可维护性和可读性，还确保了项目中所有目标的一致性配置。这样，如果需要更改某些编译选项，只需修改CommonCompileFlags.cmake文件，而不需要在每个CMakeLists.txt文件中逐一修改。
```cmake
list(
  APPEND
  BASE_COMPILE_FLAGS
  "$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:-Wall;-Wextra;-pedantic;-Werror>"
  "$<$<CXX_COMPILER_ID:MSVC>:/W4;/WX>")
```
使用了生成器表达式（Generator Expressions）来根据不同的编译器设置不同的编译标志。生成器表达式是CMake中的一种特殊语法，用于在生成构建系统时进行条件判断和变量替换。生成器表达式以$<...>的形式表示，可以嵌套使用。
如果代码使用了$<CXX_COMPILER_ID:MSVC>生成器表达式来检查当前使用的编译器是否为Microsoft Visual C++（MSVC）。如果条件为真，则添加/W4和/WX编译标志。这些标志分别用于启用较高级别的警告（级别4）以及将所有警告视为错误。

```cmake

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  include(CTest)
  if(BUILD_TESTING)
    add_subdirectory(test)
  endif()
endif()
```
首先检查当前项目是否是顶层项目，然后根据配置决定是否包含测试子目录。
如果当前项目是顶层项目,CTest是CMake的测试模块，提供了一组用于测试的命令和宏。通过包含CTest模块，可以启用项目的测试支持，并定义和运行测试。
BUILD_TESTING是由CTest模块定义的一个变量，表示是否启用测试构建。如果BUILD_TESTING为真，说明测试构建已启用，此时会执行if(BUILD_TESTING)语句块中的代码。
