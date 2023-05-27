/*
** EPITECH PROJECT, 2023
** Epitech-Jam
** File description:
** main
*/

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <fstream>

#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>

typedef struct ying_col_s {
    sf::RectangleShape square;
    float angleOffset;
    float angle;
} ying_col_t;

char *buffer_maker(char *av)
{
    struct stat bloc;
    stat(av, &bloc);
    int file = open(av, O_RDONLY);
    char *buffer = (char*) malloc(sizeof(char) * (bloc.st_size));
    int byte = read(file,buffer,bloc.st_size);
    buffer[byte] = '\0';
    return buffer;
}

std::vector<std::string> splitString(const std::string &str, const std::string &separator) {
    std::vector<std::string> result;
    size_t start = 0, end;
    while ((end = str.find(separator, start)) != std::string::npos) {
        result.push_back(str.substr(start, end - start));
        start = end + separator.length();
    }
    result.push_back(str.substr(start));
    return result;
}

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
    pos.x += std::cos(red_col->angle) * radius;
    pos.y += std::sin(red_col->angle) * radius;

    sf::Vector2f pos_blue = sprite_ying_yang.getPosition();
    pos_blue.x += std::cos(blu_col->angle) * radius;
    pos_blue.y += std::sin(blu_col->angle) * radius;

    red_col->square.setPosition(pos);
    blu_col->square.setPosition(pos_blue);
}

int main(int ac, char **av)
{
    sf::Event event;
    sf::RenderWindow window(sf::VideoMode(4010, 4066), "SFML Simple Window");
    window.setFramerateLimit(100);
    sf::Sprite sprite_ying_yang;
    sf::Texture texture;
    sprite_ying_yang.setPosition(1430,1330);
    sprite_ying_yang.setScale(0.3,0.3);
    if (!texture.loadFromFile("yinyang.png")) {
        return 84;
    }
    sprite_ying_yang.setTexture(texture);

    ying_col_s red_col = init_shape(sf::Color::Red, 1.45);
    ying_col_s blu_col = init_shape(sf::Color::Blue, -1.45);
    const float radius = texture.getSize().y / 13.0f;
    float rayon = 8.0f;

    std::string file = buffer_maker("configuration_file.txt");
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

