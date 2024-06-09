#pragma once

class A
{
public:
    A()
    {
        std::cout << "A construct" << std::endl;
    }

    ~A()
    {
        std::cout << "A destruct" << std::endl;
    }
};