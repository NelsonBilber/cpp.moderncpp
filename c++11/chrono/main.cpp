//http://en.cppreference.com/w/cpp/chrono

#include <iostream>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;

long fibonacci(unsigned n)
{
    if(n < 2)
        return n;
    return fibonacci(n-1) + fibonacci(n - 2);
}

int main()
{
  
    auto time0 = high_resolution_clock::now();
    this_thread::sleep_for(milliseconds{20});
    auto time1 = high_resolution_clock::now();
    std::cout << duration_cast<nanoseconds>(time1-time0).count() <<std::endl;
    
    std::cout << " -- " << std::endl;
    
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    std::cout << "fib(42) " << fibonacci(42) << "\n";
    end = std::chrono::system_clock::now();
    
    std::chrono::duration<double> elapesed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    
    std::cout << "Finished computation at " << std::ctime(&end_time)
              << "elapsed time : " << elapesed_seconds.count()
              << std::endl;
    
    
    
    return 0;
}

