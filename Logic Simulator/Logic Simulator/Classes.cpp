#pragma once
#include "Classes.h"
#include <SFML/Graphics.hpp>

void Basic_Logic_Components::create(int x, int y)
{
    x_pos = x;
    y_pos = y;
    texture.loadFromFile(png_name);
    sprite.setTexture(texture);
    sprite.setScale(sf::Vector2f(scale, scale));
    sprite.setPosition(sf::Vector2f(x_pos, y_pos));
    in_1.setRadius(15.0f * scale);
    in_1.setFillColor(sf::Color::Cyan);
    in_1.setPosition(x_pos - width / 3 * scale, y_pos + height/5 * scale);
    in_2.setRadius(15.0f * scale);
    in_2.setFillColor(sf::Color::Cyan);
    in_2.setPosition(x_pos - width / 3 * scale, y_pos + height *2/ 3 * scale);
    out.setRadius(15.0f * scale);
    out.setFillColor(sf::Color::Cyan);
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

void Basic_Logic_Components::draw(sf::RenderWindow* window)
{
    window -> draw(sprite);
    window -> draw(in_1);
    window -> draw(in_2);
    window -> draw(out);
}

OR::OR()
{
    png_name = "Assets/OR.png";
}

AND::AND()
{
    png_name = "Assets/AND.png";
}

NOR::NOR()
{
    png_name = "Assets/NOR.png";
}

NAND::NAND()
{
    png_name = "Assets/NAND.png";
}

XOR::XOR()
{
    png_name = "Assets/XOR.png";
}

XNOR::XNOR()
{
    png_name = "Assets/XNOR.png";
}

void Connection_Wires::is_on()
{

}
