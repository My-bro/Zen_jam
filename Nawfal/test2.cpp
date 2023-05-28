/*
** EPITECH PROJECT, 2023
** test2.cpp
** File description:
** action
*/

#include <SFML/Graphics.hpp>

void afficherFenetre()
{
    sf::RenderWindow fenetre(sf::VideoMode(800, 600), "Fenetre");
    
    sf::CircleShape cercleNoir(fenetre.getSize().x / 4);
    cercleNoir.setFillColor(sf::Color::Black);
    cercleNoir.setPosition(fenetre.getSize().x / 4 - cercleNoir.getRadius(), fenetre.getSize().y / 2 - cercleNoir.getRadius());
    
    sf::CircleShape cercleBlanc(fenetre.getSize().x / 4);
    cercleBlanc.setFillColor(sf::Color::White);
    cercleBlanc.setPosition(3 * fenetre.getSize().x / 4 - cercleBlanc.getRadius(), fenetre.getSize().y / 2 - cercleBlanc.getRadius());

    
    float rotationNoir = 0.0f;
    float rotationBlanc = 0.0f;

    while (fenetre.isOpen())
    {
        sf::Event evenement;
        while (fenetre.pollEvent(evenement))
        {
            if (evenement.type == sf::Event::Closed)
                fenetre.close();
        }
        rotationNoir += 0.01f;
        rotationBlanc -= 0.01f;
        cercleNoir.setRotation(rotationNoir);
        cercleBlanc.setRotation(rotationBlanc);

        fenetre.clear();
        fenetre.draw(cercleNoir);
        fenetre.draw(cercleBlanc);
        fenetre.display();
    }
}

int main()
{
    afficherFenetre();
    return 0;
}
