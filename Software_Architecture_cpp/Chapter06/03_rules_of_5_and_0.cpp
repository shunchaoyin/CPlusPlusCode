#include <memory>

class Misleading
{
public:
    Misleading() = default;
    Misleading(const Misleading &) = default;
    Misleading &operator=(const Misleading &) = default;
    Misleading(Misleading &&) = default;
    Misleading &operator=(Misleading &&) = default;

private:
    std::unique_ptr<int> int_;
};

class RuleofZero
{
    std::unique_ptr<int> int_;
};

int main()
{
    auto myclass = Misleading{};
    auto myclass2 = std::move(myclass);
    //below line won't compile,but is not alwasy obvious
    //auto myclass2_copu = myclass2;
    auto ruleofzero = RuleofZero{};
    auto ruleofzero2 = std::move(ruleofzero);
    // below line won't compile , but that's not surprising;
    //auto ruleofzero2_copy = uleofzero2;
};
