/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpouchep <bpouchep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:08:26 by bpouchep          #+#    #+#             */
/*   Updated: 2022/05/25 16:08:26 by bpouchep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	game_init(t_game *g)
{
	int	sizex;
	int	sizey;

	g->cub_list.n_count = 0;
	g->cub_list.s_count = 0;
	g->cub_list.e_count = 0;
	g->cub_list.w_count = 0;
	g->cub_list.f_count = 0;
	g->cub_list.c_count = 0;
	g->cub_list.map_x = 0;
	g->cub_list.map_y = 0;
	g->cub_list.init_pos_count = 0;
	g->cub_list.line_num = 0;
	g->mlx = mlx_init();
	mlx_get_screen_size(g->mlx, &sizex, &sizey);
	g->cub_list.width = sizex;
	g->cub_list.height = sizey;
	g->key_left_pressed = 0;
	g->key_right_pressed = 0;
	g->key_w_pressed = 0;
	g->key_s_pressed = 0;
	g->key_a_pressed = 0;
	g->key_d_pressed = 0;
	g->key_e_pressed = 0;
	g->rotspeed = 0.05;
}

void	buf_init(t_game *g, int i, int j)
{
	while (i < g->cub_list.height)
	{
		g->buf[i] = (int *)malloc(sizeof(int) * (g->cub_list.width));
		if (g->buf[i] == NULL)
			error(g, "Malloc failed");
		i++;
	}
	i = 0;
	while (i < g->cub_list.height)
	{
		j = 0;
		while (j < g->cub_list.width)
		{
			g->buf[i][j] = 0;
			j++;
		}
		i++;
	}
}

void	texture_init(t_game *g, int i, int j)
{
	while (i < 4)
	{
		g->texture[i] = (int *)malloc(sizeof(int) * (TEX_HEIGHT * TEX_WIDTH));
		if (g->texture[i] == NULL)
			error(g, "Malloc failed");
		i++;
	}
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < TEX_HEIGHT * TEX_WIDTH)
		{
			g->texture[i][j] = 0;
			j++;
		}
		i++;
	}
}

void	argv_check(int argc, char **argv, char **envp, t_game *g)
{
	int	i;

	if (argc != 2)
		error(g, "The number of arguments is wrong");
	if (!*envp)
		error(g, "Compilation without envp");
	i = ft_strlen(argv[1]);
	if (i < 5)
		error(g, "Map file is wrong");
	if (ft_strcmp(&argv[1][i - 4], ".cub") != 0)
		error(g, "Not a cub file");
}

void	insert_null(t_game *g)
{
	g->buf = NULL;
	g->texture = NULL;
	g->cub_list.map_matrix = NULL;
	g->cub_list.map = NULL;
	g->cub_list.n_texture = NULL;
	g->cub_list.s_texture = NULL;
	g->cub_list.e_texture = NULL;
	g->cub_list.w_texture = NULL;
	g->win = NULL;
	g->img.img = NULL;
	g->mlx = NULL;
}
