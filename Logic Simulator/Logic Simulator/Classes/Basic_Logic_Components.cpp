#include "Basic_Logic_Components.h"

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
    in_1.setPosition(x_pos - width / 3 * scale, y_pos + height / 5 * scale);
    in_2.setRadius(15.0f * scale);
    in_2.setPosition(x_pos - width / 3 * scale, y_pos + height * 2 / 3 * scale);
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
        out.setPosition(x_pos + width * 1.2 * scale, y_pos + height * 2 / 5 * scale);
    }
}

bool Basic_Logic_Components::on_click(int x, int y)
{
    return bool(x_pos < x&& x < x_pos + width * scale && y_pos < y&& y < y_pos + height * scale);
}

bool Basic_Logic_Components::input1_on_click(int x, int y)
{
    return bool(sqrt(pow((x_pos - width / 3 * scale) - x, 2) + pow((y_pos + height / 5 * scale) - y, 2)) <= 3 * 15.0f * scale);
}

bool Basic_Logic_Components::input2_on_click(int x, int y)
{
    return bool(sqrt(pow((x_pos - width / 3 * scale) - x, 2) + pow((y_pos + height * 2 / 3 * scale) - y, 2)) < 3 * 15.0f * scale);
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
    window->draw(sprite);
    window->draw(in_1);
    window->draw(in_2);
    window->draw(out);
}

void Basic_Logic_Components::output()
{
    if (!action_in_sequence)
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
        action_in_sequence = true;
        for (int i = 0; i < output_list.size(); i++)
        {
            std::cout << "aaa" << std::endl;
            output_list[i]->on = output_active;
            std::cout << "bbb" << std::endl;
            output_list[i]->output();
            std::cout << "ccc" << std::endl;

        }

    }
}