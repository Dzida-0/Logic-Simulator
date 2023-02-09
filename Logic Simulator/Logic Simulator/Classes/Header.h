#pragma once
#include "SFML/Graphics.hpp"
#include "Add.h"

class Header // klasa odpowiedzialna za pasek narzêdzi 
{
public:
	bool press_bool = true;
	bool move_bool = false;
	bool connect_bool = false;
	bool trash_bool = false;
	int size;
	bool* add_on;
	Header(int x, bool* add_on_p);
	void draw(sf::RenderWindow* window);
	void press(int x);

private:
	sf::RectangleShape bar;
	sf::RectangleShape bar_bottom;
	sf::Texture back_t, save_t;
	sf::Sprite back, save;
	sf::Texture touch_t, edit_t, connect_t, trash_t;
	sf::Sprite touch, edit, connect, trash;
	sf::RectangleShape bar_touch, bar_edit, bar_connect, bar_trash;
	sf::Texture add_t;
	sf::Sprite add;
};

