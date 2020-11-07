#ifndef __PROFILER_HPP__
#define __PROFILER_HPP__

#include <algorithm>
#include <chrono>
#include <fstream>
#include <mutex>
#include <string>
#include <thread>

namespace mm_profiler
{

/**
 * @brief Profiler result structure
 */
struct ProfilerResult
{
    std::string name;
    long long startTime;
    long long endTime;
    std::size_t threadId;
};

/**
 * \class Profiler
 */
class Profiler
{
public:
    virtual ~Profiler() {}

    static Profiler& Get()
    {
        static std::unique_ptr<Profiler> instance;
        if (instance == nullptr)
        {
            instance.reset(new Profiler);
        }

        return *instance;
    }

    void BeginSession(const std::string& name, const std::string& filepath = "results.json")
    {
        mSession = name;
        mOutputStream.open(filepath);
        WriteHeader();
    }

    void EndSession()
    {
        WriteFooter();
        mOutputStream.close();
        mProfileCount = 0;
    }

    void Write(const ProfilerResult& result)
    {
        std::lock_guard<std::mutex> lock(mMutex);

        if (mProfileCount++ > 0)
        {
            mOutputStream << ",";
        }

        std::string name = result.name;
        std::replace(name.begin(), name.end(), '"', '\'');

        mOutputStream << "{";
        mOutputStream << "\"cat\":\"function\",";
        mOutputStream << "\"dur\":" << (result.endTime - result.startTime) << ',';
        mOutputStream << "\"name\":\"" << name << "\",";
        mOutputStream << "\"ph\":\"X\",";
        mOutputStream << "\"pid\":0,";
        mOutputStream << "\"tid\":" << result.threadId << ",";
        mOutputStream << "\"ts\":" << result.startTime;
        mOutputStream << "}";

        mOutputStream.flush();
    }

private:
    std::ofstream mOutputStream;
    int mProfileCount;
    std::string mSession;
    std::mutex mMutex;

    Profiler() : mProfileCount(0), mSession("") {}

    void WriteHeader()
    {
        mOutputStream << "{\"otherData\": {},\"traceEvents\":[";
        mOutputStream.flush();
    }

    void WriteFooter()
    {
        mOutputStream << "]}";
        mOutputStream.flush();
    }
};

/**
 * \class ProfilerTimer
 */
class ProfilerTimer
{
public:
    ProfilerTimer(const char* name)
        : mName(name), mStopped(false)
    {
        mStartTimepoint = std::chrono::high_resolution_clock::now();
    }

    ~ProfilerTimer()
    {
        if (!mStopped)
        {
            Stop();
        }
    }

private:
    const char* mName;
    std::chrono::time_point<std::chrono::high_resolution_clock> mStartTimepoint;
    bool mStopped;

    void Stop()
    {
        auto endTimepoint = std::chrono::high_resolution_clock::now();

        long long start = std::chrono::time_point_cast<std::chrono::microseconds>(mStartTimepoint).time_since_epoch().count();
        long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

        std::size_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
        Profiler::Get().Write({mName, start, end, threadID});

        mStopped = true;
    }
};

}
#endif //__PROFILER_HPP__