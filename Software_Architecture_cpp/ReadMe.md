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

### “隐藏的友元”？
隐藏的友元是指那些被声明为类的友元的非成员函数，它们在类的内部定义。通常来说，普通的友元函数会在类的外部定义，但隐藏友元则直接在类的定义中出现。由于这些函数位于类的作用域中，它们只能通过**参数依赖查找（Argument Dependent Lookup, ADL）**的方式被调用。

ADL 是一种查找方式，当调用一个函数时，编译器会根据函数参数的类型来查找可能的匹配，通常在参数类型的命名空间或类作用域中查找。因此，隐藏友元函数只能在与相关类型一起被使用时才会被找到和调用，避免了污染全局命名空间的可能性。

隐藏友元的优势
1. 减少重载数量：由于隐藏友元只能通过 ADL 被找到，这意味着编译器在函数查找时会考虑的重载数量大大减少，从而加快了编译速度。
2. 更简洁的错误消息：隐藏友元的设计使得编译器给出的错误消息比普通友元或其他候选方案更短、更易读。
3. 防止隐式转换：隐藏友元的一个特性是它们无法被调用，如果首先需要发生隐式转换。这意味着这些函数不会无意中被触发那些有可能进行隐式类型转换的调用，这帮助避免了一些难以发现的隐式转换错误。

ADL 机制：在 ADL 查找的过程中，编译器会只在参数的相关命名空间内查找对应的函数。这意味着，如果你要调用一个隐藏的友元函数，编译器要求该函数的参数已经是目标类型，而不是需要通过某种隐式转换来成为目标类型。

防止隐式转换：在调用隐藏友元函数时，如果函数参数需要进行隐式转换，编译器可能不会找到这个隐藏友元，因为它的查找机制是基于实际参数类型的，而不是转换后的类型。因此，如果参数不能直接匹配，隐藏友元就不会被选择为一个有效的候选函数。这有效地阻止了一些可能会引入问题的隐式转换调用。
