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

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
void processSpeechScreen(sf::RenderWindow& window, sf::Sprite& sprite_ying_yang, ying_col_s& red_col, ying_col_s& blu_col,
                         const sf::Texture& texture, const sf::Font& font, node_t* head)
{
    static bool isSpacePressed = false;
    static bool isSpeechActive = false;
    static unsigned int currentSpeechIndex = 0;

    std::ifstream configFile("armod/config.txt");
    std::vector<std::string> speechMessages;
    std::string line;
    while (std::getline(configFile, line)) {
        speechMessages.push_back(line);
    }

    configFile.close();

    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Space && !isSpeechActive && !isSpacePressed) {
                isSpeechActive = true;
                isSpacePressed = true;
                if (currentSpeechIndex < speechMessages.size()) {
                    sf::RenderWindow speechWindow(sf::VideoMode(800, 600), "Speech Window", sf::Style::None);

                    sf::Sprite speechSprite;
                    sf::Texture speechTexture;
                    if (!speechTexture.loadFromFile("armod/image.png")) {
                        // Handle image loading error
                    }
                    speechSprite.setTexture(speechTexture);
                    speechSprite.setScale(0.5f, 0.5f);
                    speechSprite.setPosition(speechWindow.getSize().x / 2 - speechSprite.getLocalBounds().width / 2,
                                             speechWindow.getSize().y / 2 - speechSprite.getLocalBounds().height / 2);

                    sf::Text speechText;
                    speechText.setFont(font);
                    speechText.setCharacterSize(30);
                    speechText.setFillColor(sf::Color::Black);
                    speechText.setString(speechMessages[currentSpeechIndex]);
                    speechText.setPosition(speechWindow.getSize().x / 2 - speechText.getLocalBounds().width / 2,
                                           speechSprite.getPosition().y + speechSprite.getLocalBounds().height + 20);

                    while (speechWindow.isOpen()) {
                        sf::Event speechEvent;
                        while (speechWindow.pollEvent(speechEvent)) {
                            if (speechEvent.type == sf::Event::Closed) {
                                speechWindow.close();
                            }
                            else if (speechEvent.type == sf::Event::KeyPressed) {
                                if (speechEvent.key.code == sf::Keyboard::Space) {
                                    speechWindow.close();
                                }
                            }
                        }

                        speechWindow.clear(sf::Color::White);
                        speechWindow.draw(speechSprite);
                        speechWindow.draw(speechText);
                        speechWindow.display();
                    }

                    currentSpeechIndex++;
                }
                else {
                    isSpeechActive = false;
                }
            }
        }
        else if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::Space) {
                isSpacePressed = false;
            }
        }
    }
}
