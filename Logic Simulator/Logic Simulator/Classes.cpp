#pragma once
#include "Classes.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Basic_Logic_Components::Basic_Logic_Components()
{
    in_1.setFillColor(sf::Color::Color(255, 255, 255, 100));
    in_2.setFillColor(sf::Color::Color(255, 255, 255, 100));
    out.setFillColor(sf::Color::Color(255, 255, 255, 100));
}

void Basic_Logic_Components::create(int x, int y)
{
    x_pos = x;
    y_pos = y;
    texture.loadFromFile(png_name);
    sprite.setTexture(texture);
    sprite.setScale(sf::Vector2f(scale, scale));
    sprite.setPosition(sf::Vector2f(x_pos, y_pos));
    in_1.setRadius(15.0f * scale);
    in_1.setPosition(x_pos - width / 3 * scale, y_pos + height/5 * scale);
    in_2.setRadius(15.0f * scale);
    in_2.setPosition(x_pos - width / 3 * scale, y_pos + height *2/ 3 * scale);
    out.setRadius(15.0f * scale);
    out.setPosition(x_pos + width * 1.2 * scale, y_pos + height * 2 / 5 * scale);

}

void Basic_Logic_Components::move(int x, int y)
{
    if (x - width / 2 > 10 && y - height / 2 > 20)
    {
        x_pos = x - width / 2;
        y_pos = y - height / 2;
        sprite.setPosition(sf::Vector2f(x_pos, y_pos));
        in_1.setPosition(x_pos - width / 3 * scale, y_pos + height / 5 * scale);
        in_2.setPosition(x_pos - width / 3 * scale, y_pos + height * 2 / 3 * scale);
        out.setPosition(x_pos + width * 1.2 * scale, y_pos + height *2/5 * scale);
    }
}

bool Basic_Logic_Components::on_click(int x, int y)
{
    return bool(x_pos < x&& x < x_pos + width * scale && y_pos < y&& y < y_pos + height * scale);
}

bool Basic_Logic_Components::input1_on_click(int x, int y)
{
    return bool(sqrt(pow((x_pos - width / 3 * scale) - x, 2) + pow((y_pos + height / 5 * scale) - y, 2)) <= 3*15.0f * scale);
}

bool Basic_Logic_Components::input2_on_click(int x, int y)
{
    return bool(sqrt(pow((x_pos - width / 3 * scale) - x, 2) + pow((y_pos + height * 2 / 3 * scale) - y, 2)) < 3* 15.0f * scale);
}


bool Basic_Logic_Components::output_on_click(int x, int y, std::vector<Connection_Wires>* vector)
{
    if (sqrt(pow((x_pos + width * 1.2 * scale) - x, 2) + pow((y_pos + height * 2 / 5 * scale) - y, 2)) <= 3 * 15.0f * scale)
    {
       Connection_Wires wire;
        wire.x_in_pos = x_pos + width * 1.2 * scale + 15.0f * scale / 2;
        wire.y_in_pos = y_pos + height * 2 / 5 * scale + 15.0f * scale / 2;
        wire.input(output_active);
        vector->push_back(wire);
        return true;
    }
    return false;
}

void Basic_Logic_Components::draw(sf::RenderWindow* window)
{
    window -> draw(sprite);
    window -> draw(in_1);
    window -> draw(in_2);
    window -> draw(out);
}

void Basic_Logic_Components::output()
{
    output_active = logic_value_tab[input1_active][input2_active];
    if (output_active)
        out.setFillColor(sf::Color::Green);
    else
        out.setFillColor(sf::Color::Color(255, 255, 255, 100));

    if (input1_active)
        in_1.setFillColor(sf::Color::Green);
    else
        in_1.setFillColor(sf::Color::Color(255, 255, 255, 100));

    if (input2_active)
        in_2.setFillColor(sf::Color::Green);
    else
        in_2.setFillColor(sf::Color::Color(255, 255, 255, 100));
    for (int i = 0; i < output_list.size(); i++)
    {
        output_list[i]->on = output_active;
        output_list[i]->output();
    }
}

OR::OR()
{
    png_name = "Assets/OR.png";
    logic_value_tab[1][1] = true;
    logic_value_tab[0][1] = true;
    logic_value_tab[1][0] = true;
    logic_value_tab[0][0] = false;
}

AND::AND()
{
    png_name = "Assets/AND.png";
    logic_value_tab[1][1] = true;
    logic_value_tab[0][1] = false;
    logic_value_tab[1][0] = false;
    logic_value_tab[0][0] = false;
}

NOR::NOR()
{
    png_name = "Assets/NOR.png";
    output_active = true;
    logic_value_tab[1][1] = false;
    logic_value_tab[0][1] = false;
    logic_value_tab[1][0] = false;
    logic_value_tab[0][0] = true;
    output();
}

NAND::NAND()
{
    png_name = "Assets/NAND.png";
    output_active = true;
    logic_value_tab[1][1] = false;
    logic_value_tab[0][1] = true;
    logic_value_tab[1][0] = true;
    logic_value_tab[0][0] = true;
    output();
}

XOR::XOR()
{
    png_name = "Assets/XOR.png";
    logic_value_tab[1][1] = false;
    logic_value_tab[0][1] = true;
    logic_value_tab[1][0] = true;
    logic_value_tab[0][0] = false;
}

XNOR::XNOR()
{
    png_name = "Assets/XNOR.png";
    output_active = true;
    logic_value_tab[1][1] = true;
    logic_value_tab[0][1] = false;
    logic_value_tab[1][0] = false;
    logic_value_tab[0][0] = true;
    output();

}

void Connection_Wires::input(bool active)
{
    on = active;
    if (connected)
        output_created();
}

void Connection_Wires::output_created()
{
    
}

void Connection_Wires::input_move(int x, int y) 
{
    x_in_pos = x;
    y_in_pos = y;
}

void Connection_Wires::output()
{
    out->output_active = on;
    out->output();
}

void Connection_Wires::draw_cable(sf::RenderWindow* window)
{
    if (!straight_line)
    {
        sf::RectangleShape rec;
        rec.setPosition(sf::Vector2f(x_in_pos, y_in_pos));
        rec.setSize(sf::Vector2f(sqrt(pow(x_in_pos - x_out_pos, 2) + pow(y_in_pos - y_out_pos, 2)), 5));
        if (!on)
            rec.setFillColor(sf::Color::Color(255, 255, 255, 100));
        else
            rec.setFillColor(sf::Color::Green);
        if (x_out_pos - x_in_pos != 0)
        {
            if (x_out_pos - x_in_pos > 0)
                rec.setRotation(atan(float(y_out_pos - y_in_pos) / float(x_out_pos - x_in_pos)) * 180 / 3.1415);
            else
                rec.setRotation(180 + atan(float(y_out_pos - y_in_pos) / float(x_out_pos - x_in_pos)) * 180 / 3.1415);
        }
        else
        {
            if (y_in_pos > y_out_pos)
                rec.rotate(-90);
            else
                rec.rotate(90);
        }
        window->draw(rec);
    }
    else
    {
        sf::RectangleShape rec[3];
        if (abs(x_in_pos - x_out_pos) > abs(y_in_pos - y_out_pos))
        {

        }
    }
}
