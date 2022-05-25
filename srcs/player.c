/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpouchep <bpouchep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:08:00 by bpouchep          #+#    #+#             */
/*   Updated: 2022/05/25 16:08:01 by bpouchep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	key_ws(t_game *g, double s)
{
	if (g->key_w_pressed)
	{
		if (!g->cub_list.map_matrix[(int)(g->pos_x + g->dir_x * s)]
		[(int)(g->pos_y)])
			g->pos_x += g->dir_x * g->movespeed;
		if (!g->cub_list.map_matrix[(int)(g->pos_x)]
		[(int)(g->pos_y + g->dir_y * s)])
			g->pos_y += g->dir_y * g->movespeed;
	}
	if (g->key_s_pressed)
	{
		if (!g->cub_list.map_matrix[(int)(g->pos_x - g->dir_x * s)]
		[(int)(g->pos_y)])
			g->pos_x -= g->dir_x * g->movespeed;
		if (!g->cub_list.map_matrix[(int)(g->pos_x)]
		[(int)(g->pos_y - g->dir_y * s)])
			g->pos_y -= g->dir_y * g->movespeed;
	}
}

void	key_da(t_game *g, double s)
{
	if (g->key_d_pressed)
	{
		if (!g->cub_list.map_matrix[(int)(g->pos_x + g->plane_x * s)]
		[(int)(g->pos_y)])
			g->pos_x += g->plane_x * g->movespeed;
		if (!g->cub_list.map_matrix[(int)(g->pos_x)]
		[(int)(g->pos_y + g->plane_y * s)])
			g->pos_y += g->plane_y * g->movespeed;
	}
	if (g->key_a_pressed)
	{
		if (!g->cub_list.map_matrix[(int)(g->pos_x - g->plane_x * s)]
		[(int)(g->pos_y)])
			g->pos_x -= g->plane_x * g->movespeed;
		if (!g->cub_list.map_matrix[(int)(g->pos_x)]
		[(int)(g->pos_y - g->plane_y * s)])
			g->pos_y -= g->plane_y * g->movespeed;
	}
}

void	key_right(t_game *g)
{
	double	old_dirx;
	double	old_planex;

	if (g->key_right_pressed)
	{
		old_dirx = g->dir_x;
		g->dir_x = g->dir_x * cos(-g->rotspeed) - g->dir_y
			* sin(-g->rotspeed);
		g->dir_y = old_dirx * sin(-g->rotspeed) + g->dir_y
			* cos(-g->rotspeed);
		old_planex = g->plane_x;
		g->plane_x = g->plane_x * cos(-g->rotspeed) - g->plane_y
			* sin(-g->rotspeed);
		g->plane_y = old_planex * sin(-g->rotspeed) + g->plane_y
			* cos(-g->rotspeed);
	}
}

void	key_left(t_game *g)
{
	double	old_dirx;
	double	old_planex;

	if (g->key_left_pressed)
	{
		old_dirx = g->dir_x;
		g->dir_x = g->dir_x * cos(g->rotspeed)
			- g->dir_y * sin(g->rotspeed);
		g->dir_y = old_dirx * sin(g->rotspeed)
			+ g->dir_y * cos(g->rotspeed);
		old_planex = g->plane_x;
		g->plane_x = g->plane_x * cos(g->rotspeed)
			- g->plane_y * sin(g->rotspeed);
		g->plane_y = old_planex * sin(g->rotspeed)
			+ g->plane_y * cos(g->rotspeed);
	}
}

int	key_press(t_game *g)
{
	double	scaling_col;

	scaling_col = 0.3;
	if ((g->key_w_pressed && g->key_a_pressed)
		|| (g->key_w_pressed && g->key_d_pressed)
		|| (g->key_s_pressed && g->key_a_pressed)
		|| (g->key_s_pressed && g->key_d_pressed)
		|| (g->key_left_pressed && g->key_right_pressed))
		g->movespeed = 0.05;
	else
		g->movespeed = 0.1;
	key_ws(g, scaling_col);
	key_da(g, scaling_col);
	key_right(g);
	key_left(g);
	return (0);
}
