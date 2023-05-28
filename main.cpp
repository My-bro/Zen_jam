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

ying_col_s init_shape(sf::Color pubgmobil, float angle);
void modify_angle(sf::Event event , sf::Sprite *sprite_ying_yang, float rayon, ying_col_s *red_col, ying_col_s *blu_col);
void actualise_values(sf::Sprite sprite_ying_yang , float radius, ying_col_s *red_col, ying_col_s *blu_col);
node_t *init_config_file(char *path);
void draw_sprite(node_t *head, sf::RenderWindow *window, float time);
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>

/*struct ying_col_s {
    sf::RectangleShape square;
    float angle;
};*/

char* buffer_maker(char* av);
std::vector<std::string> splitString(const std::string& str, const std::string& separator);
/*
ying_col_s init_shape(sf::Color pubgmobil, float angle);
void modify_angle(sf::Event event, sf::Sprite* sprite_ying_yang, float rayon, ying_col_s* red_col, ying_col_s* blu_col);
void actualise_values(sf::Sprite sprite_ying_yang, float radius, ying_col_s* red_col, ying_col_s* blu_col);
node_t* init_config_file(const char* path);
void draw_sprite(node_t* head, sf::RenderWindow* window, float time);*/

int main(int ac, char** av)
{
    sf::Event event;
    sf::RenderWindow window(sf::VideoMode(4010, 4066), "SFML Simple Window");
    window.setFramerateLimit(100);
    sf::Sprite sprite_ying_yang;
    sf::Texture texture;
    sprite_ying_yang.setScale(0.3, 0.3);
    if (!texture.loadFromFile("./src/yinyang.png")) {
        return 84;
    }
    sprite_ying_yang.setTexture(texture);

    ying_col_s red_col = init_shape(sf::Color::Red, 1.45);
    ying_col_s blu_col = init_shape(sf::Color::Blue, -1.45);
    const float radius = texture.getSize().y / 13.0f;
    float rayon = 8.0f;

    node_t* head = init_config_file("./src/configuration_file.txt");

    sf::Font font;
    if (!font.loadFromFile("./src/font.ttf")) {
        return 84;
    }

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);

    sf::Clock clock;

    sf::Texture speechTexture;
    sf::Sprite speechSprite;
    sf::Text speechText;

    std::ifstream speechConfig("./armod/config.txt");
    std::vector<std::string> speechMessages;

    if (!speechTexture.loadFromFile("./armod/image.png")) {
        std::cout << "Failed to load speech image" << std::endl;
        return -1;
    }

    if (!speechConfig) {
        std::cout << "Failed to load speech configuration file" << std::endl;
        return -1;
    }

    std::string line;
    while (std::getline(speechConfig, line)) {
        speechMessages.push_back(line);
    }

    speechConfig.close();

    speechSprite.setTexture(speechTexture);
    sf::FloatRect spriteBounds = speechSprite.getLocalBounds();
    speechSprite.setOrigin(spriteBounds.width / 2, spriteBounds.height / 2);
    speechSprite.setPosition(window.getSize().x / 2, window.getSize().y / 2);

    speechText.setFont(font);
    speechText.setCharacterSize(24);
    speechText.setFillColor(sf::Color::White);
    speechText.setPosition(window.getSize().x / 2 - spriteBounds.width / 2, window.getSize().y / 2 + spriteBounds.height / 2);

    int currentSpeechIndex = 0;
    bool isSpeechActive = false;
    bool isSpacePressed = false;

    while (window.isOpen()) {
        window.clear(sf::Color::White);
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space && !isSpeechActive && !isSpacePressed) {
                    isSpeechActive = true;
                    isSpacePressed = true;
                    if (currentSpeechIndex < speechMessages.size()) {
                        speechText.setString(speechMessages[currentSpeechIndex]);
                        currentSpeechIndex++;
                    }
                    else {
                        isSpeechActive = false;
                    }
                }
                else {
                    modify_angle(event, &sprite_ying_yang, rayon, &red_col, &blu_col);
                }
            }
            else if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Space) {
                    isSpacePressed = false;
                }
            }
        }

        actualise_values(sprite_ying_yang, radius, &red_col, &blu_col);

        spriteBounds = sprite_ying_yang.getLocalBounds();
        sprite_ying_yang.setOrigin(spriteBounds.width / 2, spriteBounds.height / 2);
        sprite_ying_yang.setPosition(1430, 1330);

        window.draw(sprite_ying_yang);
        window.draw(red_col.square);
        window.draw(blu_col.square);
        sf::Time elapsed = clock.getElapsedTime();
        text.setString("Seconds: " + std::to_string(elapsed.asSeconds()));
        draw_sprite(head, &window, elapsed.asSeconds());

        if (isSpeechActive) {
            window.draw(speechSprite);
            window.draw(speechText);
        }

        window.draw(text);
        window.display();
    }

    return 0;
}
