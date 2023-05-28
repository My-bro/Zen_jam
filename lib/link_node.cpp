/*
** EPITECH PROJECT, 2023
** Zen_jam
** File description:
** link_node
*/

#include <SFML/Graphics.hpp>
#include "node.h"

void link_node(node_t **head, node_t **tail, node_t **node)
{
    if (*head == nullptr) {
        *head = *node;
        *tail = *node;
    } else {
        (*tail)->next = *node;
        *tail = *node;
        (*tail)->next = nullptr;
    }
}
