#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include "Connection_Wires.h"

class Connection_Wires;

class Basic_Logic_Components {
public:
    Basic_Logic_Components();

    std::vector<Connection_Wires*> output_list;
    int id;
    std::string type;

    int x_pos = 0;
    int y_pos = 0;
    int width = 200;
    int height = 200;
    float scale = 0.5;

    bool input1_connect = false;
    bool input2_connect = false;
    bool input1_active = false;
    bool input2_active = false;
    bool output_active = false;
    bool logic_value_tab[2][2];

    std::string png_name = "";
    sf::Sprite sprite;
    sf::Texture texture;
    sf::CircleShape in_1;
    sf::CircleShape in_2;
    sf::CircleShape out;
    Connection_Wires* wire;

    void create(int x, int y);
    void move(int x, int y);
    bool on_click(int x, int y);
    bool input1_on_click(int x, int y);
    bool input2_on_click(int x, int y);
    bool output_on_click(int x, int y);
    void draw(sf::RenderWindow* window);
    void output();

};