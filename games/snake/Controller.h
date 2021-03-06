#pragma once

#include "Game.h"

class Controller {
    void GetInput();
    void Draw();

    Game m_game {};
    bool m_running { true };

public:
    Controller();
    ~Controller();

    void Cycle();
    bool Running();
};
