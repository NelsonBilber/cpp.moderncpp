//from:http://msdn.microsoft.com/en-us/library/dd293608.aspx

//working with copies, mutable lambdas, ....

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int main()
{

	vector<int> v;

	for(int i =0; i < 10; i++){
		v.push_back(i);
	}

	int eventCount = 0;
	for_each( v.begin(), v.end(), [eventCount](int n) mutable{
			cout << n;
			if(n % 2 == 0) { 
				cout << " is even" << endl;
				++eventCount;
				cout << "== " << eventCount << endl;
			} else {
				cout << " is odd" << endl;
			}
		}
		);
	cout << "evens = " << eventCount << endl;
  return 0;
}


