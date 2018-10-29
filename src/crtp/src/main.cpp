#include <iostream>



#ifdef CRTP
template <typename T>
class Curve
{
public:
    float get_point(float x) 
    {
        return impl().adjust(x) * x;
    }
    
private:
    
    T& impl() 
    {
        return *static_cast<T*>(this);
    }
};

class Simple : public Curve<Simple>
{
public: 
    float adjust(float x) const
    {
        return x*0.8;
    }
    
};
#endif

#ifndef CRTP


class Curve
{
public:
    virtual float adjust(float x) const = 0;
    float get_point(float x) const
    {
        return adjust(x) * x;
    }
    
    virtual ~Curve(){};
};

class Simple final: public Curve
{
public:
    float adjust( float x ) const override final
    {
        return x*0.8;
    }
    virtual ~Simple() override final {};
};

#endif


int main(int , char**)
{
    Simple s;
    std::cout << s.get_point(1) << std::endl;
    return 0;
}