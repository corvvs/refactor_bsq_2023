# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/28 13:12:23 by louisnop          #+#    #+#              #
#    Updated: 2023/08/08 19:20:01 by corvvs           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		:=	cc
CFLAGS	:=	-Wall -Wextra -Werror -Iincludes\
			-g -fsanitize=address -fsanitize=undefined\
			-D DEBUG\

SRCDIR	:=	srcs
OBJDIR	:=	objs
INCDIR	:=	includes

FILES	:=	main.c\
			bsq_run_session.c\
			bsq_map.c\
			bsq_read_file.c\
			bsq_validators_content.c\
			bsq_validators_lines.c\
			bsq_validators_map.c\
			bsq_get_maximum_square.c\
			bsq_split.c\
			utils_number.c\
			utils_put.c\
			utils_misc.c\
			elastic_buffer.c\

SRCS	:=	$(FILES:%.c=$(SRCDIR)/%.c)
OBJS	:=	$(FILES:%.c=$(OBJDIR)/%.o)

NAME	:=	bsq


all:		$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

$(OBJDIR)/%.o:	$(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY:		all clean re
clean:
	-rm -f $(OBJS)

fclean:		clean
	-rm -f $(TARGET)

re:			fclean all

.PHONY:	up
up:
	docker-compose up --build -d

.PHONY:	down
down:
	docker-compose down

.PHONY:	it
it:
	docker-compose exec app bash
