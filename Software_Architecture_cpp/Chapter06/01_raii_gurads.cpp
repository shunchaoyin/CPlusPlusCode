#include <iostream>
#include <gsl/util>
#include <chrono>


using namespace std::chrono;

void self_measuring_function()
{
     auto timestamp_begin = high_resolution_clock::now();

    auto cleanup = gsl::finally(
        [timestamp_begin]
        {
            auto timestamp_end = high_resolution_clock::now();

            std::cout << "Execution took"
                      << duration_cast<microseconds>(timestamp_end - timestamp_begin).count()
                      << "us" << std::endl;
        });

        //perform work
    //throw std::runtime_error{"unexpected fault!"};
}

int main()
try
{
    self_measuring_function();
}
catch(const std::exception& e)
{
    std::cerr << e.what() << '\n';
}
