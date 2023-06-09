/*
** EPITECH PROJECT, 2023
** Epitech-Jam
** File description:
** init_portal_sprite
*/

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <cstring>
#include "node.h"
#include "ying_col.h"

std::vector<std::string> splitString(const std::string &str, const std::string &separator);
void link_node(node_t **head, node_t **tail, node_t **node);
char *buffer_maker(char *av);

node_t *init_config_file(char *path)
{
    node_t *head = nullptr;
    node_t *tail = nullptr;
    node_t *node = nullptr;
    std::string file = buffer_maker(path);
    std::vector<std::string> db = splitString(file,"\n");
    for (std::vector<std::string>::const_iterator it = db.begin(); it != db.end(); ++it) {
        std::vector<std::string> line = splitString(*it," ");
        node = new node_t;
        sf::Texture texture1;
        node->sprite.setScale(1, 1);
        node->sprite.setRotation(atof(line[4].c_str()));
        node->texture.loadFromFile(line[5].c_str());
        node->sprite.setTexture(node->texture);
        node->sprite.setPosition(atoi(line[1].c_str()), atoi(line[2].c_str()));
        node->time = atof(line[3].c_str());
        node->name = line[0];
        link_node(&head, &tail, &node);
        node = node->next;
    }
    return head;
}

void draw_sprite(node_t *head, sf::RenderWindow *window, float time)
{
    while (head != nullptr) {
        if (head->time < time) {
            window->draw(head->sprite);
            sf::Vector2f position = head->sprite.getPosition();
            head->sprite.setPosition(position.x, position.y + 1.2);
        }
        head = head->next;
    }
}

void check_colision(sf::Color red_pixelColor,  sf::Color blu_pixelColor, int *count_colision, float *protection, float time)
{
    if (time > *protection) {
        if (red_pixelColor.g != 255 || blu_pixelColor.g != 0) {
            *count_colision += 1;
            *protection = time + 1;
        }
    }
}
