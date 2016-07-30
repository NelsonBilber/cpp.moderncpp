//http://en.cppreference.com/w/cpp/language/override
//http://stackoverflow.com/questions/18198314/override-keyword-in-c
#include <iostream>

using namespace std;

struct A
{
	virtual void foo(){ cout << "foo from base class" << endl;}
	void bar(){}
	virtual void redefine () = 0;
};

struct B: A
{
	//void foo() const overrride //Error B B::foo does not overrride A::foo
	//	{}                       //(signature mismatch
	void foo() override          // OK: B::foo overrrides A::foo
	{
		cout << "foo from derivided class " << endl;
	}
	//void bar() override  {}    // Error: A::bar is not a virtual

	virtual void redefine() override
	{
		cout <<"redefine by derivided class "<<endl;
	}
};
 
int main()
{
	A* over = new B();
	over->redefine();
	over->foo();
	
	return 0;
}
