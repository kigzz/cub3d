/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpouchep <bpouchep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:08:20 by bpouchep          #+#    #+#             */
/*   Updated: 2022/05/25 16:08:21 by bpouchep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	keyup(int k, t_game *g)
{
	if (k == K_LEFT)
		g->key_left_pressed = 0;
	else if (k == K_E)
		g->key_e_pressed = 0;
	else if (k == K_RIGHT)
		g->key_right_pressed = 0;
	else if (k == K_W)
		g->key_w_pressed = 0;
	else if (k == K_A)
		g->key_a_pressed = 0;
	else if (k == K_S)
		g->key_s_pressed = 0;
	else if (k == K_D)
		g->key_d_pressed = 0;
	return (0);
}

int	keydown(int k, t_game *g)
{
	if (k == K_ESC)
		all_free(g);
	else if (k == K_E)
		g->key_e_pressed = 1;
	else if (k == K_LEFT)
		g->key_left_pressed = 1;
	else if (k == K_RIGHT)
		g->key_right_pressed = 1;
	else if (k == K_W)
		g->key_w_pressed = 1;
	else if (k == K_A)
		g->key_a_pressed = 1;
	else if (k == K_S)
		g->key_s_pressed = 1;
	else if (k == K_D)
		g->key_d_pressed = 1;
	return (0);
}

void	check_key_status(t_game *g)
{
	if (g->key_left_pressed)
		key_press(g);
	if (g->key_right_pressed)
		key_press(g);
	if (g->key_w_pressed)
		key_press(g);
	if (g->key_s_pressed)
		key_press(g);
	if (g->key_a_pressed)
		key_press(g);
	if (g->key_d_pressed)
		key_press(g);
}
