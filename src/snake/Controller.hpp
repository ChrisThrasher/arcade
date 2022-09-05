#pragma once

#include "Game.hpp"

class Controller {
    void get_input();
    void draw();

    Game m_game {};
    bool m_running { true };

public:
    Controller();
    ~Controller();

    void cycle();
    bool running() const { return m_running; }
};
