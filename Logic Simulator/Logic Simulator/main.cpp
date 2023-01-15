#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "Classes.h"

std::vector<Basic_Logic_Components> basic_logic_components_list;

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


    //window.setFramerateLimit(100);
    OR x;
    AND y;
    XNOR e;
    Basic_Logic_Components* z{};
    bool move_mode = true;
    bool connect_mode = true;
    bool move_active = false;
    x.create(10, 10);
    basic_logic_components_list.push_back(x);
    y.create(500, 500);
    basic_logic_components_list.push_back(y);
    e.create(30, 30);
    basic_logic_components_list.push_back(e);
    sf::Mouse mouse;
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
                if (move_mode)
                {
                    for (int i = 0; i < basic_logic_components_list.size(); i++)
                    {
                        if (basic_logic_components_list[i].on_click(mouse_x, mouse_y))
                        {
                            z = &basic_logic_components_list[i];
                            move_active = true;
                            i = basic_logic_components_list.size();
                        }
                    }
                }

            }
            if (event.type == sf::Event::MouseButtonReleased)
            {
                move_active = false;
            }
        }
        if (move_active)
        {
            z->move(mouse_x, mouse_y);
        }

        window.clear();
        window.draw(background);
        window.draw(header);
        window.draw(touch);
        window.draw(edit);
        window.draw(connect);
        window.draw(trash);
        for (int i = 0; i < basic_logic_components_list.size(); i++)
        {
            basic_logic_components_list[i].draw(&window);
        }
        window.display();
    }


    return 0;
}