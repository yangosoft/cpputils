#include "measuretime/measuretime.h"

#include <functional>
#include <iostream>
#include <chrono>

using namespace std;

void executeMe(int i)
{
    while (i > 0) {
        i--;
    }
}

int main()
{

    std::function<void(int)> fExec = executeMe;
    CppUtils::MeasureTime<std::chrono::milliseconds>::execute(fExec, 1000);
    

    return 0;
}
