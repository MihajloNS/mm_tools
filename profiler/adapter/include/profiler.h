#ifndef __PROFILER_H__
#define __PROFILER_H__

#ifdef __cplusplus
extern "C"
{
#endif

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
void profiler_start_session(const char* name, const char* filerPath);

/**
 * @brief End profiler session
 *
 * @param None
 *
 * @remarks None
 *
 * @return None
 */
void profiler_end_session();

/**
 * @brief Start profiler timer
 *
 * @param [in] name - function name
 *
 * @remarks None
 *
 * @return None
 */
void profiler_timer_start(const char* name);

/**
 * @brief Stop profiler timer
 *
 * @param None
 *
 * @remarks None
 *
 * @return None
 */
void profiler_timer_stop();

#ifdef __cplusplus
}
#endif

#endif //__PROFILER_H__