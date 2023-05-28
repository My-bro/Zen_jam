/*
** EPITECH PROJECT, 2023
** color5.cpp
** File description:
** colorrr
*/

#include <SFML/Graphics.hpp>

sf::Color calculateGradientColor(float ratio, bool clockwise)
{
    sf::Uint8 colorValue = static_cast<sf::Uint8>(ratio * 255);
    if (clockwise) {
        return sf::Color(255 - colorValue, 255 - colorValue, 255 - colorValue);
    }
    else {
        return sf::Color(colorValue, colorValue, colorValue);
    }
}

void handleEvents(sf::RenderWindow& window, float& gradientRatio, bool& clockwise) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Left) {
                gradientRatio -= 0.1f;
                if (gradientRatio < 0.0f) {
                    gradientRatio = 0.0f;
                }
                clockwise = false;
            }
            else if (event.key.code == sf::Keyboard::Right) {
                gradientRatio += 0.1f;
                if (gradientRatio > 1.0f) {
                    gradientRatio = 1.0f;
                }
                clockwise = true;
            }
        }
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Changement de couleur de fond");
    window.setFramerateLimit(60);

    float gradientRatio = 0.0f;
    bool clockwise = true;

    while (window.isOpen()) {
        handleEvents(window, gradientRatio, clockwise);

        sf::Color currentColor = calculateGradientColor(gradientRatio, clockwise);

        window.clear(currentColor);
        window.display();
    }

    return 0;
}
