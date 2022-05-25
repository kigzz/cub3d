/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpouchep <bpouchep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:08:08 by bpouchep          #+#    #+#             */
/*   Updated: 2022/05/25 16:08:10 by bpouchep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw(t_game *g)
{
	int	x;
	int	y;

	y = 0;
	while (y < g->cub_list.height)
	{
		x = 0;
		while (x < g->cub_list.width)
		{
			g->img.data[y * g->cub_list.width + x] = g->buf[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(g->mlx, g->win, g->img.img, 0, 0);
}

int	main_loop(t_game *g)
{
	check_key_status(g);
	raycast(g);
	draw(g);
	return (0);
}

int	win_close(t_game *g)
{
	all_free(g);
	return (0);
}

void	read_cub_line(t_game *g, int i, char *path)
{
	int		count;
	char	*line;

	g->cub_list.fd = open(path, O_RDONLY);
	if (g->cub_list.fd == -1)
		error(g, "Error open .cub file");
	game_init(g);
	count = 0;
	while (i > 0)
	{
		i = get_next_line(g->cub_list.fd, &line, 0);
		if (i == -1)
			error(g, "get_next_line failed");
		count++;
		build_map(line, count, g);
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_game	game;

	insert_null(&game);
	argv_check(argc, argv, envp, &game);
	read_cub_line(&game, 1, argv[1]);
	init(&game);
	game.buf = (int **)malloc(sizeof(int *) * (game.cub_list.height));
	game.texture = (int **)malloc(sizeof(int *) * 4);
	if (!game.buf || !game.texture)
		error(&game, "Malloc buf | texture failed");
	buf_init(&game, 0, 0);
	texture_init(&game, 0, 0);
	load_textures(&game);
	game.win = mlx_new_window(game.mlx, game.cub_list.width,
			game.cub_list.height, "Please don't crash");
	game.img.img = mlx_new_image(game.mlx, game.cub_list.width,
			game.cub_list.height);
	game.img.data = (int *)mlx_get_data_addr(game.img.img, &game.img.bpp,
			&game.img.size_l, &game.img.endian);
	mlx_hook(game.win, 33, 1 << 17, &win_close, &game);
	mlx_hook(game.win, 02, 1L << 0, keydown, &game);
	mlx_hook(game.win, 03, 1L << 1, keyup, &game);
	mlx_loop_hook(game.mlx, &main_loop, &game);
	mlx_loop(game.mlx);
}
