#pragma once
#include <SFML/Graphics.hpp>

class Basic_Logic_Components {
public:
    int x_pos = 0;
    int y_pos = 0;
    int width = 200;
    int height = 200;
    float scale = 0.5;
    std::string png_name = "";
    sf::Sprite sprite;
    sf::Texture texture;
    sf::CircleShape in_1;
    sf::CircleShape in_2;
    sf::CircleShape out;

    void create(int x, int y);
    void move(int x, int y);
    bool on_click(int x, int y);
    void draw(sf::RenderWindow* window);
};

class OR : public Basic_Logic_Components {
public:
    OR(); 
    void a();
};

class AND : public Basic_Logic_Components {
public:
    AND();
    void a();
};

class NOR : public Basic_Logic_Components {
public:
    NOR();
    void a();
};

class NAND : public Basic_Logic_Components {
public:
    NAND();
    void a();
};

class XOR : public Basic_Logic_Components {
public:
    XOR();
    void a();
};

class XNOR : public Basic_Logic_Components {
public:
    XNOR();
    void a();
};


class Connection_Wires {

    Basic_Logic_Components* in{};
    Basic_Logic_Components* out{};
    int x_in_pos = 0;
    int y_in_pos = 0;
    int x_out_pos = 0;
    int y_out_pos = 0;
    bool on = false;
    bool straight_line = false;

    void is_on();
};

