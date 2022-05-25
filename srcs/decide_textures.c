/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decide_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpouchep <bpouchep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:10:34 by bpouchep          #+#    #+#             */
/*   Updated: 2022/05/25 16:10:35 by bpouchep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	face_north(t_game *g)
{
	if (g->side == 1)
	{
		if (g->raydir_y > 0)
			g->tex_num = WE;
		else
			g->tex_num = EA;
	}
	else
		g->tex_num = SO;
}

void	face_south(t_game *g)
{
	if (g->side == 1)
	{
		if (g->raydir_y > 0)
			g->tex_num = WE;
		else
			g->tex_num = EA;
	}
	else
		g->tex_num = NO;
}

void	face_west(t_game *g)
{
	if (g->side == 0)
	{
		if (g->raydir_x > 0)
			g->tex_num = NO;
		else
			g->tex_num = SO;
	}
	else
		g->tex_num = EA;
}

void	face_east(t_game *g)
{
	if (g->side == 0)
	{
		if (g->raydir_x > 0)
			g->tex_num = NO;
		else
			g->tex_num = SO;
	}
	else
		g->tex_num = WE;
}

void	decide_textures(t_game *g)
{
	g->tex_num = g->cub_list.map_matrix[g->ray_mapx][g->ray_mapy];
	if (g->tex_num == 1)
	{
		if (fabs(g->dir_x) >= fabs(g->dir_y) && g->dir_x <= 0)
			face_north(g);
		else if (fabs(g->dir_x) >= fabs(g->dir_y) && g->dir_x >= 0)
			face_south(g);
		else if (fabs(g->dir_y) >= fabs(g->dir_x) && g->dir_y <= 0)
			face_west(g);
		else if (fabs(g->dir_y) >= fabs(g->dir_x) && g->dir_y >= 0)
			face_east(g);
	}
}
