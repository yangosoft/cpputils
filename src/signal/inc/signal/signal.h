#ifndef __sgsignals_h__
#define __sgsignals_h__

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
        for (auto f : lstFunctions) {
            f(values...);
        }
    }
};
}

#endif
