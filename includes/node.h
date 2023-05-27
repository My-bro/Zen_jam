/*
** EPITECH PROJECT, 2022
** chained list struct
** File description:
** make the struct
*/



#ifndef LINK_STRUCT
    #define LINK_STRUCT
        #include <stdarg.h>
        #include <SFML/Graphics.hpp>
        typedef struct node_s {
            sf::Sprite sprite_portal_a;
            sf::Sprite sprite_portal_b;
            sf::FloatRect bounds_portal_a;
            sf::FloatRect bounds_portal_b;
            sf::Vector2f coor_portal_a;
            sf::Vector2f coor_portal_b;
            struct node_s *next;
        } node_t;
#endif
