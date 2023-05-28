## EPITECH PROJECT, 2022
## BSQ Project
## File description:
## Makefile

SRC = 	lib/lib_colision/colision_shape.cpp\
		lib/splite_string.cpp\
		lib/buffer_maker.cpp\
		lib/config_file.cpp\
		lib/link_node.cpp\
		main.cpp

OBJ = $(SRC:.cpp=.o)

NAME = prog

CXX = g++

CPPFLAGS        =       -iquote includes

LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lm

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(OBJ) $(LDFLAGS) -o $(NAME)

clean:
	rm -f $(OBJ) *~

fclean: clean
	rm -f $(NAME)

re: fclean all
