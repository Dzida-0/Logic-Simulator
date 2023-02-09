#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include "Connection_Wires.h"

class Connection_Wires;

class Button { // klasa przycisku
public:
    Button();

    std::vector<Connection_Wires*> output_list;

    int id;

    int x_pos = 0;
    int y_pos = 0;
    int width = 200;
    int height = 200;
    float scale = 0.5;

    bool output_active = false;
    bool hold = false;
    bool connected = false;

    sf::Sprite sprite_on, sprite_off;
    sf::Texture texture_on, texture_off;
    sf::CircleShape out;

    void create(int x, int y, bool hold_in);
    void move(int x, int y);
    bool on_click(int x, int y);
    bool output_on_click(int x, int y);
    void draw(sf::RenderWindow* window);
    void output(bool press, bool on);

};