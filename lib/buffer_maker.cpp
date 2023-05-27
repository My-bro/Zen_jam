/*
** EPITECH PROJECT, 2023
** Zen_jam
** File description:
** buffer_maker
*/

#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>

char *buffer_maker(char *av)
{
    struct stat bloc;
    stat(av, &bloc);
    int file = open(av, O_RDONLY);
    char *buffer = (char*) malloc(sizeof(char) * (bloc.st_size));
    int byte = read(file,buffer,bloc.st_size);
    buffer[byte] = '\0';
    return buffer;
}
