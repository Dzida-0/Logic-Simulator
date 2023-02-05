#include "Add.h"
#include <iostream>
Add::Add(int x)
{	
	window_size = x;
	box.setPosition(sf::Vector2f(x * 0.8, 50));
	box.setSize(sf::Vector2f(x * 0.1, 700));
	box.setFillColor(sf::Color::Color(180, 180, 180, 255));
	and_g.create(x * 0.8, -1000);
	list.push_back(&and_g);
	or_g.create(x * 0.8, -1000);
	list.push_back(&or_g);
	nand_g.create(x * 0.8, -1000);
	list.push_back(&nand_g);
	xor_g.create(x * 0.8, -1000);
	list.push_back(&xor_g);
	nor_g.create(x * 0.8, -1000);
	list.push_back(&nor_g);
	xnor_g.create(x * 0.8, -1000);
	list.push_back(&xnor_g);
}

void Add::draw(sf::RenderWindow* window)
{
	window->draw(box);
	for (int i = 0; i < 6; i++)
	{
		Basic_Logic_Components* x = list[i];
		if (i >= on-1 && i < on + 2)
			x->move(window_size * 0.8+ 100, 100 + (i - on + 2) * 150);
		else
			x->move(window_size * 0.8, -1000);
		x->draw(window);
	}
}

void Add::move_list(int x)
{
	on += x;
	if (on == 0)
		on++;
	else if (on == 5)
		on--;
}