# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/30 18:16:42 by ufalzone          #+#    #+#              #
#    Updated: 2024/12/08 19:25:06 by ufalzone         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Couleurs
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
CYAN = \033[36m
RESET = \033[0m

# Nom de l'exécutable final
NAME = fdf

# Répertoires
SRC_DIR = srcs
LIBFT_DIR = libft
INCLUDE_DIR = includes
MLX_DIR = minilibx-linux

# Fichiers sources et objets
SRC_FILES = srcs/bresenham.c \
			srcs/draw.c \
			srcs/parsing.c \
			srcs/utils.c \
			srcs/color.c \
			srcs/keyboard_input.c \
			srcs/rotate.c \
			srcs/display_controls.c \
			srcs/mouse_input.c \
			srcs/parsing2.c \
			srcs/main.c
			
OBJ_FILES = $(SRC_FILES:.c=.o)

# Flags de compilation
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INCLUDE_DIR) -I$(MLX_DIR) -g -O3
LDFLAGS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# Librairie libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx.a

# Flags pour la MiniLibX
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# Règles
.PHONY: all clean fclean re libft_clean libft_fclean mlx_clean mlx_fclean

# Compilation principale
all: $(LIBFT) $(MLX) $(NAME)
	@echo "$(YELLOW)✨ Tout est à jour !$(RESET)"

# Compile la libft
$(LIBFT):
	@echo "$(BLUE)🔨 Compilation de la libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)

# Compile le projet fdf
$(NAME): $(OBJ_FILES) $(MLX)
	@printf "\r$(GREEN)🚀 Compilation de $(NAME)...                                           $(RESET)"
	@$(CC) $(OBJ_FILES) $(CFLAGS) $(MLX_FLAGS) -L$(LIBFT_DIR) -lft -o $(NAME)
	@echo "\n$(YELLOW)🚀 Compilation fini ! $(GREEN)$(NAME) $(YELLOW)est prêt !$(RESET)"

# Compile les fichiers objets
%.o: %.c
	@printf "\r$(CYAN)📝 Compilation de $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des fichiers objets
clean: libft_clean
	@echo "$(YELLOW)🧹 Nettoyage des fichiers objets...$(RESET)"
	@rm -f $(OBJ_FILES)

# Nettoyage complet
fclean: clean libft_fclean
	@echo "$(RED)🗑️  Suppression de $(NAME)...$(RESET)"
	@rm -f $(NAME)

# Recompile tout
re: fclean all

# Nettoyage spécifique à la libft
libft_clean:
	@$(MAKE) -C $(LIBFT_DIR) clean

libft_fclean:
	@$(MAKE) -C $(LIBFT_DIR) fclean

# Nettoyage spécifique à la MiniLibX
mlx_clean:
	@$(MAKE) -C $(MLX_DIR) clean

mlx_fclean:
	@$(MAKE) -C $(MLX_DIR) fclean

# Add MLX compilation
$(MLX):
	@echo "$(BLUE)🔨 Compilation de la MiniLibX...$(RESET)"
	@$(MAKE) -C $(MLX_DIR)
