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
#include "node.h"

char *buffer_maker(char *av);
std::vector<std::string> splitString(const std::string &str, const std::string &separator);
char *buffer_maker(char *av);
std::vector<std::string> splitString(const std::string &str, const std::string &separator);

ying_col_s init_shape(sf::Color pubgmobil, float angle);
void modify_angle(sf::Event event , sf::Sprite *sprite_ying_yang, float rayon, ying_col_s *red_col, ying_col_s *blu_col);
void actualise_values(sf::Sprite sprite_ying_yang , float radius, ying_col_s *red_col, ying_col_s *blu_col);
node_t *init_config_file(char *path);
void draw_sprite(node_t *head, sf::RenderWindow *window, float time);
void check_colision(sf::Color red_pixelColor,  sf::Color blu_pixelColor, int *count_colision, float *protection, float time);

int main(int ac, char **av)
{
    sf::Event event;
    sf::RenderWindow window(sf::VideoMode(4010, 4066), "SFML Simple Window");
    window.setFramerateLimit(100);
    sf::Sprite sprite_ying_yang;
    sf::Texture texture;

    int count_colision = -1;
    float protection = 0;

    sprite_ying_yang.setPosition(1430,1330);
    sprite_ying_yang.setScale(0.3,0.3);
    texture.loadFromFile("./src/yinyang.png");
    sprite_ying_yang.setTexture(texture);

    ying_col_s red_col = init_shape(sf::Color::Red, 1.45);
    ying_col_s blu_col = init_shape(sf::Color::Blue, -1.45);
    const float radius = texture.getSize().y / 13.0f;
    float rayon = 8.0f;

    node_t *head = init_config_file("./src/configuration_file.txt");

    sf::Font font;
    font.loadFromFile("./src/font.ttf");

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    text.setPosition(50, 50);

    sf::Text text_colision;
    text_colision.setFont(font);
    text_colision.setCharacterSize(24);
    text_colision.setFillColor(sf::Color::Black);
    text_colision.setPosition(50, 150);

    sf::Clock clock;

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
        //window.draw(red_col.square);
        //window.draw(blu_col.square);

        sf::Time elapsed = clock.getElapsedTime();
        text.setString("Seconds: " + std::to_string(elapsed.asSeconds()));
        text_colision.setString("number touch : " +  std::to_string(count_colision));
        draw_sprite(head, &window, elapsed.asSeconds());
        window.draw(text_colision);
        window.draw(text);

        window.display();

        sf::Texture texture_img;
        texture_img.create(window.getSize().x, window.getSize().y);
        texture_img.update(window);
        sf::Image screenshot = texture_img.copyToImage();
        sf::Vector2f red_center(red_col.square.getPosition().x, red_col.square.getPosition().y);
        sf::Vector2f blu_center(blu_col.square.getPosition().x, blu_col.square.getPosition().y);
        sf::Color red_pixelColor = screenshot.getPixel(red_center.x, red_center.y);
        sf::Color blu_pixelColor = screenshot.getPixel(blu_center.x, blu_center.y);
        //check_colision((sf::Color)red_pixelColor, (sf::Color)blu_pixelColor, &count_colision);
        check_colision((sf::Color)red_pixelColor,  (sf::Color) blu_pixelColor,&count_colision, &protection, elapsed.asSeconds());


        printf("RED [ r : %hhu g : %hhu b :  %hhu]\n",red_pixelColor.r, red_pixelColor.g, red_pixelColor.b);
        printf("BLUE [ r : %hhu g : %hhu b :  %hhu]\n",blu_pixelColor.r, blu_pixelColor.g, blu_pixelColor.b);
    }
    return 0;
}