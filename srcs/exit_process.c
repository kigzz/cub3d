/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpouchep <bpouchep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:10:24 by bpouchep          #+#    #+#             */
/*   Updated: 2022/05/25 16:10:25 by bpouchep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	error(t_game *g, char *error)
{
	printf("Error\n");
	printf("%s\n", error);
	all_free(g);
	exit(1);
}

void	free_mlx(t_game *g)
{
	if (g->win)
		mlx_destroy_window(g->mlx, g->win);
	if (g->img.img)
		mlx_destroy_image(g->mlx, g->img.img);
	if (g->mlx)
	{
		mlx_destroy_display(g->mlx);
		free(g->mlx);
	}
}

void	all_free(t_game *g)
{
	if (g->cub_list.map_matrix)
		int_tab_free(g->cub_list.map_matrix, g->cub_list.map_y);
	if (g->cub_list.map)
		char_tab_free(g->cub_list.map);
	if (g->texture)
		int_tab_free(g->texture, 4);
	if (g->cub_list.n_texture)
		free(g->cub_list.n_texture);
	if (g->cub_list.s_texture)
		free(g->cub_list.s_texture);
	if (g->cub_list.e_texture)
		free(g->cub_list.e_texture);
	if (g->cub_list.w_texture)
		free(g->cub_list.w_texture);
	if (g->buf)
		int_tab_free(g->buf, g->cub_list.height);
	free_mlx(g);
	exit(0);
}

void	int_tab_free(int **array, int max)
{
	int	i;

	i = 0;
	while (i < max)
	{
		if (array[i])
		{
			free(array[i]);
			array[i] = NULL;
		}
		i++;
	}
	free(array);
	array = NULL;
}

void	char_tab_free(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (array[i])
		{
			free(array[i]);
			array[i] = NULL;
		}
		i++;
	}
	free(array);
	array = NULL;
}
