#pragma once
#include <SFML/Graphics.hpp>

#include <vector>
#include <fstream>
#include <string>
#include <iostream>

#include "Classes/Background.h"
#include "Classes/Header.h"

void simulation(std::string file_name, bool to_load);
int start();
std::string new_project();
void save(std::string name, std::vector<Basic_Logic_Components*> basic_logic_components_list, std::vector<Connection_Wires*> cable_list, std::vector<Led*> led_list, std::vector<Button*> button_list);
std::string load(std::vector<Basic_Logic_Components*>* basic_logic_components_list, std::vector<Connection_Wires*>* cable_list, std::vector<Led*>* led_list, std::vector<Button*>* button_list, Add* add_box);

int main()
{
    std::string name;
    int start_action = start();
    if (start_action == 1)
    {
        name = new_project();
        simulation(name, false);
    }
    else if (start_action == 2)
        simulation("", true);
    main();


    return 0;
}

void simulation(std::string file_name, bool to_load)
{
    std::vector<Basic_Logic_Components*> basic_logic_components_list;
    std::vector<Connection_Wires*> cable_list;
    std::vector<Led*> led_list;
    std::vector<Button*> button_list;
    //
    bool move_active = false;
    bool move_led_active = false;
    bool move_button_active = false;
    bool connect_active = false;
    bool connect_active_button = false;
    Basic_Logic_Components* logic_component{};
    Connection_Wires* wire{};
    Led* led{};
    Button* button{};
    //
    Background background(sf::VideoMode().getDesktopMode().width, sf::VideoMode().getDesktopMode().height);
    Add add(1000, &basic_logic_components_list, &led_list, &button_list);
    Header header(1000, &add.add_on);
    //
    if(to_load) file_name = load(&basic_logic_components_list, &cable_list, &led_list, &button_list, &add);
    //
    sf::RenderWindow window(sf::VideoMode(1500,1000), "Logic Simulator", sf::Style::None);
    window.setFramerateLimit(100);
    sf::Mouse mouse;
    int mouse_x = mouse.getPosition().x - window.getPosition().x;
    int mouse_y = mouse.getPosition().y - window.getPosition().y;
    sf::Event event;
    //
    while (window.isOpen())
    {
        mouse_x = mouse.getPosition().x - window.getPosition().x;
        mouse_y = mouse.getPosition().y - window.getPosition().y;
        
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (mouse_y < 50)
                {
                    header.press(mouse_x);
                    if (mouse_x > 5 && mouse_x < 80)
                        window.close();
                    else if (mouse_x > 90 && mouse_x < 140)
                        save(file_name, basic_logic_components_list, cable_list, led_list, button_list);
                }
                else if (add.add_on)
                    add.press(mouse_x, mouse_y);
                else
                {
                    if (header.press_bool)
                    {
                        for(int i = 0; i < button_list.size();i++)
                        button_list[i]->output(button_list[i]->on_click(mouse_x, mouse_y), 1);
                    }
                    else if (header.move_bool)
                    {   
                        if (header.move_bool && !move_led_active && !move_button_active)
                        {
                            for (int i = 0; i < basic_logic_components_list.size(); i++)
                            {
                                if (basic_logic_components_list[i]->on_click(mouse_x, mouse_y))
                                {
                                    logic_component = basic_logic_components_list[i];
                                    move_active = true;
                                    i = basic_logic_components_list.size();
                                }
                            }
                        }

                         if (!move_active && !move_led_active)
                        {
                            for (int i = 0; i < button_list.size(); i++)
                            {
                                if (button_list[i]->on_click(mouse_x, mouse_y))
                                {
                                    button = button_list[i];
                                    move_button_active = true;
                                    i = button_list.size();
                                }
                            }
                        }
                         if  (header.move_bool && !move_active && !move_button_active)
                        {
                            for (int i = 0; i < led_list.size(); i++)
                            {
                                if (led_list[i]->on_click(mouse_x, mouse_y))
                                {
                                    led = led_list[i];
                                    move_led_active = true;
                                    i = led_list.size();
                                }
                            }
                         }

                    }
                    else if (header.connect_bool)
                    {
                        for (int i = 0; i < basic_logic_components_list.size(); i++)
                        {
                            if (basic_logic_components_list[i]->output_on_click(mouse_x, mouse_y))
                            {
                                //system("pause");
                                wire = new Connection_Wires;
                                wire->id = add.connection_wires_id_count++;
                                //system("pause");
                                wire->create(basic_logic_components_list[i]->x_pos + basic_logic_components_list[i]->width * 1.2 * basic_logic_components_list[i]->scale,
                                    basic_logic_components_list[i]->y_pos + basic_logic_components_list[i]->height * 2 / 5 * basic_logic_components_list[i]->scale, basic_logic_components_list[i], NULL);
                                // system("pause");
                                connect_active = true;
                                cable_list.push_back(wire);
                                basic_logic_components_list[i]->output_list.push_back(cable_list[cable_list.size() - 1]);
                                i = basic_logic_components_list.size();
                            }
                        }
                        for (int i = 0; i < button_list.size(); i++)
                        {
                            if (button_list[i]->output_on_click(mouse_x, mouse_y))
                            {
                                //system("pause");
                                wire = new Connection_Wires;
                                //system("pause");
                                wire->id = add.connection_wires_id_count++;
                                wire->create(button_list[i]->x_pos + button_list[i]->width * 1.2 * button_list[i]->scale,
                                    button_list[i]->y_pos + button_list[i]->height * 2 / 5 * button_list[i]->scale, NULL, button_list[i]);
                                // system("pause");
                                connect_active = true;
                                cable_list.push_back(wire);
                                button_list[i]->output_list.push_back(cable_list[cable_list.size() - 1]);
                                button_list[i]->connected = true;
                                i = button_list.size();

                            }
                        }

                    }
                    else if (header.trash_bool)
                    {
                        for (int i = 0; i < button_list.size(); i++)
                        {
                            if (button_list[i]->on_click(mouse_x, mouse_y))
                            {
                                if (button_list[i]->connected)
                                {
                                    for (int j = 0; j < button_list[i]->output_list.size(); j++)
                                    {
                                        if (!button_list[i]->output_list[j]->output_led)
                                        {
                                            if (button_list[i]->output_list[j]->input_number == 1)
                                            {
                                                button_list[i]->output_list[j]->out_basic->input1_connect = false;
                                                button_list[i]->output_list[j]->out_basic->input1_active = false;
                                            }

                                            else if (button_list[i]->output_list[j]->input_number == 2)
                                            {
                                                button_list[i]->output_list[j]->out_basic->input2_connect = false;
                                                button_list[i]->output_list[j]->out_basic->input2_active = false;
                                            }
                                            button_list[i]->output_list[j]->out_basic->output();
                                        }
                                        else
                                        {
                                            button_list[i]->output_list[j]->out_led->input_connect = false;
                                            button_list[i]->output_list[j]->out_led->input_active = false;
                                            button_list[i]->output_list[j]->out_led->connected();
                                        }
                                        button_list[i]->output_list[j]->to_delete = true;
                                    }
                                    for (int j = 0; j < cable_list.size(); j++)
                                        if (cable_list[j]->to_delete)
                                            cable_list.erase(cable_list.begin() + j);
                                    for (int j = 0; j < cable_list.size(); j++)
                                        if (cable_list[j]->to_delete)
                                            cable_list.erase(cable_list.begin() + j);
                                }
                                button_list.erase(button_list.begin() + i);
                            }
                        }
                        for (int i = 0; i < led_list.size(); i++)
                        {
                            if (led_list[i]->on_click(mouse_x, mouse_y))
                            {

                            }
                        }
                    }
                    
                }
            }

             
            else if (event.type == sf::Event::MouseButtonReleased)
            {
                move_active = false;
                move_led_active = false;
                move_button_active = false;
                if (header.connect_bool)
                {
                    for (int i = 0; i < basic_logic_components_list.size(); i++)
                    {
                        if (basic_logic_components_list[i]->input1_on_click(mouse_x, mouse_y) && !basic_logic_components_list[i]->input1_connect)
                        {
                            wire = cable_list[cable_list.size() - 1];
                            basic_logic_components_list[i]->input1_connect = true;
                           // wire->connected = true;
                           // wire->input_number = 1;
                           // wire->out_basic = &basic_logic_components_list[i];
                            //std::cout << wire->out_basic->id << std::endl;
                            wire->create_output(1, basic_logic_components_list[i], NULL);
                            wire->output_move();
                            wire->output();
                            connect_active = false;

                        }
                        else  if (basic_logic_components_list[i]->input2_on_click(mouse_x, mouse_y) && !basic_logic_components_list[i]->input2_connect)
                        {
                            wire = cable_list[cable_list.size() - 1];
                            basic_logic_components_list[i]->input2_connect = true;
                            //wire->connected = true;
                           // wire->input_number = 2;
                           // wire->out_basic = &basic_logic_components_list[i];
                            wire->create_output(2, basic_logic_components_list[i], NULL);
                            wire->output_move();
                            wire->output();
                            connect_active = false;
                        }

                    }
                    for (int i = 0; i < led_list.size(); i++)
                    {
                        if (led_list[i]->input_on_click(mouse_x, mouse_y) && !led_list[i]->input_connect)
                        {
                            wire = cable_list[cable_list.size() - 1];
                            led_list[i]->input_connect = true;
                            led_list[i]->input_wire = wire;
                            wire->create_output(1,NULL, led_list[i]);
                            wire->output_move();
                            wire->output();
                            connect_active = false;
                        }
                       
                    }
                    if (connect_active)
                    {
                        wire = {};
                        cable_list.pop_back();
                    }
                    connect_active = false;
                    connect_active_button = false;
                   

                }
                for (int i = 0; i < button_list.size(); i++)
                {
                    if (header.press_bool)
                    {
                        button_list[i]->output(button_list[i]->on_click(mouse_x, mouse_y), 0);
                    }

                }
             
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (!add.add_on)
                {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                    {
                        background.move(50, 0);
                        for (int i = 0; i < basic_logic_components_list.size(); i++)
                            basic_logic_components_list[i]->move(basic_logic_components_list[i]->x_pos + basic_logic_components_list[i]->width / 2 + 50,
                                basic_logic_components_list[i]->y_pos + basic_logic_components_list[i]->height / 2);
                        for (int i = 0; i < cable_list.size(); i++)
                             cable_list[i]->output_move();
                        for (int i = 0; i < led_list.size(); i++)
                            led_list[i]->move(led_list[i]->x_pos + led_list[i]->width / 2 + 50, led_list[i]->y_pos + led_list[i]->height / 2);
                        for (int i = 0; i < button_list.size(); i++)
                            button_list[i]->move(button_list[i]->x_pos + button_list[i]->width / 2 + 50, button_list[i]->y_pos + button_list[i]->height / 2);
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                    {
                        background.move(0, 50);
                        for (int i = 0; i < basic_logic_components_list.size(); i++)
                            basic_logic_components_list[i]->move(basic_logic_components_list[i]->x_pos + basic_logic_components_list[i]->width / 2,
                                basic_logic_components_list[i]->y_pos + basic_logic_components_list[i]->height / 2 + 50);
                        for (int i = 0; i < cable_list.size(); i++)
                                cable_list[i]->output_move();
                        for (int i = 0; i < led_list.size(); i++)
                            led_list[i]->move(led_list[i]->x_pos + led_list[i]->width / 2, led_list[i]->y_pos + led_list[i]->height / 2 + 50);
                        for (int i = 0; i < button_list.size(); i++)
                            button_list[i]->move(button_list[i]->x_pos + button_list[i]->width / 2, button_list[i]->y_pos + button_list[i]->height / 2 + 50);
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                    {
                        background.move(-50, 0);
                        for (int i = 0; i < basic_logic_components_list.size(); i++)
                            basic_logic_components_list[i]->move(basic_logic_components_list[i]->x_pos + basic_logic_components_list[i]->width / 2 - 50,
                                basic_logic_components_list[i]->y_pos + basic_logic_components_list[i]->height / 2);
                        for (int i = 0; i < cable_list.size(); i++)
                             cable_list[i]->output_move();
                        for (int i = 0; i < led_list.size(); i++)
                            led_list[i]->move(led_list[i]->x_pos + led_list[i]->width / 2 - 50, led_list[i]->y_pos + led_list[i]->height / 2);
                        for (int i = 0; i < button_list.size(); i++)
                            button_list[i]->move(button_list[i]->x_pos + button_list[i]->width / 2 - 50, button_list[i]->y_pos + button_list[i]->height / 2);
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                    {
                        background.move(0, -50);
                        for (int i = 0; i < basic_logic_components_list.size(); i++)
                            basic_logic_components_list[i]->move(basic_logic_components_list[i]->x_pos + basic_logic_components_list[i]->width / 2,
                                basic_logic_components_list[i]->y_pos + basic_logic_components_list[i]->height / 2 - 50);
                        for (int i = 0; i < cable_list.size(); i++)
                              cable_list[i]->output_move();
                        for (int i = 0; i < led_list.size(); i++)
                            led_list[i]->move(led_list[i]->x_pos + led_list[i]->width / 2, led_list[i]->y_pos + led_list[i]->height / 2 - 50);
                        for (int i = 0; i < button_list.size(); i++)
                            button_list[i]->move(button_list[i]->x_pos + button_list[i]->width / 2 , button_list[i]->y_pos + button_list[i]->height / 2 - 50);
                    }

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
        if (move_active)
        {
            logic_component->move(mouse_x, mouse_y);
            for (int i = 0; i < cable_list.size(); i++)
                cable_list[i]->output_move();
        }
        else if (move_led_active)
        {
            led->move(mouse_x, mouse_y);
            for (int i = 0; i < cable_list.size(); i++)
                cable_list[i]->output_move();
        }
        else if (move_button_active)
        {
            button->move(mouse_x, mouse_y);
            for (int i = 0; i < cable_list.size(); i++)
                cable_list[i]->output_move();
        }
        window.clear();
        background.draw(&window);
        for (int i = 0; i < basic_logic_components_list.size(); i++)
            basic_logic_components_list[i]->draw(&window);
        for (int i = 0; i < led_list.size(); i++)
            led_list[i]->draw(&window);
        for (int i = 0; i < button_list.size(); i++)
            button_list[i]->draw(&window);
        if (connect_active)
        {
            sf::RectangleShape rec;
            rec.setPosition(sf::Vector2f(wire->x_in_pos, wire->y_in_pos));
            rec.setSize(sf::Vector2f(sqrt(pow(wire->x_in_pos - mouse_x, 2) + pow(wire->y_in_pos - mouse_y, 2)), 5));
            if (!wire->on)
                rec.setFillColor(sf::Color::Color(255, 255, 255, 255));
            else
                rec.setFillColor(sf::Color::Green);
            if (mouse_x - wire->x_in_pos != 0)
            {
                if (mouse_x - wire->x_in_pos > 0)
                    rec.setRotation(atan(float(mouse_y - wire->y_in_pos) / float(mouse_x - wire->x_in_pos)) * 180 / 3.1415);
                else
                    rec.setRotation(180 + atan(float(mouse_y - wire->y_in_pos) / float(mouse_x - wire->x_in_pos)) * 180 / 3.1415);
            }
            else
            {
                if (wire->y_in_pos > mouse_y)
                    rec.rotate(-90);
                else
                    rec.rotate(90);
            }
            for (int i = 0; i < cable_list.size() - 1; i++)
            {
                cable_list[i]->draw_cable(&window);
            }
            window.draw(rec);
        }
        else
        {
            for (int i = 0; i < cable_list.size(); i++)
            {
                cable_list[i]->draw_cable(&window);
            }
        }

        header.draw(&window);
        add.draw(&window);
        window.display();
    }
}

int start()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Logic Simulator", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(100);
    // Texture
    sf::Texture background_t;
    sf::Texture button_t, button_on_t;
    sf::Texture name_t;
    sf::Texture button1_text_t, button2_text_t;
    // Sprite
    sf::Sprite background;
    sf::Sprite button1, button2, button_on;
    sf::Sprite name;
    sf::Sprite button1_text, button2_text;
    // Load texture
    if (!background_t.loadFromFile("Assets/background.png"))
        throw std::invalid_argument("File Not Find Assets/background.png");
    if (!button_t.loadFromFile("Assets/start/button.png"))
        throw std::invalid_argument("File Not Find Assets/start/button.png");
    if (!button_on_t.loadFromFile("Assets/start/button_presed.png"))
        throw std::invalid_argument("File Not Find Assets/start/button_presed.png");
    if (!name_t.loadFromFile("Assets/start/name.png"))
        throw std::invalid_argument("File Not Find Assets/start/name.png");
    if (!button1_text_t.loadFromFile("Assets/start/new_project.png"))
        throw std::invalid_argument("File Not Find Assets/start/new_project.png");
    if (!button2_text_t.loadFromFile("Assets/start/load_project.png"))
        throw std::invalid_argument("File Not Find Assets/start/load_project.png");
    // Create sprite
    background.setTexture(background_t);
    button1.setTexture(button_t);
    button2.setTexture(button_t);
    button_on.setTexture(button_on_t);
    name.setTexture(name_t);
    button1_text.setTexture(button1_text_t);
    button2_text.setTexture(button2_text_t);
    // Sprite set position
    button1.setPosition(sf::Vector2f(120, 130));
    button2.setPosition(sf::Vector2f(120, 260));
    button_on.setPosition(sf::Vector2f(-1000, -1000));
    name.setPosition(sf::Vector2f(170, 60));
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
        //
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
    if (!plik.is_open())
        throw std::invalid_argument("File Not Find Data/main_list.txt");
    while (!plik.eof())
    {
        std::string x;
        std::cout << x << std::endl;
        std::getline(plik, x);
        project_names.push_back(x);
    }
    plik.close();
    //
    sf::RenderWindow window(sf::VideoMode(700, 400), "Logic Simulator", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(100);
    // Texture
    sf::Texture background_t;
    sf::Texture textplace_t;
    sf::Texture button_t, button_false_t, button_on_t;
    sf::Texture create_t;
    // Sprite
    sf::Sprite background;
    sf::Sprite textplace;
    sf::Sprite button, button_false, button_on;
    sf::Sprite create;
    // Load texture
    if (!background_t.loadFromFile("Assets/background.png"))
        throw std::invalid_argument("File Not Find Assets/background.png");
    if (!textplace_t.loadFromFile("Assets/start/textplace.png"))
        throw std::invalid_argument("File Not Find Assets/start/textplace.png");
    if (!button_t.loadFromFile("Assets/start/button.png"))
        throw std::invalid_argument("File Not Find Assets/start/button.png");
    if (!button_on_t.loadFromFile("Assets/start/button_presed.png"))
        throw std::invalid_argument("File Not Find Assets/start/button_presed.png");
    if (!button_false_t.loadFromFile("Assets/start/button_false.png"))
        throw std::invalid_argument("File Not Find Assets/start/button_false.png");
    if (!create_t.loadFromFile("Assets/start/create.png"))
        throw std::invalid_argument("File Not Find Assets/start/create.png");
    // Create sprite
    background.setTexture(background_t);
    textplace.setTexture(textplace_t);
    button.setTexture(button_t);
    button_false.setTexture(button_false_t);
    create.setTexture(create_t);
    // Sprite set position 
    sf::Font font;
    if (!font.loadFromFile("Assets/arial.ttf"))
        throw std::invalid_argument("File Not Find Assets/arial.ttf");

    std::string name_str = "";
    sf::Text name;
    name.setFont(font);
    name.setString(name_str);
    name.setCharacterSize(34);
    name.setFillColor(sf::Color::Black);
    name.setPosition(sf::Vector2f(50, 75));
    //
    
    
    
   
    textplace.setPosition(sf::Vector2f(30, 50));
    textplace.setScale(1.6, 1);
    //
    
    
    
  
   
    button_on.setTexture(button_on_t);
    button.setPosition(sf::Vector2f(75, 180));
    button_false.setPosition(sf::Vector2f(-1000, -1000));
    button_on.setPosition(sf::Vector2f(-1000, -1000));
    //
    
   
    
    
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

void save(std::string name, std::vector<Basic_Logic_Components*> basic_logic_components_list, std::vector<Connection_Wires*> cable_list, std::vector<Led*> led_list, std::vector<Button*> button_list)
{
    std::fstream plik, plik_list;
    plik_list.open("Data/main_list.txt", std::ios::out | std::ios::app);
    //if (!plik_list.is_open())
       // error("o");
    plik_list << name << std::endl;
    plik_list.close();

    plik.open("Data/" + name + ".txt", std::ios::out);
   // if (!plik.is_open())
       // error("o");
    for (int i = 0; i < cable_list.size(); i++)
    {
        plik << "C " << cable_list[i]->id << " " << cable_list[i]->x_in_pos << " " << cable_list[i]->y_in_pos << " " << cable_list[i]->x_out_pos << " " << cable_list[i]->y_out_pos << " " << cable_list[i]->on <<
            " " << cable_list[i]->connected << " " << cable_list[i]->input_number << " " << cable_list[i]->input_button_bool << " " << cable_list[i]->output_led << " ";
        if (cable_list[i]->out_basic != NULL)
            plik << cable_list[i]->out_basic->id << " ";
        else if (cable_list[i]->out_led != NULL)
            plik << "l " << cable_list[i]->out_led->id << " ";
        plik << std::endl;
    }
    for (int i = 0; i < basic_logic_components_list.size(); i++)
    {
        plik <<"G " <<  basic_logic_components_list[i]->id << " " << basic_logic_components_list[i]->type << " " << basic_logic_components_list[i]->x_pos << " " << basic_logic_components_list[i]->y_pos << " "
            << basic_logic_components_list[i]->input1_connect << " " << basic_logic_components_list[i]->input2_connect << " " << basic_logic_components_list[i]->input1_active << " "
            << basic_logic_components_list[i]->input2_active << " " << basic_logic_components_list[i]->output_active << " " << basic_logic_components_list[i]->output_list.size() << " ";
        for (int j = 0; j < basic_logic_components_list[i]->output_list.size(); j++)
            plik << basic_logic_components_list[i]->output_list[j]->id << " ";
        plik << std::endl;
    }
    for (int i = 0; i < button_list.size(); i++)
    {
        plik << "B " << button_list[i]->id << " " << button_list[i]->x_pos << " " << button_list[i]->y_pos << " " << button_list[i]->output_active << " " << button_list[i]->hold << " " << button_list[i]->output_list.size() << " ";
        for (int j = 0; j < button_list[i]->output_list.size(); j++)
            plik << button_list[i]->output_list[j]->id << " ";
        plik << std::endl;
    }
    for (int i = 0; i < led_list.size(); i++)
    {
        plik << "L " << led_list[i]->id << " " << led_list[i]->x_pos << " " << led_list[i]->y_pos << " " << led_list[i]->input_connect << " " << led_list[i]->input_active ;
    }
    plik.close();
}

std::string load(std::vector<Basic_Logic_Components*>* basic_logic_components_list, std::vector<Connection_Wires*>* cable_list, std::vector<Led*>* led_list, std::vector<Button*>* button_list, Add* add_box)
{
    std::fstream plik_f;
    std::vector < std::string> name_list;
    std::string output;
    plik_f.open("Data/main_list.txt", std::ios::in);
    if (!plik_f.is_open())
        throw std::invalid_argument("File Not Find Data/main_list.txt");
    while (!plik_f.eof())
    {
        plik_f >> output;
        name_list.push_back(output);
    }
    plik_f.close();
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
    sf::Texture button_t, button_on_t;
    sf::Sprite button, button_on;
    if (!button_t.loadFromFile("Assets/start/button.png"))
        throw std::invalid_argument("File Not Find Assets/start/button.png");
    if (!button_on_t.loadFromFile("Assets/start/button_presed.png"))
        throw std::invalid_argument("File Not Find Assets/start/button_presed.png");
    button.setTexture(button_t);
    button_on.setTexture(button_on_t);
    button.setPosition(sf::Vector2f(75, 180));
    button_on.setPosition(sf::Vector2f(-1000, -1000));
    //
    sf::Texture textplace_t;
    sf::Sprite textplace;
    if (!textplace_t.loadFromFile("Assets/start/textplace.png"))
        throw std::invalid_argument("File Not Find Assets/start/textplace.png");
    textplace.setTexture(textplace_t);
    textplace.setPosition(sf::Vector2f(30, 50));
    textplace.setScale(1.6, 1);
    //
    sf::Font font;
    if (!font.loadFromFile("Assets/arial.ttf"))
        throw std::invalid_argument("File Not Find Assets/arial.ttf");

    std::string name_str = name_list[0];
    sf::Text name;
    name.setFont(font);
    name.setString(name_str);
    name.setCharacterSize(34);
    name.setFillColor(sf::Color::Black);
    name.setPosition(sf::Vector2f(335 - (name.findCharacterPos(name_str.length() - 1).x - name.getPosition().x) / 2, 75));
    //
    sf::Texture button_text_t;
    sf::Sprite button_text;
    if (!button_text_t.loadFromFile("Assets/start/load.png"))
        throw std::invalid_argument("File Not Find Assets/start/load.png");
    button_text.setTexture(button_text_t);
    button_text.setPosition(sf::Vector2f(270, 250));
    int kursor = 0;
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
                main();
            }

            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (mouse_x > 130 && mouse_x < 580 && mouse_y > 260 && mouse_y < 360)
                    window.close();
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    if (kursor > 0)
                    {
                        kursor--;
                        name_str = name_list[kursor];
                        name.setString(name_str);
                        name.setPosition(sf::Vector2f(335 - (name.findCharacterPos(name_str.length() - 1).x - name.getPosition().x) / 2, 75));
                    }
                }
                else
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                    {
                        if (kursor < name_list.size() - 1)
                        {
                            kursor++;
                            name_str = name_list[kursor];
                            name.setString(name_str);
                            name.setPosition(sf::Vector2f(335 - (name.findCharacterPos(name_str.length() - 1).x - name.getPosition().x) / 2, 75));
                        }
                    }

            }
        }

        if (mouse_x > 130 && mouse_x < 580 && mouse_y > 260 && mouse_y < 360)


            button_on.setPosition(sf::Vector2f(75, 180));


        else
            button_on.setPosition(sf::Vector2f(-1000, -1000));

        window.clear();
        window.draw(background);
        window.draw(textplace);
        window.draw(name);
        window.draw(button);
        window.draw(button_on);
        window.draw(button_text);
        window.display();
    }
    //
    std::fstream plik_to_open;
    plik_to_open.open("Data/" + name_str + ".txt", std::ios::in);
    if (!plik_to_open.is_open())
        throw std::invalid_argument("File Not Find Data/" + name_str + ".txt");
    char in_type;
    int id,x,y;
    std::string logic_type;
    AND* and_g;
    OR* or_g;
    NAND* nand_g;
    NOR* nor_g;
    XOR* xor_g;
    XNOR* xnor_g;
    Led* led_g;
    Button* button_g;
    Connection_Wires* wire_g;
    int count_c = 0, count_g = 0, count_b = 0, count_l = 0;
    std::cout << "q" << std::endl;
    while (!plik_to_open.eof())
    {
        plik_to_open >> in_type;
        if (in_type == 'C')
        {
            wire_g = new Connection_Wires;
            plik_to_open >> wire_g->id;
            plik_to_open >> wire_g->x_in_pos;
            plik_to_open >> wire_g->y_in_pos;
            plik_to_open >> wire_g->x_out_pos;
            plik_to_open >> wire_g->y_out_pos;
            plik_to_open >> wire_g->on;
            plik_to_open >> wire_g->connected;
            plik_to_open >> wire_g->input_number;
            plik_to_open >> wire_g->input_button_bool;
            plik_to_open >> wire_g->output_led;
            cable_list->push_back(wire_g);
            count_c++;
            std::cout << "c" << std::endl;
        }
        else if (in_type == 'G')
        {
            std::cout << "g" << std::endl;
            plik_to_open >> id;
            plik_to_open >> logic_type;
            if (logic_type == "and")
            {
                and_g = new AND;
                and_g->id = id;
                plik_to_open >> and_g->x_pos;
                plik_to_open >> and_g->y_pos;
                and_g->create(and_g->x_pos, and_g->y_pos);
                plik_to_open >> and_g->input1_connect;
                plik_to_open >> and_g->input2_connect;
                plik_to_open >> and_g->input1_active;
                plik_to_open >> and_g->input2_active;
                plik_to_open >> x;
                basic_logic_components_list->push_back(and_g);
                for (int i = 0; i < x; i++)
                {
                    plik_to_open >> y;
                    for (int j = 0; j < cable_list->size(); j++)
                        if (cable_list->at(j)->id == y)
                            cable_list->at(j)->create(cable_list->at(j)->x_in_pos, cable_list->at(j)->y_in_pos, basic_logic_components_list->at(basic_logic_components_list->size() - 1), NULL);
                           // and_g->output_list.push_back(cable_list->at(j));
                    
                }
                
                count_g++;
            }
            else if (logic_type == "or")
            {
                or_g = new OR;
                or_g->id = id;
                plik_to_open >> or_g->x_pos;
                plik_to_open >> or_g->y_pos;
                or_g->create(or_g->x_pos, or_g->y_pos);
                plik_to_open >> or_g->input1_connect;
                plik_to_open >> or_g->input2_connect;
                plik_to_open >> or_g->input1_active;
                plik_to_open >> or_g->input2_active;
                plik_to_open >> x;
                /*for (int i = 0; i < x; i++)
                {
                    plik_to_open >> y;
                    for (int j = 0; j < cable_list->size(); j++)
                        if (cable_list->at(j)->id == y)
                            or_g->output_list.push_back(cable_list->at(j));
                }*/
                basic_logic_components_list->push_back(or_g);
                for (int i = 0; i < x; i++)
                {
                    plik_to_open >> y;
                    for (int j = 0; j < cable_list->size(); j++)
                        if (cable_list->at(j)->id == y)
                            cable_list->at(j)->create(cable_list->at(j)->x_in_pos, cable_list->at(j)->y_in_pos, basic_logic_components_list->at(basic_logic_components_list->size() - 1), NULL);
                            // and_g->output_list.push_back(cable_list->at(j));

                }
                count_g++;
            }
            else  if (logic_type == "nand")
            {
                nand_g = new NAND;
                nand_g->id = id;
                plik_to_open >> nand_g->x_pos;
                plik_to_open >> nand_g->y_pos;
                nand_g->create(nand_g->x_pos, nand_g->y_pos);
                plik_to_open >> nand_g->input1_connect;
                plik_to_open >> nand_g->input2_connect;
                plik_to_open >> nand_g->input1_active;
                plik_to_open >> nand_g->input2_active;
                plik_to_open >> x;
              /*  for (int i = 0; i < x; i++)
                {
                    plik_to_open >> y;
                    for (int j = 0; j < cable_list->size(); j++)
                        if (cable_list->at(j)->id == y)
                            nand_g->output_list.push_back(cable_list->at(j));
                }*/
                basic_logic_components_list->push_back(nand_g);
                for (int i = 0; i < x; i++)
                {
                    plik_to_open >> y;
                    for (int j = 0; j < cable_list->size(); j++)
                        if (cable_list->at(j)->id == y)
                            cable_list->at(j)->create(cable_list->at(j)->x_in_pos, cable_list->at(j)->y_in_pos, basic_logic_components_list->at(basic_logic_components_list->size() - 1), NULL);
                            // and_g->output_list.push_back(cable_list->at(j));

                }
                count_g++;
            }
            else if (logic_type == "nor")
            {
                nor_g = new NOR;
                nor_g->id = id;
                plik_to_open >> nor_g->x_pos;
                plik_to_open >> nor_g->y_pos;
                nor_g->create(nor_g->x_pos, nor_g->y_pos);
                plik_to_open >> nor_g->input1_connect;
                plik_to_open >> nor_g->input2_connect;
                plik_to_open >> nor_g->input1_active;
                plik_to_open >> nor_g->input2_active;
                plik_to_open >> x;
               /* for (int i = 0; i < x; i++)
                {
                    plik_to_open >> y;
                    for (int j = 0; j < cable_list->size(); j++)
                        if (cable_list->at(j)->id == y)
                            nor_g->output_list.push_back(cable_list->at(j));
                }*/
                basic_logic_components_list->push_back(nor_g);
                for (int i = 0; i < x; i++)
                {
                    plik_to_open >> y;
                    for (int j = 0; j < cable_list->size(); j++)
                        if (cable_list->at(j)->id == y)
                            cable_list->at(j)->create(cable_list->at(j)->x_in_pos, cable_list->at(j)->y_in_pos, basic_logic_components_list->at(basic_logic_components_list->size() - 1), NULL);
                            // and_g->output_list.push_back(cable_list->at(j));

                }
                count_g++;
            }
            else if (logic_type == "xor")
            {
                xor_g = new XOR;
                xor_g->id = id;
                plik_to_open >> xor_g->x_pos;
                plik_to_open >> xor_g->y_pos;
                xor_g->create(xor_g->x_pos, xor_g->y_pos);
                plik_to_open >> xor_g->input1_connect;
                plik_to_open >> xor_g->input2_connect;
                plik_to_open >> xor_g->input1_active;
                plik_to_open >> xor_g->input2_active;
                plik_to_open >> x;
               /* for (int i = 0; i < x; i++)
                {
                    plik_to_open >> y;
                    for (int j = 0; j < cable_list->size(); j++)
                        if (cable_list->at(j)->id == y)
                            xor_g->output_list.push_back(cable_list->at(j));
                }*/
                basic_logic_components_list->push_back(xor_g);
                for (int i = 0; i < x; i++)
                {
                    plik_to_open >> y;
                    for (int j = 0; j < cable_list->size(); j++)
                        if (cable_list->at(j)->id == y)
                            cable_list->at(j)->create(cable_list->at(j)->x_in_pos, cable_list->at(j)->y_in_pos, basic_logic_components_list->at(basic_logic_components_list->size() - 1), NULL);
                            // and_g->output_list.push_back(cable_list->at(j));

                }
                count_g++;
            }
            else if (logic_type == "xnor")
            {
            xnor_g = new XNOR;
            xnor_g->id = id;
            plik_to_open >> xnor_g->x_pos;
            plik_to_open >> xnor_g->y_pos;
            xnor_g->create(xnor_g->x_pos, xnor_g->y_pos);
            plik_to_open >> xnor_g->input1_connect;
            plik_to_open >> xnor_g->input2_connect;
            plik_to_open >> xnor_g->input1_active;
            plik_to_open >> xnor_g->input2_active;
            plik_to_open >> x;
          /*  for (int i = 0; i < x; i++)
            {
                plik_to_open >> y;
                for (int j = 0; j < cable_list->size(); j++)
                    if (cable_list->at(j)->id == y)
                        xnor_g->output_list.push_back(cable_list->at(j));
            }*/
            basic_logic_components_list->push_back(xnor_g);
            for (int i = 0; i < x; i++)
            {
                plik_to_open >> y;
                for (int j = 0; j < cable_list->size(); j++)
                    if (cable_list->at(j)->id == y)
                        cable_list->at(j)->create(cable_list->at(j)->x_in_pos, cable_list->at(j)->y_in_pos, basic_logic_components_list->at(basic_logic_components_list->size() - 1), NULL);
                        // and_g->output_list.push_back(cable_list->at(j));

            }
            count_g++;
            }
        }
        else if (in_type == 'B')
        {
            std::cout << "b" << std::endl;
            button_g = new Button;
            plik_to_open >> button_g->id;
            plik_to_open >> button_g->x_pos;
            plik_to_open >> button_g->y_pos;
            plik_to_open >> button_g->output_active;
            plik_to_open >> button_g->hold;
            button_g->create(button_g->x_pos, button_g->y_pos, button_g->hold);
            plik_to_open >> x;
         /*   for (int i = 0; i < x; i++)
            {
                plik_to_open >> y;
                for (int j = 0; j < cable_list->size(); j++)
                    if (cable_list->at(j)->id == y)
                        button_g->output_list.push_back(cable_list->at(j));
            }*/
           button_list->push_back(button_g);
           for (int i = 0; i < x; i++)
           {
               plik_to_open >> y;
               for (int j = 0; j < cable_list->size(); j++)
                   if (cable_list->at(j)->id == y)
                       cable_list->at(j)->create(cable_list->at(j)->x_in_pos, cable_list->at(j)->y_in_pos, NULL, button_list->at(button_list->size()-1));
                       // and_g->output_list.push_back(cable_list->at(j));

           }
           count_b++;
        }
        else if (in_type == 'L')
            {
            std::cout << "l" << std::endl;
                led_g = new Led;
                plik_to_open >> led_g->id;
                plik_to_open >> led_g->x_pos;
                plik_to_open >> led_g->y_pos;
                plik_to_open >> led_g->input_connect;
                plik_to_open >> led_g->input_active;
                led_g->create(led_g->x_pos, led_g->y_pos);
                led_list->push_back(led_g);
                count_l++;
            }
            

            std::cout << "f" << std::endl;
    }
    plik_to_open.close();
    add_box->connection_wires_id_count = count_c;
    add_box->buttons_id_count = count_b;
    add_box->logic_components_id_count = count_l;
    add_box->leds_id_count = count_l;
    plik_to_open.open("Data/" + name_str + ".txt", std::ios::in);
    bool C = true;
    std::string in_unnown;
    int count = 0;
    std::cout << "e" << std::endl;
    while (!plik_to_open.eof() && C)
    {
        plik_to_open >> in_type;
        if (in_type == 'C')
        {
            plik_to_open >> x >> x >> x >> x >> x >> x >> x >> x >> x >> x >> in_unnown;
            if (in_unnown == "l")
            {
                plik_to_open >> x;
                for (int i = 0; i < led_list->size(); i++)
                    if (x == led_list->at(i)->id)
                        cable_list->at(count)->create_output(cable_list->at(count)->input_number, NULL, led_list->at(i));
            }
            else
            {
                x = std::stoi(in_unnown);
                std::cout << x << std::endl;
                for (int i = 0; i < basic_logic_components_list->size(); i++)
                {
                    std::cout << '1'<< std::endl;
                    if (x == basic_logic_components_list->at(i)->id)
                    {
                        cable_list->at(count)->create_output(cable_list->at(count)->input_number, basic_logic_components_list->at(i), NULL);
                       // cable_list->at(count)->out_basic = basic_logic_components_list->at(i);
                        std::cout <<"x" << count << " "<<  cable_list->at(count)->out_basic->id << std::endl;
                    }
                }
            }

        }
        else C = false;
        count++;
    }
    std::cout << "d" << std::endl;
    plik_to_open.close();
    return name_str;
}