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
        node->texture.loadFromFile(line[4].c_str());
        node->sprite.setTexture(node->texture);
        node->sprite.setPosition(atoi(line[1].c_str()), atoi(line[2].c_str()));
        node->time = atoi(line[3].c_str());
        node->name = line[0];
        link_node(&head, &tail, &node);
        node = node->next;
    }
    return head;
}

void draw_sprite(node_t *head, sf::RenderWindow *window)
{
    while (head != nullptr) {
        window->draw(head->sprite);
        head = head->next;
    }
}
