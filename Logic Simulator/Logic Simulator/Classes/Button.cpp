#include "Button.h"
#include <iostream>

Button::Button()
{
    out.setFillColor(sf::Color::Color(255, 255, 255, 255));
}

void Button::create(int x, int y, bool hold_in)
{
    x_pos = x;
    y_pos = y;
    hold = hold_in;
    if (hold)
    {
        if (!texture_on.loadFromFile("Assets/button_on.png"))
            std::cout << "f";
        if (!texture_off.loadFromFile("Assets/button_off.png"))
            std::cout << "f";
    }
    else
    {
        if (!texture_on.loadFromFile("Assets/button_press_on.png"))
            std::cout << "f";
        if (!texture_off.loadFromFile("Assets/button_press_off.png"))
            std::cout << "f";
    }
    sprite_on.setTexture(texture_on);
    sprite_off.setTexture(texture_off);
    sprite_on.setScale(sf::Vector2f(scale, scale));
    sprite_off.setScale(sf::Vector2f(scale, scale));
    sprite_on.setPosition(sf::Vector2f(x_pos, y_pos - 2000));
    sprite_off.setPosition(sf::Vector2f(x_pos, y_pos));
    out.setRadius(15.0f * scale);
    out.setPosition(x_pos + width * 1.2 * scale, y_pos + height * 2 / 5 * scale);

}

void Button::move(int x, int y)
{
    x_pos = x - width / 2;
    y_pos = y - height / 2;
    if (output_active)
    {
        sprite_off.setPosition(sf::Vector2f(x_pos, y_pos - 2000));
        sprite_on.setPosition(sf::Vector2f(x_pos, y_pos));
    }
    else
    {
        sprite_off.setPosition(sf::Vector2f(x_pos, y_pos));
        sprite_on.setPosition(sf::Vector2f(x_pos, y_pos - 2000));
    }
    out.setPosition(x_pos + width * 1.2 * scale, y_pos + height * 2 / 5 * scale);
    for (int i = 0; i < output_list.size(); i++)
    {
        output_list[i]->x_in_pos = x_pos + width * 1.2 * scale;
        output_list[i]->y_in_pos = y_pos + height * 2 / 5 * scale;
    }
}

bool Button::on_click(int x, int y)
{
    return bool(x_pos < x&& x < x_pos + width * scale && y_pos < y&& y < y_pos + height * scale);
}

bool Button::output_on_click(int x, int y)
{
    if (sqrt(pow((x_pos + width * 1.2 * scale) - x, 2) + pow((y_pos + height * 2 / 5 * scale) - y, 2)) <= 3 * 15.0f * scale)
    {

        return true;
    }
    return false;
}

void Button::draw(sf::RenderWindow* window)
{
    window->draw(sprite_on);
    window->draw(sprite_off);
    window->draw(out);
}

void Button::output(bool press, bool on)
{
    if (press)
    {
        if (hold)
        {
            if (on)
                output_active = !output_active;
        }
        else
            output_active = !output_active;
        if (output_active)
        {
            sprite_off.setPosition(sf::Vector2f(x_pos, y_pos - 2000));
            sprite_on.setPosition(sf::Vector2f(x_pos, y_pos));
            out.setFillColor(sf::Color::Green);
        }
        else
        {
            sprite_off.setPosition(sf::Vector2f(x_pos, y_pos));
            sprite_on.setPosition(sf::Vector2f(x_pos, y_pos - 2000));
            out.setFillColor(sf::Color::Color(255, 255, 255, 255));
        }

        for (int i = 0; i < output_list.size(); i++)
        {

            output_list[i]->on = output_active;

            output_list[i]->output();
        }
    }
}