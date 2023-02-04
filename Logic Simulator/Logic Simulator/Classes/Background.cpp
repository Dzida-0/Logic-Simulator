#include "Background.h"

Background::Background(int x, int y)
{
    background_t.loadFromFile("Assets/background.png");
    background.setTexture(background_t);
    background.setScale(sf::Vector2f(1, 1));
    for (int i = 0; i <= (y / 760) + 1; i++)
    {
        size_y++;
        size_x = 0;
        for (int j = 0; j <= (x / 760) + 1; j++)
        {
            background.setPosition(sf::Vector2f(-760 + 760 * j, -760 + 760 * i));
            vector_background.push_back(background);
            size_x++;
        }
    }
}

void Background::draw(sf::RenderWindow* window)
{
    for (int i = 0; i < vector_background.size(); i++)
        window->draw(vector_background[i]);
}

void Background::move(int x, int y)
{
    for (int i = 0; i < vector_background.size(); i++)
    {
        vector_background[i].setPosition(sf::Vector2f(vector_background[i].getPosition().x + x, vector_background[i].getPosition().y + y));
        if (vector_background[i].getPosition().x < -960)
            vector_background[i].setPosition(sf::Vector2f(vector_background[i].getPosition().x + size_x * 760, vector_background[i].getPosition().y));
        else  if (vector_background[i].getPosition().x > -960 + size_x * 760)
            vector_background[i].setPosition(sf::Vector2f(vector_background[i].getPosition().x - size_x * 760, vector_background[i].getPosition().y));
        if (vector_background[i].getPosition().y < -960)
            vector_background[i].setPosition(sf::Vector2f(vector_background[i].getPosition().x, vector_background[i].getPosition().y + size_y * 760));
        else  if (vector_background[i].getPosition().y > -960 + size_y * 760)
            vector_background[i].setPosition(sf::Vector2f(vector_background[i].getPosition().x, vector_background[i].getPosition().y - size_y * 760));
    }
}