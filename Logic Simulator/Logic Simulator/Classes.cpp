#pragma once
#include "Classes.h"
#include <SFML/Graphics.hpp>

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

bool Basic_Logic_Components::output_on_click(int x, int y, std::vector<Connection_Wires>* vector)
{
    if (x_pos < x && x < x_pos + width * scale && y_pos < y && y < y_pos + height * scale)
    {
       Connection_Wires wire;
        wire.x_in_pos = x_pos + width * 1.2 * scale;
        wire.y_in_pos = y_pos + height * 2 / 5 * scale;
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

}

OR::OR()
{
    png_name = "Assets/OR.png";
}

void OR::output()
{
    if (output_active)
        out.setFillColor(sf::Color::Green);
    else 
        out.setFillColor(sf::Color::Color(255, 255, 255, 100));
}

AND::AND()
{
    png_name = "Assets/AND.png";
}

void AND::output()
{
    if (output_active)
        out.setFillColor(sf::Color::Green);
    else
        out.setFillColor(sf::Color::Color(255, 255, 255, 100));
}

NOR::NOR()
{
    png_name = "Assets/NOR.png";
    output_active = true;
    output();
}

void NOR::output()
{
    if (output_active)
        out.setFillColor(sf::Color::Green);
    else
        out.setFillColor(sf::Color::Color(255, 255, 255, 100));
}

NAND::NAND()
{
    png_name = "Assets/NAND.png";
    output_active = true;
    output();
}

void NAND::output()
{
    if (output_active)
        out.setFillColor(sf::Color::Green);
    else
        out.setFillColor(sf::Color::Color(255, 255, 255, 100));
}

XOR::XOR()
{
    png_name = "Assets/XOR.png";
}

void XOR::output()
{
    if (output_active)
        out.setFillColor(sf::Color::Green);
    else
        out.setFillColor(sf::Color::Color(255, 255, 255, 100));
}

XNOR::XNOR()
{
    png_name = "Assets/XNOR.png";
    output_active = true;
    output();
}

void XNOR::output()
{
    if (output_active)
        out.setFillColor(sf::Color::Green);
    else
        out.setFillColor(sf::Color::Color(255, 255, 255, 100));
}

void Connection_Wires::input(bool active)
{
    on = active;
}

void Connection_Wires::output_created()
{
    out->output_active = on;
    out->output();
}

void Connection_Wires::input_move(int x, int y) 
{
    x_in_pos = x;
    y_in_pos = y;
}

void Connection_Wires::output()
{

}