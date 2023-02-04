#include "Connection_Wires.h"

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
