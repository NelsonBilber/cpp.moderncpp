//http://www.cprogramming.com/c++11/c++11-lambda-closures.html

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>

using namespace std;

class Foo
{
public:
    Foo () : _x( 3 ) {}
    void func ()
    {
        // a very silly, but illustrative way of printing out the value of _x
	    [this] () { cout << _x << endl; } ();
    }

private:
        int _x;
};

//delegates in c++
//-------------------------------------------------------------------------
class EmailProcessor
{
public:
    void receiveMessage (const std::string& message)
    {
        if ( _handler_func ) 
        {
            _handler_func( message );
        }
        // other processing
    }
    void setHandlerFunc (std::function<void (const std::string&)> handler_func)
    {
        _handler_func = handler_func;
    }

private:
        std::function<void (const std::string&)> _handler_func;
};


class MessageSizeStore
{
    public:
    MessageSizeStore () : _max_size( 0 ) {}
    void checkMessage (const std::string& message ) 
    {
        const int size = message.length();
        if ( size > _max_size )
        {
            _max_size = size;
        }
    }
    int getSize ()
    {
        return _max_size;
    }

private:
    int _max_size;
};

//-------------------------------------------------------------------------


int main()
{
  auto func = [] () {cout << "Hello World!" << endl;};
  func(); //now call the function  
  
  vector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
    
  for_each( v.begin(), v.end(), [] (int val)
	    {
		    std::cout << val << std::endl;
	    } );


  auto f2 = [] () -> int { return 1000; }; // now we're telling the compiler what we want

  std::cout << f2() << std::endl;

  Foo foo;
  foo.func();


  //DELEGATES
  //### Example of using delegates
  EmailProcessor processor;
  MessageSizeStore size_store;
  processor.setHandlerFunc( 
        [&] (const std::string& message) { size_store.checkMessage( message ); } 
);

  std::cout << "\n\nEnd of program ... ! \n" << std::endl;

  return 0;
}


