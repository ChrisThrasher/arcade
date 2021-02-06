#include "Controller.h"

#include <chrono>
#include <thread>

int main()
{
    Controller controller;

    const auto period = std::chrono::milliseconds(100);
    auto time = std::chrono::steady_clock::now();
    while (controller.Running()) {
        controller.Cycle();

        const auto elapsed = std::chrono::steady_clock::now() - time;
        std::this_thread::sleep_for(period - elapsed);
        time = std::chrono::steady_clock::now();
    }
}
