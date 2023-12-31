# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/27 17:14:20 by pnamnil           #+#    #+#              #
#    Updated: 2023/11/15 08:38:53 by pnamnil          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

MINILIBX_PATH = mlx
LIBFT_PATH = libft
INCLUDES = $(LIBFT_PATH)/includes

CC = cc
CFLAGS = -Wall -Werror -Wextra
FRAMEWORK = -framework OpenGL -framework AppKit
LINK_LIB = -L$(MINILIBX_PATH) -lmlx -L$(LIBFT_PATH) -lft

SRCS = $(addprefix src/, fdf.c fdf_read_file.c fdf_add_data.c fdf_utils.c\
		fdf_draw_image.c fdf_bresenham.c fdf_gradient.c fdf_free.c\
		fdf_key_hook.c fdf_control.c debug.c)

OBJS = $(SRCS:%.c=%.o)

# FILE_TEST = resource/test_maps/mars.fdf
# FILE_TEST = resource/test_maps/pyramide.fdf
# FILE_TEST = resource/test_maps/42.fdf
# FILE_TEST = empty_file
# FILE_TEST = resource/test_maps/t1.fdf

%.o: %.c
	$(CC) $(CFLAGS) -I$(MINILIBX_PATH) -I$(INCLUDES) -c $< -o $@

all: $(NAME)

# l:
# 	leaks --atExit -- ./$(NAME) $(FILE_TEST)

$(NAME): $(OBJS)
	$(MAKE) -C $(MINILIBX_PATH)
	$(MAKE) -C $(LIBFT_PATH)
	$(CC) $(CFLAGS) $(OBJS) $(LINK_LIB) $(FRAMEWORK) -o $(NAME)

clean:
	rm -f src/*.o
	$(MAKE) -C $(MINILIBX_PATH) clean
	$(MAKE) -C $(LIBFT_PATH) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT_PATH)/libft.a

re:	fclean all

.PHONY: all clean fcrean re
