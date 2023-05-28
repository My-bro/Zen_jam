#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Speech Screen");

    sf::Texture texture;
    if (!texture.loadFromFile("image.png"))
    {
        std::cout << "Failed to load image.jpg" << std::endl;
        return -1;
    }

    sf::Sprite sprite(texture);
    sprite.setPosition(100, 100);

    sf::Font font;
    if (!font.loadFromFile("font.ttf"))
    {
        std::cout << "Failed to load font.ttf" << std::endl;
        return -1;
    }

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(100, 500);

    std::ifstream configFile("config.txt");
    std::string line;
    std::vector<std::string> messages;

    while (std::getline(configFile, line))
    {
        messages.push_back(line);
    }

    configFile.close();

    int currentMessageIndex = 0;

    bool isSpeechScreenActive = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space)
                {
                    isSpeechScreenActive = true;

                    if (currentMessageIndex < messages.size())
                    {
                        text.setString(messages[currentMessageIndex]);
                        currentMessageIndex++;
                    }
                    else
                    {
                        isSpeechScreenActive = false;
                    }
                }
            }
        }

        window.clear();

        // Draw your game scene here

        if (isSpeechScreenActive)
        {
            window.draw(sprite);
            window.draw(text);
        }

        window.display();
    }

    return 0;
}
