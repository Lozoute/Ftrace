##
## Makefile for  in /home/sabbah_j/rendu/TEK2/B4-ADVANCED-PSU/AUSP_ftrace/symbole_finder
## 
## Made by jordan sabbah
## Login   <sabbah_j@epitech.net>
## 
## Started on  Sat Jul 11 22:05:29 2015 jordan sabbah
## Last update Sun Jul 12 19:20:09 2015 jordan sabbah
##

CC		= gcc

RM		= rm -f

CFLAGS		+= -Wextra -Wall -Werror
CFLAGS		+= -pedantic
CFLAGS		+= -I../include/

LDFLAGS		= -lelf

NAME		= a.out

SRC		= main.c \
		  symbol_finder.c

OBJS		= $(SRC:.c=.o)


all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
