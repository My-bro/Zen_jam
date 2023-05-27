/*
** EPITECH PROJECT, 2023
** Epitech-Jam
** File description:
** main
*/

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "ying_col.h"

char *buffer_maker(char *av);
std::vector<std::string> splitString(const std::string &str, const std::string &separator);

ying_col_s init_shape(sf::Color pubgmobil, float angle);
void modify_angle(sf::Event event , sf::Sprite *sprite_ying_yang, float rayon, ying_col_s *red_col, ying_col_s *blu_col);
void actualise_values(sf::Sprite sprite_ying_yang , float radius, ying_col_s *red_col, ying_col_s *blu_col);


int main(int ac, char **av)
{
    sf::Event event;
    sf::RenderWindow window(sf::VideoMode(4010, 4066), "SFML Simple Window");
    window.setFramerateLimit(100);
    sf::Sprite sprite_ying_yang;
    sf::Texture texture;
    sprite_ying_yang.setPosition(1430,1330);
    sprite_ying_yang.setScale(0.3,0.3);
    if (!texture.loadFromFile("./src/yinyang.png")) {
        return 84;
    }
    sprite_ying_yang.setTexture(texture);

    ying_col_s red_col = init_shape(sf::Color::Red, 1.45);
    ying_col_s blu_col = init_shape(sf::Color::Blue, -1.45);
    const float radius = texture.getSize().y / 13.0f;
    float rayon = 8.0f;

    std::string file = buffer_maker("./src/configuration_file.txt");
    std::vector<std::string> db = splitString(file," ");

    for (std::vector<std::string>::const_iterator it = db.begin(); it != db.end(); ++it) {
        std::cout << *it << std::endl;
    }

    while (window.isOpen()) {
        window.clear(sf::Color::White);
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                modify_angle(event ,&sprite_ying_yang, rayon, &red_col, &blu_col);
            }
        }

        actualise_values(sprite_ying_yang , radius, &red_col, &blu_col);

        sf::FloatRect spriteBounds = sprite_ying_yang.getLocalBounds();
        sprite_ying_yang.setOrigin(spriteBounds.width / 2, spriteBounds.height / 2);

        window.draw(sprite_ying_yang);
        window.draw(red_col.square);
        window.draw(blu_col.square);
        window.display();
    }
    return 0;
}

