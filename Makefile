# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/28 13:12:23 by louisnop          #+#    #+#              #
#    Updated: 2023/08/08 11:18:42 by corvvs           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		:= gcc
CFLAGS	:= -Wall -Wextra -Werror -Iincludes -fsanitize=address -g -D DEBUG
SRCDIR	:=	srcs
OBJDIR	:=	objs
INCDIR	:=	includes
FILES	:=	\
			main.c\
			bsq_run_session.c\
			bsq_map.c\
			bsq_read_file.c\
			bsq_validators_content.c\
			bsq_validators_lines.c\
			bsq_validators_map.c\
			bsq_get_maximum_square.c\
			bsq_split.c\
			capped_buffer.c\
			utils_misc.c\
			utils_put.c\
			utils_number.c\

SRCS	:=	$(FILES:%.c=$(SRCDIR)/%.c)
OBJS	:=	$(FILES:%.c=$(OBJDIR)/%.o)
TARGET	:= bsq

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

$(OBJDIR)/%.o:	$(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean re
clean:
	-rm -f $(OBJS)

fclean:
	-rm -f $(TARGET) $(OBJS)

re: fclean all
