#include "factory/abstractfactory.h"

#include <iostream>

using namespace std;

class MyClass1
{
public:
    MyClass1(const std::string& node)
        : i(42)
        , thisType(node){};
    virtual ~MyClass1(){

    };
    virtual std::string type()
    {
        return thisType;
    };
    int get()
    {
        return i++;
    };

private:
    int i;
    std::string thisType;
};

int main()
{

    CppUtils::AbstractFactory<std::string, MyClass1*> Factory;

    Factory.add("MyClass1", [&](std::string s) {
        std::cout << "Calling lambda with: " << s << std::endl;
        return new MyClass1("Test1");
    });

    auto p = Factory.createInstance("MyClass1");
    std::cout << p->type() << std::endl;

    return 0;
}
