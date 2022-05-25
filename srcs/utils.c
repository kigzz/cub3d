/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpouchep <bpouchep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 17:46:34 by bpouchep          #+#    #+#             */
/*   Updated: 2022/05/25 17:46:35 by bpouchep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	size_array_char(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	create_trgb(t_rgb c)
{
	return (c.t << 24 | c.red << 16 | c.green << 8 | c.blue);
}
