#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <string>
#include "Classes/Add.h"
#include "Classes/Background.h"
#include "Classes/Basic_Logic_Components.h"
#include "Classes/Basic_Logic_Gates.h"
#include "Classes/Connection_Wires.h"
#include "Classes/Header.h"
#include <iostream>

std::vector<Basic_Logic_Components> basic_logic_components_list;

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
    sf::RenderWindow window(sf::VideoMode(800, 600), "Logic Simulator", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(100);
    //
    sf::Texture background_t;
    sf::Sprite background;
    if(!background_t.loadFromFile("Assets/background.png"))
        throw std::invalid_argument("File Not Find Assets/background.png");
    background.setTexture(background_t);
    //
    sf::Texture button_t,button_on_t;
    sf::Sprite button1,button2,button_on;
    if(!button_t.loadFromFile("Assets/start/button.png"))
        throw std::invalid_argument("File Not Find Assets/start/button.png");
    if(!button_on_t.loadFromFile("Assets/start/button_presed.png"))
        throw std::invalid_argument("File Not Find Assets/start/button_presed.png");
    button1.setTexture(button_t);
    button2.setTexture(button_t);
    button_on.setTexture(button_on_t);
    button1.setPosition(sf::Vector2f(120, 130));
    button2.setPosition(sf::Vector2f(120, 260));
    button_on.setPosition(sf::Vector2f(-1000, -1000));
    //
    sf::Texture name_t;
    sf::Sprite name;
    if(!name_t.loadFromFile("Assets/start/name.png"))
        throw std::invalid_argument("File Not Find Assets/start/name.png");
    name.setTexture(name_t);
    name.setPosition(sf::Vector2f(170, 60));
    //
    sf::Texture button1_text_t, button2_text_t;
    sf::Sprite button1_text, button2_text;
    if(!button1_text_t.loadFromFile("Assets/start/new_project.png"))
        throw std::invalid_argument("File Not Find Assets/start/new_project.png");
    if(!button2_text_t.loadFromFile("Assets/start/load_project.png"))
        throw std::invalid_argument("File Not Find Assets/start/load_project.png");
    button1_text.setTexture(button1_text_t);
    button2_text.setTexture(button2_text_t);
    button1_text.setPosition(sf::Vector2f(260, 200));
    button2_text.setPosition(sf::Vector2f(250, 330));
   
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
                }
            }
        }
       
        if (mouse_x > 170 && mouse_x < 630)
        {
           if (mouse_y > 210 && mouse_y < 310)
               button_on.setPosition(sf::Vector2f(120, 130));
           else  if (mouse_y > 340 && mouse_y < 435)
               button_on.setPosition(sf::Vector2f(120, 260));
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
        window.draw(button_on);
        window.draw(button1_text);
        window.draw(button2_text);  
        window.display();
    }
}

