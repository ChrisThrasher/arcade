#include "Scramble.h"
#include "Timer.h"

#include <Tui/Tui.h>

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <map>
#include <numeric>
#include <sstream>
#include <thread>
#include <vector>

static auto FormatDuration(std::chrono::nanoseconds duration)
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

static void DrawHeader()
{
    auto row = 0;
    tui::Draw(row++, 0, "=========Controls==========");
    tui::Draw(row++, 0, "SPACE: Start/stop timer");
    tui::Draw(row++, 0, "s: Save time");
    tui::Draw(row++, 0, "d: Delete time");
    tui::Draw(row++, 0, "r: Reset timer");
    tui::Draw(row++, 0, "i: Start inspection");
    tui::Draw(row++, 0, "g: Generate scramble");
    tui::Draw(row++, 0, "q: Quit");
}

static void DrawPuzzleName(int& row, const Puzzle puzzle)
{
    std::string puzzle_name;
    switch (puzzle) {
    case Puzzle::Cube2:
        puzzle_name = "2x2";
        break;
    case Puzzle::Cube3:
        puzzle_name = "3x3";
        break;
    case Puzzle::Cube4:
        puzzle_name = "4x4";
        break;
    case Puzzle::Cube5:
        puzzle_name = "5x5";
        break;
    }
    tui::Draw(row++, 12, puzzle_name);
}

static void DrawScramble(int& row, const Scramble& scramble)
{
    if (scramble.empty())
        return;

    const auto width = std::max_element(scramble.begin(),
                                        scramble.end(),
                                        [](const auto& lhs, const auto& rhs) { return lhs.length() < rhs.length(); })
                           ->length()
        + 1;

    const auto break_point = 28 / width;
    for (size_t i = 0; i < scramble.size(); ++i) {
        tui::Draw(row, (i % break_point) * width, scramble[i]);

        const bool end_of_row = (i + 1) % break_point == 0;
        const bool not_last_element = i + 1 < scramble.size();
        if (end_of_row && not_last_element)
            ++row;
    }
    ++row;
}

static void DrawTimer(int& row, Timer& timer, bool& inspecting)
{
    using namespace std::chrono_literals;

    ++row;
    auto time = timer.Query();
    auto color = 0;
    if (inspecting) {
        if (time > 15s) {
            timer.Reset();
            inspecting = false;
        } else {
            time = 15s - time;
            if (time < 8s)
                color = tui::red;
            else
                color = tui::yellow;
        }
    }

    tui::Draw(row++, 10, FormatDuration(time), color);
}

static void DrawTimes(int& row, const std::vector<std::chrono::nanoseconds>& times)
{
    ++row;
    tui::Draw(row++, 0, "===========Times===========");
    auto sorted_times = times;
    std::sort(sorted_times.begin(), sorted_times.end());
    for (size_t i = 0; i < times.size(); ++i) {
        tui::Draw(row, 1, std::to_string(i + 1));

        int color = 0;
        if (times.size() <= 1)
            color = 0;
        else if (times[i] == sorted_times.front())
            color = tui::green;
        else if (times[i] == sorted_times.back())
            color = tui::red;
        tui::Draw(row, 6, FormatDuration(times[i]), color);

        int sorted_color = 0;
        if (sorted_times.size() <= 1)
            sorted_color = 0;
        else if (i == 0)
            sorted_color = tui::green;
        else if (i == times.size() - 1)
            sorted_color = tui::red;
        tui::Draw(row++, 18, FormatDuration(sorted_times[i]), sorted_color);
    }
    if (!times.empty()) {
        ++row;
        auto average = std::accumulate(times.begin(), times.end(), std::chrono::nanoseconds(0)) / times.size();
        tui::Draw(row++, 0, "Average: " + FormatDuration(average));
    }
    if (sorted_times.size() >= 3) {
        auto mid_avg = std::accumulate(sorted_times.begin() + 1, sorted_times.end() - 1, std::chrono::nanoseconds(0))
            / (sorted_times.size() - 2);
        tui::Draw(row++, 0, "Mid avg: " + FormatDuration(mid_avg));
    }
}

int main()
{
    tui::Init();
    timeout(10);

    DrawHeader();

    auto times = std::map<Puzzle, std::vector<std::chrono::nanoseconds>>();
    auto puzzle = Puzzle::Cube3;
    auto scramble = GenerateScramble(puzzle);
    auto timer = Timer();
    auto inspecting = false;
    for (;;) {
        switch (getch()) {
        case ' ':
            if (inspecting) {
                timer.Stop();
                timer.Reset();
                timer.Start();
                inspecting = false;
            } else {
                timer.Toggle();
            }
            break;
        case 's':
            if (timer.Query() != std::chrono::nanoseconds(0) && !inspecting) {
                times[puzzle].push_back(timer.Query());
                timer.Stop();
                timer.Reset();
                scramble = GenerateScramble(puzzle);
            }
            break;
        case 'd':
            if (!times[puzzle].empty())
                times[puzzle].pop_back();
            break;
        case 'r':
            timer.Stop();
            timer.Reset();
            inspecting = false;
            break;
        case 'i':
            if (!inspecting && !timer.Running()) {
                timer.Stop();
                timer.Reset();
                timer.Start();
                inspecting = true;
            }
            break;
        case 'g':
            scramble = GenerateScramble(puzzle);
            break;
        case '2':
            if (puzzle != Puzzle::Cube2)
                scramble = GenerateScramble(puzzle = Puzzle::Cube2);
            break;
        case '3':
            if (puzzle != Puzzle::Cube3)
                scramble = GenerateScramble(puzzle = Puzzle::Cube3);
            break;
        case '4':
            if (puzzle != Puzzle::Cube4)
                scramble = GenerateScramble(puzzle = Puzzle::Cube4);
            break;
        case '5':
            if (puzzle != Puzzle::Cube5)
                scramble = GenerateScramble(puzzle = Puzzle::Cube5);
            break;
        case 'q':
            return 0;
        }

        auto row = 8;
        move(row, 0);
        clrtobot();

        DrawPuzzleName(row, puzzle);
        DrawScramble(row, scramble);
        DrawTimer(row, timer, inspecting);
        DrawTimes(row, times[puzzle]);

        refresh();
    }
}
