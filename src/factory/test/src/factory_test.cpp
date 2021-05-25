#include <limits.h>
#include <factory/factory.h>
#include <gtest/gtest.h>
namespace
{

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

TEST(ExampleTests, TestGet)
{

    CppUtils::Factory::Instance().registerMaker("MyClass1", new CppUtils::BaseMaker<MyClass1>());
    auto p = CppUtils::Factory::Instance().create("MyClass1");
    auto q = CppUtils::Factory::Instance().create("MyClass1");
    EXPECT_NE(p, q);
}
TEST(ExampleTests, TestGetType)
{

    auto p = CppUtils::Factory::Instance().create("MyClass1");

    EXPECT_EQ(p->type(), "MyClass1");
}
};
