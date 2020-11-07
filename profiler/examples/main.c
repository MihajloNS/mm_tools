#include <stdio.h>
#include <unistd.h>

#include "profiler.h"

void b()
{
    profiler_timer_start(__FUNCTION__);
    usleep(50000);
    profiler_timer_stop(__FUNCTION__);
}

int main()
{
    profiler_start_session("test-main-c", "results-c.json");

    b();

    profiler_end_session();
    return 0;
}