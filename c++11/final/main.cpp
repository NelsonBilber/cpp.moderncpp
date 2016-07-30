//http://en.cppreference.com/w/cpp/language/final
//http://stackoverflow.com/questions/8824587/what-is-the-purpose-of-the-final-keyword-in-c11
#include <iostream>

using namespace std;

struct A /*final*/
{
	virtual void foo(){ cout << "foo from base class" << endl;}
	void bar(){}
	virtual void redefine () = 0;
	virtual void dosomething(){};
};

struct B final : A
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

	virtual void dosomething() final
	{
		cout << "something ... " << endl;
	}
};
 
int main()
{
	A* over = new B();
	over->redefine();
	over->foo();
	
	return 0;
}
