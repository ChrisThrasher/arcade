#include "Timer.h"

#include <ncurses.h>

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
    ss << std::setw(2) << seconds.count() << ':';
    ss << std::setw(2) << milliseconds.count() / 10;
    return ss.str();
}

void Print(int row, int col, const std::string& text, int color = 0)
{
    attron(color);
    mvaddstr(row, col, text.c_str());
    attroff(color);
}

int main()
{
    initscr();
    cbreak();
    noecho();
    clear();
    keypad(stdscr, TRUE);
    timeout(50);
    std::atexit([]() { endwin(); });

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
        Print(row++, 0, "========Controls========");
        Print(row++, 0, "SPACE: Start/stop timer");
        Print(row++, 0, "s: Save time");
        Print(row++, 0, "d: Delete last time");
        Print(row++, 0, "r: Reset");
        Print(row++, 0, "q: Quit");

        ++row;
        Print(row++, 9, FormatDuration(timer.Query()));

        ++row;
        Print(row++, 0, "==========Times=========");
        auto sorted_times = times;
        std::sort(sorted_times.begin(), sorted_times.end());
        for (size_t i = 0; i < times.size(); ++i) {
            Print(row, 0, std::to_string(i + 1));
            Print(row, 5, FormatDuration(times[i]));
            auto color = 0;
            if (i == 0)
                color = COLOR_PAIR(1);
            else if (i == times.size() - 1)
                color = COLOR_PAIR(2);
            Print(row++, 17, FormatDuration(sorted_times[i]), color);
        }
        if (!times.empty()) {
            ++row;
            auto average = std::accumulate(times.begin(), times.end(), std::chrono::nanoseconds(0)) / times.size();
            Print(row++, 0, "Average: " + FormatDuration(average));
        }
        if (sorted_times.size() >= 3) {
            auto mid_avg
                = std::accumulate(sorted_times.begin() + 1, sorted_times.end() - 1, std::chrono::nanoseconds(0))
                / (sorted_times.size() - 2);
            Print(row++, 0, "Mid avg: " + FormatDuration(mid_avg));
        }
        move(row, 0);

        refresh();
    }
}
