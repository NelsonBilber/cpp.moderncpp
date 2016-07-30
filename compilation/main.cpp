//http://www.codeproject.com/Articles/570638/Ten-Cplusplus-Features-Every-Cplusplus-Developer

#include <iostream>
#include <map>
#include <vector>
#include <memory>
#include <functional>

using namespace std;

class Foo{
public:
    int x;
    Foo(){  cout << "ctor Foo " << endl;}
    ~Foo(){ cout << "~dtor Foor" << endl; }
};

//returning auto types
template<typename T1, typename T2>
auto compose(T1 t1, T2 t2) -> decltype(t1 + t2)
{
    return t1+t2;
}

void bar(shared_ptr<int> p)
{
    ++(*p);
}

void foo(std::shared_ptr<int> p, int init)
{
    *p = init;
}


//===================================================
// Override and final
//===================================================

class B
{
public:
    virtual void f(int) {std::cout << "B::f" << std::endl;}
};

class D : public B
{
public:
    virtual void f(int) override final {std::cout << "D::f" << std::endl;}
};

void foo(int* p)
{
    cout << *p << endl;
}
        
template <typename Iterator>
void bar(Iterator begin, Iterator end)
{
    std::for_each(begin, end, [](int n) {std::cout << n << std::endl;});
    
    auto is_odd = [](int n) {return n%2==1;};
    auto pos = std::find_if(begin, end, is_odd);
    if(pos != end)
        std::cout << *pos << std::endl;
}

template <typename C>
void foo(C c)
{
    bar(std::begin(c), std::end(c));
}

template <typename T, size_t N>
void foo(T(&arr)[N])
{
    bar(std::begin(arr), std::end(arr));
}


template <typename T, size_t Size>
class Vector
{
    static_assert(Size < 3, "Size is too small");
    T _points[Size];
};


        
//===================================================
// Move Semantics
//===================================================

template <typename T>
class Buffer
{
    std::string          _name;
    size_t               _size;
    std::unique_ptr<T[]> _buffer;
    
public:
    // constructor
    Buffer(const std::string& name = "", size_t size = 16):
    _name(name),
    _size(size),
    _buffer(size? new T[size] : nullptr)
    {}
    
    // copy constructor
    Buffer(const Buffer& copy):
    _name(copy._name),
    _size(copy._size),
    _buffer(copy._size? new T[copy._size] : nullptr)
    {
        T* source = copy._buffer.get();
        T* dest = _buffer.get();
        std::copy(source, source + copy._size, dest);
    }
    
    // copy assignment operator
    Buffer& operator=(Buffer copy)
    {
        swap(*this, copy);
        return *this;
    }
    
    // move constructor
    Buffer(Buffer&& temp):Buffer()
    {
        swap(*this, temp);
    }
    
    friend void swap(Buffer& first, Buffer& second) noexcept
    {
        using std::swap;
        swap(first._name  , second._name);
        swap(first._size  , second._size);
        swap(first._buffer, second._buffer);
    }
};


int main(int argc, const char * argv[]) {
    
    //===================================================
    // Auto
    //===================================================
    
    auto i = 42;
    auto l = 42LL;
    auto f = new Foo();
    auto v = Foo();
    
    map<string, vector<int> > mymap;
    for(auto it= begin(mymap); it != end(mymap); ++it)
    {
        cout << "" << typeid(mymap).name() << endl;
        
    }
    
    cout << "" << typeid(i).name() << endl;
    cout << "" << typeid(l).name() << endl;
    cout << "" << typeid(f).name() << endl;
    cout << "" << typeid(v).name() << endl;
    
    auto return_auto = compose (3 , 3.14); // v's type is double
    
    cout << "" << return_auto << endl;
    
    delete f;
    
    
    //===================================================
    // nullptr
    //===================================================
    
    
    int* p1 = NULL;
    int* p2 = nullptr;
    if( p1 == p2)
        cout << "equal" << endl;
    else
        cout << "not equal " << endl;
    
    //===================================================
    // Range-base for loops
    //===================================================
    
    
    map<string , vector<int>> mmap;
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(3);
    vec.push_back(34);
    
    mmap["map"] = vec;
    
    for(const auto& kvp: mmap)
    {
        cout << kvp.first << endl;
        
        for(auto vv : kvp.second)
        {
            cout << vv << endl;
        }
    }
    
    cout << "" << endl;
    
    int arr[] = {1,2,3,4,5};
    for(int& e : arr)
    {
        e = e * e;
        cout << "" << e << endl;
    }
    
    
    //===================================================
    // Enume strongly-typed
    //===================================================
    
    enum class Options {None, One, All};
    Options o = Options::All;
    
    
    //===================================================
    // smart pointers
    //===================================================
    
    unique_ptr<int> pointer1(new int(42));
    unique_ptr<int> pointer2 = move(pointer1);
    
    if(pointer1)
        foo(pointer1.get());
    
    if(pointer2)
        foo(pointer2.get());
    
    
    shared_ptr<int> pshared (new int(54));
    shared_ptr<int> pshared2 = pshared;
    
    auto pshared3 = make_shared<int>(43);
    
    int into = 40;
    foo(std::shared_ptr<int>(new int(42)), into);

    
    //weak pointers ...
    auto p = std::make_shared<int>(42);
    std::weak_ptr<int> wp = p;
    
    {
        auto sp = wp.lock();
        std::cout << *sp << std::endl;
    }
    
    p.reset();
    
    if(wp.expired())
        std::cout << "expired" << std::endl;
    
    
    
    //===================================================
    // Lambdas
    //===================================================
   
    
    vector<int> vv;
    vv.push_back(1);
    vv.push_back(2);
    vv.push_back(3);
    
   /*
    auto is_odd = [](int n) {return n%2==1;};
    auto pos = std::find_if(std::begin(v), std::end(v), is_odd);
    if(pos != std::end(v))
        std::cout << *pos << std::endl;
    */
    
    std::function<int(int)> lfib = [&lfib](int n) {return n < 2 ? 1 : lfib(n-1) + lfib(n-2);};
    
  
    
    int arrw[] = {1,2,3};
    foo(arrw);
    
    std::vector<int> vvv;
    vvv.push_back(1);
    vvv.push_back(2);
    vvv.push_back(3);
    foo(vvv);
    
    
    //===================================================
    // static_assert and type traits
    //===================================================
    
    //Vector<int, 16> a1;
    Vector<double, 2> a2;
    
    
    //===================================================
    // Move Semantics
    //===================================================
    

    Buffer<int> b1;
    Buffer<int> b2("buf2", 64);
    Buffer<int> b3 = b2;
    
    return 0;
}
