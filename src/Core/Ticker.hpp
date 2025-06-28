#include <chrono>

struct Ticker
{
    using clock = std::chrono::steady_clock;
    std::chrono::milliseconds interval;
    clock::time_point lastTick;

    explicit Ticker(int ms_interval)
        : interval(ms_interval)
        , lastTick(clock::now())
    {
    }

    // Проверка, пора ли обновлять
    bool tick()
    {
        auto now = clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastTick) >= interval)
        {
            lastTick = now;
            return true;
        }
        return false;
    }
};
