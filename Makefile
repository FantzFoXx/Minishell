# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: udelorme <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/14 11:43:18 by udelorme          #+#    #+#              #
#    Updated: 2016/03/22 15:59:24 by udelorme         ###   ########.fr        #
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
	    $(CC) -L $(LIBDIR) -lft $^ -o $@

$(OBJDIR)%.o: $(SRCDIR)%.c
	    @mkdir $(OBJDIR) 2> /dev/null || true
		    $(CC) $(FLAGS) -I $(INCDIR) -I $(LIBDIR)includes -o $@ -c $<

#$(NAME):
#	(cd $(LIBDIR); $(MAKE) all)
#	(cd $(SRCDIR);$(CC) $(FLAGS) -c $(SRC) -I ../$(INCDIR) -I ../$(LIBDIR)includes/;mv $(OBJ) ../obj)
#	(cd $(OBJDIR);$(CC) $(FLAGS) -o ../$(NAME) $(OBJ) -L ../$(LIBDIR) -lft)

clean:
	rm -rf $(OBJS)
	@rmdir $(OBJDIR) 2> /dev/null || true

fclean: clean
	rm -rf $(NAME)

re: fclean all

lftclean:
	(cd $(LIBDIR); $(MAKE) clean)

lftfclean:
	(cd $(LIBDIR); $(MAKE) fclean)

.PHONY: $(NAME) all clean fclean re
