/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpouchep <bpouchep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:08:38 by bpouchep          #+#    #+#             */
/*   Updated: 2022/05/25 16:08:40 by bpouchep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_dir_plane(t_game *g, double x, double y, int type)
{
	g->dir_x = 0.0;
	g->dir_y = 0.0;
	g->plane_x = 0.0;
	g->plane_y = 0.0;
	if (type == 0)
	{
		g->dir_x = x;
		g->plane_y = y;
	}
	else if (type == 1)
	{
		g->dir_x = x;
		g->plane_y = y;
	}
	else if (type == 2)
	{
		g->dir_y = x;
		g->plane_x = y;
	}
	else if (type == 3)
	{
		g->dir_y = x;
		g->plane_x = y;
	}
}

void	init_setting(t_game *g, int i, int j)
{
	if (g->cub_list.map[i][j] == 'N' || g->cub_list.map[i][j] == 'S' ||
		g->cub_list.map[i][j] == 'W' || g->cub_list.map[i][j] == 'E')
	{
		g->pos_x = (double)i + 0.5;
		g->pos_y = (double)j + 0.5;
		g->cub_list.init_pos_count++;
		g->cub_list.map_matrix[i][j] = 0;
	}
	if (g->cub_list.map[i][j] == 'N')
		init_dir_plane(g, -1.0, 0.66, 0);
	else if (g->cub_list.map[i][j] == 'S')
		init_dir_plane(g, 1.0, -0.66, 1);
	else if (g->cub_list.map[i][j] == 'W')
		init_dir_plane(g, -1.0, -0.66, 2);
	else if (g->cub_list.map[i][j] == 'E')
		init_dir_plane(g, 1.0, 0.66, 3);
	else if (g->cub_list.map[i][j] == ' ')
		g->cub_list.map_matrix[i][j] = 5;
	else
		g->cub_list.map_matrix[i][j] = g->cub_list.map[i][j] - '0';
}

void	map_malloc(t_game *g)
{
	int	i;

	g->cub_list.map_matrix = (int **)malloc(sizeof(int *)
			* (g->cub_list.map_y));
	if (g->cub_list.map_matrix == NULL)
		error(g, "Malloc failed");
	i = 0;
	while (i < g->cub_list.map_y)
	{
		g->cub_list.map_matrix[i] = (int *)malloc(sizeof(int)
				* (g->cub_list.map_x));
		if (g->cub_list.map_matrix[i] == NULL)
			error(g, "Malloc failed");
		i++;
	}
}

void	set_nowall_edge(t_game *g, int i, int j, int max)
{
	while (j < max)
	{
		init_setting(g, i, j);
		if (g->cub_list.map_matrix[i][j] == 0)
		{
			if (j < g->cub_list.f_nowall_row)
				g->cub_list.f_nowall_row = j;
			if (j > g->cub_list.l_nowall_row)
				g->cub_list.l_nowall_row = j;
		}
		j++;
	}
	if ((int)ft_strlen(g->cub_list.map[i]) < g->cub_list.map_x)
	{
		while (j < g->cub_list.map_x)
			g->cub_list.map_matrix[i][j++] = 5;
	}
}

int	init(t_game *g)
{
	int	i;
	int	j;

	map_malloc(g);
	i = 0;
	while (i < g->cub_list.map_y)
	{
		j = 0;
		g->cub_list.f_nowall_row = 2147483647;
		g->cub_list.l_nowall_row = -1;
		if ((int)ft_strlen(g->cub_list.map[i]) < g->cub_list.map_x)
			set_nowall_edge(g, i, j, ft_strlen(g->cub_list.map[i]));
		else
			set_nowall_edge(g, i, j, g->cub_list.map_x);
		map_edge_check(g, &i);
	}
	map_wall_check(g);
	map_space_check(g);
	if (g->cub_list.init_pos_count != 1)
		error(g, "Map is wrong");
	return (0);
}
