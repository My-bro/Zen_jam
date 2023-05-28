/*
** EPITECH PROJECT, 2023
** color4
** File description:
** wowowo
*/

#include <SFML/Graphics.hpp>

sf::Color calculateGradientColor(float ratio) {
    sf::Uint8 colorValue = static_cast<sf::Uint8>(ratio * 255);
    return sf::Color(colorValue, colorValue, colorValue);
}

void handleEvents(sf::RenderWindow& window, float& gradientRatio) {
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
            }
            else if (event.key.code == sf::Keyboard::Right) {
                gradientRatio += 0.1f;
                if (gradientRatio > 1.0f) {
                    gradientRatio = 1.0f;
                }
            }
        }
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Changement de couleur de fond");
    window.setFramerateLimit(60);

    float gradientRatio = 0.0f;

    while (window.isOpen()) {
        handleEvents(window, gradientRatio);

        sf::Color currentColor = calculateGradientColor(gradientRatio);

        window.clear(currentColor);
        window.display();
    }

    return 0;
}
