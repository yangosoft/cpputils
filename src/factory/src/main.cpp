#include "factory/factory.h"

#include <iostream>

using namespace std;

class MyClass1 : public CppUtils::IBase
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

    CppUtils::Factory::Instance().registerMaker("MyClass1", new CppUtils::BaseMaker<MyClass1>());
    auto p = CppUtils::Factory::Instance().create("MyClass1");
    cout << p->type() << endl;
    // MyClass1 *p2 = dynamic_cast<MyClass1*>(p.get());
    // cout << p2->get() << endl;

    return 0;
}
