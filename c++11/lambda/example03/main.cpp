//from:http://msdn.microsoft.com/en-us/library/dd293603.aspx

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;


template <typename C>
void print(const string& s, const C& c)
{
	cout << s;

	for(const auto& e : c){
		cout << e << " ";
	}
	cout << endl;
}

void fillVector(vector<int>& v)
{
	static int nextValue = 1;

	generate(v.begin(), v.end(), []{ return nextValue++; } );
}

int main()
{
	const int elementCount = 9;
	vector<int> v (elementCount, 1);

	print ("initial values", v);

	int x = 1;
	int y = 1;
	
	generate_n ( v.begin() + 2, elementCount - 2 ,
				 [ = ] () mutable throw() -> int {
					 int n = x + y;
					 x = y;
					 y = n;
					 return n;
				 }
		);

	// Print the local variables x and y.
	// The values of x and y hold their initial values because
	// they are captured by value.
	cout << "x: " << x << " y: " << y << endl;
	
    print ("after call to generate_n() with lambda : ", v);

	fillVector(v);	
	print ("vector v after 1st call to fillvector : ", v);

	fillVector(v);	
	print ("vector v after 1st call to fillvector : ", v);
	
	
	return 0;
}


