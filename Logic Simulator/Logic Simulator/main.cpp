#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Classes/Background.h"
#include "Classes/Basic_Logic_Components.h"
#include "Classes/Basic_Logic_Gates.h"
#include "Classes/Connection_Wires.h"
#include "Classes/Header.h"
#include <iostream>

int start();
std::string new_project();

void simulation(std::string file_name);
void error(std::string err);

int main()
{
    std::string name;
    int start_action = start();
    if (start_action == 1)
        name = new_project();
    if (name == "")
        main();

    simulation(name);
    main();

    
    return 0;
}

int start()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Logic Simulator");
    window.setFramerateLimit(100);
    //
    sf::Texture background_t;
    sf::Sprite background;
    background_t.loadFromFile("Assets/background.png");
    background.setTexture(background_t);
    //
    sf::Texture button_t,button_on_t;
    sf::Sprite button1,button2,button3,button_on;
    button_t.loadFromFile("Assets/start/button.png");
    button_on_t.loadFromFile("Assets/start/button_presed.png");
    button1.setTexture(button_t);
    button2.setTexture(button_t);
    button3.setTexture(button_t);
    button_on.setTexture(button_on_t);
    button1.setPosition(sf::Vector2f(120, 130));
    button2.setPosition(sf::Vector2f(120, 260));
    button3.setPosition(sf::Vector2f(120, 390));
    button_on.setPosition(sf::Vector2f(-1000, -1000));
    //
    sf::Texture name_t;
    sf::Sprite name;
    name_t.loadFromFile("Assets/start/name.png");
    name.setTexture(name_t);
    name.setPosition(sf::Vector2f(170, 60));
    //
    sf::Texture button1_text_t, button2_text_t, button3_text_t;
    sf::Sprite button1_text, button2_text, button3_text;
    button1_text_t.loadFromFile("Assets/start/new_project.png");
    button2_text_t.loadFromFile("Assets/start/load_project.png");
    button3_text_t.loadFromFile("Assets/start/new_structure.png");
    button1_text.setTexture(button1_text_t);
    button2_text.setTexture(button2_text_t);
    button3_text.setTexture(button3_text_t);
    button1_text.setPosition(sf::Vector2f(260, 200));
    button2_text.setPosition(sf::Vector2f(250, 330));
    button3_text.setPosition(sf::Vector2f(235, 460));
   
    while (window.isOpen())
    {	
        sf::Mouse mouse;
        int mouse_x = mouse.getPosition().x - window.getPosition().x;
        int mouse_y = mouse.getPosition().y - window.getPosition().y;
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                exit(0);
            }

            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (mouse_x > 170 && mouse_x < 630)
                {
                    if (mouse_y > 210 && mouse_y < 310)
                        return 1;
                    else  if (mouse_y > 340 && mouse_y < 435)
                        return 2;
                    else  if (mouse_y > 450 && mouse_y < 570)
                        return 3;
                }
            }
            
        }
       
        if (mouse_x > 170 && mouse_x < 630)
        {
           if (mouse_y > 210 && mouse_y < 310)
               button_on.setPosition(sf::Vector2f(120, 130));
           else  if (mouse_y > 340 && mouse_y < 435)
               button_on.setPosition(sf::Vector2f(120, 260));
           else  if (mouse_y > 450 && mouse_y < 570)
               button_on.setPosition(sf::Vector2f(120, 390));
           else
               button_on.setPosition(sf::Vector2f(-1000, -1000));
        }
        else 
            button_on.setPosition(sf::Vector2f(-1000, -1000));
        window.clear();
        window.draw(background);
        window.draw(name);
        window.draw(button1);
        window.draw(button2);
        window.draw(button3);
        window.draw(button_on);
        window.draw(button1_text);
        window.draw(button2_text);
        window.draw(button3_text);
        window.display();
    }
}

std::string new_project()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Logic Simulator");
    window.setFramerateLimit(100);
    //
    sf::Texture background_t;
    sf::Sprite background;
    background_t.loadFromFile("Assets/background.png");
    background.setTexture(background_t);
    //
    sf::Font font;
    if (!font.loadFromFile("Assets/arial.ttf"))
    {
        error("LOL");
    }
    std::string name_str = "";
    sf::Text name;
    name.setFont(font);
    name.setString(name_str);
    name.setCharacterSize(24);
    name.setFillColor(sf::Color::Black);
    name.setPosition(sf::Vector2f(100, 100));

    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(600, 200));
    rectangle.setFillColor(sf::Color::Color(100,100,100,255));
    rectangle.setPosition(100, 100);
    sf::RectangleShape go;
    go.setSize(sf::Vector2f(50, 50));
    go.setFillColor(sf::Color::Color(100, 100, 100, 255));
    go.setPosition(700, 500);

    while (window.isOpen())
    {
        sf::Mouse mouse;
        int mouse_x = mouse.getPosition().x - window.getPosition().x;
        int mouse_y = mouse.getPosition().y - window.getPosition().y;
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return "";
            }
            else if (event.type == sf::Event::TextEntered)
            {
                if ((isalpha(event.text.unicode) || isdigit(event.text.unicode) || event.text.unicode == '_') && name_str.length() <= 30)
                {
                    name_str += event.text.unicode;
                    name.setString(name_str);
                }
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
                {
                    name_str.pop_back();
                    name.setString(name_str);
                }
            }
            else if (event.type == sf::Event::MouseButtonPressed)
                if (mouse_x > 700 && mouse_x < 750 && mouse_y > 500 && mouse_y < 550)
                {
                    window.close();
                    return name_str;
                }
        }

       
        window.clear();
        window.draw(background);
        window.draw(rectangle);
        window.draw(go);
        window.draw(name);
        window.display();

    }
}

void simulation(std::string file_name)
{
    sf::RenderWindow window(sf::VideoMode().getDesktopMode(), "Logic Simulator", sf::Style::None);
    //window.setIcon();
    window.setFramerateLimit(100);
    Background background(window.getSize().x, window.getSize().y);
    Header header(window.getSize().x);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                    background.move(100, 0);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                    background.move(0, 100);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                    background.move(-100, 0);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                    background.move(0, -100);
            }
        }

        window.clear();
        background.draw(&window);
        header.draw(&window);
        window.display();
    }

}

void error(std::string err)
{
    std::cout << err;
    exit(-1);
}