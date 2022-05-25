/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpouchep <bpouchep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 17:47:00 by bpouchep          #+#    #+#             */
/*   Updated: 2022/05/25 17:47:01 by bpouchep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	check_str_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	check_rgb(t_game *g, char **rgb_split, char *line)
{
	int	i;

	i = 0;
	while (rgb_split[i])
	{
		if (check_str_digit(rgb_split[i]))
		{
			get_next_line(g->cub_list.fd, &line, -1);
			free(line);
			char_tab_free(rgb_split);
			error(g, "Color is wrong");
		}
		i++;
	}
}

void	check_rgb2(t_game *g, char *line)
{
	if (g->cub_list.floor.red < 0 || g->cub_list.floor.green < 0
		|| g->cub_list.floor.blue < 0 || g->cub_list.floor.red > 255
		|| g->cub_list.floor.green > 255 || g->cub_list.floor.blue > 255)
	{
		get_next_line(g->cub_list.fd, &line, -1);
		free(line);
		error(g, "Color is wrong");
	}
}
