/*
** EPITECH PROJECT, 2023
** test.cpp
** File description:
** test wowo
*/

#include <SFML/Graphics.hpp>

void afficherFenetre()
{
    sf::RenderWindow fenetre(sf::VideoMode(800, 600), "Fenetre");

    sf::RectangleShape rectangleNoir(sf::Vector2f(fenetre.getSize().x / 2, fenetre.getSize().y));
    rectangleNoir.setFillColor(sf::Color::Black);

    sf::RectangleShape rectangleBlanc(sf::Vector2f(fenetre.getSize().x / 2, fenetre.getSize().y));
    rectangleBlanc.setFillColor(sf::Color::White);
    rectangleBlanc.setPosition(sf::Vector2f(fenetre.getSize().x / 2, 0));

    while (fenetre.isOpen())
    {
        sf::Event evenement;
        while (fenetre.pollEvent(evenement))
        {
            if (evenement.type == sf::Event::Closed)
                fenetre.close();
        }
        fenetre.clear();
        fenetre.draw(rectangleNoir);
        fenetre.draw(rectangleBlanc);
        fenetre.display();
    }
}

int main()
{
    afficherFenetre();
    return 0;
}
