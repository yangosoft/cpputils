#include <limits.h>
#include <factory/abstractfactory.h>
#include <gtest/gtest.h>
namespace {




class MyClass1 
{
public:
    MyClass1(const std::string& node): i(42), thisType(node){
    }; 
    virtual ~MyClass1(){
        
    };
    virtual std::string type(){
        return thisType;
    };
    int get(){ return i++;};
    
private:
    int i;
    std::string thisType;
    
};

TEST(ExampleTests, TestType) {

    CppUtils::AbstractFactory<std::string, MyClass1*>  Factory;
    
    
    Factory.add("MyClass1", [&](std::string s) {  
        std::cout << "Calling lambda with: " <<  s << std::endl;
        return new MyClass1("Test1"); 
    });

    auto p = Factory.createInstance("MyClass1");
    std::cout << p->type() << std::endl;
    
    EXPECT_EQ(p->type(),"Test1");
}


};
