
#SETUP

NAME			=	cub3D
CC				=	gcc
FLAGS			=	-Wall -Werror -Wextra -Iincludes -Ilibft -Iminilibx-linux -O3 -g3 #-fsanitize=address

RM				=	rm -rf

#LIB NAMES

LIBFT_NAME		=	libft.a
LIBFT_DIR		=	libft

MLX_NAME		=	libmlx_linux.a
MLX_DIR			=	minilibx-linux

#LIB FLAGS

MLX				=	minilibx-linux
MLX_LINUX_FLAGS	=	-Lminilibx-linux -lmlx -lXext -lX11
LIBFT_FLAGS		=	-Llibft -lft


#FILES AND PATH

SRCS    		=	main.c init_game.c build_map.c exit_process.c init_process.c player.c draw.c draw2.c	\
					key_status.c decide_textures.c load_textures.c utils.c check_map_spaces.c check_rgb.c	\
					check_map_edges.c check_map.c check_map2.c
SRCS_DIR		=	srcs/
SRCS_PATH		=	$(addprefix $(SRCS_DIR), $(SRCS))
OBJ_SRCS    	=	$(SRCS_PATH:%.c=%.o)

# RULES

%.o : %.c
					$(CC) $(FLAGS) -c $< -o $@

all:				$(NAME)

$(NAME):			$(OBJ_SRCS)
					@make -C $(LIBFT_DIR)
					@make -C $(MLX_DIR)
					@$(CC) $(FLAGS) $(OBJ_SRCS) $(LIBFT_FLAGS) $(MLX_LINUX_FLAGS) -lm -o $(NAME)

clean:
					@$(RM) $(OBJ_SRCS)
					@$(RM) $(OBJ_SRCS_BONUS)
					@make clean -C $(LIBFT_DIR)
					@make clean -C $(MLX)

fclean:				clean
					@$(RM) $(NAME) $(NAME_BONUS)
					@make fclean -C libft

re:					fclean all

.PHONY:				all clean fclean bonus re