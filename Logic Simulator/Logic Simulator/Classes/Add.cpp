#include "Add.h"
#include <iostream>

Add::Add(int x, std::vector<Basic_Logic_Components*>* list_in, std::vector<Led*>* list_in_led, std::vector<Button*>* list_in_button)
{
	list_gates = list_in;
	list_led = list_in_led;
	list_button = list_in_button;
	window_size = x;
	box.setPosition(sf::Vector2f(x * 0.8 - 15, 50));
	box.setSize(sf::Vector2f(130, 350));
	box.setFillColor(sf::Color::Color(180, 180, 180, 255));
	//
	if (!and_t.loadFromFile("Assets/AND.png"))
		std::cout << "";
	and_s.setTexture(and_t);
	and_s.setPosition(sf::Vector2f(x * 0.8, -1000));
	and_s.setScale(sf::Vector2f(0.5, 0.5));
	list.push_back(and_s);
	//
	if (!or_t.loadFromFile("Assets/OR.png"))
		std::cout << "";
	or_s.setTexture(or_t);
	or_s.setPosition(sf::Vector2f(x * 0.8, -1000));
	or_s.setScale(sf::Vector2f(0.5, 0.5));
	list.push_back(or_s);
	//
	if (!nand_t.loadFromFile("Assets/NAND.png"))
		std::cout << "";
	nand_s.setTexture(nand_t);
	nand_s.setPosition(sf::Vector2f(x * 0.8, -1000));
	nand_s.setScale(sf::Vector2f(0.5, 0.5));
	list.push_back(nand_s);
	//
	if (!nor_t.loadFromFile("Assets/NOR.png"))
		std::cout << "";
	nor_s.setTexture(nor_t);
	nor_s.setPosition(sf::Vector2f(x * 0.8, -1000));
	nor_s.setScale(sf::Vector2f(0.5, 0.5));
	list.push_back(nor_s);
	//
	if (!xor_t.loadFromFile("Assets/XOR.png"))
		std::cout << "";
	xor_s.setTexture(xor_t);
	xor_s.setPosition(sf::Vector2f(x * 0.8, -1000));
	xor_s.setScale(sf::Vector2f(0.5, 0.5));
	list.push_back(xor_s);
	//
	if (!xnor_t.loadFromFile("Assets/XNOR.png"))
		std::cout << "";
	xnor_s.setTexture(xnor_t);
	xnor_s.setPosition(sf::Vector2f(x * 0.8, -1000));
	xnor_s.setScale(sf::Vector2f(0.5, 0.5));
	list.push_back(xnor_s);
	//
	if (!led_t.loadFromFile("Assets/light_off.png"))
		std::cout << "";
	led_s.setTexture(led_t);
	led_s.setPosition(sf::Vector2f(x * 0.8, -1000));
	led_s.setScale(sf::Vector2f(0.5, 0.5));
	list.push_back(led_s);
	//
	if (!button_t.loadFromFile("Assets/button_off.png"))
		std::cout << "";
	button_s.setTexture(button_t);
	button_s.setPosition(sf::Vector2f(x * 0.8, -1000));
	button_s.setScale(sf::Vector2f(0.5, 0.5));
	list.push_back(button_s);
	//
	if (!button_t_press.loadFromFile("Assets/button_press_off.png"))
		std::cout << "";
	button_s_press.setTexture(button_t_press);
	button_s_press.setPosition(sf::Vector2f(x * 0.8, -1000));
	button_s_press.setScale(sf::Vector2f(0.5, 0.5));
	list.push_back(button_s_press);
}


void Add::draw(sf::RenderWindow* window)
{
	if (add_on)
	{
		window->draw(box);
		for (int i = 0; i < 9; i++)
		{
			sf::Sprite x = list[i];
			if (i >= on - 1 && i < on + 2)
				x.setPosition(window_size * 0.8, (i - on + 2) * 110 - 50);
			else
				x.setPosition(window_size * 0.8, -1000);
			window->draw(x);
		}
	}
}

void Add::move_list(int x)
{
	on += x;
	if (on == 0)
		on++;
	else if (on == 8)
		on--;
}

void Add::press(int x, int y)
{
	if (x > window_size * 0.8 && x < window_size * 0.8 + 100)
	{
		for (int i = 0; i < 3; i++)
		{
			if (y > (i + 1) * 110 - 50 && y < (i + 1) * 110 + 50)
			{
				if (on + i - 1 == 0)
				{
					and_g = new AND;
					and_g->id = logic_components_id_count++;
					and_g->type = "and";
					and_g->create(window_size * 0.8 - 150, (i + 1) * 110 - 50);
					list_gates->push_back(and_g);
				}
				else if (on + i - 1 == 1)
				{
					or_g = new OR;
					or_g->id = logic_components_id_count++;
					or_g->type = "or";
					or_g->create(window_size * 0.8 - 150, (i + 1) * 110 - 50);
					list_gates->push_back(or_g);
				}
				else if (on + i - 1 == 2)
				{
					nand_g = new NAND;
					nand_g->id = logic_components_id_count++;
					nand_g->type = "nand";
					nand_g->create(window_size * 0.8 - 150, (i + 1) * 110 - 50);
					list_gates->push_back(nand_g);
				}
				else if (on + i - 1 == 3)
				{
					nor_g = new NOR;
					nor_g->id = logic_components_id_count++;
					nor_g->type = "nor";
					nor_g->create(window_size * 0.8 - 150, (i + 1) * 110 - 50);
					list_gates->push_back(nor_g);
				}
				else if (on + i - 1 == 4)
				{
					xor_g = new XOR;
					xor_g->id = logic_components_id_count++;
					xor_g->type = "xor";
					xor_g->create(window_size * 0.8 - 150, (i + 1) * 110 - 50);
					list_gates->push_back(xor_g);
				}
				else if (on + i - 1 == 5)
				{
					xnor_g = new XNOR;
					xnor_g->id = logic_components_id_count++;
					xnor_g->type = "xnor";
					xnor_g->create(window_size * 0.8 - 150, (i + 1) * 110 - 50);
					list_gates->push_back(xnor_g);
				}
				else if (on + i - 1 == 6)
				{
					led_g = new Led;
					led_g->id = leds_id_count++;
					led_g->create(window_size * 0.8 - 150, (i + 1) * 110 - 50);
					list_led->push_back(led_g);
				}
				else if (on + i - 1 == 7)
				{
					button_g = new Button;
					button_g->id = buttons_id_count++;
					button_g->create(window_size * 0.8 - 150, (i + 1) * 110 - 50, true);
					list_button->push_back(button_g);
				}
				else if (on + i - 1 == 8)
				{
					button_g = new Button;
					button_g->id = buttons_id_count++;
					button_g->create(window_size * 0.8 - 150, (i + 1) * 110 - 50, false);
					list_button->push_back(button_g);
				}
			}
		}
	}
}