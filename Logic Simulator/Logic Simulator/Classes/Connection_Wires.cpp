#include "Connection_Wires.h"

void Connection_Wires::create(int x, int y) // pozycja wejscia 
{
    x_in_pos = x;
    y_in_pos = y;
}

void Connection_Wires::output() // wywo³ywanie dzia³¹nia na wyjœciu 
{
    if (!output_led)
    {
        if (input_number == 1)
            out_basic->input1_active = on;
        else  if (input_number == 2)
            out_basic->input2_active = on;
        out_basic->output();
    }
    else
    {
        out_led->input_active = on;
        out_led->connected();
    }
}

void Connection_Wires::output_move() // porusznie 
{
    if (!output_led)
    {
        if (input_number == 1)
            y_out_pos = out_basic->y_pos + out_basic->height / 5 * out_basic->scale;
        if (input_number == 2)
            y_out_pos = out_basic->y_pos + out_basic->height * 2/3 * out_basic->scale;
        x_out_pos = out_basic->x_pos - out_basic->width / 3 * out_basic->scale;
        
    }
    else
    {
       x_out_pos = out_led->x_pos - out_led->width / 3 * out_led->scale;
       y_out_pos = out_led->y_pos + out_led->height / 3 * out_led->scale;
    }
}

void Connection_Wires::create_output(int num, Basic_Logic_Components* out_logic, Led* out_led_pass) // tworzenie wyjœcia 
{
    input_number = num;
    
    if (out_logic != NULL)
        out_basic = out_logic;
    else if (out_led_pass != NULL)
    {
        out_led = out_led_pass;
        output_led = true;
    }
    connected = true;

}

bool Connection_Wires::on_click(int x, int y) // czy naciœniêty ( funkcja wykorzystywana przy usuwaniu)
{
    if (x_in_pos < x_out_pos)
    {
        if (x > x_in_pos && x < x_out_pos)
        {
            if (y_in_pos > y_out_pos)
            {
                if (y > y_out_pos && y < y_in_pos)
                {
                    float a, b;
                    a = float(y_in_pos - y_out_pos) / float(x_in_pos - x_out_pos);
                    b = y_in_pos - a * x_in_pos;
                    if (y > a * x + b - 3 && y < a * x + b + 3)
                        return true;
                }

            }
            else
            {
                if (y < y_out_pos && y > y_in_pos)
                {
                    float a, b;
                    a = float(y_in_pos - y_out_pos) / float(x_in_pos - x_out_pos);
                    b = y_in_pos - a * x_in_pos;
                    if (y > a * x + b - 3 && y < a * x + b + 3)
                        return true;
                }
            }
        }
    }
    else
    {
        if (x < x_in_pos && x > x_out_pos)
        {
            if (y_in_pos > y_out_pos)
            {
                if (y > y_out_pos && y < y_in_pos)
                {
                    float a, b;
                    a = float(y_in_pos - y_out_pos) / float(x_in_pos - x_out_pos);
                    b = y_in_pos - a * x_in_pos;
                    if (y > a * x + b - 3 && y < a * x + b + 3)
                        return true;
                }
            }
            else
            {
                if (y < y_out_pos && y > y_in_pos)
                {
                    float a, b;
                    a = float(y_in_pos - y_out_pos) / float(x_in_pos - x_out_pos);
                    b = y_in_pos - a * x_in_pos;
                    if (y > a * x + b - 3 && y < a * x + b + 3)
                        return true;
                }
            }
        }
    }
   
    return false;
}

void Connection_Wires::draw_cable(sf::RenderWindow* window) // rysowanie 
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