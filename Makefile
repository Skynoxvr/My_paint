##
## EPITECH PROJECT, 2023
## makefile
## File description:
## ...
##

NAME	=	my_paint

CFLAGS	=	-Wall -Wextra -W -g3

LDFLAGS	=	-lcsfml-graphics -lcsfml-system -lcsfml-window -lX11 -lm

SRCS    :=      $(shell find -name "*.c")

OBJS	=	$(SRCS:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
