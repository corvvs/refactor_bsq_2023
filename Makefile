# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: louisnop <louisnop@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/28 13:12:23 by louisnop          #+#    #+#              #
#    Updated: 2020/01/30 06:37:02 by louisnop         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
TARGET = bsq
SRCS = main.c ft_puts.c ft_utility.c ft_strdup.c ft_strjoin.c ft_split.c ft_atoi.c ft_info.c ft_validate_map.c makesquare2.c helpmakesquare.c
OBJS = main.o ft_puts.o ft_utility.o ft_strdup.o ft_strjoin.o ft_split.o ft_atoi.o ft_info.o ft_validate_map.o makesquare2.o helpmakesquare.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.c%.o:
	$(CC) $(CFLAGS) -c $<

.PHONY: all clean re
clean:
	-rm -f $(OBJS)

fclean:
	-rm -f $(TARGET) $(OBJS)

re: fclean all
