# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/27 16:18:45 by moabid            #+#    #+#              #
#    Updated: 2022/05/27 22:04:33 by moabid           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	fdf
NAME_BONUS	= 	fdf_bonus

FLAGS		=	-Wall -Wextra -g
CC			=	gcc
INCLUDES	= 	-I./include
LIBFT		= 	./libft/libft.a 
LINK_FLAGS	=  	-lmlx -lm -L$(LIBX) -framework OpenGL -framework AppKit
LIBX  		= 	./mlx
MINILIBX	=	./mlx/libmlx.a


SRCS_DIR	=	./src/
SRCS_FILES	=	main.c drawer.c init.c \
					parser.c colors.c keys.c \
					keys_setup.c project.c stack.c \
					utils.c utils2.c utils3.c
SRCS		= 	$(addprefix $(SRCS_DIR), $(SRCS_FILES))


OBJS	=	${SRCS:.c=.o}

%.o : %.c
	@gcc -g ${FLAGS} ${INCLUDES} -c $< -o $(<:.c=.o)

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS) 
	@echo "\033[33m----Compiling BONUS...----"
	@make -C ./libft --silent
	@$(CC) -o $(NAME) $(INCLUDES) $(OBJS) $(LIBFT) $(LINK_FLAGS) $(MINILIBX)
	@echo "\033[32mBONUS Compiled! ᕦ(\033[31m♥\033[32m_\033[31m♥\033[32m)ᕤ\n"

$(NAME): $(OBJS) 
	@echo "\033[33m----Compiling ...----"
	@make -C ./libft --silent
	@$(CC) -o $(NAME) $(INCLUDES) $(OBJS) $(LIBFT) $(LINK_FLAGS) $(MINILIBX)
	@echo "\033[32mFDF Compiled! ᕦ(\033[31m♥\033[32m_\033[31m♥\033[32m)ᕤ\n"

clean:
	@echo "\033[33m     Cleaning the garbage ..."
	@make clean -C ./libft --silent
	@rm -f $(OBJS)

fclean: clean
	@make fclean -C ./libft
	@rm -f $(NAME)
	@echo "\033[32mEverything is fcleaned! ✓ (\033[31m>_<\033[32m)\n"

re: fclean all

.PHONY: all clean fclean re
