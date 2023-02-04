#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class Background
{
    std::vector<sf::Sprite> vector_background;
    sf::Sprite background;
    sf::Texture background_t;
    int size_x = 0;
    int size_y = 0;
public:
    Background(int x, int y);
    void draw(sf::RenderWindow* window);
    void move(int x, int y);
};

