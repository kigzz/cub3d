/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpouchep <bpouchep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:35:59 by bpouchep          #+#    #+#             */
/*   Updated: 2022/05/25 16:36:00 by bpouchep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	draw_img2(t_game *g, int x, int y)
{
	if (g->key_e_pressed == 1)
	{
		while (y < g->draw_end)
		{
			if (g->tex_num == NO)
				g->buf[y++][x] = 0x0000033;
			if (g->tex_num == SO)
				g->buf[y++][x] = 0x0003319;
			if (g->tex_num == WE)
				g->buf[y++][x] = 0x0660000;
			if (g->tex_num == EA)
				g->buf[y++][x] = 0x0404040;
		}
	}
	return (y);
}

void	draw_img(t_game *g, int x, int tex_x)
{
	int	tex_y;
	int	color;
	int	y;

	while (y < g->draw_start)
		g->buf[y++][x] = g->cub_list.ceiling_dec;
	y = draw_img2(g, x, y);
	while (y < g->draw_end)
	{
		tex_y = (int) g->tex_pos;
		g->tex_pos += g->step_tex;
		color = g->texture[g->tex_num][TEX_HEIGHT * tex_y + tex_x];
		g->buf[y++][x] = color;
	}
	while (y < g->cub_list.height)
		g->buf[y++][x] = g->cub_list.floor_dec;
}
