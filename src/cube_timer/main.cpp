#include "Scramble.h"
#include "Timer.h"

#include <Tui/Tui.h>

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <map>
#include <numeric>
#include <sstream>
#include <vector>

static auto format_duration(std::chrono::nanoseconds duration)
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

static void draw_header(int& row)
{
    ++row;
    tui::draw(row++, 0, "=========Controls==========");
    tui::draw(row++, 0, "SPACE: Start/stop timer");
    tui::draw(row++, 0, "s: Save time");
    tui::draw(row++, 0, "d: Delete time");
    tui::draw(row++, 0, "r: Reset timer");
    tui::draw(row++, 0, "i: Start inspection");
    tui::draw(row++, 0, "g: Generate scramble");
    tui::draw(row++, 0, "q: Quit");
}

static void draw_puzzle_name(int& row, const Puzzle puzzle)
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
    case Puzzle::Cube6:
        puzzle_name = "6x6";
        break;
    case Puzzle::Cube7:
        puzzle_name = "7x7";
        break;
    }
    tui::draw(row++, 12, puzzle_name);
}

static void draw_scramble(int& row, const Scramble& scramble)
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
        tui::draw(row, (i % break_point) * width, scramble[i]);

        const bool end_of_row = (i + 1) % break_point == 0;
        const bool not_last_element = i + 1 < scramble.size();
        if (end_of_row && not_last_element)
            ++row;
    }
    ++row;
}

static void draw_timer(int& row, Timer& timer, bool& inspecting)
{
    using namespace std::chrono_literals;

    ++row;
    auto time = timer.query();
    auto color = 0;
    if (inspecting) {
        if (time > 15s) {
            timer.reset();
            inspecting = false;
        } else {
            time = 15s - time;
            if (time < 8s)
                color = tui::red;
            else
                color = tui::yellow;
        }
    }

    tui::draw(row++, 10, format_duration(time), color);
}

static void draw_times(int& row, const std::vector<std::chrono::nanoseconds>& times)
{
    ++row;
    tui::draw(row++, 0, "===========Times===========");
    if (times.empty()) {
        tui::draw(row++, 0, "Press 's' to save a time");
        return;
    }

    auto sorted_times = times;
    std::sort(sorted_times.begin(), sorted_times.end());
    for (size_t i = 0; i < times.size(); ++i) {
        tui::draw(row, 1, std::to_string(i + 1));

        int color = 0;
        if (times.size() <= 1)
            color = 0;
        else if (times[i] == sorted_times.front())
            color = tui::green;
        else if (times[i] == sorted_times.back())
            color = tui::red;
        tui::draw(row, 6, format_duration(times[i]), color);

        int sorted_color = 0;
        if (sorted_times.size() <= 1)
            sorted_color = 0;
        else if (i == 0)
            sorted_color = tui::green;
        else if (i == times.size() - 1)
            sorted_color = tui::red;
        tui::draw(row++, 18, format_duration(sorted_times[i]), sorted_color);
    }
    if (!times.empty()) {
        ++row;
        auto average = std::accumulate(times.begin(), times.end(), std::chrono::nanoseconds(0)) / times.size();
        tui::draw(row++, 0, "Average: " + format_duration(average));
    }
    if (sorted_times.size() >= 3) {
        auto mid_avg = std::accumulate(sorted_times.begin() + 1, sorted_times.end() - 1, std::chrono::nanoseconds(0))
            / (sorted_times.size() - 2);
        tui::draw(row++, 0, "Mid avg: " + format_duration(mid_avg));
    }
}

int main()
{
    tui::init();
    timeout(10);

    auto times = std::map<Puzzle, std::vector<std::chrono::nanoseconds>>();
    auto puzzle = Puzzle::Cube3;
    auto scramble = generate_scramble(puzzle);
    auto timer = Timer();
    auto inspecting = false;
    for (;;) {
        switch (getch()) {
        case ' ':
            if (inspecting) {
                timer.restart();
                inspecting = false;
            } else {
                timer.toggle();
            }
            break;
        case 's':
            if (timer.query() != std::chrono::nanoseconds(0) && !inspecting) {
                times[puzzle].push_back(timer.query());
                timer.clear();
                scramble = generate_scramble(puzzle);
            }
            break;
        case 'd':
            if (!times[puzzle].empty())
                times[puzzle].pop_back();
            break;
        case 'r':
            timer.clear();
            inspecting = false;
            break;
        case 'i':
            if (!inspecting && !timer.running()) {
                timer.restart();
                inspecting = true;
            }
            break;
        case 'g':
            scramble = generate_scramble(puzzle);
            break;
        case '2':
            if (puzzle != Puzzle::Cube2)
                scramble = generate_scramble(puzzle = Puzzle::Cube2);
            break;
        case '3':
            if (puzzle != Puzzle::Cube3)
                scramble = generate_scramble(puzzle = Puzzle::Cube3);
            break;
        case '4':
            if (puzzle != Puzzle::Cube4)
                scramble = generate_scramble(puzzle = Puzzle::Cube4);
            break;
        case '5':
            if (puzzle != Puzzle::Cube5)
                scramble = generate_scramble(puzzle = Puzzle::Cube5);
            break;
        case '6':
            if (puzzle != Puzzle::Cube6)
                scramble = generate_scramble(puzzle = Puzzle::Cube6);
            break;
        case '7':
            if (puzzle != Puzzle::Cube7)
                scramble = generate_scramble(puzzle = Puzzle::Cube7);
            break;
        case 'q':
            return 0;
        }

        clear();

        auto row = 0;
        draw_puzzle_name(row, puzzle);
        draw_scramble(row, scramble);
        draw_timer(row, timer, inspecting);
        draw_times(row, times[puzzle]);
        draw_header(row);

        refresh();
    }
}