std::string new_project()
{
    bool valid_name = true;
    std::vector <std::string> project_names;
    std::fstream plik;
    plik.open("Data/main_list.txt", std::ios::in);
    if(!plik.is_open())
        throw std::invalid_argument("File Not Find Data/main_list.txt");
    while (!plik.eof())
    {
        std::string x;
        std::cout << x << std::endl;
        std::getline(plik,x);
        project_names.push_back(x);
    }
    plik.close();
    //
    sf::RenderWindow window(sf::VideoMode(700, 400), "Logic Simulator", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(100);
    //
    sf::Texture background_t;
    sf::Sprite background;
    if (!background_t.loadFromFile("Assets/background.png"))
        throw std::invalid_argument("File Not Find Assets/background.png");
    background.setTexture(background_t);
    //
    sf::Font font;
    if (!font.loadFromFile("Assets/arial.ttf"))
        throw std::invalid_argument("File Not Find Assets/arial.ttf");

    std::string name_str = "";
    sf::Text name;
    name.setFont(font);
    name.setString(name_str);
    name.setCharacterSize(34);
    name.setFillColor(sf::Color::Black);
    name.setPosition(sf::Vector2f(50,75));
    //
    sf::Texture textplace_t;
    sf::Sprite textplace;
    if (!textplace_t.loadFromFile("Assets/start/textplace.png"))
        throw std::invalid_argument("File Not Find Assets/start/textplace.png");
    textplace.setTexture(textplace_t);
    textplace.setPosition(sf::Vector2f(30, 50));
    textplace.setScale(1.6, 1);
    //
    sf::Texture button_t, button_false_t, button_on_t;
    sf::Sprite button, button_false, button_on;
    if (!button_t.loadFromFile("Assets/start/button.png"))
        throw std::invalid_argument("File Not Find Assets/start/button.png");
    if (!button_on_t.loadFromFile("Assets/start/button_presed.png"))
        throw std::invalid_argument("File Not Find Assets/start/button_presed.png");
    if (!button_false_t.loadFromFile("Assets/start/button_false.png"))
        throw std::invalid_argument("File Not Find Assets/start/button_false.png");
    button.setTexture(button_t);
    button_false.setTexture(button_false_t);
    button_on.setTexture(button_on_t);
    button.setPosition(sf::Vector2f(75, 180));
    button_false.setPosition(sf::Vector2f(-1000, -1000));
    button_on.setPosition(sf::Vector2f(-1000, -1000));
    //
    sf::Texture create_t;
    sf::Sprite create;
    if (!create_t.loadFromFile("Assets/start/create.png"))
        throw std::invalid_argument("File Not Find Assets/start/create.png");
    create.setTexture(create_t);
    create.setPosition(sf::Vector2f(270, 250));
    //
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
                if ((isalpha(event.text.unicode) || isdigit(event.text.unicode) || event.text.unicode == '_') && name_str.length() <= 20)
                {
                    name_str += event.text.unicode;
                    name.setString(name_str);
                    name.setPosition(sf::Vector2f(335 - (name.findCharacterPos(name_str.length() - 1).x -name.getPosition().x)/2, 75));
                    for (int i = 0; i < project_names.size(); i++)
                        if (project_names[i] == name_str)
                        {
                            valid_name = false;
                            button_false.setPosition(sf::Vector2f(75, 180));
                            i = project_names.size();
                        }
                        else 
                            button_false.setPosition(sf::Vector2f(-1000, -1000));
                }
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
                {
                    if (name_str.length() > 0)
                    {
                        name_str.pop_back();
                        name.setString(name_str);
                        name.setPosition(sf::Vector2f(335 - (name.findCharacterPos(name_str.length() - 1).x - name.getPosition().x) / 2, 75));
                        for (int i = 0; i < project_names.size(); i++)
                            if (project_names[i] == name_str)
                            {
                                valid_name = false;
                                button_false.setPosition(sf::Vector2f(75, 180));
                                i = project_names.size();
                            }
                            else
                            {
                                button_false.setPosition(sf::Vector2f(-1000, -1000));
                                valid_name = true;
                            }
                    }
                }
            }
            else if (event.type == sf::Event::MouseButtonPressed)
                if (mouse_x > 130 && mouse_x < 580 && mouse_y > 260 && mouse_y < 360 && valid_name && name_str.length()>0)
                {
                    window.close();
                    return name_str;
                }
        }
        if (mouse_x > 130 && mouse_x < 580 && mouse_y > 260 && mouse_y < 360)
            button_on.setPosition(sf::Vector2f(75, 180));
        else 
            button_on.setPosition(sf::Vector2f(-1000, -1000));

        window.clear();
        window.draw(background);
        window.draw(textplace);
        window.draw(button);
        window.draw(button_on);
        window.draw(button_false);
        window.draw(create);
        window.draw(name);
        window.display();
    }
}

void simulation(std::string file_name)
{
    sf::RenderWindow window(sf::VideoMode().getDesktopMode(), "Logic Simulator", sf::Style::None);
    //window.setIcon();
    window.setFramerateLimit(100);
    //
    bool add_on = false;
    Add add(window.getSize().x);
    Background background(window.getSize().x, window.getSize().y);
    Header header(window.getSize().x,&add_on);
    //
    sf::Mouse mouse;
    int mouse_x = mouse.getPosition().x;
    int mouse_y = mouse.getPosition().y;
    //
    while (window.isOpen())
    {
        mouse_x = mouse.getPosition().x;
        mouse_y = mouse.getPosition().y;
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (mouse_y < 50)
                    header.press(mouse_x);
                    
                
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (!add_on)
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
                else
                {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                        add.move_list(-1);
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                        add.move_list(1);
                }
            }
           
        }

        window.clear();
        background.draw(&window);
        header.draw(&window);
        if(add_on) add.draw(&window);
        window.display();
    }

}

void error(std::string err)
{
    std::cout << err;
    exit(-1);
}