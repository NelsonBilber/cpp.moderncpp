//http://www.cplusplus.com/reference/utility/move/
//http://mbevin.wordpress.com/2012/11/20/move-semantics/
  

#include <iostream>
#include <utility>
#include <string>
#include <vector>

using namespace std;


void old_style()
{
  std::string foo = "foo";
  std::string bar = "bar";
  std::vector <std::string> mVector;

  mVector.push_back(foo); //copy vars
  mVector.push_back(bar); //move vars

  std::cout << "vector contains ..." ;
  for(std::string& x:mVector){
      std::cout << ' ' << x; 
  }
  std::cout << "\n";

  /* :: resume :: 
     ------------
  */  
  vector<string> v;
  string s { "hello world" };

  v.push_back(string("hello world")); // move possible, as string is an rvalue (and 
                                      // std::string implements move semantics)
  v.emplace_back("hello world");      // just illustrating how we do the same the less-verbose C++11 way
  v.push_back(s);                     // move can't be done, as parameter is an lvalue
  v.push_back(std::move(s));          // move possible, as we're explicitly moving the data out of s, 
                                      // making s now be empty

}


string getName()
{
  string s = "hello";
  return s;
}

void new_style()
{
  string&& name = getName();  // as getName() returns an rvalue, assigning getName()'s result to an rval
}



/* disable copy and assign operators */

template <class T> class MyVector: public vector<T>
{
public:
  MyVector():vector<T>(){}
  MyVector(int size):vector<T>(size){}
  MyVector(std::initializer_list<T> l):vector<T>(l){}
  MyVector(const MyVector&& v):vector<T>(v){} // MOVE CONSTRUCTOR
private:
  //disable
  MyVector(const MyVector&);
  MyVector& operator=(const MyVector&);
}; 

class MoveSemanticsTest
{
public:
  static void doTest()
  {
    vector<vector <int>> vv1;
    vector<MyVector <int>> vv2;

    vv1.push_back({1,2,3,4}); // std:: vector move constructor
    vv2.push_back({1,2,3,4}); // My vector move constructor

    vector<int>   v1  { 1,2,3,4 };
    MyVector<int> v2  { 1,2,3,4 };

    vv1.push_back(v1); // full copy
    //vv2.push_back(v2); //compile error, disable copy operators
  }
};


class MyClass
{
	int* buffer = nullptr;
	string myName;
private:

   // disable copying
   MyClass(const MyClass&);
   MyClass& operator=(const MyClass&);

public:

	MyClass(){}
	
   // move constructor
   MyClass(MyClass&& other)
   {
      buffer = other.buffer;
      other.buffer = nullptr;

      myName = std::move(other.myName); // using std::move no known types
   }

   // move assignment operator
   MyClass& operator=(MyClass&& other)
   {
      if(this != &other)
      {
         if(buffer)
	 {
            delete buffer;
         }
         buffer = other.buffer;
         other.buffer = nullptr;
	 myName = std::move(other.myName);
      }
      return *this;
   }

	~MyClass()
	{
		if(buffer)
		{
			delete buffer;
		}
	}
};

int main()
{
  old_style();

  new_style();
   
  MoveSemanticsTest test;

  MyClass myclass;
  
  return 0;
}
