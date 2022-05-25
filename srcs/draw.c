/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpouchep <bpouchep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:10:29 by bpouchep          #+#    #+#             */
/*   Updated: 2022/05/25 16:10:30 by bpouchep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_wall_height(t_game *g)
{
	if (g->raydir_x < 0)
	{
		g->step_x = -1;
		g->sidedist_x = (g->pos_x - g->ray_mapx) * g->deltadist_x;
	}
	else
	{
		g->step_x = 1;
		g->sidedist_x = (g->ray_mapx + 1.0 - g->pos_x) * g->deltadist_x;
	}
	if (g->raydir_y < 0)
	{
		g->step_y = -1;
		g->sidedist_y = (g->pos_y - g->ray_mapy) * g->deltadist_y;
	}
	else
	{
		g->step_y = 1;
		g->sidedist_y = (g->ray_mapy + 1.0 - g->pos_y) * g->deltadist_y;
	}
}

void	get_wall_height(t_game *g)
{
	while (g->hit == 0)
	{
		if (g->sidedist_x < g->sidedist_y)
		{
			g->sidedist_x += g->deltadist_x;
			g->ray_mapx += g->step_x;
			g->side = 0;
		}
		else
		{
			g->sidedist_y += g->deltadist_y;
			g->ray_mapy += g->step_y;
			g->side = 1;
		}
		if (g->cub_list.map_matrix[g->ray_mapx][g->ray_mapy] > 0)
			g->hit = 1;
	}
	if (g->side == 0)
		g->wall_dist = g->sidedist_x - g->deltadist_x;
	else
		g->wall_dist = g->sidedist_y - g->deltadist_y;
	g->line_h = (int)(g->cub_list.height / g->wall_dist);
}

void	raycast2(t_game *g, int x)
{
	int	tex_x;

	init_wall_height(g);
	get_wall_height(g);
	g->draw_start = -g->line_h / 2 + g->cub_list.height / 2;
	if (g->draw_start < 0)
		g->draw_start = 0;
	g->draw_end = g->line_h / 2 + g->cub_list.height / 2;
	if (g->draw_end >= g->cub_list.height)
		g->draw_end = g->cub_list.height - 1;
	decide_textures(g);
	if (g->side == 0)
		g->wall_x = g->pos_y + g->wall_dist * g->raydir_y;
	else
		g->wall_x = g->pos_x + g->wall_dist * g->raydir_x;
	g->wall_x -= floor(g->wall_x);
	tex_x = (int)(g->wall_x * (double)TEX_WIDTH);
	if (g->side == 0 && g->raydir_x > 0)
		tex_x = TEX_WIDTH - tex_x - 1;
	if (g->side == 1 && g->raydir_y < 0)
		tex_x = TEX_WIDTH - tex_x - 1;
	g->step_tex = 1.0 * TEX_HEIGHT / g->line_h;
	g->tex_pos = (g->draw_start - g->cub_list.height * 0.5
			+ g->line_h * 0.5) * g->step_tex;
	draw_img(g, x, tex_x);
}

void	init_ray(t_game *g, int x)
{
	g->camera_x = 2 * x / (double)g->cub_list.width - 1;
	g->raydir_x = g->dir_x + g->plane_x * g->camera_x;
	g->raydir_y = g->dir_y + g->plane_y * g->camera_x;
	g->ray_mapx = (int)g->pos_x;
	g->ray_mapy = (int)g->pos_y;
	if (!g->raydir_x)
		g->raydir_x = 1e30;
	else
		g->deltadist_x = fabs(1 / g->raydir_x);
	if (!g->raydir_y)
		g->raydir_y = 1e30;
	else
		g->deltadist_y = fabs(1 / g->raydir_y);
	g->hit = 0;
}

void	raycast(t_game *g)
{
	int		x;

	x = 0;
	while (x < g->cub_list.width)
	{
		init_ray(g, x);
		raycast2(g, x);
		x++;
	}
}
