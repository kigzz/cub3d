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

// -- CHECK MAP ELEMENTS

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

// -- CHECK SPACES
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

void	map_space_check(t_game *g)
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

// -- CHECK SPACE2

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
				|| g->cub_list.map_matrix[*i]
				   [g->cub_list.l_nowall_row + 1] != 1))
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

// -- CHECK TEXTURE PATH

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

// -- CHECK COLOR FLOOR AND CEILING

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


// -- UTILS : size char **
int	size_array_char(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

// -- UNIFY COLOR

int	create_trgb(t_rgb c)
{
	return (c.t << 24 | c.red << 16 | c.green << 8 | c.blue);
}


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
