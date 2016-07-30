//http://en.cppreference.com/w/cpp/error/assert
//http://en.cppreference.com/w/cpp/language/static_assert


#include <iostream>
#include <cassert>
#include <type_traits>

using namespace std;

template <class T>
void swap( T& a, T& b)
{
    static_assert(std::is_copy_constructible<T>::value,
                  "Swap requires copying");
    static_assert(noexcept(std::is_nothrow_move_constructible<T>::value
                        && std::is_nothrow_move_assignable<T>::value),
                  "Swap may throw");
    auto c = b;
    b = a;
    a = c;
}
 
template <class T>
struct data_structure
{
    static_assert(std::is_default_constructible<T>::value,
                  "Data Structure requires default-constructible elements");
};
 
struct no_copy
{
    no_copy ( const no_copy& ) = delete;
    no_copy () = default;
};
 
struct no_default
{
    no_default () = delete;
};

int main()
{
	/* asserts in run-time */
	assert(2+2==4);
	std::cout << " pass first assert" << std::endl;
	//assert(2+2==5);
	//std::cout <<"fail assert"<< std::endl;

	/* asserts in compile-time*/

	int a, b;
	swap(a, b);
 
	no_copy nc_a, nc_b;
	swap(nc_a, nc_b); // 1
 
	data_structure<int> ds_ok;
	data_structure<no_default> ds_error; // 2
	
	return 0;
}
