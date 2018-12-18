#include <iostream>
#include <signal/signal.h>

int main()
{

 CppUtils::Signal<int, int> onEvent;

 onEvent.bind([](int a, int b) {
    std::cout << "Event triggered " << a << ", " << b << "\n";
 });

  onEvent.trigger(10, 20);

  return 0;
}
