/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpouchep <bpouchep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:08:15 by bpouchep          #+#    #+#             */
/*   Updated: 2022/05/25 16:08:16 by bpouchep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	check_xpm_size(t_game *g, char *line)
{
	char	**xpm;

	xpm = ft_split(&line[1], ' ');
	if (xpm == NULL)
		error(g, "ft_split failed");
	if (ft_atoi(xpm[0]) != 64 || ft_atoi(xpm[1]) != 64)
	{
		char_tab_free(xpm);
		error(g, "xpm file size is wrong");
	}
	char_tab_free(xpm);
}

void	xpm_file_check(t_game *g, int i, char *path)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		error(g, "Error open xpm file");
	count = 0;
	while (i > 0)
	{
		i = get_next_line(fd, &line, 0);
		if (i == -1)
			error(g, "get_next_line failed");
		if (count == 3)
			check_xpm_size(g, line);
		count++;
		free(line);
	}
}

void	load_image(t_game *g, int *texture, char *path, t_img *img)
{
	int	x;
	int	y;

	xpm_file_check(g, 1, path);
	img->img = mlx_xpm_file_to_image(g->mlx, path, &img->width, &img->height);
	if (img->img == NULL)
		error(g, "The path of texture is wrong");
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp,
			&img->size_l, &img->endian);
	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			texture[img->width * y + x] = img->data[img->width * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(g->mlx, img->img);
}

void	load_textures(t_game *g)
{
	t_img	img;

	load_image(g, g->texture[NO], g->cub_list.n_texture, &img);
	load_image(g, g->texture[SO], g->cub_list.s_texture, &img);
	load_image(g, g->texture[WE], g->cub_list.w_texture, &img);
	load_image(g, g->texture[EA], g->cub_list.e_texture, &img);
}
