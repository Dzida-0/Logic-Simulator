#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include "Connection_Wires.h"

class Connection_Wires;

class Led {
public:
    Led();
    Connection_Wires* input_wire;
    int id;

    int x_pos = 0;
    int y_pos = 0;
    int width = 200;
    int height = 200;
    float scale = 0.5;

    bool input_connect = false;
    bool input_active = false;

    sf::Sprite sprite_on, sprite_off;
    sf::Texture texture_on, texture_off;
    sf::CircleShape in;

    void create(int x, int y);
    void move(int x, int y);
    void connected();
    bool on_click(int x, int y);
    bool input_on_click(int x, int y);
    void draw(sf::RenderWindow* window);

};
