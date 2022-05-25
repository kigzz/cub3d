/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpouchep <bpouchep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:10:39 by bpouchep          #+#    #+#             */
/*   Updated: 2022/05/25 16:10:40 by bpouchep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	map_wrong_process(t_game *g, char **l_split, char *line)
{
	char_tab_free(l_split);
	get_next_line(g->cub_list.fd, &line, -1);
	free(line);
	error(g, "Map is wrong");
}

void	map_line_check(t_game *g, char **line_split, char *line)
{
	int	i;
	int	j;

	if (g->cub_list.n_count != 1 || g->cub_list.s_count != 1
		|| g->cub_list.e_count != 1 || g->cub_list.w_count != 1
		|| g->cub_list.f_count != 1 || g->cub_list.c_count != 1)
		map_wrong_process(g, line_split, line);
	i = 0;
	while (line_split[i])
	{
		j = 0;
		while (line_split[i][j])
		{
			if (line_split[i][j] != '0' && line_split[i][j] != '1'
				&& line_split[i][j] != 'N' && line_split[i][j] != 'S'
				&& line_split[i][j] != 'E' && line_split[i][j] != 'W')
				map_wrong_process(g, line_split, line);
			j++;
		}
		i++;
	}
}

int	map_ns_check(t_game *g, char **l_split, char *line)
{
	if (ft_strcmp("NO", l_split[0]) == 0)
	{
		if (!l_split[1] || size_array_char(l_split) > 2)
			map_wrong_process(g, l_split, line);
		if (g->cub_list.n_count++ == 0 && g->cub_list.line_num == 0)
			g->cub_list.n_texture = ft_strdup(l_split[1]);
		if (g->cub_list.line_num != 0)
			map_wrong_process(g, l_split, line);
		char_tab_free(l_split);
		return (1);
	}
	if (ft_strcmp("SO", l_split[0]) == 0)
	{
		if (!l_split[1] || size_array_char(l_split) > 2)
			map_wrong_process(g, l_split, line);
		if (g->cub_list.s_count++ == 0 && g->cub_list.line_num == 0)
			g->cub_list.s_texture = ft_strdup(l_split[1]);
		if (g->cub_list.line_num != 0)
			map_wrong_process(g, l_split, line);
		char_tab_free(l_split);
		return (1);
	}
	return (0);
}

int	map_we_check(t_game *g, char **l_split, char *line)
{
	if (ft_strcmp("WE", l_split[0]) == 0)
	{
		if (!l_split[1] || size_array_char(l_split) > 2)
			map_wrong_process(g, l_split, line);
		if (g->cub_list.w_count == 0 && g->cub_list.line_num == 0)
			g->cub_list.w_texture = ft_strdup(l_split[1]);
		g->cub_list.w_count++;
		if (g->cub_list.line_num != 0)
			map_wrong_process(g, l_split, line);
		char_tab_free(l_split);
		return (1);
	}
	if (ft_strcmp("EA", l_split[0]) == 0)
	{
		if (!l_split[1] || size_array_char(l_split) > 2)
			map_wrong_process(g, l_split, line);
		if (g->cub_list.e_count == 0 && g->cub_list.line_num == 0)
			g->cub_list.e_texture = ft_strdup(l_split[1]);
		g->cub_list.e_count++;
		if (g->cub_list.line_num != 0)
			map_wrong_process(g, l_split, line);
		char_tab_free(l_split);
		return (1);
	}
	return (0);
}
