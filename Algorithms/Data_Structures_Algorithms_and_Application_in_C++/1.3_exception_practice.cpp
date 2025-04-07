#include <exception>
#include <iostream>
#include <string>

int abc(int a,int b,int c)
{
    if(a<0 && b< 0 && c< 0)
    {
        throw 1;
    }
    if(a==0 && b==0 && c==0)
    {
        throw 2;
    }
    return a + b * c;
}


int main()
{
    try
    {
        std::cout << abc(0, 0, 0) << std::endl;
    }
    catch(int e)  //becareful this const
    {
        if(e ==1)
        {
            std::cerr << "the parameter to abc all were little than 0"<< std::endl;
        }
        if(e==2)
        {
            std::cerr << "the parameters to abc all were 0!" << std::endl;
        }
        return 1;
    }
    return 0;
}
