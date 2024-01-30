NAME = webserv
CC = c++
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror -std=c++98

INCLUDES = -I library/include
DIR_SOURCES = library/src
DIR_OBJS = obj

SOURCES := $(wildcard $(DIR_SOURCES)/*.cpp)
SOURCES += main.cpp

OBJS := $(patsubst $(DIR_SOURCES)/%.cpp,$(DIR_OBJS)/%.o,$(filter-out main.cpp,$(SOURCES)))
OBJS += $(DIR_OBJS)/main.o

all: $(NAME)

$(DIR_OBJS)/%.o: $(DIR_SOURCES)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(DIR_OBJS)/main.o: main.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME)

clean:
	$(RM) $(DIR_OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

val: all
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes --log-file="web_leaks.txt" ./$(NAME)

.PHONY: all clean fclean re val
