/*
** EPITECH PROJECT, 2022
** chained list struct
** File description:
** make the struct
*/



#ifndef LINK_STRUCT
    #define LINK_STRUCT
        #include <stdarg.h>
        #include <string.h>
        #include <SFML/Graphics.hpp>
        typedef struct node_s {
            std::string name;
            float time;
            sf::Sprite sprite;
            sf::Texture texture;
            struct node_s *next;
        } node_t;
#endif
