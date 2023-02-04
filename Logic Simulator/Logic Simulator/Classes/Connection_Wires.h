#pragma once
#include "Basic_Logic_Components.h"

class Connection_Wires{
public:
    Basic_Logic_Components * out{};
    int x_in_pos = 0;
    int y_in_pos = 0;
    int x_out_pos = 0;
    int y_out_pos = 0;

    bool on = false;
    bool straight_line = false;
    bool connected = false;

    void input(bool active);
    void input_move(int x, int y);
    void output_created();
    void output();
    void draw_cable(sf::RenderWindow* window);
};


