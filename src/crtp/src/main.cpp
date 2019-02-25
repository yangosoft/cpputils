#include <iostream>



#ifdef CRTP
template <typename T>
class Curve
{
public:
    float getPoint(float x) 
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
    float getPoint(float x) const
    {
        return adjust(x) * x;
    }
    
    virtual ~Curve() = default;
};

class Simple final: public Curve
{
public:
    float adjust( float x ) const final
    {
        return x*0.8f;
    }
    ~Simple() final = default;
};

#endif


int main(int /*argc*/ , char** /*argv*/)
{
    Simple s;
    std::cout << s.getPoint(1) << std::endl;
    return 0;
}