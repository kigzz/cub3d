/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpouchep <bpouchep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 14:31:14 by bpouchep          #+#    #+#             */
/*   Updated: 2022/05/25 14:31:15 by bpouchep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"

# define K_W 119
# define K_S 115
# define K_D 100
# define K_A 97
# define K_E 101
# define K_ESC 65307
# define K_RIGHT 65363
# define K_LEFT 65361
# define NO 0
# define SO 1
# define WE 2
# define EA 3
# define TEX_HEIGHT 64
# define TEX_WIDTH 64

typedef struct s_img
{
	void	*img;
	int		*data;
	int		size_l;
	int		bpp;
	int		endian;
	int		width;
	int		height;
}				t_img;

typedef struct s_rgb
{
	int	t;
	int	red;
	int	green;
	int	blue;
}				t_rgb;

typedef struct s_cub
{
	int			width;
	int			height;
	int			**map_matrix;
	int			map_x;
	int			map_y;
	int			floor_dec;
	int			ceiling_dec;
	int			init_pos_count;
	int			line_num;
	int			f_nowall_row;
	int			l_nowall_row;
	int			f_nowall_col;
	int			l_nowall_col;
	int			n_count;
	int			s_count;
	int			e_count;
	int			w_count;
	int			f_count;
	int			c_count;
	int			fd;
	char		*n_texture;
	char		*s_texture;
	char		*w_texture;
	char		*e_texture;
	char		**map;
	t_rgb		floor;
	t_rgb		ceil;
}				t_cub;

typedef struct s_game
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	movespeed;
	double	rotspeed;
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	wall_dist;
	double	tex_pos;
	double	wall_x;
	double	step_tex;
	int		**buf;
	int		**texture;
	void	*mlx;
	void	*win;
	int		step_x;
	int		step_y;
	int		side;
	int		hit;
	int		line_h;
	int		ray_mapx;
	int		ray_mapy;
	int		tex_num;
	int		draw_start;
	int		draw_end;
	int		key_w_pressed;
	int		key_s_pressed;
	int		key_a_pressed;
	int		key_d_pressed;
	int		key_e_pressed;
	int		key_left_pressed;
	int		key_right_pressed;
	t_img	img;
	t_cub	cub_list;
}				t_game;

int		key_press(t_game *g);
void	raycast(t_game *g);
void	build_map(char *line, int count, t_game *g);
int		init(t_game *g);
void	buf_init(t_game *g, int i, int j);
void	texture_init(t_game *g, int i, int j);
void	load_textures(t_game *g);
void	char_tab_free(char **array);
void	error(t_game *g, char *error);
void	argv_check(int argc, char **argv, char **envp, t_game *g);
void	map_edge_check(t_game *g, int *i);
void	map_wall_check(t_game *g);
void	check_map_spaces(t_game *g);
void	map_line_check(t_game *g, char **line_split, char *line);
int		floor_check(t_game *g, char **l_split, char **rgb_split, char *line);
int		ceiling_check(t_game *g, char **l_split, char **rgb_split, char *line);
int		map_ns_check(t_game *g, char **l_split, char *line);
int		map_we_check(t_game *g, char **l_split, char *line);
void	map_wrong_process(t_game *g, char **l_split, char *line);
void	check_rgb(t_game *g, char **rgb_split, char *line);
void	check_rgb2(t_game *g, char *line);
void	decide_textures(t_game *g);
void	draw_img(t_game *g, int x, int tex_x);
int		win_close(t_game *g);
void	int_tab_free(int **array, int max);
void	game_init(t_game *g);
void	all_free(t_game *g);
void	insert_null(t_game *g);
int		keydown(int k, t_game *g);
int		keyup(int k, t_game *g);
void	check_key_status(t_game *g);
int		size_array_char(char **str);
int		create_trgb(t_rgb c);

#endif
