#pragma once
#include "SFML/Graphics.hpp"

class Header
{	
public:
	bool play_bool = false;
	bool press_bool = true;
	bool move_bool = false;
	bool connect_bool = false;
	bool trash_bool = false;

	Header(int x);
	void draw(sf::RenderWindow* window);

private:
	sf::RectangleShape bar;
	sf::RectangleShape bar_bottom;
	sf::Texture back_t, back_inact_t, save_t, save_inact_t;
	sf::Sprite back, back_inact, save, save_inact;
	sf::Texture touch_t, edit_t, edit_inact_t, connect_t, connect_inact_t, trash_t, trash_inact_t;
	sf::Sprite touch, edit, edit_inact, connect, connect_inact, trash, trash_inact;
};

