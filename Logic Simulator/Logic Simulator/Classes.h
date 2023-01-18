#pragma once
#include <SFML/Graphics.hpp>

class Connection_Wires;

class Basic_Logic_Components {
public:
    Basic_Logic_Components();
    
    std::vector<Connection_Wires>* output_list;
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
    std::string png_name = "";
    sf::Sprite sprite;
    sf::Texture texture;
    sf::CircleShape in_1;
    sf::CircleShape in_2;
    sf::CircleShape out;
    bool logic_value_tab[2][2];
    
    void create(int x, int y);
    void move(int x, int y);
    bool on_click(int x, int y);
    bool input1_on_click(int x, int y);
    bool input2_on_click(int x, int y);
    bool output_on_click(int x, int y, std::vector<Connection_Wires>* vector);
    void draw(sf::RenderWindow* window);
    void output();

};

class OR : public Basic_Logic_Components {
public:
    OR(); 
    void output();
};

class AND : public Basic_Logic_Components {
public:
    AND();
    void output();
};

class NOR : public Basic_Logic_Components {
public:
    NOR();
    void output();
};

class NAND : public Basic_Logic_Components {
public:
    NAND();
    void output();
};

class XOR : public Basic_Logic_Components {
public:
    XOR();
    void output();
};

class XNOR : public Basic_Logic_Components {
public:
    XNOR();
    void output();
};

class Connection_Wires {
public:
    Basic_Logic_Components* out{};
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
    void draw_cable(sf::RenderWindow * window);
};

