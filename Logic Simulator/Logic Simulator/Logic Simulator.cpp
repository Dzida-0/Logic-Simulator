#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include <time.h>

class Basic_Logic_Components;
class Connection_Wires;

std::vector<Basic_Logic_Components> basic_logic_components_list;



class Basic_Logic_Components {
public:
    int x_pos = 0;
    int y_pos = 0;
    int width = 200;
    int height = 200;
    float scale = 0.5;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::CircleShape in_1;
    sf::CircleShape in_2;
    sf::CircleShape out;

    void create(int x, int y) {
        x_pos = x;
        y_pos = y;
        texture.loadFromFile("OR.png");
        sprite.setTexture(texture);
        sprite.setScale(sf::Vector2f(scale, scale));
        sprite.setPosition(sf::Vector2f(x_pos, y_pos));
        width *= scale;
        height *= scale;
        in_1.setRadius(5.0f);
        in_1.setFillColor(sf::Color::Cyan);
        in_1.setPosition(x_pos - 10 * scale, y_pos + 80 * scale);
        in_2.setRadius(5.0f);
        in_2.setFillColor(sf::Color::Cyan);
        in_2.setPosition(x_pos - 10 * scale, y_pos + 130 * scale);
        out.setRadius(5.0f);
        out.setFillColor(sf::Color::Cyan);
        out.setPosition(x_pos + 180 * scale, y_pos + 100 * scale);

    }

    void move(int x, int y)
    {
        if (x - width / 2 > 10 && y - height / 2 > 20)
        {
            x_pos = x - width / 2;
            y_pos = y - height / 2;
            sprite.setPosition(sf::Vector2f(x_pos, y_pos));
            in_1.setPosition(x_pos - 10 * scale, y_pos + 80 * scale);
            in_2.setPosition(x_pos - 10 * scale, y_pos + 130 * scale);
            out.setPosition(x_pos + 180 * scale, y_pos + 100 * scale);
        }
    }

    bool on_click(int x, int y)
    {
        return bool(x_pos < x&& x < x_pos + width && y_pos < y&& y < y_pos + height);
    }
};

class OR : public Basic_Logic_Components {
public:
    void a()
    {
        std::cout << 'or';
    }
};

class Connection_Wires {

    Basic_Logic_Components* in{};
    Basic_Logic_Components* out{};
    int x_in_pos = 0;
    int y_in_pos = 0;
    int x_out_pos = 0;
    int y_out_pos = 0;
    bool on = false;
    bool straight_line = false;

    void is_on()
    {

    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode().getDesktopMode(), "Logic Simulator", sf::Style::None);
    //window.setIcon();
    sf::RectangleShape background;
    background.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    background.setFillColor(sf::Color::Color(100, 100, 100, 255));
    //window.setFramerateLimit(100);

    Basic_Logic_Components x, y;
    Basic_Logic_Components* z{};
    bool move_mode = true;
    bool connect_mode = true;
    bool move_active = false;
    x.create(10, 10);
    basic_logic_components_list.push_back(x);

    y.create(500, 500);
    basic_logic_components_list.push_back(y);
    OR e;
    e.create(30, 30);
    basic_logic_components_list.push_back(e);
    sf::Mouse mouse;
    int mouse_x = mouse.getPosition().x;
    int mouse_y = mouse.getPosition().y;
    while (window.isOpen())
    {
        mouse_x = mouse.getPosition().x;
        mouse_y = mouse.getPosition().y;
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (move_mode)
                {
                    for (int i = 0; i < basic_logic_components_list.size(); i++)
                    {
                        if (basic_logic_components_list[i].on_click(mouse_x, mouse_y))
                        {
                            z = &basic_logic_components_list[i];
                            move_active = true;
                            i = basic_logic_components_list.size();
                        }
                    }
                }

            }
            if (event.type == sf::Event::MouseButtonReleased)
            {
                move_active = false;
            }
        }
        if (move_active)
        {
            z->move(mouse_x, mouse_y);
        }

        window.clear();
        window.draw(background);
        for (int i = 0; i < basic_logic_components_list.size(); i++)
        {
            window.draw(basic_logic_components_list[i].sprite);
            window.draw(basic_logic_components_list[i].in_1);
            window.draw(basic_logic_components_list[i].in_2);
            window.draw(basic_logic_components_list[i].out);
        }
        window.display();
    }


    return 0;
}