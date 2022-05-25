/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpouchep <bpouchep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:10:43 by bpouchep          #+#    #+#             */
/*   Updated: 2022/05/25 16:10:44 by bpouchep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	build_map3(t_game *g, char **tmp, char *map_line)
{
	int	i;

	i = 0;
	while (i < g->cub_list.map_y - 1)
	{
		tmp[i] = (char *)malloc(sizeof(char)
				* (ft_strlen(g->cub_list.map[i]) + 1));
		if (tmp[i] == NULL)
			error(g, "Malloc failed");
		ft_strlcpy(tmp[i], g->cub_list.map[i],
			ft_strlen(g->cub_list.map[i]) + 1);
		i++;
	}
	tmp[i] = ft_strdup(map_line);
	if (tmp[i] == NULL)
		error(g, "ft_strdup failed");
	free(map_line);
	tmp[i + 1] = NULL;
	if (i > 0)
		char_tab_free(g->cub_list.map);
	g->cub_list.map = tmp;
}

void	build_map2(t_game *g, int count, char *line)
{
	char	**tmp;
	char	*map_line;

	if (g->cub_list.line_num != 0 && count - g->cub_list.line_num != 1)
	{
		get_next_line(g->cub_list.fd, &line, -1);
		free(line);
		error(g, "Map is wrong");
	}
	g->cub_list.line_num = count;
	g->cub_list.map_y++;
	map_line = ft_strdup(line);
	if (map_line == NULL)
		error(g, "ft_strdup failed");
	if ((int)ft_strlen(map_line) > g->cub_list.map_x)
		g->cub_list.map_x = ft_strlen(map_line);
	tmp = (char **)malloc(sizeof(char *) * (g->cub_list.map_y + 1));
	if (tmp == NULL)
		error(g, "Malloc failed");
	build_map3(g, tmp, map_line);
}

void	build_map(char *line, int count, t_game *g)
{
	char	**line_split;

	line_split = ft_split(line, ' ');
	if (line_split == NULL)
		error(g, "ft_split failed");
	if (line_split[0] == NULL)
	{
		char_tab_free(line_split);
		return ;
	}
	if (map_ns_check(g, line_split, line)
		|| map_we_check(g, line_split, line)
		|| floor_check(g, line_split, NULL, line)
		|| ceiling_check(g, line_split, NULL, line))
		return ;
	map_line_check(g, line_split, line);
	char_tab_free(line_split);
	build_map2(g, count, line);
}
