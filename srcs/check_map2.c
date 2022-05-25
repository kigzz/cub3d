/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpouchep <bpouchep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 17:47:09 by bpouchep          #+#    #+#             */
/*   Updated: 2022/05/25 17:47:10 by bpouchep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

char	**split_rgb(t_game *g, char **line_split, char **rgb_split, char *line)
{
	int	i;

	rgb_split = ft_split(line_split[1], ',');
	if (rgb_split == NULL)
		error(g, "ft_split failed");
	if (g->cub_list.line_num != 0 || size_array_char(line_split) > 2)
	{
		char_tab_free(rgb_split);
		map_wrong_process(g, line_split, line);
	}
	char_tab_free(line_split);
	i = 0;
	while (rgb_split[i])
		i++;
	if (i != 3)
	{
		char_tab_free(rgb_split);
		get_next_line(g->cub_list.fd, &line, -1);
		free(line);
		error(g, "Color is wrong");
	}
	return (rgb_split);
}

int	floor_check(t_game *g, char **l_split, char **rgb_split, char *line)
{
	int	i;

	i = ft_strcmp("F", l_split[0]);
	if (i == 0)
	{
		if (!l_split[1])
			map_wrong_process(g, l_split, line);
		rgb_split = split_rgb(g, l_split, rgb_split, line);
		check_rgb(g, rgb_split, line);
		g->cub_list.floor.red = ft_atoi(rgb_split[0]);
		g->cub_list.floor.green = ft_atoi(rgb_split[1]);
		g->cub_list.floor.blue = ft_atoi(rgb_split[2]);
		char_tab_free(rgb_split);
		check_rgb2(g, line);
		if (g->cub_list.f_count++ == 0)
			g->cub_list.floor_dec = create_trgb(g->cub_list.floor);
		return (1);
	}
	return (0);
}

int	ceiling_check(t_game *g, char **l_split, char **rgb_split, char *line)
{
	int	i;

	i = ft_strcmp("C", l_split[0]);
	if (i == 0)
	{
		if (!l_split[1])
			map_wrong_process(g, l_split, line);
		rgb_split = split_rgb(g, l_split, rgb_split, line);
		check_rgb(g, rgb_split, line);
		g->cub_list.ceil.red = ft_atoi(rgb_split[0]);
		g->cub_list.ceil.green = ft_atoi(rgb_split[1]);
		g->cub_list.ceil.blue = ft_atoi(rgb_split[2]);
		char_tab_free(rgb_split);
		check_rgb2(g, line);
		if (g->cub_list.c_count++ == 0)
			g->cub_list.ceiling_dec = create_trgb(g->cub_list.ceil);
		return (1);
	}
	return (0);
}
