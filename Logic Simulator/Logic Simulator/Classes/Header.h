#pragma once
#include "SFML/Graphics.hpp"
#include "Add.h"

class Header
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
	sf::Texture back_t, back_inact_t, save_t, save_inact_t;
	sf::Sprite back, back_inact, save, save_inact;
	sf::Texture touch_t, edit_t, edit_inact_t, connect_t, connect_inact_t, trash_t, trash_inact_t;
	sf::Sprite touch, edit, edit_inact, connect, connect_inact, trash, trash_inact;
	sf::RectangleShape bar_touch, bar_edit, bar_connect, bar_trash;
	sf::Texture add_t;
	sf::Sprite add;
};

