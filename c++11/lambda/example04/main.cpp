// from: http://msdn.microsoft.com/en-us/library/dd293599.aspx

#include <iostream>
#include <functional>
#include <list>
#include <algorithm>
#include <vector>

using namespace std;


// Negates each element in the vector object. Assumes signed data type.
template <typename T>
void negate_all(vector<T>& v)
{
	for_each(v.begin(), v.end(), [](T& n) { n = -n; });
}

// Prints to the console each element in the vector object.
template <typename T>
void print_all(const vector<T>& v)
{
	for_each(v.begin(), v.end(), [](const T& n) { cout << n << endl; });
}



int main()
{

	
/*--------------------------------------*/
/* (1) declaring variables */
/*--------------------------------------*/
	// lambda that adds two numbers
	auto f1 = [] (int x, int y) { return x + y; };
	std::cout << f1(2, 3) << std::endl;

	// use same lambda expresion to a function object
	function <int (int,int)> f2 = [] (int x , int y) { return x + y ;};
	std::cout << f2(2, 3) << std::endl;

	int i = -1;
	int j = 5;

	// The following lambda expression captures i by value and
	// j by reference.
	function <int (void)> f = [i, &j] { return i +j; };

	i = 3;
	j = 44;

	//uses the values declared before lambda was defined
	std::cout << f() << std::endl;


/*--------------------------------------*/
/* (2) calling lambda expressions */
/*--------------------------------------*/
	//passing values
	int n = [](int x, int y) {return x + y; }(5,4);
	std::cout << n << std::endl;

	list<int> numbers;
	numbers.push_back(13);
	numbers.push_back(17);
	numbers.push_back(42);
	numbers.push_back(46);
	numbers.push_back(99);

	const list<int>::const_iterator result =
		find_if(numbers.begin(), numbers.end(),
				[](int n) { return (n%2) == 0;}
			);

	if(result != numbers.end())
	{
		std::cout << "the first even number in the list " << *result << "." << std::endl; 
	}
	else
	{
		std::cout <<"no even numbers"<< std::endl;
	}


	
/*--------------------------------------*/
// (3) nesting lambda expressions 
/*--------------------------------------*/
    int timetwoplusthree = [] (int x) { return [](int y) {return y * 2;}(x) + 3; }(5);
	std::cout << timetwoplusthree << std::endl;


	// The following code declares a lambda expression that returns
	// another lambda expression that adds two numbers.
	// The returned lambda expression captures parameter x by value.
	auto addtwointegers = [](int x) -> function<int(int)> {
		return [=](int y) { return x + y; };
	};

	// The following code declares a lambda expression that takes another
	// lambda expression as its argument.
	// The lambda expression applies the argument z to the function f
	// and multiplies by 2.
	auto higherorder = [](const function<int(int)>& f, int z) {
		return f(z) * 2;
	};

	// Call the lambda expression that is bound to higherorder.
	auto answer = higherorder(addtwointegers(7), 8);

	// Print the result, which is (7+8)*2.
	std::cout << answer << std::endl;


/*--------------------------------------*/
// (4) lambdas with templates 
/*--------------------------------------*/

	// Create a vector of signed integers with a few elements.
	vector<int> v;
	v.push_back(34);
	v.push_back(-43);
	v.push_back(56);

	print_all(v);
	negate_all(v);
	cout << "After negate_all():" << endl;
	print_all(v);

/*--------------------------------------*/
// (5) handling exceptions 
/*--------------------------------------*/
	vector<int> elements(3);
	vector<int> indices(3);
	indices[0] = 0;
	indices[1] = -1;
	indices[2] = 2;

	try
	{
		for_each(indices.begin(), indices.end(), [&](int index){
				elements.at(index) = index;
		});
	}
	catch( const out_of_range& e)
	{
		std::cerr << "caught " << e.what() << " ." << std::endl;
	}
	
	return 0;
}
