/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_spaces.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpouchep <bpouchep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 17:46:42 by bpouchep          #+#    #+#             */
/*   Updated: 2022/05/25 17:46:43 by bpouchep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	first_row_check(t_game *info, int i, int j)
{
	if (j == 0)
	{
		if (info->cub_list.map_matrix[i][j + 1] == 0
			|| info->cub_list.map_matrix[i + 1][j] == 0)
			error(info, "Map is wrong");
		return ;
	}
	else if (j == info->cub_list.map_x - 1)
	{
		if (info->cub_list.map_matrix[i][j - 1] == 0
			|| info->cub_list.map_matrix[i + 1][j] == 0)
			error(info, "Map is wrong");
		return ;
	}
	if (info->cub_list.map_matrix[i][j - 1] == 0
		|| info->cub_list.map_matrix[i + 1][j] == 0
		|| info->cub_list.map_matrix[i][j + 1] == 0)
		error(info, "Map is wrong");
}

void	last_row_check(t_game *info, int i, int j)
{
	if (j == 0)
	{
		if (info->cub_list.map_matrix[i][j + 1] == 0
			|| info->cub_list.map_matrix[i - 1][j] == 0)
			error(info, "Map is wrong");
		return ;
	}
	else if (j == info->cub_list.map_x - 1)
	{
		if (info->cub_list.map_matrix[i][j - 1] == 0
			|| info->cub_list.map_matrix[i - 1][j] == 0)
			error(info, "Map is wrong");
		return ;
	}
	if (info->cub_list.map_matrix[i][j - 1] == 0
		|| info->cub_list.map_matrix[i - 1][j] == 0
		|| info->cub_list.map_matrix[i][j + 1] == 0)
		error(info, "Map is wrong");
}

void	middle_row_check_other(t_game *info, int i, int j)
{
	if (info->cub_list.map_matrix[i][j - 1] == 0
		|| info->cub_list.map_matrix[i + 1][j] == 0
		|| info->cub_list.map_matrix[i][j + 1] == 0
		|| info->cub_list.map_matrix[i - 1][j] == 0)
		error(info, "Map is wrong");
}

void	middle_row_check(t_game *info, int i, int j)
{
	if (j == 0)
	{
		if (info->cub_list.map_matrix[i][j + 1] == 0
			|| info->cub_list.map_matrix[i + 1][j] == 0
			|| info->cub_list.map_matrix[i - 1][j] == 0)
			error(info, "Map is wrong");
	}
	else if (j == info->cub_list.map_x - 1)
	{
		if (info->cub_list.map_matrix[i][j - 1] == 0
			|| info->cub_list.map_matrix[i + 1][j] == 0
			|| info->cub_list.map_matrix[i - 1][j] == 0)
			error(info, "Map is wrong");
	}
	else
		middle_row_check_other(info, i, j);
}

void	check_map_spaces(t_game *g)
{
	int	i;
	int	j;

	i = 0;
	while (i < g->cub_list.map_y)
	{
		j = 0;
		while (j < g->cub_list.map_x)
		{
			if (g->cub_list.map_matrix[i][j] == 5)
			{
				if (i == 0)
					first_row_check(g, i, j);
				else if (i == g->cub_list.map_y - 1)
					last_row_check(g, i, j);
				else
					middle_row_check(g, i, j);
			}
			j++;
		}
		i++;
	}
}
