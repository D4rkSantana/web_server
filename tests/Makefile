# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ryoshio- <ryoshio-@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/29 05:51:07 by ryoshio-          #+#    #+#              #
#    Updated: 2024/02/29 06:30:37 by ryoshio-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = test

CC = c++
RM = rm -rf
CFLAGS = -g -Wall -Wextra -Werror -std=c++98

INCLUDES = -I ../includes 
DIR_SOURCES = ../src
DIR_OBJS = build

DIR_TESTS = src
INCLUDES_TESTS = -I include
DIR_TEST_OBJS = build


# Listar todos os arquivos .cpp em src
TESTS := $(wildcard $(DIR_SOURCES)/*.cpp)
# Filtrar os arquivos .cpp exceto main.cpp
TESTS:= $(filter-out $(DIR_SOURCES)/main.cpp,$(TESTS))
TESTS += $(wildcard $(DIR_TESTS)/*.cpp)

TEST_OBJS := $(patsubst $(DIR_TESTS)/%.cpp,$(DIR_TEST_OBJS)/%.o,$(TESTS))

$(DIR_TEST_OBJS)/%.o: $(DIR_TESTS)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) $(INCLUDES_TESTS) -c $< -o $@


all: $(TEST_OBJS) 
	$(CC) $(CFLAGS) $(INCLUDES) $(INCLUDES_TESTS) $^ -o $(NAME)

clean:
	$(RM)  $(DIR_TEST_OBJS) 

fclean: clean
	$(RM) $(NAME) 

re: fclean all

val: all
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes --log-file="web_leaks.txt" ./$(NAME)

.PHONY: all clean fclean re val
