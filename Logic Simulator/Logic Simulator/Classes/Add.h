#pragma once
#include "SFML/Graphics.hpp"
#include "Basic_Logic_Gates.h"

struct Add
{
private:
	std::vector<Basic_Logic_Components*> list;
	int on = 1;
	int window_size;
	sf::RectangleShape box;
	AND and_g;
	NAND nand_g;
	OR or_g;
	NOR nor_g;
	XOR xor_g;
	XNOR xnor_g;

public:
	Add(int x);
	void draw(sf::RenderWindow* window);
	void press();
	void create();
	void move_list(int x);
};

