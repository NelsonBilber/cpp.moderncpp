//The C++ Programming Language 4th Editon" by Bjarne Stroustrup
//http://en.cppreference.com/w/cpp/language/constexpr
//http://www.cprogramming.com/c++11/c++11-compile-time-processing-with-constexpr.html
//http://blog.smartbear.com/c-plus-plus/using-constexpr-to-improve-security-performance-and-encapsulation-in-c/


#include <iostream>
#include <cmath>
#include <stdexcept>

using namespace std;

/*example 01*/

constexpr double square(double x) { return x*x; }

void stroustrup()
{
	const int dmv = 17;
	int var = 17;
	constexpr double max1 = 1.4*square(dmv);

//evaluate in compile time	
//	constexpr double max2 = 1.4*square(var); //error var is not a constexpr

//evaluate in run time
	const double max3 = 1.4*square(var);

}


/* example 02 */

// The C++11 constexpr functions use recursion rather than iteration
// (C++14 constexpr functions may use local variables and loops)
constexpr int factorial(int n)
{
	return n <= 1 ? 1 : (n * factorial( n -1));
}

// literal class
class conststr {
    const char * p;
    std::size_t sz;
 public:
    template<std::size_t N>
    constexpr conststr(const char(&a)[N]) : p(a), sz(N-1) {}
    // constexpr functions signal errors by throwing exceptions
    // in C++11, they must do so from the conditional operator ?:
    constexpr char operator[](std::size_t n) const {
        return n < sz ? p[n] : throw std::out_of_range("");
    }
    constexpr std::size_t size() const { return sz; }
};
 
// C++11 constexpr functions had to put everything in a single return statement
// (C++14 doesn't have that requirement)
constexpr std::size_t countlower(conststr s, std::size_t n = 0,
                                             std::size_t c = 0) {
    return n == s.size() ? c :
           s[n] >= 'a' && s[n] <= 'z' ? countlower(s, n+1, c+1) :
           countlower(s, n+1, c);
}
 
// output function that requires a compile-time constant, for testing
template<int n> struct constN {
    constN() { std::cout << n << '\n'; }
};


int main()
{
	/*example 01*/
	stroustrup();

	/*example 02*/
	std::cout << "4! = ";
	constN<factorial(4)> out1;

	volatile int k = 8;
	std::cout << k << "! = " << factorial(k) << '\n';

	std::cout << "Number of letters of word test ... ";
	constN<countlower("test")> out2;

	return 0;
}
