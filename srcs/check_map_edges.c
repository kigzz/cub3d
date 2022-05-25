/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_edges.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpouchep <bpouchep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 17:47:45 by bpouchep          #+#    #+#             */
/*   Updated: 2022/05/25 17:47:46 by bpouchep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	map_edge_check(t_game *g, int *i)
{
	if (g->cub_list.l_nowall_row == -1)
	{
		(*i)++;
		return ;
	}
	else if (*i == 0 || *i == g->cub_list.map_y - 1)
		error(g, "Map is wrong");
	else
	{
		if (g->cub_list.f_nowall_row == 0
			|| g->cub_list.l_nowall_row == g->cub_list.map_x - 1)
			error(g, "Map is wrong");
		if (g->cub_list.l_nowall_row != -1
			&& (g->cub_list.map_matrix[*i][g->cub_list.f_nowall_row - 1] != 1
			|| g->cub_list.map_matrix[*i][g->cub_list.l_nowall_row + 1] != 1))
			error(g, "Map is wrong");
	}
	(*i)++;
}

void	col_edge_check(t_game *g, int *j)
{
	if (g->cub_list.l_nowall_col == -1)
	{
		(*j)++;
		return ;
	}
	if (*j == 0 || *j == g->cub_list.map_x - 1)
		error(g, "Map is wrong");
	else
	{
		if (g->cub_list.f_nowall_col == 0
			|| g->cub_list.l_nowall_col == g->cub_list.map_y - 1)
			error(g, "Map is wrong");
		if (g->cub_list.f_nowall_col != -1)
		{
			if (g->cub_list.map_matrix[g->cub_list.f_nowall_col - 1][*j] != 1
			|| g->cub_list.map_matrix[g->cub_list.l_nowall_col + 1][*j] != 1)
				error(g, "Map is wrong");
		}
	}
	(*j)++;
}

void	map_wall_check(t_game *g)
{
	int	i;
	int	j;

	j = 0;
	while (j < g->cub_list.map_x)
	{
		g->cub_list.f_nowall_col = 2147483647;
		g->cub_list.l_nowall_col = -1;
		i = 0;
		while (i < g->cub_list.map_y)
		{
			if (g->cub_list.map_matrix[i][j] == 0)
			{
				if (i < g->cub_list.f_nowall_col)
					g->cub_list.f_nowall_col = i;
				if (i > g->cub_list.l_nowall_col)
					g->cub_list.l_nowall_col = i;
			}
			i++;
		}
		col_edge_check(g, &j);
	}
}
