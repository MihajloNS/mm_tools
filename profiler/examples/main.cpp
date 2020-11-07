
#include <unistd.h>
#include <vector>

#include "profiler.hpp"

#define TIMEIT() mm_profiler::ProfilerTimer timer(__FUNCTION__);

void a()
{
    TIMEIT()
    usleep(50000);
}

void b()
{
    TIMEIT()
    usleep(50000);
}

void f1() {
    TIMEIT()
    usleep(200000);
    a();
}

void f2() {
    TIMEIT()
    usleep(200000);
    b();
}

void f3() {
    TIMEIT()
    usleep(200000);
    a();
    b();
}

int main()
{
    mm_profiler::Profiler::Get().BeginSession("test-main-cpp");

    std::vector<std::thread> workers;

    workers.push_back(std::thread(f1));
    workers.push_back(std::thread(f2));
    workers.push_back(std::thread(f3));

    for (auto& w : workers)
    {
        w.join();
    }

    mm_profiler::Profiler::Get().EndSession();

    return 0;
}