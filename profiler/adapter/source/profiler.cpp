#include "profiler.h"
#include "profiler.hpp"

void* profilerTimerObj;

/**
 * @brief Start profiler session
 *
 * @param [in] name - session name
 * @param [in] port - file path to the profiler result
 *
 * @remarks None
 *
 * @return None
 */
void profiler_start_session(const char* name, const char* filerPath)
{
    if (!name || !filerPath)
    {
        return;
    }

    mm_profiler::Profiler::Get().BeginSession(name, filerPath);
}

/**
 * @brief End profiler session
 *
 * @param None
 *
 * @remarks None
 *
 * @return None
 */
void profiler_end_session()
{
    mm_profiler::Profiler::Get().EndSession();
}

/**
 * @brief Start profiler timer
 *
 * @param [in] name - function name
 *
 * @remarks None
 *
 * @return None
 */
void profiler_timer_start(const char* name)
{
    if (!name)
    {
        return;
    }

    profilerTimerObj = new mm_profiler::ProfilerTimer(name);
}

/**
 * @brief Stop profiler timer
 *
 * @param None
 *
 * @remarks None
 *
 * @return None
 */
void profiler_timer_stop()
{
    delete static_cast<mm_profiler::ProfilerTimer*>(profilerTimerObj);
}