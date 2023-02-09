#include "Led.h"
#include "Basic_Logic_Components.h"
#include <iostream>

Led::Led()
{
    in.setFillColor(sf::Color::Color(255, 255, 255, 255)); 
}

void Led::create(int x, int y) // tworzenie bloczka dodawanie tekstur i pozycjonowanie 
{
    x_pos = x;
    y_pos = y;
    if (!texture_on.loadFromFile("Assets/light_on.png"))
        throw std::invalid_argument("File Not Find Assets/light_on.png");
    if (!texture_off.loadFromFile("Assets/light_off.png"))
        throw std::invalid_argument("File Not Find Assets/light_on.png");
    sprite_on.setTexture(texture_on);
    sprite_off.setTexture(texture_off);
    sprite_on.setScale(sf::Vector2f(scale, scale));
    sprite_off.setScale(sf::Vector2f(scale, scale));
    sprite_on.setPosition(sf::Vector2f(-1000, -1000));
    sprite_off.setPosition(sf::Vector2f(x_pos, y_pos));
    in.setRadius(15.0f * scale);
    in.setPosition(x_pos - width / 3 * scale, y_pos + height / 3 * scale);
}

void Led::move(int x, int y) // porusznie ledów 
{
    x_pos = x - width / 2;
    y_pos = y - height / 2;
    if (input_active)
    {
        sprite_on.setPosition(sf::Vector2f(x_pos, y_pos));
        sprite_off.setPosition(sf::Vector2f(x_pos, y_pos - 2000));
    }
    else
    {
        sprite_on.setPosition(sf::Vector2f(x_pos, y_pos - 2000));
        sprite_off.setPosition(sf::Vector2f(x_pos, y_pos));
    }

    in.setPosition(x_pos - width / 3 * scale, y_pos + height / 3 * scale);
}

void Led::connected() // zapalanie i gaszenie leda 
{
    if (input_active)
    {
        sprite_on.setPosition(sf::Vector2f(x_pos, y_pos));
        sprite_off.setPosition(sf::Vector2f(x_pos, y_pos - 2000));
        in.setFillColor(sf::Color::Green);
    }
    else
    {
        sprite_on.setPosition(sf::Vector2f(x_pos, y_pos - 2000));
        sprite_off.setPosition(sf::Vector2f(x_pos, y_pos));
        in.setFillColor(sf::Color::Color(255, 255, 255, 255));
    }
}

bool Led::on_click(int x, int y) // czy naciœniêty 
{
    return bool(x_pos < x&& x < x_pos + width * scale && y_pos < y&& y < y_pos + height * scale);
}

bool Led::input_on_click(int x, int y) // czy wejœcie naciœniête 
{
    return bool(sqrt(pow((x_pos - width / 3 * scale) - x, 2) + pow((y_pos + height / 3 * scale) - y, 2)) <= 3 * 15.0f * scale);
}

void Led::draw(sf::RenderWindow* window) // rysowanie 
{
    window->draw(sprite_on);
    window->draw(sprite_off);
    window->draw(in);
}
