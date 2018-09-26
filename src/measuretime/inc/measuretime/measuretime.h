#ifndef MEASURETIME_H
#define MEASURETIME_H

#include <chrono>
#include <utility>

namespace CppUtils {




/**
 * @todo write docs
 */


template<typename TimeT = std::chrono::milliseconds>
struct MeasureTime{
template<typename F, typename ...Args>
static auto execute(F&& func, Args&&... args)
{
    auto start = std::chrono::steady_clock::now();
    std::forward<decltype(func)>(func)(std::forward<Args>(args)...);
    return std::chrono::duration_cast<TimeT>(std::chrono::steady_clock::now()-start);
} 

};
}

#endif // MEASURETIME_H
