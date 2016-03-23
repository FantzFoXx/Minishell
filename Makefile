# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: udelorme <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/14 11:43:18 by udelorme          #+#    #+#              #
#    Updated: 2016/03/23 10:32:20 by udelorme         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang
FLAGS = -Wall -Werror -Wextra
NAME = minishell
SRC = main.c catch_errors.c	handle_command.c	\
	  builtin_commands.c handle_signal.c		\
	  builtin_commands_2.c builtin_env.c		\
	  builtin_env_2.c

OBJ = $(SRC:.c=.o)

SRCDIR = src/
OBJDIR = obj/
INCDIR = includes/
LIBDIR = libft/

SRCS = $(addprefix $(SRCDIR),$(SRC))
OBJS = $(addprefix $(OBJDIR),$(OBJ))

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBDIR)
	$(CC) -L $(LIBDIR) -lft $^ -o $@

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir $(OBJDIR) 2> /dev/null || true
	$(CC) $(FLAGS) -I $(INCDIR) -I $(LIBDIR)includes -o $@ -c $<

clean:
	rm -rf $(OBJS)
	@rmdir $(OBJDIR) 2> /dev/null || true

fclean: clean
	rm -rf $(NAME)

re: fclean all

lftclean:
	$(MAKE) -C $(LIBDIR) clean

lftfclean:
	$(MAKE) -C $(LIBDIR) fclean

.PHONY: all clean fclean re
