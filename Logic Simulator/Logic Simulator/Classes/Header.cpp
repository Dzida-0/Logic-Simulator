#include "Header.h"

Header::Header(int x, bool* add_on_p)
{
    add_on = add_on_p;
    size = x;
    bar.setSize(sf::Vector2f(x, 50));
    bar_bottom.setSize(sf::Vector2f(x, 5));
    bar.setFillColor(sf::Color::Color(180, 180, 180, 255));
    bar_bottom.setFillColor(sf::Color::Color(240, 240, 240, 255));
    bar_bottom.setPosition(sf::Vector2f(0, 45));
    //
    bar_touch.setSize(sf::Vector2f(50, 6));
    bar_touch.setPosition(sf::Vector2f(x * 0.6 - 10, 44));
    bar_touch.setFillColor(sf::Color::Color(0, 0, 0, 255));
    bar_edit.setSize(sf::Vector2f(50, 6));
    bar_edit.setPosition(sf::Vector2f(x * 0.6 + 63, 44));
    bar_edit.setFillColor(sf::Color::Color(0, 0, 0, 255));
    bar_connect.setSize(sf::Vector2f(50, 6));
    bar_connect.setPosition(sf::Vector2f(x * 0.6 + 135, 44));
    bar_connect.setFillColor(sf::Color::Color(0, 0, 0, 255));
    bar_trash.setSize(sf::Vector2f(50, 6));
    bar_trash.setPosition(sf::Vector2f(x * 0.6 + 205, 44));
    bar_trash.setFillColor(sf::Color::Color(0, 0, 0, 255));
    //
    if (!back_t.loadFromFile("Assets/header/back.png"))
        throw std::invalid_argument("File Not Find Assets/header/back.png");
    back.setTexture(back_t);
    back.setPosition(sf::Vector2f(5, 5));
    back.setScale(sf::Vector2f(0.2, 0.2));
    //
    if (!back_inact_t.loadFromFile("Assets/header/back_inact.png"))
        throw std::invalid_argument("File Not Find Assets/header/back_inact.png");
    back_inact.setTexture(back_inact_t);
    back_inact.setPosition(sf::Vector2f(5, 5));
    back_inact.setScale(sf::Vector2f(0.2, 0.2));
    //
    if (!save_t.loadFromFile("Assets/header/save.png"))
        throw std::invalid_argument("File Not Find Assets/header/save.png");
    save.setTexture(save_t);
    save.setPosition(sf::Vector2f(90, 5));
    save.setScale(sf::Vector2f(0.17, 0.17));
    //
    if (!save_inact_t.loadFromFile("Assets/header/save_inact.png"))
        throw std::invalid_argument("File Not Find Assets/header/save_inact.png");
    save_inact.setTexture(save_inact_t);
    save_inact.setPosition(sf::Vector2f(90, 5));
    save_inact.setScale(sf::Vector2f(0.17, 0.17));
    //
    if (!touch_t.loadFromFile("Assets/header/touch.png"))
        throw std::invalid_argument("File Not Find Assets/header/touch.png");
    touch.setTexture(touch_t);
    touch.setPosition(sf::Vector2f(x * 0.6, 5));
    touch.setScale(sf::Vector2f(0.07, 0.07));
    //
    if (!edit_t.loadFromFile("Assets/header/edit.png"))
        throw std::invalid_argument("File Not Find Assets/header/edit.png");
    edit.setTexture(edit_t);
    edit.setPosition(sf::Vector2f(x * 0.6 + 70, 5));
    edit.setScale(sf::Vector2f(0.07, 0.07));
    //
    if (!edit_inact_t.loadFromFile("Assets/header/edit_inact.png"))
        throw std::invalid_argument("File Not Find Assets/header/edit_inact.png");
    edit_inact.setTexture(edit_inact_t);
    edit_inact.setPosition(sf::Vector2f(x * 0.6 + 70, 5));
    edit_inact.setScale(sf::Vector2f(0.07, 0.07));
    //
    if (!connect_t.loadFromFile("Assets/header/connect.png"))
        throw std::invalid_argument("File Not Find Assets/header/connect.png");
    connect.setTexture(connect_t);
    connect.setPosition(sf::Vector2f(x * 0.6 + 140, 5));
    connect.setScale(sf::Vector2f(0.04, 0.04));
    //
    if (!connect_inact_t.loadFromFile("Assets/header/connect_inact.png"))
        throw std::invalid_argument("File Not Find Assets/header/connect_inact.png");
    connect_inact.setTexture(connect_inact_t);
    connect_inact.setPosition(sf::Vector2f(x * 0.6 + 140, 5));
    connect_inact.setScale(sf::Vector2f(0.05, 0.05));
    //
    if (!trash_t.loadFromFile("Assets/header/trash.png"))
        throw std::invalid_argument("File Not Find Assets/header/trash.png");
    trash.setTexture(trash_t);
    trash.setPosition(sf::Vector2f(x * 0.6 + 210, 5));
    trash.setScale(sf::Vector2f(0.07, 0.07));
    //
    if (!trash_inact_t.loadFromFile("Assets/header/trash_inact.png"))
        throw std::invalid_argument("File Not Find Assets/header/trash_inact.png");
    trash_inact.setTexture(trash_inact_t);
    trash_inact.setPosition(sf::Vector2f(x * 0.6 + 210, 5));
    trash_inact.setScale(sf::Vector2f(0.07, 0.07));
    //
    if (!add_t.loadFromFile("Assets/header/add.png"))
        throw std::invalid_argument("File Not Find Assets/header/add.png");
    add.setTexture(add_t);
    add.setPosition(sf::Vector2f(x * 0.8, 4));
    add.setScale(sf::Vector2f(0.05, 0.05));
}

void Header::draw(sf::RenderWindow* window)
{
    window->draw(bar);
    window->draw(save);
    window->draw(back);
    window->draw(edit);
    window->draw(connect);
    window->draw(trash);

    if (move_bool)
        window->draw(add);
    window->draw(touch);

    window->draw(bar_bottom);
    if (press_bool)
        window->draw(bar_touch);
    else if (move_bool)
        window->draw(bar_edit);
    else if (connect_bool)
        window->draw(bar_connect);
    else if (trash_bool)
        window->draw(bar_trash);
}

void Header::press(int x)
{
    if (x > size * 0.6 && x < size * 0.6 + 50)
    {
        press_bool = true;
        move_bool = false;
        connect_bool = false;
        trash_bool = false;
        *add_on = false;
    }
    else if (x > size * 0.6 + 70 && x < size * 0.6 + 120)
    {
        press_bool = false;
        move_bool = true;
        connect_bool = false;
        trash_bool = false;
        *add_on = false;
    }
    else if (x > size * 0.6 + 140 && x < size * 0.6 + 190)
    {
        press_bool = false;
        move_bool = false;
        connect_bool = true;
        trash_bool = false;
        *add_on = false;
    }
    else if (x > size * 0.6 + 210 && x < size * 0.6 + 280)
    {
        press_bool = false;
        move_bool = false;
        connect_bool = false;
        trash_bool = true;
        *add_on = false;
    }
    else if (x > size * 0.8 && x < size * 0.8 + 50 && move_bool)
    {
        if (*add_on)
            *add_on = false;
        else
            *add_on = true;
    }

}

