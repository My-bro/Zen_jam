/*
** EPITECH PROJECT, 2023
** Zen_jam
** File description:
** colision_shape
*/

#include <SFML/Graphics.hpp>
#include "ying_col.h"

ying_col_s init_shape(sf::Color pubgmobil, float angle)
{
    sf::RectangleShape square(sf::Vector2f(40, 40));
    square.setFillColor(pubgmobil);
    square.setOrigin(20, 20);
    ying_col_s col = {square,angle,angle};
    return col;
}

void modify_angle(sf::Event event , sf::Sprite *sprite_ying_yang, float rayon, ying_col_s *red_col, ying_col_s *blu_col)
{
    if (event.key.code == sf::Keyboard::Left) {
        sprite_ying_yang->setRotation(sprite_ying_yang->getRotation() - rayon);
        red_col->angle -= rayon / 57.3;
        blu_col->angle -= rayon / 57.3;
    } else if (event.key.code == sf::Keyboard::Right) {
        sprite_ying_yang->setRotation(sprite_ying_yang->getRotation() + rayon);
        red_col->angle += rayon / 57.3;
        blu_col->angle += rayon / 57.3;
    }
}

void actualise_values(sf::Sprite sprite_ying_yang , float radius, ying_col_s *red_col, ying_col_s *blu_col)
{
    sf::Vector2f pos = sprite_ying_yang.getPosition();
    pos.x += cos(red_col->angle) * radius;
    pos.y += sin(red_col->angle) * radius;

    sf::Vector2f pos_blue = sprite_ying_yang.getPosition();
    pos_blue.x += cos(blu_col->angle) * radius;
    pos_blue.y += sin(blu_col->angle) * radius;

    red_col->square.setPosition(pos);
    blu_col->square.setPosition(pos_blue);
}