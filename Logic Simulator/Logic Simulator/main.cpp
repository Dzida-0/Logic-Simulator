#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "Classes.h"

std::vector<Basic_Logic_Components> basic_logic_components_list;
std::vector<Connection_Wires> cable_list;

int main()
{
    sf::RenderWindow window(sf::VideoMode().getDesktopMode(), "Logic Simulator", sf::Style::None);
    //window.setIcon();
    sf::RectangleShape background;
    background.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    background.setFillColor(sf::Color::Color(100, 100, 100, 255));
    sf::RectangleShape header;
    header.setSize(sf::Vector2f(window.getSize().x, 40));
    header.setFillColor(sf::Color::Color(255,255,255, 255));
    sf::Texture touch_t, edit_t, connect_t, trash_t;
    sf::Sprite touch, edit, connect, trash;
    touch_t.loadFromFile("Assets/touch.png");
    edit_t.loadFromFile("Assets/edit.png");
    connect_t.loadFromFile("Assets/connect.png");
    trash_t.loadFromFile("Assets/trash.png");
    touch.setTexture(touch_t);
    edit.setTexture(edit_t);
    connect.setTexture(connect_t);
    trash.setTexture(trash_t);
    touch.setScale(sf::Vector2f(0.035,0.035));
    edit.setScale(sf::Vector2f(0.035, 0.035));
    connect.setScale(sf::Vector2f(0.035, 0.035));
    trash.setScale(sf::Vector2f(0.035, 0.035));
    touch.setPosition(sf::Vector2f(1000, 2));
    edit.setPosition(sf::Vector2f(1050, 2));
    connect.setPosition(sf::Vector2f(1100, 2));
    trash.setPosition(sf::Vector2f(1150, 2));
    sf::Texture button_t;
    sf::Sprite button;
    button_t.loadFromFile("Assets/button.png");
    button.setTexture(button_t);
    button.setScale(sf::Vector2f(0.15, 0.15));
    button.setPosition(sf::Vector2f(200, 200));


    window.setFramerateLimit(50);
    OR x;
    AND y;
    XNOR e;
    Basic_Logic_Components* z{};
    Connection_Wires* wire{};
    //Connection_Wires r;
    //cable_list.push_back(r);
    bool tough_mode = true;
    bool move_mode = false;
    bool connect_mode = false;
    bool move_active = false;
    bool connect_active = false;
    x.create(10, 10);
    basic_logic_components_list.push_back(x);
    y.create(500, 500);
    basic_logic_components_list.push_back(y);
    e.create(30, 30);
    basic_logic_components_list.push_back(e);
    sf::Mouse mouse;
    for (int i = 0; i < basic_logic_components_list.size(); i++)
    {
        z = &basic_logic_components_list[i];
        
    }
    int mouse_x = mouse.getPosition().x;
    int mouse_y = mouse.getPosition().y;
    while (window.isOpen())
    {
        mouse_x = mouse.getPosition().x;
        mouse_y = mouse.getPosition().y;
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                for (int i = 0; i < basic_logic_components_list.size(); i++)
                {
                    if (move_mode)
                    {
                        if (basic_logic_components_list[i].on_click(mouse_x, mouse_y))
                        {
                            z = &basic_logic_components_list[i];
                            move_active = true;
                            i = basic_logic_components_list.size();
                        }
                    }
                    else if (connect_mode)
                    {
                        if (basic_logic_components_list[i].output_on_click(mouse_x, mouse_y, &cable_list))
                        {
                            connect_active = true;
                            wire = &cable_list[cable_list.size() - 1];
                            i = basic_logic_components_list.size();
                        }
                    }
                    
                }
                if (mouse_x > 1000 && mouse_x < 1035 && mouse_y < 35)
                {
                    tough_mode = true;
                    move_mode = false;
                    connect_mode = false;
                }
                else if (mouse_x > 1050 && mouse_x < 1085 && mouse_y < 35)
                {
                    tough_mode = false;
                    move_mode = true;
                    connect_mode = false;
                }
                else if (mouse_x > 1100 && mouse_x < 1135 && mouse_y < 35)
                {
                    tough_mode = false;
                    move_mode = false;
                    connect_mode = true;
                }

            }
            if (event.type == sf::Event::MouseButtonReleased)
            {
                move_active = false;
                if (connect_active)
                {
                    for (int i = 0; i < basic_logic_components_list.size(); i++)
                    {
                        if (basic_logic_components_list[i].input1_on_click(mouse_x, mouse_y) && !basic_logic_components_list[i].input1_connect)
                        {
                            wire->x_out_pos = mouse_x;
                            wire->y_out_pos = mouse_y;
                            wire->out = &basic_logic_components_list[i];
                            basic_logic_components_list[i].input1_active = wire->on;
                            basic_logic_components_list[i].input1_connect = true;
                            basic_logic_components_list[i].output();
                            connect_active = false;
                            std::cout << "1"<< std::endl;
                        }
                        else  if (basic_logic_components_list[i].input2_on_click(mouse_x, mouse_y) && !basic_logic_components_list[i].input2_connect)
                        {
                            wire->x_out_pos = mouse_x;
                            wire->y_out_pos = mouse_y;
                            wire->out = &basic_logic_components_list[i];
                            basic_logic_components_list[i].input2_active = wire->on;
                            basic_logic_components_list[i].input2_connect = true;
                            basic_logic_components_list[i].output();
                            connect_active = false;
                            std::cout << "2" << std::endl;
                        }
                 
                    }
                    if (connect_active)
                    {
                        wire = {};
                        cable_list.pop_back();
                    }
                }
                connect_active = false;
            }
        }
        if (move_active)
        {
            z->move(mouse_x, mouse_y);
        }
        window.clear();
        window.draw(background);
        if (connect_active)
        {
            sf::RectangleShape rec;
            rec.setPosition(sf::Vector2f(wire->x_in_pos, wire->y_in_pos));
            rec.setSize(sf::Vector2f(sqrt(pow(wire->x_in_pos - mouse_x, 2) + pow(wire->y_in_pos - mouse_y, 2)),5));
            if (!wire->on)
                rec.setFillColor(sf::Color::Color(255, 255, 255, 100));
            else
                rec.setFillColor(sf::Color::Green);
            if (mouse_x - wire->x_in_pos != 0)
            {
                if (mouse_x - wire->x_in_pos > 0)
                rec.setRotation(atan(float(mouse_y - wire->y_in_pos) / float(mouse_x - wire->x_in_pos)) * 180 / 3.1415);
                else 
                    rec.setRotation(180 + atan(float(mouse_y - wire->y_in_pos) / float(mouse_x - wire->x_in_pos)) * 180 / 3.1415);
            }
            for (int i = 0; i < cable_list.size() - 1; i++)
            {
                cable_list[i].draw_cable(&window);
            }
            window.draw(rec);
        }
        else
        {
            for (int i = 0; i < cable_list.size(); i++)
                {
                    cable_list[i].draw_cable(&window);
                }
        }


        window.draw(header);
        window.draw(touch);
        window.draw(edit);
        window.draw(connect);
        window.draw(trash);
        window.draw(button);
        for (int i = 0; i < basic_logic_components_list.size(); i++)
        {
            basic_logic_components_list[i].draw(&window);
        }
        window.display();
    }


    return 0;
}