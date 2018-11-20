#ifndef __sgsignals_h__
#define __sgsignals_h__


#include <algorithm>
#include <list>
#include <memory>

#include <functional>

namespace CppUtils
{
template <typename... Values>
class Signal
{
    using Function = std::function<void(Values...)>;
    using LstFunction = std::list<Function>;
private:

    LstFunction lstFunctions;

public:
    void bind(Function f)
    {
        lstFunctions.push_back(f);
    }
    void trigger(Values... values)
    {
        std::for_each(lstFunctions.begin(), lstFunctions.end(), [this](auto f){ 
            f(values...);
        });
    }
};
}

#endif
