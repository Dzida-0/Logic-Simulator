#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include "Basic_Logic_Gates.h"
#include "Button.h"
#include "Led.h"

struct Add // klasa dodawania nowych elementów
{
private:
	std::vector<sf::Sprite> list;
	std::vector<Basic_Logic_Components*>* list_gates{};
	std::vector<Led*>* list_led{};
	std::vector<Button*>* list_button{};
	int on = 1;
	int window_size;
	sf::RectangleShape box;
	sf::Texture and_t, or_t, nand_t, xor_t, nor_t, xnor_t, led_t, button_t, button_t_press;
	sf::Sprite and_s, or_s, nand_s, xor_s, nor_s, xnor_s, led_s, button_s, button_s_press;
	AND* and_g;
	OR* or_g;
	NAND* nand_g;
	NOR* nor_g;
	XOR* xor_g;
	XNOR* xnor_g;
	Led* led_g;
	Button* button_g, button_g_press;

public:
	int logic_components_id_count = 0;
	int buttons_id_count = 0;
	int leds_id_count = 0;
	int connection_wires_id_count = 0;
	bool add_on = false;

	Add(int x, std::vector<Basic_Logic_Components*>* list_in, std::vector<Led*>* list_in_led, std::vector<Button*>* list_in_button);
	void draw(sf::RenderWindow* window);
	void press(int x, int y);
	void move_list(int x);
};

