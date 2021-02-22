#include "Timer.h"

#include <Tui/Tui.h>

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <numeric>
#include <sstream>
#include <thread>
#include <vector>

auto FormatDuration(std::chrono::nanoseconds duration)
{
    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration -= minutes);
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration -= seconds);

    std::stringstream ss;
    ss << std::setfill('0');
    ss << std::setw(1) << minutes.count() << ':';
    ss << std::setw(2) << seconds.count() << '.';
    ss << std::setw(2) << milliseconds.count() / 10;
    return ss.str();
}

int main()
{
    tui::Init();
    timeout(50);

    start_color();
    use_default_colors();
    init_pair(1, COLOR_GREEN, -1);
    init_pair(2, COLOR_RED, -1);

    std::vector<std::chrono::nanoseconds> times;
    Timer timer;
    for (;;) {
        switch (getch()) {
        case ' ':
            timer.StartStop();
            break;
        case 's':
            if (timer.Query() != std::chrono::nanoseconds(0))
                times.push_back(timer.Query());
            timer.Stop();
            timer.Reset();
            break;
        case 'd':
            if (!times.empty())
                times.pop_back();
            break;
        case 'r':
            timer.Reset();
            break;
        case 'q':
            return 0;
        }

        clear();

        auto row = 0;
        tui::Print(row++, 0, "========Controls========");
        tui::Print(row++, 0, "SPACE: Start/stop timer");
        tui::Print(row++, 0, "s: Save time");
        tui::Print(row++, 0, "d: Delete last time");
        tui::Print(row++, 0, "r: Reset");
        tui::Print(row++, 0, "q: Quit");

        ++row;
        tui::Print(row++, 9, FormatDuration(timer.Query()));

        ++row;
        tui::Print(row++, 0, "==========Times=========");
        auto sorted_times = times;
        std::sort(sorted_times.begin(), sorted_times.end());
        for (size_t i = 0; i < times.size(); ++i) {
            tui::Print(row, 0, std::to_string(i + 1));

            auto color = 0;
            if (times[i] == sorted_times.front())
                color = COLOR_PAIR(1);
            else if (times[i] == sorted_times.back())
                color = COLOR_PAIR(2);
            tui::Print(row, 5, FormatDuration(times[i]), color);

            auto sorted_color = 0;
            if (i == 0)
                sorted_color = COLOR_PAIR(1);
            else if (i == times.size() - 1)
                sorted_color = COLOR_PAIR(2);
            tui::Print(row++, 17, FormatDuration(sorted_times[i]), sorted_color);
        }
        if (!times.empty()) {
            ++row;
            auto average = std::accumulate(times.begin(), times.end(), std::chrono::nanoseconds(0)) / times.size();
            tui::Print(row++, 0, "Average: " + FormatDuration(average));
        }
        if (sorted_times.size() >= 3) {
            auto mid_avg
                = std::accumulate(sorted_times.begin() + 1, sorted_times.end() - 1, std::chrono::nanoseconds(0))
                / (sorted_times.size() - 2);
            tui::Print(row++, 0, "Mid avg: " + FormatDuration(mid_avg));
        }

        refresh();
    }
}
