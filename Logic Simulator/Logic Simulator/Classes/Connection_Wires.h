#pragma once
#include "Basic_Logic_Components.h"
#include "Button.h"
#include "Led.h"

class Basic_Logic_Components;
class Led;
class Button;

class Connection_Wires {
public:
    int id;
    Basic_Logic_Components* out_basic{};
    Led* out_led{};
    Basic_Logic_Components* input_basic{};
    Button* input_button{};

    int x_in_pos = 0;
    int y_in_pos = 0;
    int x_out_pos = 0;
    int y_out_pos = 0;
    int input_number = 0;
    
    bool to_delete = false;
    bool on = false;
    bool connected = false;
    bool input_button_bool = false;
    bool output_led = false;

    void create(int x, int y, Basic_Logic_Components* in_logic, Button* in_button);
    void create_output(int num, Basic_Logic_Components* out_logic, Led* out_led_pass);
    void output();
    void output_move();
    void draw_cable(sf::RenderWindow* window);
};


