#include "Controller.hpp"

#include <cxxcurses/cxxcurses.hpp>

#include <chrono>
#include <thread>

int main()
{
    const cxxcurses::terminal init;

    Controller controller;

    const auto period = std::chrono::milliseconds(100);
    auto time = std::chrono::steady_clock::now();
    while (controller.running()) {
        controller.cycle();

        const auto elapsed = std::chrono::steady_clock::now() - time;
        std::this_thread::sleep_for(period - elapsed);
        time = std::chrono::steady_clock::now();
    }
}
