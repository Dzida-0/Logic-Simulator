#include "Header.h"

Header::Header(int x)
{
    bar.setSize(sf::Vector2f(x, 50));
    bar_bottom.setSize(sf::Vector2f(x, 5));
    bar.setFillColor(sf::Color::Color(180, 180, 180, 255));
    bar_bottom.setFillColor(sf::Color::Color(240, 240, 240, 255));
    bar_bottom.setPosition(sf::Vector2f(0, 45));
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
    touch.setPosition(sf::Vector2f(x*0.6, 5));
    touch.setScale(sf::Vector2f(0.07, 0.07));
    //
    if (!edit_t.loadFromFile("Assets/header/edit.png"))
        throw std::invalid_argument("File Not Find Assets/header/edit.png");
    edit.setTexture(edit_t);
    edit.setPosition(sf::Vector2f(x * 0.6+70, 5));
    edit.setScale(sf::Vector2f(0.07, 0.07));
    //
    if (!edit_inact_t.loadFromFile("Assets/header/edit_inact.png"))
        throw std::invalid_argument("File Not Find Assets/header/edit_inact.png");
    edit_inact.setTexture(edit_inact_t);
    edit_inact.setPosition(sf::Vector2f(x * 0.6+70, 5));
    edit_inact.setScale(sf::Vector2f(0.07, 0.07));
    //
    if (!connect_t.loadFromFile("Assets/header/connect.png"))
        throw std::invalid_argument("File Not Find Assets/header/connect.png");
    connect.setTexture(connect_t);
    connect.setPosition(sf::Vector2f(x * 0.6 + 140, 5));
    connect.setScale(sf::Vector2f(0.05, 0.05));
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
}

void Header::draw(sf::RenderWindow* window)
{
    window->draw(bar);
    if (!play_bool)
    {
        window->draw(save);
        window->draw(back);
        window->draw(edit);
        window->draw(connect);
        window->draw(trash);
    }
    else
    {
        window->draw(save_inact);
        window->draw(back_inact);
        window->draw(edit_inact);
        window->draw(connect_inact);
        window->draw(trash_inact);
    }
    window->draw(touch);
    window->draw(bar_bottom);
}
